#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

#include <fstream>
#include <sstream>

#include <cmath>
#include <memory>

#if defined( _WIN32 ) || defined( _WIN64 )
#	define TAG_DLL_EXPORT __declspec( dllexport )
#	define TAG_DLL_IMPORT __declspec( dllimport )
#else
#	define TAG_DLL_EXPORT
#	define TAG_DLL_IMPORT
#endif 

#ifdef ZENO_EXPORTS
#	define ZENO_DLL TAG_DLL_EXPORT
#else
#	define ZENO_DLL TAG_DLL_IMPORT
#endif

#if defined( _MSC_VER ) && ( _MSC_VER >= 1400 )
#    pragma warning( disable: 4996)
#    define _CRT_SECURE_NO_DEPRECATE  1
#    define _CRT_NONSTDC_NO_DEPRECATE 1
#endif

#if _MSC_VER >= 1200
#	pragma warning(disable : 4006)
#	pragma warning(disable : 4786)
#	pragma warning(disable : 4251)
#	pragma warning(disable : 4100)
#endif

#define VK_KEY0 0x30
#define VK_KEY1 0x31
#define VK_KEY2 0x32
#define VK_KEY3 0x33
#define VK_KEY4 0x34
#define VK_KEY5 0x35
#define VK_KEY6 0x36
#define VK_KEY7 0x37
#define VK_KEY8 0x38
#define VK_KEY9 0x39
#define VK_KEYA 0x41
#define VK_KEYB 0x42
#define VK_KEYC 0x43
#define VK_KEYD 0x44
#define VK_KEYE 0x45
#define VK_KEYF 0x46
#define VK_KEYG 0x47
#define VK_KEYH 0x48
#define VK_KEYI 0x49
#define VK_KEYJ 0x4A
#define VK_KEYK 0x4B
#define VK_KEYL 0x4C
#define VK_KEYM 0x4D
#define VK_KEYN 0x4E
#define VK_KEYO 0x4F
#define VK_KEYP 0x50
#define VK_KEYQ 0x51
#define VK_KEYR 0x52
#define VK_KEYS 0x53
#define VK_KEYT 0x54
#define VK_KEYU 0x55
#define VK_KEYV 0x56
#define VK_KEYW 0x57
#define VK_KEYX 0x58
#define VK_KEYY 0x59
#define VK_KEYZ 0x5A

#define KEY_DOWN( Key ) ( GetAsyncKeyState( Key ) & 0x8000 )
#define KEY_UP( Key ) ( !KEY_DOWN( Key ) )
