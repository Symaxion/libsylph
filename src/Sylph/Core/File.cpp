#include "File.h"
#include "Primitives.h"
#include "../OS/GuessOS.h"
#include "StringBuffer.h"

SYLPH_BEGIN_NAMESPACE

inline bool isSerparator(uchar c) {
    return c == '/'
#ifdef SYLPH_OS_WINDOWS
            || c == '\\'
#endif
            ;
}


idx_t filenamePos(const String str, idx_t endpos) {


    // case: "//"
    if (endpos == 2 && str == "//") return 0;

    // case: ends in "/"
    if (endpos && str.at(endpos - 1) == '/')
        return endpos - 1;

    // set pos to start of last element
    sidx_t pos = str.lastIndexOf("/", endpos - 1);
#ifdef SYLPH_OS_WINDOWS
    if (pos == -1)
        pos = str.lastIndexOf("\\", endpos - 1);
    if (pos == -1)
        pos = str.lastIndexOf(":", endpos - 2);
#endif

    return ( pos == -1 // path itself must be a filename (or empty)
            || (pos == 1 && str.at(0) == '/')) // or net
            ? 0 // so filename is entire string
            : pos + 1; // or starts after delimiter
}

void firstElement(const String  src, idx_t & elementPos ,size_t & elementSize,
        ssize_t len = -1) {
    if (len == -1) len = src.length();
    elementPos = 0;
    elementSize = 0;
    if (src == "") return;

    size_t cur = 0;

    // deal with // [network]
    if (len >= 2 && src.startsWith("//")
            && (len == 2
            || src.at(2) != '/')) {
        cur += 2;
        elementSize += 2;
    }// leading (not non-network) separator
    else if (src.startsWith("/")) {
        ++elementSize;
        // bypass extra leading separators
        while (cur + 1 < len
                && src.at(cur + 1) == '/') {
            ++cur;
            ++elementPos;
        }
        return;
    }

    // at this point, we have either a plain name, a network name,
    // or (on Windows only) a device name

    // find the end
    while (cur < len
#ifdef SYLPH_OS_WINDOWS
            && src.at(cur) != ':'
#endif
            && src.at(cur) != '/') {
        ++cur;
        ++elementSize;
    }

#ifdef SYLPH_OS_WINDOWS
    if (cur == len) return;
    // include device delimiter
    if (src.at(cur) == ':') {
        ++elementSize;
    }
#endif

    return;
}

sidx_t rootDirectoryStart(const String & s, size_t len) {

#ifdef SYLPH_OS_WINDOWS
    // case "c:/"
    if (len > 2 && s.at(1) == ':' && s.at(2) == '/') return 2;
#endif

    // case "//"
    if (len == 2 && s.at(0) == '/' && s.at(1) == '/') return -1;

    // case "//net {/}"
    if (len > 3 && s.at(0) == '/' && s.at(1) == '/' && s.at(2) != '/') {
        idx_t pos = s.indexOf('/', 2);
        return pos < len ? pos : -1;
    }

    // case "/"
    if (len > 0 && s.at(0) == '/') return 0;

    return -1;
}

bool isNonRootSlash(const String & str, idx_t pos) {

    if (str == "" || str.at(pos) != '/')
        sthrow(IllegalArgumentException, "No / at pos!");

        // subsequent logic expects pos to be for leftmost slash of a set
        while (pos > 0 && str.at(pos - 1) == '/')
            --pos;

    return pos != 0
            && (pos <= 2 || str.at(1) != '/'
            || str.indexOf('/', 2) != pos)
#ifdef SYLPH_OS_WINDOWS
            && (pos != 2 || str.at(1) != ':')
#endif
            ;
}

String File::filename() const {
    idx_t endpos = filenamePos(path, path.length());
    return (path.length() && endpos && path.at(endpos) == '/'
            && isNonRootSlash(path, endpos)) ? String('.')
            : path.substring(endpos);
}

String File::stem() const {
    String name = filename();
    idx_t n = name.lastIndexOf('.');
    return name.substring(0, n);
}

String File::extension() const {
    String name = filename();
    idx_t n = name.lastIndexOf('.');
    return n == -1 ? "" : name.substring(n);
}

File File::parent() const {
    idx_t endpos = filenamePos(path, path.length()-1);

    bool filenameWasSerparator = path.length() && path.at(endpos) == '/';

    // skip separators unless root directory
    idx_t rootDirPos = rootDirectoryStart(path, endpos);
    for (; endpos > 0 && (endpos - 1) != rootDirPos &&
            path.at(endpos - 1) == '/'; --endpos) {
    }

    return (endpos == 1 && rootDirPos == 0 && filenameWasSerparator)
            ? File() : File(path.substring(0, endpos));
}

// 2do

File File::relativePath() const {
    iterator itr(begin());
    for (; itr.pos != path.length()
            && (itr.cur.at(0) == '/'
#ifdef SYLPH_OS_WINDOWS
            || itr.m_name[itr.m_name.size() - 1]
            == colon<path_type>::value
#endif
            ); ++itr) {
    }

    return File(path.substring(itr.pos));
}

String File::rootName() const {
    iterator itr(begin());

    return ( itr.pos != path.length()
            && (
            (itr.cur.length() > 1 && itr.cur.startsWith("//")
            )
#ifdef SYLPH_OS_WINDOWS
            || itr.cur.at(itr.m_name.size() - 1) == ':'
#endif
            ))
            ? *itr
            : "";
}

String File::rootDirectory() const {
    idx_t start = rootDirectoryStart(path, path.length());

    return start == -1 ? "" : path.substring(start, 1);
}

File File::rootPath() const {
    // even on POSIX, root_name() is non-empty() on network paths
    return File(rootName()) /= rootDirectory();
}

bool File::complete() const {
#ifdef BOOST_WINDOWS_PATH
    return hasRootName() && hasRootDirectory();
#else
    return hasRootDirectory();
#endif
}

bool File::hasRootPath() const {
    return rootPath().toString() != "";
}

bool File::hasRootName() const {
    return rootName() != "";
}

bool File::hasRootDirectory() const {
    return rootDirectory() != "";
}

void File::appendSeparatorIfNeeded() {
    if (
#ifdef SYLPH_OS_WINDOWS
            path.at(path.length() - 1) != ':' &&
#endif
            path.at(path.length() - 1) != '/') {
        path += (uchar)'/';
    }
}

void File::append(uchar value) {

#ifdef SYLPH_OS_WINDOWS
    path += (value == '\\' ? '/' : value);
#else
    path += value;
#endif
}

File& File::operator/=(const String next) {
    // ignore escape sequence on POSIX or Windows
    if (next.startsWith("//:")) next = next.substring(3);

    // append slash<path_type>::value if needed
    if (!empty() && (next.length()) != 0
            && !next.startsWith("/")) {
        appendSeparatorIfNeeded();
    }

    for (idx_t i = 0; i < next.length(); ++i) append(next.at(i));
    return *this;
}

/* I don't really know what to do with this...
 *
 * File & File::append(
InputIterator first, InputIterator last) {
    // append slash<path_type>::value if needed
    if (!empty() && first != last
            && !detail::is_separator<path_type > (*first)) {
        m_append_separator_if_needed();
    }

    // song-and-dance to avoid violating InputIterator requirements
    // (which prohibit lookahead) in detecting a possible escape sequence
    // (escape sequences are simply ignored on POSIX and Windows)
    bool was_escape_sequence(true);
    std::size_t append_count(0);
    typename String::size_type initial_pos(m_path.size());

    for (; first != last && *first; ++first) {
        if (append_count == 0 && *first != slash<path_type>::value)
            was_escape_sequence = false;
        if (append_count == 1 && *first != slash<path_type>::value)
            was_escape_sequence = false;
        if (append_count == 2 && *first != colon<path_type>::value)
            was_escape_sequence = false;
        m_append(*first);
        ++append_count;
    }

    // erase escape sequence if any
    if (was_escape_sequence && append_count >= 3)
        m_path.erase(initial_pos, 3);

    return *this;
}*/

File& File::removeFilename() {
    path = path.substring(0, filenamePos(path, path.length()));
    return *this;
}

File & File::replaceExtension(const String newExt) {
    // erase existing extension if any
    String oldExt = extension();
    if (oldExt != 0)
        path = path.substring(0, path.length() - oldExt.length());

    if (newExt != "" && newExt.at(0) != '.')
        path += '.';

    path += newExt;

    return *this;
}

const String File::nativeString() const {
#ifdef SYLPH_OS_WINDOWS
    // for Windows, use the alternate separator, and bypass extra
    // root separators

    idx_t rootDirStart = rootDirectoryStart(path, path.length());
    bool inRoot = rootDirStart != -1;
    StringBuffer buf;
    for (idx_t idx = 0; idx != path.length(); ++idx) {
        // special case // [net]
        if (idx == 0 && path.length() > 1 && path.startsWith("//")
                && (path.length() == 2 || path.at(2) != '/')) {
            ++idx;
            buf << "\\\\";
            continue;
        }

        // bypass extra root separators
        if (inRoot) {
            if (buf.length() > 0 && buf.at(buf.length() - 1) == '\\'
                    && path.at(idx) == '/') continue;
        }

        buf << path.at(idx) == '/' ? '\\' : path.at(idx);

        if (idx > rootDirStart && path.at(idx) == '/') {
            inRoot = false;
        }
    }
    return buf;
#else
    return path;
#endif
}

File::iterator::iterator(bool begin, const File* obj)
    : File::iterator::super(begin), file(const_cast<File*>(obj)) {

    if (begin) {
        size_t elementSize;
        firstElement(file, pos, elementSize);
        cur = file->path.substring(pos, elementSize);
    } else {
        pos = file->path.length();
    }
}

File::iterator::iterator(bool begin, File* obj)
    : File::iterator::super(begin), file(const_cast<File*>(obj)) {

    if (begin) {
        size_t elementSize;
        firstElement(file, pos, elementSize);
        cur = file->path.substring(pos, elementSize);
    } else {
        pos = file->path.length();
    }
}

void File::iterator::next() const {
    bool wasNet = cur.startsWith("//") && cur.at(2) != '/';

    // increment to position past current element
    pos += cur.length();

    // if end reached, create end iterator
    if (pos == file->path.length()) {
        cur = "";
        return;
    }

    // process separator (Windows drive spec is only case not a separator)
    if (file->path.at(pos) == '/') {
        // detect root directory
        if (wasNet
#ifdef SYLPH_OS_WINDOWS
                // case "c:/"
                || cur.at(cur.length() - 1) == ':'
#endif
                ) {
            cur = '/';
            return;
        }

        // bypass separators
        while (pos != file->path.length()
                && file->path.at(pos) == '/') {
            ++pos;
        }

        // detect trailing separator, and treat it as ".", per POSIX spec
        if (pos == file->path.length() && isNonRootSlash(file->path, pos - 1)) {
            --pos;
            cur = '.';
            return;
        }
    }

    // get next element
    idx_t endPos = file->path.indexOf('/', pos);
    cur = file->path.substring(pos, endPos - pos);
}

bool File::iterator::hasNext() const {
    return pos < file->path.length();
}

void File::iterator::previous() const {
    idx_t endPos = pos;

    idx_t rootDirPos = rootDirectoryStart( file->path, endPos);

    // if at end and there was a trailing non-root '/', return "."
    if (pos == file->path.length() && file->path.length() > 1
            && file->path.at(pos - 1) == '/' && isNonRootSlash(file->path,
            pos - 1)) {
        --pos;
        cur = '.';
        return;
    }

    // skip separators unless root directory
    for (; endPos > 0 && (endPos - 1) != rootDirPos
            && file->path.at(endPos - 1) == '/'; --endPos) {}

    pos = filenamePos(file->path, endPos);
    cur = file->path.substring(pos, endPos - pos);
}
bool File::iterator::hasPrevious() const {
    return pos;
}

SYLPH_END_NAMESPACE