#pragma once
#include <hge.h>
#include <Director.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeguictrls.h>
//�ٴ��������Ҫ������ͷ�ļ�

#pragma comment(lib, "hge.lib")
#pragma comment(lib, "hgehelp.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")	//���ԵͰ汾��libc.lib��

#ifdef _DEBUG
#pragma comment(lib, "Director_d")
#else
#pragma comment(lib, "Director")
#endif

HGE *getShareHGE();