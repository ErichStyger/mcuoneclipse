/*
 * Midi.h
 *
 *  Created on: 19.04.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_MIDI_H_
#define SOURCES_MIDI_H_


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
#define MIDI_NOTE_Cm     0
#define MIDI_NOTE_Chm    1
#define MIDI_NOTE_Dm     2
#define MIDI_NOTE_Dhm    3
#define MIDI_NOTE_Em     4
#define MIDI_NOTE_Fm     5
#define MIDI_NOTE_Fhm    6
#define MIDI_NOTE_Gm     7
#define MIDI_NOTE_Ghm    8
#define MIDI_NOTE_Am     9
#define MIDI_NOTE_Ahm   10
#define MIDI_NOTE_Bm    11
/* Octave 0 */
#define MIDI_NOTE_C0    12
#define MIDI_NOTE_Ch0   13
#define MIDI_NOTE_D0    14
#define MIDI_NOTE_Dh0   15
#define MIDI_NOTE_E0    16
#define MIDI_NOTE_F0    17
#define MIDI_NOTE_Fh0   18
#define MIDI_NOTE_G0    19
#define MIDI_NOTE_Gh0   20
#define MIDI_NOTE_A0    21
#define MIDI_NOTE_Ah0   22
#define MIDI_NOTE_B0    23
/* Octave 1 */
#define MIDI_NOTE_C1    24
#define MIDI_NOTE_Ch1   25
#define MIDI_NOTE_D1    26
#define MIDI_NOTE_Dh1   27
#define MIDI_NOTE_E1    28
#define MIDI_NOTE_F1    29
#define MIDI_NOTE_Fh1   30
#define MIDI_NOTE_G1    31
#define MIDI_NOTE_Gh1   32
#define MIDI_NOTE_A1    33
#define MIDI_NOTE_Ah1   34
#define MIDI_NOTE_B1    35
/* Octave 2 */
#define MIDI_NOTE_C2    36
#define MIDI_NOTE_Ch2   37
#define MIDI_NOTE_D2    38
#define MIDI_NOTE_Dh2   39
#define MIDI_NOTE_E2    40
#define MIDI_NOTE_F2    41
#define MIDI_NOTE_Fh2   42
#define MIDI_NOTE_G2    43
#define MIDI_NOTE_Gh2   44
#define MIDI_NOTE_A2    45
#define MIDI_NOTE_Ah2   46
#define MIDI_NOTE_B2    47
/* Octave 3 */
#define MIDI_NOTE_C3    48
#define MIDI_NOTE_Ch3   49
#define MIDI_NOTE_D3    50
#define MIDI_NOTE_Dh3   51
#define MIDI_NOTE_E3    52
#define MIDI_NOTE_F3    53
#define MIDI_NOTE_Fh3   54
#define MIDI_NOTE_G3    55
#define MIDI_NOTE_Gh3   56
#define MIDI_NOTE_A3    57
#define MIDI_NOTE_Ah3   58
#define MIDI_NOTE_B3    59
/* Octave 4 */
#define MIDI_NOTE_C4    60
#define MIDI_NOTE_Ch4   61
#define MIDI_NOTE_D4    62
#define MIDI_NOTE_Dh4   63
#define MIDI_NOTE_E4    64
#define MIDI_NOTE_F4    65
#define MIDI_NOTE_Fh4   66
#define MIDI_NOTE_G4    67
#define MIDI_NOTE_Gh4   68
#define MIDI_NOTE_A4    69
#define MIDI_NOTE_Ah4   70
#define MIDI_NOTE_B4    71
/* Octave 5 */
#define MIDI_NOTE_C5    72
#define MIDI_NOTE_Ch5   73
#define MIDI_NOTE_D5    74
#define MIDI_NOTE_Dh5   75
#define MIDI_NOTE_E5    76
#define MIDI_NOTE_F5    77
#define MIDI_NOTE_Fh5   78
#define MIDI_NOTE_G5    79
#define MIDI_NOTE_Gh5   80
#define MIDI_NOTE_A5    81
#define MIDI_NOTE_Ah5   82
#define MIDI_NOTE_B5    83
/* Octave 6 */
#define MIDI_NOTE_C6    84
#define MIDI_NOTE_Ch6   85
#define MIDI_NOTE_D6    86
#define MIDI_NOTE_Dh6   87
#define MIDI_NOTE_E6    88
#define MIDI_NOTE_F6    89
#define MIDI_NOTE_Fh6   90
#define MIDI_NOTE_G6    91
#define MIDI_NOTE_Gh6   92
#define MIDI_NOTE_A6    93
#define MIDI_NOTE_Ah6   94
#define MIDI_NOTE_B6    95
/* Octave 7 */
#define MIDI_NOTE_C7    96
#define MIDI_NOTE_Ch7   97
#define MIDI_NOTE_D7    98
#define MIDI_NOTE_Dh7   99
#define MIDI_NOTE_E7   100
#define MIDI_NOTE_F7   101
#define MIDI_NOTE_Fh7  102
#define MIDI_NOTE_G7   103
#define MIDI_NOTE_Gh7  104
#define MIDI_NOTE_A7   105
#define MIDI_NOTE_Ah7  106
#define MIDI_NOTE_B7   107
/* Octave 8 */
#define MIDI_NOTE_C8   108
#define MIDI_NOTE_Ch8  109
#define MIDI_NOTE_D8   110
#define MIDI_NOTE_Dh8  111
#define MIDI_NOTE_E8   112
#define MIDI_NOTE_F8   113
#define MIDI_NOTE_Fh8  114
#define MIDI_NOTE_G8   115
#define MIDI_NOTE_Gh8  116
#define MIDI_NOTE_A8   117
#define MIDI_NOTE_Ah8  118
#define MIDI_NOTE_B8   119
/* Octave 9 */
#define MIDI_NOTE_C9   120
#define MIDI_NOTE_Ch9  121
#define MIDI_NOTE_D9   122
#define MIDI_NOTE_Dh9  123
#define MIDI_NOTE_E9   124
#define MIDI_NOTE_F9   125
#define MIDI_NOTE_Fh9  126
#define MIDI_NOTE_G9   127

/* GM1 instruments */
#define MIDI_INSTR_Default               0
#define MIDI_INSTR_AcousticGrandPiano    1
#define MIDI_INSTR_PanFlute              76
#define MIDI_INSTR_GuitarFretNoise       121
#define MIDI_INSTR_BreatNoise            122
#define MIDI_INSTR_Seashore              123
#define MIDI_INSTR_BirdTweet             124
#define MIDI_INSTR_TelephoneRing         125
#define MIDI_INSTR_Helicopter            126
#define MIDI_INSTR_Applause              127
#define MIDI_INSTR_GunShot               128



#endif /* SOURCES_MIDI_H_ */
