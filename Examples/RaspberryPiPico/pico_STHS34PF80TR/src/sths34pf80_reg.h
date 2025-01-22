/**
  ******************************************************************************
  * @file    sths34pf80_reg.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          sths34pf80_reg.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STHS34PF80_REGS_H
#define STHS34PF80_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup STHS34PF80
  * @{
  *
  */

/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*stmdev_mdelay_ptr)(uint32_t millisec);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Component optional fields **/
  stmdev_mdelay_ptr   mdelay;
  /** Customizable optional pointer **/
  void *handle;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */

/** @defgroup STHS34PF80_Infos
  * @{
  *
  */

/** I2C Device Address 8 bit format **/
#define STHS34PF80_I2C_ADD                    0xB5U

/** Device Identification (Who am I) **/
#define STHS34PF80_ID                         0xD3U

/**
  * @}
  *
  */

/** @defgroup bitfields page main
  * @{
  *
  */

#define STHS34PF80_LPF1    0x0CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lpf_m  : 3;
  uint8_t lpf_p_m  : 3;
  uint8_t not_used0  : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used0  : 2;
  uint8_t lpf_p_m  : 3;
  uint8_t lpf_m  : 3;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_lpf1_t;

#define STHS34PF80_LPF2    0x0DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lpf_a_t  : 3;
  uint8_t lpf_p  : 3;
  uint8_t not_used0  : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used0  : 2;
  uint8_t lpf_p  : 3;
  uint8_t lpf_a_t  : 3;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_lpf2_t;

#define STHS34PF80_WHO_AM_I    0x0FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t id  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t id  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_who_am_i_t;

#define STHS34PF80_AVG_TRIM    0x10U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t avg_tmos  : 3;
  uint8_t not_used0  : 1;
  uint8_t avg_t  : 2;
  uint8_t not_used1  : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used1  : 2;
  uint8_t avg_t  : 2;
  uint8_t not_used0  : 1;
  uint8_t avg_tmos  : 3;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_avg_trim_t;

#define STHS34PF80_CTRL0    0x17U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used0  : 4;
  uint8_t gain       : 3;
  uint8_t not_used1  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used1  : 1;
  uint8_t gain       : 3;
  uint8_t not_used0  : 4;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_ctrl0_t;

#define STHS34PF80_SENS_DATA    0x1DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sens  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t sens  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_sens_data_t;

#define STHS34PF80_CTRL1    0x20U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t odr  : 4;
  uint8_t bdu  : 1;
  uint8_t not_used0  : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used0  : 3;
  uint8_t bdu  : 1;
  uint8_t odr  : 4;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_ctrl1_t;

#define STHS34PF80_CTRL2    0x21U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t one_shot  : 1;
  uint8_t not_used0  : 3;
  uint8_t func_cfg_access  : 1;
  uint8_t not_used1  : 2;
  uint8_t boot  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot  : 1;
  uint8_t not_used1  : 2;
  uint8_t func_cfg_access  : 1;
  uint8_t not_used0  : 3;
  uint8_t one_shot  : 1;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_ctrl2_t;

#define STHS34PF80_CTRL3    0x22U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ien  : 2;
  uint8_t int_latched  : 1;
  uint8_t int_msk  : 3;
  uint8_t pp_od  : 1;
  uint8_t int_h_l  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int_h_l  : 1;
  uint8_t pp_od  : 1;
  uint8_t int_msk  : 3;
  uint8_t int_latched  : 1;
  uint8_t ien  : 2;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_ctrl3_t;

#define STHS34PF80_STATUS    0x23U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used0  : 2;
  uint8_t drdy  : 1;
  uint8_t not_used1  : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used1  : 5;
  uint8_t drdy  : 1;
  uint8_t not_used0  : 2;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_status_t;

#define STHS34PF80_FUNC_STATUS    0x25U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tamb_shock_flag  : 1;
  uint8_t mot_flag  : 1;
  uint8_t pres_flag  : 1;
  uint8_t not_used0  : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used0  : 5;
  uint8_t pres_flag  : 1;
  uint8_t mot_flag  : 1;
  uint8_t tamb_shock_flag  : 1;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_func_status_t;

#define STHS34PF80_TOBJECT_L    0x26U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tobject  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tobject  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tobject_l_t;

#define STHS34PF80_TOBJECT_H    0x27U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tobject  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tobject  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tobject_h_t;

#define STHS34PF80_TAMBIENT_L    0x28U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tambient  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tambient  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tambient_l_t;

#define STHS34PF80_TAMBIENT_H    0x29U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tambient  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tambient  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tambient_h_t;

#define STHS34PF80_TOBJ_COMP_L    0x38U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tobj_comp  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tobj_comp  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tobj_comp_l_t;

#define STHS34PF80_TOBJ_COMP_H    0x39U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tobj_comp  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tobj_comp  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tobj_comp_h_t;

#define STHS34PF80_TPRESENCE_L    0x3AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tpresence  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tpresence  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tpresence_l_t;

#define STHS34PF80_TPRESENCE_H    0x3BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tpresence  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tpresence  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tpresence_h_t;

#define STHS34PF80_TMOTION_L    0x3CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tmotion  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tmotion  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tmotion_l_t;

#define STHS34PF80_TMOTION_H    0x3DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tmotion  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tmotion  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tmotion_h_t;

#define STHS34PF80_TAMB_SHOCK_L    0x3EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tamb_shock  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tamb_shock  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tamb_shock_l_t;

#define STHS34PF80_TAMB_SHOCK_H    0x3FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tamb_shock  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tamb_shock  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_tamb_shock_h_t;

/**
  * @}
  *
  */

/** @defgroup bitfields page embedded
  * @{
  *
  */

#define STHS34PF80_FUNC_CFG_ADDR    0x08U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t func_cfg_addr  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t func_cfg_addr  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_func_cfg_addr_t;

#define STHS34PF80_FUNC_CFG_DATA    0x09U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t func_cfg_data  : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t func_cfg_data  : 8;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_func_cfg_data_t;

#define STHS34PF80_PAGE_RW    0x11U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used0  : 5;
  uint8_t func_cfg_read  : 1;
  uint8_t func_cfg_write  : 1;
  uint8_t not_used1  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used1  : 1;
  uint8_t func_cfg_write  : 1;
  uint8_t func_cfg_read  : 1;
  uint8_t not_used0  : 5;
#endif /* DRV_BYTE_ORDER */
} sths34pf80_page_rw_t;

#define STHS34PF80_PRESENCE_THS       0x20U
#define STHS34PF80_MOTION_THS         0x22U
#define STHS34PF80_TAMB_SHOCK_THS     0x24U
#define STHS34PF80_HYST_MOTION        0x26U
#define STHS34PF80_HYST_PRESENCE      0x27U
#define STHS34PF80_ALGO_CONFIG        0x28U
#define STHS34PF80_HYST_TAMB_SHOCK    0x29U
#define STHS34PF80_RESET_ALGO         0x2AU

/**
  * @}
  *
  */

typedef union
{
  sths34pf80_lpf1_t    lpf1;
  sths34pf80_lpf2_t    lpf2;
  sths34pf80_who_am_i_t    who_am_i;
  sths34pf80_avg_trim_t    avg_trim;
  sths34pf80_ctrl1_t    ctrl1;
  sths34pf80_ctrl2_t    ctrl2;
  sths34pf80_ctrl3_t    ctrl3;
  sths34pf80_status_t    status;
  sths34pf80_func_status_t    func_status;
  sths34pf80_tobject_l_t    tobject_l;
  sths34pf80_tobject_h_t    tobject_h;
  sths34pf80_tambient_l_t    tambient_l;
  sths34pf80_tambient_h_t    tambient_h;
  sths34pf80_tpresence_l_t    tpresence_l;
  sths34pf80_tpresence_h_t    tpresence_h;
  sths34pf80_tmotion_l_t    tmotion_l;
  sths34pf80_tmotion_h_t    tmotion_h;
  sths34pf80_tamb_shock_l_t    tamb_shock_l;
  sths34pf80_tamb_shock_h_t    tamb_shock_h;
  bitwise_t    bitwise;
  uint8_t    byte;
} prefix_lowmain_t;

typedef union
{
  sths34pf80_func_cfg_addr_t    func_cfg_addr;
  sths34pf80_func_cfg_data_t    func_cfg_data;
  sths34pf80_page_rw_t    page_rw;
  bitwise_t    bitwise;
  uint8_t    byte;
} prefix_lowembedded_t;

/**
  * @}
  *
  */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/*
 * These are the basic platform dependent I/O routines to read
 * and write device registers connected on a standard bus.
 * The driver keeps offering a default implementation based on function
 * pointers to read/write routines for backward compatibility.
 * The default implementation is declared with a __weak directive to
 * allow the final application to overwrite it with a custom implementation.
 */
int32_t sths34pf80_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                            uint8_t *data,
                            uint16_t len);
int32_t sths34pf80_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                             uint8_t *data,
                             uint16_t len);

int32_t sths34pf80_device_id_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  STHS34PF80_AVG_TMOS_2 = 0x0,
  STHS34PF80_AVG_TMOS_8 = 0x1,
  STHS34PF80_AVG_TMOS_32 = 0x2,
  STHS34PF80_AVG_TMOS_128 = 0x3,
  STHS34PF80_AVG_TMOS_256 = 0x4,
  STHS34PF80_AVG_TMOS_512 = 0x5,
  STHS34PF80_AVG_TMOS_1024 = 0x6,
  STHS34PF80_AVG_TMOS_2048 = 0x7,
} sths34pf80_avg_tobject_num_t;
int32_t sths34pf80_avg_tobject_num_set(const stmdev_ctx_t *ctx, sths34pf80_avg_tobject_num_t val);
int32_t sths34pf80_avg_tobject_num_get(const stmdev_ctx_t *ctx, sths34pf80_avg_tobject_num_t *val);

typedef enum
{
  STHS34PF80_AVG_T_8 = 0x0,
  STHS34PF80_AVG_T_4 = 0x1,
  STHS34PF80_AVG_T_2 = 0x2,
  STHS34PF80_AVG_T_1 = 0x3,
} sths34pf80_avg_tambient_num_t;
int32_t sths34pf80_avg_tambient_num_set(const stmdev_ctx_t *ctx, sths34pf80_avg_tambient_num_t val);
int32_t sths34pf80_avg_tambient_num_get(const stmdev_ctx_t *ctx,
                                        sths34pf80_avg_tambient_num_t *val);

typedef enum
{
  STHS34PF80_GAIN_WIDE_MODE = 0x0,
  STHS34PF80_GAIN_DEFAULT_MODE = 0x7,
} sths34pf80_gain_mode_t;

int32_t sths34pf80_gain_mode_set(const stmdev_ctx_t *ctx, sths34pf80_gain_mode_t val);
int32_t sths34pf80_gain_mode_get(const stmdev_ctx_t *ctx, sths34pf80_gain_mode_t *val);

int32_t sths34pf80_tobject_sensitivity_set(const stmdev_ctx_t *ctx, uint16_t *val);
int32_t sths34pf80_tobject_sensitivity_get(const stmdev_ctx_t *ctx, uint16_t *val);

typedef enum
{
  STHS34PF80_ODR_OFF = 0x0,
  STHS34PF80_ODR_AT_0Hz25 = 0x1,
  STHS34PF80_ODR_AT_0Hz50 = 0x2,
  STHS34PF80_ODR_AT_1Hz = 0x3,
  STHS34PF80_ODR_AT_2Hz = 0x4,
  STHS34PF80_ODR_AT_4Hz = 0x5,
  STHS34PF80_ODR_AT_8Hz = 0x6,
  STHS34PF80_ODR_AT_15Hz = 0x7,
  STHS34PF80_ODR_AT_30Hz = 0x8,
} sths34pf80_odr_t;
int32_t sths34pf80_odr_set(const stmdev_ctx_t *ctx, sths34pf80_odr_t val);
int32_t sths34pf80_odr_get(const stmdev_ctx_t *ctx, sths34pf80_odr_t *val);

int32_t sths34pf80_block_data_update_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_block_data_update_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  STHS34PF80_IDLE_MODE = 0x0,
  STHS34PF80_ONE_SHOT = 0x1,
} sths34pf80_one_shot_t;
int32_t sths34pf80_one_shot_set(const stmdev_ctx_t *ctx, sths34pf80_one_shot_t val);
int32_t sths34pf80_one_shot_get(const stmdev_ctx_t *ctx, sths34pf80_one_shot_t *val);

typedef enum
{
  STHS34PF80_MAIN_MEM_BANK = 0x0,
  STHS34PF80_EMBED_FUNC_MEM_BANK = 0x1,
} sths34pf80_mem_bank_t;
int32_t sths34pf80_mem_bank_set(const stmdev_ctx_t *ctx, sths34pf80_mem_bank_t val);
int32_t sths34pf80_mem_bank_get(const stmdev_ctx_t *ctx, sths34pf80_mem_bank_t *val);

int32_t sths34pf80_boot_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_boot_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef struct
{
  uint8_t drdy : 1;
} sths34pf80_drdy_status_t;
int32_t sths34pf80_drdy_status_get(const stmdev_ctx_t *ctx, sths34pf80_drdy_status_t *val);

int32_t sths34pf80_func_status_get(const stmdev_ctx_t *ctx, sths34pf80_func_status_t *val);

int32_t sths34pf80_tobject_raw_get(const stmdev_ctx_t *ctx, int16_t *val);
int32_t sths34pf80_tambient_raw_get(const stmdev_ctx_t *ctx, int16_t *val);
int32_t sths34pf80_tobj_comp_raw_get(const stmdev_ctx_t *ctx, int16_t *val);
int32_t sths34pf80_tpresence_raw_get(const stmdev_ctx_t *ctx, int16_t *val);
int32_t sths34pf80_tmotion_raw_get(const stmdev_ctx_t *ctx, int16_t *val);
int32_t sths34pf80_tamb_shock_raw_get(const stmdev_ctx_t *ctx, int16_t *val);

typedef enum
{
  STHS34PF80_LPF_ODR_DIV_9 = 0x0,
  STHS34PF80_LPF_ODR_DIV_20 = 0x1,
  STHS34PF80_LPF_ODR_DIV_50 = 0x2,
  STHS34PF80_LPF_ODR_DIV_100 = 0x3,
  STHS34PF80_LPF_ODR_DIV_200 = 0x4,
  STHS34PF80_LPF_ODR_DIV_400 = 0x5,
  STHS34PF80_LPF_ODR_DIV_800 = 0x6,
} sths34pf80_lpf_bandwidth_t;
int32_t sths34pf80_lpf_m_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val);
int32_t sths34pf80_lpf_m_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val);
int32_t sths34pf80_lpf_p_m_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val);
int32_t sths34pf80_lpf_p_m_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val);
int32_t sths34pf80_lpf_a_t_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val);
int32_t sths34pf80_lpf_a_t_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val);
int32_t sths34pf80_lpf_p_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val);
int32_t sths34pf80_lpf_p_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val);

typedef enum
{
  STHS34PF80_INT_HIZ = 0x0,
  STHS34PF80_INT_DRDY = 0x1,
  STHS34PF80_INT_OR = 0x2,
} sths34pf80_route_int_t;
int32_t sths34pf80_route_int_set(const stmdev_ctx_t *ctx, sths34pf80_route_int_t val);
int32_t sths34pf80_route_int_get(const stmdev_ctx_t *ctx, sths34pf80_route_int_t *val);

typedef enum
{
  STHS34PF80_INT_NONE = 0x0,
  STHS34PF80_INT_TSHOCK = 0x1,
  STHS34PF80_INT_MOTION = 0x2,
  STHS34PF80_INT_TSHOCK_MOTION = 0x3,
  STHS34PF80_INT_PRESENCE = 0x4,
  STHS34PF80_INT_TSHOCK_PRESENCE = 0x5,
  STHS34PF80_INT_MOTION_PRESENCE = 0x6,
  STHS34PF80_INT_ALL = 0x7,
} sths34pf80_int_or_t;
int32_t sths34pf80_int_or_set(const stmdev_ctx_t *ctx, sths34pf80_int_or_t val);
int32_t sths34pf80_int_or_get(const stmdev_ctx_t *ctx, sths34pf80_int_or_t *val);

typedef struct
{
  enum
  {
    STHS34PF80_PUSH_PULL = 0x0,
    STHS34PF80_OPEN_DRAIN = 0x1,
  } pin;

  enum
  {
    STHS34PF80_ACTIVE_HIGH = 0x0,
    STHS34PF80_ACTIVE_LOW = 0x1,
  } polarity;
} sths34pf80_int_mode_t;
int32_t sths34pf80_int_mode_set(const stmdev_ctx_t *ctx, sths34pf80_int_mode_t val);
int32_t sths34pf80_int_mode_get(const stmdev_ctx_t *ctx, sths34pf80_int_mode_t *val);

typedef enum
{
  STHS34PF80_DRDY_PULSED = 0x0,
  STHS34PF80_DRDY_LATCHED = 0x1,
} sths34pf80_drdy_mode_t;
int32_t sths34pf80_drdy_mode_set(const stmdev_ctx_t *ctx, sths34pf80_drdy_mode_t val);
int32_t sths34pf80_drdy_mode_get(const stmdev_ctx_t *ctx, sths34pf80_drdy_mode_t *val);

int32_t sths34pf80_func_cfg_write(const stmdev_ctx_t *ctx, uint8_t addr, uint8_t *data,
                                  uint8_t len);
int32_t sths34pf80_func_cfg_read(const stmdev_ctx_t *ctx, uint8_t addr, uint8_t *data, uint8_t len);

int32_t sths34pf80_presence_threshold_set(const stmdev_ctx_t *ctx, uint16_t val);
int32_t sths34pf80_presence_threshold_get(const stmdev_ctx_t *ctx, uint16_t *val);

int32_t sths34pf80_motion_threshold_set(const stmdev_ctx_t *ctx, uint16_t val);
int32_t sths34pf80_motion_threshold_get(const stmdev_ctx_t *ctx, uint16_t *val);

int32_t sths34pf80_tambient_shock_threshold_set(const stmdev_ctx_t *ctx, uint16_t val);
int32_t sths34pf80_tambient_shock_threshold_get(const stmdev_ctx_t *ctx, uint16_t *val);

int32_t sths34pf80_motion_hysteresis_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_motion_hysteresis_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t sths34pf80_presence_hysteresis_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_presence_hysteresis_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t sths34pf80_tambient_shock_hysteresis_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_tambient_shock_hysteresis_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t sths34pf80_int_or_pulsed_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_int_or_pulsed_get(const stmdev_ctx_t *ctx, uint8_t *val);
int32_t sths34pf80_tobject_algo_compensation_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_tobject_algo_compensation_get(const stmdev_ctx_t *ctx, uint8_t *val);
int32_t sths34pf80_presence_abs_value_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t sths34pf80_presence_abs_value_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t sths34pf80_algo_reset(const stmdev_ctx_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /*STHS34PF80_DRIVER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
