#include <stdio.h>
#include <math.h>

double mygamma   = 2.4; // Correction factor
int   max_in  = 255, // Top end of INPUT range
      max_out = 255; // Top end of OUTPUT range
 
int main() {
  printf("const uint8_t gamma8[] = {");
  for(int i=0; i<=max_in; i++) {
    if(i > 0) printf(",");
    if((i & 15) == 0) printf("\n  ");
    
    printf("%3d",(int)(pow((double)i / (double)max_in, mygamma) * max_out + 0.5));
  }
  printf("\n };\n");
  return 0;
}
