/*-----------------------------------------
 * File Name : HSVconv.h
 * Author    : Yuta Kondo
 * Date      : 2024/08/06
 * Summary   : Convert RGB to HSV
 * ----------------------------------------*/
 
#include "HSVconv.h"
#include <stdio.h>

using namespace ev3api;

HSVconv::HSVconv(const ColorSensor& colorsensor)
	: mColorSensor(colorsensor)
{
	;
}

void HSVconv::calcHSV()
{
	setRGB();
	setMAX();
	setMIN();
	calcH();
	calcS();
	calcV();
}

void HSVconv::setRGB()
{
	mColorSensor.getRawColor(rgb);
}

void HSVconv::setMAX()
{
	max = rgb.r;
	if (max < rgb.g)
	{
		max = rgb.g;
	}
	
	if (max < rgb.b)
	{
		max = rgb.b;
	}
}

void HSVconv::setMIN()
{
	if (max == rgb.r)
	{
		min = rgb.g;
		if (min > rgb.b)
		{
			min = rgb.b;
		}
	}
	else if (max == rgb.g)
	{
		min = rgb.b;
		if (min > rgb.r)
		{
			min = rgb.r;
		}
	}
	else if (max == rgb.b)
	{
		min = rgb.r;
		if (min > rgb.g)
		{
			min = rgb.g;
		}
	}
}

void HSVconv::calcH()
{
	if (max == rgb.r)
	{
		h = 60 * ((rgb.g - rgb.b) / (max - min));
	}
	else if (max == rgb.g)
	{
		h = 60 * ((rgb.b - rgb.r) / (max - min)) + 120;
	}
	else if (max == rgb.b)
	{
		h = 60 * ((rgb.r - rgb.g) / (max - min)) + 240;
	}
	else if (rgb.r == rgb.g && rgb.g == rgb.b)
	{
		h = 0;
	}
	
	if (h < 0)
	{
		h += 360;
	}
}

void HSVconv::calcS()
{
	float f;
	f = (max - min) / max;
	s = f * 100;
}

void HSVconv::calcV()
{
	float f;
	f = max / 255;
	v = f * 100;
}

int HSVconv::getH() const
{
	return h;
}

int HSVconv::getS() const
{
	return s;
}

int HSVconv::getV() const
{
	return v;
}

int HSVconv::getR() const
{
	return rgb.r;
}

int HSVconv::getG() const
{
	return rgb.g;
}

int HSVconv::getB() const
{
	return rgb.b;
}

float HSVconv::getMAX() const
{
	return max;
}

float HSVconv::getMIN() const
{
	return min;
}
