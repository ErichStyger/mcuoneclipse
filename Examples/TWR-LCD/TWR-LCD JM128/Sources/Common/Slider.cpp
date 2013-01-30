/*
 * Slider.cpp
 *
 *  Created on: 08.09.2011
 *      Author: Erich Styger
 */

#include "Platform.h"

#if PL_HAS_UI

#include "Slider.h"
extern "C" {
  #include "UI1.h"
  #include "Cour08n.h"
  #include "FDisp1.h"
  #include "UTIL1.h"
}

#define SLIDER_MIN_WIDTH   20 // minimal width of a slider control
#define SLIDER_MIN_HEIGHT  12 // minimal height of a slider control
#define SLIDER_H_BORDER     6 // minimal border left and right
#define KNOB_WIDTH    6 // width of knob in pixels
#define KNOB_HEIGHT  12 // height of knob in pixels
#define KNOB_H_BORDER 3 // minimal upper and lower knob border


typedef int32_t SliderValT;   // type for slider value
typedef uint16_t SliderStepT; // type for number of slider steps
struct WidgetArea {
  UI1_PixelDim x, y, w, h;
  WidgetArea(void)
    : x(0), y(0), w(0), h(0) {};
  WidgetArea(UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h)
    : x(x), y(y), w(w), h(h) {};
};

class RangeValue {
private:
  SliderValT m_val, m_min, m_max;
protected:
  RangeValue(void) : m_val(0), m_min(0), m_max(0) {} // default constructor
  inline void SetRange(SliderValT min, SliderValT max);
public:
  inline void SetVal (SliderValT val);
protected:
  SliderValT GetVal(void) { return m_val; }
  SliderValT GetMin(void) { return m_min; }
  SliderValT GetMax(void) { return m_max; }
};

inline void RangeValue::SetRange(SliderValT min, SliderValT max) {
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

inline void RangeValue::SetVal (SliderValT val) {
  if (val>m_max) {
    val = m_max;
  } else if (val<m_min) {
    val = m_min;
  }
  m_val = val;
}

class Widget {
  protected:
    WidgetArea m_area; // widget coordinates
    UI1_Window *m_window; // pointer to window
  protected:
    /* \todo Implement constructor
     * Widget(void)
     */
    Widget(void)
      : m_window(NULL), m_area(0,0,0,0) {};

    Widget(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h)
      : m_window(window),  m_area(x,y,w,h) {};
    inline void Init(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h);
    bool isInside(UI1_Coordinate* coord);
};

inline void Widget::Init(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h) {
  /* \todo Implement init method */
  // ensure minimal sizes:
  if (w<SLIDER_MIN_WIDTH) { w = SLIDER_MIN_WIDTH; }
  if (h<SLIDER_MIN_HEIGHT) { h = SLIDER_MIN_HEIGHT; }
  m_window = window;
  m_area.x = x;
  m_area.y = y;
  m_area.w = w;
  m_area.h = h;
}

bool Widget::isInside(UI1_Coordinate* coord) {
  // determine if coordinates are inside the widget
  return   coord->x >= m_area.x
        && coord->x <= m_area.x+m_area.w
        && coord->y >= m_area.y
        && coord->y <= m_area.y+m_area.h;
}

class SliderWidget : Widget, RangeValue {
  private:
    SliderStepT m_steps; // number of steps
    const unsigned char *m_label; // label text
  private:
    WidgetArea GetKnobPosition(void);
    void SetKnobPosition(WidgetArea *clickPos);
    SliderWidget& operator++(void);  // ++prefix
    SliderWidget operator++(int unused); // postfix++
    SliderWidget& operator--(void); // --prefix
    SliderWidget operator--(int unused); // postfix--
  public:
    SliderWidget(void) : m_steps(0), m_label(NULL) {}
    void Init(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h, SliderValT min, SliderValT max, SliderStepT steps, const unsigned char *label, SliderValT initValue);
    SliderValT GetValue(void) { return this->GetVal(); }
    void Paint(void);
    void OnClick(UI1_Coordinate* clickPos);
    void OnClickMove(UI1_Coordinate* clickPos);
};

void SliderWidget::Init(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h, SliderValT min, SliderValT max, SliderStepT steps, const unsigned char *label, SliderValT initValue) {
  Widget::Init(window, x, y, w, h);
  RangeValue::SetRange(min, max);
  if (steps==0) { // need to have at least one step!
    steps = 1;
  }
  m_steps = steps;
  m_label = label;
  SetVal(initValue);
}

SliderWidget& SliderWidget::operator++(void) { // ++prefix
  SetVal(GetVal()+((GetMax()-GetMin())/m_steps));
  return *this;
}

SliderWidget SliderWidget::operator++(int unused) { // postfix++
  (void)unused;
  SliderWidget result = *this;
  ++(*this); // call prefix SliderWidget::operator++();
  return result;
}

SliderWidget& SliderWidget::operator--(void) { // --prefix
  SetVal(GetVal()-((GetMax()-GetMin())/m_steps));
  return *this;
}

SliderWidget SliderWidget::operator--(int unused) { // postfix--
  (void)unused;
  SliderWidget result = *this;
  --(*this); // call prefix SliderWidget::operator--();
  return result;
}

WidgetArea SliderWidget::GetKnobPosition(void) {
  WidgetArea area;
  int i;

  area.w = KNOB_WIDTH; // with of knob in pixels, must be an even number!
  area.h = m_area.h-(KNOB_H_BORDER*2);
  if (area.h>KNOB_HEIGHT) {
    area.h = KNOB_HEIGHT; // max height
  }
  i = (int)((GetVal()-GetMin())/((GetMax()-GetMin())/m_steps)); // i is in range 0..m_steps
  area.x = SLIDER_H_BORDER+(UI1_PixelDim)(m_area.x+(m_area.w*i/m_steps));
  area.x -= area.w/2; // center know at pixel position
  if (area.x<m_area.x+SLIDER_H_BORDER) { // completely to the left: start at left side
    area.x = m_area.x+SLIDER_H_BORDER;
  } else if (area.x>m_area.x+m_area.w-SLIDER_H_BORDER-area.w) { // completely to the right: adjust position
    area.x = m_area.x+m_area.w-SLIDER_H_BORDER-area.w;
  }
  area.y = m_area.y + (m_area.h/2) - area.h/2; // center
  return area;
}

void SliderWidget::SetKnobPosition(WidgetArea *clickPos) {
  SliderValT delta;
  WidgetArea currKnob;

  currKnob = GetKnobPosition();
  delta = clickPos->x-currKnob.x; // get difference in pixels
  delta *= (GetMax()-GetMin())/m_area.w; // scale to value
  SetVal(GetVal()+delta);
}

void SliderWidget::Paint(void) {
  UI1_PixelDim x, y;
  WidgetArea knobArea;
  unsigned char buf[24];

  // background
  UI1_DrawFilledBox(m_window, m_area.x, m_area.y, m_area.w, m_area.h, UI1_COLOR_BRIGHT_BLUE);
  // slider horizontal line
  UI1_DrawHLine(m_window, m_area.x+SLIDER_H_BORDER, m_area.y+(m_area.h/2)-2, m_area.w-(SLIDER_H_BORDER*2), UI1_COLOR_BRIGHT_GREY);
  UI1_DrawVLine(m_window, m_area.x+SLIDER_H_BORDER, m_area.y+(m_area.h/2)-1, 3, UI1_COLOR_BRIGHT_GREY);
  UI1_DrawHLine(m_window, m_area.x+SLIDER_H_BORDER, m_area.y+(m_area.h/2)+2, m_area.w-(SLIDER_H_BORDER*2), UI1_COLOR_WHITE);
  UI1_DrawVLine(m_window, m_area.x+m_area.w-SLIDER_H_BORDER, m_area.y+(m_area.h/2)-1, 3, UI1_COLOR_WHITE);

  // draw slider knob
  knobArea = GetKnobPosition();
  UI1_DrawFilledBox(m_window, knobArea.x+1, knobArea.y+1, knobArea.w-2, knobArea.h-2, UI1_COLOR_BRIGHT_BLUE);
  UI1_DrawHLine(m_window, knobArea.x, knobArea.y, knobArea.w, UI1_COLOR_BLACK);
  UI1_DrawVLine(m_window, knobArea.x, knobArea.y+1, knobArea.h-2, UI1_COLOR_BLACK);
  UI1_DrawHLine(m_window, knobArea.x, knobArea.y+knobArea.h-1, knobArea.w, UI1_COLOR_WHITE);
  UI1_DrawVLine(m_window, knobArea.x+knobArea.w-1, knobArea.y+1, knobArea.h-2, UI1_COLOR_WHITE);
  // write label and value
  UTIL1_strcpy(buf, sizeof(buf), m_label);
  UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)": ");
  UTIL1_strcatNum32s(buf, sizeof(buf), GetVal());
  x = (UI1_PixelDim)(m_window->prop.x + m_area.x);
  y = (UI1_PixelDim)(m_window->prop.y + m_area.y);
  FDisp1_WriteString(buf, UI1_COLOR_BLACK, &x, &y, Cour08n_GetFont());
}

void SliderWidget::OnClick(UI1_Coordinate* clickPos) {
  if (this->isInside(clickPos)) {
    WidgetArea knobArea;

    knobArea = GetKnobPosition();
    if (clickPos->x < knobArea.x) {
      (*this)--;
      (*this).Paint();
    } else if (clickPos->x > knobArea.x+knobArea.w) {
      (*this)++;
      (*this).Paint();
    }
  }
}

void SliderWidget::OnClickMove(UI1_Coordinate* clickPos) {
  if (this->isInside(clickPos)) {
    WidgetArea knobArea;

    knobArea = GetKnobPosition();
    knobArea.x = clickPos->x;
    knobArea.y = clickPos->y;
    (*this).SetKnobPosition(&knobArea);
    (*this).Paint();
  }
}

static SliderWidget sliderP, sliderI, sliderD, sliderV, sliderPWM;

void SLIDER_CreateSliders(UI1_Window *window, UI1_PixelDim x, UI1_PixelDim y, UI1_PixelDim w, UI1_PixelDim h) {
  /* \todo Implement creation of widgets */
  sliderP.Init(window, x, y, w, (UI1_PixelDim)(h/6), 0, 10000, 1000, (const unsigned char*)"P", 360);
  sliderI.Init(window, x, y+(h/6), w, (UI1_PixelDim)(h/6), 0, 1000, 100, (const unsigned char*)"I", 125);
  sliderD.Init(window, x, y+2*(h/6), w, (UI1_PixelDim)(h/6), 0, 1000, 100, (const unsigned char*)"D", 150);
  sliderV.Init(window, x, y+3*(h/6), w, (UI1_PixelDim)(h/6), -30000, +30000, 1000, (const unsigned char*)"v", 0);
  sliderPWM.Init(window, x, y+4*(h/6), w, (UI1_PixelDim)(h/6), -100, 100, 200, (const unsigned char*)"PWM", 0);
}

void SLIDER_SliderW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)element;
  if (kind==UI1_EVENT_CLICK) {
    sliderP.OnClick((UI1_Coordinate*)data);
    sliderI.OnClick((UI1_Coordinate*)data);
    sliderD.OnClick((UI1_Coordinate*)data);
    sliderV.OnClick((UI1_Coordinate*)data);
    sliderPWM.OnClick((UI1_Coordinate*)data);
  } else if (kind==UI1_EVENT_CLICK_MOVE) {
    sliderP.OnClickMove((UI1_Coordinate*)data);
    sliderI.OnClickMove((UI1_Coordinate*)data);
    sliderD.OnClickMove((UI1_Coordinate*)data);
    sliderV.OnClickMove((UI1_Coordinate*)data);
    sliderPWM.OnClickMove((UI1_Coordinate*)data);
  } else if (kind==UI1_EVENT_PAINT) {
    sliderP.Paint();
    sliderI.Paint();
    sliderD.Paint();
    sliderV.Paint();
    sliderPWM.Paint();
  }
}

void SLIDER_GetCmdString(unsigned char *buf, size_t bufSize) {
  SliderValT val;
  static SliderValT oldPWM=-1, oldKp=-1, oldKi=-1, oldKd=-1, oldV=-1;

  for(;;) { // breaks
    val = sliderPWM.GetValue();
    if (val!=oldPWM) {
      UTIL1_strcpy(buf, bufSize, (const unsigned char*)"motor duty ");
      UTIL1_strcatNum32s(buf, bufSize, val);
      oldPWM = val;
      break;
    }
#if 1
    /* \todo Add other command providers as needed */
    val = sliderP.GetValue();
    if (val!=oldKp) {
      UTIL1_strcpy(buf, bufSize, (const unsigned char*)"pid kp ");
      UTIL1_strcatNum32s(buf, bufSize, val);
      oldKp = val;
      break;
    }
    val = sliderI.GetValue();
    if (val!=oldKi) {
      UTIL1_strcpy(buf, bufSize, (const unsigned char*)"pid ki ");
      UTIL1_strcatNum32s(buf, bufSize, val);
      oldKi = val;
      break;
    }
    val = sliderD.GetValue();
    if (val!=oldKd) {
      UTIL1_strcpy(buf, bufSize, (const unsigned char*)"pid kd ");
      UTIL1_strcatNum32s(buf, bufSize, val);
      oldKd = val;
      break;
    }
    val = sliderV.GetValue();
    if (val!=oldV) {
      UTIL1_strcpy(buf, bufSize, (const unsigned char*)"pid setpoint ");
      UTIL1_strcatNum32s(buf, bufSize, val);
      oldV = val;
      break;
    }
#endif
    buf[0] = '\0'; // empty response
    break;
  }
}

#endif /* PL_HAS_UI */
