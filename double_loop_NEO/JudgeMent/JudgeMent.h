#ifndef ___CLASS_JUDGEMENT
#define ___CLASS_JUDGEMENT

class JudgeMent {
protected:
	JudgeMent();
public:
	virtual ~JudgeMent() = 0;
	virtual bool judge() = 0;
};

#endif // ___CLASS_JUDGE