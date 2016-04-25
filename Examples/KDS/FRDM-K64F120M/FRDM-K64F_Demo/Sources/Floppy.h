/*
 * Floppy.h
 *
 *  Created on: 14.04.2016
 *      Author: Erich Styger
 */

#ifndef FLOPPY_H_
#define FLOPPY_H_

#include "CLS1.h"

uint8_t FLOPPY_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void FLOPPY_OnInterrupt(void);

/* MIDI interface */
void FLOPPY_MIDI_SetBank(uint8_t channel, uint8_t value);
void FLOPPY_MIDI_NoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void FLOPPY_MIDI_NoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void FLOPPY_MIDI_SetInstrument(uint8_t channel, uint8_t instrument);
void FLOPPY_MIDI_SetVolume(uint8_t channel, uint8_t volume);
void FLOPPY_MIDI_SetPan(uint8_t channel, uint8_t pan);
void FLOPPY_MIDI_AllSoundOff(uint8_t channel);

void FLOPPY_SetOffset(int offset);
void FLOPPY_Init(void);

#endif /* FLOPPY_H_ */


