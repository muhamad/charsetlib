// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_HPP
#define CHARSET_HPP

#include "unicode/unicode.hpp"
#include "encoding/include.hpp"
#include "convert/basic_converter.hpp"

#define CHARSET_MAJ 1
#define CHARSET_MIN 1
#define CHARSET_FIX 1
#define CHARSET_VER ((CHARSET_MAJ << 24) | (CHARSET_MIN << 16) | CHARSET_FIX)

#endif // CHARSET_HPP
