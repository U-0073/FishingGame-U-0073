#pragma once

class GameObject
{
public:
	GameObject();
	GameObject(LPDIRECT3DDEVICE9 lpD3DDevice);
	~GameObject();
	virtual void Init();		//âºëzä÷êî
	virtual void Update() = 0;	//èÉêàâºëzä÷êî
	virtual void Draw2D();
	virtual void Draw3D();

protected:
	KdMatrix m_world;
	std::shared_ptr<KdModel> m_pModel = nullptr;



};