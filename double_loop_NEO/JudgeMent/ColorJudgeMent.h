#ifndef ___CLASS_COLORJUDGEMENT
#define ___CLASS_COLORJUDGEMENT

#include "JudgeMent.h"
#include "ColorDetect.h"

class ColorJudgeMent : public JudgeMent {
private:
	ColorDetect *mColorDetect;

	unsigned char mtarget_color;
	unsigned char mcurrent_color;

public:
	ColorJudgeMent(unsigned char target_color);
	~ColorJudgeMent();
	bool judge();
};

#endif // ___CLASS_COLORJUDGEMENT