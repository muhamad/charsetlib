// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

template<typename ICS, typename OCS, typename IS, typename OS>
struct ctu_converter
{
	typedef conversion::states states;
	typedef conversion::charset_map<ICS, OCS> cmap;

	inline static OS& execute(IS& is, OS& os, states& state, const bool& os_be, const bool& os_bom)
	{
		using namespace charset::conversion;
		typedef bom<IS, OS> utf_bom;
		typedef stream<IS, OS> utf_stream;

		state = OK;

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

		for(;;)
		{
			ncp_t c;
			is.get((typename IS::char_type&)c);
			if (is.eof()) return os;

			utf32_t value = ICS::convert_to_utf32(c);
			if (value == helper::not_defined_in_unicode) return set_state(os, state, CodePointNotDefinedInUnicode);

			switch(OCS::id)
			{
			case 0:
				if (!utf_stream::write(os, state, unicode::to_utf8(value))) return os;
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

private:
	inline static OS& set_state(OS& os, states& state, const states& value)
	{
		state = value;
		return os;
	}
};
