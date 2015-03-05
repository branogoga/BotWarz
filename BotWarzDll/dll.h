#pragma once

#ifdef BOTWARZDLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif

#ifdef BOTWARZDLL_EXPORTS
#define TESTABLE _declspec(dllexport)
#else
#define TESTABLE _declspec(dllimport)
#endif