#pragma once

class GameObject
{
public:
	GameObject();
	GameObject(LPDIRECT3DDEVICE9 lpD3DDevice);
	~GameObject();
	virtual void Init();		//仮想関数
	virtual void Update() = 0;	//純粋仮想関数
	virtual void Draw2D(LPDIRECT3DDEVICE9 lpD3DDevice);
	virtual void Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice);

protected:
	KdMatrix m_world;
	std::shared_ptr<KdModel> m_pModel = nullptr;



};