#include "Pipe.h"

CPipe::CPipe()
	: m_Hight(100), m_X(800)
{
	HTEXTURE topTex = getShareHGE()->Texture_Load("res\\images\\Pipe_Top.png");
	HTEXTURE bottomTex = getShareHGE()->Texture_Load("res\\images\\Pipe_Bottom.png");

	m_Top = new hgeSprite(topTex,0,0,52,420);
	m_Bottom = new hgeSprite(bottomTex,0,0,52,420);
	m_Top->SetHotSpot(0, 420);
	m_Bottom->SetHotSpot(0, 0);

	m_Y = getShareHGE()->Random_Int(50,488-50-m_Hight);
}

CPipe::~CPipe()
{
	delete m_Top;
	delete m_Bottom;
}

void CPipe::Render()
{
	m_Top->Render(m_X, m_Y);
	m_Bottom->Render(m_X, m_Y+m_Hight);
}

void CPipe::getBoundingBox(hgeRect &TopBox, hgeRect &BottomBox, hgeRect &GradeBox)
{
	m_Top->GetBoundingBox(m_X, m_Y, &TopBox);
	m_Bottom->GetBoundingBox(m_X, m_Y+m_Hight, &BottomBox);
	TopBox.y1 += 2;
	TopBox.y2 -= 2;
	BottomBox.y1 += 2;
	BottomBox.y2 -= 2;

	GradeBox.x1 = m_X+25;
	GradeBox.y1 = m_Y;
	GradeBox.x2 = m_X+50;
	GradeBox.y2 = m_Y+m_Hight;
}