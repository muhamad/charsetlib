// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_ARRAY_HPP
#define CHARSET_ARRAY_HPP

namespace charset
{
namespace csi
{

template<typename T, int size>
struct array
{
	static const int count = size;
	T e[size];

	T& operator[](int i) { return e[i]; }
	T operator[](int i) const { return e[i]; }
};

}
}

#endif // CHARSET_ARRAY_HPP
