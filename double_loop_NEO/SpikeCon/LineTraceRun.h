#ifndef ___CLASS_LINETRACERUN
#define ___CLASS_LINETRACERUN	// インクルードカード

#include "abstract_run.h"
#include "PDcon.h"

class LineTraceRun : public Run {
private:
	static const unsigned char mLINETRACE = 1;

	PDcon *mPDcon;

	enum eEdge { RIGHT, LEFT, };

	int mturn;
	unsigned char medge;

public:
	LineTraceRun(unsigned char edge, int pwm = 42);
	~LineTraceRun();
	void run();
};

#endif // ___CLASS_LINETRACERUN
