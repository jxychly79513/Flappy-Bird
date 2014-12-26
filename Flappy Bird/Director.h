#pragma once
#include <vector>
#include "stdafx.h"
#include "Bird.h"
#include "Pipe.h"
using namespace std;

class CMyDirector : public CDirector
{
public:
	enum sceneStatus
	{
		START = 0,
		RUN = 1,
		OVER = 2
	};
public:
	CMyDirector(HGE *hge);
	~CMyDirector();

	virtual void Init();
	virtual bool RenderFunc();		//äÖÈ¾º¯Êý
	virtual bool FrameFunc();		//Ö¡º¯Êý

	void StartRender();
	void StartFrame(float dt);
	void RunRender();
	void RunFrame(float dt);
	void OverRender();
	void OverFrame(float dt);
private:
	sceneStatus m_Scene;
	bool m_hadGraded;
	const float m_moveVel;
	float m_guiEnterTime;

	CBird *m_bird;
	hgeSprite *m_background;
	hgeSprite *m_ground;
		float m_posGround;
	vector<CPipe*> m_PipeGroup;
		float m_timer;
	hgeRect m_skyBox;

	hgeSprite *m_GetReady;
	hgeSprite *m_click;

	HEFFECT m_flySound;
	HEFFECT m_menuSound;
	HEFFECT m_hitSound;
	HEFFECT m_dieSound;
	HEFFECT m_pointSound;

	hgeFont *m_font_Big;

	hgeGUI m_gui;

	int m_grade;
};