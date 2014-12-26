#include "stdafx.h"
#include "Director.h"

#define BTN_RESTART 0
#define BTN_GRADE 1

//======================================================
//CMyDirector
//�����࣬������Ϸ�����е�Ԫ��
//======================================================
CMyDirector::CMyDirector(HGE *hge)
	: CDirector(hge, 800, 600, "flappy bird"), m_posGround(0), m_moveVel(100), m_timer(0), m_skyBox(0,-50,800,0), m_grade(0), m_hadGraded(false),
	m_guiEnterTime(0)
{
	m_IsShowSplash = false;
	m_IsUseSound = true;
	hge->System_SetState(HGE_HIDEMOUSE,false);
}
CMyDirector::~CMyDirector()
{
	delete m_bird;
	delete m_background;
	delete m_ground;
	delete m_GetReady;
	delete m_click;
	delete m_font_Big;
	//delete m_btnReStart;
	//delete m_btnGrade;
	for (auto pipe : m_PipeGroup)
	{
		delete pipe;
	}
}

void CMyDirector::Init()
{
	HTEXTURE bg = m_hge->Texture_Load("res\\images\\Background.png");
	HTEXTURE ground = m_hge->Texture_Load("res\\images\\Ground.png");
	HTEXTURE hint = m_hge->Texture_Load("res\\images\\Hint.png");
	HTEXTURE button = m_hge->Texture_Load("res\\images\\buttons.png");

	m_bird = new CBird();
	m_background = new hgeSprite(bg,0,0,800,600);
	m_ground = new hgeSprite(ground,m_posGround,0,800,112);

	m_GetReady = new hgeSprite(hint, 0,0,290,83);
	m_click = new hgeSprite(hint, 0,172,239,150);

	m_flySound = m_hge->Effect_Load("res\\Sounds\\Wing.mp3");
	m_menuSound = m_hge->Effect_Load("res\\sounds\\Swooshing.mp3");
	m_hitSound = m_hge->Effect_Load("res\\sounds\\Hit.mp3");
	m_dieSound = m_hge->Effect_Load("res\\sounds\\Die.mp3");
	m_pointSound = m_hge->Effect_Load("res\\sounds\\point.mp3");

	m_font_Big = new hgeFont("res\\images\\Font_big.fnt");
	
	m_gui.AddCtrl(new hgeGUIButton(BTN_RESTART,220,600,178,99,button,0,0));
	m_gui.AddCtrl(new hgeGUIButton(BTN_GRADE,420,600,178,99,button,0,99));

	m_Scene = START;
}

bool CMyDirector::FrameFunc()
{
	float dt = getShareHGE()->Timer_GetDelta();
	switch (m_Scene)
	{
	case CMyDirector::START:
		StartFrame(dt);
		break;
	case CMyDirector::RUN:
		RunFrame(dt);
		break;
	case CMyDirector::OVER:
		OverFrame(dt);
		break;
	default:
		break;
	}
	return false;
}
bool CMyDirector::RenderFunc()
{
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0xFF000000);
	m_background->Render(0,0);
	switch (m_Scene)
	{
	case CMyDirector::START:
		StartRender();
		break;
	case CMyDirector::RUN:
		RunRender();
		break;
	case CMyDirector::OVER:
		OverRender();
		break;
	default:
		break;
	}
	m_hge->Gfx_EndScene();
	return false;
}

void CMyDirector::StartRender()
{
	m_bird->Render();
	m_GetReady->Render(250,50);
	m_click->Render(280,200);
	m_ground->Render(0,488);
}

void CMyDirector::StartFrame(float dt)		//��Ϸ��ʼʱ��֡����
{
	m_posGround += dt*m_moveVel;
	m_ground->SetTextureRect(m_posGround,0,800,112);

	m_bird->UpData(dt);
	if (m_hge->Input_KeyDown(HGEK_LBUTTON) || m_hge->Input_KeyDown(HGEK_SPACE))
	{
		m_Scene = RUN;
		m_bird->m_vY = -350;
		m_hge->Effect_Play(m_flySound);
	}
}

void CMyDirector::RunRender()				//��Ϸ����ʱ����Ⱦ����
{
	for (auto pipe : m_PipeGroup)
	{
		pipe->Render();
	}
	m_bird->Render();
	m_font_Big->printf(380,70,HGETEXT_LEFT,"%d",m_grade);
	m_ground->Render(0,488);
}

void CMyDirector::RunFrame(float dt)		//��Ϸ����ʱ��֡����
{
	hgeRect bird;
	m_bird->getBoundingBox(bird);
	/*�����ƶ�*/
	m_posGround += dt*m_moveVel;
	m_ground->SetTextureRect(m_posGround,0,800,112);

	/*��*/
	m_bird->m_vY = m_bird->m_vY + 1200*dt;
	m_bird->m_Y += m_bird->m_vY*dt;
	if (!bird.Intersect(&m_skyBox))			//��û��������������
	{
		if (m_hge->Input_KeyDown(HGEK_LBUTTON) || m_hge->Input_KeyDown(HGEK_SPACE))
		{
			m_bird->m_vY = -350;
			m_hge->Effect_Play(m_flySound);
		}
	}
	m_bird->UpData(dt);

	/*��ʱ�����µĹ���*/
	m_timer += dt;
	if (m_timer > 2)
	{
		m_PipeGroup.push_back(new CPipe());
		m_timer = 0;
	}
	/*�ƶ�����*/
	for (unsigned i = 0; i < m_PipeGroup.size(); i++)
	{
		m_PipeGroup[i]->m_X -= dt*m_moveVel;
	}
	/*���ٳ���Ĺ���*/
	if (!m_PipeGroup.empty())
	{
		if (m_PipeGroup[0]->m_X <= -52)
		{
			delete m_PipeGroup[0];
			m_PipeGroup.erase(m_PipeGroup.begin());
		}
	}

	/*��ײ���*/
	hgeRect topPipe, bottomPipe, grade, groundBox;
	for (auto pipe : m_PipeGroup)
	{
		pipe->getBoundingBox(topPipe, bottomPipe, grade);
		if (bird.Intersect(&topPipe) || bird.Intersect(&bottomPipe))
		{
			m_hge->Effect_Play(m_menuSound);
			m_Scene = OVER;
			m_hge->Effect_Play(m_hitSound);
			m_hge->Effect_Play(m_dieSound);
		}
		if (bird.Intersect(&grade))				//����������˼Ʒ���
		{
			if (!m_hadGraded)					//��֮ǰû�н����(��һ�ν���)
			{
				m_grade ++;
				m_hge->Effect_Play(m_pointSound);
				m_hadGraded = true;				//���Ϊ�������
			}
			goto GOTO_OUT;						//ֻҪ����һ���Ʒ����������񣬾�Ҫ����
		}
	}
	m_hadGraded = false;						//�ߵ���һ��˵�����еļƷ����ﶼû������ô���ñ�Ǳ���
	GOTO_OUT:
	m_ground->GetBoundingBox(0,488,&groundBox);
	if (bird.Intersect(&groundBox))
	{
		m_hge->Effect_Play(m_menuSound);
		m_Scene = OVER;
		m_hge->Effect_Play(m_hitSound);
		m_hge->Effect_Play(m_dieSound);
	}
}

void CMyDirector::OverRender()				//��Ϸ����ʱ����Ⱦ����
{
	for (auto pipe : m_PipeGroup)
	{
		pipe->Render();
	}
	m_bird->Render();
	m_ground->Render(0,488);
	m_gui.Render();
}

void CMyDirector::OverFrame(float dt)		//��Ϸ����ʱ��֡����
{
	hgeRect bird, groundBox;
	m_bird->getBoundingBox(bird);
	m_ground->GetBoundingBox(0,488,&groundBox);
	m_gui.Update(dt);

	if (m_gui.GetCtrl(BTN_RESTART)->rect.y1 >= 300)
	{
		m_gui.Move(0,-0.8);
	}

	if (!bird.Intersect(&groundBox))
	{
		m_bird->m_vY = m_bird->m_vY + 1200*dt;
		m_bird->m_Y += m_bird->m_vY*dt;
		m_bird->UpData(dt);
	}
	if (static_cast<hgeGUIButton*>(m_gui.GetCtrl(BTN_RESTART))->GetState())
	{
		delete m_bird;
		for (auto pipe : m_PipeGroup)
		{
			delete pipe;
		}
		m_PipeGroup.clear();
		m_bird = new CBird();
		m_gui.Move(0,300);
		
		m_Scene = START;
		m_grade = 0;

		static_cast<hgeGUIButton*>(m_gui.GetCtrl(BTN_RESTART))->SetState(false);
	}
}