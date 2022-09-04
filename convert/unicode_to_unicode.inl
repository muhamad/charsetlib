// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

template<typename ICS, typename OCS, typename IS, typename OS>
struct unicode_converter
{
	typedef conversion::states states;
	typedef conversion::charset_map<ICS, OCS> cmap;

	inline static OS& execute(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom)
	{
		using namespace charset::conversion;
		if (!stream<IS, OS>::can_unget(is))
		{
			state = NoUnget;
			return os;
		};

		state = OK;

		switch(ICS::id)
		{
		case 0: // UTF-8
			return utf8_to_any(is, os, state, os_be, os_bom);
		case 1: // UTF-16
			return utf16_to_any(is, os, state, os_be, os_bom);
		case 2: // UTF-32
			return utf32_to_any(is, os, state, os_be, os_bom);
		}

		return os;
	}

private:
	inline static OS& utf8_to_any (IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom);
	inline static OS& utf16_to_any(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom);
	inline static OS& utf32_to_any(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom);
};

template<typename ICS, typename OCS, typename IS, typename OS>
inline OS& unicode_converter<ICS, OCS, IS, OS>::
utf8_to_any(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom)
{
	using namespace charset::conversion;
	typedef bom<IS, OS> utf_bom;
	typedef stream<IS, OS> utf_stream;

	utf8_t value = utf_stream::read_utf8(is, state);
	if (state != OK) return os;

	// if output stream is not UTF-8, BOM must be written
	if (os_bom /*|| OCS::id != 0*/)
	{
		switch(OCS::id)
		{
		case 0:
			utf_bom::write_utf8(os, state);
			break;

		case 1:
			utf_bom::write_utf16(os, state, os_be);
			break;

		case 2:
			utf_bom::write_utf32(os, state, os_be);
			break;
		}
		if (state != OK) return os;
	}

	if (!utf_bom::is_bom(value))
	{
		switch(OCS::id)
		{
		case 0:
			if (!utf_stream::write(os, state, value)) return os;
			break;
		case 1:
			if (!utf_stream::write(os, state, unicode::to_utf16(value), os_be)) return os;
			break;
		case 2:
			if (!utf_stream::write(os, state, unicode::to_utf32(value), os_be)) return os;
			break;
		}
	}

	while(!utf_stream::is_eof(is))
	{
		value = utf_stream::read_utf8(is, state);
		if (state != OK) break;

		switch(OCS::id)
		{
		case 0:
			if (!utf_stream::write(os, state, value)) return os;
			break;
		case 1:
			if (!utf_stream::write(os, state, unicode::to_utf16(value), os_be)) return os;
			break;
		case 2:
			if (!utf_stream::write(os, state, unicode::to_utf32(value), os_be)) return os;
			break;
		}
	}

	return os;
}

template<typename ICS, typename OCS, typename IS, typename OS>
inline OS& unicode_converter<ICS, OCS, IS, OS>::
utf16_to_any(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom)
{
	using namespace charset::conversion;
	typedef bom<IS, OS> utf_bom;
	typedef stream<IS, OS> utf_stream;

	bool is_big = false;
	if (!utf_bom::read_utf16(is, state, is_big)) return os;

	// if output stream is not UTF-8, BOM must be written
	if (os_bom /*|| OCS::id != 0*/)
	{
		switch(OCS::id)
		{
		case 0:
			utf_bom::write_utf8(os, state);
			break;

		case 1:
			utf_bom::write_utf16(os, state, os_be);
			break;

		case 2:
			utf_bom::write_utf32(os, state, os_be);
			break;
		}
		if (state != OK) return os;
	}

	while(!utf_stream::is_eof(is))
	{
		utf16_t value = utf_stream::read_utf16(is, state, is_big);
		if (state != OK) break;

		switch(OCS::id)
		{
		case 0:
			if (!utf_stream::write(os, state, unicode::to_utf8(value) )) return os;
			break;
		case 1:
			if (!utf_stream::write(os, state, value, os_be)) return os;
			break;
		case 2:
			if (!utf_stream::write(os, state, unicode::to_utf32(value), os_be)) return os;
			break;
		}
	}

	return os;
}

template<typename ICS, typename OCS, typename IS, typename OS>
inline OS& unicode_converter<ICS, OCS, IS, OS>::
utf32_to_any(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom)
{
	using namespace charset::conversion;
	typedef bom<IS, OS> utf_bom;
	typedef stream<IS, OS> utf_stream;

	bool is_big = false;
	if (!utf_bom::read_utf32(is, state, is_big)) return os;

	// if output stream is not UTF-8, BOM must be written
	if (os_bom /*|| OCS::id != 0*/)
	{
		switch(OCS::id)
		{
		case 0:
			utf_bom::write_utf8(os, state);
			break;

		case 1:
			utf_bom::write_utf16(os, state, os_be);
			break;

		case 2:
			utf_bom::write_utf32(os, state, os_be);
			break;
		}
		if (state != OK) return os;
	}

	while(!utf_stream::is_eof(is))
	{
		utf32_t value = utf_stream::read_utf32(is, state, is_big);
		if (state != OK) break;

		switch(OCS::id)
		{
		case 0:
			if (!utf_stream::write(os, state, unicode::to_utf8(value) )) return os;
			break;
		case 1:
			if (!utf_stream::write(os, state, unicode::to_utf16(value), os_be)) return os;
			break;
		case 2:
			if (!utf_stream::write(os, state, value, os_be)) return os;
			break;
		}
	}

	return os;
}
