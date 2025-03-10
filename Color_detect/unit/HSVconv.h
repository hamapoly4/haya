/*-----------------------------------------
 * File Name : HSVconv.h
 * Author    : Yuta Kondo
 * Date      : 2024/08/06
 * Summary   : Convert RGB to HSV
 * ----------------------------------------*/
#ifndef HSVCONV_H_
#define HSVCONV_H_
 
#include "ColorSensor.h"

class HSVconv {
private:
	const ev3api::ColorSensor& mColorSensor;
	rgb_raw_t rgb;
	float max;
	float min;
	int h;
	int s;
	int v;

public:
	HSVconv(const ev3api::ColorSensor& colorsensor);
	void calcHSV();
	void setRGB();
	void setMAX();
	void setMIN();
	void calcH();
	void calcS();
	void calcV();
	
	int getH() const;
	int getS() const;
	int getV() const;
	
	int getR() const;
	int getG() const;
	int getB() const;
	
	float getMAX() const;
	float getMIN() const;
};

#endif
