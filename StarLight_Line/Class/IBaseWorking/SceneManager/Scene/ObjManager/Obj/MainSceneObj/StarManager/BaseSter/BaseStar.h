﻿#ifndef BASE_STAR_H_
#define BASE_STAR_H_

#include <Windows.h>

#include <d3dx9.h>

struct StarPlace
{
	D3DXVECTOR3	m_Pos;				//x,y,z座標
	int m_Division;					//区分け数
	float m_StarsNumInDivision;		//区分けの中の星の数
	float m_DropPerMinute;			//1分間にどれだけ落ちてくるか
	float m_Time;					//落ちTてくる時間
};

#include "../../../Obj.h"
/*
*ベーススタークラス
*/
class BaseStar :public Obj
{
public:
	BaseStar() :Obj(OT_TRANSPARENCY, 0.5f) {};

	virtual ~BaseStar() {};

	virtual VOID Init();
	virtual VOID Update();
	virtual VOID Render();

	VOID SetStarInfo(const StarPlace& StarInfo);
	VOID FallStarPosYTime();									//落ちてくる時間設定関数

protected:
	VOID InitBaseStar();										//敵に必要な情報の初期化関数
	VOID PosOfStarYCoordinate(const LONGLONG& CurrentTime);		//y座標を移動させる関数
	VOID DefaultLight();										//ライトのデフォルト値設定関数
	VOID ConvertLocalToWorld(D3DXMATRIX* matWorld);				//ローカル座標からワールド座標への変換

	StarPlace m_Info;				//スターの基本情報

	const float ColorMax = 0xFF;
};

#endif // !BASE_STAR_H_