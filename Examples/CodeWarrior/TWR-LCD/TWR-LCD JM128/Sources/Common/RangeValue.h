/*
 * RangeValue.h
 *
 *  Created on: Nov 24, 2012
 *      Author: Erich Styger
 */

#ifndef RANGEVALUE_H_
#define RANGEVALUE_H_

extern "C" {
  #include "PE_Types.h"
}

typedef int32_t SliderValT;   // type for slider value

class RangeValue {
private:
  SliderValT m_val, m_min, m_max;
protected:
  RangeValue(void) : m_val(0), m_min(0), m_max(0) {} // default constructor
  void SetRange(SliderValT min, SliderValT max);
public:
  void SetVal (SliderValT val);
protected:
  SliderValT GetVal(void) { return m_val; }
  SliderValT GetMin(void) { return m_min; }
  SliderValT GetMax(void) { return m_max; }
};



#endif /* RANGEVALUE_H_ */
