/*
 * MusicMidiReady.c
 *
 *  Created on: 01.01.2015
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_MIDI
#include "MidiMusic.h"
#include "MidiMusicReady.h"
//#include "VS1.h"

/* http://www.sengpielaudio.com/calculator-notenames.htm
Octave #  MIDI Note Numbers
          C   C#  D   D#  E   F   F#  G   G#  A   A#  B
-1        0   1   2   3   4   5   6   7   8   9  10  11
0        12  13  14  15  16  17  18  19  20  21  22  23
1        24  25  26  27  28  29  30  31  32  33  34  35
2        36  37  38  39  40  41  42  43  44  45  46  47
3        48  49  50  51  52  53  54  55  56  57  58  59
4        60  61  62  63  64  65  66  67  68  69  70  71
5        72  73  74  75  76  77  78  79  80  81  82  83
6        84  85  86  87  88  89  90  91  92  93  94  95
7        96  97  98  99 100 101 102 103 104 105 106 107
8       108 109 110 111 112 113 114 115 116 117 118 119
9       120 121 122 123 124 125 126 127
*/
/* 'm' is for -1 octave, 'h' is for '#' */
/* Octave -1 */
#define VS1_MIDI_NOTE_Cm     0
#define VS1_MIDI_NOTE_Chm    1
#define VS1_MIDI_NOTE_Dm     2
#define VS1_MIDI_NOTE_Dhm    3
#define VS1_MIDI_NOTE_Em     4
#define VS1_MIDI_NOTE_Fm     5
#define VS1_MIDI_NOTE_Fhm    6
#define VS1_MIDI_NOTE_Gm     7
#define VS1_MIDI_NOTE_Ghm    8
#define VS1_MIDI_NOTE_Am     9
#define VS1_MIDI_NOTE_Ahm   10
#define VS1_MIDI_NOTE_Bm    11
/* Octave 0 */
#define VS1_MIDI_NOTE_C0    12
#define VS1_MIDI_NOTE_Ch0   13
#define VS1_MIDI_NOTE_D0    14
#define VS1_MIDI_NOTE_Dh0   15
#define VS1_MIDI_NOTE_E0    16
#define VS1_MIDI_NOTE_F0    17
#define VS1_MIDI_NOTE_Fh0   18
#define VS1_MIDI_NOTE_G0    19
#define VS1_MIDI_NOTE_Gh0   20
#define VS1_MIDI_NOTE_A0    21
#define VS1_MIDI_NOTE_Ah0   22
#define VS1_MIDI_NOTE_B0    23
/* Octave 1 */
#define VS1_MIDI_NOTE_C1    24
#define VS1_MIDI_NOTE_Ch1   25
#define VS1_MIDI_NOTE_D1    26
#define VS1_MIDI_NOTE_Dh1   27
#define VS1_MIDI_NOTE_E1    28
#define VS1_MIDI_NOTE_F1    29
#define VS1_MIDI_NOTE_Fh1   30
#define VS1_MIDI_NOTE_G1    31
#define VS1_MIDI_NOTE_Gh1   32
#define VS1_MIDI_NOTE_A1    33
#define VS1_MIDI_NOTE_Ah1   34
#define VS1_MIDI_NOTE_B1    35
/* Octave 2 */
#define VS1_MIDI_NOTE_C2    36
#define VS1_MIDI_NOTE_Ch2   37
#define VS1_MIDI_NOTE_D2    38
#define VS1_MIDI_NOTE_Dh2   39
#define VS1_MIDI_NOTE_E2    40
#define VS1_MIDI_NOTE_F2    41
#define VS1_MIDI_NOTE_Fh2   42
#define VS1_MIDI_NOTE_G2    43
#define VS1_MIDI_NOTE_Gh2   44
#define VS1_MIDI_NOTE_A2    45
#define VS1_MIDI_NOTE_Ah2   46
#define VS1_MIDI_NOTE_B2    47
/* Octave 3 */
#define VS1_MIDI_NOTE_C3    48
#define VS1_MIDI_NOTE_Ch3   49
#define VS1_MIDI_NOTE_D3    50
#define VS1_MIDI_NOTE_Dh3   51
#define VS1_MIDI_NOTE_E3    52
#define VS1_MIDI_NOTE_F3    53
#define VS1_MIDI_NOTE_Fh3   54
#define VS1_MIDI_NOTE_G3    55
#define VS1_MIDI_NOTE_Gh3   56
#define VS1_MIDI_NOTE_A3    57
#define VS1_MIDI_NOTE_Ah3   58
#define VS1_MIDI_NOTE_B3    59
/* Octave 4 */
#define VS1_MIDI_NOTE_C4    60
#define VS1_MIDI_NOTE_Ch4   61
#define VS1_MIDI_NOTE_D4    62
#define VS1_MIDI_NOTE_Dh4   63
#define VS1_MIDI_NOTE_E4    64
#define VS1_MIDI_NOTE_F4    65
#define VS1_MIDI_NOTE_Fh4   66
#define VS1_MIDI_NOTE_G4    67
#define VS1_MIDI_NOTE_Gh4   68
#define VS1_MIDI_NOTE_A4    69
#define VS1_MIDI_NOTE_Ah4   70
#define VS1_MIDI_NOTE_B4    71
/* Octave 5 */
#define VS1_MIDI_NOTE_C5    72
#define VS1_MIDI_NOTE_Ch5   73
#define VS1_MIDI_NOTE_D5    74
#define VS1_MIDI_NOTE_Dh5   75
#define VS1_MIDI_NOTE_E5    76
#define VS1_MIDI_NOTE_F5    77
#define VS1_MIDI_NOTE_Fh5   78
#define VS1_MIDI_NOTE_G5    79
#define VS1_MIDI_NOTE_Gh5   80
#define VS1_MIDI_NOTE_A5    81
#define VS1_MIDI_NOTE_Ah5   82
#define VS1_MIDI_NOTE_B5    83
/* Octave 6 */
#define VS1_MIDI_NOTE_C6    84
#define VS1_MIDI_NOTE_Ch6   85
#define VS1_MIDI_NOTE_D6    86
#define VS1_MIDI_NOTE_Dh6   87
#define VS1_MIDI_NOTE_E6    88
#define VS1_MIDI_NOTE_F6    89
#define VS1_MIDI_NOTE_Fh6   90
#define VS1_MIDI_NOTE_G6    91
#define VS1_MIDI_NOTE_Gh6   92
#define VS1_MIDI_NOTE_A6    93
#define VS1_MIDI_NOTE_Ah6   94
#define VS1_MIDI_NOTE_B6    95
/* Octave 7 */
#define VS1_MIDI_NOTE_C7    96
#define VS1_MIDI_NOTE_Ch7   97
#define VS1_MIDI_NOTE_D7    98
#define VS1_MIDI_NOTE_Dh7   99
#define VS1_MIDI_NOTE_E7   100
#define VS1_MIDI_NOTE_F7   101
#define VS1_MIDI_NOTE_Fh7  102
#define VS1_MIDI_NOTE_G7   103
#define VS1_MIDI_NOTE_Gh7  104
#define VS1_MIDI_NOTE_A7   105
#define VS1_MIDI_NOTE_Ah7  106
#define VS1_MIDI_NOTE_B7   107
/* Octave 8 */
#define VS1_MIDI_NOTE_C8   108
#define VS1_MIDI_NOTE_Ch8  109
#define VS1_MIDI_NOTE_D8   110
#define VS1_MIDI_NOTE_Dh8  111
#define VS1_MIDI_NOTE_E8   112
#define VS1_MIDI_NOTE_F8   113
#define VS1_MIDI_NOTE_Fh8  114
#define VS1_MIDI_NOTE_G8   115
#define VS1_MIDI_NOTE_Gh8  116
#define VS1_MIDI_NOTE_A8   117
#define VS1_MIDI_NOTE_Ah8  118
#define VS1_MIDI_NOTE_B8   119
/* Octave 9 */
#define VS1_MIDI_NOTE_C9   120
#define VS1_MIDI_NOTE_Ch9  121
#define VS1_MIDI_NOTE_D9   122
#define VS1_MIDI_NOTE_Dh9  123
#define VS1_MIDI_NOTE_E9   124
#define VS1_MIDI_NOTE_F9   125
#define VS1_MIDI_NOTE_Fh9  126
#define VS1_MIDI_NOTE_G9   127

/* GM1 instruments */
#define VS1_MIDI_INSTR_Default               0
#define VS1_MIDI_INSTR_AcousticGrandPiano    1
#define VS1_MIDI_INSTR_PanFlute              76
#define VS1_MIDI_INSTR_GuitarFretNoise       121
#define VS1_MIDI_INSTR_BreatNoise            122
#define VS1_MIDI_INSTR_Seashore              123
#define VS1_MIDI_INSTR_BirdTweet             124
#define VS1_MIDI_INSTR_TelephoneRing         125
#define VS1_MIDI_INSTR_Helicopter            126
#define VS1_MIDI_INSTR_Applause              127
#define VS1_MIDI_INSTR_GunShot               128


#define NOF_TRACKS                  2  /* this music has two tracks */
#define NOF_TICKS_PER_QUARTER_NOTE  0x180 /* see http://www.ccarh.org/courses/253/assignment/midifile/ */

static const MIDI_MusicLine track0[] =
{
/* beat,ticks, event,          note,              value */
  {0,  0, MIDI_BANK,      0, 0},
  {0,  0, MIDI_PATCH,     VS1_MIDI_INSTR_Default, 0},
  {0,  0, MIDI_PAN,       64, 0},
  {0,  0, MIDI_VOLUME,    127, 0},
  {0,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Fh6, 127},
  {0, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Fh6, 100},
  {0, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {0,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {0,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {0,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {0,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {0,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {1,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Fh5, 127},
  {1, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Fh5, 100},
  {1, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {1,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {1,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {1,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {1,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {1,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {2,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Fh4, 127},
  {2, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Fh4, 100},
  {2, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {2,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {2,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {2,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {2,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {2,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {3,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {3,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {3,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {3,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {4,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {4, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {4, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {4,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {4,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {4,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {5, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {5,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {5,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {5,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {6,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G6 , 127},
  {6, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G6 , 100},
  {6, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_A6 , 127},
  {6,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_A6 , 100},
  {6,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {6,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {6,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {6,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {7,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_E6 , 127},
  {7, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_E6 , 100},
  {7,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {7,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {7,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C6 , 127},
  {7,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C6 , 100},
  {8, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ch6, 127},
  {8,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ch6, 100},
  {8,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {8,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {9, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ch6, 127},
  {9,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ch6, 100},
  {9,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G5 , 127},
  {9,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G5 , 100},
  {10,  0, MIDI_NOTE_ON,   VS1_MIDI_NOTE_Ch6, 127},
  {10, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ch6, 100},
  {10,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {10,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {10,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {10,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {11,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_D6 , 127},
  {11,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_D6 , 100},
  {11,256, MIDI_END_OF_TRACK, 0,  0}
};

static const MIDI_MusicLine track1[] =
{
/* beat,ticks, event,          note,              value */
  {0,  0, MIDI_BANK,      0, 0},
  {0,  0, MIDI_PATCH ,    VS1_MIDI_INSTR_Default, 0},
  {0,  0, MIDI_PAN,       64,                  0},
  {0,  0, MIDI_VOLUME,    127,                 0},
  {3,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {3,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {3,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_A4 , 127},
  {3,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_A4 , 100},
  {4,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_B4 , 127},
  {4, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_B4 , 100},
  {4, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {4,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {4,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {4,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {4,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {4,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {5,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {5, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {5, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {5,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {5,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {5,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {5,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {5,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {6,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {6, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {6, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {6,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {6,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {6,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {6,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {6,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {7,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {7, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {7, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {7,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {7,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {7,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {7,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_C5 , 127},
  {7,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_C5 , 100},
  {8,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {8, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {8, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {8,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {8,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {8,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {8,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {8,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {9,  0, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {9, 64, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {9, 96, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {9,160, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {9,192, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_G4 , 127},
  {9,256, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_G4 , 100},
  {9,288, MIDI_NOTE_ON ,  VS1_MIDI_NOTE_Ah4, 127},
  {9,352, MIDI_NOTE_OFF,  VS1_MIDI_NOTE_Ah4, 100},
  {10,  0, MIDI_NOTE_ON,  VS1_MIDI_NOTE_G4,  127},
  {10, 64, MIDI_NOTE_OFF, VS1_MIDI_NOTE_G4,  100},
  {10, 96, MIDI_NOTE_ON , VS1_MIDI_NOTE_B4,  127},
  {10,160, MIDI_NOTE_OFF, VS1_MIDI_NOTE_B4,  100},
  {10,192, MIDI_NOTE_ON , VS1_MIDI_NOTE_G4,  127},
  {10,256, MIDI_NOTE_OFF, VS1_MIDI_NOTE_G4,  100},
  {10,288, MIDI_NOTE_ON , VS1_MIDI_NOTE_B4,  127},
  {10,352, MIDI_NOTE_OFF, VS1_MIDI_NOTE_B4,  100},
  {11,  0, MIDI_NOTE_ON , VS1_MIDI_NOTE_G4,  127},
  {11,256, MIDI_NOTE_OFF, VS1_MIDI_NOTE_G4,  100},
  {11,256, MIDI_END_OF_TRACK, 0,  0}
};

uint8_t MMReady_GetMidiMusicInfo(MIDI_MusicTrack *tracks, uint8_t nofTracks) {

  if (nofTracks>NOF_TRACKS) {
    return ERR_OVERFLOW; /* not enough tracks available */
  }
  tracks[0].lines = &track0[0];
  tracks[0].nofLines = sizeof(track0)/sizeof(track0[0]);
  tracks[0].currLine = 0;
  tracks[0].nofTicksPerQuarterNote = NOF_TICKS_PER_QUARTER_NOTE;
  tracks[1].lines = &track1[0];
  tracks[1].nofLines = sizeof(track1)/sizeof(track1[0]);
  tracks[1].currLine = 0;
  tracks[1].nofTicksPerQuarterNote = NOF_TICKS_PER_QUARTER_NOTE;
  return ERR_OK;
}

#endif /* PL_HAS_MIDI */

