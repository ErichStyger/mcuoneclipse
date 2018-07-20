//--------------------------------------------------------------------------
// Uncanny eyes for PJRC Teensy 3.1 with Adafruit 1.5" OLED (product #1431)
// or 1.44" TFT LCD (#2088).  This uses Teensy-3.1-specific features and
// WILL NOT work on normal Arduino or other boards!  Use 72 MHz (Optimized)
// board speed -- OLED does not work at 96 MHz.
//
// Adafruit invests time and resources providing this open source code,
// please support Adafruit and open-source hardware by purchasing products
// from Adafruit!
//
// Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
// MIT license.  SPI FIFO insight from Paul Stoffregen's ILI9341_t3 library.
// Inspired by David Boccabella's (Marcwolf) hybrid servo/OLED eye concept.
// Ported by Erich Styger (https://mcuoneclipse.com/) to Processor Expert and Kinetis
//--------------------------------------------------------------------------

#include <stdlib.h> /* for rand() */
#include <stdint.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#include "GDisp1.h"  // Display interface

// If using a SINGLE EYE, you might want this next line enabled, which
// uses a simpler "football-shaped" eye that's left/right symmetrical.
// Default shape includes the caruncle, creating distinct left/right eyes.
//#define SYMMETRICAL_EYELID

// Enable ONE of these #includes -- HUGE graphics tables for various eyes:
#include "defaultEye.h"        // Standard human-ish hazel eye
//#include "logo.h"
//#include "noScleraEye.h"       // Large iris, no sclera
//#include "dragonEye.h"         // Slit pupil fiery dragon/demon eye
//#include "goatEye.h"           // Horizontal pupil goat/Krampus eye
//#include "newtEye.h"

// Then tweak settings below, e.g. change IRIS_MIN/MAX or disable TRACKING.
#if 1
// INPUT CONFIG (for eye motion -- enable or comment out as needed) --------
//#define JOYSTICK_X_PIN A0 // Analog pin for eye horiz pos (else auto)
//#define JOYSTICK_Y_PIN A1 // Analog pin for eye vert position (")
//#define JOYSTICK_X_FLIP   // If set, reverse stick X axis
//#define JOYSTICK_Y_FLIP   // If set, reverse stick Y axis
#define TRACKING          // If enabled, eyelid tracks pupil
#define EYES_USE_INTERACTIVE_IRIS    0  /* 1: scale iris depending on value (e.g. ambilight level); 0: do not scale iris */
#define IRIS_SMOOTH   1    // If enabled, filter input from GetIrisValue()
#define IRIS_MIN      120 // Clip lower analogRead() range from GetIrisValue()
#define IRIS_MAX      720 // Clip upper "
//#define WINK_L_PIN      0 // Pin for LEFT eye wink button
//#define BLINK_PIN       1 // Pin for blink button (BOTH eyes)
//#define WINK_R_PIN      2 // Pin for RIGHT eye wink button
#define AUTOBLINK        1 // If enabled, eyes blink autonomously
#endif

typedef struct {
	uint16_t width, height;
	const uint16_t *image;
} EyeImageDesc;
typedef struct {
	uint16_t width, height;
	const uint8_t *upper, *lower;
} EyeScreenDesc;


typedef struct {
	EyeImageDesc sclera;
	EyeScreenDesc screen;
	EyeImageDesc irisMap;
	EyeImageDesc iris;
} EyeDesc;

static const EyeDesc eyes[] = {
  {
	.sclera.width = SCLERA_WIDTH, .sclera.height=SCLERA_HEIGHT, .sclera.image = &sclera[0][0],
    .screen.width = SCREEN_WIDTH, .screen.height = SCREEN_HEIGHT, .screen.upper = &upper[0][0], .screen.lower = &lower[0][0],
	.irisMap.width = IRIS_MAP_WIDTH, .irisMap.height=IRIS_MAP_HEIGHT, .irisMap.image = &iris[0][0],
	.iris.width = IRIS_WIDTH, .iris.height=IRIS_HEIGHT, .iris.image = &polar[0][0],
  }
};

// DISPLAY HARDWARE CONFIG -------------------------------------------------
#if EYES_USE_INTERACTIVE_IRIS
uint16_t GetAmbilightValue(void) {
  /* try to keep it between IRIS_MIN and IRIS_MAX */
  return 512;  /* // e.g. dial/photocell reading */
}
#endif

bool Blink(void) {
  return FALSE; /* state of a blink signal/pin */
}

bool Wink(int eye) {
  return FALSE;
}

static int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
  return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

static int32_t constrain(int32_t val, int32_t min, int32_t max) {
  if (val<min) {
    return min;
  } else if (val>max) {
    return max;
  }
  return val;
}

int32_t random_between(int32_t min, int32_t max) {
  return rand()%(max-min+1)+min;
}

static int32_t random(int32_t min, int32_t max) {
  int32_t val;

  val = random_between(min, max);
  val = constrain(val, min, max);
  return val;
}

static uint32_t micros(void) {
  extern uint32_t msCntr;
  return msCntr*1000;
}

// Probably don't need to edit any config below this line, -----------------
// unless building a single-eye project (pendant, etc.), in which case one
// of the two elements in the eye[] array further down can be commented out.

// Eye blinks are a tiny 3-state machine.  Per-eye allows winks + blinks.
#define NOBLINK 0     // Not currently engaged in a blink
#define ENBLINK 1     // Eyelid is currently closing
#define DEBLINK 2     // Eyelid is currently opening
typedef struct {
  uint8_t  state;     // NOBLINK/ENBLINK/DEBLINK
  int32_t  duration;  // Duration of blink state (micros)
  uint32_t startTime; // Time (micros) of last state change
} eyeBlink;

struct {
  uint16_t posOffsetX, posOffsetY;
  eyeBlink    blink;   // Current blink state
} eye[] = { // OK to comment out one of these for single-eye display:
  //displayType(SELECT_L_PIN,DISPLAY_DC,0),SELECT_L_PIN,{WINK_L_PIN,NOBLINK},
    {.posOffsetX=250, .posOffsetY=40, {NOBLINK, 0, 0}}, /* first eye */
    {.posOffsetX=80,  .posOffsetY=40, {NOBLINK, 0, 0}}  /* second eye */
};
#define NUM_EYES (sizeof(eye) / sizeof(eye[0]))

// EYE-RENDERING FUNCTION --------------------------------------------------
void drawEye( // Renders one eye.  Inputs must be pre-clipped & valid.
  uint8_t  e,       // Eye array index; 0 or 1 for left/right
  uint32_t iScale,  // Scale factor for iris
  uint8_t  scleraX, // First pixel X offset into sclera image
  uint8_t  scleraY, // First pixel Y offset into sclera image
  uint8_t  uT,      // Upper eyelid threshold value
  uint8_t  lT) {    // Lower eyelid threshold value

  uint8_t  screenX, screenY, scleraXsave;
  int16_t  irisX, irisY;
  uint16_t p, a;
  uint32_t d;
  const EyeDesc *currEye = &eyes[0];

  scleraXsave = scleraX; // Save initial X value to reset on each line
  irisY       = scleraY - (currEye->sclera.height - currEye->iris.height) / 2;
  for(screenY=0; screenY<currEye->screen.height; screenY++, scleraY++, irisY++) {
    scleraX = scleraXsave;
    irisX   = scleraXsave - (currEye->sclera.width - currEye->iris.width) / 2;
    for(screenX=0; screenX<currEye->screen.width; screenX++, scleraX++, irisX++) {
      bool eyeLidCovered = FALSE;
      if (e==0) {
		  if ((currEye->screen.lower[screenY*currEye->screen.width + screenX] <= lT) || (currEye->screen.upper[screenY*currEye->screen.width + screenX] <= uT)) {
			  p = 0;
			  eyeLidCovered = TRUE;
		  }
      } else if (e==1) {
    	  if ((currEye->screen.lower[screenY*currEye->screen.width + currEye->screen.width-screenX-1] <= lT) || (currEye->screen.upper[screenY*currEye->screen.width + currEye->screen.width-screenX-1] <= uT)) {
    		  p = 0;
    		  eyeLidCovered = TRUE;
    	  }
      }
#if 0
      if((lower[screenY][screenX] <= lT) || (upper[screenY][screenX] <= uT))
      {             // Covered by eyelid
        p = 0;
      } else
#endif
    if (!eyeLidCovered) {
    	  if((irisY < 0) || (irisY >= currEye->iris.height) || (irisX < 0) || (irisX >= currEye->iris.width)) { // In sclera
			p = currEye->sclera.image[scleraY*currEye->sclera.width + scleraX];
		  } else {                                          // Maybe iris...
			p = polar[irisY][irisX];                        // Polar angle/dist
			d = (iScale * (p & 0x7F)) / 128;                // Distance (Y)
			if(d < currEye->irisMap.height) {                       // Within iris area
			  a = (currEye->sclera.width * (p >> 7)) / 512;        // Angle (X)
			  p = iris[d][a];                               // Pixel = iris
			} else {                                        // Not in iris
			  p = currEye->sclera.image[scleraY*currEye->sclera.width + scleraX];                 // Pixel = sclera
			}
		  }
		}
       GDisp1_PutPixel(screenX+eye[e].posOffsetX, screenY+eye[e].posOffsetY, p);
    }
  }
}

// EYE ANIMATION -----------------------------------------------------------
const uint8_t ease[] = { // Ease in/out curve for eye movements 3*t^2-2*t^3
    0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  2,  2,  2,  3,   // T
    3,  3,  4,  4,  4,  5,  5,  6,  6,  7,  7,  8,  9,  9, 10, 10,   // h
   11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 18, 19, 20, 21, 22, 23,   // x
   24, 25, 26, 27, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 39,   // 2
   40, 41, 42, 44, 45, 46, 47, 48, 50, 51, 52, 53, 54, 56, 57, 58,   // A
   60, 61, 62, 63, 65, 66, 67, 69, 70, 72, 73, 74, 76, 77, 78, 80,   // l
   81, 83, 84, 85, 87, 88, 90, 91, 93, 94, 96, 97, 98,100,101,103,   // e
  104,106,107,109,110,112,113,115,116,118,119,121,122,124,125,127,   // c
  128,130,131,133,134,136,137,139,140,142,143,145,146,148,149,151,   // J
  152,154,155,157,158,159,161,162,164,165,167,168,170,171,172,174,   // a
  175,177,178,179,181,182,183,185,186,188,189,190,192,193,194,195,   // c
  197,198,199,201,202,203,204,205,207,208,209,210,211,213,214,215,   // o
  216,217,218,219,220,221,222,224,225,226,227,228,228,229,230,231,   // b
  232,233,234,235,236,237,237,238,239,240,240,241,242,243,243,244,   // s
  245,245,246,246,247,248,248,249,249,250,250,251,251,251,252,252,   // o
  252,253,253,253,254,254,254,254,254,255,255,255,255,255,255,255 }; // n

#if AUTOBLINK
static uint32_t timeOfLastBlink = 0L, timeToNextBlink = 0L;
#endif

void frame( // Process motion for a single frame of left or right eye
  uint16_t        iScale) {     // Iris scale (0-1023) passed in
//  static uint32_t frames   = 0; // Used in frame rate calculation
  static uint8_t  eyeIndex = 0; // eye[] array counter
  int16_t         eyeX, eyeY;
  uint32_t        t = micros(); // Time at start of function

  //Serial.println((++frames * 1000) / millis()); // Show frame rate
  // X/Y movement
#if defined(JOYSTICK_X_PIN) && (JOYSTICK_X_PIN >= 0) && \
    defined(JOYSTICK_Y_PIN) && (JOYSTICK_Y_PIN >= 0)

  // Read X/Y from joystick, constrain to circle
  int16_t dx, dy;
  int32_t d;
  eyeX = analogRead(JOYSTICK_X_PIN); // Raw (unclipped) X/Y reading
  eyeY = analogRead(JOYSTICK_Y_PIN);
#ifdef JOYSTICK_X_FLIP
  eyeX = 1023 - eyeX;
#endif
#ifdef JOYSTICK_Y_FLIP
  eyeY = 1023 - eyeY;
#endif
  dx = (eyeX * 2) - 1023; // A/D exact center is at 511.5.  Scale coords
  dy = (eyeY * 2) - 1023; // X2 so range is -1023 to +1023 w/center at 0.
  if((d = (dx * dx + dy * dy)) > (1023 * 1023)) { // Outside circle
    d    = (int32_t)sqrt((float)d);               // Distance from center
    eyeX = ((dx * 1023 / d) + 1023) / 2;          // Clip to circle edge,
    eyeY = ((dy * 1023 / d) + 1023) / 2;          // scale back to 0-1023
  }

#else // Autonomous X/Y eye motion
      // Periodically initiates motion to a new random point, random speed,
      // holds there for random period until next motion.

  static bool  eyeInMotion      = FALSE;
  static int16_t  eyeOldX=512, eyeOldY=512, eyeNewX=512, eyeNewY=512;
  static uint32_t eyeMoveStartTime = 0L;
  static int32_t  eyeMoveDuration  = 0L;

  int32_t dt = t - eyeMoveStartTime;      // uS elapsed since last eye event
  if(eyeInMotion) {                       // Currently moving?
    if(dt >= eyeMoveDuration) {           // Time up?  Destination reached.
      eyeInMotion      = FALSE;           // Stop moving
      eyeMoveDuration  = random(0, 3000000); // 0-3 sec stop
      eyeMoveStartTime = t;               // Save initial time of stop
      eyeX = eyeOldX = eyeNewX;           // Save position
      eyeY = eyeOldY = eyeNewY;
    } else { // Move time's not yet fully elapsed -- interpolate position
      int16_t e = ease[255 * dt / eyeMoveDuration] + 1;   // Ease curve
      eyeX = eyeOldX + (((eyeNewX - eyeOldX) * e) / 256); // Interp X
      eyeY = eyeOldY + (((eyeNewY - eyeOldY) * e) / 256); // and Y
    }
  } else {                                // Eye stopped
    eyeX = eyeOldX;
    eyeY = eyeOldY;
    if(dt > eyeMoveDuration) {            // Time up?  Begin new move.
      int16_t  dx, dy;
      uint32_t d;
      do {                                // Pick new dest in circle
        eyeNewX = random(0, 1024);
        eyeNewY = random(0, 1024);
        dx      = (eyeNewX * 2) - 1023;
        dy      = (eyeNewY * 2) - 1023;
      } while((d = (dx * dx + dy * dy)) > (1023 * 1023)); // Keep trying
      eyeMoveDuration  = random(72000, 144000); // ~1/14 - ~1/7 sec
      eyeMoveStartTime = t;               // Save initial time of move
      eyeInMotion      = TRUE;            // Start move on next frame
    }
  }
#endif // JOYSTICK_X_PIN etc.
  // Blinking
#if AUTOBLINK
  // Similar to the autonomous eye movement above -- blink start times
  // and durations are random (within ranges).
  if((t - timeOfLastBlink) >= timeToNextBlink) { // Start new blink?
    timeOfLastBlink = t;
    uint32_t blinkDuration = random(36000, 72000); // ~1/28 - ~1/14 sec
    // Set up durations for both eyes (if not already winking)
    for(uint8_t e=0; e<NUM_EYES; e++) {
      if(eye[e].blink.state == NOBLINK) {
        eye[e].blink.state     = ENBLINK;
        eye[e].blink.startTime = t;
        eye[e].blink.duration  = blinkDuration;
      }
    }
    timeToNextBlink = blinkDuration * 3 + random(0, 4000000);
  }
#endif
  if(eye[eyeIndex].blink.state) { // Eye currently blinking?
    // Check if current blink state time has elapsed
    if((t - eye[eyeIndex].blink.startTime) >= eye[eyeIndex].blink.duration) {
      // Yes -- increment blink state, unless...
      if((eye[eyeIndex].blink.state == ENBLINK)   // Enblinking and...
          && (Blink() || Wink(eyeIndex))
        //&&((digitalRead(BLINK_PIN) == LOW) ||         // blink or wink held...
        //  digitalRead(eye[eyeIndex].blink.pin) == LOW)
          ) {
        // Don't advance state yet -- eye is held closed instead
      } else { // No buttons, or other state...
        if(++eye[eyeIndex].blink.state > DEBLINK) { // Deblinking finished?
          eye[eyeIndex].blink.state = NOBLINK;      // No longer blinking
        } else { // Advancing from ENBLINK to DEBLINK mode
          eye[eyeIndex].blink.duration *= 2; // DEBLINK is 1/2 ENBLINK speed
          eye[eyeIndex].blink.startTime = t;
        }
      }
    }
  } else { // Not currently blinking...check buttons!
    if (Blink()) {
    //if (digitalRead(BLINK_PIN) == LOW) {
      // Manually-initiated blinks have random durations like auto-blink
      uint32_t blinkDuration = random(36000, 72000);
      for(uint8_t e=0; e<NUM_EYES; e++) {
        if(eye[e].blink.state == NOBLINK) {
          eye[e].blink.state     = ENBLINK;
          eye[e].blink.startTime = t;
          eye[e].blink.duration  = blinkDuration;
        }
      }
    } else if (Wink(eyeIndex)) {
    //} else if(digitalRead(eye[eyeIndex].blink.pin) == LOW) { // Wink!
      eye[eyeIndex].blink.state     = ENBLINK;
      eye[eyeIndex].blink.startTime = t;
      eye[eyeIndex].blink.duration  = random(45000, 90000);
    }
  }
  // Process motion, blinking and iris scale into renderable values

  // Iris scaling: remap from 0-1023 input to iris map height pixel units
  iScale = ((IRIS_MAP_HEIGHT + 1) * 1024) /
           (1024 - (iScale * (IRIS_MAP_HEIGHT - 1) / IRIS_MAP_HEIGHT));

  // Scale eye X/Y positions (0-1023) to pixel units used by drawEye()
  #define SCLERA_BORDER  128  /* outside border of the sclera which is not used for eye coordingates */
  eyeX = map(eyeX, 0, 1023, 0, SCLERA_WIDTH  - SCLERA_BORDER);
  eyeY = map(eyeY, 0, 1023, 0, SCLERA_HEIGHT - SCLERA_BORDER);
#if 0
  if(eyeIndex == 1) {
	  eyeX = (SCLERA_WIDTH - SCLERA_BORDER) - eyeX; // Mirrored display
  }
#endif
  // Horizontal position is offset so that eyes are very slightly crossed
  // to appear fixated (converged) at a conversational distance.  Number
  // here was extracted from my posterior and not mathematically based.
  // I suppose one could get all clever with a range sensor, but for now...
  if(NUM_EYES > 1) {
	  eyeX += 4;
  }
  if(eyeX > (SCLERA_WIDTH - SCLERA_BORDER)) {
	  eyeX = (SCLERA_WIDTH - SCLERA_BORDER);
  }

  // Eyelids are rendered using a brightness threshold image.  This same
  // map can be used to simplify another problem: making the upper eyelid
  // track the pupil (eyes tend to open only as much as needed -- e.g. look
  // down and the upper eyelid drops).  Just sample a point in the upper
  // lid map slightly above the pupil to determine the rendering threshold.
  static uint8_t uThreshold = 128;
  uint8_t        lThreshold, n;
#ifdef TRACKING
  int16_t sampleX = SCLERA_WIDTH  / 2 - (eyeX / 2), // Reduce X influence
          sampleY = SCLERA_HEIGHT / 2 - (eyeY + IRIS_HEIGHT / 4);
  // Eyelid is slightly asymmetrical, so two readings are taken, averaged
  if(sampleY < 0) {
	  n = 0;
  }  else {
	  n = (upper[sampleY][sampleX] +
          upper[sampleY][SCREEN_WIDTH - 1 - sampleX]) / 2;
  }
  uThreshold = (uThreshold * 3 + n) / 4; // Filter/soften motion
  // Lower eyelid doesn't track the same way, but seems to be pulled upward
  // by tension from the upper lid.
  lThreshold = 254 - uThreshold;
#else // No tracking -- eyelids full open unless blink modifies them
  uThreshold = lThreshold = 0;
#endif

  // The upper/lower thresholds are then scaled relative to the current
  // blink position so that blinks work together with pupil tracking.
  if(eye[eyeIndex].blink.state) { // Eye currently blinking?
    uint32_t s = (t - eye[eyeIndex].blink.startTime);
    if(s >= eye[eyeIndex].blink.duration) {
    	s = 255;   // At or past blink end
    } else {
    	s = 255 * s / eye[eyeIndex].blink.duration; // Mid-blink
    }
    s          = (eye[eyeIndex].blink.state == DEBLINK) ? 1 + s : 256 - s;
    n          = (uThreshold * s + 254 * (257 - s)) / 256;
    lThreshold = (lThreshold * s + 254 * (257 - s)) / 256;
  } else {
    n          = uThreshold;
  }
  // Pass all the derived values to the eye-rendering function:
  drawEye(eyeIndex, iScale, eyeX, eyeY, n, lThreshold);
  if (eyeIndex==NUM_EYES-1) { /* both eyes are in the frame */
    GDisp1_UpdateFull();
  }
  eyeIndex++;
  if(eyeIndex >= NUM_EYES) {
	  eyeIndex = 0; // Cycle through eyes, 1 per call
  }
}

// AUTONOMOUS IRIS SCALING (if no photocell or dial) -----------------------

#if !EYES_USE_INTERACTIVE_IRIS
// Autonomous iris motion uses a fractal behavior to similate both the major
// reaction of the eye plus the continuous smaller adjustments that occur.

static uint16_t oldIris = (IRIS_MIN + IRIS_MAX) / 2, newIris;

void split( // Subdivides motion path into two sub-paths w/randimization
  int16_t  startValue, // Iris scale value (IRIS_MIN to IRIS_MAX) at start
  int16_t  endValue,   // Iris scale value at end
  uint32_t startTime,  // micros() at start
  int32_t  duration,   // Start-to-end time, in microseconds
  int16_t  range) {    // Allowable scale value variance when subdividing

  if(range >= 8) {     // Limit subdvision count, because recursion
    range    /= 2;     // Split range & time in half for subdivision,
    duration /= 2;     // then pick random center point within range:
    int16_t  midValue = (startValue + endValue - range) / 2 + random(0, range);
    uint32_t midTime  = startTime + duration;
    split(startValue, midValue, startTime, duration, range); // First half
    split(midValue  , endValue, midTime  , duration, range); // Second half
  } else {             // No more subdivisons, do iris motion...
    int32_t dt;        // Time (micros) since start of motion
    int16_t v;         // Interim value
    while((dt = (micros() - startTime)) < duration) {
      v = startValue + (((endValue - startValue) * dt) / duration);
      if(v < IRIS_MIN)     {
    	  v = IRIS_MIN; // Clip just in case
      } else if(v > IRIS_MAX) {
    	v = IRIS_MAX;
      }
      frame(v);        // Draw frame w/interim iris scale value
    }
  }
}
#endif

void EYES_ShowLogo(void) {
#ifdef LOGO_TOP_WIDTH
#if 0
  uint8_t e; // Eye index, 0 to NUM_EYES-1
  int x, y, idx;

  // I noticed lots of folks getting right/left eyes flipped, or
  // installing upside-down, etc.  Logo split across screens may help:
  for(e=0; e<NUM_EYES; e++) { // Another pass, after all screen inits
	idx = 0;
	for(x=0; x<LOGO_TOP_WIDTH; x++) {
		for(y=0;y<LOGO_TOP_HEIGHT;y++) {
		  GDisp1_PutPixel(x, y, logo_top[idx]);
		}
	}
#if 0
	//drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
    eye[e].display->fillScreen(0);
    eye[e].display->drawBitmap(NUM_EYES*64 - e*128 - 20,
      0, logo_top, LOGO_TOP_WIDTH, LOGO_TOP_HEIGHT, 0xFFFF);
    eye[e].display->drawBitmap(NUM_EYES*64 - e*128 - LOGO_BOTTOM_WIDTH/2,
      LOGO_TOP_HEIGHT, logo_bottom, LOGO_BOTTOM_WIDTH, LOGO_BOTTOM_HEIGHT,
      0xFFFF);
#endif
  }
  GDisp1_UpdateFull(); /*screen */
#endif
#endif
}

// MAIN LOOP -- runs continuously after setup() ----------------------------

void EYES_Run(void) {
#if EYES_USE_INTERACTIVE_IRIS
  uint16_t v;

  v = GetAmbilightValue();
  v = map(v, 0, 1023, IRIS_MIN, IRIS_MAX); // Scale to iris range
 #if IRIS_SMOOTH // Filter input (gradual motion)
  static uint16_t irisValue = (IRIS_MIN + IRIS_MAX) / 2;
  irisValue = ((irisValue * 15) + v) / 16;
  frame(irisValue);
 #else // Unfiltered (immediate motion)
  frame(v);
 #endif /* IRIS_SMOOTH */
#else  // Autonomous iris scaling -- invoke recursive function
  newIris = random(IRIS_MIN, IRIS_MAX);
  split(oldIris, newIris, micros(), 10000000L, IRIS_MAX - IRIS_MIN);
  oldIris = newIris;
#endif /* EYES_USE_INTERACTIVE_IRIS */
}

void EYES_Init(void) {
  //srand((int32_t)KIN1_GetCycleCounter()); /* seed for random number generator */ /* \todo */
  srand(0x459457);
}
