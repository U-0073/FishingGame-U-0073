#pragma once

class KdMatrix;

//���b�s���O:���C�u�����⑼�l�̍�����v���O������
//�g���₷���悤�Ɏ���̃N���X��֐��Ɏ��߂邱��
class KdVec3 :public D3DXVECTOR3{

public:
	KdVec3(){ x = y = z = 0; }
	KdVec3(float ix, float iy, float iz){ 
		x = ix;y = iy;z = iz;
	}
	KdVec3(const D3DXVECTOR3& v) {
		x = v.x; y = v.y; z = v.z;
	}

	//�u=�v���Z�q���g��ꂽ��g�p�����֐�
	const D3DXVECTOR3& operator=(const D3DXVECTOR3& v) {
		x = v.x; y = v.y; z = v.z;
		return *this;//=�̐���Ȃ��Ɏg����
	}



	//�ݒ�
	void Set(float ix, float iy, float iz) {
		x = ix; y = iy; z = iz;
	}
	//�P�ʍs��
	void Normalize() {
		D3DXVec3Normalize(this, this);
	}

	//�w��̒����Ƀx�N�g���𑵂���(�����͂��̂܂�)
	void SetLength(float len){
		Normalize();
		*this *= len;
	}
	void TransCoord(const KdMatrix& mat);
	void TransNormal(const KdMatrix& mat);

	//�x�N�g���̒������擾
	float Length()const { return D3DXVec3Length(this); }

	float LengthToTarget(const KdVec3& v) const{
		KdVec3 vv = v- (*this) ;
		return D3DXVec3Length(&vv);
	}

	//�����������������t�s��
	void  Inverse(KdVec3& v) const{v= (*this)*-1; }
	//���������������ċt�s��
	const void Inverse() { *this *= -1; }
};

//�}�g���b�N�X�֌W���b�v
class KdMatrix :public D3DXMATRIX {

	//�����o�ϐ��̒ǉ��֎~
public:
	
	KdMatrix(){ D3DXMatrixIdentity(this); }
	
	KdMatrix(const D3DXMATRIX& m) { 
		*(D3DXMATRIX*)this = m;
	}

	const D3DXMATRIX& operator=(const D3DXMATRIX& m)
	{
		*(D3DXMATRIX*)this = m;
		return *this;
	}


	//�ړ�
	void CreateTrans(float x, float y, float z) {
		(*this)._41 = x;
		(*this)._42 = y;
		(*this)._43 = z;


	}
	void CreateTrans(const KdVec3& v) {
		(*this)._41 = v.x;
		(*this)._42 = v.y;
		(*this)._43 = v.z;
	}

	//��]
	void CreateRotationX(const float rad) {
		KdVec3 pos, scl;
		KdMatrix  rM, sM;

		pos = (*this).GetPos();
		scl.x = (*this).GetScaleX();
		scl.y = (*this).GetScaleY();
		scl.z = (*this).GetScaleZ();
		D3DXMatrixRotationX(this, rad);
		D3DXMatrixScaling(&sM, scl.x, scl.y, scl.z);
		(*this) = sM * rM * (*this);
		(*this)._41 = pos.x;
		(*this)._42 = pos.y;
		(*this)._43 = pos.z;
	}
	void CreateRotationY(const float rad) {
		KdVec3 pos, scl;
		KdMatrix  rM, sM;

		pos = (*this).GetPos();
		scl.x = (*this).GetScaleX();
		scl.y = (*this).GetScaleY();
		scl.z = (*this).GetScaleZ();
		D3DXMatrixRotationY(this, rad);
		D3DXMatrixScaling(&sM, scl.x, scl.y, scl.z);
		(*this) = sM * rM * (*this);
		(*this)._41 = pos.x;
		(*this)._42 = pos.y;
		(*this)._43 = pos.z;
	}
	void CreateRotationZ(const float rad) {
		KdVec3 pos, scl;
		KdMatrix  rM, sM;
		pos = (*this).GetPos();
		scl.x = (*this).GetScaleX();
		scl.y = (*this).GetScaleY();
		scl.z = (*this).GetScaleZ();
		D3DXMatrixRotationZ(this, rad);
		D3DXMatrixScaling(&sM, scl.x, scl.y, scl.z);
		(*this) = sM * rM * (*this);
		(*this)._41 = pos.x;
		(*this)._42 = pos.y;
		(*this)._43 = pos.z;
	}
	void CreateRotation(float radx, float rady, float radz) {
		KdVec3 pos, scl;
		KdMatrix  rM,sM,Mat;
		pos = (*this).GetPos();
		scl.x = (*this).GetScaleX();
		scl.y = (*this).GetScaleY();
		scl.z = (*this).GetScaleZ();
		D3DXMatrixRotationYawPitchRoll(&rM,rady,radx, radz);
		D3DXMatrixScaling(&sM, scl.x, scl.y, scl.z);
		D3DXMatrixTranslation(&Mat, pos.x, pos.y, pos.z);
		(*this) = sM * rM, Mat;
	}

	//�g��s��
	inline void CreateScale(float x, float y, float z) {
		KdVec3 Pos = (*this).GetPos();

		KdMatrix scl,Mat,rM;

		D3DXMatrixTranslation(&Mat, Pos.x, Pos.y, Pos.z);
		rM = (*this);
		
		rM._41 = 0;
		rM._42 = 0;
		rM._43 = 0;
		D3DXMatrixScaling(&scl, x, y, z);
		(*this)=rM * scl*Mat;

	}
	//���I�Ȋg��s��̕ύX

	void MoveScal(float x, float y, float z) {
		KdMatrix s;
		D3DXMatrixScaling(&s, x, y, z);
		(*this) = s * (*this);
	}

	//����n--------------------------->
	//������k�V�n�ɐi��float
	void MoveWorld(float x, float y, float z) {
		KdMatrix m;
		m.CreateTrans(x, y, z);
		*this = (*this)*m;
	}

	//������k�V�n�ɐi��
	void MoveWorld(const KdVec3& v) {
		KdMatrix m;
		m.CreateTrans(v.x, v.y, v.z);
		*this = (*this)*m;
	}

	//�㉺���E�ɓ���float
	void MoveLocal(float x, float y, float z) {
		KdMatrix m;
		m.CreateTrans(x, y, z);
		*this = m * (*this);
	}


	//�㉺���E�ɓ���
	void MoveLocal(const KdVec3& v) {
		KdMatrix m;
		m.CreateTrans(v.x, v.y, v.z);
		*this = m * (*this);
	}
	
	//���E���W��]
	void RotateXWorld(float rad) {
		KdMatrix m;
		m.CreateRotationX(rad);
		*this = (*this)*m;
	}
	void RotateYWorld(float rad) {
		KdMatrix m;
		m.CreateRotationY(rad);
		*this = (*this)*m;
	}
	void RotateZWorld(float rad) {
		KdMatrix m;
		m.CreateRotationZ(rad);
		*this = (*this)*m;
	}
	void RotateWorld(float radx, float rady, float radz ) {
		KdMatrix m;
		m.CreateRotation(radx,rady,radz);
		*this = (*this)*m;
	}
	//�������W��]
	void RotateXLocal(float rad) {
		KdMatrix m;
		m.CreateRotationX(rad);
		*this = m * (*this);
	}
	void RotateYLocal(float rad) {
		KdMatrix m;
		m.CreateRotationY(rad);
		*this = m * (*this);
	}void RotateZLocal(float rad) {
		KdMatrix m;
		m.CreateRotationZ(rad);
		*this = m * (*this);
	}
	void RotateLocal(float radx, float rady, float radz) {
		KdMatrix m;
		m.CreateRotation(radx, rady, radz);
		*this = m * (*this);
	}
	void Scaling(float x, float y, float z) {
		KdMatrix m;
		m.CreateScale(x, y, z);
		*this = m * (*this);
	}

	//�t�s��
	void Inverse() {
		D3DXMatrixInverse(this, NULL, this);
	}

	
	const KdVec3& GetPos()const {
		return *(KdVec3*)&_41;//float�^��vec3�|�C���^�ɃL���X�g�����Q�Ƃ̃A�h���X
	}

	//�������̃x�N�g��
	const KdVec3&GetXAxis()const {
		return*(KdVec3*)&_11;
	}
	//������̃x�N�g��
	const KdVec3&GetYAxis()const {
		return*(KdVec3*)&_21;
	}
	//�O�����̃x�N�g��
	const KdVec3&GetZAxis()const {
		return*(KdVec3*)&_31;
	}

	//�g�嗦=����
	float GetScaleX()const {
		return GetXAxis().Length();
	}
	float GetScaleY()const {
		return GetYAxis().Length();
	}
	float GetScaleZ()const {
		return GetZAxis().Length();
	}

	//////�����̌X��rad�p
	//float GetXDegRot() {
	//	KdVec3 v = GetYAxis();

	//	v.Normalize();
	//	v.x = 0;

	//	float ToRot = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &v);

	//	//======================================

	//	//�p�x�ϊ�
	//	ToRot = D3DXToDegree(acos(ToRot));
	//	//�␳
	//	if (v.x < 0) {
	//		ToRot *= -1;
	//	}
	//	return ToRot;
	//}



	//////�����̌X��rad�p
	//float GetYDegRot(){
	//	KdVec3 v = GetXAxis();

	//	v.Normalize();
	//	v.y = 0;

	//	float ToRot = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &v);

	//	//======================================

	//	//�p�x�ϊ�
	//	ToRot = D3DXToDegree(acos(ToRot));
	//	//�␳
	//	if (v.y < 0) {
	//		ToRot *= -1;
	//	}
	//	return ToRot;
	//}
	////�����̌X��rad�p
	//float GetZDegRot() {
	//	KdVec3 v = GetXAxis();

	//	v.Normalize();
	//	//v.Inverse();
	//	v.z = 0;

	//	float ToRot = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &v);

	//	//======================================

	//	//�p�x�ϊ�
	//	ToRot = D3DXToDegree(acos(ToRot));
	//	//�␳
	//	if (v.x < 0) {
	//		ToRot *= -1;
	//	}
	//	ToRot *= -1;
	//	return ToRot;

	//}
	
};