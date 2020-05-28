#include"../System/KdLibrary/KdLibrary.h"
#include"ShopObject.h"

ShopObject::ShopObject()
{
}

ShopObject::~ShopObject()
{
}

	KdVec3 getvec;
	KdMatrix getmat;

void ShopObject::Init()
{
	GameObject::Init();
	Rod["Wood"] = RESOURCE_MNG.GetModel("WoodRod");
	Rod["Carbon"] = RESOURCE_MNG.GetModel("CarbonRod");
	Rod["Bamboo"] = RESOURCE_MNG.GetModel("BambooRod");
	Rod["Golden"] = RESOURCE_MNG.GetModel("GoldenRod");

	Reel["Reel"] = RESOURCE_MNG.GetModel("Reel");
	Reel["SimpleReel"] = RESOURCE_MNG.GetModel("SimpleReel");
	
	//ƒJƒƒ‰‚ÌÝ’è
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -5.5f), D3DXVECTOR3(0, 0, 1));

	//ˆÊ’u’²®
	m_world.MoveLocal(0.5f, -0.5f, 0);
	m_world.SetRotation(D3DXToRadian(0), D3DXToRadian(90), D3DXToRadian(-45));

	m_reel.SetTrans(9, 7, 0);
	m_reelScal.SetScale(40, 40, 40);
	m_reel = m_reelScal * m_reel;
	
	KD3D.CreateDirectionalLight(D3DXVECTOR3(0, 0, 10), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0));
}

void ShopObject::Update()
{

}

void ShopObject::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	if (tPattern == 0) {
		//’Þ‚èŠÆ
		switch (Cur)
		{
		case 0:
			Rod["Wood"]->Draw();
			break;
		case 1:
			Rod["Carbon"]->Draw();
			break;
		case 2:
			Rod["Wood"]->Draw();
			break;
		case 3:
			Rod["Bamboo"]->Draw();
			break;
		case 4:
			Rod["Carbon"]->Draw();
			break;
		case 5:
			Rod["Golden"]->Draw();
			break;
		case 6:
			Rod["Bamboo"]->Draw();
			break;
		case 7:
			Rod["Golden"]->Draw();
			break;
		}
	}
	D3DEV->SetRenderState(D3DRS_LIGHTING, FALSE);


	KD3D.SetWorldMatrix(&m_reel);
	D3DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	if (tPattern == 2) {
		//ƒŠ[ƒ‹
		switch (Cur)
		{
		case 0:
			Reel["Reel"]->Draw();
			break;
		case 1:
			Reel["SimpleReel"]->Draw();
			break;
		case 2:
			Reel["Reel"]->Draw();
			break;
		case 3:
			Reel["SimpleReel"]->Draw();
			break;
		case 4:
			Reel["Reel"]->Draw();
			break;
		case 5:
			Reel["SimpleReel"]->Draw();
			break;
		case 6:
			Reel["Reel"]->Draw();
			break;
		case 7:
			Reel["SimpleReel"]->Draw();
			break;
		}
	}
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void ShopObject::End()
{
	m_pModel = nullptr;
	Rod["Wood"] = nullptr;
	Rod["Carbon"] = nullptr;
	Rod["Bamboo"] = nullptr;
	Rod["Golden"] = nullptr;
}

void ShopObject::Get2D(int tPat, int cur)
{
	tPattern = tPat;
	Cur = cur;
}
