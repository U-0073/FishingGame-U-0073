#pragma once

class GameObject
{
public:
	GameObject();
	GameObject(LPDIRECT3DDEVICE9 lpD3DDevice);
	~GameObject();
	virtual void Init();		//���z�֐�
	virtual void Update() = 0;	//�������z�֐�
	virtual void Draw2D(LPDIRECT3DDEVICE9 lpD3DDevice);
	virtual void Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice);

protected:
	KdMatrix m_world;
	std::shared_ptr<KdModel> m_pModel = nullptr;



};