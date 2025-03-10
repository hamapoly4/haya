#include "app.h" // <1>
#include "Tracer.h" // <2>
#include "Clock.h"  // <3>

using namespace ev3api;

Tracer tracer;  // <4>
Clock clock;    // <5>

pup_device_t *colorC;

pup_color_rgb_t pup_color_sensor_rgb(pup_device_t *pdev);

typedf struct{
   uint16_t h;
   uint8_t s;
   uint8_t v;
  }pup_color_hsv_t;

typedef pbio_color_hsv_t pup_color_hsv_t;

pup_color_hsv_t pup_color_sensor_color(pup_device_t *pdeb, bool surface);

pup_color_hsv_t cd_color_map_defaultl[] = {
  
    { PBIO_COLOR_HUE_RED, 100, 100},
    { PBIO_COLOR_HUE_GREEN, 100, 100},
    { PBIO_COLOR_HUE_BULE, 100, 100 },
    {0, 0, 100},//white
    {0, 0, 0},//none
    
};
    
typedef enum{
  PBIO_COLOR_HUE_RED = 0,
  PBIO_COLOR_HUE_GREEN = 120,
  PBIO_COLOR_HUE_BULE = 240,
} pbio_color_hue_t;

pup_color_hsv_t hsv = pup_color_sensor_color{colorC, ture);
  

void tracer_task(intptr_t exinf) { // <1>
  tracer.run(); // <2>
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  const uint32_t duration = 100*1000; // <2>
  
  colorC = pup_color_sensor_get_device(PBIO_PORT_ID_C);
  
  if(hsb.h == PBIO_COLOR_HUE_BULE){
  leftWheel.setPWM(pwm + turn + 5);
  rightWheel.setPWM(pwm - turn);
  };


  tracer.init(); // <3>
  sta_cyc(TRACER_CYC); // <4>
  
  while (!ev3_button_is_pressed(LEFT_BUTTON)) { // <1>
      clock.sleep(duration);   // <2>
  }

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}

