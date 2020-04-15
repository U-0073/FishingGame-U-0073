#include"../KdLibrary/KdLibrary.h"
#include "CSceneBase.h"
#include"wavread.h"





CSceneBase::CSceneBase()

{





}


CSceneBase::~CSceneBase()
{

}

void CSceneBase::Init()
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


