/** ###################################################################
**     Filename  : Cube.C
**     Project   : Tower_LCD
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 09.01.2010, 20:03
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Cube */

#include "Platform.h"

#if PL_HAS_CUBE_DEMO
#include "Cube.h"
#include "WAIT1.h"
#include "GDisp1.h"
#include "FRTOS1.h"
#include "RTOS.h"
#include "Helv12n.h"
#include "App.h"
#include "EVNT1.h"

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT   PL_FONT()
#else
  #define FONT   Helv12n_GetFont()
#endif

static bool doCloseCubeWindow = FALSE;

/* http://www.pyrofersprojects.com/code/3dcube.txt */
//
// 3D Cube by Jason Wright (C)opyright Pyrofer 2006
//
// This code is free, there is no charge for it nor should anybody else charge
// for the code, its distribution or derivitives of this code.
//
// You may use this code, modify and change and improve upon it on the following conditions,
//
// 1> You send me the modified source code and where possible make it public
// 2> I am credited for the original work in all derivitives of this code
// 3> You do not charge for this code or code derived from this code
// 4> You comment the code you change! 
//
// Basically, use this to learn! I could'nt find anything this simple when I started so I hope
// that this helps others to learn. You should be able to change the LCD routines to drive almost 
// any graphics device. The base resolution is 128x128 for this display. Simply set the X and Y offset
// to half the screen resolution for each axis.
// Then adjust the Z offset to make the object fit nicely in the screen.


//#include "math.h"  // include complex math routines

const float si[360]={
0.000001 ,                                                                                                                            //  0
0.01745239 , 0.03489947 , 0.05233591 , 0.06975641 , 0.08715567 , 0.1045284 , 0.1218692 , 0.139173 , 0.1564343 , 0.173648 ,            // 1 - 10
0.1908088 , 0.2079115 , 0.2249509 , 0.2419217 , 0.2588188 , 0.2756371 , 0.2923715 , 0.3090167 , 0.3255679 , 0.3420198 ,               // 11 - 20
0.3583677 , 0.3746063 , 0.3907308 , 0.4067363 , 0.4226179 , 0.4383708 , 0.4539901 , 0.4694712 , 0.4848093 , 0.4999996 ,               // 21 - 30
0.5150377 , 0.5299189 , 0.5446386 , 0.5591925 , 0.573576 , 0.5877848 , 0.6018146 , 0.615661 , 0.62932 , 0.6427872 ,                   // 31 - 40
0.6560586 , 0.6691301 , 0.6819978 , 0.6946579 , 0.7071063 , 0.7193394 , 0.7313532 , 0.7431444 , 0.7547091 , 0.7660439 ,               // 41 - 50
0.7771455 , 0.7880103 , 0.798635 , 0.8090165 , 0.8191515 , 0.8290371 , 0.8386701 , 0.8480476 , 0.8571668 , 0.8660249 ,                // 51 - 60
0.8746193 , 0.8829472 , 0.8910061 , 0.8987936 , 0.9063074 , 0.913545 , 0.9205045 , 0.9271835 , 0.9335801 , 0.9396922 ,                // 61 - 70
0.9455183 , 0.9510562 , 0.9563044 , 0.9612614 , 0.9659255 , 0.9702954 , 0.9743698 , 0.9781474 , 0.981627 , 0.9848075 ,                // 71 - 80
0.9876881 , 0.9902679 , 0.992546 , 0.9945218 , 0.9961946 , 0.9975639 , 0.9986295 , 0.9993908 , 0.9998476 , 0.99999 ,                  // 81 - 90
0.9998477 , 0.9993909 , 0.9986296 , 0.9975642 , 0.9961948 , 0.994522 , 0.9925463 , 0.9902682 , 0.9876886 , 0.984808 ,                 // 91 - 100
0.9816275 , 0.9781479 , 0.9743704 , 0.9702961 , 0.9659262 , 0.9612621 , 0.9563052 , 0.9510571 , 0.9455191 , 0.9396932 ,               // 101 - 110
0.933581 , 0.9271844 , 0.9205055 , 0.9135461 , 0.9063086 , 0.8987948 , 0.8910073 , 0.8829485 , 0.8746206 , 0.8660263 ,                // 111 - 120
0.8571682 , 0.8480491 , 0.8386716 , 0.8290385 , 0.8191531 , 0.8090182 , 0.7986366 , 0.7880119 , 0.7771472 , 0.7660457 ,               // 121 - 130
0.7547108 , 0.7431462 , 0.7313551 , 0.7193412 , 0.7071083 , 0.6946598 , 0.6819999 , 0.6691321 , 0.6560606 , 0.6427892 ,               // 131 - 140
0.629322 , 0.6156631 , 0.6018168 , 0.5877869 , 0.5735782 , 0.5591948 , 0.5446408 , 0.5299212 , 0.5150401 , 0.5000019 ,                // 141 - 150
0.4848116 , 0.4694737 , 0.4539925 , 0.4383733 , 0.4226205 , 0.4067387 , 0.3907333 , 0.3746087 , 0.3583702 , 0.3420225 ,               // 151 - 160
0.3255703 , 0.3090193 , 0.2923741 , 0.2756396 , 0.2588214 , 0.2419244 , 0.2249534 , 0.2079142 , 0.1908116 , 0.1736506 ,               // 161 - 170
0.156437 , 0.1391758 , 0.1218719 , 0.1045311 , 0.08715825 , 0.06975908 , 0.05233867 , 0.03490207 , 0.01745508 , 0.0277 ,              // 171 - 180
-0.01744977 , -0.03489676 , -0.05233313 , -0.06975379 , -0.08715296 , -0.1045256 , -0.1218666 , -0.1391703 , -0.1564316 , -0.1736454 ,// 181 - 190
-0.1908061 , -0.207909 , -0.2249483 , -0.241919 , -0.2588163 , -0.2756345 , -0.2923688 , -0.3090142 , -0.3255653 , -0.3420173 ,       // 191 - 200
-0.3583652 , -0.3746038 , -0.3907282 , -0.4067339 , -0.4226155 , -0.4383683 , -0.4539878 , -0.4694688 , -0.4848068 , -0.4999973 ,     // 201 - 210
-0.5150353 , -0.5299166 , -0.5446364 , -0.5591902 , -0.5735739 , -0.5877826 , -0.6018124 , -0.615659 , -0.6293178 , -0.642785 ,       // 211 - 220
-0.6560566 , -0.6691281 , -0.6819958 , -0.694656 , -0.7071043 , -0.7193374 , -0.7313514 , -0.7431425 , -0.7547074 , -0.7660421 ,      // 221 - 230
-0.7771439 , -0.7880087 , -0.7986334 , -0.8090149 , -0.8191499 , -0.8290355 , -0.8386687 , -0.8480463 , -0.8571655 , -0.8660236 ,     // 231 - 240
-0.8746178 , -0.882946 , -0.8910049 , -0.8987925 , -0.9063062 , -0.9135439 , -0.9205033 , -0.9271825 , -0.9335791 , -0.9396913 ,      // 241 - 250
-0.9455173 , -0.9510553 , -0.9563036 , -0.9612607 , -0.9659248 , -0.9702948 , -0.9743692 , -0.9781467 , -0.9816265 , -0.9848071 ,     // 251 - 260
-0.9876878 , -0.9902675 , -0.9925456 , -0.9945215 , -0.9961944 , -0.9975638 , -0.9986293 , -0.9993907 , -0.9998476 , -0.99999 ,       // 261 - 270
-0.9998478 , -0.9993909 , -0.9986298 , -0.9975643 , -0.9961951 , -0.9945223 , -0.9925466 , -0.9902686 , -0.987689 , -0.9848085 ,      // 271 - 280
-0.981628 , -0.9781484 , -0.974371 , -0.9702968 , -0.965927 , -0.9612629 , -0.9563061 , -0.9510578 , -0.9455199 , -0.9396941 ,        // 281 - 290
-0.933582 , -0.9271856 , -0.9205065 , -0.9135472 , -0.9063097 , -0.898796 , -0.8910086 , -0.8829498 , -0.8746218 , -0.8660276 ,       // 291 - 300
-0.8571696 , -0.8480505 , -0.8386731 , -0.8290402 , -0.8191546 , -0.8090196 , -0.7986383 , -0.7880136 , -0.777149 , -0.7660476 ,      // 301 - 310
-0.7547125 , -0.7431479 , -0.7313569 , -0.7193431 , -0.7071103 , -0.6946616 , -0.6820017 , -0.6691341 , -0.6560627 , -0.6427914 ,     // 311 - 320
-0.6293243 , -0.6156651 , -0.6018188 , -0.5877892 , -0.5735805 , -0.5591971 , -0.5446434 , -0.5299233 , -0.5150422 , -0.5000043 ,     // 321 - 330
-0.484814 , -0.4694761 , -0.4539948 , -0.4383755 , -0.4226228 , -0.4067413 , -0.3907359 , -0.3746115 , -0.3583725 , -0.3420248 ,      // 331 - 340
-0.325573 , -0.3090219 , -0.2923768 , -0.2756425 , -0.2588239 , -0.2419269 , -0.2249561 , -0.2079169 , -0.1908143 , -0.1736531 ,      // 341 - 350
-0.1564395 , -0.1391783 , -0.1218746 , -0.1045339 , -0.08716125 , -0.06976161 , -0.0523412 , -0.03490484 , -0.01745785 };             // 351 - 359

const float co[360]={
0.99999 ,                                                                                                                            //  0
0.9998477 , 0.9993908 , 0.9986295 , 0.9975641 , 0.9961947 , 0.9945219 , 0.9925462 , 0.9902681 , 0.9876884 , 0.9848078 ,              // 1 - 10
0.9816272 , 0.9781477 , 0.9743701 , 0.9702958 , 0.9659259 , 0.9612617 , 0.9563049 , 0.9510566 , 0.9455186 , 0.9396928 ,              // 11 - 20
0.9335806 , 0.927184 , 0.920505 , 0.9135456 , 0.906308 , 0.8987943 , 0.8910067 , 0.8829478 , 0.8746199 , 0.8660256 ,                 // 21 - 30
0.8571675 , 0.8480483 , 0.8386709 , 0.8290379 , 0.8191524 , 0.8090173 , 0.7986359 , 0.7880111 , 0.7771463 , 0.7660448 ,              // 31 - 40
0.75471 , 0.7431452 , 0.7313541 , 0.7193403 , 0.7071072 , 0.6946589 , 0.6819989 , 0.6691311 , 0.6560596 , 0.6427882 ,                // 41 - 50
0.629321 , 0.6156621 , 0.6018156 , 0.5877859 , 0.5735771 , 0.5591936 , 0.5446398 , 0.52992 , 0.5150389 , 0.5000008 ,                 // 51 - 60
0.4848104 , 0.4694724 , 0.4539914 , 0.438372 , 0.4226191 , 0.4067376 , 0.3907321 , 0.3746075 , 0.3583689 , 0.3420211 ,               // 61 - 70
0.3255692 , 0.309018 , 0.2923728 , 0.2756384 , 0.2588201 , 0.241923 , 0.2249522 , 0.2079128 , 0.1908101 , 0.1736494 ,                // 71 - 80
0.1564357 , 0.1391743 , 0.1218706 , 0.1045297 , 0.08715699 , 0.06975782 , 0.05233728 , 0.0349008 , 0.01745369 , 0.0138 ,             // 81 - 90
-0.01745104 , -0.03489815 , -0.05233451 , -0.06975505 , -0.08715434 , -0.1045271 , -0.1218679 , -0.1391717 , -0.156433 , -0.1736467 ,// 91 - 100
-0.1908075 , -0.2079102 , -0.2249495 , -0.2419204 , -0.2588175 , -0.2756359 , -0.2923701 , -0.3090155 , -0.3255666 , -0.3420185 ,    // 101 - 110
-0.3583664 , -0.3746051 , -0.3907295 , -0.4067351 , -0.4226166 , -0.4383696 , -0.4539889 , -0.4694699 , -0.4848081 , -0.4999984 ,    // 111 - 120
-0.5150366 , -0.5299177 , -0.5446375 , -0.5591914 , -0.5735749 , -0.5877837 , -0.6018136 , -0.6156599 , -0.6293188 , -0.6427862 ,    // 121 - 130
-0.6560575 , -0.669129 , -0.6819969 , -0.6946569 , -0.7071053 , -0.7193384 , -0.7313522 , -0.7431435 , -0.7547083 , -0.7660431 ,     // 131 - 140
-0.7771447 , -0.7880094 , -0.7986342 , -0.8090158 , -0.8191508 , -0.8290363 , -0.8386694 , -0.8480469 , -0.8571661 , -0.8660243 ,    // 141 - 150
-0.8746186 , -0.8829465 , -0.8910055 , -0.898793 , -0.9063068 , -0.9135445 , -0.9205039 , -0.927183 , -0.9335796 , -0.9396918 ,      // 151 - 160
-0.9455178 , -0.9510558 , -0.956304 , -0.9612611 , -0.9659252 , -0.9702951 , -0.9743695 , -0.978147 , -0.9816267 , -0.9848073 ,      // 161 - 170
-0.9876879 , -0.9902677 , -0.9925459 , -0.9945216 , -0.9961945 , -0.9975639 , -0.9986294 , -0.9993907 , -0.9998476 , -0.99999 ,      // 171 - 180
-0.9998477 , -0.9993909 , -0.9986297 , -0.9975642 , -0.9961949 , -0.9945222 , -0.9925465 , -0.9902685 , -0.9876888 , -0.9848083 ,    // 181 - 190
-0.9816277 , -0.9781482 , -0.9743707 , -0.9702965 , -0.9659266 , -0.9612625 , -0.9563056 , -0.9510574 , -0.9455196 , -0.9396937 ,    // 191 - 200
-0.9335815 , -0.927185 , -0.9205061 , -0.9135467 , -0.9063091 , -0.8987955 , -0.8910079 , -0.8829491 , -0.8746213 , -0.866027 ,      // 201 - 210
-0.857169 , -0.8480497 , -0.8386723 , -0.8290394 , -0.8191538 , -0.8090189 , -0.7986375 , -0.7880127 , -0.7771481 , -0.7660466 ,     // 211 - 220
-0.7547117 , -0.743147 , -0.731356 , -0.7193421 , -0.7071092 , -0.6946609 , -0.6820008 , -0.6691331 , -0.6560616 , -0.6427905 ,      // 221 - 230
-0.6293229 , -0.6156641 , -0.6018178 , -0.5877882 , -0.5735794 , -0.5591961 , -0.5446419 , -0.5299222 , -0.5150412 , -0.5000032 ,    // 231 - 240
-0.4848129 , -0.4694746 , -0.4539936 , -0.4383744 , -0.4226216 , -0.4067401 , -0.3907347 , -0.3746099 , -0.3583714 , -0.3420237 ,    // 241 - 250
-0.3255718 , -0.3090207 , -0.2923756 , -0.2756409 , -0.2588227 , -0.2419256 , -0.2249549 , -0.2079156 , -0.1908126 , -0.1736519 ,    // 251 - 260
-0.1564383 , -0.139177 , -0.1218734 , -0.1045326 , -0.08715951 , -0.06976035 , -0.05233994 , -0.03490358 , -0.01745659 , -0.0427 ,   // 261 - 270
0.01744851 , 0.0348955 , 0.05233186 , 0.06975229 , 0.08715146 , 0.1045246 , 0.1218654 , 0.139169 , 0.1564303 , 0.1736439 ,           // 271 - 280
0.1908047 , 0.2079078 , 0.224947 , 0.2419178 , 0.2588149 , 0.2756331 , 0.2923674 , 0.309013 , 0.3255641 , 0.3420161 ,                // 281 - 290
0.3583638 , 0.3746024 , 0.3907273 , 0.4067327 , 0.4226143 , 0.4383671 , 0.4539864 , 0.4694674 , 0.4848059 , 0.4999962 ,              // 291 - 300
0.5150342 , 0.5299154 , 0.5446351 , 0.559189 , 0.5735728 , 0.5877816 , 0.6018113 , 0.6156578 , 0.6293167 , 0.6427839 ,               // 301 - 310
0.6560556 , 0.6691272 , 0.6819949 , 0.6946549 , 0.7071033 , 0.7193366 , 0.7313506 , 0.7431416 , 0.7547064 , 0.7660413 ,              // 311 - 320
0.7771428 , 0.7880079 , 0.7986327 , 0.8090141 , 0.8191492 , 0.8290347 , 0.8386678 , 0.8480456 , 0.8571648 , 0.8660229 ,              // 321 - 330
0.8746172 , 0.8829452 , 0.8910043 , 0.8987919 , 0.9063057 , 0.9135434 , 0.9205029 , 0.9271819 , 0.9335786 , 0.9396909 ,              // 331 - 340
0.9455169 , 0.9510549 , 0.9563032 , 0.9612602 , 0.9659245 , 0.9702945 , 0.9743689 , 0.9781465 , 0.9816261 , 0.9848069 ,              // 341 - 350
0.9876875 , 0.9902673 , 0.9925455 , 0.9945213 , 0.9961942 , 0.9975637 , 0.9986292 , 0.9993906 , 0.9998476 };                         // 351 - 359

typedef struct {
  CUBE_WindowDesc *descP;
} CUBE_WinParams;

static CUBE_WinParams cubeParam;
#if PL_HAS_SHIP_DEMO
  static TaskHandle_t xHandleTask3Dship = NULL;
#endif

#define CUBE_NOF_LINES  12 /* cube has 12 lines */
#define CUBE_NOF_VERTEX  8 /* .. and 8 corners */

// use const as they are in rom, saving ram
static const signed int cubex[CUBE_NOF_VERTEX]={10,-10,-10,10,   10,-10,-10,10};	// x data for shape vertex
static const signed int cubey[CUBE_NOF_VERTEX]={10,10,-10,-10,   10,10,-10,-10};	// y data for shape vertex
static const signed int cubez[CUBE_NOF_VERTEX]={-10,-10,-10,-10, 10,10,10,10};		// z data for shape vertex

static const int cubels[CUBE_NOF_LINES]={1,2,3,4,  5,6,7,8, 1,2,3,4};  // start vertex for lines
static const int cubele[CUBE_NOF_LINES]={2,3,4,1,  6,7,8,5, 5,6,7,8};  // end vertex for lines

#define CUBE_COLOR_LINES         GDisp1_COLOR_RED
#define CUBE_COLOR_BACKGROUND    UI1_COLOR_BRIGHT_GREEN

#define OFFSETZ  30

static portTASK_FUNCTION(Task3Dcube, pvParameters) {
  // routine to draw and calc 3d cube
  CUBE_WinParams *params;
  GDisp1_PixelDim sx,sy,ex,ey;  // vars for calling graphics subroutines
  byte i;                  // temp variable for loops
  float xt,yt,zt,x,y,z;
  float sinax,cosax,sinay,cosay,sinaz,cosaz,vertex;  // lots of work variables
  word rotx;      // starting amount of x rotation
  word roty;      // starting amount of y rotation
  word rotz;      // starting amount of z rotation
  word xpos;			// position for object in 3d space, in x
  word ypos;			// y
  word zpos;			// and z values
  GDisp1_PixelDim oldx[CUBE_NOF_VERTEX], newx[CUBE_NOF_VERTEX];      // translated screen x co-ordinates for vertex
  GDisp1_PixelDim oldy[CUBE_NOF_VERTEX], newy[CUBE_NOF_VERTEX];      // translated screen y co-ordinates for vertex

  params = (CUBE_WinParams*)pvParameters;

  for (i=0; i<CUBE_NOF_VERTEX; i++) { /* init previous cube drawing coordinates */
    oldx[i]=0;
    oldy[i]=0;
  }
  xpos=0;				// position for object in 3d space, in x
  ypos=0;				// y
  zpos=0;				// and z values
  rotx=0;       // starting amount of x rotation
  roty=0;       // starting amount of y rotation
  rotz=0;       // starting amount of z rotation
  for(;;) {
   #if 0
    xpos += 0;			// move the object
    ypos += 0;			// it would wander off screen
    zpos += 0;			// really quick, so leave it centered
   #endif
    rotx += 5;     // rotate the cube on X axis
    if (rotx>359) {
      rotx -= 360;
    }
    roty += 2;      // and on its y axis
    if (roty>359) {
      roty -= 360;
    }
    #if 0
    rotz += 0;     // don't bother with z or it gets confusing
    #endif
    if (rotz>359) {
      rotz -= 360;
    }

    sinax=si[rotx];			// precalculate the sin and cos values
    cosax=co[rotx];			// for the rotation as this saves a 

    sinay=si[roty];			// little time when running as we
    cosay=co[roty];			// call sin and cos less often

    sinaz=si[rotz];			// they are slow routines
    cosaz=co[rotz];			// and we don't want slow!

    for (i=0; i<CUBE_NOF_VERTEX; i++) {
      // translate 3d vertex position to 2d screen position
      x=(float)(cubex[i]);         // get x for vertex i
      y=(float)(cubey[i]);         // get y for vertex i
      z=(float)(cubez[i]);         // get z for vertex i

      yt = y*cosax - z*sinax;	// rotate around the x axis
      zt = y*sinax + z*cosax;	// using the Y and Z for the rotation
      y = yt;
      z = zt;

      xt = x * cosay - z*sinay;	// rotate around the Y axis
      zt = x * sinay + z*cosay;	// using X and Z
      x = xt;
      z = zt;

      xt = x*cosaz - y*sinaz;	// finally rotate around the Z axis
      yt = x*sinaz + y*cosaz;	// using X and Y
      x = xt;
      y = yt;

      x = (float)(x+xpos);			// add the object position offset
      y = (float)(y+ypos);			// for both x and y
      z = (float)(OFFSETZ-zpos);// as well as Z

      newx[i]=(GDisp1_PixelDim)((x*64/z)+UI1_GetElementWidth(&cubeParam.descP->windowCube)/2);	// translate 3d to 2d coordinates for screen
      newy[i]=(GDisp1_PixelDim)((y*64/z)+UI1_GetElementHeight(&cubeParam.descP->windowCube)/2);	// drawing so we can see the cube
    }
    for (i=0; i<CUBE_NOF_LINES; i++)	{
      /* clear previous line of the object */
      vertex=(float)(cubels[i]-1);// temp = start vertex for this line
      sx=oldx[(int)vertex];   // set line start x to vertex[i] x position
      sy=oldy[(int)vertex];   // set line start y to vertex[i] y position
      vertex=(float)(cubele[i]-1);// temp = end vertex for this line
      ex=oldx[(int)vertex];	  // set line end x to vertex[i+1] x position
      ey=oldy[(int)vertex];	  // set line end y to vertex[i+1] y position
      UI1_DrawLine(&cubeParam.descP->windowCube, sx, sy, ex, ey, CUBE_COLOR_BACKGROUND);		// draw the line between these 2 vertex
    }
    for (i=0; i<CUBE_NOF_LINES; i++)	{
      // draw the lines that make up the object
      vertex=(float)(cubels[i]-1);// temp = start vertex for this line
      sx=newx[(int)vertex];   // set line start x to vertex[i] x position
      sy=newy[(int)vertex];   // set line start y to vertex[i] y position
      vertex=(float)(cubele[i]-1);// temp = end vertex for this line
      ex=newx[(int)vertex];	  // set line end x to vertex[i+1] x position
      ey=newy[(int)vertex];	  // set line end y to vertex[i+1] y position
      UI1_DrawLine(&cubeParam.descP->windowCube, sx, sy, ex, ey, CUBE_COLOR_LINES);		// draw the line between these 2 vertex
    }
    for (i=0; i<CUBE_NOF_VERTEX; i++) { /* save values for next iteration */
      oldx[i]=newx[i];
      oldy[i]=newy[i];
    }
    if (doCloseCubeWindow && EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) { /* request to close application */
      EVNT1_ClearEvent(EVNT1_APP_MODE_CHANGE); /* reset event flag */
      FRTOS1_vTaskDelete(NULL); /* kill ourself */ 
    }
    vTaskDelay(pdMS_TO_TICKS(80)); /* give user a chance to see the cube rotating... */
  } /* for */
}

void CUBE_CloseCubeWindow(void) {
  doCloseCubeWindow = TRUE;
  EVNT1_SetEvent(EVNT1_APP_MODE_CHANGE); /* request to close application */
  while(EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) {
    /* wait until task has killed itself */
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  (void)UI1_RemoveWindowPaintBackground(&cubeParam.descP->screen, &cubeParam.descP->windowCube);
  if (cubeParam.descP->screen.first==NULL) {
    /* were the last window: close screen */
    APP_SetApplicationMode(APP_MODE_MAIN_MENU);
  }
}

static void cubeW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &cubeParam.descP->iconCloseCube)) {
      CUBE_CloseCubeWindow();
      return;
    }
  }
}

#if PL_HAS_SHIP_DEMO
/* another idea by Justin Rajewski (http://www.best-microcontroller-projects.com/polygon-graphics.html) */

static bool doCloseShipWindow = FALSE;

#define SHIP_COLOR_LINES         GDisp1_COLOR_BLACK
#define SHIP_COLOR_BACKGROUND    UI1_COLOR_BRIGHT_YELLOW

#define SHIP_NOF_LINES  41 /* number lines */
#define SHIP_NOF_VERTEX 23 /* number of corners */

/* X data */
static const signed int shipx [SHIP_NOF_VERTEX]={0, 5,-5, 5,-5,12,-12, 16,-16, 5,-5,11,-11, 5,-5, 1,-1, 3,-3,1,-1,2,-3} ;
/* Y data */
static const signed int shipy [SHIP_NOF_VERTEX]={0,-2,-2, 2, 2, 2,  2,  4,  4,-2,-2, 1,  1, 2, 2, -2,-2,-2,-2,-2,-2,-4,-4} ;
/* Z data */
static const signed int shipz [SHIP_NOF_VERTEX]={20,5, 5, 5, 5,-8, -8,-15,-15,-8,-8,-9, -9,-8,-8, 4, 4,-4,-4,-6,-6,-3,-3,} ;

/* start of lines */
const int shipls[SHIP_NOF_LINES]={1,1,1,1,3, 5,7,2, 4,6,8,10,11,3,2,13,12,14,14,15,15,14,14,15,11,10,3,5,16,17,19,21,20,18,22,22,22,22,23,23,23,}  ;
/* end of lines */
const int shiple[SHIP_NOF_LINES]={2,3,4,5,7,13,9,6,12,8,10,11,9,5,4, 9, 8,10,8,11,9,15,4,5,3,2,2,  4,17,19,21,20,18,16,16,18,20,23,17,19,21,}  ;

static portTASK_FUNCTION(Task3Dship, pvParameters) {
  // routine to draw and calc 3d object
  CUBE_WinParams *params;
  GDisp1_PixelDim sx,sy,ex,ey;  // vars for calling graphics subroutines
  byte i;                  // temp variable for loops
  float xt,yt,zt,x,y,z;
  float sinax,cosax,sinay,cosay,sinaz,cosaz,vertex;  // lots of work variables
  word rotx;      // starting amount of x rotation
  word roty;      // starting amount of y rotation
  word rotz;      // starting amount of z rotation
  word xpos;			// position for object in 3d space, in x
  word ypos;			// y
  word zpos;			// and z values
  GDisp1_PixelDim oldx[SHIP_NOF_VERTEX], newx[SHIP_NOF_VERTEX];      // translated screen x co-ordinates for vertex
  GDisp1_PixelDim oldy[SHIP_NOF_VERTEX], newy[SHIP_NOF_VERTEX];      // translated screen y co-ordinates for vertex

  params = (CUBE_WinParams*)pvParameters;

  for (i=0; i<SHIP_NOF_VERTEX; i++) { /* init previous cube drawing coordinates */
    oldx[i]=0;
    oldy[i]=0;
  }
  xpos=0;				// position for object in 3d space, in x
  ypos=0;				// y
  zpos=0;				// and z values
  rotx=0;       // starting amount of x rotation
  roty=0;       // starting amount of y rotation
  rotz=0;       // starting amount of z rotation
  for(;;) {
   #if 0
    xpos += 0;			// move the object
    ypos += 0;			// it would wander off screen
    zpos += 0;			// really quick, so leave it centered
   #endif
    rotx += 5;     // rotate the cube on X axis
    if (rotx>359) {
      rotx -= 360;
    }
    roty += 2;      // and on its y axis
    if (roty>359) {
      roty -= 360;
    }
    #if 0
    rotz += 0;     // Don't bother with z or it gets confusing
    #endif
    if (rotz>359) {
      rotz -= 360;
    }

    sinax=si[rotx];			// precalculate the sin and cos values
    cosax=co[rotx];			// for the rotation as this saves a 

    sinay=si[roty];			// little time when running as we
    cosay=co[roty];			// call sin and cos less often

    sinaz=si[rotz];			// they are slow routines
    cosaz=co[rotz];			// and we dont want slow!

    for (i=0; i<SHIP_NOF_VERTEX; i++) {
      // translate 3d vertex position to 2d screen position
      x=(float)(shipx[i]);         // get x for vertex i
      y=(float)(shipy[i]);         // get y for vertex i
      z=(float)(shipz[i]);         // get z for vertex i

      yt = y*cosax - z*sinax;	// rotate around the x axis
      zt = y*sinax + z*cosax;	// using the Y and Z for the rotation
      y = yt;
      z = zt;

      xt = x * cosay - z*sinay;	// rotate around the Y axis
      zt = x * sinay + z*cosay;	// using X and Z
      x = xt;
      z = zt;

      xt = x*cosaz - y*sinaz;	// finaly rotate around the Z axis
      yt = x*sinaz + y*cosaz;	// using X and Y
      x = xt;
      y = yt;

      x = (float)(x+xpos);			// add the object position offset
      y = (float)(y+ypos);			// for both x and y
      z = (float)(OFFSETZ-zpos);// as well as Z

      newx[i]=(GDisp1_PixelDim)((x*64/z)+UI1_GetElementWidth(&cubeParam.descP->windowShip)/2);	// translate 3d to 2d coordinates for screen
      newy[i]=(GDisp1_PixelDim)((y*64/z)+UI1_GetElementHeight(&cubeParam.descP->windowShip)/2);	// drawing so we can see the cube
    }
    for (i=0; i<SHIP_NOF_LINES; i++)	{
      /* clear previous line of the object */
      vertex=(float)(shipls[i]-1);// temp = start vertex for this line
      sx=oldx[(int)vertex];   // set line start x to vertex[i] x position
      sy=oldy[(int)vertex];   // set line start y to vertex[i] y position
      vertex=(float)(shiple[i]-1);// temp = end vertex for this line
      ex=oldx[(int)vertex];	  // set line end x to vertex[i+1] x position
      ey=oldy[(int)vertex];	  // set line end y to vertex[i+1] y position
      UI1_DrawLine(&cubeParam.descP->windowShip, sx, sy, ex, ey, SHIP_COLOR_BACKGROUND);		// draw the line between these 2 vertex
    }
    for (i=0; i<SHIP_NOF_LINES; i++)	{
      // draw the lines that make up the object
      vertex=(float)(shipls[i]-1);// temp = start vertex for this line
      sx=newx[(int)vertex];   // set line start x to vertex[i] x position
      sy=newy[(int)vertex];   // set line start y to vertex[i] y position
      vertex=(float)(shiple[i]-1);// temp = end vertex for this line
      ex=newx[(int)vertex];	  // set line end x to vertex[i+1] x position
      ey=newy[(int)vertex];	  // set line end y to vertex[i+1] y position
      UI1_DrawLine(&cubeParam.descP->windowShip, sx, sy, ex, ey, SHIP_COLOR_LINES);		// draw the line between these 2 vertex
    }
    for (i=0; i<SHIP_NOF_VERTEX; i++) { /* save values for next iteration */
      oldx[i]=newx[i];
      oldy[i]=newy[i];
    }
    if (doCloseShipWindow && EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) { /* request to close application */
      EVNT1_ClearEvent(EVNT1_APP_MODE_CHANGE); /* reset event flag */
      xHandleTask3Dship = NULL;
      FRTOS1_vTaskDelete(NULL); /* kill ourself */ 
    }
    vTaskDelay(pdMS_TO_TICKS(50)); /* give user a chance to see the cube rotating... */
  } /* for */
}
#endif /* PL_HAS_SHIP_DEMO */


#if PL_HAS_SHIP_DEMO
void CUBE_CloseShipWindow(void) {
  doCloseShipWindow = TRUE;
  EVNT1_SetEvent(EVNT1_APP_MODE_CHANGE); /* request to close application */
  while(EVNT1_GetEvent(EVNT1_APP_MODE_CHANGE)) {
    /* wait until task has killed itself */
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  (void)UI1_RemoveWindowPaintBackground(&cubeParam.descP->screen, &cubeParam.descP->windowShip);
  if (cubeParam.descP->screen.first==NULL) {
    /* we were the last window: close screen */
    APP_SetApplicationMode(APP_MODE_MAIN_MENU);
  }
}

static void shipW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &cubeParam.descP->iconCloseShip)) {
      CUBE_CloseShipWindow();
      return;
    }
  }
}
#endif /* PL_HAS_SHIP_DEMO */

static void CUBE_CreateScreen(void) {
  UI1_PixelDim h;

  UI1_CreateScreen(&cubeParam.descP->screen, UI1_COLOR_WHITE);
  
  /* Cube window */
  (void)UI1_CreateWindow(&cubeParam.descP->screen, &cubeParam.descP->windowCube, CUBE_COLOR_BACKGROUND, 10, 10, 130, 130);
  UI1_WindowSetBorder(&cubeParam.descP->windowCube);
  (void)UI1_CreateHeader(&cubeParam.descP->windowCube, &cubeParam.descP->headerCube, (unsigned char*)"3D Cube", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&cubeParam.descP->headerCube.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&cubeParam.descP->windowCube, cubeW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&cubeParam.descP->headerCube));
  (void)UI1_CreateIcon(&cubeParam.descP->windowCube, &cubeParam.descP->iconCloseCube, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  cubeParam.descP->iconCloseCube.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&cubeParam.descP->windowCube); /* right align element(s) if needed */
  UI1_ChangeElementColor(&cubeParam.descP->iconCloseCube, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&cubeParam.descP->iconCloseCube, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&cubeParam.descP->iconCloseCube);

#if PL_HAS_SHIP_DEMO
{
  /* Ship window */
  UI1_DisplayOrientation orientation = UI1_GetDisplayOrientation();
  
  if (orientation==UI1_ORIENTATION_PORTRAIT180 || orientation==UI1_ORIENTATION_PORTRAIT) {
    (void)UI1_CreateWindow(&cubeParam.descP->screen, &cubeParam.descP->windowShip, SHIP_COLOR_BACKGROUND, 10, 150, 130, 130);
  } else {
    (void)UI1_CreateWindow(&cubeParam.descP->screen, &cubeParam.descP->windowShip, SHIP_COLOR_BACKGROUND, 150, 10, 130, 130);
  }
  UI1_WindowSetBorder(&cubeParam.descP->windowShip);
  (void)UI1_CreateHeader(&cubeParam.descP->windowShip, &cubeParam.descP->headerShip, (unsigned char*)"3D Ship", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&cubeParam.descP->headerShip.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&cubeParam.descP->windowShip, shipW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&cubeParam.descP->headerShip));
  (void)UI1_CreateIcon(&cubeParam.descP->windowShip, &cubeParam.descP->iconCloseShip, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  cubeParam.descP->iconCloseShip.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&cubeParam.descP->windowShip); /* right align element(s) if needed */
  UI1_ChangeElementColor(&cubeParam.descP->iconCloseShip, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&cubeParam.descP->iconCloseShip, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&cubeParam.descP->iconCloseShip);
}
#endif /* PL_HAS_SHIP_DEMO */

  /* update the screen */
  UI1_UpdateScreen(&cubeParam.descP->screen);
}

void CUBE_CreateWindow(CUBE_WindowDesc *desc) {
  cubeParam.descP = desc; /* store pointer */
  
  doCloseCubeWindow = FALSE;
  CUBE_CreateScreen();
  if (FRTOS1_xTaskCreate(Task3Dcube, "Cube", configMINIMAL_STACK_SIZE+80, &cubeParam, tskIDLE_PRIORITY+3, NULL)!=pdPASS) {
    for(;;) {} /* out of memory? */
  }
#if PL_HAS_SHIP_DEMO
  doCloseShipWindow = FALSE;
  /* Start space ship task */
  if (xTaskCreate(Task3Dship, "Ship", configMINIMAL_STACK_SIZE+80, &cubeParam, tskIDLE_PRIORITY+3, &xHandleTask3Dship)!=pdPASS) {
    /* task creation failed */
    for(;;) {} /* out of memory? */
  }
#endif
}

void CUBE_StopTask(TaskHandle_t task) {
  GDisp1_GetDisplay();
  FRTOS1_vTaskSuspend(task);
  GDisp1_GiveDisplay();
}

void CUBE_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event) {
  (void)screen;
  (void)window;
  (void)element;
  switch(event) {
    case UI1_EVENT_ORIENTATION_CHANGE:
     #if PL_HAS_SHIP_DEMO
     if (xHandleTask3Dship!= NULL) { /* only if we have the task started and running */
        UI1_DisplayOrientation orientation = UI1_GetDisplayOrientation();

        if (orientation==UI1_ORIENTATION_PORTRAIT180 || orientation==UI1_ORIENTATION_PORTRAIT) {
          cubeParam.descP->windowShip.prop.x = 10;
          cubeParam.descP->windowShip.prop.y = 150;
        } else {
          cubeParam.descP->windowShip.prop.x = 150;
          cubeParam.descP->windowShip.prop.y = 10;
        }
     } /* endif */
     #endif
     break;
  } /* switch */
}

#endif /* PL_HAS_CUBE_DEMO */


/* END Cube */
