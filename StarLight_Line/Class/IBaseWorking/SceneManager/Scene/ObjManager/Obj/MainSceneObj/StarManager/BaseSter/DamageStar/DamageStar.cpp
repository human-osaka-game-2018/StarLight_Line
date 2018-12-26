﻿#include"DamageStar.h"

VOID DamageStar::Render()
{
	DefaultLight();

	if (m_Info.m_CollisionPos.y < -m_STAR_HALF_SCALE || m_Info.m_CollisionPos.y > m_WND_SIZE.m_y + m_STAR_HALF_SCALE) return;

	ConvertLocalToWorld(&m_MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 DamageColor(ColorMax / ColorMax, ColorMax / ColorMax, ColorMax / ColorMax, ColorMax / ColorMax);
	rEnemyStar.SetEmissive(&DamageColor);

	m_rGameLib.Render(rEnemyStar, m_MatWorld);
}

DamageStar::~DamageStar()
{
}
