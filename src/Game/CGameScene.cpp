#include"../System/KdLibrary/KdLibrary.h"
#include"CGameScene.h"
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include"C_Player.h"
#include"TestCharacter.h"
#include"Skysphere.h"
#include"Sea.h"



CGameScene::CGameScene()
{
	//�e�X�g�L�����N�^�[
	test = std::make_shared<TestCharacter>();
	test->Init();
	//�X�J�C�X�t�B�A
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	Seas = std::make_shared<Sea>();

	//�v���C���[
	m_Player = std::make_shared<C_Player>();
	
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	m_Player->Update();
}

void CGameScene::Draw2D()
{
	m_Player->Draw2D();
}

void CGameScene::Draw3D()
{
	test->Draw3D();
	Sky->Draw3D();
	Seas->Draw();
	m_Player->Draw3D();
}
