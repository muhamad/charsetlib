// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_BASIC_CONVERTER_HPP
#define CHARSET_BASIC_CONVERTER_HPP

#include <istream>
#include <ostream>

#include "unicode_tags.hpp"
#include "charset_map.hpp"
#include "states.hpp"

namespace charset
{
namespace conversion
{

// convert data between character-sets
// ICS: input character-set
// OCS: output character-set
// IS: type with input data. (default std::istream)
// OS: type to save result data. (default std::ostream)
template<typename ICS, typename OCS,
		 typename IS = std::istream, typename OS = std::ostream,
		 bool ics_is_tag = csi::is_tag_class<ICS>::value,
		 bool ocs_is_tag = csi::is_tag_class<OCS>::value>
struct basic_converter;

// convert between non-Unicode character-sets using standard streams
template<typename ICS, typename OCS, typename CharT, typename Traits>
struct basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, false, false>
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;
	typedef charset_map<ICS, OCS> cs_map;

	inline basic_converter(IS& istm, OS& ostm, const cs_map& csmap)
		: is(istm), os(ostm), iomap(csmap), cstate(OK) {}

	inline static bool may_fail() { return true/*iomap.may_fail()*/; }

	inline OS& run();

	inline states state() const { return cstate; }

	inline bool failed() const { return cstate != OK; }

private:
	IS& is;
	OS& os;
	const cs_map& iomap;
	states cstate;
};

// convert character-set to Unicode using standard streams
template<class ICS, class OCS, typename CharT, typename Traits>
struct basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, false, true>
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;

	inline basic_converter(IS& istm, OS& ostm)
			: is(istm), os(ostm), cstate(OK), os_be(false), os_bom(false) {}
	inline basic_converter(IS& istm, OS& ostm, bool ostm_be)
			: is(istm), os(ostm), cstate(OK), os_be(ostm_be), os_bom(false) {}
	inline basic_converter(IS& istm, OS& ostm, bool ostm_be, bool ostm_bom)
			: is(istm), os(ostm), cstate(OK), os_be(ostm_be), os_bom(ostm_bom) {}

	inline static bool may_fail() { return ICS::have_undefined_unicode_chars; }

	inline OS& run();

	inline states state() const { return cstate; }

	inline bool failed() const { return cstate != OK; }

private:
	IS& is;
	OS& os;
	states cstate;
	bool os_be, os_bom;
};

// convert Unicode to character-set using standard streams
template<class ICS, class OCS, typename CharT, typename Traits>
struct basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, true, false>
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;

	inline basic_converter(IS& istm, OS& ostm) : is(istm), os(ostm), cstate(OK) {}

	inline static bool may_fail() { return true; }

	inline OS& run();

	inline states state() const { return cstate; }

	inline bool failed() const { return cstate != OK; }

private:
	IS& is;
	OS& os;
	states cstate;
};

// convert Unicode to Unicode using standard streams
template<class ICS, class OCS, typename CharT, typename Traits>
struct basic_converter<ICS, OCS, std::basic_istream<CharT, Traits>, std::basic_ostream<CharT, Traits>, true, true>
{
	typedef std::basic_istream<CharT, Traits> IS;
	typedef std::basic_ostream<CharT, Traits> OS;

	inline basic_converter(IS& istm, OS& ostm)
			: is(istm), os(ostm), cstate(OK), os_be(false), os_bom(false) {}
	inline basic_converter(IS& istm, OS& ostm, bool ostm_be)
			: is(istm), os(ostm), cstate(OK), os_be(ostm_be), os_bom(false) {}
	inline basic_converter(IS& istm, OS& ostm, bool ostm_be, bool ostm_bom)
			: is(istm), os(ostm), cstate(OK), os_be(ostm_be), os_bom(ostm_bom) {}

	inline static bool may_fail() { return false; }

	inline OS& run();

	inline states state() const { return cstate; }

	inline bool failed() const { return cstate != OK; }

private:
	IS& is;
	OS& os;
	states cstate;
	bool os_be, os_bom;
};

}

namespace csi
{
#include "helper.inl"
#include "charset_to_charset.inl"
#include "charset_to_unicode.inl"
#include "unicode_to_unicode.inl"
#include "unicode_to_charset.inl"
}

namespace conversion
{
#include "basic_converter.inl"
}

}

#endif // CHARSET_BASIC_CONVERTER_HPP
