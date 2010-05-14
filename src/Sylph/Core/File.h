/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 16 juli 2009, 14:41
 */

#ifndef FILE_H_
#define	FILE_H_

#include "Object.h"
#include "String.h"
#include "Iterator.h"
#include "Iterable.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

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

    class iterator;
    friend class iterator;
    class iterator : public BidirectionalIterator<String, iterator> {
	friend class File;
    public:
        typedef BidirectionalIterator<String,iterator> super;
        iterator(bool begin = false, const File* obj = null);
        iterator(bool begin = false, File* obj = null);

        reference current() const {
            return cur;
        }
        void next() const;
        bool hasNext() const;

        bool equals(const iterator& other) const {
            return file == other.file && pos == other.pos;
        }

        iterator(const iterator& other) {
            file = other.file;
            cur = other.cur;
            pos = other.pos;
        }
        bool hasPrevious() const;
        void previous() const;
    private:
        File * file;
        mutable String cur;
        mutable idx_t pos;
    };

    S_ITERABLE(String)
public:

    /**
     * Default constructor. Creates an empty path reference.
     */
    File() {
    }

    /**
     * Creates a file from given path.
     */
    File(const String s) {
        operator/=(s);
    }

    /**
     * Creates a file from given path as a C string.
     */
    File(const char* s) {
        operator/=(String(s));
    }

    virtual ~File() {
    }

    /**
     * Replaces the extension of this abstract pathname with given, or none.
     * @return this
     */
    File& replaceExtension(const String newExt = String());

    /**
     * @return internal representation of this pathname
     */
    const String toString() const {
        return path;
    }

    /**
     * @return the root this file is on (unix: '/')
     */
    inline File rootPath() const {
        return File(rootName());
    }

    /**
     * @return the root this file is on, as a string
     */
    String rootName() const;

    File parent() const;

    String filename() const;

    String stem() const;

    String extension() const;

    inline bool empty() const {
        return path == "";
    }

    bool absolute() const;
    bool canonical() const;

    File toAbsolute() const;
    inline String toAbsoluteName() const {
        return toAbsolute().toString();
    }
    File toCanonical() const;
    inline String toCanonicalName() const {
        return toAbsolute().toString();
    }

    bool hasFilename() const {
        return path != "";
    }

    bool hasParent() const {
        return !parent().empty();
    }

    bool exists() const;
    bool create() const;
    bool remove() const;

    bool canRead() const;
    bool canWrite() const;

    bool mkdir() const;
    bool mkdirs() const;

    bool isFile() const;
    bool isDirectory() const;

    bool chmod(suint mode, bool sylphmode = false) const;

    Array<File> contents() const;
    static File workingDir();

    inline File& operator=(const File& f) {
        return operator=(f.path);
    }

    inline File& operator=(const String s) {
        path = "";
        operator/=(s);
        return *this;
    }

    inline File& operator=(const char* s) {
        return operator=(String(s));
    }

    File& operator/=(const File & rhs) {
        return operator /=(rhs.toString());
    }

    File& operator/=(const String);

    inline File& operator/=(const char* s) {
        return operator/=(String(s));
    }

    static const String Separator;

private:

    String path;
};

inline bool operator==(const File& lhs, const File& rhs) {
    return lhs.toCanonicalName() == rhs.toCanonicalName();
}
inline bool operator<(const File& lhs, const File& rhs) {
    return lhs.toCanonicalName() < rhs.toCanonicalName();
}

S_CMP_SEQ(const File&)

inline File operator/(const File& lhs, const File& rhs) {
    return File(lhs) /= rhs;
}
inline std::ostream& operator<<(std::ostream& lhs, const File& rhs) {
    return lhs << rhs.toString();
}

SYLPH_END_NAMESPACE

#endif	/* FILE_H_ */

