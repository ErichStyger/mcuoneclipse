/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_SystemSetupData.c
*
* @brief  Defines the structs and information needed for the configuration and decoders usage 
*
* @version 1.0.87.0
* 
* @date Sep-20-2012
* 
* All the declarations of structures and information are bassed in the values
* provided by the user in the SystemSetup.h file                             
*
***********************************************************************************************************************/


#include "TSS_SystemSetup.h"
#include "TSS_API.h"
#include "TSS_SystemSetupVal.h"
#include "derivative.h" 

/* Prototypes */

UINT16 TSS_IIRFilterEquation(UINT16 u16CurrentCapSample, UINT8 u8ElecNum);

/* Decoding macros */

#if TSS_ASLIDER_POSITION_IIR_USED
  #define TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_RESULT(res)     &TSS_C##res##_POSFILTER_CONTEXT
  #define TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_CONV(text)      TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_RESULT(text)
  #define TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(decoder)   TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_CONV(decoder)
#else
  #define TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(decoder)   NULL
#endif

#if TSS_ASLIDER_DELAY_USED
  #define TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_RESULT(res)     &TSS_C##res##_DELAY_CONTEXT
  #define TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_CONV(text)      TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_RESULT(text)
  #define TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(decoder)   TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_CONV(decoder)

  #define TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_RESULT(res)      TSS_C##res##_DELAY_BUFFER
  #define TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_CONV(text)       TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_RESULT(text)
  #define TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(decoder)    TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_CONV(decoder)
#else
  #define TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(decoder)   NULL
  #define TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(decoder)    NULL
#endif

#if TSS_ASLIDER_TREND_USED
  #define TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_RESULT(res)     &TSS_C##res##_TREND_CONTEXT
  #define TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_CONV(text)      TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_RESULT(text)
  #define TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(decoder)   TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_CONV(decoder)

  #define TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_RESULT(res)      TSS_C##res##_TREND_BUFFER
  #define TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_CONV(text)       TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_RESULT(text)
  #define TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(decoder)    TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_CONV(decoder)
#else
  #define TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(decoder)   NULL
  #define TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(decoder)    NULL
#endif

#if TSS_MATRIX_POSITION_IIR_USED
  #define TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_RESULT(res)     &TSS_C##res##_MATRIX_POSFILTER_IIR_CONTEXT
  #define TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_CONV(text)      TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_RESULT(text)
  #define TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(decoder)   TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_CONV(decoder)
#else
  #define TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(decoder)   NULL
#endif

/* The section below declares all the structures needed for each decoder */

#if TSS_N_CONTROLS > 0
    #if (TSS_C0_TYPE == TSS_CT_KEYPAD)                  /* Validates the Controler Type */
        UINT8 TSS_C0_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE]; /* Declares Events Buffer for Keypad */    
        #ifdef TSS_C0_KEYS
        const UINT16 TSS_C0_KEYS_GROUP[] = TSS_C0_KEYS;
        #define TSS_C0_KEYS_COUNT sizeof(TSS_C0_KEYS_GROUP)/sizeof(TSS_C0_KEYS_GROUP[0])
        #else
        #define TSS_C0_KEYS_GROUP NULL
        #define TSS_C0_KEYS_COUNT TSS_C0_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C0_STRUCTURE = { {0u, TSS_C0_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C0_KEYPAD_EVENTS_BUFFER}; /* Declares the control KeyPad Structure */
        TSS_KeypadContext TSS_C0_STRUCTURE_CONTEXT = { 0u, TSS_C0_KEYS_GROUP, 0u,0u, TSS_C0_KEYS_COUNT};     /* Declares the context KeyPad Structure */
        #define C0_DECODER      TSS_KeypadDecoder       /* Defines a reference constant for the Decoder type function */
    #elif (TSS_C0_TYPE == TSS_CT_SLIDER)                /* Validates the Controler Type */
        TSS_CSSlider TSS_C0_STRUCTURE = { {0u, TSS_C0_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u}; /* Declares the control Slider Structure */
        TSS_SingleContext TSS_C0_STRUCTURE_CONTEXT;     /* Declares the context Slider Structure */
        #define C0_DECODER      TSS_SliderDecoder       /* Defines a reference constant for the Decoder type functions */       
    #elif (TSS_C0_TYPE == TSS_CT_ROTARY)                /* Validates the Controler Type */
        TSS_CSRotary TSS_C0_STRUCTURE = { {0u, TSS_C0_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u}; /* Declares the control Rotary Structure */
        TSS_SingleContext TSS_C0_STRUCTURE_CONTEXT;     /* Declares the context Rotary Structure */
        #define C0_DECODER      TSS_SliderDecoder       /* Defines a reference constant for the Decoder type functions */
    #elif (TSS_C0_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C0_STRUCTURE = { {0u, TSS_C0_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };        
        TSS_MatrixTouchContext TSS_C0_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C0_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C0_STRUCTURE_CONTEXT = { TSS_C0_ELECTRODES_X, TSS_C0_ELECTRODES_Y,
                                                             &TSS_C0_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(0) };
        #define C0_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C0_TYPE == TSS_CT_ASLIDER)               
        TSS_CSASlider TSS_C0_STRUCTURE = { {0u, TSS_C0_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u}; /* Declares the control ASlider Structure */
      #else
        TSS_CSARotary TSS_C0_STRUCTURE = { {0u, TSS_C0_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u}; /* Declares the control ARotary Structure */
      #endif
        TSS_ASliderPosFilterContext TSS_C0_POSFILTER_CONTEXT;        /* Declares PosFilter contex struture for ASlider/ARotary */
        TSS_ASliderDelayContext TSS_C0_DELAY_CONTEXT;                /* Declares Delay contex struture for ASlider/ARotary */
        TSS_ASliderTrendContext TSS_C0_TREND_CONTEXT;                /* Declares Trend contex struture for ASlider/ARotary */
        UINT8 TSS_C0_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];  /* Declares Delay buffer for ASlider/ARotary */
        INT8 TSS_C0_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];   /* Declares Delay buffer for ASlider/ARotary */
        const TSS_ASliderContext TSS_C0_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(0),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(0),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(0),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(0),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(0)
                                                            };     /* Declares the context ASlider Structure */
        #define C0_DECODER      TSS_ASliderDecoder      /* Defines a reference constant for the Decoder type functions */
    #endif
    void TSS_C0_CALLBACK(TSS_CONTROL_ID u8ControlId);            /* Declares the callback fucntion */
    UINT8 C0_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command); /* Declares the decoder type function */
#endif

/* Depending on the number of controls declared by the user the strcutures are created */
#if TSS_N_CONTROLS > 1
    #if (TSS_C1_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C1_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C1_KEYS
          const UINT16 TSS_C1_KEYS_GROUP[] = TSS_C1_KEYS;
          #define TSS_C1_KEYS_COUNT sizeof(TSS_C1_KEYS_GROUP)/sizeof(TSS_C1_KEYS_GROUP[0])
        #else
          #define TSS_C1_KEYS_GROUP NULL
          #define TSS_C1_KEYS_COUNT TSS_C1_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C1_STRUCTURE = { {1u, TSS_C1_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C1_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C1_STRUCTURE_CONTEXT = { 0u, TSS_C1_KEYS_GROUP, 0u,0u, TSS_C1_KEYS_COUNT}; 
        #define C1_DECODER      TSS_KeypadDecoder
    #elif (TSS_C1_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C1_STRUCTURE = { {1u, TSS_C1_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C1_STRUCTURE_CONTEXT;
        #define C1_DECODER      TSS_SliderDecoder
    #elif (TSS_C1_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C1_STRUCTURE = { {1u, TSS_C1_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C1_STRUCTURE_CONTEXT;
        #define C1_DECODER      TSS_SliderDecoder
    #elif (TSS_C1_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C1_STRUCTURE = { {1u, TSS_C1_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C1_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C1_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C1_STRUCTURE_CONTEXT = { TSS_C1_ELECTRODES_X, TSS_C1_ELECTRODES_Y,
                                                             &TSS_C1_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(1) };
        #define C1_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C1_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C1_STRUCTURE = { {1u, TSS_C1_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C1_STRUCTURE = { {1u, TSS_C1_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C1_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C1_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C1_TREND_CONTEXT;
        UINT8 TSS_C1_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C1_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C1_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(1),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(1),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(1),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(1),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(1)
                                                            };     /* Declares the context ASlider Structure */
        #define C1_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C1_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C1_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 2
    #if (TSS_C2_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C2_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C2_KEYS
          const UINT16 TSS_C2_KEYS_GROUP[] = TSS_C2_KEYS;
          #define TSS_C2_KEYS_COUNT sizeof(TSS_C2_KEYS_GROUP)/sizeof(TSS_C2_KEYS_GROUP[0])
        #else
          #define TSS_C2_KEYS_GROUP NULL
          #define TSS_C2_KEYS_COUNT TSS_C2_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C2_STRUCTURE = { {2u, TSS_C2_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C2_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C2_STRUCTURE_CONTEXT = { 0u, TSS_C2_KEYS_GROUP, 0u,0u, TSS_C2_KEYS_COUNT}; 
        #define C2_DECODER      TSS_KeypadDecoder
    #elif (TSS_C2_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C2_STRUCTURE = { {2u, TSS_C2_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C2_STRUCTURE_CONTEXT;
        #define C2_DECODER      TSS_SliderDecoder
    #elif (TSS_C2_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C2_STRUCTURE = { {2u, TSS_C2_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C2_STRUCTURE_CONTEXT;
        #define C2_DECODER      TSS_SliderDecoder
    #elif (TSS_C2_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C2_STRUCTURE = { {2u, TSS_C2_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C2_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C2_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C2_STRUCTURE_CONTEXT = { TSS_C2_ELECTRODES_X, TSS_C2_ELECTRODES_Y,
                                                             &TSS_C2_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(2) };
        #define C2_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C2_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C2_STRUCTURE = { {2u, TSS_C2_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C2_STRUCTURE = { {2u, TSS_C2_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C2_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C2_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C2_TREND_CONTEXT;
        UINT8 TSS_C2_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C2_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C2_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(2),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(2),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(2),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(2),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(2)
                                                            };     /* Declares the context ASlider Structure */
        #define C2_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C2_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C2_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 3
    #if (TSS_C3_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C3_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C3_KEYS
          const UINT16 TSS_C3_KEYS_GROUP[] = TSS_C3_KEYS;
          #define TSS_C3_KEYS_COUNT sizeof(TSS_C3_KEYS_GROUP)/sizeof(TSS_C3_KEYS_GROUP[0])
        #else
          #define TSS_C3_KEYS_GROUP NULL
          #define TSS_C3_KEYS_COUNT TSS_C3_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C3_STRUCTURE = { {3u, TSS_C3_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C3_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C3_STRUCTURE_CONTEXT = { 0u, TSS_C3_KEYS_GROUP, 0u,0u, TSS_C3_KEYS_COUNT}; 
        #define C3_DECODER      TSS_KeypadDecoder
    #elif (TSS_C3_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C3_STRUCTURE = { {3u, TSS_C3_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C3_STRUCTURE_CONTEXT;
        #define C3_DECODER      TSS_SliderDecoder
    #elif (TSS_C3_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C3_STRUCTURE = { {3u, TSS_C3_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C3_STRUCTURE_CONTEXT;
        #define C3_DECODER      TSS_SliderDecoder
    #elif (TSS_C3_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C3_STRUCTURE = { {3u, TSS_C3_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C3_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C3_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C3_STRUCTURE_CONTEXT = { TSS_C3_ELECTRODES_X, TSS_C3_ELECTRODES_Y,
                                                             &TSS_C3_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(3) };
        #define C3_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C3_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C3_STRUCTURE = { {3u, TSS_C3_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C3_STRUCTURE = { {3u, TSS_C3_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C3_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C3_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C3_TREND_CONTEXT;
        UINT8 TSS_C3_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C3_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C3_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(3),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(3),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(3),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(3),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(3)
                                                            };     /* Declares the context ASlider Structure */
        #define C3_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C3_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C3_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 4
    #if (TSS_C4_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C4_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C4_KEYS
          const UINT16 TSS_C4_KEYS_GROUP[] = TSS_C4_KEYS;
          #define TSS_C4_KEYS_COUNT sizeof(TSS_C4_KEYS_GROUP)/sizeof(TSS_C4_KEYS_GROUP[0])
        #else
          #define TSS_C4_KEYS_GROUP NULL
          #define TSS_C4_KEYS_COUNT TSS_C4_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C4_STRUCTURE = { {4u, TSS_C4_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C4_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C4_STRUCTURE_CONTEXT = { 0u, TSS_C4_KEYS_GROUP, 0u,0u, TSS_C4_KEYS_COUNT}; 
        #define C4_DECODER      TSS_KeypadDecoder
    #elif (TSS_C4_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C4_STRUCTURE = { {4u, TSS_C4_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C4_STRUCTURE_CONTEXT;
        #define C4_DECODER      TSS_SliderDecoder
    #elif (TSS_C4_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C4_STRUCTURE = { {4u, TSS_C4_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C4_STRUCTURE_CONTEXT;
        #define C4_DECODER      TSS_SliderDecoder
    #elif (TSS_C4_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C4_STRUCTURE = { {4u, TSS_C4_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C4_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C4_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C4_STRUCTURE_CONTEXT = { TSS_C4_ELECTRODES_X, TSS_C4_ELECTRODES_Y,
                                                             &TSS_C4_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(4) };
        #define C4_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C4_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C4_STRUCTURE = { {4u, TSS_C4_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C4_STRUCTURE = { {4u, TSS_C4_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C4_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C4_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C4_TREND_CONTEXT;
        UINT8 TSS_C4_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C4_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C4_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(4),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(4),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(4),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(4),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(4)
                                                            };     /* Declares the context ASlider Structure */
        #define C4_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C4_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C4_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 5
    #if (TSS_C5_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C5_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C5_KEYS
          const UINT16 TSS_C5_KEYS_GROUP[] = TSS_C5_KEYS;
          #define TSS_C5_KEYS_COUNT sizeof(TSS_C5_KEYS_GROUP)/sizeof(TSS_C5_KEYS_GROUP[0])
        #else
          #define TSS_C5_KEYS_GROUP NULL
          #define TSS_C5_KEYS_COUNT TSS_C5_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C5_STRUCTURE = { {5u, TSS_C5_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C5_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C5_STRUCTURE_CONTEXT = { 0u, TSS_C5_KEYS_GROUP, 0u,0u, TSS_C5_KEYS_COUNT}; 
        #define C5_DECODER      TSS_KeypadDecoder
    #elif (TSS_C5_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C5_STRUCTURE = { {5u, TSS_C5_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C5_STRUCTURE_CONTEXT;
        #define C5_DECODER      TSS_SliderDecoder
    #elif (TSS_C5_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C5_STRUCTURE = { {5u, TSS_C5_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C5_STRUCTURE_CONTEXT;
        #define C5_DECODER      TSS_SliderDecoder
    #elif (TSS_C5_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C5_STRUCTURE = { {5u, TSS_C5_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C5_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C5_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C5_STRUCTURE_CONTEXT = { TSS_C5_ELECTRODES_X, TSS_C5_ELECTRODES_Y,
                                                             &TSS_C5_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(5) };
        #define C5_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C5_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C5_STRUCTURE = { {5u, TSS_C5_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C5_STRUCTURE = { {5u, TSS_C5_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C5_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C5_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C5_TREND_CONTEXT;
        UINT8 TSS_C5_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C5_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C5_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(5),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(5),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(5),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(5),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(5)
                                                            };     /* Declares the context ASlider Structure */
        #define C5_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C5_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C5_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 6
    #if (TSS_C6_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C6_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C6_KEYS
          const UINT16 TSS_C6_KEYS_GROUP[] = TSS_C6_KEYS;
          #define TSS_C6_KEYS_COUNT sizeof(TSS_C6_KEYS_GROUP)/sizeof(TSS_C6_KEYS_GROUP[0])
        #else
          #define TSS_C6_KEYS_GROUP NULL
          #define TSS_C6_KEYS_COUNT TSS_C6_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C6_STRUCTURE = { {6u, TSS_C6_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C6_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C6_STRUCTURE_CONTEXT = { 0u, TSS_C6_KEYS_GROUP, 0u,0u, TSS_C6_KEYS_COUNT}; 
        #define C6_DECODER      TSS_KeypadDecoder
    #elif (TSS_C6_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C6_STRUCTURE = { {6u, TSS_C6_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C6_STRUCTURE_CONTEXT;
        #define C6_DECODER      TSS_SliderDecoder
    #elif (TSS_C6_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C6_STRUCTURE = { {6u, TSS_C6_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C6_STRUCTURE_CONTEXT;
        #define C6_DECODER      TSS_SliderDecoder
    #elif (TSS_C6_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C6_STRUCTURE = { {6u, TSS_C6_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C6_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C6_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C6_STRUCTURE_CONTEXT = { TSS_C6_ELECTRODES_X, TSS_C6_ELECTRODES_Y,
                                                             &TSS_C6_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(6) };
        #define C6_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C6_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C6_STRUCTURE = { {6u, TSS_C6_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C6_STRUCTURE = { {6u, TSS_C6_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C6_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C6_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C6_TREND_CONTEXT;
        UINT8 TSS_C6_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C6_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C6_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(6),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(6),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(6),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(6),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(6)
                                                            };     /* Declares the context ASlider Structure */
        #define C6_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C6_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C6_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 7
    #if (TSS_C7_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C7_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C7_KEYS
          const UINT16 TSS_C7_KEYS_GROUP[] = TSS_C7_KEYS;
          #define TSS_C7_KEYS_COUNT sizeof(TSS_C7_KEYS_GROUP)/sizeof(TSS_C7_KEYS_GROUP[0])
        #else
          #define TSS_C7_KEYS_GROUP NULL
          #define TSS_C7_KEYS_COUNT TSS_C7_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C7_STRUCTURE = { {7u, TSS_C7_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C7_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C7_STRUCTURE_CONTEXT = { 0u, TSS_C7_KEYS_GROUP, 0u,0u, TSS_C7_KEYS_COUNT}; 
        #define C7_DECODER      TSS_KeypadDecoder
    #elif (TSS_C7_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C7_STRUCTURE = { {7u, TSS_C7_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C7_STRUCTURE_CONTEXT;
        #define C7_DECODER      TSS_SliderDecoder
    #elif (TSS_C7_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C7_STRUCTURE = { {7u, TSS_C7_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C7_STRUCTURE_CONTEXT;
        #define C7_DECODER      TSS_SliderDecoder
    #elif (TSS_C7_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C7_STRUCTURE = { {7u, TSS_C7_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C7_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C7_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C7_STRUCTURE_CONTEXT = { TSS_C7_ELECTRODES_X, TSS_C7_ELECTRODES_Y,
                                                             &TSS_C7_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(7) };
        #define C7_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C7_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C7_STRUCTURE = { {7u, TSS_C7_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C7_STRUCTURE = { {7u, TSS_C7_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C7_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C7_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C7_TREND_CONTEXT;
        UINT8 TSS_C7_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C7_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C7_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(7),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(7),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(7),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(7),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(7)
                                                            };     /* Declares the context ASlider Structure */
        #define C7_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C7_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C7_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 8
    #if (TSS_C8_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C8_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C8_KEYS
          const UINT16 TSS_C8_KEYS_GROUP[] = TSS_C8_KEYS;
          #define TSS_C8_KEYS_COUNT sizeof(TSS_C8_KEYS_GROUP)/sizeof(TSS_C8_KEYS_GROUP[0])
        #else
          #define TSS_C8_KEYS_GROUP NULL
          #define TSS_C8_KEYS_COUNT TSS_C8_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C8_STRUCTURE = { {8u, TSS_C8_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C8_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C8_STRUCTURE_CONTEXT = { 0u, TSS_C8_KEYS_GROUP, 0u,0u, TSS_C8_KEYS_COUNT}; 
        #define C8_DECODER      TSS_KeypadDecoder
    #elif (TSS_C8_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C8_STRUCTURE = { {8u, TSS_C8_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C8_STRUCTURE_CONTEXT;
        #define C8_DECODER      TSS_SliderDecoder
    #elif (TSS_C8_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C8_STRUCTURE = { {8u, TSS_C8_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C8_STRUCTURE_CONTEXT;
        #define C8_DECODER      TSS_SliderDecoder
    #elif (TSS_C8_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C8_STRUCTURE = { {8u, TSS_C8_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C8_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C8_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C8_STRUCTURE_CONTEXT = { TSS_C8_ELECTRODES_X, TSS_C8_ELECTRODES_Y,
                                                             &TSS_C8_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(8) };
        #define C8_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C8_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C8_STRUCTURE = { {8u, TSS_C8_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C8_STRUCTURE = { {8u, TSS_C8_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C8_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C8_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C8_TREND_CONTEXT;
        UINT8 TSS_C8_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C8_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C8_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(8),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(8),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(8),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(8),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(8)
                                                            };     /* Declares the context ASlider Structure */
        #define C8_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C8_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C8_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 9
    #if (TSS_C9_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C9_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C9_KEYS
          const UINT16 TSS_C9_KEYS_GROUP[] = TSS_C9_KEYS;
          #define TSS_C9_KEYS_COUNT sizeof(TSS_C9_KEYS_GROUP)/sizeof(TSS_C9_KEYS_GROUP[0])
        #else
          #define TSS_C9_KEYS_GROUP NULL
          #define TSS_C9_KEYS_COUNT TSS_C9_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C9_STRUCTURE = { {9u, TSS_C9_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C9_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C9_STRUCTURE_CONTEXT = { 0u, TSS_C9_KEYS_GROUP, 0u,0u, TSS_C9_KEYS_COUNT}; 
        #define C9_DECODER      TSS_KeypadDecoder
    #elif (TSS_C9_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C9_STRUCTURE = { {9u, TSS_C9_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C9_STRUCTURE_CONTEXT;
        #define C9_DECODER      TSS_SliderDecoder
    #elif (TSS_C9_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C9_STRUCTURE = { {9u, TSS_C9_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C9_STRUCTURE_CONTEXT;
        #define C9_DECODER      TSS_SliderDecoder
    #elif (TSS_C9_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C9_STRUCTURE = { {9u, TSS_C9_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C9_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C9_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C9_STRUCTURE_CONTEXT = { TSS_C9_ELECTRODES_X, TSS_C9_ELECTRODES_Y,
                                                             &TSS_C9_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(9) };
        #define C9_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C9_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C9_STRUCTURE = { {9u, TSS_C9_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C9_STRUCTURE = { {9u, TSS_C9_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C9_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C9_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C9_TREND_CONTEXT;
        UINT8 TSS_C9_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C9_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C9_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(9),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(9),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(9),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(9),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(9)
                                                            };     /* Declares the context ASlider Structure */
        #define C9_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C9_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C9_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 10
    #if (TSS_C10_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C10_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C10_KEYS
          const UINT16 TSS_C10_KEYS_GROUP[] = TSS_C10_KEYS;
          #define TSS_C10_KEYS_COUNT sizeof(TSS_C10_KEYS_GROUP)/sizeof(TSS_C10_KEYS_GROUP[0])
        #else
          #define TSS_C10_KEYS_GROUP NULL
          #define TSS_C10_KEYS_COUNT TSS_C10_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C10_STRUCTURE = { {10u, TSS_C10_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C10_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C10_STRUCTURE_CONTEXT = { 0u, TSS_C10_KEYS_GROUP, 0u,0u, TSS_C10_KEYS_COUNT}; 
        #define C10_DECODER      TSS_KeypadDecoder
    #elif (TSS_C10_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C10_STRUCTURE = { {10u, TSS_C10_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C10_STRUCTURE_CONTEXT;
        #define C10_DECODER      TSS_SliderDecoder
    #elif (TSS_C10_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C10_STRUCTURE = { {10u, TSS_C10_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C10_STRUCTURE_CONTEXT;
        #define C10_DECODER      TSS_SliderDecoder
    #elif (TSS_C10_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C10_STRUCTURE = { {10u, TSS_C10_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C10_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C10_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C10_STRUCTURE_CONTEXT = { TSS_C10_ELECTRODES_X, TSS_C10_ELECTRODES_Y,
                                                             &TSS_C10_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(10) };
        #define C10_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C10_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C10_STRUCTURE = { {10u, TSS_C10_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C10_STRUCTURE = { {10u, TSS_C10_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C10_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C10_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C10_TREND_CONTEXT;
        UINT8 TSS_C10_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C10_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C10_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(10),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(10),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(10),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(10),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(10)
                                                            };     /* Declares the context ASlider Structure */
        #define C10_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C10_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C10_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 11
    #if (TSS_C11_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C11_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C11_KEYS
          const UINT16 TSS_C11_KEYS_GROUP[] = TSS_C11_KEYS;
          #define TSS_C11_KEYS_COUNT sizeof(TSS_C11_KEYS_GROUP)/sizeof(TSS_C11_KEYS_GROUP[0])
        #else
          #define TSS_C11_KEYS_GROUP NULL
          #define TSS_C11_KEYS_COUNT TSS_C11_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C11_STRUCTURE = { {11u, TSS_C11_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C11_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C11_STRUCTURE_CONTEXT = { 0u, TSS_C11_KEYS_GROUP, 0u,0u, TSS_C11_KEYS_COUNT}; 
        #define C11_DECODER      TSS_KeypadDecoder
    #elif (TSS_C11_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C11_STRUCTURE = { {11u, TSS_C11_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C11_STRUCTURE_CONTEXT;
        #define C11_DECODER      TSS_SliderDecoder
    #elif (TSS_C11_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C11_STRUCTURE = { {11u, TSS_C11_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C11_STRUCTURE_CONTEXT;
        #define C11_DECODER      TSS_SliderDecoder
    #elif (TSS_C11_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C11_STRUCTURE = { {11u, TSS_C11_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C11_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C11_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C11_STRUCTURE_CONTEXT = { TSS_C11_ELECTRODES_X, TSS_C11_ELECTRODES_Y,
                                                             &TSS_C11_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(11) };
        #define C11_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C11_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C11_STRUCTURE = { {11u, TSS_C11_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C11_STRUCTURE = { {11u, TSS_C11_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C11_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C11_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C11_TREND_CONTEXT;
        UINT8 TSS_C11_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C11_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C11_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(11),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(11),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(11),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(11),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(11)
                                                            };     /* Declares the context ASlider Structure */
        #define C11_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C11_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C11_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 12
    #if (TSS_C12_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C12_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C12_KEYS
          const UINT16 TSS_C12_KEYS_GROUP[] = TSS_C12_KEYS;
          #define TSS_C12_KEYS_COUNT sizeof(TSS_C12_KEYS_GROUP)/sizeof(TSS_C12_KEYS_GROUP[0])
        #else
          #define TSS_C12_KEYS_GROUP NULL
          #define TSS_C12_KEYS_COUNT TSS_C12_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C12_STRUCTURE = { {12u, TSS_C12_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C12_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C12_STRUCTURE_CONTEXT = { 0u, TSS_C12_KEYS_GROUP, 0u,0u, TSS_C12_KEYS_COUNT}; 
        #define C12_DECODER      TSS_KeypadDecoder
    #elif (TSS_C12_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C12_STRUCTURE = { {12u, TSS_C12_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C12_STRUCTURE_CONTEXT;
        #define C12_DECODER      TSS_SliderDecoder
    #elif (TSS_C12_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C12_STRUCTURE = { {12u, TSS_C12_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C12_STRUCTURE_CONTEXT;
        #define C12_DECODER      TSS_SliderDecoder
    #elif (TSS_C12_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C12_STRUCTURE = { {12u, TSS_C12_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C12_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C12_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C12_STRUCTURE_CONTEXT = { TSS_C12_ELECTRODES_X, TSS_C12_ELECTRODES_Y,
                                                             &TSS_C12_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(12) };
        #define C12_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C12_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C12_STRUCTURE = { {12u, TSS_C12_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C12_STRUCTURE = { {12u, TSS_C12_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C12_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C12_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C12_TREND_CONTEXT;
        UINT8 TSS_C12_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C12_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C12_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(12),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(12),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(12),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(12),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(12)
                                                            };     /* Declares the context ASlider Structure */
        #define C12_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C12_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C12_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 13
    #if (TSS_C13_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C13_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C13_KEYS
          const UINT16 TSS_C13_KEYS_GROUP[] = TSS_C13_KEYS;
          #define TSS_C13_KEYS_COUNT sizeof(TSS_C13_KEYS_GROUP)/sizeof(TSS_C13_KEYS_GROUP[0])
        #else
          #define TSS_C13_KEYS_GROUP NULL
          #define TSS_C13_KEYS_COUNT TSS_C13_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C13_STRUCTURE = { {13u, TSS_C13_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C13_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C13_STRUCTURE_CONTEXT = { 0u, TSS_C13_KEYS_GROUP, 0u,0u, TSS_C13_KEYS_COUNT}; 
        #define C13_DECODER      TSS_KeypadDecoder
    #elif (TSS_C13_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C13_STRUCTURE = { {13u, TSS_C13_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C13_STRUCTURE_CONTEXT;
        #define C13_DECODER      TSS_SliderDecoder
    #elif (TSS_C13_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C13_STRUCTURE = { {13u, TSS_C13_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C13_STRUCTURE_CONTEXT;
        #define C13_DECODER      TSS_SliderDecoder
    #elif (TSS_C13_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C13_STRUCTURE = { {13u, TSS_C13_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C13_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C13_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C13_STRUCTURE_CONTEXT = { TSS_C13_ELECTRODES_X, TSS_C13_ELECTRODES_Y,
                                                             &TSS_C13_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(13) };
        #define C13_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C13_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C13_STRUCTURE = { {13u, TSS_C13_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C13_STRUCTURE = { {13u, TSS_C13_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C13_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C13_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C13_TREND_CONTEXT;
        UINT8 TSS_C13_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C13_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C13_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(13),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(13),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(13),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(13),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(13)
                                                            };     /* Declares the context ASlider Structure */
        #define C13_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C13_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C13_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 14
    #if (TSS_C14_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C14_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C14_KEYS
          const UINT16 TSS_C14_KEYS_GROUP[] = TSS_C14_KEYS;
          #define TSS_C14_KEYS_COUNT sizeof(TSS_C14_KEYS_GROUP)/sizeof(TSS_C14_KEYS_GROUP[0])
        #else
          #define TSS_C14_KEYS_GROUP NULL
          #define TSS_C14_KEYS_COUNT TSS_C14_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C14_STRUCTURE = { {14u, TSS_C14_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C14_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C14_STRUCTURE_CONTEXT = { 0u, TSS_C14_KEYS_GROUP, 0u,0u, TSS_C14_KEYS_COUNT}; 
        #define C14_DECODER      TSS_KeypadDecoder
    #elif (TSS_C14_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C14_STRUCTURE = { {14u, TSS_C14_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C14_STRUCTURE_CONTEXT;
        #define C14_DECODER      TSS_SliderDecoder
    #elif (TSS_C14_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C14_STRUCTURE = { {14u, TSS_C14_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C14_STRUCTURE_CONTEXT;
        #define C14_DECODER      TSS_SliderDecoder
    #elif (TSS_C14_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C14_STRUCTURE = { {14u, TSS_C14_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C14_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C14_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C14_STRUCTURE_CONTEXT = { TSS_C14_ELECTRODES_X, TSS_C14_ELECTRODES_Y,
                                                             &TSS_C14_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(14) };
        #define C14_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C14_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C14_STRUCTURE = { {14u, TSS_C14_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C14_STRUCTURE = { {14u, TSS_C14_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C14_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C14_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C14_TREND_CONTEXT;
        UINT8 TSS_C14_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C14_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C14_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(14),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(14),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(14),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(14),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(14)
                                                            };     /* Declares the context ASlider Structure */
        #define C14_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C14_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C14_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

#if TSS_N_CONTROLS > 15
    #if (TSS_C15_TYPE == TSS_CT_KEYPAD)
        UINT8 TSS_C15_KEYPAD_EVENTS_BUFFER[TSS_KEYPAD_EVENTS_BUFFER_SIZE];
        #ifdef TSS_C15_KEYS
          const UINT16 TSS_C15_KEYS_GROUP[] = TSS_C15_KEYS;
          #define TSS_C15_KEYS_COUNT sizeof(TSS_C15_KEYS_GROUP)/sizeof(TSS_C15_KEYS_GROUP[0])
        #else
          #define TSS_C15_KEYS_GROUP NULL
          #define TSS_C15_KEYS_COUNT TSS_C15_ELECTRODES
        #endif
        TSS_CSKeypad TSS_C15_STRUCTURE = { {15u, TSS_C15_TYPE}, TSS_KEYPAD_CONTCONF_INIT, 0u,0u, TSS_KEYPAD_EVENTS_INIT, 0u,0u,0u, TSS_C15_KEYPAD_EVENTS_BUFFER};
        TSS_KeypadContext TSS_C15_STRUCTURE_CONTEXT = { 0u, TSS_C15_KEYS_GROUP, 0u,0u, TSS_C15_KEYS_COUNT}; 
        #define C15_DECODER      TSS_KeypadDecoder
    #elif (TSS_C15_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C15_STRUCTURE = { {15u, TSS_C15_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C15_STRUCTURE_CONTEXT;
        #define C15_DECODER      TSS_SliderDecoder
    #elif (TSS_C15_TYPE == TSS_CT_ROTARY)
        TSS_CSRotary TSS_C15_STRUCTURE = { {15u, TSS_C15_TYPE}, TSS_SLIDER_CONTROL_INIT, TSS_SLIDER_DYN_INIT, TSS_SLIDER_STAT_INIT, TSS_SLIDER_EVENTS_INIT, 0u,0u};
        TSS_SingleContext TSS_C15_STRUCTURE_CONTEXT;
        #define C15_DECODER      TSS_SliderDecoder
    #elif (TSS_C15_TYPE == TSS_CT_MATRIX)
        TSS_CSMatrix TSS_C15_STRUCTURE = { {15u, TSS_C15_TYPE}, TSS_MATRIX_CONTROL_INIT, TSS_MATRIX_EVENTS_INIT, 0u,0u, TSS_MATRIX_DYN_INIT, TSS_MATRIX_DYN_INIT, 0u,0u,0u,0u,0u,0u };
        TSS_MatrixTouchContext TSS_C15_MATRIX_TOUCH_CONTEXT = { 0u,0u,0u,0u };
        TSS_MatrixPosIIRFilterContext TSS_C15_MATRIX_POSFILTER_IIR_CONTEXT = { 0u,0u };
        const TSS_MatrixContext TSS_C15_STRUCTURE_CONTEXT = { TSS_C15_ELECTRODES_X, TSS_C15_ELECTRODES_Y,
                                                             &TSS_C15_MATRIX_TOUCH_CONTEXT,
                                                             TSS_GET_CONTROL_MATRIX_POSFILTER_IIR_CONTEXT_TYPE(15) };
        #define C15_DECODER      TSS_MatrixDecoder
    #else /* TSS_CT_ASLIDER || TSS_CT_AROTARY */
      #if (TSS_C15_TYPE == TSS_CT_ASLIDER)
        TSS_CSASlider TSS_C15_STRUCTURE = { {15u, TSS_C15_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #else
        TSS_CSARotary TSS_C15_STRUCTURE = { {15u, TSS_C15_TYPE}, TSS_ASLIDER_CONTROL_INIT, TSS_ASLIDER_DYN_INIT, 0u, TSS_ASLIDER_EVENTS_INIT, 0u,0u,0u};
      #endif
        TSS_ASliderPosFilterContext TSS_C15_POSFILTER_CONTEXT;
        TSS_ASliderDelayContext TSS_C15_DELAY_CONTEXT;
        TSS_ASliderTrendContext TSS_C15_TREND_CONTEXT;
        UINT8 TSS_C15_DELAY_BUFFER[TSS_ASLIDER_DELAY_BUFFER_LENGTH];
        INT8 TSS_C15_TREND_BUFFER[TSS_ASLIDER_TREND_BUFFER_LENGTH];
        const TSS_ASliderContext TSS_C15_STRUCTURE_CONTEXT = { TSS_GET_CONTROL_ASLIDER_POSFILTER_CONTEXT_TYPE(15),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_CONTEXT_TYPE(15),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_CONTEXT_TYPE(15),
                                                              TSS_GET_CONTROL_ASLIDER_DELAY_BUFFER_TYPE(15),
                                                              TSS_GET_CONTROL_ASLIDER_TREND_BUFFER_TYPE(15)
                                                            };     /* Declares the context ASlider Structure */
        #define C15_DECODER      TSS_ASliderDecoder
    #endif
    void TSS_C15_CALLBACK(TSS_CONTROL_ID u8ControlId);
    UINT8 C15_DECODER(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command);
#endif

    
/*
* The section below defines an array of pointers to 
 * all the callback functions defined by the user for each decoder
 * 
 */

#if TSS_N_CONTROLS != 0
/* Pointer to Callback functions */
void (* const tss_faCallback[TSS_N_CONTROLS])(TSS_CONTROL_ID u8ControlId) = 
{
    TSS_C0_CALLBACK,
    #if TSS_N_CONTROLS > 1
        TSS_C1_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 2
        TSS_C2_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 3
        TSS_C3_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 4
        TSS_C4_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 5
        TSS_C5_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 6
        TSS_C6_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 7
        TSS_C7_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 8
        TSS_C8_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 9
        TSS_C9_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 10
        TSS_C10_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 11
        TSS_C11_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 12
        TSS_C12_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 13
        TSS_C13_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 14
        TSS_C14_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 15
        TSS_C15_CALLBACK,
    #endif
};
#else          /* If there are no defined controlers a single element array es created */
    void (* const tss_faCallback[1])(TSS_CONTROL_ID u8ControlId);  
#endif


/*
 * The section below declares an array of pointers with the
 * direction of all the decoders controls context structures
 * created in the sections above
 */

/* Array of pointers to decoders controls context data */ 
#if TSS_N_CONTROLS != 0
UINT8 * const tss_acpsDecContext[TSS_N_CONTROLS] = {
    (UINT8 *)&TSS_C0_STRUCTURE_CONTEXT,
    #if TSS_N_CONTROLS > 1
        (UINT8 *)&TSS_C1_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 2
        (UINT8 *)&TSS_C2_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 3
        (UINT8 *)&TSS_C3_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 4
        (UINT8 *)&TSS_C4_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 5
        (UINT8 *)&TSS_C5_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 6
        (UINT8 *)&TSS_C6_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 7
        (UINT8 *)&TSS_C7_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 8
        (UINT8 *)&TSS_C8_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 9
        (UINT8 *)&TSS_C9_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 10
        (UINT8 *)&TSS_C10_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 11
        (UINT8 *)&TSS_C11_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 12
        (UINT8 *)&TSS_C12_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 13
        (UINT8 *)&TSS_C13_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 14
        (UINT8 *)&TSS_C14_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 15
        (UINT8 *)&TSS_C15_STRUCTURE_CONTEXT,
    #endif
};
#else        /* If there are no defined controlers a single element array es created */
    UINT8 * const tss_acpsDecContext[1];
#endif

/*
 * The section below declares an array of pointers with the
 * direction of all the decoders controls system structures
 * created in the sections above
 */

#if TSS_N_CONTROLS != 0
/* Array of pointers to controls structure data */ 
const UINT8 * const tss_acpsCSStructs[TSS_N_CONTROLS] = {
    (UINT8 *)&TSS_C0_STRUCTURE,
    #if TSS_N_CONTROLS > 1
        (UINT8 *)&TSS_C1_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 2
        (UINT8 *)&TSS_C2_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 3
        (UINT8 *)&TSS_C3_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 4
        (UINT8 *)&TSS_C4_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 5
        (UINT8 *)&TSS_C5_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 6
        (UINT8 *)&TSS_C6_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 7
        (UINT8 *)&TSS_C7_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 8
        (UINT8 *)&TSS_C8_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 9
        (UINT8 *)&TSS_C9_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 10
        (UINT8 *)&TSS_C10_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 11
        (UINT8 *)&TSS_C11_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 12
        (UINT8 *)&TSS_C12_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 13
        (UINT8 *)&TSS_C13_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 14
        (UINT8 *)&TSS_C14_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 15
        (UINT8 *)&TSS_C15_STRUCTURE,
    #endif
};
#else          /* If there are no defined controlers a single element array es created */
    const UINT8 * const tss_acpsCSStructs[1] = 
    {
        NULL
    };
#endif

/*
*
* The section below declares an array where strores the
* number of electrodes per decoder
*/


#if TSS_N_CONTROLS != 0
/* Sumatory of electrodes arranged by control */
const UINT8 tss_cau8CntrlElecBound[TSS_N_CONTROLS] = {
    (UINT8)TSS_C0_ELECTRODES,
    #if TSS_N_CONTROLS > 1
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 2
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 3
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 4
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 5
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 6
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 7
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 8
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 9
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 10
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 11
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 12
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 13
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 14
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES + (UINT8)TSS_C14_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 15
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES + (UINT8)TSS_C14_ELECTRODES + (UINT8)TSS_C15_ELECTRODES,
    #endif
};
#else
    const UINT8 tss_cau8CntrlElecBound[1] =
    {
        (TSS_N_ELECTRODES - 1)
    };
#endif




/*
 * The section below defines an array of pointers to 
 * all the decoders functions defined above
 * 
 */

#if TSS_N_CONTROLS != 0
/* Pointer to Decoders functions */
UINT8 (* const tss_faDecoders[TSS_N_CONTROLS])(UINT8 u8CtrlNum, const UINT16 *pu16Buffer, UINT8 u8Command) = 
{
    C0_DECODER,
    #if TSS_N_CONTROLS > 1
        C1_DECODER,
    #endif
    #if TSS_N_CONTROLS > 2
        C2_DECODER,
    #endif
    #if TSS_N_CONTROLS > 3
        C3_DECODER,
    #endif
    #if TSS_N_CONTROLS > 4
        C4_DECODER,
    #endif
    #if TSS_N_CONTROLS > 5
        C5_DECODER,
    #endif
    #if TSS_N_CONTROLS > 6
        C6_DECODER,
    #endif
    #if TSS_N_CONTROLS > 7
        C7_DECODER,
    #endif
    #if TSS_N_CONTROLS > 8
        C8_DECODER,
    #endif
    #if TSS_N_CONTROLS > 9
        C9_DECODER,
    #endif
    #if TSS_N_CONTROLS > 10
        C10_DECODER,
    #endif
    #if TSS_N_CONTROLS > 11
        C11_DECODER,
    #endif
    #if TSS_N_CONTROLS > 12
        C12_DECODER,
    #endif
    #if TSS_N_CONTROLS > 13
        C13_DECODER,
    #endif
    #if TSS_N_CONTROLS > 14
        C14_DECODER,
    #endif
    #if TSS_N_CONTROLS > 15
        C15_DECODER,
    #endif
};
#else          /* If there are no defined controlers a single element array es created */
    UINT8 (* const tss_faDecoders[1])(UINT8 u8CtrlNum, UINT16 *pu16Buffer, UINT8 u8Command);
#endif

/*
 * Initializes the Shield Config array
 */
#if TSS_USE_SIGNAL_SHIELDING

  #define TSS_SHIELD_NOT_USED             0x7F
  #define TSS_SHIELD_ELECTRODE_MASK       0x7F    
  #define TSS_SHIELD_ELECTRODE_FLAG       0x80
  #define TSS_SHIELD_ELECTRODE_FLAG_MASK  0x80    
  #define TSS_SHIELD_ELECTRODE_USED(x,y)  (TSS_E##x##_SHIELD_DATA == y)
  #define TSS_SHIELD_ELECTRODES_USED(x)   (TSS_SHIELD_ELECTRODE_USED(0,x) || TSS_SHIELD_ELECTRODE_USED(1,x) || TSS_SHIELD_ELECTRODE_USED(2,x) || TSS_SHIELD_ELECTRODE_USED(3,x) || TSS_SHIELD_ELECTRODE_USED(4,x) || TSS_SHIELD_ELECTRODE_USED(5,x) || TSS_SHIELD_ELECTRODE_USED(6,x) || TSS_SHIELD_ELECTRODE_USED(7,x) || TSS_SHIELD_ELECTRODE_USED(8,x) || TSS_SHIELD_ELECTRODE_USED(9,x) || TSS_SHIELD_ELECTRODE_USED(10,x) || TSS_SHIELD_ELECTRODE_USED(11,x) || TSS_SHIELD_ELECTRODE_USED(12,x) || TSS_SHIELD_ELECTRODE_USED(13,x) || TSS_SHIELD_ELECTRODE_USED(14,x) || TSS_SHIELD_ELECTRODE_USED(15,x) || TSS_SHIELD_ELECTRODE_USED(16,x) || TSS_SHIELD_ELECTRODE_USED(17,x) || TSS_SHIELD_ELECTRODE_USED(18,x) || TSS_SHIELD_ELECTRODE_USED(19,x) || TSS_SHIELD_ELECTRODE_USED(20,x) || TSS_SHIELD_ELECTRODE_USED(21,x) || TSS_SHIELD_ELECTRODE_USED(22,x) || TSS_SHIELD_ELECTRODE_USED(23,x) || TSS_SHIELD_ELECTRODE_USED(24,x) || TSS_SHIELD_ELECTRODE_USED(25,x) || TSS_SHIELD_ELECTRODE_USED(26,x) || TSS_SHIELD_ELECTRODE_USED(27,x) || TSS_SHIELD_ELECTRODE_USED(28,x) || TSS_SHIELD_ELECTRODE_USED(29,x) || TSS_SHIELD_ELECTRODE_USED(30,x) || TSS_SHIELD_ELECTRODE_USED(31,x) || TSS_SHIELD_ELECTRODE_USED(32,x) || TSS_SHIELD_ELECTRODE_USED(33,x) || TSS_SHIELD_ELECTRODE_USED(34,x) || TSS_SHIELD_ELECTRODE_USED(35,x) || TSS_SHIELD_ELECTRODE_USED(36,x) || TSS_SHIELD_ELECTRODE_USED(37,x) || TSS_SHIELD_ELECTRODE_USED(38,x) || TSS_SHIELD_ELECTRODE_USED(39,x) || TSS_SHIELD_ELECTRODE_USED(40,x) || TSS_SHIELD_ELECTRODE_USED(41,x) || TSS_SHIELD_ELECTRODE_USED(42,x) || TSS_SHIELD_ELECTRODE_USED(43,x) || TSS_SHIELD_ELECTRODE_USED(44,x) || TSS_SHIELD_ELECTRODE_USED(45,x) || TSS_SHIELD_ELECTRODE_USED(46,x) || TSS_SHIELD_ELECTRODE_USED(47,x) || TSS_SHIELD_ELECTRODE_USED(48,x) || TSS_SHIELD_ELECTRODE_USED(49,x) || TSS_SHIELD_ELECTRODE_USED(50,x) || TSS_SHIELD_ELECTRODE_USED(51,x) || TSS_SHIELD_ELECTRODE_USED(52,x) || TSS_SHIELD_ELECTRODE_USED(53,x) || TSS_SHIELD_ELECTRODE_USED(54,x) || TSS_SHIELD_ELECTRODE_USED(55,x) || TSS_SHIELD_ELECTRODE_USED(56,x) || TSS_SHIELD_ELECTRODE_USED(57,x) || TSS_SHIELD_ELECTRODE_USED(58,x) || TSS_SHIELD_ELECTRODE_USED(59,x) || TSS_SHIELD_ELECTRODE_USED(60,x) || TSS_SHIELD_ELECTRODE_USED(61,x) || TSS_SHIELD_ELECTRODE_USED(62,x) || TSS_SHIELD_ELECTRODE_USED(63,x))

  #ifdef TSS_E0_SHIELD_ELECTRODE
    #define TSS_E0_SHIELD_DATA TSS_E0_SHIELD_ELECTRODE
  #else
    #define TSS_E0_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E1_SHIELD_ELECTRODE
    #define TSS_E1_SHIELD_DATA TSS_E1_SHIELD_ELECTRODE
  #else
    #define TSS_E1_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E2_SHIELD_ELECTRODE
    #define TSS_E2_SHIELD_DATA TSS_E2_SHIELD_ELECTRODE
  #else
    #define TSS_E2_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E3_SHIELD_ELECTRODE
    #define TSS_E3_SHIELD_DATA TSS_E3_SHIELD_ELECTRODE
  #else
    #define TSS_E3_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E4_SHIELD_ELECTRODE
    #define TSS_E4_SHIELD_DATA TSS_E4_SHIELD_ELECTRODE
  #else
    #define TSS_E4_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E5_SHIELD_ELECTRODE
    #define TSS_E5_SHIELD_DATA TSS_E5_SHIELD_ELECTRODE
  #else
    #define TSS_E5_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E6_SHIELD_ELECTRODE
    #define TSS_E6_SHIELD_DATA TSS_E6_SHIELD_ELECTRODE
  #else
    #define TSS_E6_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E7_SHIELD_ELECTRODE
    #define TSS_E7_SHIELD_DATA TSS_E7_SHIELD_ELECTRODE
  #else
    #define TSS_E7_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E8_SHIELD_ELECTRODE
    #define TSS_E8_SHIELD_DATA TSS_E8_SHIELD_ELECTRODE
  #else
    #define TSS_E8_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E9_SHIELD_ELECTRODE
    #define TSS_E9_SHIELD_DATA TSS_E9_SHIELD_ELECTRODE
  #else
    #define TSS_E9_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E10_SHIELD_ELECTRODE
    #define TSS_E10_SHIELD_DATA TSS_E10_SHIELD_ELECTRODE
  #else
    #define TSS_E10_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E11_SHIELD_ELECTRODE
    #define TSS_E11_SHIELD_DATA TSS_E11_SHIELD_ELECTRODE
  #else
    #define TSS_E11_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E12_SHIELD_ELECTRODE
    #define TSS_E12_SHIELD_DATA TSS_E12_SHIELD_ELECTRODE
  #else
    #define TSS_E12_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E13_SHIELD_ELECTRODE
    #define TSS_E13_SHIELD_DATA TSS_E13_SHIELD_ELECTRODE
  #else
    #define TSS_E13_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E14_SHIELD_ELECTRODE
    #define TSS_E14_SHIELD_DATA TSS_E14_SHIELD_ELECTRODE
  #else
    #define TSS_E14_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E15_SHIELD_ELECTRODE
    #define TSS_E15_SHIELD_DATA TSS_E15_SHIELD_ELECTRODE
  #else
    #define TSS_E15_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E16_SHIELD_ELECTRODE
    #define TSS_E16_SHIELD_DATA TSS_E16_SHIELD_ELECTRODE
  #else
    #define TSS_E16_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E17_SHIELD_ELECTRODE
    #define TSS_E17_SHIELD_DATA TSS_E17_SHIELD_ELECTRODE
  #else
    #define TSS_E17_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E18_SHIELD_ELECTRODE
    #define TSS_E18_SHIELD_DATA TSS_E18_SHIELD_ELECTRODE
  #else
    #define TSS_E18_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E19_SHIELD_ELECTRODE
    #define TSS_E19_SHIELD_DATA TSS_E19_SHIELD_ELECTRODE
  #else
    #define TSS_E19_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E20_SHIELD_ELECTRODE
    #define TSS_E20_SHIELD_DATA TSS_E20_SHIELD_ELECTRODE
  #else
    #define TSS_E20_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E21_SHIELD_ELECTRODE
    #define TSS_E21_SHIELD_DATA TSS_E21_SHIELD_ELECTRODE
  #else
    #define TSS_E21_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E22_SHIELD_ELECTRODE
    #define TSS_E22_SHIELD_DATA TSS_E22_SHIELD_ELECTRODE
  #else
    #define TSS_E22_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E23_SHIELD_ELECTRODE
    #define TSS_E23_SHIELD_DATA TSS_E23_SHIELD_ELECTRODE
  #else
    #define TSS_E23_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E24_SHIELD_ELECTRODE
    #define TSS_E24_SHIELD_DATA TSS_E24_SHIELD_ELECTRODE
  #else
    #define TSS_E24_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E25_SHIELD_ELECTRODE
    #define TSS_E25_SHIELD_DATA TSS_E25_SHIELD_ELECTRODE
  #else
    #define TSS_E25_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E26_SHIELD_ELECTRODE
    #define TSS_E26_SHIELD_DATA TSS_E26_SHIELD_ELECTRODE
  #else
    #define TSS_E26_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E27_SHIELD_ELECTRODE
    #define TSS_E27_SHIELD_DATA TSS_E27_SHIELD_ELECTRODE
  #else
    #define TSS_E27_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E28_SHIELD_ELECTRODE
    #define TSS_E28_SHIELD_DATA TSS_E28_SHIELD_ELECTRODE
  #else
    #define TSS_E28_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E29_SHIELD_ELECTRODE
    #define TSS_E29_SHIELD_DATA TSS_E29_SHIELD_ELECTRODE
  #else
    #define TSS_E29_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E30_SHIELD_ELECTRODE
    #define TSS_E30_SHIELD_DATA TSS_E30_SHIELD_ELECTRODE
  #else
    #define TSS_E30_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E31_SHIELD_ELECTRODE
    #define TSS_E31_SHIELD_DATA TSS_E31_SHIELD_ELECTRODE
  #else
    #define TSS_E31_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E32_SHIELD_ELECTRODE
    #define TSS_E32_SHIELD_DATA TSS_E32_SHIELD_ELECTRODE
  #else
    #define TSS_E32_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E33_SHIELD_ELECTRODE
    #define TSS_E33_SHIELD_DATA TSS_E33_SHIELD_ELECTRODE
  #else
    #define TSS_E33_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E34_SHIELD_ELECTRODE
    #define TSS_E34_SHIELD_DATA TSS_E34_SHIELD_ELECTRODE
  #else
    #define TSS_E34_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E35_SHIELD_ELECTRODE
    #define TSS_E35_SHIELD_DATA TSS_E35_SHIELD_ELECTRODE
  #else
    #define TSS_E35_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E36_SHIELD_ELECTRODE
    #define TSS_E36_SHIELD_DATA TSS_E36_SHIELD_ELECTRODE
  #else
    #define TSS_E36_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E37_SHIELD_ELECTRODE
    #define TSS_E37_SHIELD_DATA TSS_E37_SHIELD_ELECTRODE
  #else
    #define TSS_E37_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E38_SHIELD_ELECTRODE
    #define TSS_E38_SHIELD_DATA TSS_E38_SHIELD_ELECTRODE
  #else
    #define TSS_E38_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E39_SHIELD_ELECTRODE
    #define TSS_E39_SHIELD_DATA TSS_E39_SHIELD_ELECTRODE
  #else
    #define TSS_E39_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E40_SHIELD_ELECTRODE
    #define TSS_E40_SHIELD_DATA TSS_E40_SHIELD_ELECTRODE
  #else
    #define TSS_E40_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E41_SHIELD_ELECTRODE
    #define TSS_E41_SHIELD_DATA TSS_E41_SHIELD_ELECTRODE
  #else
    #define TSS_E41_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E42_SHIELD_ELECTRODE
    #define TSS_E42_SHIELD_DATA TSS_E42_SHIELD_ELECTRODE
  #else
    #define TSS_E42_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E43_SHIELD_ELECTRODE
    #define TSS_E43_SHIELD_DATA TSS_E43_SHIELD_ELECTRODE
  #else
    #define TSS_E43_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E44_SHIELD_ELECTRODE
    #define TSS_E44_SHIELD_DATA TSS_E44_SHIELD_ELECTRODE
  #else
    #define TSS_E44_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E45_SHIELD_ELECTRODE
    #define TSS_E45_SHIELD_DATA TSS_E45_SHIELD_ELECTRODE
  #else
    #define TSS_E45_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E46_SHIELD_ELECTRODE
    #define TSS_E46_SHIELD_DATA TSS_E46_SHIELD_ELECTRODE
  #else
    #define TSS_E46_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E47_SHIELD_ELECTRODE
    #define TSS_E47_SHIELD_DATA TSS_E47_SHIELD_ELECTRODE
  #else
    #define TSS_E47_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E48_SHIELD_ELECTRODE
    #define TSS_E48_SHIELD_DATA TSS_E48_SHIELD_ELECTRODE
  #else
    #define TSS_E48_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E49_SHIELD_ELECTRODE
    #define TSS_E49_SHIELD_DATA TSS_E49_SHIELD_ELECTRODE
  #else
    #define TSS_E49_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E50_SHIELD_ELECTRODE
    #define TSS_E50_SHIELD_DATA TSS_E50_SHIELD_ELECTRODE
  #else
    #define TSS_E50_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E51_SHIELD_ELECTRODE
    #define TSS_E51_SHIELD_DATA TSS_E51_SHIELD_ELECTRODE
  #else
    #define TSS_E51_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E52_SHIELD_ELECTRODE
    #define TSS_E52_SHIELD_DATA TSS_E52_SHIELD_ELECTRODE
  #else
    #define TSS_E52_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E53_SHIELD_ELECTRODE
    #define TSS_E53_SHIELD_DATA TSS_E53_SHIELD_ELECTRODE
  #else
    #define TSS_E53_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E54_SHIELD_ELECTRODE
    #define TSS_E54_SHIELD_DATA TSS_E54_SHIELD_ELECTRODE
  #else
    #define TSS_E54_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E55_SHIELD_ELECTRODE
    #define TSS_E55_SHIELD_DATA TSS_E55_SHIELD_ELECTRODE
  #else
    #define TSS_E55_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E56_SHIELD_ELECTRODE
    #define TSS_E56_SHIELD_DATA TSS_E56_SHIELD_ELECTRODE
  #else
    #define TSS_E56_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E57_SHIELD_ELECTRODE
    #define TSS_E57_SHIELD_DATA TSS_E57_SHIELD_ELECTRODE
  #else
    #define TSS_E57_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E58_SHIELD_ELECTRODE
    #define TSS_E58_SHIELD_DATA TSS_E58_SHIELD_ELECTRODE
  #else
    #define TSS_E58_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E59_SHIELD_ELECTRODE
    #define TSS_E59_SHIELD_DATA TSS_E59_SHIELD_ELECTRODE
  #else
    #define TSS_E59_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E60_SHIELD_ELECTRODE
    #define TSS_E60_SHIELD_DATA TSS_E60_SHIELD_ELECTRODE
  #else
    #define TSS_E60_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E61_SHIELD_ELECTRODE
    #define TSS_E61_SHIELD_DATA TSS_E61_SHIELD_ELECTRODE
  #else
    #define TSS_E61_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E62_SHIELD_ELECTRODE
    #define TSS_E62_SHIELD_DATA TSS_E62_SHIELD_ELECTRODE
  #else
    #define TSS_E62_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif
  #ifdef TSS_E63_SHIELD_ELECTRODE
    #define TSS_E63_SHIELD_DATA TSS_E63_SHIELD_ELECTRODE
  #else
    #define TSS_E63_SHIELD_DATA TSS_SHIELD_NOT_USED
  #endif

  const UINT8 tss_cau8ShieldPairs[TSS_N_ELECTRODES] = {
    #if TSS_N_ELECTRODES > 0
      #if TSS_SHIELD_ELECTRODES_USED(0)
        TSS_E0_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E0_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 1
      #if TSS_SHIELD_ELECTRODES_USED(1)
        TSS_E1_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E1_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 2
      #if TSS_SHIELD_ELECTRODES_USED(2)
        TSS_E2_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E2_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 3
      #if TSS_SHIELD_ELECTRODES_USED(3)
        TSS_E3_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E3_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 4
      #if TSS_SHIELD_ELECTRODES_USED(4)
        TSS_E4_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E4_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 5
      #if TSS_SHIELD_ELECTRODES_USED(5)
        TSS_E5_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E5_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 6
      #if TSS_SHIELD_ELECTRODES_USED(6)
        TSS_E6_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E6_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 7
      #if TSS_SHIELD_ELECTRODES_USED(7)
        TSS_E7_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E7_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 8
      #if TSS_SHIELD_ELECTRODES_USED(8)
        TSS_E8_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E8_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 9
      #if TSS_SHIELD_ELECTRODES_USED(9)
        TSS_E9_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E9_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 10
      #if TSS_SHIELD_ELECTRODES_USED(10)
        TSS_E10_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E10_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 11
      #if TSS_SHIELD_ELECTRODES_USED(11)
        TSS_E11_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E11_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 12
      #if TSS_SHIELD_ELECTRODES_USED(12)
        TSS_E12_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E12_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 13
      #if TSS_SHIELD_ELECTRODES_USED(13)
        TSS_E13_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E13_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 14
      #if TSS_SHIELD_ELECTRODES_USED(14)
        TSS_E14_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E14_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 15
      #if TSS_SHIELD_ELECTRODES_USED(15)
        TSS_E15_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E15_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 16
      #if TSS_SHIELD_ELECTRODES_USED(16)
        TSS_E16_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E16_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 17
      #if TSS_SHIELD_ELECTRODES_USED(17)
        TSS_E17_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E17_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 18
      #if TSS_SHIELD_ELECTRODES_USED(18)
        TSS_E18_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E18_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 19
      #if TSS_SHIELD_ELECTRODES_USED(19)
        TSS_E19_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E19_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 20
      #if TSS_SHIELD_ELECTRODES_USED(20)
        TSS_E20_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E20_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 21
      #if TSS_SHIELD_ELECTRODES_USED(21)
        TSS_E21_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E21_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 22
      #if TSS_SHIELD_ELECTRODES_USED(22)
        TSS_E22_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E22_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 23
      #if TSS_SHIELD_ELECTRODES_USED(23)
        TSS_E23_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E23_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 24
      #if TSS_SHIELD_ELECTRODES_USED(24)
        TSS_E24_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E24_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 25
      #if TSS_SHIELD_ELECTRODES_USED(25)
        TSS_E25_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E25_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 26
      #if TSS_SHIELD_ELECTRODES_USED(26)
        TSS_E26_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E26_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 27
      #if TSS_SHIELD_ELECTRODES_USED(27)
        TSS_E27_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E27_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 28
      #if TSS_SHIELD_ELECTRODES_USED(28)
        TSS_E28_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E28_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 29
      #if TSS_SHIELD_ELECTRODES_USED(29)
        TSS_E29_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E29_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 30
      #if TSS_SHIELD_ELECTRODES_USED(30)
        TSS_E30_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E30_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 31
      #if TSS_SHIELD_ELECTRODES_USED(31)
        TSS_E31_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E31_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 32
      #if TSS_SHIELD_ELECTRODES_USED(32)
        TSS_E32_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E32_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 33
      #if TSS_SHIELD_ELECTRODES_USED(33)
        TSS_E33_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E33_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 34
      #if TSS_SHIELD_ELECTRODES_USED(34)
        TSS_E34_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E34_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 35
      #if TSS_SHIELD_ELECTRODES_USED(35)
        TSS_E35_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E35_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 36
      #if TSS_SHIELD_ELECTRODES_USED(36)
        TSS_E36_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E36_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 37
      #if TSS_SHIELD_ELECTRODES_USED(37)
        TSS_E37_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E37_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 38
      #if TSS_SHIELD_ELECTRODES_USED(38)
        TSS_E38_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E38_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 39
      #if TSS_SHIELD_ELECTRODES_USED(39)
        TSS_E39_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E39_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 40
      #if TSS_SHIELD_ELECTRODES_USED(40)
        TSS_E40_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E40_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 41
      #if TSS_SHIELD_ELECTRODES_USED(41)
        TSS_E41_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E41_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 42
      #if TSS_SHIELD_ELECTRODES_USED(42)
        TSS_E42_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E42_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 43
      #if TSS_SHIELD_ELECTRODES_USED(43)
        TSS_E43_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E43_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 44
      #if TSS_SHIELD_ELECTRODES_USED(44)
        TSS_E44_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E44_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 45
      #if TSS_SHIELD_ELECTRODES_USED(45)
        TSS_E45_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E45_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 46
      #if TSS_SHIELD_ELECTRODES_USED(46)
        TSS_E46_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E46_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 47
      #if TSS_SHIELD_ELECTRODES_USED(47)
        TSS_E47_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E47_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 48
      #if TSS_SHIELD_ELECTRODES_USED(48)
        TSS_E48_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E48_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 49
      #if TSS_SHIELD_ELECTRODES_USED(49)
        TSS_E49_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E49_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 50
      #if TSS_SHIELD_ELECTRODES_USED(50)
        TSS_E50_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E50_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 51
      #if TSS_SHIELD_ELECTRODES_USED(51)
        TSS_E51_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E51_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 52
      #if TSS_SHIELD_ELECTRODES_USED(52)
        TSS_E52_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E52_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 53
      #if TSS_SHIELD_ELECTRODES_USED(53)
        TSS_E53_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E53_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 54
      #if TSS_SHIELD_ELECTRODES_USED(54)
        TSS_E54_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E54_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 55
      #if TSS_SHIELD_ELECTRODES_USED(55)
        TSS_E55_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E55_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 56
      #if TSS_SHIELD_ELECTRODES_USED(56)
        TSS_E56_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E56_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 57
      #if TSS_SHIELD_ELECTRODES_USED(57)
        TSS_E57_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E57_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 58
      #if TSS_SHIELD_ELECTRODES_USED(58)
        TSS_E58_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E58_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 59
      #if TSS_SHIELD_ELECTRODES_USED(59)
        TSS_E59_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E59_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 60
      #if TSS_SHIELD_ELECTRODES_USED(60)
        TSS_E60_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E60_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 61
      #if TSS_SHIELD_ELECTRODES_USED(61)
        TSS_E61_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E61_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 62
      #if TSS_SHIELD_ELECTRODES_USED(62)
        TSS_E62_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E62_SHIELD_DATA,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 63
      #if TSS_SHIELD_ELECTRODES_USED(63)
        TSS_E63_SHIELD_DATA | TSS_SHIELD_ELECTRODE_FLAG,
      #else
        TSS_E63_SHIELD_DATA,
      #endif
    #endif
  };
#else
  const UINT8 tss_cau8ShieldPairs[1];
#endif

/*
 * Initializes the Divider Config array
 */
#define TSS_SINAL_DIVIDER_NOT_USED     1u    

#if TSS_USE_SIGNAL_DIVIDER
/* Array of Signal Divider Config values */ 
const UINT8 tss_cau8SignalDivider[TSS_N_ELECTRODES] = {
    #if TSS_N_ELECTRODES > 0
      #if defined(TSS_E0_SIGNAL_DIVIDER)
        #if (TSS_E0_SIGNAL_DIVIDER > 0)
          TSS_E0_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 1
      #if defined(TSS_E1_SIGNAL_DIVIDER)
        #if (TSS_E1_SIGNAL_DIVIDER > 0)
          TSS_E1_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 2
      #if defined(TSS_E2_SIGNAL_DIVIDER)
        #if (TSS_E2_SIGNAL_DIVIDER > 0)
          TSS_E2_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 3
      #if defined(TSS_E3_SIGNAL_DIVIDER)
        #if (TSS_E3_SIGNAL_DIVIDER > 0)
          TSS_E3_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 4
      #if defined(TSS_E4_SIGNAL_DIVIDER)
        #if (TSS_E4_SIGNAL_DIVIDER > 0)
          TSS_E4_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 5
      #if defined(TSS_E5_SIGNAL_DIVIDER)
        #if (TSS_E5_SIGNAL_DIVIDER > 0)
          TSS_E5_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 6
      #if defined(TSS_E6_SIGNAL_DIVIDER)
        #if (TSS_E6_SIGNAL_DIVIDER > 0)
          TSS_E6_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 7
      #if defined(TSS_E7_SIGNAL_DIVIDER)
        #if (TSS_E7_SIGNAL_DIVIDER > 0)
          TSS_E7_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 8
      #if defined(TSS_E8_SIGNAL_DIVIDER)
        #if (TSS_E8_SIGNAL_DIVIDER > 0)
          TSS_E8_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 9
      #if defined(TSS_E9_SIGNAL_DIVIDER)
        #if (TSS_E9_SIGNAL_DIVIDER > 0)
          TSS_E9_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 10
      #if defined(TSS_E10_SIGNAL_DIVIDER)
        #if (TSS_E10_SIGNAL_DIVIDER > 0)
          TSS_E10_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 11
      #if defined(TSS_E11_SIGNAL_DIVIDER)
        #if (TSS_E11_SIGNAL_DIVIDER > 0)
          TSS_E11_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 12
      #if defined(TSS_E12_SIGNAL_DIVIDER)
        #if (TSS_E12_SIGNAL_DIVIDER > 0)
          TSS_E12_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 13
      #if defined(TSS_E13_SIGNAL_DIVIDER)
        #if (TSS_E13_SIGNAL_DIVIDER > 0)
          TSS_E13_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 14
      #if defined(TSS_E14_SIGNAL_DIVIDER)
        #if (TSS_E14_SIGNAL_DIVIDER > 0)
          TSS_E14_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 15
      #if defined(TSS_E15_SIGNAL_DIVIDER)
        #if (TSS_E15_SIGNAL_DIVIDER > 0)
          TSS_E15_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 16
      #if defined(TSS_E16_SIGNAL_DIVIDER)
        #if (TSS_E16_SIGNAL_DIVIDER > 0)
          TSS_E16_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 17
      #if defined(TSS_E17_SIGNAL_DIVIDER)
        #if (TSS_E17_SIGNAL_DIVIDER > 0)
          TSS_E17_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 18
      #if defined(TSS_E18_SIGNAL_DIVIDER)
        #if (TSS_E18_SIGNAL_DIVIDER > 0)
          TSS_E18_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 19
      #if defined(TSS_E19_SIGNAL_DIVIDER)
        #if (TSS_E19_SIGNAL_DIVIDER > 0)
          TSS_E19_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 20
      #if defined(TSS_E20_SIGNAL_DIVIDER)
        #if (TSS_E20_SIGNAL_DIVIDER > 0)
          TSS_E20_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 21
      #if defined(TSS_E21_SIGNAL_DIVIDER)
        #if (TSS_E21_SIGNAL_DIVIDER > 0)
          TSS_E21_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 22
      #if defined(TSS_E22_SIGNAL_DIVIDER)
        #if (TSS_E22_SIGNAL_DIVIDER > 0)
          TSS_E22_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 23
      #if defined(TSS_E23_SIGNAL_DIVIDER)
        #if (TSS_E23_SIGNAL_DIVIDER > 0)
          TSS_E23_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 24
      #if defined(TSS_E24_SIGNAL_DIVIDER)
        #if (TSS_E24_SIGNAL_DIVIDER > 0)
          TSS_E24_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 25
      #if defined(TSS_E25_SIGNAL_DIVIDER)
        #if (TSS_E25_SIGNAL_DIVIDER > 0)
          TSS_E25_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 26
      #if defined(TSS_E26_SIGNAL_DIVIDER)
        #if (TSS_E26_SIGNAL_DIVIDER > 0)
          TSS_E26_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 27
      #if defined(TSS_E27_SIGNAL_DIVIDER)
        #if (TSS_E27_SIGNAL_DIVIDER > 0)
          TSS_E27_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 28
      #if defined(TSS_E28_SIGNAL_DIVIDER)
        #if (TSS_E28_SIGNAL_DIVIDER > 0)
          TSS_E28_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 29
      #if defined(TSS_E29_SIGNAL_DIVIDER)
        #if (TSS_E29_SIGNAL_DIVIDER > 0)
          TSS_E29_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 30
      #if defined(TSS_E30_SIGNAL_DIVIDER)
        #if (TSS_E30_SIGNAL_DIVIDER > 0)
          TSS_E30_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 31
      #if defined(TSS_E31_SIGNAL_DIVIDER)
        #if (TSS_E31_SIGNAL_DIVIDER > 0)
          TSS_E31_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 32
      #if defined(TSS_E32_SIGNAL_DIVIDER)
        #if (TSS_E32_SIGNAL_DIVIDER > 0)
          TSS_E32_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 33
      #if defined(TSS_E33_SIGNAL_DIVIDER)
        #if (TSS_E33_SIGNAL_DIVIDER > 0)
          TSS_E33_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 34
      #if defined(TSS_E34_SIGNAL_DIVIDER)
        #if (TSS_E34_SIGNAL_DIVIDER > 0)
          TSS_E34_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 35
      #if defined(TSS_E35_SIGNAL_DIVIDER)
        #if (TSS_E35_SIGNAL_DIVIDER > 0)
          TSS_E35_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 36
      #if defined(TSS_E36_SIGNAL_DIVIDER)
        #if (TSS_E36_SIGNAL_DIVIDER > 0)
          TSS_E36_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 37
      #if defined(TSS_E37_SIGNAL_DIVIDER)
        #if (TSS_E37_SIGNAL_DIVIDER > 0)
          TSS_E37_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 38
      #if defined(TSS_E38_SIGNAL_DIVIDER)
        #if (TSS_E38_SIGNAL_DIVIDER > 0)
          TSS_E38_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 39
      #if defined(TSS_E39_SIGNAL_DIVIDER)
        #if (TSS_E39_SIGNAL_DIVIDER > 0)
          TSS_E39_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 40
      #if defined(TSS_E40_SIGNAL_DIVIDER)
        #if (TSS_E40_SIGNAL_DIVIDER > 0)
          TSS_E40_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 41
      #if defined(TSS_E41_SIGNAL_DIVIDER)
        #if (TSS_E41_SIGNAL_DIVIDER > 0)
          TSS_E41_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 42
      #if defined(TSS_E42_SIGNAL_DIVIDER)
        #if (TSS_E42_SIGNAL_DIVIDER > 0)
          TSS_E42_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 43
      #if defined(TSS_E43_SIGNAL_DIVIDER)
        #if (TSS_E43_SIGNAL_DIVIDER > 0)
          TSS_E43_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 44
      #if defined(TSS_E44_SIGNAL_DIVIDER)
        #if (TSS_E44_SIGNAL_DIVIDER > 0)
          TSS_E44_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 45
      #if defined(TSS_E45_SIGNAL_DIVIDER)
        #if (TSS_E45_SIGNAL_DIVIDER > 0)
          TSS_E45_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 46
      #if defined(TSS_E46_SIGNAL_DIVIDER)
        #if (TSS_E46_SIGNAL_DIVIDER > 0)
          TSS_E46_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 47
      #if defined(TSS_E47_SIGNAL_DIVIDER)
        #if (TSS_E47_SIGNAL_DIVIDER > 0)
          TSS_E47_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 48
      #if defined(TSS_E48_SIGNAL_DIVIDER)
        #if (TSS_E48_SIGNAL_DIVIDER > 0)
          TSS_E48_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 49
      #if defined(TSS_E49_SIGNAL_DIVIDER)
        #if (TSS_E49_SIGNAL_DIVIDER > 0)
          TSS_E49_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 50
      #if defined(TSS_E50_SIGNAL_DIVIDER)
        #if (TSS_E50_SIGNAL_DIVIDER > 0)
          TSS_E50_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 51
      #if defined(TSS_E51_SIGNAL_DIVIDER)
        #if (TSS_E51_SIGNAL_DIVIDER > 0)
          TSS_E51_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 52
      #if defined(TSS_E52_SIGNAL_DIVIDER)
        #if (TSS_E52_SIGNAL_DIVIDER > 0)
          TSS_E52_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 53
      #if defined(TSS_E53_SIGNAL_DIVIDER)
        #if (TSS_E53_SIGNAL_DIVIDER > 0)
          TSS_E53_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 54
      #if defined(TSS_E54_SIGNAL_DIVIDER)
        #if (TSS_E54_SIGNAL_DIVIDER > 0)
          TSS_E54_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 55
      #if defined(TSS_E55_SIGNAL_DIVIDER)
        #if (TSS_E55_SIGNAL_DIVIDER > 0)
          TSS_E55_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 56
      #if defined(TSS_E56_SIGNAL_DIVIDER)
        #if (TSS_E56_SIGNAL_DIVIDER > 0)
          TSS_E56_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 57
      #if defined(TSS_E57_SIGNAL_DIVIDER)
        #if (TSS_E57_SIGNAL_DIVIDER > 0)
          TSS_E57_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 58
      #if defined(TSS_E58_SIGNAL_DIVIDER)
        #if (TSS_E58_SIGNAL_DIVIDER > 0)
          TSS_E58_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 59
      #if defined(TSS_E59_SIGNAL_DIVIDER)
        #if (TSS_E59_SIGNAL_DIVIDER > 0)
          TSS_E59_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 60
      #if defined(TSS_E60_SIGNAL_DIVIDER)
        #if (TSS_E60_SIGNAL_DIVIDER > 0)
          TSS_E60_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 61
      #if defined(TSS_E61_SIGNAL_DIVIDER)
        #if (TSS_E61_SIGNAL_DIVIDER > 0)
          TSS_E61_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 62
      #if defined(TSS_E62_SIGNAL_DIVIDER)
        #if (TSS_E62_SIGNAL_DIVIDER > 0)
          TSS_E62_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 63
      #if defined(TSS_E63_SIGNAL_DIVIDER)
        #if (TSS_E63_SIGNAL_DIVIDER > 0)
          TSS_E63_SIGNAL_DIVIDER,
        #else
          TSS_SINAL_DIVIDER_NOT_USED,
        #endif
      #else
        TSS_SINAL_DIVIDER_NOT_USED,
      #endif
    #endif
};    
#else
const UINT8 tss_cau8SignalDivider[1u];
#endif

/*
 * Initializes the Signal Multiplier Config array
 */
#define TSS_SINAL_MULTIPLIER_NOT_USED     1u    

#if TSS_USE_SIGNAL_MULTIPLIER
/* Array of Signal Multiplier Config values */ 
const UINT8 tss_cau8SignalMultiplier[TSS_N_ELECTRODES] = {
    #if TSS_N_ELECTRODES > 0
      #if defined(TSS_E0_SIGNAL_MULTIPLIER)
        #if (TSS_E0_SIGNAL_MULTIPLIER > 0)
          TSS_E0_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 1
      #if defined(TSS_E1_SIGNAL_MULTIPLIER)
        #if (TSS_E1_SIGNAL_MULTIPLIER > 0)
          TSS_E1_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 2
      #if defined(TSS_E2_SIGNAL_MULTIPLIER)
        #if (TSS_E2_SIGNAL_MULTIPLIER > 0)
          TSS_E2_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 3
      #if defined(TSS_E3_SIGNAL_MULTIPLIER)
        #if (TSS_E3_SIGNAL_MULTIPLIER > 0)
          TSS_E3_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 4
      #if defined(TSS_E4_SIGNAL_MULTIPLIER)
        #if (TSS_E4_SIGNAL_MULTIPLIER > 0)
          TSS_E4_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 5
      #if defined(TSS_E5_SIGNAL_MULTIPLIER)
        #if (TSS_E5_SIGNAL_MULTIPLIER > 0)
          TSS_E5_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 6
      #if defined(TSS_E6_SIGNAL_MULTIPLIER)
        #if (TSS_E6_SIGNAL_MULTIPLIER > 0)
          TSS_E6_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 7
      #if defined(TSS_E7_SIGNAL_MULTIPLIER)
        #if (TSS_E7_SIGNAL_MULTIPLIER > 0)
          TSS_E7_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 8
      #if defined(TSS_E8_SIGNAL_MULTIPLIER)
        #if (TSS_E8_SIGNAL_MULTIPLIER > 0)
          TSS_E8_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 9
      #if defined(TSS_E9_SIGNAL_MULTIPLIER)
        #if (TSS_E9_SIGNAL_MULTIPLIER > 0)
          TSS_E9_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 10
      #if defined(TSS_E10_SIGNAL_MULTIPLIER)
        #if (TSS_E10_SIGNAL_MULTIPLIER > 0)
          TSS_E10_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 11
      #if defined(TSS_E11_SIGNAL_MULTIPLIER)
        #if (TSS_E11_SIGNAL_MULTIPLIER > 0)
          TSS_E11_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 12
      #if defined(TSS_E12_SIGNAL_MULTIPLIER)
        #if (TSS_E12_SIGNAL_MULTIPLIER > 0)
          TSS_E12_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 13
      #if defined(TSS_E13_SIGNAL_MULTIPLIER)
        #if (TSS_E13_SIGNAL_MULTIPLIER > 0)
          TSS_E13_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 14
      #if defined(TSS_E14_SIGNAL_MULTIPLIER)
        #if (TSS_E14_SIGNAL_MULTIPLIER > 0)
          TSS_E14_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 15
      #if defined(TSS_E15_SIGNAL_MULTIPLIER)
        #if (TSS_E15_SIGNAL_MULTIPLIER > 0)
          TSS_E15_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 16
      #if defined(TSS_E16_SIGNAL_MULTIPLIER)
        #if (TSS_E16_SIGNAL_MULTIPLIER > 0)
          TSS_E16_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 17
      #if defined(TSS_E17_SIGNAL_MULTIPLIER)
        #if (TSS_E17_SIGNAL_MULTIPLIER > 0)
          TSS_E17_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 18
      #if defined(TSS_E18_SIGNAL_MULTIPLIER)
        #if (TSS_E18_SIGNAL_MULTIPLIER > 0)
          TSS_E18_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 19
      #if defined(TSS_E19_SIGNAL_MULTIPLIER)
        #if (TSS_E19_SIGNAL_MULTIPLIER > 0)
          TSS_E19_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 20
      #if defined(TSS_E20_SIGNAL_MULTIPLIER)
        #if (TSS_E20_SIGNAL_MULTIPLIER > 0)
          TSS_E20_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 21
      #if defined(TSS_E21_SIGNAL_MULTIPLIER)
        #if (TSS_E21_SIGNAL_MULTIPLIER > 0)
          TSS_E21_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 22
      #if defined(TSS_E22_SIGNAL_MULTIPLIER)
        #if (TSS_E22_SIGNAL_MULTIPLIER > 0)
          TSS_E22_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 23
      #if defined(TSS_E23_SIGNAL_MULTIPLIER)
        #if (TSS_E23_SIGNAL_MULTIPLIER > 0)
          TSS_E23_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 24
      #if defined(TSS_E24_SIGNAL_MULTIPLIER)
        #if (TSS_E24_SIGNAL_MULTIPLIER > 0)
          TSS_E24_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 25
      #if defined(TSS_E25_SIGNAL_MULTIPLIER)
        #if (TSS_E25_SIGNAL_MULTIPLIER > 0)
          TSS_E25_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 26
      #if defined(TSS_E26_SIGNAL_MULTIPLIER)
        #if (TSS_E26_SIGNAL_MULTIPLIER > 0)
          TSS_E26_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 27
      #if defined(TSS_E27_SIGNAL_MULTIPLIER)
        #if (TSS_E27_SIGNAL_MULTIPLIER > 0)
          TSS_E27_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 28
      #if defined(TSS_E28_SIGNAL_MULTIPLIER)
        #if (TSS_E28_SIGNAL_MULTIPLIER > 0)
          TSS_E28_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 29
      #if defined(TSS_E29_SIGNAL_MULTIPLIER)
        #if (TSS_E29_SIGNAL_MULTIPLIER > 0)
          TSS_E29_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 30
      #if defined(TSS_E30_SIGNAL_MULTIPLIER)
        #if (TSS_E30_SIGNAL_MULTIPLIER > 0)
          TSS_E30_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 31
      #if defined(TSS_E31_SIGNAL_MULTIPLIER)
        #if (TSS_E31_SIGNAL_MULTIPLIER > 0)
          TSS_E31_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 32
      #if defined(TSS_E32_SIGNAL_MULTIPLIER)
        #if (TSS_E32_SIGNAL_MULTIPLIER > 0)
          TSS_E32_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 33
      #if defined(TSS_E33_SIGNAL_MULTIPLIER)
        #if (TSS_E33_SIGNAL_MULTIPLIER > 0)
          TSS_E33_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 34
      #if defined(TSS_E34_SIGNAL_MULTIPLIER)
        #if (TSS_E34_SIGNAL_MULTIPLIER > 0)
          TSS_E34_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 35
      #if defined(TSS_E35_SIGNAL_MULTIPLIER)
        #if (TSS_E35_SIGNAL_MULTIPLIER > 0)
          TSS_E35_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 36
      #if defined(TSS_E36_SIGNAL_MULTIPLIER)
        #if (TSS_E36_SIGNAL_MULTIPLIER > 0)
          TSS_E36_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 37
      #if defined(TSS_E37_SIGNAL_MULTIPLIER)
        #if (TSS_E37_SIGNAL_MULTIPLIER > 0)
          TSS_E37_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 38
      #if defined(TSS_E38_SIGNAL_MULTIPLIER)
        #if (TSS_E38_SIGNAL_MULTIPLIER > 0)
          TSS_E38_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 39
      #if defined(TSS_E39_SIGNAL_MULTIPLIER)
        #if (TSS_E39_SIGNAL_MULTIPLIER > 0)
          TSS_E39_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 40
      #if defined(TSS_E40_SIGNAL_MULTIPLIER)
        #if (TSS_E40_SIGNAL_MULTIPLIER > 0)
          TSS_E40_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 41
      #if defined(TSS_E41_SIGNAL_MULTIPLIER)
        #if (TSS_E41_SIGNAL_MULTIPLIER > 0)
          TSS_E41_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 42
      #if defined(TSS_E42_SIGNAL_MULTIPLIER)
        #if (TSS_E42_SIGNAL_MULTIPLIER > 0)
          TSS_E42_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 43
      #if defined(TSS_E43_SIGNAL_MULTIPLIER)
        #if (TSS_E43_SIGNAL_MULTIPLIER > 0)
          TSS_E43_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 44
      #if defined(TSS_E44_SIGNAL_MULTIPLIER)
        #if (TSS_E44_SIGNAL_MULTIPLIER > 0)
          TSS_E44_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 45
      #if defined(TSS_E45_SIGNAL_MULTIPLIER)
        #if (TSS_E45_SIGNAL_MULTIPLIER > 0)
          TSS_E45_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 46
      #if defined(TSS_E46_SIGNAL_MULTIPLIER)
        #if (TSS_E46_SIGNAL_MULTIPLIER > 0)
          TSS_E46_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 47
      #if defined(TSS_E47_SIGNAL_MULTIPLIER)
        #if (TSS_E47_SIGNAL_MULTIPLIER > 0)
          TSS_E47_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 48
      #if defined(TSS_E48_SIGNAL_MULTIPLIER)
        #if (TSS_E48_SIGNAL_MULTIPLIER > 0)
          TSS_E48_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 49
      #if defined(TSS_E49_SIGNAL_MULTIPLIER)
        #if (TSS_E49_SIGNAL_MULTIPLIER > 0)
          TSS_E49_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 50
      #if defined(TSS_E50_SIGNAL_MULTIPLIER)
        #if (TSS_E50_SIGNAL_MULTIPLIER > 0)
          TSS_E50_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 51
      #if defined(TSS_E51_SIGNAL_MULTIPLIER)
        #if (TSS_E51_SIGNAL_MULTIPLIER > 0)
          TSS_E51_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 52
      #if defined(TSS_E52_SIGNAL_MULTIPLIER)
        #if (TSS_E52_SIGNAL_MULTIPLIER > 0)
          TSS_E52_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 53
      #if defined(TSS_E53_SIGNAL_MULTIPLIER)
        #if (TSS_E53_SIGNAL_MULTIPLIER > 0)
          TSS_E53_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 54
      #if defined(TSS_E54_SIGNAL_MULTIPLIER)
        #if (TSS_E54_SIGNAL_MULTIPLIER > 0)
          TSS_E54_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 55
      #if defined(TSS_E55_SIGNAL_MULTIPLIER)
        #if (TSS_E55_SIGNAL_MULTIPLIER > 0)
          TSS_E55_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 56
      #if defined(TSS_E56_SIGNAL_MULTIPLIER)
        #if (TSS_E56_SIGNAL_MULTIPLIER > 0)
          TSS_E56_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 57
      #if defined(TSS_E57_SIGNAL_MULTIPLIER)
        #if (TSS_E57_SIGNAL_MULTIPLIER > 0)
          TSS_E57_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 58
      #if defined(TSS_E58_SIGNAL_MULTIPLIER)
        #if (TSS_E58_SIGNAL_MULTIPLIER > 0)
          TSS_E58_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 59
      #if defined(TSS_E59_SIGNAL_MULTIPLIER)
        #if (TSS_E59_SIGNAL_MULTIPLIER > 0)
          TSS_E59_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 60
      #if defined(TSS_E60_SIGNAL_MULTIPLIER)
        #if (TSS_E60_SIGNAL_MULTIPLIER > 0)
          TSS_E60_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 61
      #if defined(TSS_E61_SIGNAL_MULTIPLIER)
        #if (TSS_E61_SIGNAL_MULTIPLIER > 0)
          TSS_E61_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 62
      #if defined(TSS_E62_SIGNAL_MULTIPLIER)
        #if (TSS_E62_SIGNAL_MULTIPLIER > 0)
          TSS_E62_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
    #if TSS_N_ELECTRODES > 63
      #if defined(TSS_E63_SIGNAL_MULTIPLIER)
        #if (TSS_E63_SIGNAL_MULTIPLIER > 0)
          TSS_E63_SIGNAL_MULTIPLIER,
        #else
          TSS_SINAL_MULTIPLIER_NOT_USED,
        #endif
      #else
        TSS_SINAL_MULTIPLIER_NOT_USED,
      #endif
    #endif
};
#else
const UINT8 tss_cau8SignalMultiplier[1u];
#endif


/*
 * The section below defines an array of pointers to 
 * private dat for each control
 * 
 */
    
#if TSS_USE_CONTROL_PRIVATE_DATA    
    void * tss_apsControlPrivateData[TSS_N_CONTROLS] = 
    {
      NULL,
      #if TSS_N_CONTROLS > 1
          NULL,
      #endif
      #if TSS_N_CONTROLS > 2
          NULL,
      #endif
      #if TSS_N_CONTROLS > 3
          NULL,
      #endif
      #if TSS_N_CONTROLS > 4
          NULL,
      #endif
      #if TSS_N_CONTROLS > 5
          NULL,
      #endif
      #if TSS_N_CONTROLS > 6
          NULL,
      #endif
      #if TSS_N_CONTROLS > 7
          NULL,
      #endif
      #if TSS_N_CONTROLS > 8
          NULL,
      #endif
      #if TSS_N_CONTROLS > 9
          NULL,
      #endif
      #if TSS_N_CONTROLS > 10
          NULL,
      #endif
      #if TSS_N_CONTROLS > 11
          NULL,
      #endif
      #if TSS_N_CONTROLS > 12
          NULL,
      #endif
      #if TSS_N_CONTROLS > 13
          NULL,
      #endif
      #if TSS_N_CONTROLS > 14
          NULL,
      #endif
      #if TSS_N_CONTROLS > 15
          NULL,
      #endif
    };
#else
    void * tss_apsControlPrivateData[1u];
#endif    
    
/*
 * Declaration of main structures and arrays used by TSS 
 */

TSS_CSSystem tss_CSSys;
UINT8 tss_au8Sensitivity[TSS_N_ELECTRODES];
UINT8 tss_au8ElectrodeEnablers[((TSS_N_ELECTRODES - 1)/ 8) + 1];
UINT8 tss_au8ElectrodeStatus[((TSS_N_ELECTRODES - 1)/ 8) + 1];
UINT16 tss_au16ElecBaseline[TSS_N_ELECTRODES];
UINT8 tss_au8ElectrodeMeasured[((TSS_N_ELECTRODES - 1)/ 8) + 1];

/* Declaration of arrays used to store electrode behavior values */
INT8  tss_ai8CalPrevDelta[TSS_N_ELECTRODES];
UINT8 tss_au8DebounceCount[TSS_N_ELECTRODES];
UINT8 tss_au8TouchCount[TSS_N_ELECTRODES];
UINT8 tss_au8ReleaseCount[TSS_N_ELECTRODES];
UINT8 tss_au8ElecState[TSS_N_ELECTRODES];

/* Evaluate No of Controls */
#if TSS_N_CONTROLS != 0
    extern void TSS_ExecuteDecoders(void);
    void (* const tss_fExecuteDecoders) (void) = TSS_ExecuteDecoders;    
    
    extern void TSS_KeyDetectorDetectDecoder(UINT8 u8Status, UINT8 u8ElecCount);
    void (* const tss_fKeyDetectorDetectDecoder) (UINT8 u8Status, UINT8 u8ElecCount) = TSS_KeyDetectorDetectDecoder;    

    extern UINT8 TSS_KeyDetectorDecoderDataInit(UINT8 *u8GrpCount, UINT8 *u8GrpByteSel, UINT8 *u8GrpBitSel, UINT8 u8ElecCount, UINT8 u8ElectrodeCommand);
    UINT8 (* const tss_fDecoderDataInit) (UINT8 *u8GrpCount, UINT8 *u8GrpByteSel, UINT8 *u8GrpBitSel, UINT8 u8ElecCount, UINT8 u8ElectrodeCommand) = TSS_KeyDetectorDecoderDataInit;  

    UINT8 tss_au8ControlScheduleCount[TSS_N_CONTROLS];
    UINT8 tss_au8ControlIdleCounter[TSS_N_CONTROLS];
    UINT8 tss_au8ControlIdleState[((TSS_N_CONTROLS - 1)/ 8) + 1];
    UINT16 tss_au16ControlBuffers[TSS_N_CONTROLS * 2];
#else
    void (* const tss_fExecuteDecoders) (void) = NULL;
    void (* const tss_fKeyDetectorDetectDecoder) (UINT8 u8Status, UINT8 u8ElecCount) = NULL;    
    UINT8 (* const tss_fDecoderDataInit) (UINT8 *u8GrpCount, UINT8 *u8GrpByteSel, UINT8 *u8GrpBitSel, UINT8 u8ElecCount, UINT8 u8ElectrodeCommand) = NULL;  
    
    UINT8 tss_au8ControlScheduleCount[1];
    UINT8 tss_au8ControlIdleCounter[1];
    UINT8 tss_au8ControlIdleState[1];
    UINT16 tss_au16ControlBuffers[1];
#endif

const UINT8 tss_cu8NumElecs = (UINT8)TSS_N_ELECTRODES;
const UINT8 tss_cu8NumCtrls = (UINT8)TSS_N_CONTROLS;
const UINT8 tss_cu8ElecBitFldLn = (UINT8)(((UINT8)TSS_N_ELECTRODES - 1U) / 8U) + 1U;
const UINT16 tss_cu16Version = __TSS_VERSION__;

#if TSS_N_CONTROLS != 0
    const UINT8 tss_cu8CtrlBitFldLn = (UINT8)(((UINT8)TSS_N_CONTROLS - 1U) / 8u) + 1u;
#else
    const UINT8 tss_cu8CtrlBitFldLn = 1U;
#endif

/*
 * The section below defines separation of the functions 
 * called in low level functions according to selected TSS features by user
 * 
 */

#if TSS_USE_IIR_FILTER
    extern void TSS_KeyDetectorCalculateIIRFilter(UINT8 u8ElecNum);
   
    void (* const tss_fCalculateIIRFilter) (UINT8 u8ElecNum) = TSS_KeyDetectorCalculateIIRFilter;
#else
    void (* const tss_fCalculateIIRFilter) (UINT8 u8ElecNum) = NULL;
#endif

#if TSS_USE_SIGNAL_SHIELDING
    extern void TSS_KeyDetectorCalculateShielding(UINT8 u8ElecNum); 
    
    void (* const tss_fCalculateShielding) (UINT8 u8ElecNum) = TSS_KeyDetectorCalculateShielding;  
#else 
    void (* const tss_fCalculateShielding) (UINT8 u8ElecNum) = NULL;
#endif
   
#if TSS_USE_SIGNAL_SHIELDING || TSS_USE_IIR_FILTER
    extern void TSS_KeyDetectorInitPrevCapSample(UINT8 u8ElecNum);

    void (* const tss_fInitPrevCapSample) (UINT8 u8ElecNum) = TSS_KeyDetectorInitPrevCapSample;    

    UINT16 tss_au16PrevCapSample[TSS_N_ELECTRODES];
#else
    void (* const tss_fInitPrevCapSample) (UINT8 u8ElecNum) = NULL;    

    UINT16 tss_au16PrevCapSample[1]; /* Dummy */
#endif    

#if TSS_USE_DELTA_LOG
    extern void TSS_KeyDetectorFillDeltaLogBuffer(UINT8 u8ElecNum, INT8 i8Delta);
   
    void (* const tss_fFillDeltaLoglBuffer) (UINT8 u8ElecNum, INT8 i8Delta) = TSS_KeyDetectorFillDeltaLogBuffer;

    INT8 tss_ai8InstantDelta[TSS_N_ELECTRODES];
#else
    void (* const tss_fFillDeltaLoglBuffer) (UINT8 u8ElecNum, INT8 i8Delta) = NULL;

    INT8 tss_ai8InstantDelta[1]; /* Dummy */
#endif

#if TSS_USE_SIGNAL_LOG 
    extern void TSS_KeyDetectorFillSignalLogBuffer(UINT8 u8ElecNum);
    
    void (* const tss_fFillSignalLoglBuffer) (UINT8 u8ElecNum) = TSS_KeyDetectorFillSignalLogBuffer;
        
    UINT16 tss_au16InstantSignal[TSS_N_ELECTRODES];
#else
    void (* const tss_fFillSignalLoglBuffer) (UINT8 u8ElecNum) = NULL;
    
    UINT16 tss_au16InstantSignal[1]; /* Dummy */
#endif

#if TSS_USE_DATA_CORRUPTION_CHECK
    extern void TSS_DataCorruptionCheck(UINT8 u8Command);
    
    void (* const tss_fDataCorruptionCheck) (UINT8 u8Command) = TSS_DataCorruptionCheck;
    
    UINT8 tss_u8ConfCheckSum;
#else
    void (* const tss_fDataCorruptionCheck) (UINT8 u8Command) = NULL;

    UINT8 tss_u8ConfCheckSum; /* Dummy */
#endif

#if TSS_USE_FREEMASTER_GUI
    extern void TSS_FmstrCall(void);
    
    void (* const tss_fFmstrCall) (void) = TSS_FmstrCall;
#else
    void (* const tss_fFmstrCall) (void) = NULL;
#endif
    
#if TSS_USE_TRIGGER_FUNCTION
    extern UINT8 TSS_TriggerConfig(UINT8 u8Parameter, UINT8 u8Value);
    extern UINT8 TSS_TriggerControl(UINT8 u8Command);
    
    UINT8 (* const tss_fTriggerConfig) (UINT8 u8Parameter, UINT8 u8Value) = TSS_TriggerConfig;
    UINT8 (* const tss_fTriggerControl) (UINT8 u8Command) = TSS_TriggerControl;
#else
    UINT8 (* const tss_fTriggerConfig) (UINT8 u8Parameter, UINT8 u8Value) = NULL;
    UINT8 (* const tss_fTriggerControl) (UINT8 u8Command) = NULL;
#endif

#if TSS_LOWPOWER_USED || defined(TSS_ONPROXIMITY_CALLBACK)
    extern UINT8 TSS_LowPowerConfig(UINT8 u8Parameter, UINT8 u8Value);
    
    UINT8 (* const tss_fLowPowerConfig) (UINT8 u8Parameter, UINT8 u8Value) = TSS_LowPowerConfig;
#else
    UINT8 (* const tss_fLowPowerConfig) (UINT8 u8Parameter, UINT8 u8Value) = NULL;
#endif

#ifdef TSS_ONFAULT_CALLBACK
    extern void TSS_ONFAULT_CALLBACK(UINT8 u8FaultElecNum);
  
    void (* const tss_fOnFault) (UINT8 u8FaultElecNum) = TSS_ONFAULT_CALLBACK;
#else 
    void (* const tss_fOnFault) (UINT8 u8FaultElecNum) = NULL;
#endif
    
#ifdef TSS_ONINIT_CALLBACK
    extern void TSS_ONINIT_CALLBACK(void);
  
    void (* const tss_fOnInit) (void) = TSS_ONINIT_CALLBACK;
#else 
    extern void TSS_fOnInit(void);
    
    void (* const tss_fOnInit) (void) = TSS_fOnInit;
#endif

#if TSS_ASLIDER_POSITION_IIR_USED
    const UINT8 tss_cu8APosFilterWeight = TSS_ASLIDER_POSITION_IIR_WEIGHT;
    extern UINT16 TSS_ASliderCalculatePosIIRFilter(UINT8 u8CtrlId, UINT8 u8Command, UINT16 u16Position);
    
    UINT16 (* const tss_fASliderCalculatePosIIRFilter) (UINT8 u8CtrlId, UINT8 u8Command, UINT16 u16Position) = TSS_ASliderCalculatePosIIRFilter;
#else
    const UINT8 tss_cu8APosFilterWeight = 1u;
    UINT16 (* const tss_fASliderCalculatePosIIRFilter) (UINT8 u8CtrlId, UINT8 u8Command, UINT16 u16Position) = NULL;
#endif

#if TSS_ASLIDER_DELAY_USED
    const UINT8 tss_cu8ASliderDelayBufferLength = TSS_ASLIDER_DELAY_BUFFER_LENGTH;
    extern UINT8 TSS_ASliderDelayControl(UINT8 u8CtrlId, UINT8 u8Command, UINT8 *u8Pos);
    
    UINT8 (* const tss_fASliderDelayControl) (UINT8 u8CtrlId, UINT8 u8Command, UINT8 *u8Pos) = TSS_ASliderDelayControl;
#else
    const UINT8 tss_cu8ASliderDelayBufferLength = 1u;
    UINT8 (* const tss_fASliderDelayControl) (UINT8 u8CtrlId, UINT8 u8Command, UINT8 *u8Pos) = NULL;
#endif

#if TSS_ASLIDER_TREND_USED
    const UINT8 tss_cu8ASliderTrendBufferLength = TSS_ASLIDER_TREND_BUFFER_LENGTH;
    #if TSS_ASLIDER_TREND_THRESHOLD
      const INT8 tss_i8ASliderTrendThreshold = TSS_ASLIDER_TREND_THRESHOLD;  
      UINT8 (* const tss_fASliderTrendThreshold) (UINT8 u8MaxPos1, UINT8 u8MaxPos2) = NULL;        
    #else
      const INT8 tss_i8ASliderTrendThreshold = 40;  /* Coeficient for automatic threshold calculation */
      extern UINT8 TSS_ASliderTrendThreshold(UINT8 u8MaxPos1, UINT8 u8MaxPos2);
        
      UINT8 (* const tss_fASliderTrendThreshold) (UINT8 u8MaxPos1, UINT8 u8MaxPos2) = TSS_ASliderTrendThreshold;        
    #endif
    
    extern UINT8 TSS_ASliderTrendControl(UINT8 u8CtrlId, UINT8 u8Command, UINT8 u8MaxPos1, UINT8 u8MaxPos2);
    
    UINT8 (* const tss_fASliderTrendControl) (UINT8 u8CtrlId, UINT8 u8Command, UINT8 u8MaxPos1, UINT8 u8MaxPos2) = TSS_ASliderTrendControl;
#else
    const UINT8 tss_cu8ASliderTrendBufferLength = 1u;    
    UINT8 (* const tss_fASliderTrendControl) (UINT8 u8CtrlId, UINT8 u8Command, UINT8 u8MaxPos1, UINT8 u8MaxPos2) = NULL;  
#endif

#if TSS_MATRIX_POSITION_IIR_USED
    const UINT8 tss_cu8MatrixPosFilterWeight = TSS_MATRIX_POSITION_IIR_WEIGHT;
    
    extern UINT16 TSS_MatrixCalculatePosIIRFilter(UINT16 u16Position, UINT16 *pu16PrevPosition);
    UINT16 (* const tss_fMatrixCalculatePosIIRFilter) (UINT16 u16Position, UINT16 *pu16PrevPosition) = TSS_MatrixCalculatePosIIRFilter;
#else
    const UINT8 tss_cu8MatrixPosFilterWeight = 1u;
    UINT16 (* const tss_fMatrixCalculatePosIIRFilter) (UINT16 u16Position, UINT16 *pu16PrevPosition) = NULL;
#endif    
    
#ifdef TSS_ONPROXIMITY_CALLBACK
    extern void TSS_ONPROXIMITY_CALLBACK(void);
    extern UINT8 TSS_ProximityConfig(UINT8 u8Value);
    
    void (* const tss_fOnProximity) (void) = TSS_ONPROXIMITY_CALLBACK;
    UINT8 (* const tss_fProximityConfig) (UINT8 u8Value) = TSS_ProximityConfig;
#else 
    void (* const tss_fOnProximity) (void) = NULL;
    UINT8 (* const tss_fProximityConfig) (UINT8 u8Value) = NULL;
#endif
    
#if TSS_USE_STUCK_KEY
    extern void TSS_KeyDetectorStuckKeyControl(UINT8 u8ElecNum, INT8 i8Delta, UINT8 u8RetVal);
    extern void TSS_KeyDetectorResetStuckKeyCounter(UINT8 u8ElecNum);
    
    void (* const tss_fStuckKeyControl) (UINT8 u8ElecNum, INT8 i8Delta, UINT8 u8RetVal) = TSS_KeyDetectorStuckKeyControl;
    void (* const tss_fResetStuckKeyCounter) (UINT8 u8ElecNum) = TSS_KeyDetectorResetStuckKeyCounter;
    
    UINT8 tss_au8StuckCount[TSS_N_ELECTRODES];    
#else
    void (* const tss_fStuckKeyControl) (UINT8 u8ElecNum, INT8 i8Delta, UINT8 u8RetVal) = NULL;
    void (* const tss_fResetStuckKeyCounter) (UINT8 u8ElecNum) = NULL;

    UINT8 tss_au8StuckCount[1];  /* Dummy */
#endif

#if TSS_USE_NEGATIVE_BASELINE_DROP
    extern void TSS_KeyDetectorNegativeBaselineDrop(UINT8 u8ElecNum, INT8 i8Delta);

    void (* const tss_fNegativeBaselineDrop) (UINT8 u8ElecNum, INT8 i8Delta) = TSS_KeyDetectorNegativeBaselineDrop;
#else
    void (* const tss_fNegativeBaselineDrop) (UINT8 u8ElecNum, INT8 i8Delta) = NULL;
#endif

#if TSS_USE_AUTO_HW_RECALIBRATION
    extern UINT8 TSS_KeyDetectorRecalibrationRequest(UINT8 u8ElecNum);
    
    UINT8 (* const tss_fKeyDetectorRecalibrationRequest) (UINT8 u8ElecNum) = TSS_KeyDetectorRecalibrationRequest;
#else
    UINT8 (* const tss_fKeyDetectorRecalibrationRequest) (UINT8 u8ElecNum) = NULL;
#endif
    
#if TSS_USE_SIGNAL_DIVIDER
    extern void TSS_KeyDetectorSignalDivider(UINT8 u8ElecNum);

    void (* const tss_fSignalDivider) (UINT8 u8ElecNum) = TSS_KeyDetectorSignalDivider;
#else
    void (* const tss_fSignalDivider) (UINT8 u8ElecNum) = NULL;
#endif    

#if TSS_USE_SIGNAL_MULTIPLIER
    extern void TSS_KeyDetectorSignalMultiplier(UINT8 u8ElecNum);

    void (* const tss_fSignalMultiplier) (UINT8 u8ElecNum) = TSS_KeyDetectorSignalMultiplier;
#else
    void (* const tss_fSignalMultiplier) (UINT8 u8ElecNum) = NULL;
#endif    
    
/*************************** AUTOCALIBRATION **************************/

#if TSS_USE_AUTO_SENS_CALIBRATION
    extern UINT8 TSS_AutoCalibration(UINT8 u8ElecNum, UINT8 u8Command);

    UINT8 (* const tss_fAutoCalibration) (UINT8 u8ElecNum, UINT8 u8Command) = TSS_AutoCalibration;
    INT8 tss_ai8MaxDeltaAmplitude[TSS_N_ELECTRODES];
    INT8 tss_ai8DeltaAmplitude[TSS_N_ELECTRODES];
    
    TSS_AutoSensCalibrationData tss_asAutoCalibrationData[TSS_N_ELECTRODES];
    
    #if TSS_USE_AUTO_SENS_CALIB_INIT_DURATION
        INT8 tss_ai8NoiseAmplitude[TSS_N_ELECTRODES];
    #else 
        INT8 tss_ai8NoiseAmplitude[1];
    #endif    

#else 
    UINT8 (* const tss_fAutoCalibration) (UINT8 u8ElecNum, UINT8 u8Command) = NULL;
    INT8 tss_ai8MaxDeltaAmplitude[1];
    INT8 tss_ai8DeltaAmplitude[1];		
    INT8 tss_ai8NoiseAmplitude[1];
    TSS_AutoSensCalibrationData tss_asAutoCalibrationData[1];		
#endif

#if TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH    
  extern UINT8 TSS_DeltaNoiseAnalysisBufferControl(UINT8 u8ElecCount, INT8 i8Delta, UINT8 u8Command);        

  UINT8 (* const tss_fDeltaNoiseAnalysisBufferControl) (UINT8 u8ElecCount, INT8 i8Delta, UINT8 u8Command) = TSS_DeltaNoiseAnalysisBufferControl;        
  INT8 tss_ai8DeltaNoiseAnalysisBuffer[TSS_N_ELECTRODES * TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH];

  TSS_DeltaNoiseAnalysisBufferData tss_asDeltaNoiseAnalysisBufferData[TSS_N_ELECTRODES];
#else      
  UINT8 (* const tss_fDeltaNoiseAnalysisBufferControl) (UINT8 u8ElecCount, INT8 i8Delta, UINT8 u8Command) = NULL;        
  INT8 tss_ai8DeltaNoiseAnalysisBuffer[1];  
  TSS_DeltaNoiseAnalysisBufferData tss_asDeltaNoiseAnalysisBufferData[1];  
#endif

#if TSS_USE_DELTA_NOISE_ANALYSIS_IIR    
  extern UINT8 TSS_DeltaNoiseAnalysisIIRControl(UINT8 u8ElecCount, INT8 i8Delta, UINT8 u8Command);        

  UINT8 (* const tss_fDeltaNoiseAnalysisIIRControl) (UINT8 u8ElecCount, INT8 i8Delta, UINT8 u8Command) = TSS_DeltaNoiseAnalysisIIRControl;        

  TSS_DeltaNoiseAnalysisIIRData tss_asDeltaNoiseAnalysisIIRData[TSS_N_ELECTRODES];
#else      
  UINT8 (* const tss_fDeltaNoiseAnalysisIIRControl) (UINT8 u8ElecCount, INT8 i8Delta, UINT8 u8Command) = NULL;
  TSS_DeltaNoiseAnalysisIIRData tss_asDeltaNoiseAnalysisIIRData[1];  
#endif

const UINT8 tss_u8BaselineInitLength = TSS_USE_BASELINE_INIT_DURATION;
const UINT8 tss_u8AutoCalibInitLength = TSS_USE_AUTO_SENS_CALIB_INIT_DURATION;
const UINT8 tss_u8DeltaNoiseAnalysisBufferLength = TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH;
const INT8 tss_i8DeltaNoiseAnalysisIIRWeight1 = TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1;
const INT8 tss_i8DeltaNoiseAnalysisIIRWeight2 = TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2;
const TSS_AutoSensCalibContext tss_csASCContext = {4,100u,255u,2,2,0u};


/***************************************************************************//*!
*
* @brief  Performs a calculation of new capacitance value by user defined 
*         IIR filter equation from the current capacitance value and 
*         previous capacitance value for a certain electrode 
*
* @param  u16CurrentCapSample - Current measured oversampled capacitance value
*         u8ElecNum - Defines electrode number
*
* @return New calculated capacitance value
*
* @remarks Array tss_au16PrevCapSample[] is used as global storage for 
*          backup of previous capacitance values. The parameter u8ElecNum of 
*          TSS_IIRFilterEquation() should be used as pointer on the currently 
*          used previous capacitance value e.g. tss_au16PrevCapSample[u8ElecNum].
*          The principle of IIR Filter is to modify u16CurrentCapSample by any 
*          weight of tss_au16PrevCapSample[u8ElecNum] and the calculated value is
*          returned to the library by the return value of TSS_IIRFilterEquation().
*          The user may edit the equation according to his requirements,
*          but he has to follow previous rules.
*          Warning: Design new equation with respect to unsigned integer value 
*                   range of variables and number of samples used by TSS.
*
****************************************************************************/
#if TSS_USE_IIR_FILTER
#define IIR_WEIGHT 3u
    UINT16 TSS_IIRFilterEquation(UINT16 u16CurrentCapSample, UINT8 u8ElecNum)
    {
#if TSS_HCS08_MCU
    if (u16CurrentCapSample > (0xFFFF/IIR_WEIGHT))
    {
        u16CurrentCapSample = 0xFFFF/IIR_WEIGHT;
    }
    return (UINT16) ((u16CurrentCapSample + (IIR_WEIGHT * tss_au16PrevCapSample[u8ElecNum])) /(IIR_WEIGHT+1));
#else
      return (UINT16) ((u16CurrentCapSample + ((UINT32)IIR_WEIGHT * tss_au16PrevCapSample[u8ElecNum])) /(IIR_WEIGHT+1));
#endif
    }
#else
    /* Dummy Function - just for relations, anyway removed from flash */
    UINT16 TSS_IIRFilterEquation(UINT16 u16CurrentCapSample, UINT8 u8ElecNum)
    {
      (void) u16CurrentCapSample;
      (void) u8ElecNum;
      
      return TSS_STATUS_OK; 
    }
#endif
