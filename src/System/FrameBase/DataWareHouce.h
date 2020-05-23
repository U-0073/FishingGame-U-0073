#pragma once

class DataWareHouce
{
public:
	void SetName(const std::string& Tag, const std::string& data)	{ Str[Tag] = data; }
	void SetPos (const std::string& Tag, const KdVec3& data)		{ Pos[Tag] = data; }
	void SetNo  (const std::string& Tag, const float& data)			{ No[Tag] = data; }
	void SetFlg  (const std::string& Tag, const float& data)			{ Flg[Tag] = data; }

	std::string& GetFishName(const std::string& Tag) { return Str[Tag]; }
	KdVec3&		GetPos(const std::string& Tag)		{ return Pos[Tag]; }
	float&	    GetNo(const std::string& Tag)		{ return No[Tag]; }
	bool&	    GetFlg(const std::string& Tag)		{ return Flg[Tag]; }

private:
	std::map<std::string, std::string>	Str;
	std::map<std::string, KdVec3>		Pos;
	std::map<std::string, float>		No;
	std::map<std::string, bool>		Flg;

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