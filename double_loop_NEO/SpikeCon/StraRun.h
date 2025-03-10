#ifndef ___CLASS_STRARUN
#define ___CLASS_STRARUN	// インクルードカード

#include "abstract_run.h"
#include "PDcon.h"

class StraRun : public Run {
private:
	static const unsigned char mSTRAIGHT = 0;
	PDcon *mPDcon;
	int mturn;
public:
	StraRun(int pwm = 70);
	~StraRun();
	void run();
};

#endif // ___CLASS_STRARUN
