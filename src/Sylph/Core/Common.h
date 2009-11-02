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
 * Created on 25 april 2009, 15:42
 */

#ifndef COMMON_H_
#define	COMMON_H_

/**
 * @file
 * @headerfile Sylph/Core/Common.h
 * This file is a shortcut to include many commonly used headers. Actually, it
 * will include the following headers (relative to @c Sylph/Core):
 * <code><ul>
 * <li>Any.h</li>
 * <li>Array.h</li>
 * <li>Dictionary.h</li>
 * <li>File.h</li>
 * <li>Primitives.h</li>
 * <li>Range.h</li>
 * <li>String.h</li>
 * <li>Exception.h</li>
 * </ul></code>
 * It also has 'using' statements for following classes:
 * <code><ul>
 * <li>Sylph::Array</li>
 * <li>Sylph::Dictionary</li>
 * <li>Sylph::String</li>
 * <li>Sylph::range</li>
 * </ul></code>
 * You can turn this of by defining the macro @c SYLPH_NO_COMMON_USING before
 * inclusion.
 */

#include "Any.h"
#include "Array.h"
#include "Dictionary.h"
#include "File.h"
#include "Primitives.h"
#include "Range.h"
#include "String.h"
#include "Exception.h"

#ifndef SYLPH_NO_COMMON_USING
using Sylph::Array;
using Sylph::Dictionary;
using Sylph::String;
using Sylph::range;
#endif


#endif	/* COMMON_H_ */

