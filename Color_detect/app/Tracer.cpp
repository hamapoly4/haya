#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer(HSVconv& hsvconv):
  leftWheel(PORT_C), rightWheel(PORT_B), gyroSensor(PORT_4), mHSVconv(hsvconv) { // <2>
}

bool Tracer::run() {
  
  const float Kp = 1.5;
  const float Kd = 3;
  const int target = 0;
  static int old_diff = 0;
  int diff = 0;
  int D_value = 0;
  int P_value = 0;
  int turn = 0;
  /* 左右のモータの角位置に関する変数 */
  int32_t leftwheel_count;
  int32_t rightwheel_count;
  
  int angle;

  // P control
  angle = gyroSensor.getAngle();
  diff = angle - target;
  P_value = Kp * diff;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + D_value;

  mHSVconv.calcHSV();
  printf("h : %d\n", mHSVconv.getH());
  printf("s : %d\n", mHSVconv.getS());
  printf("v : %d\n\n", mHSVconv.getV());

  leftwheel_count = leftWheel.getCount();     // 左モータの角位置を取得
  rightwheel_count = rightWheel.getCount();   // 右モータの角位置を取得
  if (leftwheel_count >= 90 && rightwheel_count >= 90)
  {
    printf("leftwheel_count : %d\n", leftwheel_count);    //
    printf("rightwheel_count : %d\n", rightwheel_count);  // 角位置の観測値
    
    return true;
  }

  // RasPike run!!
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);

  old_diff = diff;

  return false;
}

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
