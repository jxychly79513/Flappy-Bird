#include "Bird.h"
#include <math.h>

CBird::CBird()
	: m_Y(250), m_vY(0), m_rot(0), m_X(250)
{
	m_tex = getShareHGE()->Texture_Load("res\\Images\\Birds.png");
	m_animation = new hgeAnimation(m_tex,3,10,0,0,40,40);
	m_animation->SetHotSpot(20,20);
	m_animation->Play();
}
CBird::~CBird()
{
	delete m_animation;
}

void CBird::Render()
{
	//hgeSprite _tq(getShareHGE()->Texture_Load(""),0,0,50,50);
	//hgeRect _tr;
	//m_animation->GetBoundingBoxEx(m_X, m_Y, m_rot/1.8, 0.7, 0.5, &_tr);
	//_tq.RenderStretch(_tr.x1, _tr.y1, _tr.x2, _tr.y2);
	m_animation->RenderEx(m_X, m_Y, m_rot);
}

void CBird::UpData(float dt)
{
	m_animation->Update(dt);
	m_rot = atan2f(m_vY, 700);
}

void CBird::getBoundingBox(hgeRect &BoundingBox)
{
	m_animation->GetBoundingBoxEx(m_X, m_Y, m_rot/1.8, 0.7, 0.5, &BoundingBox);
}