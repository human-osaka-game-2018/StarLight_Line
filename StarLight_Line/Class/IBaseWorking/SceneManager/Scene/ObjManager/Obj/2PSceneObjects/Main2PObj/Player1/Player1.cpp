﻿#include "Player1.h"

VOID PlayerOne::Init()
{
	m_pOnePlayerData = new TwoPlayerResultData(_T("PlayerOne"), m_contrllerType);

	DefaultLight();

	m_rGameLib.CreateFbx(_T("Eiwi"), "3DModels/Eiwi/Eiwi.fbx");

	m_PlayerPoint.x = m_MAXXARRAYNUM / 3;
	m_PlayerPoint.y = m_MAXYARRAYNUM / 2;
	m_PlayerPoint.z = 1;
	m_PlayerPos.z = 0.2f;
	m_Speed.x = m_Speed.y = m_Speed.z = 0.0f;
	m_PlayerPos.x = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].x;
	m_PlayerPos.y = m_BasePos[m_PlayerPoint.y][m_PlayerPoint.x].y;

	m_rGameCollision.ResiterPlayerPoint(_T("PlayerOne"), &m_PlayerPos);
}

VOID PlayerOne::Update()
{
	CoordinatePoint PlayerPointBuffer = m_PlayerPoint;
	HIT_KEY HitKey;

	int* pPoX = &m_PlayerPoint.x;
	int* pPoY = &m_PlayerPoint.y;

	//キー入力によってプレイヤーの動きを決める
	//y座標の移動
	if (m_rGameLib.PushJoyconAnalogStick(m_contrllerType,Joycon::UP_TILT) &&
		*pPoY > 0)
	{
		HitKey = UP;
	}

	if (m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::DOWN_TILT) &&
		*pPoY < (m_MAXYARRAYNUM - 1))
	{
		HitKey = DOWN;
	}

	//x座標の移動
	if (m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::LEFT_TILT) &&
		*pPoX > 0)
	{
		HitKey = LEFT;
	}

	if (m_rGameLib.PushJoyconAnalogStick(m_contrllerType, Joycon::RIGHT_TILT) &&
		*pPoX < (m_MAXXARRAYNUM - 1))
	{
		HitKey = RIGHT;
	}

	DecideSpeed(&PlayerPointBuffer, HitKey);
	RestrictedMoving();

	m_pOnePlayerData->Update();
}

VOID PlayerOne::Render()
{
	D3DXMATRIX MatTrans, MatScale, MatRotate;
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&MatTrans);
	D3DXMatrixIdentity(&MatScale);

	const float MODELSCALE = 0.05f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	// 拡大
	D3DXMatrixScaling(&MatScale, MODELSCALE, MODELSCALE, MODELSCALE);
	D3DXMatrixMultiply(&m_World, &m_World, &MatScale);

	static FLOAT deg = 0;
	deg += 1.0f;
	D3DXMatrixRotationZ(&MatRotate, D3DXToRadian(deg));
	D3DXMatrixMultiply(&m_World, &m_World, &MatRotate);

	deg += 0.5f;
	D3DXMatrixRotationX(&MatRotate, D3DXToRadian(deg));
	D3DXMatrixMultiply(&m_World, &m_World, &MatRotate);

	// 移動
	D3DXMatrixTranslation(&MatTrans, m_PlayerPos.x, m_PlayerPos.y, m_PlayerPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &MatTrans);

	SetPlayerFbxMaterial();

	m_rGameLib.Render(m_rGameLib.GetFbx(_T("Eiwi")), m_World, m_rGameLib.GetTex(_T("PlayerTex")));

	m_pOnePlayerData->Render();
}

VOID PlayerOne::SetPlayerFbxMaterial()
{
	FLOAT AdditionalColor = 60.0f;

	FbxRelated& rEiwi = m_rGameLib.GetFbx(_T("Eiwi"));

	D3DXVECTOR4 EiwiAmbient(0.7f, (170.0f + AdditionalColor) / 255.0f, (170.0f + AdditionalColor) / 255.0f, (-30.0f + AdditionalColor) / 255.0f);
	rEiwi.SetAmbient(&EiwiAmbient);

	D3DXVECTOR4 EiwiEmissive(0.8f, (150.0f + AdditionalColor) / 255.0f, (130.0f + AdditionalColor) / 255.0f, (-30.0f + AdditionalColor) / 255.0f);
	rEiwi.SetEmissive(&EiwiEmissive);

	rEiwi.SetPower(0.8f);

	D3DXVECTOR4 VertexColor(255.0f, 255.0f, 255.0f, 255.0f);
	rEiwi.SetColor(&VertexColor);
}
