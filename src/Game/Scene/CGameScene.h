#pragma once
#include"../../System/FrameBase/CSceneBase.h"

//default数値マジックナンバつぶし
#define scaleInitialize 2.0f
#define scaleLimit 0.0f

#define EFReduction 0.0215f		//EveryFrameInitialize、毎フレーム縮小用
#define clickInitialize 10
#define defLenInitialize 10000	//Lenの初期呼び出し

#define ZEROreturn 0				//0入れて制御する用。NULLじゃダメなのか？

//judge関連
#define judgeMin 0.5
#define judgeMax 1.0
#define Length 100
#define FishSuccess 0.6
enum judgeNum
{
	Default_judge,
	Excellent_judge,
	Miss_judge,
};

//music関連
#define MFInitialize 240		//MusicFrameInitialize、曲初期フレーム呼び出し
enum MusicChoiseNum
{
	PhantomA2,		//Phantom_Apartment_2
	DDCats,				//Dance_Dance_Cats
	GStage2	,			//Green_Stage_2
	ROTWind2,			//Ride_On_The_Wind_2
	START,				//START!!
	ROTWindSP,		//Ride_On_The_Wind
	MusicGenerally	//音楽の総量
};



class CGameProc;

class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return GAME; };
	void End()override;
private:
	//固定枠
	std::shared_ptr<LPDIRECT3DTEXTURE9> ringTex = nullptr;
	KdMatrix ringMat;


	//ノーツ
	std::shared_ptr<LPDIRECT3DTEXTURE9> notesTex = nullptr;
	KdMatrix notesMat;
	float scale;

	//判定文字
	std::shared_ptr<LPDIRECT3DTEXTURE9> judgeTex = nullptr;
	std::shared_ptr<LPDIRECT3DTEXTURE9> resultTex = nullptr;
	KdMatrix judgeMat;

	std::shared_ptr<LPDIRECT3DTEXTURE9> backTex = nullptr;
	KdMatrix backMat;

	float speed;
	int size;
	int clickNum;
	bool keyFlg;
	int frame;
	int judgeFlg;

	//マウス関連
	POINT Mouse;
	KdVec3 clickPos;
	float len;
	bool Check;
	bool frameStopper;

	int MusicChoise;

	//判定用画像のポジション設定用関数
	const void SetPos(const KdVec3& Vec) {
		judgeMat._41 = Vec.x;
		judgeMat._42 = Vec.y;
		judgeMat._43 = Vec.z;
	}


	KdVec3 score;
	const void SetScore(const int Excellent, const int Miss)
	{
	}


	//スコアチェッカー
	int clickCNT;
	int Excellent;
	int Miss;

	//何の魚か
	std::string name;

	std::shared_ptr<SoundBase> m_pSound = nullptr;

};