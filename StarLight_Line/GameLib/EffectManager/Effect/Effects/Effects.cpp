﻿#include "Effects.h"

#include "../Effect.h"
#include "../../../../Class/IBaseWorking/SceneManager/Scene/ObjManager/Obj/Obj.h"
#include "../../../DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"

VOID GetScoreStarEffect::Update()
{
	InitActivatedParticle();

	for (INT i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->LifeFrame() > 50)
		{
			m_ends = TRUE;

			return;
		}

		m_particles[i]->FeedIn(0, 10);
		m_particles[i]->FeedOut(20, 25);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Update();
	}
}

VOID GetClearStarEffect::Update()
{
	InitActivatedParticle();

	for (INT i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->LifeFrame() > 50)
		{
			m_ends = TRUE;

			return;
		}

		m_particles[i]->FeedIn(0, 10);
		m_particles[i]->FeedOut(20, 25);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Circulate(5.0f);
		m_particles[i]->Update();
	}
}

VOID GetDamageStarEffect::Update()
{
	InitActivatedParticle();

	for (INT i = 0; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->LifeFrame() > 30)
		{
			m_ends = TRUE;

			return;
		}

		m_particles[i]->FeedIn(0, 10);
		m_particles[i]->FeedOut(10, 20);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Update();
	}
}

VOID MouseCursorEffect::Update()
{
	m_rGameLib.CreateTex(_T("2DTextures/EffectTexture/Star.png"), _T("2DTextures/EffectTexture/Star.png"));

	InitActivatedParticle();

	POINT cursorPos;
	m_rGameLib.CursorPos(&cursorPos);
	D3DXVECTOR3 center = { static_cast<FLOAT>(cursorPos.x), static_cast<FLOAT>(cursorPos.y), 0.0f };
	D3DXVECTOR2 gravity = { 0.0f, 0.1f };

	InitCursor(m_particles[0]);
	m_particles[0]->RotateZ(5.0f);
	m_particles[0]->Update();

	for (INT i = 1; i < m_particles.size(); ++i)
	{
		if (i > m_activeLimit) continue;

		if (m_particles[i]->LifeFrame() > 60) Init(m_particles[i]);

		m_particles[i]->FeedIn(0, 10);
		m_particles[i]->FeedOut(30, 25);
		m_particles[i]->RotateZ(3.0f);
		m_particles[i]->Accelarate(gravity);
		m_particles[i]->Update();
	}
}
