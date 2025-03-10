#ifndef ___CLASS_ROTATERUN
#define ___CLASS_ROTATERUN	// インクルードカード

#include "abstract_run.h"

class RotateRun : public Run {
private:
	enum Rota { RIGHT, LEFT, };
	unsigned char mrota;

public:
	RotateRun(unsigned char rota, int pwm = 55);
	~RotateRun();

	void run();
};

#endif // ___CLASS_ROTATERUN
