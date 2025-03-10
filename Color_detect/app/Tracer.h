#include "Motor.h"       // <1>
#include "GyroSensor.h"
#include "ev3api.h"
#include "HSVconv.h"

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer(HSVconv& hsvconv);
  bool run();       // <2>
  void terminate();

private:
  Motor leftWheel;
  Motor rightWheel;
  GyroSensor gyroSensor; // <3>
  HSVconv& mHSVconv;
  const int8_t mThreshold = 20;  // <4>
#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 35;
#endif

  rgb_raw_t rgb;
};
