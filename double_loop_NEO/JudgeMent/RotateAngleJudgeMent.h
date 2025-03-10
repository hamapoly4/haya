#ifndef ___CLASS_ROTATEANGLEJUDGEMENT
#define ___CLASS_ROTATEANGLEJUDGEMENT

#include "JudgeMent.h"
#include "GyroSensor.h"

class RotateAngleJudgeMent : public JudgeMent {
private:
	static ev3api::GyroSensor mGyroSensor;

	enum eRota { RIGHT, LEFT, };
	
	int mtarget_angle;
	int mcurrent_angle;
	unsigned char mrota;
	bool angle_reset;

public:
	RotateAngleJudgeMent(unsigned char rota, int target_angle);
	~RotateAngleJudgeMent();
	bool judge();
};

#endif // ___CLASS_ROTATEANGLEJUDGEMENT
