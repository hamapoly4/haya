#include "app.h" // <1>
#include "Tracer.h" // <2>
#include "Clock.h"  // <3>

using namespace ev3api;

Tracer tracer;  // <4>
Clock clock;

void tracer_task(intptr_t exinf) { // <1>
  tracer.run();
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  const uint32_t duration = 100*1000; // <2>

  sta_cyc(TRACER_CYC); // <4>
  
  while (!ev3_button_is_pressed(LEFT_BUTTON)) { // <1>
      clock.sleep(duration);   // <2>
  }

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}

