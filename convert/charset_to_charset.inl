// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

template<typename ICS, typename OCS, typename IS, typename OS>
struct charset_converter
{
	typedef conversion::states states;
	typedef conversion::charset_map<ICS, OCS> cmap;

	inline static OS& execute(IS& is, OS& os, const cmap& m, states& state)
	{
		using namespace charset::conversion;

		ncp_t c = 0;
		state = OK;

		for(;;)
		{
			is.get((typename IS::char_type&)c);
			if (is.eof()) return os;

			if (c >= ICS::cp_count) return set_state(os, state, OutOfRangeCharsetCodePoint);
			const ccp_t r = m[c];
			if (r == helper::not_defined_in_charset) return set_state(os, state, CodePointNotDefinedInCharset);

			os.put( (typename IS::char_type)r );
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
