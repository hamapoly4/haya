#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2), sonarSensor(PORT_3) { // <2>
  }

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  static unsigned char flag = false;
  int16_t dist;
  dist = sonarSensor.getDistance();
  
  if (-1 < dist && dist < 5)
  {
    flag = true;
    return;
  }
  
  if (flag == false)
  {
    printf("Haikyu!!\n");
    return;
  }
  const float Kp = 0.50;
  const float Ki = 0.015;
  const float Kd = 1.3;
  const int target = 69;
  const int bias = 0;
  static int old_diff = 0;
  static int i = 0;
  static int sum = 0;
  int diff = 0;
  int D_value = 0;
  int I_value = 0;
  int P_value = 0;
  int turn = 0;

  // P control
  diff = colorSensor.getBrightness() - target;
  P_value = Kp * diff;
  
  // I control
  sum += diff;
  I_value = sum * Ki;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + I_value + D_value;
  
  // RasPike run!!
  leftWheel.setPWM(pwm + turn);
  rightWheel.setPWM(pwm - turn);
  
  i++;
  if (i >= 10)
  {
    sum = 0;
    i = 0;
  }
  old_diff = diff;
}
