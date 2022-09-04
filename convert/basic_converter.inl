// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

template<typename ICS, typename OCS, typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, false, false>::run()
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;
	char stream_char_type_must_be_of_type_char[ sizeof(CharT) == 1? 1: 0 ];

	return csi::charset_converter<ICS, OCS, IS, OS>::execute(is, os, iomap, cstate);
}

template<typename ICS, typename OCS, typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, false, true>::run()
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;
	char stream_char_type_must_be_of_type_char[ (sizeof(CharT) == 1)? 1: 0 ];
	char output_charset_must_be_UTF_8_16_or_32[ (OCS::id >= 0 && OCS::id <= 2)? 1: 0 ];

	return csi::ctu_converter<ICS, OCS, IS, OS>::execute(is, os, cstate, os_be, os_bom);
}

template<typename ICS, typename OCS, typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, true, false>::run()
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;
	char stream_char_type_must_be_of_type_char[ (sizeof(CharT) == 1)? 1: 0 ];
	char input_charset_must_be_UTF_8_16_or_32[ (ICS::id >= 0 && ICS::id <= 2)? 1: 0 ];

	return csi::utc_converter<ICS, OCS, IS, OS>::execute(is, os, cstate);
}

template<typename ICS, typename OCS, typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, true, true>::run()
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;
	char stream_char_type_must_be_of_type_char[ (sizeof(CharT) == 1)? 1: 0 ];
	char input_charset_must_be_UTF_8_16_or_32[ (ICS::id >= 0 && ICS::id <= 2)? 1: 0 ];
	char output_charset_must_be_UTF_8_16_or_32[ (OCS::id >= 0 && OCS::id <= 2)? 1: 0 ];

	return csi::unicode_converter<ICS, OCS, IS, OS>::execute(is, os, cstate, os_be, os_bom);
}
