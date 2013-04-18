/*
 * RangeValue.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: Erich Styger
 */

#include "RangeValue.h"

void RangeValue::SetRange(SliderValT min, SliderValT max) {
  if (min>max) { // error? make sure that min<=max
    min = max;
  }
  m_min = min; m_max = max;
  // make sure m_val is in range
  if (m_val<m_min) {
    m_val = m_min;
  } else if (m_val>m_max) {
    m_val = m_max;
  }
};

void RangeValue::SetVal (SliderValT val) {
  if (val>m_max) {
    val = m_max;
  } else if (val<m_min) {
    val = m_min;
  }
  m_val = val;
}
