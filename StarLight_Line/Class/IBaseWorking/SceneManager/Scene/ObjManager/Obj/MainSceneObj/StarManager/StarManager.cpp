﻿#include "StarManager.h"

#include<fstream>
#include<sstream>
#include<algorithm>

#include "BaseSter/DamageStar/DamageStar.h"
#include "BaseSter/ScoreStar/ScoreStar.h"
#include "BaseSter/ClearStar/ClearStar.h"

VOID StarManager::Init()
{
	m_rGameLib.SetStartTime();

	m_Init = TRUE;

	for (BaseStar* pI : m_StarNotes)
	{
		pI->Init();
	}
}

VOID StarManager::Update()
{
	for (BaseStar* pI : m_StarNotes)
	{
		pI->Update();
	}
}

VOID StarManager::Render()
{
	m_rGameLib.SetCameraTransform();

	for (BaseStar* pI : m_StarNotes)
	{
		pI->Render();
	}

	if (m_Init)
	{
		m_Init = FALSE;

		for (int i = 0;i != m_StarNotes.size();++i)
		{
			m_rGameCollision.ResiterEnemyPoint(
				static_cast<BaseStar*>(m_StarNotes[i])->GetStarPos(),
				static_cast<BaseStar*>(m_StarNotes[i])->GetType());
		}
	}
}

VOID StarManager::LoadStarData(const char* pFileName)
{
	std::ifstream ifs(pFileName);
	std::string str;

	static int cnt;
	cnt = 0;

	while (getline(ifs, str))
	{
		replace(str.begin(), str.end(), ',', ' ');
		std::stringstream stream(str);

		int Kind;
		stream >> Kind;

		Create(static_cast<STAR_TYPE>(Kind));

		StarPlace StarInfo;
		StarInfo.m_Type = static_cast<STAR_TYPE>(Kind);

		stream >> 
			StarInfo.m_DropPerMinute >>
			StarInfo.m_Division >> 
			StarInfo.m_StarsNumInDivision >> 
			StarInfo.m_Pos.x;

		StarDataToAssign(cnt, StarInfo);

		cnt++;
	}
}

VOID StarManager::Create(const STAR_TYPE& Kind)
{
	BaseStar* pBase = nullptr;

	switch (Kind)
	{
	case DAMAGE:
		pBase = static_cast<BaseStar*>(new DamageStar());

		break;

	case SCORE:
		pBase = static_cast<BaseStar*>(new ScoreStar());

		break;

	case CLEAR:
		pBase = static_cast<BaseStar*>(new ClearStar());

		break;
	}

	m_StarNotes.push_back(pBase);
}

VOID StarManager::StarDataToAssign(const int& rArrayNum,const StarPlace& rStarPlace)
{
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->SetStarInfo(rStarPlace);
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->FallStarPosYTime();
	(static_cast<BaseStar*>(m_StarNotes[rArrayNum]))->SetType(rStarPlace.m_Type);
}

StarManager::~StarManager()
{
	for (auto i : m_StarNotes)
	{
		delete i;
	}
	m_StarNotes.clear();

	m_rGameLib.ReleaseTex();
}
