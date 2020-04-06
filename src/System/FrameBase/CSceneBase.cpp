#include"../KdLibrary/KdLibrary.h"
#include "../FrameBase/CSceneBase.h"






CSceneBase::CSceneBase()

{





}


CSceneBase::~CSceneBase()
{

}

void CSceneBase::Update()
{


}

void CSceneBase::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);


	SPRITE->End();
}

void CSceneBase::Draw3D()
{
}


