#include "PT1000.h"

#include "AD1.h"

#define PT_RESISTOR_OHM_VALUE 1000 /* the PT1000 value */
#define PT_RESISTOR_OHM_OFFSET 200 /* the offset resistor */

#define PT1000_MIN_TEMP -25
#define PT1000_MAX_TEMP 100
#define PT1000_TABLE_OFFSET 1  /* 1 degree celsius offset between table entries */
#define PT1000_TABLE_SIZE  (PT1000_MAX_TEMP-PT1000_MIN_TEMP+1)
static const word PT1000_cento[PT1000_TABLE_SIZE] = { /* deci-Ohm (51.3 Ohm ==> 513 */ 
    /* -25°C */ 9019,
    /* -24°C */ 9059,
    /* -23°C */ 9098,
    /* -22°C */ 9137,
    /* -21°C */ 9177,
    /* -20°C */ 9216,
    /* -19°C */ 9255,
    /* -18°C */ 9295,
    /* -17°C */ 9334,
    /* -16°C */ 9373,
    /* -15°C */ 9412,
    /* -14°C */ 9452,
    /* -13°C */ 9491,
    /* -12°C */ 9530,
    /* -11°C */ 9569,
    /* -10°C */ 9609,
    /* -9°C */ 9648,
    /* -8°C */ 9687,
    /* -7°C */ 9726,
    /* -6°C */ 9765,
    /* -5°C */ 9804,
    /* -4°C */ 9844,
    /* -3°C */ 9883,
    /* -2°C */ 9922,
    /* -1°C */ 9961,
    /* 0°C */ 10000,
    /* 1°C */ 10039,
    /* 2°C */ 10078,
    /* 3°C */ 10117,
    /* 4°C */ 10156,
    /* 5°C */ 10195,
    /* 6°C */ 10234,
    /* 7°C */ 10273,
    /* 8°C */ 10312,
    /* 9°C */ 10351,
    /* 10°C */ 10390,
    /* 11°C */ 10429,
    /* 12°C */ 10468,
    /* 13°C */ 10507,
    /* 14°C */ 10546,
    /* 15°C */ 10585,
    /* 16°C */ 10624,
    /* 17°C */ 10663,
    /* 18°C */ 10702,
    /* 19°C */ 10740,
    /* 20°C */ 10779,
    /* 21°C */ 10818,
    /* 22°C */ 10857,
    /* 23°C */ 10896,
    /* 24°C */ 10935,
    /* 25°C */ 10973,
    /* 26°C */ 11012,
    /* 27°C */ 11051,
    /* 28°C */ 11090,
    /* 29°C */ 11128,
    /* 30°C */ 11167,
    /* 31°C */ 11206,
    /* 32°C */ 11245,
    /* 33°C */ 11283,
    /* 34°C */ 11322,
    /* 35°C */ 11361,
    /* 36°C */ 11399,
    /* 37°C */ 11438,
    /* 38°C */ 11477,
    /* 39°C */ 11515,
    /* 40°C */ 11554,
    /* 41°C */ 11593,
    /* 42°C */ 11631,
    /* 43°C */ 11670,
    /* 44°C */ 11708,
    /* 45°C */ 11747,
    /* 46°C */ 11785,
    /* 47°C */ 11824,
    /* 48°C */ 11862,
    /* 49°C */ 11901,
    /* 50°C */ 11940,
    /* 51°C */ 11978,
    /* 52°C */ 12016,
    /* 53°C */ 12055,
    /* 54°C */ 12093,
    /* 55°C */ 12132,
    /* 56°C */ 12170,
    /* 57°C */ 12209,
    /* 58°C */ 12247,
    /* 59°C */ 12286,
    /* 60°C */ 12324,
    /* 61°C */ 12362,
    /* 62°C */ 12401,
    /* 63°C */ 12439,
    /* 64°C */ 12477,
    /* 65°C */ 12516,
    /* 66°C */ 12554,
    /* 67°C */ 12592,
    /* 68°C */ 12631,
    /* 69°C */ 12669,
    /* 70°C */ 12707,
    /* 71°C */ 12745,
    /* 72°C */ 12784,
    /* 73°C */ 12822,
    /* 74°C */ 12860,
    /* 75°C */ 12898,
    /* 76°C */ 12937,
    /* 77°C */ 12975,
    /* 78°C */ 13013,
    /* 79°C */ 13051,
    /* 80°C */ 13089,
    /* 81°C */ 13127,
    /* 82°C */ 13166,
    /* 83°C */ 13204,
    /* 84°C */ 13242,
    /* 85°C */ 13280,
    /* 86°C */ 13318,
    /* 87°C */ 13356,
    /* 88°C */ 13394,
    /* 89°C */ 13432,
    /* 90°C */ 13470,
    /* 91°C */ 13508,
    /* 92°C */ 13546,
    /* 93°C */ 13584,
    /* 94°C */ 13622,
    /* 95°C */ 13660,
    /* 96°C */ 13698,
    /* 97°C */ 13736,
    /* 98°C */ 13774,
    /* 99°C */ 13812,
    /* 100°C */ 13850
};

/*! \brief Returns the resistance in Ohms */
word PT_GetResistance(void) {
  word value;
  long tmp;
  /* http://www.cq.cx/interface.pl#1 */
  (void)AD1_Measure(TRUE);
  (void)AD1_GetValue16(&value);
  tmp = value*(long)PT_RESISTOR_OHM_OFFSET;
  value = (word)(tmp/(0xffff-value));
  //value /= 0xffff/PT_RESISTOR_OHM_VALUE;
  return value;
}

/*! \brief Returns the temperature in deci-Celsius (e.g. 126 for 12.6 degree celsius) */
short PT_GetTemperatureCelsiusD(void) {
  word ad_value;
  word a, b, c;
  short temp;
  
  ad_value = PT_GetResistance();
  ad_value *= 10;
  if (ad_value < PT1000_cento[0]) {
    ad_value = PT1000_cento[0];
  } else if (ad_value > PT1000_cento[PT1000_TABLE_SIZE-1]) {
    ad_value = PT1000_cento[PT1000_TABLE_SIZE-1];
  }
  a = 0;
  b = PT1000_TABLE_SIZE-1;
  c = (a+b)/2;
  do { /* binary search */
    if (PT1000_cento[c]>ad_value) {
      b = c;
    } else {
      a = c;
    }
    c = (a+b)/2;
  } while(PT1000_cento[c]!=ad_value && a!=c);
  /* interpolate */
  temp = ((signed)c+PT1000_MIN_TEMP)*10;
  if (ad_value > PT1000_cento[c]) {
    temp += ((ad_value-PT1000_cento[c])*10)/(PT1000_cento[c+1]-PT1000_cento[c]);
  } else if (ad_value < PT1000_cento[c]) {
    temp -= ((PT1000_cento[c]-ad_value)*10)/(PT1000_cento[c]-PT1000_cento[c-1]);
  }
  return temp;
}
