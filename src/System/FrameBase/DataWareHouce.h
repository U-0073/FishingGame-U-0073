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

	//シングルトン
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
釣れた魚の名前

Game
missとかの数

Result
売却金額

Shop
何を買ったか、何を装備してるか
所持金
*/