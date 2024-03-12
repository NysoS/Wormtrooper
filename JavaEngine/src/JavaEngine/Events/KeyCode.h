#pragma once

#include <cstdint>

namespace JavaEngine
{
	using KeyCode = uint16_t;

	enum class Key
	{
		Unknown = -1, //!< Unhandled key
		A = 0,        //!< The A key
		B,            //!< The B key
		C,            //!< The C key
		D,            //!< The D key
		E,            //!< The E key
		F,            //!< The F key
		G,            //!< The G key
		H,            //!< The H key
		I,            //!< The I key
		J,            //!< The J key
		K,            //!< The K key
		L,            //!< The L key
		M,            //!< The M key
		N,            //!< The N key
		O,            //!< The O key
		P,            //!< The P key
		Q,            //!< The Q key
		R,            //!< The R key
		S,            //!< The S key
		T,            //!< The T key
		U,            //!< The U key
		V,            //!< The V key
		W,            //!< The W key
		X,            //!< The X key
		Y,            //!< The Y key
		Z,            //!< The Z key
		Num0,         //!< The 0 key
		Num1,         //!< The 1 key
		Num2,         //!< The 2 key
		Num3,         //!< The 3 key
		Num4,         //!< The 4 key
		Num5,         //!< The 5 key
		Num6,         //!< The 6 key
		Num7,         //!< The 7 key
		Num8,         //!< The 8 key
		Num9,         //!< The 9 key
		Escape,       //!< The Escape key
		LControl,     //!< The left Control key
		LShift,       //!< The left Shift key
		LAlt,         //!< The left Alt key
		LSystem,      //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
		RControl,     //!< The right Control key
		RShift,       //!< The right Shift key
		RAlt,         //!< The right Alt key
		RSystem,      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
		Menu,         //!< The Menu key
		LBracket,     //!< The [ key
		RBracket,     //!< The ] key
		Semicolon,    //!< The ; key
		Comma,        //!< The , key
		Period,       //!< The . key
		Apostrophe,   //!< The ' key
		Slash,        //!< The / key
		Backslash,    //!< The \ key
		Grave,        //!< The ` key
		Equal,        //!< The = key
		Hyphen,       //!< The - key (hyphen)
		Space,        //!< The Space key
		Enter,        //!< The Enter/Return keys
		Backspace,    //!< The Backspace key
		Tab,          //!< The Tabulation key
		PageUp,       //!< The Page up key
		PageDown,     //!< The Page down key
		End,          //!< The End key
		Home,         //!< The Home key
		Insert,       //!< The Insert key
		Delete,       //!< The Delete key
		Add,          //!< The + key
		Subtract,     //!< The - key (minus, usually from numpad)
		Multiply,     //!< The * key
		Divide,       //!< The / key
		Left,         //!< Left arrow
		Right,        //!< Right arrow
		Up,           //!< Up arrow
		Down,         //!< Down arrow
		Numpad0,      //!< The numpad 0 key
		Numpad1,      //!< The numpad 1 key
		Numpad2,      //!< The numpad 2 key
		Numpad3,      //!< The numpad 3 key
		Numpad4,      //!< The numpad 4 key
		Numpad5,      //!< The numpad 5 key
		Numpad6,      //!< The numpad 6 key
		Numpad7,      //!< The numpad 7 key
		Numpad8,      //!< The numpad 8 key
		Numpad9,      //!< The numpad 9 key
		F1,           //!< The F1 key
		F2,           //!< The F2 key
		F3,           //!< The F3 key
		F4,           //!< The F4 key
		F5,           //!< The F5 key
		F6,           //!< The F6 key
		F7,           //!< The F7 key
		F8,           //!< The F8 key
		F9,           //!< The F9 key
		F10,          //!< The F10 key
		F11,          //!< The F11 key
		F12,          //!< The F12 key
		F13,          //!< The F13 key
		F14,          //!< The F14 key
		F15,          //!< The F15 key
		Pause,        //!< The Pause key
		//Space = 32,
		//Apostrophe = 39, /* ' */
		//Comma = 44, /* , */
		//Minus = 45, /* - */
		//Period = 46, /* . */
		//Slash = 47, /* / */

		//PAD0 = 48, /* 0 */
		//PAD1 = 49, /* 1 */
		//PAD2 = 50, /* 2 */
		//PAD3 = 51, /* 3 */
		//PAD4 = 52, /* 4 */
		//PAD5 = 53, /* 5 */
		//PAD6 = 54, /* 6 */
		//PAD7 = 55, /* 7 */
		//PAD8 = 56, /* 8 */
		//PAD9 = 57, /* 9 */

		//Semicolon = 59, /* ; */
		//Equal = 61, /* = */

		//A = 65,
		//B = 66,
		//C = 67,
		//D = 68,
		//E = 69,
		//F = 70,
		//G = 71,
		//H = 72,
		//I = 73,
		//J = 74,
		//K = 75,
		//L = 76,
		//M = 77,
		//N = 78,
		//O = 79,
		//P = 80,
		//Q = 81,
		//R = 82,
		//S = 83,
		//T = 84,
		//U = 85,
		//V = 86,
		//W = 87,
		//X = 88,
		//Y = 89,
		//Z = 90,

		//LeftBracket = 91,  /* [ */
		//Backslash = 92,  /* \ */
		//RightBracket = 93,  /* ] */
		//GraveAccent = 96,  /* ` */

		//World1 = 161, /* non-US #1 */
		//World2 = 162, /* non-US #2 */

		///* Function keys */
		//Escape = 256,
		//Enter = 257,
		//Tab = 258,
		//Backspace = 259,
		//Insert = 260,
		//Delete = 261,
		//Right = 262,
		//Left = 263,
		//Down = 264,
		//Up = 265,
		//PageUp = 266,
		//PageDown = 267,
		//Home = 268,
		//End = 269,
		//CapsLock = 280,
		//ScrollLock = 281,
		//NumLock = 282,
		//PrintScreen = 283,
		//Pause = 284,
		//F1 = 290,
		//F2 = 291,
		//F3 = 292,
		//F4 = 293,
		//F5 = 294,
		//F6 = 295,
		//F7 = 296,
		//F8 = 297,
		//F9 = 298,
		//F10 = 299,
		//F11 = 300,
		//F12 = 301,
		//F13 = 302,
		//F14 = 303,
		//F15 = 304,
		//F16 = 305,
		//F17 = 306,
		//F18 = 307,
		//F19 = 308,
		//F20 = 309,
		//F21 = 310,
		//F22 = 311,
		//F23 = 312,
		//F24 = 313,
		//F25 = 314,

		///* Keypad */
		//KP0 = 320,
		//KP1 = 321,
		//KP2 = 322,
		//KP3 = 323,
		//KP4 = 324,
		//KP5 = 325,
		//KP6 = 326,
		//KP7 = 327,
		//KP8 = 328,
		//KP9 = 329,
		//KPDecimal = 330,
		//KPDivide = 331,
		//KPMultiply = 332,
		//KPSubtract = 333,
		//KPAdd = 334,
		//KPEnter = 335,
		//KPEqual = 336,

		//LeftShift = 340,
		//LeftControl = 341,
		//LeftAlt = 342,
		//LeftSuper = 343,
		//RightShift = 344,
		//RightControl = 345,
		//RightAlt = 346,
		//RightSuper = 347,
		//Menu = 348
	};


}
