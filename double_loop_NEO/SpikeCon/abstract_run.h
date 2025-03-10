/*--------------------------------------------
 *	FILE NAME : abstract_run
 *	FILE TYPE : Header File
 *	AUTHOR    : Yuta Kondo
 * 	SUMMARY   : Abstract Class &
 *		    Sub Class
 *--------------------------------------------*/

#ifndef ___ABSTRACT_CLASS
#define ___ABSTRACT_CLASS	// インクルードカード

#include "Motor.h"

class Run {
protected:
	static ev3api::Motor LeftMotor;
	static ev3api::Motor RightMotor;
	
	int mfix_pwm;	// 既定のPWM値
	Run(int pwm);	// コンストラクタ
public:
	virtual ~Run() = 0; // 純粋仮想デストラクタ
	virtual void run() = 0;	// 純粋仮想関数
};

#endif // ___ABSTRACT_CLASS
