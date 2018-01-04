#pragma once

#include <Types/Generic.h>
#include <Template/Enum.h>
#include <Template/PlatformDefines.h>

namespace oi {

	#ifdef __WINDOWS__
	UEnum(Key,
		"KEY_UNDEFINED", 0,
		"0", '0',
		"1", '1',
		"2", '2',
		"3", '3',
		"4", '4',
		"5", '5',
		"6", '6',
		"7", '7',
		"8", '8',
		"9", '9',
		"A", 'A',
		"B", 'B',
		"C", 'C',
		"D", 'D',
		"E", 'E',
		"F", 'F',
		"G", 'G',
		"H", 'H',
		"I", 'I',
		"J", 'J',
		"K", 'K',
		"L", 'L',
		"M", 'M',
		"N", 'N',
		"O", 'O',
		"P", 'P',
		"Q", 'Q',
		"R", 'R',
		"S", 'S',
		"T", 'T',
		"U", 'U',
		"V", 'V',
		"W", 'W',
		"X", 'X',
		"Y", 'Y',
		"Z", 'Z',
		"-", VK_OEM_MINUS,
		"=", VK_OEM_NEC_EQUAL,
		"[", VK_OEM_4,
		"]", VK_OEM_6,
		";", VK_OEM_1,
		"'", VK_OEM_7,
		"~", VK_OEM_3,
		"\\", VK_OEM_5,
		",", VK_OEM_COMMA,
		".", VK_OEM_PERIOD,
		"/", VK_OEM_2,
		" ", VK_SPACE,
		"0n", VK_NUMPAD0,
		"1n", VK_NUMPAD1,
		"2n", VK_NUMPAD2,
		"3n", VK_NUMPAD3,
		"4n", VK_NUMPAD4,
		"5n", VK_NUMPAD5,
		"6n", VK_NUMPAD6,
		"7n", VK_NUMPAD7,
		"8n", VK_NUMPAD8,
		"9n", VK_NUMPAD9,
		"-n", VK_SUBTRACT,
		"+n", VK_ADD,
		".n", VK_DECIMAL,
		"*n", VK_MULTIPLY,
		"/n", VK_DIVIDE,
		"F1", VK_F1,
		"F2", VK_F2,
		"F3", VK_F3,
		"F4", VK_F4,
		"F5", VK_F5,
		"F6", VK_F6,
		"F7", VK_F7,
		"F8", VK_F8,
		"F9", VK_F9,
		"F10", VK_F10,
		"F11", VK_F11,
		"F12", VK_F12,
		"F13", VK_F13,
		"F14", VK_F14,
		"F15", VK_F15,
		"F16", VK_F16,
		"F17", VK_F17,
		"F18", VK_F18,
		"F19", VK_F19,
		"F20", VK_F20,
		"F21", VK_F21,
		"F22", VK_F22,
		"F23", VK_F23,
		"F24", VK_F24,
		"UP", VK_UP,
		"DOWN", VK_DOWN,
		"LEFT", VK_LEFT,
		"RIGHT", VK_RIGHT,
		"PAGEUP", VK_NEXT,
		"PAGEDOWN", VK_PRIOR,
		"HOME", VK_HOME,
		"END", VK_END,
		"INSERT", VK_INSERT,
		"DELETE", VK_DELETE,
		"SCRLLCK", VK_SCROLL,
		"NUMLCK", VK_NUMLOCK,
		"CAPS",	VK_CAPITAL,
		"RALT", VK_RMENU,
		"RSHIFT", VK_RSHIFT,
		"RCTRL", VK_RCONTROL,
		"LALT", VK_LMENU,
		"LSHIFT", VK_LSHIFT,
		"LCTRL", VK_LCONTROL,
		"TAB", VK_TAB,
		"ENTER", VK_RETURN,
		"BACKSPACE", VK_BACK,
		"ESC", VK_ESCAPE
	);
	#endif
}