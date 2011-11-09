/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Created on 16 juli 2009, 14:41
 */

#ifndef SYLPH_CORE_FILE_H_
#define	SYLPH_CORE_FILE_H_

#include "Object.h"
#include "String.h"
#include "Iterator.h"
#include "Iterable.h"

SYLPH_BEGIN_NAMESPACE

// chmod constants
const suint S_MOD_OWN = 0x100;
const suint S_MOD_GRP = 0x010;
const suint S_MOD_OTH = 0x001;
const suint S_MOD_ALL = 0x111;

const suint S_MOD_N = 0x8;
const suint S_MOD_R = 0x4;
const suint S_MOD_W = 0x2;
const suint S_MOD_X = 0x1;
const suint S_MOD_K = 0x0;

/**
 * File represents the path to a file.
 * @todo update documentation!
 */
class File : public virtual Object {
public:

    template<class C, class V> class S_ITERATOR;
    template<class C, class V> friend class S_ITERATOR;

    template<class C, class V>
    class S_ITERATOR : public BidirectionalIterator<V, S_ITERATOR<C,V> > {
	friend class File;
    public:
        typedef BidirectionalIterator<V,S_ITERATOR<C,V> > super;

        S_ITERATOR(bool begin = false, C* obj = null);

        typename super::value_type& current() {
            return cur;
        }

        typename super::const_reference current() const {
            return cur;
        }

        void next();
        bool hasNext() const;

        template<class C1, class V1>
        bool equals(const S_ITERATOR<C1,V1>& other) const {
            return file == other.file && pos == other.pos;
        }

        template<class C1, class V1>
        S_ITERATOR(const S_ITERATOR<C1,V1> & other) {
            file = other.file;
            cur = other.cur;
            pos = other.pos;
        }
        bool hasPrevious() const;
        void previous();
    //private:
        C* file;
        String cur;
        idx_t pos;
    };

    S_ITERABLE(File, String)
public:

    /**
     * Default constructor. Creates an empty path reference.
     */
    File() {
    }

    /**
     * Creates a file from given path.
     * @param s A path in the notational conventions of the current OS.
     */
    File(const String s) {
        append(s,true);
    }

    /**
     * Creates a file from given path as a C string.
     * @param s A path, as a C string, in the notational conventions of the
     * current OS.
     */
    File(const char* s) {
        append(String(s),true);
    }

    virtual ~File() {
    }

    /**
     * Replaces the extension of this abstract pathname with given, or none.
     * @return A reference to this File object.
     */
    File& replaceExtension(const String newExt = String());

    /**
     * @return A string, containg the internal representation of this pathname,
     * in the notational conventions of the current OS.
     */
    const String toString() const {
        return path;
    }

    /**
     * @return the root this file is on (unix: '/')
     * @crossplatform Does not work on Windows.
     */
    inline File rootPath() const {
        return File(rootName());
    }

    /**
     * @return The root this file is on, as a string.
     * @crossplatform Does not work on Windows.
     */
    String rootName() const;

    /** 
     * @return The parent directory of this file.
     */
    File parent() const;

    /** 
     * Returns the name of the file itself. The file name is defined as 
     * everything in the path from the last file seperator to the end.
     * E.g, <code>/var/log/foo</code> would give <code>foo</code>, 
     * <code>/var/cache/</code> would give <code>cache</code>.
     * @return The file name component of the path.
     */
    String filename() const;

    /**
     * Returns the file name without the extension.
     * @return The file name without the extension.
     */
    String stem() const;

    /**
     * Returns the extension of this file. The extension is everything from the
     * last dot to the end, unless the file name starts with a dot.
     * @return The file extension.
     */
    String extension() const;

    /**
     * @return If this File's path is equal to the emtpy path.
     */
    inline bool empty() const {
        return path == "";
    }

    /**
     * Returns if this File's pathname is absolute. A pathname is absolute if
     * and only if it's location is not relative to the current working
     * directory, in other words it starts with a root.
     * @return @c true if the path of this file is absolute
     */
    bool absolute() const;

    /** */
    bool canonical() const;

    /** */
    File toAbsolute() const;

    /** */
    inline String toAbsoluteName() const {
        return toAbsolute().toString();
    }

    /** */
    File toCanonical() const;

    /** */
    inline String toCanonicalName() const {
        return toAbsolute().toString();
    }

    /** */
    bool hasFilename() const {
        return filename() != "";
    }

    /** */
    bool hasParent() const {
        return !parent().empty();
    }

    /**
     * Checks whether a given pathname exists.
     * @return true if and only if the pathname exists
     * @throw IOException If an IO error occurs.
     * @crossplatform Does not work on Windows.
     */
    bool exists() const throw(IOException);

    /**
     * Creates an empty file if it doesn't exist. 
     * @return <i>true</i> if a new file is created, <i>false</i> otherwise.
     * @throw IOException If an IO error occurs.
     */
    bool create() const throw(IOException);

    /** 
     * Attempts to remove this file if it exists.
     * @return <i>true</i> if the file was successfully removed.
     * @throw IOException if an IO error occurs.
     */
    bool remove() const throw(IOException);

    /** */
    bool canRead() const throw(IOException);

    /** */
    bool canWrite() const throw(IOException);

    bool mkdir() const throw(IOException);

    /** */
    bool mkdirs() const throw(IOException);

    /** */
    bool isFile() const throw(IOException);

    /** */
    bool isDirectory() const throw(IOException);

    /** */
    bool chmod(suint mode, bool sylphmode = false) const throw(IOException);

    /** */
    Array<File> contents() const throw(IOException);

    /** */
    static File workingDir() throw(IOException);

    /** */
    inline File& operator=(const File& f) {
        return operator=(f.path);
    }

    /** */
    inline File& operator=(const String s) {
        path = "";
        operator/=(s);
        return *this;
    }

    /** */
    inline File& operator=(const char* s) {
        return operator=(String(s));
    }

    /** */
    File& operator/=(const File& rhs) {
        return operator /=(rhs.toString());
    }

    /** */
    File& operator/=(const String);

    /** */
    inline File& operator/=(const char* s) {
        return operator/=(String(s));
    }

    /** */
    static const String Separator;

private:
    File& append(String, bool);

    String path;
};

/** */
inline bool operator==(const File& lhs, const File& rhs) {
    return lhs.toCanonicalName() == rhs.toCanonicalName();
}

/** */
inline bool operator<(const File& lhs, const File& rhs) {
    return lhs.toCanonicalName() < rhs.toCanonicalName();
}

S_CMP_SEQ(const File&)

/** */
inline File operator/(const File& lhs, const File& rhs) {
    return File(lhs) /= rhs;
}

/** */
inline std::ostream& operator<<(std::ostream& lhs, const File& rhs) {
    return lhs << rhs.toString();
}

SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_FILE_H_ */

