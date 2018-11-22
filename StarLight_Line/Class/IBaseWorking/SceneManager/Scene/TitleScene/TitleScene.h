﻿#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <windows.h>

#include "../Scene.h"
#include "../ObjManager/Obj/Obj.h"
#include "../ObjManager/Obj/TitleSceneObj/TitleSceneObj.h"
class TitleBack;
class TitleLogo;
class TitleInputPrompt;
class TitleCometEffect;
class TitleSmallStarEffect;

class TitleScene :public Scene
{
public:
	TitleScene()
	{
		m_pObjManager->Resister(static_cast<Obj*>(new TitleBack()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleLogo()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleInputPrompt()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleMenu()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleCometEffect()));
		m_pObjManager->Resister(static_cast<Obj*>(new TitleSmallStarEffect()));
	}

	~TitleScene() {};
};

#endif // !TITLE_SCENE_H
