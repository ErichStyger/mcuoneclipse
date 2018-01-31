#include "Arduino.h"

class iSin
{
  public:
      int convert(long x);
  private:
      uint8_t isinTable8[91] = { 
          0, 4, 9, 13, 18, 22, 27, 31, 35, 40, 44, 
          49, 53, 57, 62, 66, 70, 75, 79, 83, 87, 
          91, 96, 100, 104, 108, 112, 116, 120, 124, 128, 
          131, 135, 139, 143, 146, 150, 153, 157, 160, 164, 
          167, 171, 174, 177, 180, 183, 186, 190, 192, 195, 
          198, 201, 204, 206, 209, 211, 214, 216, 219, 221, 
          223, 225, 227, 229, 231, 233, 235, 236, 238, 240, 
          241, 243, 244, 245, 246, 247, 248, 249, 250, 251, 
          252, 253, 253, 254, 254, 254, 255, 255, 255, 255
      };
};

int iSin::convert(long x)
{
    boolean pos = true;  // positive - keeps an eye on the sign.
    if (x < 0) 
    {
        x = -x;
        pos = !pos;  
    }  
    if (x >= 360) x %= 360;   
    if (x > 180) 
    {
        x -= 180;
        pos = !pos;
    }
    if (x > 90) x = 180 - x;
    if (pos) return isinTable8[x]/2 ;
    return -isinTable8[x]/2 ;
}
