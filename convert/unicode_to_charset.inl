// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

template<typename ICS, typename OCS, typename IS, typename OS>
struct utc_converter
{
	typedef conversion::states states;

	inline static OS& execute(IS& is, OS& os, states& state)
	{
		using namespace charset::conversion;
		typedef bom<IS, OS> utf_bom;
		typedef stream<IS, OS> utf_stream;

		if (!utf_stream::can_unget(is))
		{
			state = NoUnget;
			return os;
		};

		bool is_big = false;
		state = OK;

		if (ICS::id == 0)
		{
			utf8_t value = utf_stream::read_utf8(is, state);
			if (state != OK) return os;

			if (!utf_bom::is_bom(value))
			{
				ccp_t code = OCS::convert_to_charset(value);
				if (code == helper::not_defined_in_charset) return set_state(os, state, CodePointNotDefinedInCharset);
				os.put( (typename OS::char_type)code );
				if (!os.good()) return set_state(os, state, WriteError);
			}
		}
		else if (ICS::id == 1)
		{
			if (!utf_bom::read_utf16(is, state, is_big)) return os;
		}
		else if (ICS::id == 2)
		{
			if (!utf_bom::read_utf32(is, state, is_big)) return os;
		}

		while(!utf_stream::is_eof(is))
		{
			ccp_t value = 0;

			if (ICS::id == 0)
			{
				utf8_t u8 = utf_stream::read_utf8(is, state);
				if (state != OK) break;
				value = OCS::convert_to_charset(u8);
			}
			else if (ICS::id == 1)
			{
				utf16_t u16 = utf_stream::read_utf16(is, state, is_big);
				if (state != OK) break;
				value = OCS::convert_to_charset(u16);
			}
			else if (ICS::id == 2)
			{
				utf32_t u32 = utf_stream::read_utf32(is, state, is_big);
				if (state != OK) break;
				value = OCS::convert_to_charset(u32);
			}

			if (value == helper::not_defined_in_charset) return set_state(os, state, CodePointNotDefinedInCharset);
			os.put( (typename OS::char_type)value );
			if (!os.good()) return set_state(os, state, WriteError);
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
