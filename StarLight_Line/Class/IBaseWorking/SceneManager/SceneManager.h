﻿#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <windows.h>

#include <vector>

#include "../../Singleton/Singleton.h"
#include "../IBaseWorking.h"
#include "Scene/Scene.h"
#include "Scene/Enum/SCENE_KIND.h"
#include "Scene/TitleScene/TitleScene.h"

#include "../../../GameLib/GameLib.h"
#include "../../../GameLib/DX/DX3D/CustomVertexEditor/Data/ObjData.h"
#include "../../../GameLib/DX/DX3D/CustomVertexEditor/Data/CustomVertex.h"
#include "Data/StageData.h"
#include "Data/ResultData.h"

class SceneManager :public IBaseWorking, public Singleton<SceneManager>
{
public:
	friend class Singleton<SceneManager>;

	~SceneManager()
	{
		TurnOffBGM();

		Sleep(1000);	//ながれているBGMを止めるのには少しかかり
						//再生中にプログラムを終了するとメモリリークが起こる

		delete m_pScene;
	}

	inline VOID Update()
	{
		if (m_isRequestedChangeResent) return;

		if (m_pSubScene != nullptr)
		{
			m_pSubScene->Update();

			return;
		}

		m_pScene->Update();
	}

	inline VOID Render()
	{
		if (m_pSubScene != nullptr)
		{
			m_pSubScene->Render();
			StageTransition();

			return;
		}

		m_pScene->Render();

		StageTransition();
	}

	inline VOID SetCurrentScene(SCENE_KIND currentScene)
	{
		m_currentScene = currentScene;
	}

	inline VOID SetNextScene(SCENE_KIND nextScene)
	{
		m_nextScene = nextScene;

		m_isRequestedChangeResent = TRUE;
	}

	VOID Factory();

	inline BOOL LatterTransitionStagingIsEnded()
	{
		if(!m_transitionStagingAlpha || m_isRequestedChangeResent) return TRUE;

		return FALSE;
	}

	inline VOID SetStageData(StageData stageData)
	{
		m_stageData = stageData;
	}

	inline VOID SetResultData(ResultData resultData)
	{
		m_resultData = resultData;
	}

	inline VOID GetStageData(StageData* pStageData) const
	{
		*pStageData = m_stageData;
	}

	inline VOID GetResultData(ResultData* pResultData) const
	{
		*pResultData = m_resultData;
	}

	inline VOID Set2PModeScore(const INT& Player,const INT& Score)
	{
		m_2PModeScore[Player] = Score;
	}

	inline INT Get2PModeScore(const INT& Player)
	{
		return m_2PModeScore[Player];
	}

	inline VOID Set2PlayMode(const BOOL& Mode)
	{
		m_is2PMode = Mode;
	}

	inline BOOL Get2PlayMode() const
	{
		return m_is2PMode;
	}

	inline VOID SetTransitionMode(const BOOL& Mode)
	{
		m_SceneTransitionMode = Mode;
	}

	inline VOID SetCanTransferSubScene(BOOL CanTransferSubScene)
	{
		m_CanTransferSubScene = CanTransferSubScene;
	}

	inline VOID TurnOffBGM()
	{
		GameLib& rGameLib = GameLib::GetInstance();

		rGameLib.StopSound(m_pBGM_KEY[m_currentScene]);
	}

	inline VOID TurnOnBGM()
	{
		GameLib& rGameLib = GameLib::GetInstance();

		rGameLib.LoopStartSound(m_pBGM_KEY[m_nextScene]);
	}

	inline VOID SetIsTutorial(BOOL isTutorial)
	{
		m_isTutorial = isTutorial;
	}

	inline BOOL GetIsTutorial() const
	{
		return m_isTutorial;
	}

private:
	SceneManager() 
	{
		InitBGM();
		TurnOnBGM();

		m_pScene = new TitleScene();
	}

	VOID StageTransition();

	VOID InitBGM();

	Scene* m_pScene = nullptr;
	Scene* m_pSubScene = nullptr;

	SCENE_KIND m_currentScene	= SK_TITLE;
	SCENE_KIND m_nextScene		= SK_TITLE;

	const TCHAR* m_pBGM_KEY[SK_MAX] =
	{
		_T("TITLE_BGM")			,
		_T("TUTORIAL_BGM")		,
		_T("STAGESELECT_BGM")	,
		_T("2P_STAGESELECT_BGM"),
		_T("GAME_BGM")			,
		_T("2P_GAME_BGM")		,
		_T("SAVE_DATA_BGM")		,
		_T("PAUSE_BGM")			,
		_T("RESULT_BGM")		,
		_T("2P_RESULT_BGM")		,
		_T("END_BGM")			,
	};

	BOOL m_isRequestedChangeResent = FALSE;
	BOOL m_CanTransferSubScene = FALSE;
	BOOL m_SceneTransitionMode = TRUE;

	INT m_transitionStagingAlpha = 0;

	INT m_2PModeScore[Joycon::MAX_CONTROLLER];

	StageData m_stageData;
	ResultData m_resultData;

	BOOL m_isTutorial = FALSE;
	BOOL m_is2PMode = FALSE;
};

#endif // !SCENE_MANAGER_H
