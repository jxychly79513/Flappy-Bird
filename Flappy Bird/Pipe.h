#pragma once
#include "stdafx.h"

class CPipe
{
public:
	float m_X;

	CPipe();
	~CPipe();

	void Render();
	void getBoundingBox(hgeRect &TopBox, hgeRect &BottomBox, hgeRect &GradeBox);
private:
	float m_Y;
	const float m_Hight;

	hgeSprite *m_Top;
	hgeSprite *m_Bottom;

	hgeRect m_TopBox;
	hgeRect m_BottomBox;
	hgeRect m_GradeBox;
};