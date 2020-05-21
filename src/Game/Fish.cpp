#include"../System/KdLibrary/KdLibrary.h"
#include"Fish.h"

Fish::Fish()
{
}

Fish::~Fish()
{
}

void Fish::SetTagType(int No)
{
	switch (No)
	{
	case 0:
		m_Tag = "RedSnapper";
	
		break;
	case 1:
		m_Tag = "Saury";	
		break;
	case 2:
		m_Tag = "Tuna";
		break;
	case 3:
		m_Tag = "Shark";
		break;
	case 4:
		m_Tag = "SunFish";
		break;
	case 5:
		m_Tag = "Whale";
		break;
	}
}

void Fish::Init()
{
	GameObject::Init();



	m_pModel= RESOURCE_MNG.GetModel(m_Tag);
	
}

void Fish::Update()
{
	FishLen = KdVec3(FishPos.x, FishPos.y, FishPos.z);
	KdVec3 m,n;

	float len =m.LengthToTarget(n);

	if (GetKey('Q') & 0x8000)
	{
		Init();
	}

	KdMatrix RotMat;
	static float FishPosZCnt;
	static float FishPosYCnt;

	if (!FishFlg) {
		D3DXVECTOR3	Vec;

		RotMat.CreateRotationY(D3DXToRadian(CamAngY));
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);

		FishPos = PlayerPos + Vec * 20 - KdVec3(0.0f, 4.0f, 0.0f);
		FishPosZCnt = 20.0f;
		FishPosYCnt = 8.0f;
	}
	else {
		if (FishPosZCnt > 0 &&FishPosYCnt<7) {

			D3DXVECTOR3	Vec;
			RotMat.CreateRotationY(D3DXToRadian(CamAngY));
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);

			FishPos -= Vec * 0.5;
			FishPosZCnt -= 0.5f;
		}

		if (FishPosYCnt > 0) {
			if (FishPosYCnt > 7) {
				FishPos += KdVec3(0.0f, 0.2f, 0.0f);
				FishPosYCnt -= 0.2f;
			}
			else {
			FishPos += KdVec3(0.0f, 0.2f, 0.0f);
			FishPosYCnt -= 0.4f;
			}
		}
	}

	KdMatrix RotMatX;
	//RotMatX.CreateRotationX(D3DXToRadian(90));

	
	
	
	
	m_world.MoveLocal(0, 0, -0.5);

	
	m_world.RotateYLocal(D3DXToRadian((rand()%10)-5));

}


void Fish::Draw2D()
{
	SPRITE->End();
	RECT rcText = { 10,30 * 0,0,0 };
	char Text[100];
	sprintf_s(Text, sizeof(Text), "FishPos x %f y %f z %f", FishPos.x, FishPos.y, FishPos.z);
	FONT->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
}

void Fish::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Fish::End()
{
	m_pModel = nullptr;
}

void Fish::TitleUpdate()
{

	D3DXMATRIX RotMat;
	D3DXMatrixRotationY(&RotMat, D3DXToRadian(0));
	D3DXVECTOR3 Vec;
	D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0.0f, 0.0f, -0.05f), &RotMat);
	FishPos += Vec;
	
	TransMat.CreateTrans(FishPos);
	m_world = ScaleMat * TransMat;

}

void Fish::ResultUpdate()
{
	D3DXMATRIX RotMat;
	D3DXMatrixRotationY(&RotMat, D3DXToRadian(90));
	FishPos = D3DXVECTOR3(0.0f,1.0f, 0);
	TransMat.CreateTrans(FishPos);
	ScaleMat.CreateScale(1,1,1);
	
	m_world = ScaleMat*TransMat*RotMat;
}



void Fishes::Init()
{
	std::vector<std::shared_ptr<Fish>>m_Fishs;
	for (int c = 0; c < 3; c++) {
		int name = rand() % 3;
		KdVec3 Pos;
		for (int i = 0; i < rand() % 5; i++) {

			auto l_Fish = std::make_shared<Fish>();


			l_Fish->SetTagType(name);
			l_Fish->Init();
			Pos=+l_Fish->GetPos();
			m_Fishs.push_back(l_Fish);
			

		}
		if (m_Fishs.size()>0) {
			Pos = Pos / m_Fishs.size();
			CenterPoss.push_back(Pos);
			m_Fihes.push_back(m_Fishs);//“ñŽŸŒ³”z—ñ‰»
			c++;
		}
		
	}
}
void Fishes::Update()
{
	int i = 0;
	for (auto&& p : m_Fihes) {

		int c=0;
		for (auto&& pp : p) {
			CenterPoss[i]+=pp->GetPos();
			pp->Update();
			c++;
		}
		if (c != 0) {
			CenterPoss[i] = CenterPoss[i] / (float)c;
		}
		for (auto&& pp : p) {
			CenterPoss[i] += pp->GetPos();
			pp->SetCenter(CenterPoss[i]);
		}
	}


	

}

void Fishes::Draw2D()
{
	for (auto&& p : m_Fihes) {
		for (auto&& pp : p) {
			pp->Draw2D();

		}
	}
}

void Fishes::Draw3D()
{
	for (auto&& p : m_Fihes) {
		for (auto&& pp : p) {
			pp->Draw3D();

		}
	}
}
