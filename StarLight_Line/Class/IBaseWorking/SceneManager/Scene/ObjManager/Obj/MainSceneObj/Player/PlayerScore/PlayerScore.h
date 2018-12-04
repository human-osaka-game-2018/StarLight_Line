﻿#ifndef PLAYER_SCORE_H_
#define PLAYER_SCORE_H_

#include <vector>

#include "../../../Obj.h"
#include "../../../../../../../.././../GameLib/GameLib.h"

class PlayerScore :public Obj
{
public:
	PlayerScore() :Obj(OT_UI, 1.0f)
	{
		Init();
	}

	~PlayerScore()
	{
		m_rGameLib.ReleaseTex();
		Release();
	}

	VOID Init();
	VOID Update();
	VOID Render();

	//セットしたときにスコアに足す
	VOID SetScore(const INT& Score)
	{
		m_Score += Score;
	}

private:
	//スコアの桁が繰り上がったら
	//矩形を作り、桁数を上げる処理をする関数
	VOID SearchDigitIncreasedAndCreateNewDigit();

	//数字フォントのTuTv切り取り関数
	VOID DisplayNum(TexUV* UV, const INT& Num);

	//vectorの解放関数
	VOID Release();

	INT m_Score = 0;

	std::vector<CustomVertex*> m_ScoreFont;
	std::vector<INT> m_Digit;
};

#endif // !PLAYER_SCORE_H_