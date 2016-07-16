/**
 * \file adc-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Board ADC driver implementation
 *
 */

#include "board.h"
#include "adc-board.h"

void AdcMcuInit(Adc_t *obj, PinNames adcInput)
{

}

void AdcMcuFormat(Adc_t *obj, AdcResolution AdcRes, AdcNumConversion AdcNumConv,
        AdcTriggerConv AdcTrig, AdcDataAlignement AdcDataAlig)
{

}

uint16_t AdcMcuRead(Adc_t *obj, uint8_t channel)
{
    return 0;

}
