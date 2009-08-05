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

// Adapted from The Boost Libraries, v1.39.0. Original license follows:

//  boost/filesystem/path.hpp  -----------------------------------------------//

//  Copyright Beman Dawes 2002-2005
//  Copyright Vladimir Prus 2002

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

//  basic_path's stem(), extension(), and replace_extension() are based on
//  basename(), extension(), and change_extension() from the original
//  filesystem/convenience.hpp header by Vladimir Prus.

//----------------------------------------------------------------------------//

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class File : public virtual Object {
public:

    class iterator : public BidirectionalIterator<String, iterator> {
	friend class File;
    public:
        typedef BidirectionalIterator<String,iterator> super;
        iterator(bool begin = false, const File* obj = NULL);
        iterator(bool begin = false, File* obj = NULL);

        reference current() const {
            return cur;
        }
        void next() const;
        bool hasNext() const;

        bool equals(const iterator& other) const {
            return file == other.file && cur == other.cur && pos == other.pos;
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
        mutable MutableString cur;
        mutable idx_t pos;
    };

    S_ITERABLE(String)
public:

    File() {
    }

    File(const String s) {
        operator/=(s);
    }

    ~File() {
    }

    File & removeFilename();
    File & replaceExtension(const String newExt = String());

    const String toString() const {
        return path;
    }

    // file_string
    const String nativeString() const;

    File rootPath() const;
    String rootName() const;
    String rootDirectory() const;
    File relativePath() const;
    File parent() const;
    String filename() const;
    String stem() const;
    String extension() const;

    bool empty() const {
        return path == "";
    }
    bool complete() const;
    bool hasRootPath() const;
    bool hasRootName() const;
    bool hasRootDirectory() const;

    bool hasRelativePath() const {
        return !relativePath().empty();
    }

    bool hasFilename() const {
        return path != "";
    }

    bool hasParent() const {
        return !parent().empty();
    }

    File & operator=(const String s) {
        path = "";
        operator/=(s);
        return *this;
    }

    File & operator/=(const File & rhs) {
        return operator /=(rhs.toString());
    }

    File & operator/=(const String);

private:
    void appendSeparatorIfNeeded();
    void append(uchar c);

    String path;
};

bool operator==(const File& lhs, const File& rhs);
bool operator<(const File& lhs, const File& rhs);
File & operator/(const File& rhs, const File& lhs);

SYLPH_END_NAMESPACE

#endif	/* FILE_H_ */

