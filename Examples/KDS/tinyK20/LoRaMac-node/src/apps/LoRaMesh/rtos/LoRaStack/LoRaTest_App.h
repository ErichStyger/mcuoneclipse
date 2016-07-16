/**
 * \file LoRaTest_App.h
 * \author Alexander Winiger alexander.winiger@hslu.ch
 * \date Dec 11, 2015
 * \version 1.0
 *
 * \brief
 *
 *******************************************************************************
 *  Change log:
 *      [1.0]   Dec 11, 2015      	Alexander Winiger
 *          - created
 *******************************************************************************
 */
#ifndef __LORATEST_APP_H_
#define __LORATEST_APP_H_

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "LoRaMesh_AppConfig.h"

#if LORAMESH_TEST_APP_ACTIVATED
/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * MODULE FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * \brief Initialize LoRa stack test application.
 */
void LoRaTest_AppInit( void );

#if 0
/*!
 * \brief Add a test regular LoRa join accept message to the rx message queue.
 */
void LoRaTest_AddJoinAcc( uint8_t* devEui, uint8_t* appEui, uint8_t appKey,
        bool addChannelList );
#endif

/*!
 * \brief Add a test data frame to the rx message queue.
 *
 * \param devAddr Device address
 */
void LoRaTest_AddDataFrame(uint32_t devAddr);

#if 0
/*!
 * \brief Add a test frame to the rx message queue.
 */
void LoRaTest_AddFrame( void );
#endif

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
#endif /* LORAMESH_TEST_APP_ACTIVATED */
#endif /* __LORATEST_APP_H_ */
