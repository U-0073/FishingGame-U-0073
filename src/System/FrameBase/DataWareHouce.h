#pragma once

class DataWareHouce
{
public:
	void SetFishName(std::string data) { FishName = data; };
	void SetPos(D3DXVECTOR3 data) {};
	void SetNo(float data) {};

	std::string GetFishName() { return FishName; };
	D3DXVECTOR3 GetPos() { return Pos; };
	float	    GetNo() { return No; };

private:
	std::string FishName;
	D3DXVECTOR3 Pos;
	float		No;

	//�V���O���g��
private:

	DataWareHouce() {
	}

public:
	static DataWareHouce& GetInstance() {
		static DataWareHouce Instance;
		return Instance;
	}
};

#define DTWHOUCE DataWareHouce::GetInstance()
/*
Map
�ނꂽ���̖��O

Game
miss�Ƃ��̐�

Result
���p���z

Shop
���𔃂������A���𑕔����Ă邩
������
*/