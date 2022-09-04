// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_MAP_HPP
#define CHARSET_MAP_HPP

#include "unicode_tags.hpp"
#include "../helper/array.hpp"

namespace charset
{
namespace conversion
{

// conversion map
template<typename ICS, typename OCS,
		 bool ics_tag = csi::is_tag_class<ICS>::value,
		 bool ocs_tag = csi::is_tag_class<OCS>::value,
		 bool ics_mb = !ics_tag && ICS::is_multibyte,
		 bool ocs_mb = !ocs_tag && OCS::is_multibyte>
struct charset_map;

// only allowed between non-Unicode character-sets which are non-multibyte
template<typename ICS, typename OCS>
struct charset_map<ICS, OCS, false, false, false, false>
{
	static const bool both_have_ascii = ICS::ascii_compatible && OCS::ascii_compatible;
	static const cs_int32 array_size = ICS::char_count - (both_have_ascii? 128: 0);
	static const cs_int32 start_index = both_have_ascii? 128: 0;

	inline charset_map() : m_may_fail(false)
	{
		for (cs_int32 i=start_index; i<ICS::cp_count; ++i)
		{
			const cs_int32 abs_idx = i - start_index;

			const utf32_t u32 = ICS::convert_to_utf32( utf32_t(i) );

			if (u32 == helper::not_defined_in_unicode)
			{
				m_map[abs_idx] = helper::not_defined_in_charset;
				continue;
			}

			m_map[abs_idx] = OCS::convert_to_charset(u32);

			if (m_may_fail || m_map[abs_idx] == helper::not_defined_in_charset) m_may_fail = true;
		}
	}

	inline bool may_fail() const { return m_may_fail; }

	inline ccp_t operator[](const ncp_t& cp) const { return at((cs_uint8)cp); }
	inline ccp_t operator[](const ccp_t& cp) const { return at(cp); }

private:
	inline ccp_t at(const ccp_t cp) const
	{
		if (both_have_ascii && cp < 128) return cp;
		return m_map[cp - start_index];
	}

private:
	csi::array<ccp_t, array_size> m_map;
	bool m_may_fail;
};

}
}

#endif // CHARSET_MAP_HPP
