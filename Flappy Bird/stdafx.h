#pragma once
#include <hge.h>
#include <Director.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeguictrls.h>
//再次添加其他要包含的头文件

#pragma comment(lib, "hge.lib")
#pragma comment(lib, "hgehelp.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")	//忽略低版本的libc.lib库

#ifdef _DEBUG
#pragma comment(lib, "Director_d")
#else
#pragma comment(lib, "Director")
#endif

HGE *getShareHGE();