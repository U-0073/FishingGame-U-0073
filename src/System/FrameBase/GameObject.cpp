#include"../KdLibrary/KdLibrary.h"
#include"GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(LPDIRECT3DDEVICE9 lpD3DDevice)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	D3DXMatrixIdentity(&m_world);
}

void GameObject::Draw2D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
}

void GameObject::Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
}
