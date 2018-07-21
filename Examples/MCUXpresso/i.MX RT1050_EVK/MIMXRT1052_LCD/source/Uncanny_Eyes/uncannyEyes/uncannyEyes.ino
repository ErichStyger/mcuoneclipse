//--------------------------------------------------------------------------
// Uncanny eyes for Adafruit 1.5" OLED (product #1431) or 1.44" TFT LCD
// (#2088).  Works on PJRC Teensy 3.x and on Adafruit M0 and M4 boards
// (Feather, Metro, etc.).  This code uses features specific to these
// boards and WILL NOT work on normal Arduino or other boards!
//
// SEE FILE "config.h" FOR MOST CONFIGURATION (graphics, pins, display type,
// etc).  Probably won't need to edit THIS file unless you're doing some
// extremely custom modifications.
//
// Adafruit invests time and resources providing this open source code,
// please support Adafruit and open-source hardware by purchasing products
// from Adafruit!
//
// Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
// MIT license.  SPI FIFO insight from Paul Stoffregen's ILI9341_t3 library.
// Inspired by David Boccabella's (Marcwolf) hybrid servo/OLED eye concept.
//--------------------------------------------------------------------------

#include <SPI.h>
#include <Adafruit_GFX.h>
#ifdef ARDUINO_ARCH_SAMD
  #include <Adafruit_ZeroDMA.h>
#endif

typedef struct {        // Struct is defined before including config.h --
  int8_t select;        // pin numbers for each eye's screen select line
  int8_t wink;          // and wink button (or -1 if none)
} eyePins_t;            // are specified there...

#include "config.h"     // ****** CONFIGURATION IS DONE IN HERE ******

#if defined(_ADAFRUIT_ST7735H_) || defined(_ADAFRUIT_ST77XXH_)
  typedef Adafruit_ST7735  displayType; // Using TFT display(s)
#else
  typedef Adafruit_SSD1351 displayType; // Using OLED display(s)
#endif

// A simple state machine is used to control eye blinks/winks:
#define NOBLINK 0       // Not currently engaged in a blink
#define ENBLINK 1       // Eyelid is currently closing
#define DEBLINK 2       // Eyelid is currently opening
typedef struct {
  uint8_t  state;       // NOBLINK/ENBLINK/DEBLINK
  uint32_t duration;    // Duration of blink state (micros)
  uint32_t startTime;   // Time (micros) of last state change
} eyeBlink;

#define NUM_EYES (sizeof eyePins / sizeof eyePins[0]) // config.h pin list

struct {                // One-per-eye structure
  displayType *display; // -> OLED/TFT object
  eyeBlink     blink;   // Current blink/wink state
} eye[NUM_EYES];

#ifdef ARDUINO_ARCH_SAMD
  // SAMD boards use DMA (Teensy uses SPI FIFO instead):
  // Two single-line 128-pixel buffers (16bpp) are used for DMA.
  // Though you'd think fewer larger transfers would improve speed,
  // multi-line buffering made no appreciable difference.
  uint16_t          dmaBuf[2][128];
  uint8_t           dmaIdx = 0; // Active DMA buffer # (alternate fill/send)
  Adafruit_ZeroDMA  dma;
  DmacDescriptor   *descriptor;

  // DMA transfer-in-progress indicator and callback
  static volatile bool dma_busy = false;
  static void dma_callback(Adafruit_ZeroDMA *dma) { dma_busy = false; }
#endif

uint32_t startTime;  // For FPS indicator


// INITIALIZATION -- runs once at startup ----------------------------------

void setup(void) {
  uint8_t e; // Eye index, 0 to NUM_EYES-1

  Serial.begin(115200);
  randomSeed(analogRead(A3)); // Seed random() from floating analog input

  // Initialize eye objects based on eyePins list in config.h:
  for(e=0; e<NUM_EYES; e++) {
    eye[e].display     = new displayType(eyePins[e].select, DISPLAY_DC, -1);
    eye[e].blink.state = NOBLINK;
    // If project involves only ONE eye and NO other SPI devices, its
    // select line can be permanently tied to GND and corresponding pin
    // in config.h set to -1.  Best to use it though.
    if(eyePins[e].select >= 0) {
      pinMode(eyePins[e].select, OUTPUT);
      digitalWrite(eyePins[e].select, HIGH); // Deselect them all
    }
    // Also set up an individual eye-wink pin if defined:
    if(eyePins[e].wink >= 0) pinMode(eyePins[e].wink, INPUT_PULLUP);
  }
#if defined(BLINK_PIN) && (BLINK_PIN >= 0)
  pinMode(BLINK_PIN, INPUT_PULLUP); // Ditto for all-eyes blink pin
#endif

#if defined(DISPLAY_RESET) && (DISPLAY_RESET >= 0)
  // Because both displays share a common reset pin, -1 is passed to
  // the display constructor above to prevent the begin() function from
  // resetting both displays after one is initialized.  Instead, handle
  // the reset manually here to take care of both displays just once:
  pinMode(DISPLAY_RESET, OUTPUT);
  digitalWrite(DISPLAY_RESET, LOW);  delay(1);
  digitalWrite(DISPLAY_RESET, HIGH); delay(50);
  // Alternately, all display reset pin(s) could be connected to the
  // microcontroller reset, in which case DISPLAY_RESET should be set
  // to -1 or left undefined in config.h.
#endif

  // After all-displays reset, now call init/begin func for each display:
  for(e=0; e<NUM_EYES; e++) {
#if defined(_ADAFRUIT_ST7735H_) || defined(_ADAFRUIT_ST77XXH_)
    eye[e].display->initR(INITR_144GREENTAB); // TFT
#else
    eye[e].display->begin();                  // OLED
#endif
  }

#ifdef LOGO_TOP_WIDTH
  // I noticed lots of folks getting right/left eyes flipped, or
  // installing upside-down, etc.  Logo split across screens may help:
  for(e=0; e<NUM_EYES; e++) { // Another pass, after all screen inits
    eye[e].display->fillScreen(0);
    eye[e].display->drawBitmap(NUM_EYES*64 - e*128 - 20,
      0, logo_top, LOGO_TOP_WIDTH, LOGO_TOP_HEIGHT, 0xFFFF);
    eye[e].display->drawBitmap(NUM_EYES*64 - e*128 - LOGO_BOTTOM_WIDTH/2,
      LOGO_TOP_HEIGHT, logo_bottom, LOGO_BOTTOM_WIDTH, LOGO_BOTTOM_HEIGHT,
      0xFFFF);
  }
  delay(2000); // Pause for screen layout/orientation
#endif

  // One of the displays is configured to mirror on the X axis.  Simplifies
  // eyelid handling in the drawEye() function -- no need for distinct
  // L-to-R or R-to-L inner loops.  Just the X coordinate of the iris is
  // then reversed when drawing this eye, so they move the same.  Magic!
#if defined(_ADAFRUIT_ST7735H_) || defined(_ADAFRUIT_ST77XXH_) // TFT
  digitalWrite(eyePins[0].select, LOW);
  digitalWrite(DISPLAY_DC, LOW);
#ifdef ST77XX_MADCTL
  SPI.transfer(ST77XX_MADCTL); // Current TFT lib
#else
  SPI.transfer(ST7735_MADCTL); // Older TFT lib
#endif
  digitalWrite(DISPLAY_DC, HIGH);
  SPI.transfer(0x88); // MADCTL_MY | MADCTL_BGR
  digitalWrite(eyePins[0].select , HIGH);
#else // OLED
  eye[0].display->writeCommand(SSD1351_CMD_SETREMAP);
  eye[0].display->writeData(0x76);
#endif

#ifdef ARDUINO_ARCH_SAMD
  // Set up SPI DMA on SAMD boards:

  int                dmac_id;
  volatile uint32_t *data_reg;
  if(&PERIPH_SPI == &sercom0) {
    dmac_id  = SERCOM0_DMAC_ID_TX;
    data_reg = &SERCOM0->SPI.DATA.reg;
#if defined SERCOM1
  } else if(&PERIPH_SPI == &sercom1) {
    dmac_id  = SERCOM1_DMAC_ID_TX;
    data_reg = &SERCOM1->SPI.DATA.reg;
#endif
#if defined SERCOM2
  } else if(&PERIPH_SPI == &sercom2) {
    dmac_id  = SERCOM2_DMAC_ID_TX;
    data_reg = &SERCOM2->SPI.DATA.reg;
#endif
#if defined SERCOM3
  } else if(&PERIPH_SPI == &sercom3) {
    dmac_id  = SERCOM3_DMAC_ID_TX;
    data_reg = &SERCOM3->SPI.DATA.reg;
#endif
#if defined SERCOM4
  } else if(&PERIPH_SPI == &sercom4) {
    dmac_id  = SERCOM4_DMAC_ID_TX;
    data_reg = &SERCOM4->SPI.DATA.reg;
#endif
#if defined SERCOM5
  } else if(&PERIPH_SPI == &sercom5) {
    dmac_id  = SERCOM5_DMAC_ID_TX;
    data_reg = &SERCOM5->SPI.DATA.reg;
#endif
  }

  dma.allocate();
  dma.setTrigger(dmac_id);
  dma.setAction(DMA_TRIGGER_ACTON_BEAT);
  descriptor = dma.addDescriptor(
    NULL,               // move data
    (void *)data_reg,   // to here
    sizeof dmaBuf[0],   // this many...
    DMA_BEAT_SIZE_BYTE, // bytes/hword/words
    true,               // increment source addr?
    false);             // increment dest addr?
  dma.setCallback(dma_callback);

#endif // End SAMD-specific SPI DMA init

  startTime = millis(); // For frame-rate calculation
}


// EYE-RENDERING FUNCTION --------------------------------------------------

SPISettings settings(SPI_FREQ, MSBFIRST, SPI_MODE0);

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

  // Set up raw pixel dump to entire screen.  Although such writes can wrap
  // around automatically from end of rect back to beginning, the region is
  // reset on each frame here in case of an SPI glitch.
  SPI.beginTransaction(settings);
  digitalWrite(eyePins[e].select, LOW);                        // Chip select
#if defined(_ADAFRUIT_ST7735H_) || defined(_ADAFRUIT_ST77XXH_) // TFT
  eye[e].display->setAddrWindow(0, 0, 128, 128);
#else // OLED
  eye[e].display->writeCommand(SSD1351_CMD_SETROW);    // Y range
  eye[e].display->writeData(0); eye[e].display->writeData(SCREEN_HEIGHT - 1);
  eye[e].display->writeCommand(SSD1351_CMD_SETCOLUMN); // X range
  eye[e].display->writeData(0); eye[e].display->writeData(SCREEN_WIDTH  - 1);
  eye[e].display->writeCommand(SSD1351_CMD_WRITERAM);  // Begin write
#endif
  digitalWrite(eyePins[e].select, LOW);                // Re-chip-select
  digitalWrite(DISPLAY_DC, HIGH);                      // Data mode
  // Now just issue raw 16-bit values for every pixel...

  scleraXsave = scleraX; // Save initial X value to reset on each line
  irisY       = scleraY - (SCLERA_HEIGHT - IRIS_HEIGHT) / 2;
  for(screenY=0; screenY<SCREEN_HEIGHT; screenY++, scleraY++, irisY++) {
#ifdef ARDUINO_ARCH_SAMD
    uint16_t *ptr = &dmaBuf[dmaIdx][0];
#endif
    scleraX = scleraXsave;
    irisX   = scleraXsave - (SCLERA_WIDTH - IRIS_WIDTH) / 2;
    for(screenX=0; screenX<SCREEN_WIDTH; screenX++, scleraX++, irisX++) {
      if((lower[screenY][screenX] <= lT) ||
         (upper[screenY][screenX] <= uT)) {             // Covered by eyelid
        p = 0;
      } else if((irisY < 0) || (irisY >= IRIS_HEIGHT) ||
                (irisX < 0) || (irisX >= IRIS_WIDTH)) { // In sclera
        p = sclera[scleraY][scleraX];
      } else {                                          // Maybe iris...
        p = polar[irisY][irisX];                        // Polar angle/dist
        d = (iScale * (p & 0x7F)) / 128;                // Distance (Y)
        if(d < IRIS_MAP_HEIGHT) {                       // Within iris area
          a = (IRIS_MAP_WIDTH * (p >> 7)) / 512;        // Angle (X)
          p = iris[d][a];                               // Pixel = iris
        } else {                                        // Not in iris
          p = sclera[scleraY][scleraX];                 // Pixel = sclera
        }
      }
#ifdef ARDUINO_ARCH_SAMD
      *ptr++ = __builtin_bswap16(p); // DMA: store in scanline buffer
#else
      // SPI FIFO technique from Paul Stoffregen's ILI9341_t3 library:
      while(KINETISK_SPI0.SR & 0xC000); // Wait for space in FIFO
      KINETISK_SPI0.PUSHR = p | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
#endif
    } // end column
#ifdef ARDUINO_ARCH_SAMD
    while(dma_busy); // Wait for prior DMA xfer to finish
    descriptor->SRCADDR.reg = (uint32_t)&dmaBuf[dmaIdx] + sizeof dmaBuf[0];
    dma_busy = true;
    dmaIdx   = 1 - dmaIdx;
    dma.startJob();
#endif
  } // end scanline

#ifdef ARDUINO_ARCH_SAMD
  while(dma_busy);  // Wait for last scanline to transmit
#else
  KINETISK_SPI0.SR |= SPI_SR_TCF;         // Clear transfer flag
  while((KINETISK_SPI0.SR & 0xF000) ||    // Wait for SPI FIFO to drain
       !(KINETISK_SPI0.SR & SPI_SR_TCF)); // Wait for last bit out
#endif

  digitalWrite(eyePins[e].select, HIGH);          // Deselect
  SPI.endTransaction();
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

#ifdef AUTOBLINK
uint32_t timeOfLastBlink = 0L, timeToNextBlink = 0L;
#endif

void frame( // Process motion for a single frame of left or right eye
  uint16_t        iScale) {     // Iris scale (0-1023) passed in
  static uint32_t frames   = 0; // Used in frame rate calculation
  static uint8_t  eyeIndex = 0; // eye[] array counter
  int16_t         eyeX, eyeY;
  uint32_t        t = micros(); // Time at start of function

  if(!(++frames & 255)) { // Every 256 frames...
    uint32_t elapsed = (millis() - startTime) / 1000;
    if(elapsed) Serial.println(frames / elapsed); // Print FPS
  }

  if(++eyeIndex >= NUM_EYES) eyeIndex = 0; // Cycle through eyes, 1 per call

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

  static boolean  eyeInMotion      = false;
  static int16_t  eyeOldX=512, eyeOldY=512, eyeNewX=512, eyeNewY=512;
  static uint32_t eyeMoveStartTime = 0L;
  static int32_t  eyeMoveDuration  = 0L;

  int32_t dt = t - eyeMoveStartTime;      // uS elapsed since last eye event
  if(eyeInMotion) {                       // Currently moving?
    if(dt >= eyeMoveDuration) {           // Time up?  Destination reached.
      eyeInMotion      = false;           // Stop moving
      eyeMoveDuration  = random(3000000); // 0-3 sec stop
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
        eyeNewX = random(1024);
        eyeNewY = random(1024);
        dx      = (eyeNewX * 2) - 1023;
        dy      = (eyeNewY * 2) - 1023;
      } while((d = (dx * dx + dy * dy)) > (1023 * 1023)); // Keep trying
      eyeMoveDuration  = random(72000, 144000); // ~1/14 - ~1/7 sec
      eyeMoveStartTime = t;               // Save initial time of move
      eyeInMotion      = true;            // Start move on next frame
    }
  }

#endif // JOYSTICK_X_PIN etc.

  // Blinking

#ifdef AUTOBLINK
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
    timeToNextBlink = blinkDuration * 3 + random(4000000);
  }
#endif

  if(eye[eyeIndex].blink.state) { // Eye currently blinking?
    // Check if current blink state time has elapsed
    if((t - eye[eyeIndex].blink.startTime) >= eye[eyeIndex].blink.duration) {
      // Yes -- increment blink state, unless...
      if((eye[eyeIndex].blink.state == ENBLINK) && ( // Enblinking and...
#if defined(BLINK_PIN) && (BLINK_PIN >= 0)
        (digitalRead(BLINK_PIN) == LOW) ||           // blink or wink held...
#endif
        ((eyePins[eyeIndex].wink >= 0) &&
         digitalRead(eyePins[eyeIndex].wink) == LOW) )) {
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
#if defined(BLINK_PIN) && (BLINK_PIN >= 0)
    if(digitalRead(BLINK_PIN) == LOW) {
      // Manually-initiated blinks have random durations like auto-blink
      uint32_t blinkDuration = random(36000, 72000);
      for(uint8_t e=0; e<NUM_EYES; e++) {
        if(eye[e].blink.state == NOBLINK) {
          eye[e].blink.state     = ENBLINK;
          eye[e].blink.startTime = t;
          eye[e].blink.duration  = blinkDuration;
        }
      }
    } else
#endif
    if((eyePins[eyeIndex].wink >= 0) &&
       (digitalRead(eyePins[eyeIndex].wink) == LOW)) { // Wink!
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
  eyeX = map(eyeX, 0, 1023, 0, SCLERA_WIDTH  - 128);
  eyeY = map(eyeY, 0, 1023, 0, SCLERA_HEIGHT - 128);
  if(eyeIndex == 1) eyeX = (SCLERA_WIDTH - 128) - eyeX; // Mirrored display

  // Horizontal position is offset so that eyes are very slightly crossed
  // to appear fixated (converged) at a conversational distance.  Number
  // here was extracted from my posterior and not mathematically based.
  // I suppose one could get all clever with a range sensor, but for now...
  if(NUM_EYES > 1) eyeX += 4;
  if(eyeX > (SCLERA_WIDTH - 128)) eyeX = (SCLERA_WIDTH - 128);

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
  if(sampleY < 0) n = 0;
  else            n = (upper[sampleY][sampleX] +
                       upper[sampleY][SCREEN_WIDTH - 1 - sampleX]) / 2;
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
    if(s >= eye[eyeIndex].blink.duration) s = 255;   // At or past blink end
    else s = 255 * s / eye[eyeIndex].blink.duration; // Mid-blink
    s          = (eye[eyeIndex].blink.state == DEBLINK) ? 1 + s : 256 - s;
    n          = (uThreshold * s + 254 * (257 - s)) / 256;
    lThreshold = (lThreshold * s + 254 * (257 - s)) / 256;
  } else {
    n          = uThreshold;
  }

  // Pass all the derived values to the eye-rendering function:
  drawEye(eyeIndex, iScale, eyeX, eyeY, n, lThreshold);
}


// AUTONOMOUS IRIS SCALING (if no photocell or dial) -----------------------

#if !defined(IRIS_PIN) || (IRIS_PIN < 0)

// Autonomous iris motion uses a fractal behavior to similate both the major
// reaction of the eye plus the continuous smaller adjustments that occur.

uint16_t oldIris = (IRIS_MIN + IRIS_MAX) / 2, newIris;

void split( // Subdivides motion path into two sub-paths w/randimization
  int16_t  startValue, // Iris scale value (IRIS_MIN to IRIS_MAX) at start
  int16_t  endValue,   // Iris scale value at end
  uint32_t startTime,  // micros() at start
  int32_t  duration,   // Start-to-end time, in microseconds
  int16_t  range) {    // Allowable scale value variance when subdividing

  if(range >= 8) {     // Limit subdvision count, because recursion
    range    /= 2;     // Split range & time in half for subdivision,
    duration /= 2;     // then pick random center point within range:
    int16_t  midValue = (startValue + endValue - range) / 2 + random(range);
    uint32_t midTime  = startTime + duration;
    split(startValue, midValue, startTime, duration, range); // First half
    split(midValue  , endValue, midTime  , duration, range); // Second half
  } else {             // No more subdivisons, do iris motion...
    int32_t dt;        // Time (micros) since start of motion
    int16_t v;         // Interim value
    while((dt = (micros() - startTime)) < duration) {
      v = startValue + (((endValue - startValue) * dt) / duration);
      if(v < IRIS_MIN)      v = IRIS_MIN; // Clip just in case
      else if(v > IRIS_MAX) v = IRIS_MAX;
      frame(v);        // Draw frame w/interim iris scale value
    }
  }
}

#endif // !IRIS_PIN


// MAIN LOOP -- runs continuously after setup() ----------------------------

void loop() {

#if defined(IRIS_PIN) && (IRIS_PIN >= 0) // Interactive iris

  uint16_t v = analogRead(IRIS_PIN);       // Raw dial/photocell reading
#ifdef IRIS_PIN_FLIP
  v = 1023 - v;
#endif
  v = map(v, 0, 1023, IRIS_MIN, IRIS_MAX); // Scale to iris range
#ifdef IRIS_SMOOTH // Filter input (gradual motion)
  static uint16_t irisValue = (IRIS_MIN + IRIS_MAX) / 2;
  irisValue = ((irisValue * 15) + v) / 16;
  frame(irisValue);
#else // Unfiltered (immediate motion)
  frame(v);
#endif // IRIS_SMOOTH

#else  // Autonomous iris scaling -- invoke recursive function

  newIris = random(IRIS_MIN, IRIS_MAX);
  split(oldIris, newIris, micros(), 10000000L, IRIS_MAX - IRIS_MIN);
  oldIris = newIris;

#endif // IRIS_PIN
}
