/**
  ******************************************************************************
  * @file    sths34pf80_reg.c
  * @author  Sensors Software Solution Team
  * @brief   STHS34PF80 driver file
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

#include "sths34pf80_reg.h"
#include "McuI2cLib.h"

/*
 * Prototypes of routines used only throughout this driver and not exported
 * outside as APIs
 */
typedef struct
{
  uint8_t int_pulsed : 1;
  uint8_t comp_type : 1;
  uint8_t sel_abs : 1;
} sths34pf80_algo_config_t;

static int32_t sths34pf80_reset_algo_bit_set(const stmdev_ctx_t *ctx);
static int32_t sths34pf80_algo_config_get(const stmdev_ctx_t *ctx, sths34pf80_algo_config_t *val);
static int32_t sths34pf80_algo_config_set(const stmdev_ctx_t *ctx, sths34pf80_algo_config_t val);
static int32_t sths34pf80_safe_power_down(const stmdev_ctx_t *ctx, sths34pf80_ctrl1_t *ctrl1);
static int32_t sths34pf80_odr_safe_set(const stmdev_ctx_t *ctx,
                                       sths34pf80_ctrl1_t *ctrl1,
                                       uint8_t odr_new);

/**
  * @defgroup  STHS34PF80
  * @brief     This file provides a set of functions needed to drive the
  *            sths34pf80 enhanced inertial module.
  * @{
  *
  */

/**
  * @defgroup  Interfaces functions
  * @brief     This section provide a set of functions used to read and
  *            write a generic register of the device.
  *            MANDATORY: return 0 -> no Error.
  * @{
  *
  */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to read.
  * @param  data  buffer for data read.(ptr)
  * @param  len   number of consecutive register to read.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak sths34pf80_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                   uint8_t *data,
                                   uint16_t len)
{
  int32_t ret;

  if (ctx == NULL)
  {
    return -1;
  }

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to write.
  * @param  data  the buffer contains data to be written.(ptr)
  * @param  len   number of consecutive register to write.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak sths34pf80_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                    uint8_t *data,
                                    uint16_t len)
{
  int32_t ret;

  if (ctx == NULL)
  {
    return -1;
  }

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup Common
  * @brief    Common
  * @{/
  *
  */
/**
  * @brief  Device ID.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Device ID.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_device_id_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_WHO_AM_I, val, 1);

  return ret;
}

/**
  * @brief  Select number of averages for object temperature.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      AVG_TMOS_2, AVG_TMOS_8, AVG_TMOS_32, AVG_TMOS_128, AVG_TMOS_256, AVG_TMOS_512, AVG_TMOS_1024, AVG_TMOS_2048,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_avg_tobject_num_set(const stmdev_ctx_t *ctx, sths34pf80_avg_tobject_num_t val)
{
  sths34pf80_avg_trim_t avg_trim;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);

  if (ret == 0)
  {
    avg_trim.avg_tmos = ((uint8_t)val & 0x7U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);
  }

  return ret;
}

/**
  * @brief  Select number of averages for object temperature.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      AVG_TMOS_2, AVG_TMOS_8, AVG_TMOS_32, AVG_TMOS_128, AVG_TMOS_256, AVG_TMOS_512, AVG_TMOS_1024, AVG_TMOS_2048,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_avg_tobject_num_get(const stmdev_ctx_t *ctx, sths34pf80_avg_tobject_num_t *val)
{
  sths34pf80_avg_trim_t avg_trim;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);

  switch (avg_trim.avg_tmos)
  {
    case STHS34PF80_AVG_TMOS_2:
      *val = STHS34PF80_AVG_TMOS_2;
      break;

    case STHS34PF80_AVG_TMOS_8:
      *val = STHS34PF80_AVG_TMOS_8;
      break;

    case STHS34PF80_AVG_TMOS_32:
      *val = STHS34PF80_AVG_TMOS_32;
      break;

    case STHS34PF80_AVG_TMOS_128:
      *val = STHS34PF80_AVG_TMOS_128;
      break;

    case STHS34PF80_AVG_TMOS_256:
      *val = STHS34PF80_AVG_TMOS_256;
      break;

    case STHS34PF80_AVG_TMOS_512:
      *val = STHS34PF80_AVG_TMOS_512;
      break;

    case STHS34PF80_AVG_TMOS_1024:
      *val = STHS34PF80_AVG_TMOS_1024;
      break;

    case STHS34PF80_AVG_TMOS_2048:
      *val = STHS34PF80_AVG_TMOS_2048;
      break;

    default:
      *val = STHS34PF80_AVG_TMOS_2;
      break;
  }
  return ret;
}

/**
  * @brief  Select number of averages for ambient temperature.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      AVG_T_8, AVG_T_4, AVG_T_2, AVG_T_1,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_avg_tambient_num_set(const stmdev_ctx_t *ctx, sths34pf80_avg_tambient_num_t val)
{
  sths34pf80_avg_trim_t avg_trim;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);

  if (ret == 0)
  {
    avg_trim.avg_t = ((uint8_t)val & 0x3U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);
  }

  return ret;
}

/**
  * @brief  Select number of averages for ambient temperature.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      AVG_T_8, AVG_T_4, AVG_T_2, AVG_T_1,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_avg_tambient_num_get(const stmdev_ctx_t *ctx, sths34pf80_avg_tambient_num_t *val)
{
  sths34pf80_avg_trim_t avg_trim;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);

  switch (avg_trim.avg_t)
  {
    case STHS34PF80_AVG_T_8:
      *val = STHS34PF80_AVG_T_8;
      break;

    case STHS34PF80_AVG_T_4:
      *val = STHS34PF80_AVG_T_4;
      break;

    case STHS34PF80_AVG_T_2:
      *val = STHS34PF80_AVG_T_2;
      break;

    case STHS34PF80_AVG_T_1:
      *val = STHS34PF80_AVG_T_1;
      break;

    default:
      *val = STHS34PF80_AVG_T_8;
      break;
  }
  return ret;
}

/**
  * @brief  temperature range.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      range: GAIN_WIDE_MODE, GAIN_DEFAULT_MODE
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_gain_mode_set(const stmdev_ctx_t *ctx, sths34pf80_gain_mode_t val)
{
  sths34pf80_ctrl0_t ctrl0;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL0, (uint8_t *)&ctrl0, 1);

  if (ret == 0)
  {
    ctrl0.gain = (uint8_t)val;
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL0, (uint8_t *)&ctrl0, 1);
  }

  return ret;
}

/**
  * @brief  temperature range.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      range: GAIN_WIDE_MODE, GAIN_DEFAULT_MODE
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_gain_mode_get(const stmdev_ctx_t *ctx, sths34pf80_gain_mode_t *val)
{
  sths34pf80_ctrl0_t ctrl0;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL0, (uint8_t *)&ctrl0, 1);

  switch (ctrl0.gain)
  {
    case STHS34PF80_GAIN_WIDE_MODE:
      *val = STHS34PF80_GAIN_WIDE_MODE;
      break;

    case STHS34PF80_GAIN_DEFAULT_MODE:
      *val = STHS34PF80_GAIN_DEFAULT_MODE;
      break;

    default:
      *val = STHS34PF80_GAIN_DEFAULT_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  sensitivity data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      IN: desired sensitivity value
  *                  OUT: rounded sensitivity value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tobject_sensitivity_set(const stmdev_ctx_t *ctx, uint16_t *val)
{
  sths34pf80_sens_data_t data;
  int32_t ret;

  data.sens = (*val >= 2048U) ?
              (*val - 2048U + 8U) / 16U :
              (*val - 2048U - 8U) / 16U;
  ret = sths34pf80_write_reg(ctx, STHS34PF80_SENS_DATA, (uint8_t *)&data, 1);
  *val = (int8_t)data.sens * 16U + 2048U;

  return ret;
}

/**
  * @brief  sensitivity data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      rounded sensitivity value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tobject_sensitivity_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  sths34pf80_sens_data_t data;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_SENS_DATA, (uint8_t *)&data, 1);
  *val = (int8_t)data.sens * 16 + 2048;

  return ret;
}

/**
  * @brief  Enter to power-down in a safe way
  *
  * @param  ctx      read / write interface definitions
  * @param  ctrl1    Pointer to CTRL1 register
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
static int32_t sths34pf80_safe_power_down(const stmdev_ctx_t *ctx, sths34pf80_ctrl1_t *ctrl1)
{
  sths34pf80_func_status_t func_status;
  sths34pf80_drdy_status_t status;
  int32_t ret;

  /* if sensor is already in power-down then do nothing */
  if (ctrl1->odr == 0U)
  {
    return 0;
  }

  /* reset the DRDY bit */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_FUNC_STATUS, (uint8_t *)&func_status, 1);

  /* wait DRDY bit go to '1'. Maximum wait may be up to 4 sec (0.25 Hz) */
  uint16_t retry = 0U;
  do
  {
    ret += sths34pf80_drdy_status_get(ctx, &status);
    ctx->mdelay(1);
  } while (status.drdy == 0U && retry++ < 4000U);

  if (ret != 0 || retry >= 4000U)
  {
    return -1;
  };

  /* perform power-down */
  ctrl1->odr = 0U;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)ctrl1, 1);

  /* reset the DRDY bit */
  ret += sths34pf80_read_reg(ctx, STHS34PF80_FUNC_STATUS, (uint8_t *)&func_status, 1);

  return ret;
}

/**
  * @brief  Change odr in a safe way
  *
  * @param  ctx      read / write interface definitions
  * @param  ctrl1    Pointer to CTRL1 register
  * @param  odr_new  Value of new odr to be set
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
static int32_t sths34pf80_odr_safe_set(const stmdev_ctx_t *ctx,
                                       sths34pf80_ctrl1_t *ctrl1,
                                       uint8_t odr_new)
{
  int32_t ret;

  /* perform power-down transition in a safe way. */
  ret = sths34pf80_safe_power_down(ctx, ctrl1);

  if (odr_new > 0U)
  {
    /*
     * Do a clean reset algo procedure everytime odr is changed to an
     * operative state.
     */
    ret += sths34pf80_reset_algo_bit_set(ctx);

    /* set new odr */
    ctrl1->odr = (odr_new & 0xfU);
    ret += sths34pf80_write_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)ctrl1, 1);
  }

  return ret;
}

/**
  * @brief  Selects the tmos odr.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      ODR_OFF, ODR_AT_0Hz25, ODR_AT_0Hz50, ODR_1Hz, ODR_2Hz, ODR_4Hz, ODR_8Hz, ODR_15Hz, ODR_30Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_odr_set(const stmdev_ctx_t *ctx, sths34pf80_odr_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  sths34pf80_avg_trim_t avg_trim;
  sths34pf80_odr_t max_odr = STHS34PF80_ODR_AT_30Hz;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);

  if (ret == 0)
  {
    ret = sths34pf80_read_reg(ctx, STHS34PF80_AVG_TRIM, (uint8_t *)&avg_trim, 1);

    switch (avg_trim.avg_tmos)
    {
      default:
      case STHS34PF80_AVG_TMOS_2:
      case STHS34PF80_AVG_TMOS_8:
      case STHS34PF80_AVG_TMOS_32:
        max_odr = STHS34PF80_ODR_AT_30Hz;
        break;
      case STHS34PF80_AVG_TMOS_128:
        max_odr = STHS34PF80_ODR_AT_8Hz;
        break;
      case STHS34PF80_AVG_TMOS_256:
        max_odr = STHS34PF80_ODR_AT_4Hz;
        break;
      case STHS34PF80_AVG_TMOS_512:
        max_odr = STHS34PF80_ODR_AT_2Hz;
        break;
      case STHS34PF80_AVG_TMOS_1024:
        max_odr = STHS34PF80_ODR_AT_1Hz;
        break;
      case STHS34PF80_AVG_TMOS_2048:
        max_odr = STHS34PF80_ODR_AT_0Hz50;
        break;
    }
  }

  if (ret == 0)
  {
    if (val > max_odr)
    {
      return -1;
    }

    ret = sths34pf80_odr_safe_set(ctx, &ctrl1, (uint8_t)val);
  }

  return ret;
}

/**
  * @brief  Selects the tmos odr.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      ODR_OFF, ODR_AT_0Hz25, ODR_AT_0Hz50, ODR_1Hz, ODR_2Hz, ODR_4Hz, ODR_8Hz, ODR_15Hz, ODR_30Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_odr_get(const stmdev_ctx_t *ctx, sths34pf80_odr_t *val)
{
  sths34pf80_ctrl1_t ctrl1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);

  switch (ctrl1.odr)
  {
    case STHS34PF80_ODR_OFF:
      *val = STHS34PF80_ODR_OFF;
      break;

    case STHS34PF80_ODR_AT_0Hz25:
      *val = STHS34PF80_ODR_AT_0Hz25;
      break;

    case STHS34PF80_ODR_AT_0Hz50:
      *val = STHS34PF80_ODR_AT_0Hz50;
      break;

    case STHS34PF80_ODR_AT_1Hz:
      *val = STHS34PF80_ODR_AT_1Hz;
      break;

    case STHS34PF80_ODR_AT_2Hz:
      *val = STHS34PF80_ODR_AT_2Hz;
      break;

    case STHS34PF80_ODR_AT_4Hz:
      *val = STHS34PF80_ODR_AT_4Hz;
      break;

    case STHS34PF80_ODR_AT_8Hz:
      *val = STHS34PF80_ODR_AT_8Hz;
      break;

    case STHS34PF80_ODR_AT_15Hz:
      *val = STHS34PF80_ODR_AT_15Hz;
      break;

    case STHS34PF80_ODR_AT_30Hz:
      *val = STHS34PF80_ODR_AT_30Hz;
      break;

    default:
      *val = STHS34PF80_ODR_OFF;
      break;
  }
  return ret;
}

/**
  * @brief  Block Data Update (BDU): output registers are not updated until LSB and MSB have been read). [set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Block Data Update (BDU): output registers are not updated until LSB and MSB have been read).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_block_data_update_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);

  if (ret == 0)
  {
    ctrl1.bdu = val;
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  }

  return ret;
}

/**
  * @brief  Block Data Update (BDU): output registers are not updated until LSB and MSB have been read). [get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Block Data Update (BDU): output registers are not updated until LSB and MSB have been read).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_block_data_update_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_ctrl1_t ctrl1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);

  *val = ctrl1.bdu;


  return ret;
}

/**
  * @brief  Selects data output mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      IDLE_MODE, ONE_SHOT
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_one_shot_set(const stmdev_ctx_t *ctx, sths34pf80_one_shot_t val)
{
  sths34pf80_ctrl2_t ctrl2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);

  if (ret == 0)
  {
    ctrl2.one_shot = ((uint8_t)val & 0x1U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Selects data output mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      IDLE_MODE, ONE_SHOT
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_one_shot_get(const stmdev_ctx_t *ctx, sths34pf80_one_shot_t *val)
{
  sths34pf80_ctrl2_t ctrl2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);

  switch (ctrl2.one_shot)
  {
    case STHS34PF80_IDLE_MODE:
      *val = STHS34PF80_IDLE_MODE;
      break;

    case STHS34PF80_ONE_SHOT:
      *val = STHS34PF80_ONE_SHOT;
      break;

    default:
      *val = STHS34PF80_IDLE_MODE;
      break;
  }
  return ret;
}

/**
  * @brief  Change memory bank.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      MAIN_MEM_BANK, EMBED_FUNC_MEM_BANK, SENSOR_HUB_MEM_BANK, STRED_MEM_BANK,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_mem_bank_set(const stmdev_ctx_t *ctx, sths34pf80_mem_bank_t val)
{
  sths34pf80_ctrl2_t ctrl2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);

  if (ret == 0)
  {
    ctrl2.func_cfg_access = ((uint8_t)val & 0x1U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Change memory bank.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      MAIN_MEM_BANK, EMBED_FUNC_MEM_BANK, SENSOR_HUB_MEM_BANK, STRED_MEM_BANK,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_mem_bank_get(const stmdev_ctx_t *ctx, sths34pf80_mem_bank_t *val)
{
  sths34pf80_ctrl2_t ctrl2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);

  switch (ctrl2.func_cfg_access)
  {
    case STHS34PF80_MAIN_MEM_BANK:
      *val = STHS34PF80_MAIN_MEM_BANK;
      break;

    case STHS34PF80_EMBED_FUNC_MEM_BANK:
      *val = STHS34PF80_EMBED_FUNC_MEM_BANK;
      break;

    default:
      *val = STHS34PF80_MAIN_MEM_BANK;
      break;
  }
  return ret;
}

/**
  * @brief  Global reset of the device.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      READY, RESTORE_CTRL_REGS,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_boot_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl2_t ctrl2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);

  if (ret == 0)
  {
    ctrl2.boot = val;
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Global reset of the device.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      READY, RESTORE_CTRL_REGS,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_boot_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_ctrl2_t ctrl2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL2, (uint8_t *)&ctrl2, 1);
  *val = ctrl2.boot;

  return ret;
}

/**
  * @brief  status of drdy.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      status of drdy bit (TAMB, TOBJ, TAMB_SHOCK, TPRESENCE, TMOTION).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_drdy_status_get(const stmdev_ctx_t *ctx, sths34pf80_drdy_status_t *val)
{
  sths34pf80_status_t status;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_STATUS, (uint8_t *)&status, 1);

  val->drdy = status.drdy;

  return ret;
}

/**
  * @brief  status of internal functions.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      status of internal functions.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_func_status_get(const stmdev_ctx_t *ctx, sths34pf80_func_status_t *val)
{
  sths34pf80_func_status_t func_status;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_FUNC_STATUS, (uint8_t *)&func_status, 1);

  val->tamb_shock_flag = func_status.tamb_shock_flag;
  val->mot_flag = func_status.mot_flag;
  val->pres_flag = func_status.pres_flag;

  return ret;
}

/**
  * @brief  Object temperature output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Object temperature output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tobject_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TOBJECT_L, &buff[0], 2);

  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Ambient temperature output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Ambient temperature output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tambient_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TAMBIENT_L, &buff[0], 2);

  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Object compensation output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Object compensation output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tobj_comp_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TOBJ_COMP_L, &buff[0], 2);

  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Presence algo data output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Presence algo data output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tpresence_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TPRESENCE_L, &buff[0], 2);

  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Motion algo data output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Motion algo data output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tmotion_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TMOTION_L, &buff[0], 2);

  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Temperature ambient shock algo data output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Temperature ambient shock algo data output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tamb_shock_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_TAMB_SHOCK_L, &buff[0], 2);

  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup Filters
  * @brief    Filters
  * @{/
  *
  */
/**
  * @brief  low-pass filter configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_m_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val)
{
  sths34pf80_lpf1_t lpf1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, (uint8_t *)&lpf1, 1);

  if (ret == 0)
  {
    lpf1.lpf_m = ((uint8_t)val & 0x7U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF1, (uint8_t *)&lpf1, 1);
  }

  return ret;
}

/**
  * @brief  low-pass filter configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_m_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val)
{
  sths34pf80_lpf1_t lpf1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, (uint8_t *)&lpf1, 1);

  switch ((lpf1.lpf_m))
  {
    case STHS34PF80_LPF_ODR_DIV_9:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;

    case STHS34PF80_LPF_ODR_DIV_20:
      *val = STHS34PF80_LPF_ODR_DIV_20;
      break;

    case STHS34PF80_LPF_ODR_DIV_50:
      *val = STHS34PF80_LPF_ODR_DIV_50;
      break;

    case STHS34PF80_LPF_ODR_DIV_100:
      *val = STHS34PF80_LPF_ODR_DIV_100;
      break;

    case STHS34PF80_LPF_ODR_DIV_200:
      *val = STHS34PF80_LPF_ODR_DIV_200;
      break;

    case STHS34PF80_LPF_ODR_DIV_400:
      *val = STHS34PF80_LPF_ODR_DIV_400;
      break;

    case STHS34PF80_LPF_ODR_DIV_800:
      *val = STHS34PF80_LPF_ODR_DIV_800;
      break;

    default:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;
  }
  return ret;
}

/**
  * @brief  low-pass filter configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_p_m_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val)
{
  sths34pf80_lpf1_t lpf1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, (uint8_t *)&lpf1, 1);

  if (ret == 0)
  {
    lpf1.lpf_p_m = ((uint8_t)val & 0x7U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF1, (uint8_t *)&lpf1, 1);
  }

  return ret;
}

/**
  * @brief  low-pass filter configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_p_m_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val)
{
  sths34pf80_lpf1_t lpf1;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF1, (uint8_t *)&lpf1, 1);

  switch ((lpf1.lpf_p_m))
  {
    case STHS34PF80_LPF_ODR_DIV_9:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;

    case STHS34PF80_LPF_ODR_DIV_20:
      *val = STHS34PF80_LPF_ODR_DIV_20;
      break;

    case STHS34PF80_LPF_ODR_DIV_50:
      *val = STHS34PF80_LPF_ODR_DIV_50;
      break;

    case STHS34PF80_LPF_ODR_DIV_100:
      *val = STHS34PF80_LPF_ODR_DIV_100;
      break;

    case STHS34PF80_LPF_ODR_DIV_200:
      *val = STHS34PF80_LPF_ODR_DIV_200;
      break;

    case STHS34PF80_LPF_ODR_DIV_400:
      *val = STHS34PF80_LPF_ODR_DIV_400;
      break;

    case STHS34PF80_LPF_ODR_DIV_800:
      *val = STHS34PF80_LPF_ODR_DIV_800;
      break;

    default:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;
  }
  return ret;
}

/**
  * @brief  low-pass filter configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_a_t_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val)
{
  sths34pf80_lpf2_t lpf2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, (uint8_t *)&lpf2, 1);

  if (ret == 0)
  {
    lpf2.lpf_a_t = ((uint8_t)val & 0x7U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF2, (uint8_t *)&lpf2, 1);
  }

  return ret;
}

/**
  * @brief  low-pass filter configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_a_t_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val)
{
  sths34pf80_lpf2_t lpf2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, (uint8_t *)&lpf2, 1);

  switch ((lpf2.lpf_a_t))
  {
    case STHS34PF80_LPF_ODR_DIV_9:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;

    case STHS34PF80_LPF_ODR_DIV_20:
      *val = STHS34PF80_LPF_ODR_DIV_20;
      break;

    case STHS34PF80_LPF_ODR_DIV_50:
      *val = STHS34PF80_LPF_ODR_DIV_50;
      break;

    case STHS34PF80_LPF_ODR_DIV_100:
      *val = STHS34PF80_LPF_ODR_DIV_100;
      break;

    case STHS34PF80_LPF_ODR_DIV_200:
      *val = STHS34PF80_LPF_ODR_DIV_200;
      break;

    case STHS34PF80_LPF_ODR_DIV_400:
      *val = STHS34PF80_LPF_ODR_DIV_400;
      break;

    case STHS34PF80_LPF_ODR_DIV_800:
      *val = STHS34PF80_LPF_ODR_DIV_800;
      break;

    default:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;
  }
  return ret;
}

/**
  * @brief  low-pass filter configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_p_bandwidth_set(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t val)
{
  sths34pf80_lpf2_t lpf2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, (uint8_t *)&lpf2, 1);

  if (ret == 0)
  {
    lpf2.lpf_p = ((uint8_t)val & 0x7U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_LPF2, (uint8_t *)&lpf2, 1);
  }

  return ret;
}

/**
  * @brief  low-pass filter configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      LPF_ODR_DIV_9, LPF_ODR_DIV_20, LPF_ODR_DIV_50, LPF_ODR_DIV_100, LPF_ODR_DIV_200, LPF_ODR_DIV_400, LPF_ODR_DIV_800,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_lpf_p_bandwidth_get(const stmdev_ctx_t *ctx, sths34pf80_lpf_bandwidth_t *val)
{
  sths34pf80_lpf2_t lpf2;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_LPF2, (uint8_t *)&lpf2, 1);

  switch ((lpf2.lpf_p))
  {
    case STHS34PF80_LPF_ODR_DIV_9:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;

    case STHS34PF80_LPF_ODR_DIV_20:
      *val = STHS34PF80_LPF_ODR_DIV_20;
      break;

    case STHS34PF80_LPF_ODR_DIV_50:
      *val = STHS34PF80_LPF_ODR_DIV_50;
      break;

    case STHS34PF80_LPF_ODR_DIV_100:
      *val = STHS34PF80_LPF_ODR_DIV_100;
      break;

    case STHS34PF80_LPF_ODR_DIV_200:
      *val = STHS34PF80_LPF_ODR_DIV_200;
      break;

    case STHS34PF80_LPF_ODR_DIV_400:
      *val = STHS34PF80_LPF_ODR_DIV_400;
      break;

    case STHS34PF80_LPF_ODR_DIV_800:
      *val = STHS34PF80_LPF_ODR_DIV_800;
      break;

    default:
      *val = STHS34PF80_LPF_ODR_DIV_9;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup Interrupt PINs
  * @brief    Interrupt PINs
  * @{/
  *
  */
/**
  * @brief  Selects interrupts to be routed.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      INT_HIZ, INT_DRDY, INT_OR,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_route_int_set(const stmdev_ctx_t *ctx, sths34pf80_route_int_t val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  if (ret == 0)
  {
    ctrl3.ien = ((uint8_t)val & 0x3U);
    if (val == STHS34PF80_INT_OR)
    {
      ctrl3.int_latched = 0; /* guarantee that latched is zero in INT_OR case */
    }
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects interrupts to be routed.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      INT_HIZ, INT_DRDY, INT_OR,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_route_int_get(const stmdev_ctx_t *ctx, sths34pf80_route_int_t *val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  switch ((ctrl3.ien))
  {
    case STHS34PF80_INT_HIZ:
      *val = STHS34PF80_INT_HIZ;
      break;

    case STHS34PF80_INT_DRDY:
      *val = STHS34PF80_INT_DRDY;
      break;

    case STHS34PF80_INT_OR:
      *val = STHS34PF80_INT_OR;
      break;

    default:
      *val = STHS34PF80_INT_HIZ;
      break;
  }
  return ret;
}

/**
  * @brief  Selects interrupts output.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      INT_NONE, INT_TSHOCK, INT_MOTION, INT_TSHOCK_MOTION, INT_PRESENCE, INT_TSHOCK_PRESENCE, INT_MOTION_PRESENCE, INT_ALL,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_int_or_set(const stmdev_ctx_t *ctx, sths34pf80_int_or_t val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  if (ret == 0)
  {
    ctrl3.int_msk = ((uint8_t)val & 0x7U);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects interrupts output.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      INT_NONE, INT_TSHOCK, INT_MOTION, INT_TSHOCK_MOTION, INT_PRESENCE, INT_TSHOCK_PRESENCE, INT_MOTION_PRESENCE, INT_ALL,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_int_or_get(const stmdev_ctx_t *ctx, sths34pf80_int_or_t *val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  switch ((ctrl3.int_msk))
  {
    case STHS34PF80_INT_NONE:
      *val = STHS34PF80_INT_NONE;
      break;

    case STHS34PF80_INT_TSHOCK:
      *val = STHS34PF80_INT_TSHOCK;
      break;

    case STHS34PF80_INT_MOTION:
      *val = STHS34PF80_INT_MOTION;
      break;

    case STHS34PF80_INT_TSHOCK_MOTION:
      *val = STHS34PF80_INT_TSHOCK_MOTION;
      break;

    case STHS34PF80_INT_PRESENCE:
      *val = STHS34PF80_INT_PRESENCE;
      break;

    case STHS34PF80_INT_TSHOCK_PRESENCE:
      *val = STHS34PF80_INT_TSHOCK_PRESENCE;
      break;

    case STHS34PF80_INT_MOTION_PRESENCE:
      *val = STHS34PF80_INT_MOTION_PRESENCE;
      break;

    case STHS34PF80_INT_ALL:
      *val = STHS34PF80_INT_ALL;
      break;

    default:
      *val = STHS34PF80_INT_NONE;
      break;
  }
  return ret;
}

/**
  * @brief  Push-pull/open-drain selection on INT1 and INT2 pins.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      PUSH_PULL, OPEN_DRAIN,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_int_mode_set(const stmdev_ctx_t *ctx, sths34pf80_int_mode_t val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  if (ret == 0)
  {
    ctrl3.pp_od = ((uint8_t)val.pin);
    ctrl3.int_h_l = ((uint8_t)val.polarity);
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open-drain selection on INT1 and INT2 pins.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      PUSH_PULL, OPEN_DRAIN,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_int_mode_get(const stmdev_ctx_t *ctx, sths34pf80_int_mode_t *val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  switch (ctrl3.pp_od)
  {
    case STHS34PF80_PUSH_PULL:
      val->pin = STHS34PF80_PUSH_PULL;
      break;

    case STHS34PF80_OPEN_DRAIN:
      val->pin = STHS34PF80_OPEN_DRAIN;
      break;

    default:
      val->pin = STHS34PF80_PUSH_PULL;
      break;
  }

  switch (ctrl3.int_h_l)
  {
    case STHS34PF80_ACTIVE_HIGH:
      val->polarity = STHS34PF80_ACTIVE_HIGH;
      break;

    case STHS34PF80_ACTIVE_LOW:
      val->polarity = STHS34PF80_ACTIVE_LOW;
      break;

    default:
      val->polarity = STHS34PF80_ACTIVE_HIGH;
      break;
  }

  return ret;
}

/**
  * @brief  DRDY mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DRDY_PULSED, DRDY_LATCHED,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_drdy_mode_set(const stmdev_ctx_t *ctx, sths34pf80_drdy_mode_t val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  if (ret == 0)
  {
    ctrl3.int_latched = (uint8_t)val;
    ret = sths34pf80_write_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  DRDY mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DRDY_PULSED, DRDY_LATCHED,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_drdy_mode_get(const stmdev_ctx_t *ctx, sths34pf80_drdy_mode_t *val)
{
  sths34pf80_ctrl3_t ctrl3;
  int32_t ret;

  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL3, (uint8_t *)&ctrl3, 1);

  switch (ctrl3.int_latched)
  {
    case STHS34PF80_DRDY_PULSED:
      *val = STHS34PF80_DRDY_PULSED;
      break;

    case STHS34PF80_DRDY_LATCHED:
      *val = STHS34PF80_DRDY_LATCHED;
      break;

    default:
      *val = STHS34PF80_DRDY_PULSED;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup Embedded
  * @brief    Embedded
  * @{/
  *
  */
/**
  * @brief  Function Configuration write
  *
  * @param  ctx      read / write interface definitions
  * @param  addr     embedded register address
  * @param  data     embedded register data
  * @param  len      embedded register data len
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_func_cfg_write(const stmdev_ctx_t *ctx, uint8_t addr, uint8_t *data, uint8_t len)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  sths34pf80_page_rw_t page_rw = {0};
  int32_t ret;
  uint8_t i;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  /* Enable access to embedded functions register */
  ret += sths34pf80_mem_bank_set(ctx, STHS34PF80_EMBED_FUNC_MEM_BANK);

  /* Enable write mode */
  page_rw.func_cfg_write = 1;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* Select register address (it will autoincrement when writing) */
  ret += sths34pf80_write_reg(ctx, STHS34PF80_FUNC_CFG_ADDR, &addr, 1);

  for (i = 0; i < len; i++)
  {
    /* Write data */
    ret += sths34pf80_write_reg(ctx, STHS34PF80_FUNC_CFG_DATA, &data[i], 1);
  }

  /* Disable write mode */
  page_rw.func_cfg_write = 0;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* Disable access to embedded functions register */
  ret += sths34pf80_mem_bank_set(ctx, STHS34PF80_MAIN_MEM_BANK);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Function Configuration read
  *
  * @param  ctx      read / write interface definitions
  * @param  addr     embedded register address
  * @param  data     embedded register data
  * @param  len      embedded register data len
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_func_cfg_read(const stmdev_ctx_t *ctx, uint8_t addr, uint8_t *data, uint8_t len)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  uint8_t reg_addr;
  sths34pf80_page_rw_t page_rw = {0};
  int32_t ret;
  uint8_t i;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  /* Enable access to embedded functions register */
  ret += sths34pf80_mem_bank_set(ctx, STHS34PF80_EMBED_FUNC_MEM_BANK);

  /* Enable read mode */
  page_rw.func_cfg_read = 1;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, (uint8_t *)&page_rw, 1);

  for (i = 0; i < len; i++)
  {
    /* Select register address */
    reg_addr = addr + i;
    ret += sths34pf80_write_reg(ctx, STHS34PF80_FUNC_CFG_ADDR, &reg_addr, 1);

    /* Read data */
    ret += sths34pf80_read_reg(ctx, STHS34PF80_FUNC_CFG_DATA, &data[i], 1);
  }

  /* Disable read mode */
  page_rw.func_cfg_read = 0;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* Disable access to embedded functions register */
  ret += sths34pf80_mem_bank_set(ctx, STHS34PF80_MAIN_MEM_BANK);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Presence threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      presence threshold level
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_presence_threshold_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  uint8_t buff[2];
  int32_t ret;

  if ((val & 0x8000U) != 0x0U)
  {
    /* threshold values are on 15 bits */
    return -1;
  }

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret += sths34pf80_func_cfg_write(ctx, STHS34PF80_PRESENCE_THS, &buff[0], 2);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Presence threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      presence threshold level
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_presence_threshold_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_PRESENCE_THS, &buff[0], 2);

  *val = buff[1];
  *val = (*val * 256U) +  buff[0];

  return ret;
}

/**
  * @brief  Motion threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      motion threshold level
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_motion_threshold_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  uint8_t buff[2];
  int32_t ret;

  if ((val & 0x8000U) != 0x0U)
  {
    /* threshold values are on 15 bits */
    return -1;
  }

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret += sths34pf80_func_cfg_write(ctx, STHS34PF80_MOTION_THS, &buff[0], 2);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Motion threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      motion threshold level
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_motion_threshold_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_MOTION_THS, &buff[0], 2);

  *val = buff[1];
  *val = (*val * 256U) +  buff[0];

  return ret;
}

/**
  * @brief  Tambient shock threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Tambient shock threshold level
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tambient_shock_threshold_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  uint8_t buff[2];
  int32_t ret;

  if ((val & 0x8000U) != 0x0U)
  {
    /* threshold values are on 15 bits */
    return -1;
  }

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret += sths34pf80_func_cfg_write(ctx, STHS34PF80_TAMB_SHOCK_THS, &buff[0], 2);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Tambient shock threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Tambient shock threshold level
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tambient_shock_threshold_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_TAMB_SHOCK_THS, &buff[0], 2);

  *val = buff[1];
  *val = (*val * 256U) +  buff[0];

  return ret;
}

/**
  * @brief  Motion hysteresis threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Motion hysteresis value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_motion_hysteresis_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  int32_t ret;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  ret += sths34pf80_func_cfg_write(ctx, STHS34PF80_HYST_MOTION, &val, 1);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Motion hysteresis threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Motion hysteresis value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_motion_hysteresis_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_HYST_MOTION, val, 1);

  return ret;
}

/**
  * @brief  Presence hysteresis.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Presence hysteresis value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_presence_hysteresis_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  int32_t ret;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  ret += sths34pf80_func_cfg_write(ctx, STHS34PF80_HYST_PRESENCE, &val, 1);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Presence hysteresis.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Presence hysteresis value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_presence_hysteresis_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_HYST_PRESENCE, val, 1);

  return ret;
}

/**
  * @brief  Tambient shock hysteresis.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Tambient shock hysteresis value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tambient_shock_hysteresis_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  int32_t ret;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);

  ret += sths34pf80_func_cfg_write(ctx, STHS34PF80_HYST_TAMB_SHOCK, &val, 1);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Tambient shock hysteresis.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Tambient shock hysteresis value
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tambient_shock_hysteresis_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_HYST_TAMB_SHOCK, val, 1);

  return ret;
}

/**
  * @brief  Algo configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Algo configuration structure
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
static int32_t sths34pf80_algo_config_set(const stmdev_ctx_t *ctx, sths34pf80_algo_config_t val)
{
  uint8_t tmp;
  int32_t ret;

  tmp = (val.int_pulsed << 3) | (val.comp_type << 2) | (val.sel_abs << 1);
  ret = sths34pf80_func_cfg_write(ctx, STHS34PF80_ALGO_CONFIG, &tmp, 1);

  return ret;
}

/**
  * @brief  Algo configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Algo configuration structure
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
static int32_t sths34pf80_algo_config_get(const stmdev_ctx_t *ctx, sths34pf80_algo_config_t *val)
{
  uint8_t tmp;
  int32_t ret;

  ret = sths34pf80_func_cfg_read(ctx, STHS34PF80_ALGO_CONFIG, &tmp, 1);
  val->sel_abs = (tmp >> 1) & 0x1U;
  val->comp_type = (tmp >> 2) & 0x1U;
  val->int_pulsed = (tmp >> 3) & 0x1U;

  return ret;
}

/**
  * @brief  Tobject compensation.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Ambient compensation for object temperature (0, 1)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tobject_algo_compensation_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  sths34pf80_algo_config_t config;
  int32_t ret;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);
  if (ret != 0)
  {
    return ret;
  }

  ret = sths34pf80_algo_config_get(ctx, &config);
  config.comp_type = val;
  ret += sths34pf80_algo_config_set(ctx, config);
  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  Tobject compensation.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Ambient compensation for object temperature (0, 1)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_tobject_algo_compensation_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_algo_config_t config;
  int32_t ret;

  ret = sths34pf80_algo_config_get(ctx, &config);
  *val = config.comp_type;

  return ret;
}

/**
  * @brief  presence absolute value.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Presence absolute value (0, 1)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_presence_abs_value_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  sths34pf80_algo_config_t config;
  int32_t ret;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, 0);
  if (ret != 0)
  {
    return ret;
  }

  ret = sths34pf80_algo_config_get(ctx, &config);
  config.sel_abs = val;
  ret += sths34pf80_algo_config_set(ctx, config);
  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ret += sths34pf80_odr_safe_set(ctx, &ctrl1, odr);

  return ret;
}

/**
  * @brief  presence absolute value.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Presence absolute value (0, 1)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_presence_abs_value_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_algo_config_t config;
  int32_t ret;

  ret = sths34pf80_algo_config_get(ctx, &config);
  *val = config.sel_abs;

  return ret;
}

/**
  * @brief  int_or mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      int_pulsed value (0, 1)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_int_or_pulsed_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  sths34pf80_algo_config_t config;
  int32_t ret;

  ret = sths34pf80_algo_config_get(ctx, &config);
  config.int_pulsed = val;
  ret += sths34pf80_algo_config_set(ctx, config);

  return ret;
}

/**
  * @brief  int_or mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      int_pulsed value (0, 1)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_int_or_pulsed_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  sths34pf80_algo_config_t config;
  int32_t ret;

  ret = sths34pf80_algo_config_get(ctx, &config);
  *val = config.int_pulsed;

  return ret;
}

/*
 * Internal routine to reset algo bit
 */
static int32_t sths34pf80_reset_algo_bit_set(const stmdev_ctx_t *ctx)
{
  sths34pf80_page_rw_t page_rw = {0};
  int32_t ret;

  /* Enable access to embedded functions register */
  ret = sths34pf80_mem_bank_set(ctx, STHS34PF80_EMBED_FUNC_MEM_BANK);

  /* Enable write mode */
  page_rw.func_cfg_write = 1;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* Select register address (it will autoincrement when writing) */
  uint8_t addr = STHS34PF80_RESET_ALGO;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_FUNC_CFG_ADDR, &addr, 1);

  /* Write data */
  uint8_t data = 0x01;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_FUNC_CFG_DATA, &data, 1);

  /* Disable write mode */
  page_rw.func_cfg_write = 0;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* Disable access to embedded functions register */
  ret += sths34pf80_mem_bank_set(ctx, STHS34PF80_MAIN_MEM_BANK);

  return ret;
}

/**
  * @brief  Reset algo
  *
  * @param  ctx      read / write interface definitions
  * @param  val      reset algo structure
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t sths34pf80_algo_reset(const stmdev_ctx_t *ctx)
{
  sths34pf80_ctrl1_t ctrl1;
  uint8_t odr;
  int32_t ret;

  /* Save current odr and enter PD mode */
  ret = sths34pf80_read_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);
  odr = ctrl1.odr;
  ret += sths34pf80_safe_power_down(ctx, &ctrl1);

  ret += sths34pf80_reset_algo_bit_set(ctx);

  /* Set saved odr back */
  ctrl1.odr = odr;
  ret += sths34pf80_write_reg(ctx, STHS34PF80_CTRL1, (uint8_t *)&ctrl1, 1);

  return ret;
}

/**
  * @}
  *
  */
