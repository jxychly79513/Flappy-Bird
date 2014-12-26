#include "stdafx.h"
#include "Director.h"

CDirector *g_Dirctor;
HGE *hge;

//���ƺ���
bool RenderFunc()
{
	return g_Dirctor->RenderFunc();
}

//֡����
bool FrameFunc()
{
	return g_Dirctor->FrameFunc();
}

HGE *getShareHGE()
{
	return hge;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);

	CMyDirector director(hge);
	g_Dirctor = &director;
	director.Start();

	return 0;
}