#ifndef BASE_STAR_H_
#define BASE_STAR_H_

#include <Windows.h>

struct StarPlace
{
	D3DXVECTOR3	m_Pos;				//x,y,z���W
	float m_DropPerMinute;			//1���Ԃɂǂꂾ�������Ă��邩
	float m_Time;					//����T�Ă��鎞��
	int m_Division;					//�敪����
	int m_StarsNumInDivision;		//�敪���̒��̐��̐�
};

#include "../../../Obj.h"
/*
*�x�[�X�X�^�[�N���X
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
	VOID PosOfStarYCoordinate();								//�����Ă��鎞�Ԑݒ�֐�

protected:
	VOID InitBaseStar();										//�G�ɕK�v�ȏ��̏������֐�
	VOID FollingStarPosYTime(const LONGLONG& rCurrentTime);		//y���W���ړ�������֐�
	VOID DefaultLight();										//���C�g�̃f�t�H���g�l�ݒ�֐�
	VOID ConvertLocalToWorld(D3DXMATRIX* matWorld);				//���[�J�����W���烏�[���h���W�ւ̕ϊ�

	StarPlace m_Info;				//�X�^�[�̊�{���

	const float ColorMax = 255.f;
};

#endif // !BASE_STAR_H_