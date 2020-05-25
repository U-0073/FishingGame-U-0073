#include"../System/KdLibrary/KdLibrary.h"
#include"../System/FrameBase/CGameFrame.h"
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
	if (!m_Tag.length())
	{
		if (MessageBox(GETHWND, "魚の名前が設定されていません", "Error", MB_ICONINFORMATION) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	m_pModel = RESOURCE_MNG.GetModel(m_Tag);
	m_world.SetScale(0.1, 0.1, 0.1);

}

void Fish::Update()
{
	if (GetKey('Q') & 0x8000)
	{
		Init();
	}
	//振り向き処理
	if (DTWHOUCE.GetFlg("Fishing"))
	{
		MoveHoriizontal();
	/*
		{
			//今魚がどこを向いているか
			KdVec3 vKVec;
			D3DXVec3TransformNormal(&vKVec, &KdVec3(0, 0, 1), &m_world);
			float nowRot = D3DXVec3Dot(&KdVec3(0, 0, 1), &vKVec);
			nowRot = D3DXToDegree(acos(nowRot));
			if (vKVec.x < 0) { nowRot *= -1; }

			//魚とウキの角度の差
			KdVec3 fpos, bpos;
			fpos = m_world.GetPos();
			bpos = DTWHOUCE.GetVec("Buoy");
			fpos = bpos - fpos;
			fpos.y = 0;
			fpos.Normalize();
			float FishRot = D3DXVec3Dot(&KdVec3(0, 0, 1), &fpos);
			FishRot = D3DXToDegree(acos(FishRot));
			if (fpos.x < 0) { FishRot *= -1; }

			//どっち向きに何度移動するか
			float Rot = FishRot - nowRot;
			if (Rot > 180) { Rot = 360 - Rot; }
			if (Rot < -180) { Rot = 360 + Rot; }
			if (Rot > 0) {
				if (Rot > 3) { m_world.RotateYLocal(D3DXToRadian(3.0f)); }
				if (Rot < 3) { m_world.RotateYLocal(D3DXToRadian(Rot)); }
			}
			if (Rot < 0) {
				if (Rot < -3) { m_world.RotateYLocal(D3DXToRadian(-3.0f)); }
				if (Rot > -3) { m_world.RotateYLocal(D3DXToRadian(Rot)); }
			}
			m_world.MoveLocal(0, 0, -0.5);
			//m_world.RotateYLocal(D3DXToRadian((rand() % 10) - 5));
		}
	*/
	}
	else
	{
		//フラフラ動く
		m_world.MoveLocal(0, 0, -0.5);
		m_world.RotateYLocal(D3DXToRadian((rand() % 10) - 5));
	}
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

void Fish::TitleInit()
{
	m_Tag = "RedSnapper";
	m_pModel = RESOURCE_MNG.GetModel(m_Tag);
	m_world.SetScale(0.2, 0.2, 0.2);

}
void Fish::TitleUpdate()
{
	m_world.MoveLocal(0, 0, -0.5);
}

void Fish::ResultInit()
{
	m_Tag = DTWHOUCE.GetStr("FishName");
	if (!m_Tag.length())
	{
		if (MessageBox(GETHWND, "魚の名前が設定されていません", "Error", MB_ICONINFORMATION) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	m_pModel = RESOURCE_MNG.GetModel(m_Tag);

	m_world.SetTrans(0.0f, 5.0f, 0);
	m_world.CreateRotationY(D3DXToRadian(90));
	m_world.SetScale(2, 2, 2);
}

void Fish::MoveHoriizontal()
{
	KdVec3 fpos, bpos;
	fpos = m_world.GetPos();
	bpos = DTWHOUCE.GetVec("Buoy");




	//自分の逆行列を計算
	auto mInv = m_world;
	mInv.Inverse();


	KdVec3 vTo;
	D3DXVec3TransformCoord(&vTo, &bpos, &mInv);
	float dist = vTo.Length();
	vTo.Normalize();




	//操縦桿を左右に
	KdVec3 vCross;

	auto vnZ = vTo;
	vnZ.x =0 ;
	vnZ.Normalize();

	//さらに細かい計算をするために内積を求める
	float dot = D3DXVec3Dot(&vnZ, &KdVec3(0, 0, 1));
	float rad = acos(dot);//2つのベクトルがなす角(ラジアン角)



	//自分の姿勢から見た方向なので0,-1,0でOK
	D3DXVec3Cross(&vCross, &vnZ, &KdVec3(0, 0, 1));
	if (vCross.z > 0.1f) { m_world.RotateYLocal(D3DXToRadian(-5));}
	if (vCross.z < -0.1f) { m_world.RotateYLocal(D3DXToRadian(5)); }
	//フラフラ動く
	m_world.MoveLocal(0, 0, -0.5);


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
			Pos = +l_Fish->GetPos();
			m_Fishs.push_back(l_Fish);


		}
		if (m_Fishs.size() > 0) {
			Pos = Pos / m_Fishs.size();
			CenterPos.push_back(Pos);
			m_Fihes.push_back(m_Fishs);//二次元配列化
			c++;
		}

	}
}

void Fishes::Update()
{
	int i = 0;
	for (auto&& p : m_Fihes) {

		int c = 0;
		for (auto&& pp : p) {
			CenterPos[i] += pp->GetPos();
			pp->Update();
			c++;
		}
		if (c != 0) {
			CenterPos[i] = CenterPos[i] / (float)c;
		}
		for (auto&& pp : p) {
			CenterPos[i] += pp->GetPos();
			pp->SetCenter(CenterPos[i]);
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
