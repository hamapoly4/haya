#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "abstract_run.h"	// 抽象クラスのヘッダ（走行）
#include "RotateRun.h"		//
#include "StraRun.h"		//
#include "LineSearchRun.h"	//
#include "LineTraceRun.h"	// 派生クラス

#include "JudgeMent.h"				// 抽象クラスのヘッダ（判定）
#include "RotateAngleJudgeMent.h"	//
#include "RunDistJudgeMent.h"		//
#include "ColorJudgeMent.h"			// 派生クラス

class Scene {
private:
	enum eWhich { RIGHT, LEFT, BOTH, };

	enum eColor { BLACK, BLUE, };

	Run* mRun[19];
	JudgeMent* mJudgeMent[19];

	unsigned char mcurrent_scene_no;

public:
	Scene(unsigned char scene_no);
	~Scene();
	void run();
	bool fin_judge();
};

#endif // ___CLASS_SCENE
