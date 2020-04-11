#include"../System/KdLibrary/KdLibrary.h"
//#include<d3dx9.h>
#include"CGameScene.h"
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include"C_Player.h"
#include"Skysphere.h"
#include"Sea.h"
#include"Port.h"
#include"Fish.h"



CGameScene::CGameScene()
{
	//�X�J�C�X�t�B�A
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	//�C
	Seas = std::make_shared<Sea>();

	//�`
	m_Port = std::make_shared<Port>();
	m_Port->Init();
	//��
	Fishes = std::make_shared<Fish>();
	Fishes->Init();
	//�v���C���[
	m_Player = std::make_shared<C_Player>();

	//m_PSound->LoadSound("Resouce/Sound/MetroNight.wav");
	//m_PSound->SoundPlay("Resouce/Sound/MetroNight.wav", true, false, nullptr);
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	m_Player->Update();
	Sky->SetPos(m_Player->GetPlayerPos());
	m_Port->Update();
	Fishes->Update();
}

void CGameScene::Draw2D()
{
	m_Player->Draw2D();
}

void CGameScene::Draw3D()
{
	Sky->Draw3D();
	m_Port->Draw3D();
	Seas->Draw();
	Fishes->Draw3D();
	//m_Player->Draw3D();
}
