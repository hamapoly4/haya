#include "Tracer.h" // <1>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}


  float Tracer::calc_prop_value(){
  const float Kp = 0.8;
  const int target = 35;
  const int bias = 5;

    int diff = colorSensor.getBrightness() - target;
    return (Kp * diff + bias);
  }

void Tracer::run() {
  const float Kp = 0.83;
  const int target = 10;
  const int bias = 0;

  msg_f("runnning...", 1);
  int diff = colorSensor.getBrightness() - target;
  float turn = Kp * diff + bias;
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm - turn);
}
