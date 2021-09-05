#pragma once
#include "CompileHashText.h"

#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define MAX(a,b)  ((a) > (b) ? (a) : (b))
#define ABS(_a) ((_a) > 0 ? (_a) : -(_a))

#define SAFE_DELETE(a) delete (a); a=NULL;

#define RANGE(VAR, MIN, MAX) ((VAR) < (MIN)) ? (MIN) : ((VAR) > (MAX)) ? (MAX) : (VAR)

#define TINYXML_CHECKQUERY(value) if (value != 0) assert(false && #value);

#ifdef PI
#undef PI
#endif
#define PI 3.14159265359f


#ifdef NDEBUG
	#define LIT_STRING unsigned int
	#define HASH_STRING(_x) (MM<sizeof(_x)-1>::crc32(_x))
	#define STRING unsigned int
#else 
	#define HASH_STRING(_x) _x
	#define LIT_STRING const char*
	#define STRING std::string
#endif

#ifdef DLLEXPORT  
#define DllAPI __declspec(dllexport)
#define DllExtern
#else  
#define DllAPI __declspec(dllimport)   
#define DllExtern extern
#endif 
