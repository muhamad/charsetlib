// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_CODEPOINT_HPP
#define CHARSET_CODEPOINT_HPP

#include "types.hpp"

namespace charset
{
namespace csi
{
// generic code-point type designed specifically for
// Unicode UTF-X but can be used with multi-byte character-sets
// only if they obey the design.
// T : must never be signed type
// len: maximum number of code-units
template<typename T, int len>
struct code_point
{
	typedef T code_unit;
	typedef code_point<T, len> type;
	static const cs_int32 max_units = len;

	union
	{
		T  units[len]; // code-point units
		cs_uint32 all;  // all code-units as unsigned integer
	};
	cs_int32 count; // number of occupied code-units

	// initialize to empty
	inline code_point() : all(0), count(0) {}
	// initialize with single code-unit
	inline code_point(const T& value) : all(0), count(1) { units[0] = value; }

	// access units using subscript operator
	inline T& operator[](int index) { return units[index]; }
	inline T operator[](int index) const { return units[index]; }

	// get all code-units as unsigned integer
	// BEWARE value of all units depends on platform byte-order
	inline operator cs_uint32() const { return all; }

	// assign all code-units at once and reset count
	// BEWARE value of all units depends on platform byte-order
	inline type& operator=(const cs_uint32& value)
	{
		all = value;
		count = 0;
		return *this;
	}
};
}
}

#endif // CHARSET_CODEPOINT_HPP
