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
	
	//ƒJƒƒ‰‚ÌÝ’è
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -5.5f), D3DXVECTOR3(0, 0, 1));

	//ˆÊ’u’²®
	m_world.MoveLocal(0.5f, -0.5f, 0);
	m_world.RotateLocal(D3DXToRadian(-45), D3DXToRadian(90), D3DXToRadian(0));

	//D3DXVec3TransformCoord(&getvec, &D3DXVECTOR3(0, 0, 2.5f),&m_world);
	//getmat.CreateTrans(getvec);
	//m_world = m_world * getmat;
}

void ShopObject::Update()
{
	
}

void ShopObject::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (tPattern == 0) {
		Rod["Wood"]->Draw();
		Rod["Carbon"]->Draw();
		Rod["Bamboo"]->Draw();
		Rod["Golden"]->Draw();
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

void ShopObject::GetListChange(int tPat)
{
	tPattern = tPat;
}
