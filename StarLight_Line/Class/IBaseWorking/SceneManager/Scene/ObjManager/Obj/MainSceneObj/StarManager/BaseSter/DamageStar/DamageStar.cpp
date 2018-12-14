﻿#include"DamageStar.h"

VOID DamageStar::Update()
{
	m_rGameLib.SetEndTime();
	PosOfStarYCoordinate(m_rGameLib.GetMilliSecond());
}

VOID DamageStar::Render()
{
	DefaultLight();

	ConvertLocalToWorld(&m_MatWorld);

	FbxRelated& rEnemyStar = m_rGameLib.GetFbx(_T("StarFBX"));

	//色の設定
	D3DXVECTOR4 DamageColor(ColorMax, ColorMax, ColorMax, ColorMax);
	rEnemyStar.SetEmissive(&DamageColor);

	m_rGameLib.Render(rEnemyStar, m_MatWorld);
}

VOID DamageStar::Init()
{

}

DamageStar::~DamageStar()
{
}