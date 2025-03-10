#include "Tracer.h" // <1>
#include <ev3api_sensor.h>


static int  Blue_cnt = 0; 
static int left = 20 ,right = 20;
int left_cnt,right_cnt,sonar=0;
static int mode=0;
rgb_raw_t rgb;
char color,angle,dir,dir_con=0;
static int turn0_f = 0,turn1_f = 1,turn2_f = 1,turn3_f = 1;
static int t=0;


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


void Tracer::run()
{
  
  const float Kp = 0.79;
  const float Ki = 0.03;
  const float Kd = 2;
  const int target = 38;
  const int bias = 0;
  static int old_diff = 0;
  static int i = 0;
  static int sum = 0;
  int diff = 0;
  int D_value = 0;
  int I_value = 0;
  int P_value = 0;
  float turn = 0;
  colorSensor.getRawColor(rgb);
  color = color_set(rgb);
  int Blue_flg = 0;
    
  if(t%10 == 0)
    printf("red:%d green:%d blue:%d",rgb.r,rgb.g,rgb.b);
  
}

char color_set(rgb_raw_t & rgb)
{
    char c;
    if(rgb.r<30&&rgb.g<30&&rgb.b<30)      //Black
      c='K';
    else if(rgb.r>50&&rgb.g>50&&rgb.b>50) //White
      c='W';
    else if(rgb.r<20&&rgb.g<30&&rgb.b>40) //Blue
      c='B';
    else
      c='A';                             //Another
    return c;
}

  




