#ifndef CORE_H
#define CORE_H

#ifdef JE_PLATFORM_WINDOWS
	#ifdef JE_BUILD_DLL
		#define JE_API __declspec(dllexport)
	#else
		#define JE_API __declspec(dllimport)
	#endif
#else
	#error JavaEngine only supports Windows!
#endif

#define BIT(x) (1 << x)
 
#endif