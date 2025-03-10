#include "app.h" // <1>
#include "Tracer.h" // <2>
#include "HSVconv.h"

#include <stdio.h>

using namespace ev3api;

ColorSensor gcolorSensor(PORT_2);
HSVconv gHSVconv(gcolorSensor);
Tracer tracer(gHSVconv);  // <4>

void tracer_task(intptr_t exinf) { // <1>
  if (tracer.run() == true)
  {
    wup_tsk(MAIN_TASK);
  }
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>

  sta_cyc(TRACER_CYC); // <4>
  
  slp_tsk();

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}
