#ifndef ___CLASS_RUNDISTJUDGEMENT
#define ___CLASS_RUNDISTJUDGEMENT

#include "JudgeMent.h"
#include "RunDistDetect.h"

class RunDistJudgeMent : public JudgeMent {
private:
	RunDistDetect *mRunDistDetect;

	enum eTire { RIGHT, LEFT, BOTH, };

	float mtarget_dist;
	float mcurrent_dist;
	unsigned char mtire;
	
public:
	RunDistJudgeMent(unsigned char tire, float target_dist);
	~RunDistJudgeMent();
	bool judge();
};

#endif // ___CLASS_RUNDISTJUDGEMENT