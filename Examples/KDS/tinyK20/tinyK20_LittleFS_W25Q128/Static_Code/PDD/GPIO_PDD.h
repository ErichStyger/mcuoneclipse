/*
  PDD layer implementation for peripheral type GPIO
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(GPIO_PDD_H_)
#define GPIO_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error GPIO PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK10D5) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK10D7) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK10F12) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK10DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK11DA5) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MK11DA5WS) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MK11D5) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK11D5WS) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK12D5) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK20D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK20D5) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK20D7) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK20F12) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK20DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK21DA5) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MK21DA5WS) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MK21D5) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK21D5WS) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK21FA12) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MK21FA12WS) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MK21F12) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK21F12WS) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK22D5) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK22F12810) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK22F12) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK22F25612) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK22F51212) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK24F12) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK30D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK30D7) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK30DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK40D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK40D7) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK40DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK40X256VMD100) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK50D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK50D7) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK50DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK51D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK51D7) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK51DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK52D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK52DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK53D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK53DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK60D10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK60F12) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK60F15) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK60DZ10) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK60N512VMD100) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK61F12) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK61F15) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK61F12WS) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK61F15WS) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK63F12) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK63F12WS) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK64F12) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MK70F12) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK70F15) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK70F12WS) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MK70F15WS) /* PTA, PTB, PTC, PTD, PTE, PTF */ && \
      !defined(MCU_MKE02Z2) /* GPIOA, GPIOB */ && \
      !defined(MCU_MKE02Z4) /* GPIOA, GPIOB */ && \
      !defined(MCU_SKEAZN642) /* GPIOA, GPIOB */ && \
      !defined(MCU_MKE04Z1284) /* GPIOA, GPIOB, GPIOC */ && \
      !defined(MCU_MKE04Z4) /* GPIOA */ && \
      !defined(MCU_SKEAZN84) /* GPIOA */ && \
      !defined(MCU_MKE06Z4) /* GPIOA, GPIOB, GPIOC */ && \
      !defined(MCU_MKL02Z4) /* PTA, PTB */ && \
      !defined(MCU_MKL04Z4) /* PTA, PTB */ && \
      !defined(MCU_MKL05Z4) /* PTA, PTB */ && \
      !defined(MCU_MKL14Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL15Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL16Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL24Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL25Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL26Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL34Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL36Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKL46Z4) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKV10Z7) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKV31F12810) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKV31F25612) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKV31F51212) /* PTA, PTB, PTC, PTD, PTE */ && \
      !defined(MCU_MKW01Z4) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKW21D5) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKW21D5WS) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKW22D5) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKW22D5WS) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKW24D5) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_MKW24D5WS) /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE */ && \
      !defined(MCU_SKEAZ1284) /* GPIOA, GPIOB, GPIOC */
  // Unsupported MCU is active
  #error GPIO PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Pin masks */
#define GPIO_PDD_PIN_0  0x1U                     /**< Pin 0 mask */
#define GPIO_PDD_PIN_1  0x2U                     /**< Pin 1 mask */
#define GPIO_PDD_PIN_2  0x4U                     /**< Pin 2 mask */
#define GPIO_PDD_PIN_3  0x8U                     /**< Pin 3 mask */
#define GPIO_PDD_PIN_4  0x10U                    /**< Pin 4 mask */
#define GPIO_PDD_PIN_5  0x20U                    /**< Pin 5 mask */
#define GPIO_PDD_PIN_6  0x40U                    /**< Pin 6 mask */
#define GPIO_PDD_PIN_7  0x80U                    /**< Pin 7 mask */
#define GPIO_PDD_PIN_8  0x100U                   /**< Pin 8 mask */
#define GPIO_PDD_PIN_9  0x200U                   /**< Pin 9 mask */
#define GPIO_PDD_PIN_10 0x400U                   /**< Pin 10 mask */
#define GPIO_PDD_PIN_11 0x800U                   /**< Pin 11 mask */
#define GPIO_PDD_PIN_12 0x1000U                  /**< Pin 12 mask */
#define GPIO_PDD_PIN_13 0x2000U                  /**< Pin 13 mask */
#define GPIO_PDD_PIN_14 0x4000U                  /**< Pin 14 mask */
#define GPIO_PDD_PIN_15 0x8000U                  /**< Pin 15 mask */
#define GPIO_PDD_PIN_16 0x10000U                 /**< Pin 16 mask */
#define GPIO_PDD_PIN_17 0x20000U                 /**< Pin 17 mask */
#define GPIO_PDD_PIN_18 0x40000U                 /**< Pin 18 mask */
#define GPIO_PDD_PIN_19 0x80000U                 /**< Pin 19 mask */
#define GPIO_PDD_PIN_20 0x100000U                /**< Pin 20 mask */
#define GPIO_PDD_PIN_21 0x200000U                /**< Pin 21 mask */
#define GPIO_PDD_PIN_22 0x400000U                /**< Pin 22 mask */
#define GPIO_PDD_PIN_23 0x800000U                /**< Pin 23 mask */
#define GPIO_PDD_PIN_24 0x1000000U               /**< Pin 24 mask */
#define GPIO_PDD_PIN_25 0x2000000U               /**< Pin 25 mask */
#define GPIO_PDD_PIN_26 0x4000000U               /**< Pin 26 mask */
#define GPIO_PDD_PIN_27 0x8000000U               /**< Pin 27 mask */
#define GPIO_PDD_PIN_28 0x10000000U              /**< Pin 28 mask */
#define GPIO_PDD_PIN_29 0x20000000U              /**< Pin 29 mask */
#define GPIO_PDD_PIN_30 0x40000000U              /**< Pin 30 mask */
#define GPIO_PDD_PIN_31 0x80000000U              /**< Pin 31 mask */


/* ----------------------------------------------------------------------------
   -- GetPortDataInput
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets port data input independently of current direction setting nor
 * pin usage. It returns zeros for pins which are not configured for a digital
 * function.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: GPIOA_PDIR, GPIOB_PDIR,
 *          GPIOC_PDIR, GPIOD_PDIR, GPIOE_PDIR, GPIOF_PDIR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = GPIO_PDD_GetPortDataInput(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define GPIO_PDD_GetPortDataInput(PeripheralBase) ( \
    (uint32_t)GPIO_PDIR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetPortDataOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets port data output. The value is driven out to the corresponding
 * pin if direction of the pin is set to output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new data output value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDOR, GPIOB_PDOR,
 *          GPIOC_PDOR, GPIOD_PDOR, GPIOE_PDOR, GPIOF_PDOR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortDataOutput(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define GPIO_PDD_SetPortDataOutput(PeripheralBase, Value) ( \
    GPIO_PDOR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetPortDataOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets port data output independently of current direction setting.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: GPIOA_PDOR, GPIOB_PDOR,
 *          GPIOC_PDOR, GPIOD_PDOR, GPIOE_PDOR, GPIOF_PDOR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = GPIO_PDD_GetPortDataOutput(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define GPIO_PDD_GetPortDataOutput(PeripheralBase) ( \
    (uint32_t)GPIO_PDOR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearPortDataOutputMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears required bits of port data output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Parameter specifying port pins which should be cleared. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PCOR, GPIOB_PCOR,
 *          GPIOC_PCOR, GPIOD_PCOR, GPIOE_PCOR, GPIOF_PCOR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_ClearPortDataOutputMask(<peripheral>_BASE_PTR, GPIO_PDD_PIN_0);
 *      @endcode
 */
#define GPIO_PDD_ClearPortDataOutputMask(PeripheralBase, Mask) ( \
    GPIO_PCOR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- SetPortDataOutputMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets required bits of port data output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Parameter specifying port pins which should be set. Use constants
 *        from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PSOR, GPIOB_PSOR,
 *          GPIOC_PSOR, GPIOD_PSOR, GPIOE_PSOR, GPIOF_PSOR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortDataOutputMask(<peripheral>_BASE_PTR, GPIO_PDD_PIN_0);
 *      @endcode
 */
#define GPIO_PDD_SetPortDataOutputMask(PeripheralBase, Mask) ( \
    GPIO_PSOR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- TogglePortDataOutputMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Toggles required bits of port data output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Parameter specifying port pins which should be inverted. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PTOR, GPIOB_PTOR,
 *          GPIOC_PTOR, GPIOD_PTOR, GPIOE_PTOR, GPIOF_PTOR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_TogglePortDataOutputMask(<peripheral>_BASE_PTR,
 *      GPIO_PDD_PIN_0);
 *      @endcode
 */
#define GPIO_PDD_TogglePortDataOutputMask(PeripheralBase, Mask) ( \
    GPIO_PTOR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- SetPortInputDirectionMask
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets required pins as input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Parameter specifying port pins which should be set as input. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR, GPIOA_PIDR,
 *          GPIOB_PIDR, GPIOC_PIDR (depending on the peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortInputDirectionMask(<peripheral>_BASE_PTR,
 *      GPIO_PDD_PIN_0);
 *      @endcode
 */
  #define GPIO_PDD_SetPortInputDirectionMask(PeripheralBase, Mask) ( \
      (GPIO_PDDR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)(Mask))), \
      (GPIO_PIDR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)(Mask))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets required pins as input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Parameter specifying port pins which should be set as input. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR, GPIOA_PIDR,
 *          GPIOB_PIDR, GPIOC_PIDR (depending on the peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortInputDirectionMask(<peripheral>_BASE_PTR,
 *      GPIO_PDD_PIN_0);
 *      @endcode
 */
  #define GPIO_PDD_SetPortInputDirectionMask(PeripheralBase, Mask) ( \
      GPIO_PDDR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)(Mask)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPortOutputDirectionMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets required pins as output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Parameter specifying port pins which should be set as output. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortOutputDirectionMask(<peripheral>_BASE_PTR,
 *      GPIO_PDD_PIN_0);
 *      @endcode
 */
#define GPIO_PDD_SetPortOutputDirectionMask(PeripheralBase, Mask) ( \
    GPIO_PDDR_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- SetPortDirectionMask
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets direction on pins specified by mask parameters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param InputMask Mask of port pins defining which should be set as input. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @param OutputMask Mask of port pins defining which should be set as output.
 *        Use constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR, GPIOA_PIDR,
 *          GPIOB_PIDR, GPIOC_PIDR (depending on the peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortDirectionMask(<peripheral>_BASE_PTR, GPIO_PDD_PIN_0,
 *      GPIO_PDD_PIN_0);
 *      @endcode
 */
  #define GPIO_PDD_SetPortDirectionMask(PeripheralBase, InputMask, OutputMask) ( \
      (GPIO_PDDR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(GPIO_PDDR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)(InputMask)))) | ( \
        (uint32_t)(OutputMask)))), \
      (GPIO_PIDR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)(InputMask))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets direction on pins specified by mask parameters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param InputMask Mask of port pins defining which should be set as input. Use
 *        constants from group "Pin masks". This parameter is 32 bits wide.
 * @param OutputMask Mask of port pins defining which should be set as output.
 *        Use constants from group "Pin masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR, GPIOA_PIDR,
 *          GPIOB_PIDR, GPIOC_PIDR (depending on the peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortDirectionMask(<peripheral>_BASE_PTR, GPIO_PDD_PIN_0,
 *      GPIO_PDD_PIN_0);
 *      @endcode
 */
  #define GPIO_PDD_SetPortDirectionMask(PeripheralBase, InputMask, OutputMask) ( \
      GPIO_PDDR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(GPIO_PDDR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)(InputMask)))) | ( \
        (uint32_t)(OutputMask))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPortDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets direction of every pin in the port.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new direction for port pins. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      GPIO_PDD_SetPortDirection(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define GPIO_PDD_SetPortDirection(PeripheralBase, Value) ( \
    GPIO_PDDR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetPortDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets direction of every pin in the port.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: GPIOA_PDDR, GPIOB_PDDR,
 *          GPIOC_PDDR, GPIOD_PDDR, GPIOE_PDDR, GPIOF_PDDR (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = GPIO_PDD_GetPortDirection(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define GPIO_PDD_GetPortDirection(PeripheralBase) ( \
    (uint32_t)GPIO_PDDR_REG(PeripheralBase) \
  )
#endif  /* #if defined(GPIO_PDD_H_) */

/* GPIO_PDD.h, eof. */
