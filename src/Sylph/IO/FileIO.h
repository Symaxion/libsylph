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
 * Created on 7 augustus 2009, 13:21
 */

#ifndef FILEIO_H_
#define	FILEIO_H_

#include "../Core/Object.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

namespace IO {
    enum IOType {
        Normal = 0,
        Text = Normal,
        Append = 1,
        Binary = 2
    };
}
SYLPH_END_NAMESPACE

#endif	/* FILEIO_H_ */

