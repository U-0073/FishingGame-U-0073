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

void GameObject::Init(LPDIRECT3DDEVICE9 &lpD3DDevice)
{
	D3DXMatrixIdentity(&m_world);
}

void GameObject::Draw2D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
}

void GameObject::Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
}
