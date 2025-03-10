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

void Tracer::run() {
 
  rgb_raw_t rgb;
  char color;
  colorSensor.getRawColor(rgb);
  color = color_set(rgb);
  int H;// SIKiSOU
  int S;// SAIDO
  int V;// MEiDO
  

  if(rgb.r > rgb.g && rgb.r > rgb.b)
  {
    if(rgb.g > rgb.b)
    
      H = 60 * ((rgb.g - rgb.b) / (rgb.r - rgb.b));
      
    
    else if (rgb.b > rgb.g)
  
      H = 60 * ((rgb.b - rgb.g) / (rgb.r - rgb.g));
    
  }
  
  else if(rgb.g > rgb.r && rgb.g > rgb.b)
  {
    if(rgb.r > rgb.b)
    
      H = 60 * ((rgb.b - rgb.r) / (rgb.g - rgb.b) + 120);
      
    
    else if (rgb.r > rgb.r)
    
      H = 60 * ((rgb.b - rgb.r) / (rgb.g - rgb.r) + 120);
    
  }
  
  
  else if(rgb.b > rgb.g && rgb.b > rgb.r)
  {
    if(rgb.g > rgb.r)
    
      H = 60 * ((rgb.r - rgb.g) / (rgb.b - rgb.r) + 240);
      
    
    else if (rgb.b > rgb.g)
    
      H = 60 * ((rgb.r - rgb.g) / (rgb.b - rgb.g) + 240);
    
  }
  
  printf("%d\n",H);

}

char color_set(rgb_raw_t & rgb)
{
    char c;
    if(rgb.r<10&&rgb.g<10&&rgb.b<10)      //Black
      c='K';
    else if(rgb.r>50&&rgb.g>50&&rgb.b>50) //White
      c='W';
    else if(rgb.r<20&&rgb.g<20&&rgb.b>25) //Blue
      c='B';
    else
      c='A';                             //Another
    return c;
}
