// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

template<typename IS, typename OS>
struct bom
{
	typedef conversion::states states;

	inline static void write_utf8(OS& os, states& state);
	inline static void write_utf16(OS& os, states& state, const bool& big);
	inline static void write_utf32(OS& os, states& state, const bool& big);

	inline static bool read_utf16(IS& is, states& state, bool& is_big);
	inline static bool read_utf32(IS& is, states& state, bool& is_big);

	inline static bool is_bom(const utf8_t& cp);
	inline static bool is_bom(const utf16_t& cp);
	inline static bool is_bom(const utf32_t& cp);
};

template<typename IS, typename OS>
struct stream
{
	typedef conversion::states states;

	inline static bool write(OS& os, states& state, const utf8_t& value);
	inline static bool write(OS& os, states& state, const utf16_t& value, const bool& big);
	inline static bool write(OS& os, states& state, const utf32_t& value, const bool& big);

	inline static utf8_t  read_utf8(IS& is, states& state);
	inline static utf16_t read_utf16(IS& is, states& state, const bool& big);
	inline static utf32_t read_utf32(IS& is, states& state, const bool& big);

	inline static bool can_unget(IS& is);
	inline static bool is_eof(IS& is);
};

template<typename IS, typename OS>
inline void bom<IS, OS>::write_utf8(OS& os, states& state)
{
	using namespace charset::conversion;

	const cs_uint8 bytes[] = { 0xEF, 0xBB, 0xBF };
	os.write((const typename OS::char_type*)bytes, 3);
	state = os.good()? OK: WriteError;
}

template<typename IS, typename OS>
inline void bom<IS, OS>::write_utf16(OS& os, states& state, const bool& big)
{
	using namespace charset::conversion;

	cs_uint8 bytes[] = { 0xFF, 0xFE };
	if (big)
	{
		bytes[0] = 0xFE;
		bytes[1] = 0xFF;
	}

	os.write((const typename OS::char_type*)bytes, 2);
	state = os.good()? OK: WriteError;
}

template<typename IS, typename OS>
inline void bom<IS, OS>::write_utf32(OS& os, states& state, const bool& big)
{
	using namespace charset::conversion;

	cs_uint8 bytes[] = { 0xFF, 0xFE, 0x00, 0x00 };

	if (big)
	{
		bytes[0] = bytes[1] = 0x00;
		bytes[2] = 0xFE;
		bytes[3] = 0xFF;
	}

	os.write((const typename OS::char_type*)bytes, 4);
	state = os.good()? OK: WriteError;
}

template<typename IS, typename OS>
inline bool bom<IS, OS>::read_utf16(IS& is, states& state, bool& is_big)
{
	using namespace charset::conversion;

	state = OK;

	cs_uint8 bytes[2];
	is.read((const typename IS::char_type*)bytes, 2);

	if (!is.good())
	{
		state = is.eof()? UnexpectedEndOfFile: ReadError;
		return false;
	}

	if (bytes[0] == 0xFE && bytes[1] == 0xFF)
		return is_big = true;

	if (bytes[0] == 0xFF && bytes[1] == 0xFE)
	{
		is_big = false;
		return true;
	}

	state = InvalidUTF16BOM;
	return false;
}

template<typename IS, typename OS>
inline bool bom<IS, OS>::read_utf32(IS& is, states& state, bool& is_big)
{
	using namespace charset::conversion;

	state = OK;

	cs_uint8 bytes[4];
	is.read((const typename IS::char_type*)bytes, 4);

	if (!is.good())
	{
		state = is.eof()? UnexpectedEndOfFile: ReadError;
		return false;
	}

	if ((bytes[0] & bytes[1]) == 0x00 && bytes[2] == 0xFE && bytes[3] == 0xFF)
		return is_big = true;

	if (bytes[0] == 0xFF && bytes[1] == 0xFE && (bytes[2] & bytes[3]) == 0x00)
	{
		is_big = false;
		return true;
	}

	state = InvalidUTF32BOM;
	return false;
}

template<typename IS, typename OS>
inline bool bom<IS, OS>::is_bom(const utf8_t& cp)
{
	return cp.count == 3 && cp[0] == 0xEF && cp[1] == 0xBB && cp[2] == 0xBF;
}

template<typename IS, typename OS>
inline bool bom<IS, OS>::is_bom(const utf16_t& cp)
{
	return cp.count == 1 && cp[0] == 0xFEFF;
}

template<typename IS, typename OS>
inline bool bom<IS, OS>::is_bom(const utf32_t& cp)
{
	return cp == 0xFEFF;
}

template<typename IS, typename OS>
inline bool stream<IS, OS>::write(OS& os, states& state, const utf8_t& value)
{
	using namespace charset::conversion;

	os.write((const typename IS::char_type*)value.units, value.count);
	state = os.good()? OK: WriteError;
	return state == OK;
}

template<typename IS, typename OS>
inline bool stream<IS, OS>::write(OS& os, states& state, const utf16_t& value, const bool& big)
{
	using namespace charset::conversion;

	cs_uint8 bytes[4];

	if (big)
	{
		bytes[0] = value[0] >> 8;
		bytes[1] = value[0] & 0xFF;

		if (value.count == 2)
		{
			bytes[2] = value[1] >> 8;
			bytes[3] = value[1] & 0xFF;
		}
	}
	else
	{
		bytes[0] = value[0] & 0xFF;
		bytes[1] = value[0] >> 8;

		if (value.count == 2)
		{
			bytes[2] = value[1] & 0xFF;
			bytes[3] = value[1] >> 8;
		}
	}

	os.write((const typename IS::char_type*)bytes, value.count * 2);
	state = os.good()? OK: WriteError;
	return state == OK;
}

template<typename IS, typename OS>
inline bool stream<IS, OS>::write(OS& os, states& state, const utf32_t& value, const bool& big)
{
	using namespace charset::conversion;

	cs_uint8 bytes[4];

	if (big)
	{
		bytes[0] = (value >> 24) & 0xFF;
		bytes[1] = (value >> 16) & 0xFF;
		bytes[2] = (value >>  8) & 0xFF;
		bytes[3] = value & 0xFF;
	}
	else
	{
		bytes[0] = value & 0xFF;
		bytes[1] = (value >>  8) & 0xFF;
		bytes[2] = (value >> 16) & 0xFF;
		bytes[3] = (value >> 24) & 0xFF;
	}

	os.write((const typename IS::char_type*)bytes, 4);
	state = os.good()? OK: WriteError;
	return state == OK;
}

template<typename IS, typename OS>
inline utf8_t stream<IS, OS>::read_utf8(IS& is, states& state)
{
	using namespace charset::conversion;

	const utf8_t invalid = helper::not_defined<utf8_t>();

	state = OK;

	utf8_t value;
	is.get((typename IS::char_type&)value.units[0]);

	if (is.eof())
	{
		state = UnexpectedEndOfFile;
		return invalid;
	}

	if (value[0] < 0x80) return utf8_t(value[0]);

	if (value[0] == 0xC0 || value[0] == 0xC1 || (value[0] >= 0xF5 && value[0] <= 0xFF))
	{
		state = InvalidUTF8Byte;
		return invalid;
	}

	if ((value[0] & 0xF0) == 0xF0)
		value.count = 4;
	else if ((value[0] & 0xE0) == 0xE0)
		value.count = 3;
	else if ((value[0] & 0xC0) == 0xC0)
		value.count = 2;
	else
	{
		state = InvalidUTF8Byte;
		return invalid;
	}

	is.read((typename IS::char_type*)&value.units[1], value.count - 1);
	if (!is.good())
	{
		state = is.eof()? UnexpectedEndOfFile: ReadError;
		return invalid;
	}

	for (cs_int32 i=1; i<value.count; ++i)
	{
		if ((value[i] & 0x80) != 0x80)
		{
			state = InvalidUTF8Byte;
			return invalid;
		}
	}

	return value;
}

template<typename IS, typename OS>
inline utf16_t stream<IS, OS>::read_utf16(IS& is, states& state, const bool& big)
{
	using namespace charset::conversion;

	const utf16_t invalid = helper::not_defined<utf16_t>();

	state = OK;
	cs_uint8 bytes[2];

	is.read((typename IS::char_type*)bytes, 2);
	if (!is.good())
	{
		state = is.eof()? UnexpectedEndOfFile: ReadError;
		return invalid;
	}

	utf16_t value;
	value[0] = bytes[0];

	if (big)
		value[0] = (value[0] << 8) | cu16_t(bytes[1]);
	else
		value[0] |= cu16_t(bytes[1]) << 8;

	if (value[0] < helper::u16_surrogate_min || value[0] > helper::u16_surrogate_max)
	{
		value.count = 1;
		return value;
	}
	else
		value.count = 2;

	if (value[0] < helper::u16_lo_surrogate || value[0] > helper::u16_lo_surrogate_end)
	{
		state = InvalidUTF16Surrogate;
		return invalid;
	}

	is.read((typename IS::char_type*)bytes, 2);
	if (!is.good())
	{
		state = is.eof()? UnexpectedEndOfFile: ReadError;
		return invalid;
	}

	value[1] = bytes[0];

	if (big)
		value[1] = (value[1] << 8) | cu16_t(bytes[1]);
	else
		value[1] |= cu16_t(bytes[1]) << 8;

	if (value[1] < helper::u16_hi_surrogate || value[1] > helper::u16_hi_surrogate_end)
	{
		state = InvalidUTF16Surrogate;
		return invalid;
	}

	return value;
}

template<typename IS, typename OS>
inline utf32_t stream<IS, OS>::read_utf32(IS& is, states& state, const bool& big)
{
	using namespace charset::conversion;

	const utf32_t invalid = helper::not_defined_in_unicode;

	state = OK;
	cs_uint8 bytes[4];

	is.read((typename IS::char_type*)&bytes, 4);
	if (!is.good())
	{
		state = is.eof()? UnexpectedEndOfFile: ReadError;
		return invalid;
	}

	utf32_t value;

	if (big)
		value = (cu32_t(bytes[0]) << 24) | (cu32_t(bytes[1]) << 16) |
				(cu32_t(bytes[2]) << 8) | cu32_t(bytes[3]);
	else
		value = cu32_t(bytes[0]) | (cu32_t(bytes[1]) << 8) |
			   (cu32_t(bytes[2]) << 16) | (cu32_t(bytes[3]) << 24);

	if (value > helper::max_unicode_cp)
	{
		state = OutOfRangeUnicodeCodePoint;
		return invalid;
	}

	if (value >= helper::u16_surrogate_min && value <= helper::u16_surrogate_max)
	{
		state = UTF32InUTF16ReservedArea;
		return invalid;
	}

	return value;
}

template<typename IS, typename OS>
inline bool stream<IS, OS>::can_unget(IS& is)
{
	is.get();
	is.unget();
	return is.good();
}

template<typename IS, typename OS>
inline bool stream<IS, OS>::is_eof(IS& is)
{
	is.get();
	if (is.eof()) return true;
	is.unget();
	return false;
}
