// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_OEM_HPP
#define CHARSET_OEM_HPP

#include "code_page_x.hpp"

namespace charset
{
#define DEFINE_OEM_X(ID, CC) \
	struct oem ## ID : public csi::code_page_x<oem ## ID, CC, 128> \
{ \
	static const utf32_t chars[array_size]; \
\
	inline static const char* get_name() { return "OEM-" #ID; } \
\
	inline static const char* get_description(); \
};

DEFINE_OEM_X(437, 256)
DEFINE_OEM_X(667, 256)
DEFINE_OEM_X(720, 248)
DEFINE_OEM_X(737, 256)
DEFINE_OEM_X(775, 256)
DEFINE_OEM_X(850, 256)
DEFINE_OEM_X(852, 256)
DEFINE_OEM_X(855, 256)
DEFINE_OEM_X(857, 254)
DEFINE_OEM_X(858, 256)
DEFINE_OEM_X(860, 256)
DEFINE_OEM_X(861, 256)
DEFINE_OEM_X(862, 256)
DEFINE_OEM_X(863, 256)
DEFINE_OEM_X(864, 251)
DEFINE_OEM_X(865, 256)
DEFINE_OEM_X(866, 256)
DEFINE_OEM_X(867, 256)
DEFINE_OEM_X(869, 247)
DEFINE_OEM_X(MIK, 256)
DEFINE_OEM_X(Iran, 256)

inline const char* oem437::get_description() { return "Latin US"; }
inline const char* oem667::get_description() { return "Polish"; }
inline const char* oem720::get_description() { return "Arabic"; }
inline const char* oem737::get_description() { return "Greek"; }
inline const char* oem775::get_description() { return "Baltic Rim"; }
inline const char* oem850::get_description() { return "Latin 1"; }
inline const char* oem852::get_description() { return "Latin 2"; }
inline const char* oem855::get_description() { return "Cyrillic"; }
inline const char* oem857::get_description() { return "Turkish"; }
inline const char* oem858::get_description() { return "Modified Latin 1"; }
inline const char* oem860::get_description() { return "Portuguese"; }
inline const char* oem861::get_description() { return "Icelandic"; }
inline const char* oem862::get_description() { return "Hebrew"; }
inline const char* oem863::get_description() { return "French Canada"; }
inline const char* oem864::get_description() { return "Arabic"; }
inline const char* oem865::get_description() { return "Nordic"; }
inline const char* oem866::get_description() { return "Cyrillic"; }
inline const char* oem867::get_description() { return "Czech"; }
inline const char* oem869::get_description() { return "Greek 2"; }
inline const char* oemMIK::get_description() { return "Cyrillic"; }
inline const char* oemIran::get_description() { return "Iran System"; }

#undef DEFINE_OEM_X
}

#endif // CHARSET_OEM_HPP
