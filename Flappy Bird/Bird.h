#pragma once
#include "stdafx.h"

class CBird
{
public:
	float m_Y;
	const float m_X;
	float m_vY;
	float m_rot;

	CBird();
	~CBird();

	void Render();
	void UpData(float dt);
	void getBoundingBox(hgeRect &BoundingBox);
private:
	hgeAnimation *m_animation;
	HTEXTURE m_tex;
};