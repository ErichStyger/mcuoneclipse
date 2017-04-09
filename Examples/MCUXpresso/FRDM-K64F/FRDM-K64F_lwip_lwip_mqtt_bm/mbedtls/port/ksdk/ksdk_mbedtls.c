/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "fsl_common.h"

#define CLEAN_RETURN(value) \
    {                       \
        ret = value;        \
        goto cleanup;       \
    }

/******************************************************************************/
/*************************** DES **********************************************/
/******************************************************************************/

#if defined(MBEDTLS_DES_C)

#if defined(MBEDTLS_FREESCALE_LTC_DES) || defined(MBEDTLS_FREESCALE_MMCAU_DES)

#include "mbedtls/des.h"

#if defined(MBEDTLS_FREESCALE_MMCAU_DES)
const unsigned char parityLookup[128] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0,
                                         0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1,
                                         0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1,
                                         1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                                         0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
#endif

/*
 * DES key schedule (56-bit, encryption)
 */
int mbedtls_des_setkey_enc(mbedtls_des_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
    int i;
    unsigned char *sk_b = (unsigned char *)ctx->sk;

#if defined(MBEDTLS_FREESCALE_LTC_DES)
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE; i++)
    {
        sk_b[i] = key[i];
    }
    ctx->mode = MBEDTLS_DES_ENCRYPT;
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    /* fix key parity, if needed */
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE; i++)
    {
        sk_b[i] = ((key[i] & 0xFE) | parityLookup[key[i] >> 1]);
    }
#endif
    ctx->mode = MBEDTLS_DES_ENCRYPT;

    return (0);
}

/*
 * DES key schedule (56-bit, decryption)
 */
int mbedtls_des_setkey_dec(mbedtls_des_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
    int i;
    unsigned char *sk_b = (unsigned char *)ctx->sk;

#if defined(MBEDTLS_FREESCALE_LTC_DES)
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE; i++)
    {
        sk_b[i] = key[i];
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    /* fix key parity, if needed */
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE; i++)
    {
        sk_b[i] = ((key[i] & 0xFE) | parityLookup[key[i] >> 1]);
    }
#endif
    ctx->mode = MBEDTLS_DES_DECRYPT;

    return (0);
}

/*
 * Triple-DES key schedule (112-bit, encryption)
 */
int mbedtls_des3_set2key_enc(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 2])
{
    int i;
    unsigned char *sk_b = (unsigned char *)ctx->sk;

#if defined(MBEDTLS_FREESCALE_LTC_DES)
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 2; i++)
    {
        sk_b[i] = key[i];
    }
    for (i = MBEDTLS_DES_KEY_SIZE * 2; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = key[i - MBEDTLS_DES_KEY_SIZE * 2];
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    /* fix key parity, if needed */
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 2; i++)
    {
        sk_b[i] = ((key[i] & 0xFE) | parityLookup[key[i] >> 1]);
    }
    for (i = MBEDTLS_DES_KEY_SIZE * 2; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = ((key[i - MBEDTLS_DES_KEY_SIZE * 2] & 0xFE) | parityLookup[key[i - MBEDTLS_DES_KEY_SIZE * 2] >> 1]);
    }
#endif
    ctx->mode = MBEDTLS_DES_ENCRYPT;

    return (0);
}

/*
 * Triple-DES key schedule (112-bit, decryption)
 */
int mbedtls_des3_set2key_dec(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 2])
{
    int i;
    unsigned char *sk_b = (unsigned char *)ctx->sk;

#if defined(MBEDTLS_FREESCALE_LTC_DES)
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 2; i++)
    {
        sk_b[i] = key[i];
    }
    for (i = MBEDTLS_DES_KEY_SIZE * 2; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = key[i - MBEDTLS_DES_KEY_SIZE * 2];
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    /* fix key parity, if needed */
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 2; i++)
    {
        sk_b[i] = ((key[i] & 0xFE) | parityLookup[key[i] >> 1]);
    }
    for (i = MBEDTLS_DES_KEY_SIZE * 2; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = ((key[i - MBEDTLS_DES_KEY_SIZE * 2] & 0xFE) | parityLookup[key[i - MBEDTLS_DES_KEY_SIZE * 2] >> 1]);
    }
#endif
    ctx->mode = MBEDTLS_DES_DECRYPT;

    return (0);
}

/*
 * Triple-DES key schedule (168-bit, encryption)
 */
int mbedtls_des3_set3key_enc(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 3])
{
    int i;
    unsigned char *sk_b = (unsigned char *)ctx->sk;

#if defined(MBEDTLS_FREESCALE_LTC_DES)
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = key[i];
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    /* fix key parity, if needed */
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = ((key[i] & 0xFE) | parityLookup[key[i] >> 1]);
    }
#endif
    ctx->mode = MBEDTLS_DES_ENCRYPT;

    return (0);
}

/*
 * Triple-DES key schedule (168-bit, decryption)
 */
int mbedtls_des3_set3key_dec(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 3])
{
    int i;
    unsigned char *sk_b = (unsigned char *)ctx->sk;

#if defined(MBEDTLS_FREESCALE_LTC_DES)
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = key[i];
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    /* fix key parity, if needed */
    for (i = 0; i < MBEDTLS_DES_KEY_SIZE * 3; i++)
    {
        sk_b[i] = ((key[i] & 0xFE) | parityLookup[key[i] >> 1]);
    }
#endif
    ctx->mode = MBEDTLS_DES_DECRYPT;
    return (0);
}

/*
 * DES-ECB block encryption/decryption
 */
int mbedtls_des_crypt_ecb(mbedtls_des_context *ctx, const unsigned char input[8], unsigned char output[8])
{
    uint8_t *key = (uint8_t *)ctx->sk;
#if defined(MBEDTLS_FREESCALE_LTC_DES)
    if (ctx->mode == MBEDTLS_DES_ENCRYPT)
    {
        LTC_DES_EncryptEcb(LTC_INSTANCE, input, output, 8, key);
    }
    else
    {
        LTC_DES_DecryptEcb(LTC_INSTANCE, input, output, 8, key);
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    if (ctx->mode == MBEDTLS_DES_ENCRYPT)
    {
        MMCAU_DES_EncryptEcb(input, key, output);
    }
    else
    {
        MMCAU_DES_DecryptEcb(input, key, output);
    }
#endif
    return (0);
}

/*
 * 3DES-ECB block encryption/decryption
 */
int mbedtls_des3_crypt_ecb(mbedtls_des3_context *ctx, const unsigned char input[8], unsigned char output[8])
{
    uint8_t *key = (uint8_t *)ctx->sk;
#if defined(MBEDTLS_FREESCALE_LTC_DES)
    if (ctx->mode == MBEDTLS_DES_ENCRYPT)
    {
        LTC_DES3_EncryptEcb(LTC_INSTANCE, input, output, 8, key, key + 8, key + 16);
    }
    else
    {
        LTC_DES3_DecryptEcb(LTC_INSTANCE, input, output, 8, key, key + 8, key + 16);
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_DES)
    if (ctx->mode == MBEDTLS_DES_ENCRYPT)
    {
        MMCAU_DES_EncryptEcb(input, key, output);
        MMCAU_DES_DecryptEcb(output, key + 8, output);
        MMCAU_DES_EncryptEcb(output, key + 16, output);
    }
    else
    {
        MMCAU_DES_DecryptEcb(input, key + 16, output);
        MMCAU_DES_EncryptEcb(output, key + 8, output);
        MMCAU_DES_DecryptEcb(output, key, output);
    }
#endif
    return (0);
}

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/*
 * DES-CBC buffer encryption/decryption
 */
#if defined(MBEDTLS_FREESCALE_LTC_DES)
int mbedtls_des_crypt_cbc(mbedtls_des_context *ctx,
                          int mode,
                          size_t length,
                          unsigned char iv[8],
                          const unsigned char *input,
                          unsigned char *output)
{
    unsigned char temp[8];
    uint8_t *key = (uint8_t *)ctx->sk;

    if (length % 8)
        return (MBEDTLS_ERR_DES_INVALID_INPUT_LENGTH);

    if (mode == MBEDTLS_DES_ENCRYPT)
    {
        LTC_DES_EncryptCbc(LTC_INSTANCE, input, output, length, iv, key);
        memcpy(iv, output + length - 8, 8);
    }
    else /* MBEDTLS_DES_DECRYPT */
    {
        memcpy(temp, input + length - 8, 8);
        LTC_DES_DecryptCbc(LTC_INSTANCE, input, output, length, iv, key);
        memcpy(iv, temp, 8);
    }
    return (0);
}

/*
 * 3DES-CBC buffer encryption/decryption
 */
int mbedtls_des3_crypt_cbc(mbedtls_des3_context *ctx,
                           int mode,
                           size_t length,
                           unsigned char iv[8],
                           const unsigned char *input,
                           unsigned char *output)
{
    unsigned char temp[8];
    uint8_t *key = (uint8_t *)ctx->sk;

    if (length % 8)
        return (MBEDTLS_ERR_DES_INVALID_INPUT_LENGTH);

    if (mode == MBEDTLS_DES_ENCRYPT)
    {
        LTC_DES3_EncryptCbc(LTC_INSTANCE, input, output, length, iv, key, key + 8, key + 16);
        memcpy(iv, output + length - 8, 8);
    }
    else /* MBEDTLS_DES_DECRYPT */
    {
        memcpy(temp, input + length - 8, 8);
        LTC_DES3_DecryptCbc(LTC_INSTANCE, input, output, length, iv, key, key + 8, key + 16);
        memcpy(iv, temp, 8);
    }

    return (0);
}

#endif /* MBEDTLS_FREESCALE_LTC_DES */
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#endif /*MBEDTLS_FREESCALE_LTC_DES || MBEDTLS_FREESCALE_MMCAU_DES*/

#endif /* MBEDTLS_DES_C */

/******************************************************************************/
/*************************** AES **********************************************/
/******************************************************************************/

#if defined(MBEDTLS_AES_C)

#if defined(MBEDTLS_FREESCALE_LTC_AES) || defined(MBEDTLS_FREESCALE_MMCAU_AES) || \
    defined(MBEDTLS_FREESCALE_LPC_AES) || defined(MBEDTLS_FREESCALE_CAU3_AES)

#include "mbedtls/aes.h"

/*
 * AES key schedule (encryption)
 */
int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
    uint32_t *RK;

#if defined(MBEDTLS_FREESCALE_LTC_AES) || defined(MBEDTLS_FREESCALE_LPC_AES) || defined(MBEDTLS_FREESCALE_CAU3_AES)
    const unsigned char *key_tmp = key;
    ctx->rk = RK = ctx->buf;
    memcpy(RK, key_tmp, keybits / 8);

    switch (keybits)
    { /* Set keysize in bytes.*/
        case 128:
            ctx->nr = 16;
            break;
        case 192:
            ctx->nr = 24;
            break;
        case 256:
            ctx->nr = 32;
            break;
        default:
            return (MBEDTLS_ERR_AES_INVALID_KEY_LENGTH);
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    ctx->rk = RK = ctx->buf;

    switch (keybits)
    {
        case 128:
            ctx->nr = 10;
            break;
        case 192:
            ctx->nr = 12;
            break;
        case 256:
            ctx->nr = 14;
            break;
        default:
            return (MBEDTLS_ERR_AES_INVALID_KEY_LENGTH);
    }

    MMCAU_AES_SetKey(key, keybits / 8, (uint8_t *)RK);
#endif
    return (0);
}

/*
 * AES key schedule (decryption)
 */
int mbedtls_aes_setkey_dec(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
    uint32_t *RK;

    ctx->rk = RK = ctx->buf;

#if defined(MBEDTLS_FREESCALE_LTC_AES) || defined(MBEDTLS_FREESCALE_LPC_AES) || defined(MBEDTLS_FREESCALE_CAU3_AES)
    const unsigned char *key_tmp = key;

    memcpy(RK, key_tmp, keybits / 8);

    switch (keybits)
    {
        case 128:
            ctx->nr = 16;
            break;
        case 192:
            ctx->nr = 24;
            break;
        case 256:
            ctx->nr = 32;
            break;
        default:
            return (MBEDTLS_ERR_AES_INVALID_KEY_LENGTH);
    }
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    ctx->rk = RK = ctx->buf;

    switch (keybits)
    {
        case 128:
            ctx->nr = 10;
            break;
        case 192:
            ctx->nr = 12;
            break;
        case 256:
            ctx->nr = 14;
            break;
        default:
            return (MBEDTLS_ERR_AES_INVALID_KEY_LENGTH);
    }

    MMCAU_AES_SetKey(key, keybits / 8, (uint8_t *)RK);
#endif

    return 0;
}

/*
 * AES-ECB block encryption
 */
void mbedtls_aes_encrypt(mbedtls_aes_context *ctx, const unsigned char input[16], unsigned char output[16])
{
    uint8_t *key;

    key = (uint8_t *)ctx->rk;
#if defined(MBEDTLS_FREESCALE_LTC_AES)
    LTC_AES_EncryptEcb(LTC_INSTANCE, input, output, 16, key, ctx->nr);
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    MMCAU_AES_EncryptEcb(input, key, ctx->nr, output);
#elif defined(MBEDTLS_FREESCALE_CAU3_AES)
    cauKeyContext cau_ctx;

    cau_ctx.keySched = ctx->rk;
    cau_ctx.keySize = ctx->nr;
    memcpy(&cau_ctx.key, key, cau_ctx.keySize);
    CAU_LoadKeyContext((uint32_t *)&cau_ctx, 0, MBEDTLS_CAU3_COMPLETION_SIGNAL);
    CAU3_WRAP_AES_EncryptEcb(input, 0, output, MBEDTLS_CAU3_COMPLETION_SIGNAL);
#elif defined(MBEDTLS_FREESCALE_LPC_AES)
    AES_SetKey(AES_INSTANCE, key, ctx->nr);
    AES_EncryptEcb(AES_INSTANCE, input, output, 16);
#endif
}

/*
 * AES-ECB block decryption
 */
void mbedtls_aes_decrypt(mbedtls_aes_context *ctx, const unsigned char input[16], unsigned char output[16])
{
    uint8_t *key;

    key = (uint8_t *)ctx->rk;
#if defined(MBEDTLS_FREESCALE_LTC_AES)
    LTC_AES_DecryptEcb(LTC_INSTANCE, input, output, 16, key, ctx->nr, kLTC_EncryptKey);
#elif defined(MBEDTLS_FREESCALE_MMCAU_AES)
    MMCAU_AES_DecryptEcb(input, key, ctx->nr, output);
#elif defined(MBEDTLS_FREESCALE_CAU3_AES)
    cauKeyContext cau_ctx;

    cau_ctx.keySched = ctx->rk;
    cau_ctx.keySize = ctx->nr;
    memcpy(&cau_ctx.key, key, cau_ctx.keySize);
    CAU_LoadKeyContext((uint32_t *)&cau_ctx, 0, MBEDTLS_CAU3_COMPLETION_SIGNAL);
    CAU3_WRAP_AES_DecryptEcb(input, 0, output, MBEDTLS_CAU3_COMPLETION_SIGNAL);
#elif defined(MBEDTLS_FREESCALE_LPC_AES)
    AES_SetKey(AES_INSTANCE, key, ctx->nr);
    AES_DecryptEcb(AES_INSTANCE, input, output, 16);
#endif
}

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/*
 * AES-CBC buffer encryption/decryption
 */
#if defined(MBEDTLS_FREESCALE_LTC_AES)
int mbedtls_aes_crypt_cbc(mbedtls_aes_context *ctx,
                          int mode,
                          size_t length,
                          unsigned char iv[16],
                          const unsigned char *input,
                          unsigned char *output)
{
    uint8_t *key = (uint8_t *)ctx->rk;
    uint32_t keySize = ctx->nr;

    if (length % 16)
        return (MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH);

    if (mode == MBEDTLS_AES_DECRYPT)
    {
        uint8_t tmp[16];
        memcpy(tmp, input + length - 16, 16);
        LTC_AES_DecryptCbc(LTC_INSTANCE, input, output, length, iv, key, keySize, kLTC_EncryptKey);
        memcpy(iv, tmp, 16);
    }
    else
    {
        LTC_AES_EncryptCbc(LTC_INSTANCE, input, output, length, iv, key, keySize);
        memcpy(iv, output + length - 16, 16);
    }

    return (0);
}
#elif defined(MBEDTLS_FREESCALE_LPC_AES)
int mbedtls_aes_crypt_cbc(mbedtls_aes_context *ctx,
                          int mode,
                          size_t length,
                          unsigned char iv[16],
                          const unsigned char *input,
                          unsigned char *output)
{
    uint8_t *key;
    size_t keySize;

    if (length % 16)
        return (MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH);

    key = (uint8_t *)ctx->rk;
    keySize = (size_t)ctx->nr;
    AES_SetKey(AES_INSTANCE, key, keySize);

    if (mode == MBEDTLS_AES_DECRYPT)
    {
        uint8_t tmp[16];
        memcpy(tmp, input + length - 16, 16);
        AES_DecryptCbc(AES_INSTANCE, tmp, output, length, iv);
        memcpy(iv, tmp, 16);
    }
    else
    {
        AES_EncryptCbc(AES_INSTANCE, input, output, length, iv);
        memcpy(iv, output + length - 16, 16);
    }

    return (0);
}
#endif
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
#if defined(MBEDTLS_FREESCALE_LPC_AES)
/*
 * AES-CFB128 buffer encryption/decryption
 */
int mbedtls_aes_crypt_cfb128(mbedtls_aes_context *ctx,
                             int mode,
                             size_t length,
                             size_t *iv_off,
                             unsigned char iv[16],
                             const unsigned char *input,
                             unsigned char *output)
{
    uint8_t *key;
    size_t keySize;

    key = (uint8_t *)ctx->rk;
    keySize = (size_t)ctx->nr;
    AES_SetKey(AES_INSTANCE, key, keySize);

    if (mode == MBEDTLS_AES_DECRYPT)
    {
        AES_DecryptCfb(AES_INSTANCE, input, output, length, iv);
    }
    else
    {
        AES_EncryptCfb(AES_INSTANCE, input, output, length, iv);
    }

    return (0);
}

/*
 * AES-CFB8 buffer encryption/decryption
 */
int mbedtls_aes_crypt_cfb8(mbedtls_aes_context *ctx,
                           int mode,
                           size_t length,
                           unsigned char iv[16],
                           const unsigned char *input,
                           unsigned char *output)
{
    int status;
    unsigned char c;
    unsigned char ov[17];

    while (length--)
    {
        memcpy(ov, iv, 16);
        status = mbedtls_aes_crypt_ecb(ctx, MBEDTLS_AES_ENCRYPT, iv, iv);
        if (status != 0)
        {
            return status;
        }

        if (mode == MBEDTLS_AES_DECRYPT)
            ov[16] = *input;

        c = *output++ = (unsigned char)(iv[0] ^ *input++);

        if (mode == MBEDTLS_AES_ENCRYPT)
            ov[16] = c;

        memcpy(iv, ov + 1, 16);
    }

    return (0);
}
#endif /* MBEDTLS_FREESCALE_LPC_AES */
#endif /* MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
/*
 * AES-CTR buffer encryption/decryption
 */
#if defined(MBEDTLS_FREESCALE_LTC_AES)
int mbedtls_aes_crypt_ctr(mbedtls_aes_context *ctx,
                          size_t length,
                          size_t *nc_off,
                          unsigned char nonce_counter[16],
                          unsigned char stream_block[16],
                          const unsigned char *input,
                          unsigned char *output)
{
    uint8_t *key;
    uint32_t keySize;

    key = (uint8_t *)ctx->rk;
    keySize = ctx->nr;
    LTC_AES_CryptCtr(LTC_INSTANCE, input, output, length, nonce_counter, key, keySize, stream_block,
                     (uint32_t *)nc_off);

    return (0);
}
#elif defined(MBEDTLS_FREESCALE_LPC_AES)
int mbedtls_aes_crypt_ctr(mbedtls_aes_context *ctx,
                          size_t length,
                          size_t *nc_off,
                          unsigned char nonce_counter[16],
                          unsigned char stream_block[16],
                          const unsigned char *input,
                          unsigned char *output)
{
    uint8_t *key;
    size_t keySize;

    key = (uint8_t *)ctx->rk;
    keySize = (size_t)ctx->nr;

    AES_SetKey(AES_INSTANCE, key, keySize);
    AES_CryptCtr(AES_INSTANCE, input, output, length, nonce_counter, stream_block, nc_off);

    return (0);
}
#endif
#endif /* MBEDTLS_CIPHER_MODE_CTR */

#if defined(MBEDTLS_CCM_C)

#include "mbedtls/ccm.h"

#define CCM_ENCRYPT 0
#define CCM_DECRYPT 1

/*
 * Authenticated encryption or decryption
 */
#if defined(MBEDTLS_FREESCALE_LTC_AES)
static int ccm_auth_crypt(mbedtls_ccm_context *ctx,
                          int mode,
                          size_t length,
                          const unsigned char *iv,
                          size_t iv_len,
                          const unsigned char *add,
                          size_t add_len,
                          const unsigned char *input,
                          unsigned char *output,
                          unsigned char *tag,
                          size_t tag_len)
{
    status_t status;
    const uint8_t *key;
    uint8_t keySize;
    mbedtls_aes_context *aes_ctx;

    aes_ctx = (mbedtls_aes_context *)ctx->cipher_ctx.cipher_ctx;
    key = (uint8_t *)aes_ctx->rk;
    keySize = aes_ctx->nr;
    if (mode == CCM_ENCRYPT)
    {
        status = LTC_AES_EncryptTagCcm(LTC_INSTANCE, input, output, length, iv, iv_len, add, add_len, key, keySize, tag,
                                       tag_len);
    }
    else
    {
        status = LTC_AES_DecryptTagCcm(LTC_INSTANCE, input, output, length, iv, iv_len, add, add_len, key, keySize, tag,
                                       tag_len);
    }

    if (status == kStatus_InvalidArgument)
    {
        return MBEDTLS_ERR_CCM_BAD_INPUT;
    }
    else if (status != kStatus_Success)
    {
        return MBEDTLS_ERR_CCM_AUTH_FAILED;
    }

    return (0);
}

/*
 * Authenticated encryption
 */
int mbedtls_ccm_encrypt_and_tag(mbedtls_ccm_context *ctx,
                                size_t length,
                                const unsigned char *iv,
                                size_t iv_len,
                                const unsigned char *add,
                                size_t add_len,
                                const unsigned char *input,
                                unsigned char *output,
                                unsigned char *tag,
                                size_t tag_len)
{
    return (ccm_auth_crypt(ctx, CCM_ENCRYPT, length, iv, iv_len, add, add_len, input, output, tag, tag_len));
}

/*
 * Authenticated decryption
 */
int mbedtls_ccm_auth_decrypt(mbedtls_ccm_context *ctx,
                             size_t length,
                             const unsigned char *iv,
                             size_t iv_len,
                             const unsigned char *add,
                             size_t add_len,
                             const unsigned char *input,
                             unsigned char *output,
                             const unsigned char *tag,
                             size_t tag_len)
{
    unsigned char tag_copy[16];

    memcpy(tag_copy, tag, tag_len);
    return (ccm_auth_crypt(ctx, CCM_DECRYPT, length, iv, iv_len, add, add_len, input, output, tag_copy, tag_len));
}
#endif /* MBEDTLS_FREESCALE_LTC_AES */
#endif /* MBEDTLS_CCM_C */

#if defined(MBEDTLS_GCM_C)
#if defined(MBEDTLS_FREESCALE_LTC_AES_GCM)

#include "mbedtls/gcm.h"

int mbedtls_gcm_crypt_and_tag(mbedtls_gcm_context *ctx,
                              int mode,
                              size_t length,
                              const unsigned char *iv,
                              size_t iv_len,
                              const unsigned char *add,
                              size_t add_len,
                              const unsigned char *input,
                              unsigned char *output,
                              size_t tag_len,
                              unsigned char *tag)
{
    status_t status;
    uint8_t *key;
    uint32_t keySize;
    mbedtls_aes_context *aes_ctx;

    ctx->len = length;
    ctx->add_len = add_len;
    aes_ctx = (mbedtls_aes_context *)ctx->cipher_ctx.cipher_ctx;
    key = (uint8_t *)aes_ctx->rk;
    keySize = aes_ctx->nr;
    if (mode == MBEDTLS_GCM_ENCRYPT)
    {
        status = LTC_AES_EncryptTagGcm(LTC_INSTANCE, input, output, length, iv, iv_len, add, add_len, key, keySize, tag,
                                       tag_len);
    }
    else
    {
        status = LTC_AES_DecryptTagGcm(LTC_INSTANCE, input, output, length, iv, iv_len, add, add_len, key, keySize, tag,
                                       tag_len);
    }

    if (status == kStatus_InvalidArgument)
    {
        return MBEDTLS_ERR_GCM_BAD_INPUT;
    }
    else if (status != kStatus_Success)
    {
        return MBEDTLS_ERR_GCM_AUTH_FAILED;
    }

    return 0;
}

int mbedtls_gcm_auth_decrypt(mbedtls_gcm_context *ctx,
                             size_t length,
                             const unsigned char *iv,
                             size_t iv_len,
                             const unsigned char *add,
                             size_t add_len,
                             const unsigned char *tag,
                             size_t tag_len,
                             const unsigned char *input,
                             unsigned char *output)
{
    unsigned char tag_copy[16];
    memcpy(tag_copy, tag, tag_len);
    return (mbedtls_gcm_crypt_and_tag(ctx, MBEDTLS_GCM_DECRYPT, length, iv, iv_len, add, add_len, input, output,
                                      tag_len, tag_copy));
}

#elif defined(MBEDTLS_FREESCALE_LPC_AES_GCM)

#include "mbedtls/gcm.h"

int mbedtls_gcm_crypt_and_tag(mbedtls_gcm_context *ctx,
                              int mode,
                              size_t length,
                              const unsigned char *iv,
                              size_t iv_len,
                              const unsigned char *add,
                              size_t add_len,
                              const unsigned char *input,
                              unsigned char *output,
                              size_t tag_len,
                              unsigned char *tag)
{
    status_t status;
    uint8_t *key;
    size_t keySize;
    mbedtls_aes_context *aes_ctx;

    ctx->len = length;
    ctx->add_len = add_len;
    aes_ctx = (mbedtls_aes_context *)ctx->cipher_ctx.cipher_ctx;
    key = (uint8_t *)aes_ctx->rk;
    keySize = (size_t)aes_ctx->nr;

    status = AES_SetKey(AES_INSTANCE, key, keySize);
    if (status != kStatus_Success)
    {
        return MBEDTLS_ERR_GCM_BAD_INPUT;
    }

    if (mode == MBEDTLS_GCM_ENCRYPT)
    {
        status = AES_EncryptTagGcm(AES_INSTANCE, input, output, length, iv, iv_len, add, add_len, tag, tag_len);
    }
    else
    {
        status = AES_DecryptTagGcm(AES_INSTANCE, input, output, length, iv, iv_len, add, add_len, tag, tag_len);
    }

    if (status == kStatus_InvalidArgument)
    {
        return MBEDTLS_ERR_GCM_BAD_INPUT;
    }
    else if (status != kStatus_Success)
    {
        return MBEDTLS_ERR_GCM_AUTH_FAILED;
    }

    return 0;
}

int mbedtls_gcm_auth_decrypt(mbedtls_gcm_context *ctx,
                             size_t length,
                             const unsigned char *iv,
                             size_t iv_len,
                             const unsigned char *add,
                             size_t add_len,
                             const unsigned char *tag,
                             size_t tag_len,
                             const unsigned char *input,
                             unsigned char *output)
{
    unsigned char tag_copy[16];

    memcpy(tag_copy, tag, tag_len);
    return (mbedtls_gcm_crypt_and_tag(ctx, MBEDTLS_GCM_DECRYPT, length, iv, iv_len, add, add_len, input, output,
                                      tag_len, tag_copy));
}

#endif
#endif /* MBEDTLS_GCM_C */

#endif /* MBEDTLS_FREESCALE_LTC_AES || MBEDTLS_FREESCALE_MMCAU_AES || MBEDTLS_FREESCALE_LPC_AES */

#endif /* MBEDTLS_AES_C */

/******************************************************************************/
/*************************** PKHA *********************************************/
/******************************************************************************/

#if defined(MBEDTLS_FREESCALE_LTC_PKHA) || defined(MBEDTLS_FREESCALE_CAU3_PKHA)

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_calloc calloc
#define mbedtls_free free
#endif

static void ltc_reverse_array(uint8_t *src, size_t src_len)
{
    int i;

    for (i = 0; i < src_len / 2; i++)
    {
        uint8_t tmp;

        tmp = src[i];
        src[i] = src[src_len - 1 - i];
        src[src_len - 1 - i] = tmp;
    }
}

#if defined(MBEDTLS_BIGNUM_C)

#include "mbedtls/bignum.h"

#if defined(MBEDTLS_FREESCALE_CAU3_PKHA)
typedef size_t pkha_size_t;
#define LTC_PKHA_ModAdd CAU3_PKHA_ModAdd
#define LTC_PKHA_ModSub1 CAU3_PKHA_ModSub1
#define LTC_PKHA_ModMul CAU3_PKHA_ModMul
#define LTC_PKHA_ModRed CAU3_PKHA_ModRed
#define LTC_PKHA_ModExp CAU3_PKHA_ModExp
#define LTC_PKHA_GCD CAU3_PKHA_GCD
#define LTC_PKHA_ModInv CAU3_PKHA_ModInv
#define LTC_PKHA_PrimalityTest CAU3_PKHA_PrimalityTest
#define LTC_INSTANCE ((CAU3_PKHA_Type *)CAU3_BASE)

#define kLTC_PKHA_IntegerArith kCAU3_PKHA_IntegerArith
#define kLTC_PKHA_NormalValue kCAU3_PKHA_NormalValue
#define kLTC_PKHA_TimingEqualized kCAU3_PKHA_TimingEqualized
#else
typedef uint16_t pkha_size_t;
#endif

#if defined(MBEDTLS_MPI_ADD_ABS_ALT)

/* Access to original version of mbedtls_mpi_add_abs function. */
int mbedtls_mpi_add_abs_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B );

/*
 * Unsigned addition: X = |A| + |B|  (HAC 14.7)
 */
int mbedtls_mpi_add_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    pkha_size_t sizeA = mbedtls_mpi_size(A);
    pkha_size_t sizeB = mbedtls_mpi_size(B);
    pkha_size_t sizeN = FREESCALE_PKHA_INT_MAX_BYTES;
    
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    /*
     * Perform HW acceleration only if the size in bytes is less than maximum.
     * Since modular add is used below, the result would be wrong
     * if the real sum of operands exceeded LTC maximum number value.
     */
    if ((sizeA < sizeN) && (sizeB < sizeN))
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        pkha_size_t sizeC;
        uint8_t *N = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrB = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrC = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == N) || (NULL == ptrA) || (NULL == ptrB) || (NULL == ptrC))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        memset(N, 0xFF, sizeN);

        mbedtls_mpi_write_binary(A, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(B, ptrB, sizeB);
        ltc_reverse_array(ptrB, sizeB);

        ret = (int)LTC_PKHA_ModAdd(LTC_INSTANCE, ptrA, sizeA, ptrB, sizeB, N, sizeN, ptrC, &sizeC, kLTC_PKHA_IntegerArith);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrC, sizeC);
        mbedtls_mpi_read_binary(X, ptrC, sizeC);
        X->s = 1;
    cleanup:
        if (N)
        {
            mbedtls_free(N);
        }
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrB)
        {
            mbedtls_free(ptrB);
        }
        if (ptrC)
        {
            mbedtls_free(ptrC);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_add_abs_orig(X, A, B);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_ADD_ABS_ALT */

#if defined(MBEDTLS_MPI_SUB_ABS_ALT)

/* Access to original version of mbedtls_mpi_sub_abs function. */
int mbedtls_mpi_sub_abs_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B );

/*
 * Unsigned subtraction: X = |A| - |B|  (HAC 14.9)
 */
int mbedtls_mpi_sub_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    pkha_size_t sizeA = mbedtls_mpi_size(A);
    pkha_size_t sizeB = mbedtls_mpi_size(B);
    pkha_size_t sizeN = FREESCALE_PKHA_INT_MAX_BYTES;

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    /*
     * Perform HW acceleration only if |A| >= |B|. Since modular subtraction is used below,
     * the result would be wrong if the real sum of operands exceeded maximum.
     */
    if ((sizeA <= sizeN) && (sizeB <= sizeN) && (mbedtls_mpi_cmp_abs(A, B) >= 0))
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        pkha_size_t sizeC;
        uint8_t *N = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrB = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrC = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == N) || (NULL == ptrA) || (NULL == ptrB) || (NULL == ptrC))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        memset(N, 0xFF, sizeN);

        mbedtls_mpi_write_binary(A, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(B, ptrB, sizeB);
        ltc_reverse_array(ptrB, sizeB);

        ret = (int)LTC_PKHA_ModSub1(LTC_INSTANCE, ptrA, sizeA, ptrB, sizeB, N, sizeN, ptrC, &sizeC);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrC, sizeC);
        mbedtls_mpi_read_binary(X, ptrC, sizeC);
        X->s = 1;
    cleanup:
        if (N)
        {
            mbedtls_free(N);
        }
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrB)
        {
            mbedtls_free(ptrB);
        }
        if (ptrC)
        {
            mbedtls_free(ptrC);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_sub_abs_orig(X, A, B);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_SUB_ABS_ALT */

#if defined(MBEDTLS_MPI_MUL_MPI_ALT)

/* Access to original version of mbedtls_mpi_mul_mpi function. */
int mbedtls_mpi_mul_mpi_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B );

/*
 * Baseline multiplication: X = A * B  (HAC 14.12)
 */
int mbedtls_mpi_mul_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    pkha_size_t sizeA = mbedtls_mpi_size(A);
    pkha_size_t sizeB = mbedtls_mpi_size(B);
    pkha_size_t sizeN = FREESCALE_PKHA_INT_MAX_BYTES;

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    /*
     * Should be "if ((sizeA + sizeB) <= sizeN)", but if the multiplication result
     * would be maximum LTC number (the same value as the modulus N below),
     * zero would be returned instead, which is wrong value.
     */
    if ((sizeA + sizeB) < sizeN)
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        pkha_size_t sizeC;

        uint8_t *N = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrB = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrC = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == N) || (NULL == ptrA) || (NULL == ptrB) || (NULL == ptrC))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        memset(N, 0xFF, sizeN);
        
        mbedtls_mpi_write_binary(A, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(B, ptrB, sizeB);
        ltc_reverse_array(ptrB, sizeB);

        /*
         * Modular multiplication operation is used here. Since the modulus N is larger
         * than the expected result of A * B, the effect is normal multiplication.
         * TODO use PKHA MUL_IM_OM instead.
         */
        ret = (int)LTC_PKHA_ModMul(LTC_INSTANCE, ptrA, sizeA, ptrB, sizeB, N, sizeN, ptrC, &sizeC, kLTC_PKHA_IntegerArith,
                                   kLTC_PKHA_NormalValue, kLTC_PKHA_NormalValue, kLTC_PKHA_TimingEqualized);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrC, sizeC);
        mbedtls_mpi_read_binary(X, ptrC, sizeC);
        X->s = A->s * B->s;
    cleanup:
        if (N)
        {
            mbedtls_free(N);
        }
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrB)
        {
            mbedtls_free(ptrB);
        }
        if (ptrC)
        {
            mbedtls_free(ptrC);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_mul_mpi_orig(X, A, B);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_MUL_MPI_ALT */

#if defined(MBEDTLS_MPI_MOD_MPI_ALT)

/* Access to original version of mbedtls_mpi_mod_mpi function. */
int mbedtls_mpi_mod_mpi_orig( mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B );

/*
 * Modulo: R = A mod B
 */
int mbedtls_mpi_mod_mpi(mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    pkha_size_t sizeA = mbedtls_mpi_size(A);
    pkha_size_t sizeB = mbedtls_mpi_size(B);

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    if ((sizeA <= FREESCALE_PKHA_INT_MAX_BYTES) && (sizeB <= FREESCALE_PKHA_INT_MAX_BYTES))
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        pkha_size_t sizeC;
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrB = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrC = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == ptrA) || (NULL == ptrB) || (NULL == ptrC))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        mbedtls_mpi_write_binary(A, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(B, ptrB, sizeB);
        ltc_reverse_array(ptrB, sizeB);

        ret = (int)LTC_PKHA_ModRed(LTC_INSTANCE, ptrA, sizeA, ptrB, sizeB, ptrC, &sizeC, kLTC_PKHA_IntegerArith);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrC, sizeC);
        mbedtls_mpi_read_binary(R, ptrC, sizeC);
        R->s = A->s;

        while (mbedtls_mpi_cmp_int(R, 0) < 0)
            mbedtls_mpi_add_mpi(R, R, B); /* MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( R, R, B ) ); */

        while (mbedtls_mpi_cmp_mpi(R, B) >= 0)
            mbedtls_mpi_sub_mpi(R, R, B); /* MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( R, R, B ) ); cleanup:*/
    cleanup:
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrB)
        {
            mbedtls_free(ptrB);
        }
        if (ptrC)
        {
            mbedtls_free(ptrC);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_mod_mpi_orig(R, A, B);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_MOD_MPI_ALT */

#if defined(MBEDTLS_MPI_EXP_MOD_ALT)

/* Access to original version of mbedtls_mpi_exp_mod function. */
int mbedtls_mpi_exp_mod_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RR );

/*
 * Sliding-window exponentiation: X = A^E mod N  (HAC 14.85)
 */
int mbedtls_mpi_exp_mod(
    mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RR)
{
    int ret;
    pkha_size_t sizeE = mbedtls_mpi_size(E);
    pkha_size_t sizeN = mbedtls_mpi_size(N);

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    if ((sizeE <= FREESCALE_PKHA_INT_MAX_BYTES) && (sizeN <= FREESCALE_PKHA_INT_MAX_BYTES))
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        mbedtls_mpi *AA; // TODO rename etc.

        /*
         * If number is greater than modulus, we must first reduce it due to LTC requirement
         * on modular exponentiaton that it needs number less than modulus.
         * We can take advantage of modular arithmetic rule that: A^B mod C = ( (A mod C)^B ) mod C.
         * So we do (A mod N) first and if the size of A in bytes fits into LTC, it will be done in LTC
         * (here LTC does not give size requirement on A versus N), otherwise it will be done in SW
         * and since the size of N fits into LTC, the result of (A mod N) will also fit into LTC.
         * Then we can do modular exponentiation in LTC.
         */
        if (mbedtls_mpi_cmp_mpi(A, N) >= 0)
        {
            /* A >= N, perform X = (A mod N). */            
            ret = mbedtls_mpi_mod_mpi(X, A, N);

            if (ret != kStatus_Success)
                return (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

            /* Exponenciation will be performed with X. */
            AA = X;
        }
        else
        {
            /* Exponentiation will be performed with original A. */
            AA = (mbedtls_mpi *)A;
        }

        pkha_size_t sizeA = mbedtls_mpi_size(AA);
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrE = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrN = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == ptrA) || (NULL == ptrE) || (NULL == ptrN))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        mbedtls_mpi_write_binary(AA, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(E, ptrE, sizeE);
        ltc_reverse_array(ptrE, sizeE);

        mbedtls_mpi_write_binary(N, ptrN, sizeN);
        ltc_reverse_array(ptrN, sizeN);

        ret = (int)LTC_PKHA_ModExp(LTC_INSTANCE, ptrA, sizeA, ptrN, sizeN, ptrE, sizeE, ptrN, &sizeN,
                                   kLTC_PKHA_IntegerArith, kLTC_PKHA_NormalValue, kLTC_PKHA_TimingEqualized);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrN, sizeN);
        mbedtls_mpi_read_binary(X, ptrN, sizeN);
    cleanup:
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrE)
        {
            mbedtls_free(ptrE);
        }
        if (ptrN)
        {
            mbedtls_free(ptrN);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_exp_mod_orig(X, A, E, N, _RR);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_EXP_MOD_ALT */

#if defined(MBEDTLS_MPI_GCD_ALT)

/* Access to original version of mbedtls_mpi_gcd function. */
int mbedtls_mpi_gcd_orig( mbedtls_mpi *G, const mbedtls_mpi *A, const mbedtls_mpi *B );

/*
 * Greatest common divisor: G = gcd(A, B)  (HAC 14.54)
 */
int mbedtls_mpi_gcd(mbedtls_mpi *G, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
    pkha_size_t sizeA = mbedtls_mpi_size(A);
    pkha_size_t sizeB = mbedtls_mpi_size(B);

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    if ((sizeA <= FREESCALE_PKHA_INT_MAX_BYTES) && (sizeB <= FREESCALE_PKHA_INT_MAX_BYTES))
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        pkha_size_t sizeC;
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrB = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrC = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == ptrA) || (NULL == ptrB) || (NULL == ptrC))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        mbedtls_mpi_write_binary(A, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(B, ptrB, sizeB);
        ltc_reverse_array(ptrB, sizeB);

        if (mbedtls_mpi_cmp_mpi(A, B) >= 0)
        {
            ret = (int)LTC_PKHA_ModRed(LTC_INSTANCE, ptrA, sizeA, ptrB, sizeB, ptrA, &sizeA, kLTC_PKHA_IntegerArith);

            if (ret != kStatus_Success)
                CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);
        }

        ret = (int)LTC_PKHA_GCD(LTC_INSTANCE, ptrA, sizeA, ptrB, sizeB, ptrC, &sizeC, kLTC_PKHA_IntegerArith);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrC, sizeC);
        mbedtls_mpi_read_binary(G, ptrC, sizeC);
    cleanup:
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrB)
        {
            mbedtls_free(ptrB);
        }
        if (ptrC)
        {
            mbedtls_free(ptrC);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_gcd_orig(G, A, B);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_GCD_ALT */

#if defined(MBEDTLS_MPI_INV_MOD_ALT)

/* Access to original version of mbedtls_mpi_inv_mod function. */
int mbedtls_mpi_inv_mod_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N );

/*
 * Modular inverse: X = A^-1 mod N  (HAC 14.61 / 14.64)
 */
int mbedtls_mpi_inv_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N)
{
    pkha_size_t sizeA = mbedtls_mpi_size(A);
    pkha_size_t sizeN = mbedtls_mpi_size(N);

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    if ((sizeA <= FREESCALE_PKHA_INT_MAX_BYTES) && (sizeN <= FREESCALE_PKHA_INT_MAX_BYTES))
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        pkha_size_t sizeC;
        uint8_t *ptrA = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrN = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        uint8_t *ptrC = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if ((NULL == ptrA) || (NULL == ptrN) || (NULL == ptrC))
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        /* N cannot be negative */
        if (N->s < 0 || mbedtls_mpi_cmp_int(N, 0) == 0)
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_BAD_INPUT_DATA);
        }

        mbedtls_mpi_write_binary(A, ptrA, sizeA);
        ltc_reverse_array(ptrA, sizeA);

        mbedtls_mpi_write_binary(N, ptrN, sizeN);
        ltc_reverse_array(ptrN, sizeN);

        if (mbedtls_mpi_cmp_mpi(A, N) >= 0)
        {
            ret = (int)LTC_PKHA_ModRed(LTC_INSTANCE, ptrA, sizeA, ptrN, sizeN, ptrA, &sizeA, kLTC_PKHA_IntegerArith);

            if (ret != kStatus_Success)
                CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);
        }

        ret = (int)LTC_PKHA_ModInv(LTC_INSTANCE, ptrA, sizeA, ptrN, sizeN, ptrC, &sizeC, kLTC_PKHA_IntegerArith);

        if (ret != kStatus_Success)
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

        ltc_reverse_array(ptrC, sizeC);
        mbedtls_mpi_read_binary(X, ptrC, sizeC);
    cleanup:
        if (ptrA)
        {
            mbedtls_free(ptrA);
        }
        if (ptrN)
        {
            mbedtls_free(ptrN);
        }
        if (ptrC)
        {
            mbedtls_free(ptrC);
        }
        return (ret);
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_inv_mod_orig(X, A, N);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_INV_MOD_ALT */

#if defined(MBEDTLS_MPI_IS_PRIME_ALT)

/* Access to original version of mbedtls_mpi_is_prime function. */
int mbedtls_mpi_is_prime_orig( const mbedtls_mpi *X, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/*
 * Pseudo-primality test: small factors, then Miller-Rabin
 */
int mbedtls_mpi_is_prime(const mbedtls_mpi *X, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
    pkha_size_t sizeX = mbedtls_mpi_size(X);

#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    if (sizeX <= FREESCALE_PKHA_INT_MAX_BYTES)
    {
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
        int ret;
        int random;
        bool result = false;
        uint8_t *ptrX = mbedtls_calloc(FREESCALE_PKHA_INT_MAX_BYTES, 1);
        if (NULL == ptrX)
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_ALLOC_FAILED);
        }

        mbedtls_mpi_write_binary(X, ptrX, FREESCALE_PKHA_INT_MAX_BYTES);
        ltc_reverse_array(ptrX, FREESCALE_PKHA_INT_MAX_BYTES);

        // Get the random seed number
        f_rng(p_rng, (unsigned char *)(&random), sizeof(random));

        ret = (int)LTC_PKHA_PrimalityTest(LTC_INSTANCE, (unsigned char *)&random, sizeof(random), (const uint8_t *)"1", 1u,
                                          ptrX, sizeX, &result);

        if (ret != kStatus_Success)
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);
        }

        if (result == false)
        {
            CLEAN_RETURN (MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);
        }
    cleanup:
        if (ptrX)
        {
            mbedtls_free(ptrX);
        }
        return ret;
#if defined(FREESCALE_PKHA_LONG_OPERANDS_ENABLE)
    }
    else
    {
        return mbedtls_mpi_is_prime_orig(X, f_rng, p_rng);
    }
#endif /* FREESCALE_PKHA_LONG_OPERANDS_ENABLE */
}
#endif /* MBEDTLS_MPI_IS_PRIME_ALT */

#endif /* MBEDTLS_BIGNUM_C */

#if defined(MBEDTLS_ECP_C)

#include "mbedtls/ecp.h"

#define LTC_MAX_ECC (512)

/* convert from mbedtls_mpi to LTC integer, as array of bytes of size sz.
 * if mbedtls_mpi has less bytes than sz, add zero bytes at most significant byte positions.
 * This is when for example modulus is 32 bytes (P-256 curve)
 * and mbedtls_mpi has only 31 bytes, we add leading zeroes
 * so that result array has 32 bytes, same as modulus (sz).
 */
#if defined(MBEDTLS_ECP_MUL_COMB_ALT) || defined(MBEDTLS_ECP_ADD_ALT)
static int ltc_get_from_mbedtls_mpi(uint8_t *dst, const mbedtls_mpi *a, size_t sz)
{
    size_t szbin;
    int offset;
    int ret;

    /* check how many bytes are in the mbedtls_mpi */
    szbin = mbedtls_mpi_size(a);

    /* compute offset from dst */
    offset = sz - szbin;
    if (offset < 0)
        offset = 0;
    if (offset > sz)
        offset = sz;

    /* add leading zeroes */
    if (offset)
        memset(dst, 0, offset);

    /* convert mbedtls_mpi to array of bytes */
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(a, dst + offset, szbin));

    /* reverse array for LTC direct use */
    ltc_reverse_array(dst, sz);
cleanup:
    return (ret);
}
#endif /*MBEDTLS_ECP_MUL_COMB_ALT || MBEDTLS_ECP_ADD_ALT */

/*
 * Multiplication using the comb method,
 * for curves in short Weierstrass form
 */
#if defined(MBEDTLS_ECP_MUL_COMB_ALT)
int ecp_mul_comb(mbedtls_ecp_group *grp,
                 mbedtls_ecp_point *R,
                 const mbedtls_mpi *m,
                 const mbedtls_ecp_point *P,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng)
{
    int ret;
    bool is_inf;
    size_t size;
    size_t size_bin;

    ltc_pkha_ecc_point_t A;
    ltc_pkha_ecc_point_t result;

    uint8_t AX[LTC_MAX_ECC / 8] = {0};
    uint8_t AY[LTC_MAX_ECC / 8] = {0};
    uint8_t RX[LTC_MAX_ECC / 8] = {0};
    uint8_t RY[LTC_MAX_ECC / 8] = {0};
    uint8_t E[FREESCALE_PKHA_INT_MAX_BYTES] = {0};
    uint8_t N[LTC_MAX_ECC / 8] = {0};
    uint8_t paramA[LTC_MAX_ECC / 8] = {0};
    uint8_t paramB[LTC_MAX_ECC / 8] = {0};

    A.X = AX;
    A.Y = AY;
    result.X = RX;
    result.Y = RY;
    size = mbedtls_mpi_size(&grp->P);
    if (mbedtls_mpi_size(&P->X) > (LTC_MAX_ECC / 8) || (mbedtls_mpi_get_bit(&grp->N, 0) != 1))
    {
        CLEAN_RETURN (MBEDTLS_ERR_ECP_BAD_INPUT_DATA);
    }

    /* Convert multi precision integers to arrays */
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(A.X, &P->X, size));
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(A.Y, &P->Y, size));
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(paramA, &grp->A, size));
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(paramB, &grp->B, size));

    /* scalar multiplier integer of any size */
    size_bin = mbedtls_mpi_size(m);
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(m, E, size_bin));
    ltc_reverse_array(E, size_bin);

    /* modulus */
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&grp->P, N, size));
    ltc_reverse_array(N, size);

    /* Multiply */
    LTC_PKHA_ECC_PointMul(LTC_INSTANCE, &A, E, size_bin, N, NULL, paramA, paramB, size, kLTC_PKHA_TimingEqualized,
                          kLTC_PKHA_IntegerArith, &result, &is_inf);
    /* Convert result */
    ltc_reverse_array(RX, size);
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&R->X, RX, size));
    ltc_reverse_array(RY, size);
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&R->Y, RY, size));
    /* if the integer multiplier is negative, the computation happens with abs() value
     * and the result (x,y) is changed to (x, -y)
     */
    R->Y.s = m->s;
    mbedtls_mpi_read_string(&R->Z, 10, "1");

cleanup:
    return (ret);
}
#endif /* MBEDTLS_ECP_MUL_COMB_ALT */

/*
 * Curve types: internal for now, might be exposed later
 */
typedef enum
{
    ECP_TYPE_NONE = 0,
    ECP_TYPE_SHORT_WEIERSTRASS, /* y^2 = x^3 + a x + b      */
    ECP_TYPE_MONTGOMERY,        /* y^2 = x^3 + a x^2 + x    */
} ecp_curve_type;
/*
 * Get the type of a curve
 */
static inline ecp_curve_type ecp_get_type(const mbedtls_ecp_group *grp)
{
    if (grp->G.X.p == NULL)
        return (ECP_TYPE_NONE);

    if (grp->G.Y.p == NULL)
        return (ECP_TYPE_MONTGOMERY);
    else
        return (ECP_TYPE_SHORT_WEIERSTRASS);
}

/*
 * Addition: R = P + Q, result's coordinates normalized
 */
#if defined(MBEDTLS_ECP_ADD_ALT)
int ecp_add(const mbedtls_ecp_group *grp, mbedtls_ecp_point *R, const mbedtls_ecp_point *P, const mbedtls_ecp_point *Q)
{
    int ret;
    size_t size;
    ltc_pkha_ecc_point_t A;
    ltc_pkha_ecc_point_t B;
    ltc_pkha_ecc_point_t result;

    uint8_t AX[LTC_MAX_ECC / 8] = {0};
    uint8_t AY[LTC_MAX_ECC / 8] = {0};
    uint8_t BX[LTC_MAX_ECC / 8] = {0};
    uint8_t BY[LTC_MAX_ECC / 8] = {0};
    uint8_t RX[LTC_MAX_ECC / 8] = {0};
    uint8_t RY[LTC_MAX_ECC / 8] = {0};
    uint8_t N[LTC_MAX_ECC / 8] = {0};
    uint8_t paramA[LTC_MAX_ECC / 8] = {0};
    uint8_t paramB[LTC_MAX_ECC / 8] = {0};

    if (ecp_get_type(grp) != ECP_TYPE_SHORT_WEIERSTRASS)
        CLEAN_RETURN (MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE);

    A.X = AX;
    A.Y = AY;
    B.X = BX;
    B.Y = BY;
    result.X = RX;
    result.Y = RY;
    size = mbedtls_mpi_size(&grp->P);
    if (mbedtls_mpi_size(&P->X) > (LTC_MAX_ECC / 8) || (mbedtls_mpi_get_bit(&grp->P, 0) != 1))
    {
        CLEAN_RETURN (MBEDTLS_ERR_ECP_BAD_INPUT_DATA);
    }

    /* Convert multi precision integers to arrays */
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(A.X, &P->X, size));
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(A.Y, &P->Y, size));
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(B.X, &Q->X, size));
    MBEDTLS_MPI_CHK(ltc_get_from_mbedtls_mpi(B.Y, &Q->Y, size));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&grp->P, N, size));
    ltc_reverse_array(N, size);
    /* Multiply */
    LTC_PKHA_ECC_PointAdd(LTC_INSTANCE, &A, &B, N, NULL, paramA, paramB, size, kLTC_PKHA_IntegerArith, &result);
    /* Convert result */
    ltc_reverse_array(RX, size);
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&R->X, RX, size));
    ltc_reverse_array(RY, size);
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&R->Y, RY, size));
    R->X.s = P->X.s;
    R->Y.s = P->Y.s;
    mbedtls_mpi_read_string(&R->Z, 10, "1");

cleanup:
    return (ret);
}
#endif /* MBEDTLS_ECP_ADD_ALT */

#endif /* MBEDTLS_ECP_C */

#endif /* MBEDTLS_FREESCALE_LTC_PKHA */

/******************************************************************************/
/*************************** MD5 **********************************************/
/******************************************************************************/

#if defined(MBEDTLS_MD5_C)

#if defined(MBEDTLS_FREESCALE_MMCAU_MD5)

#include "mbedtls/md5.h"

void mbedtls_md5_process(mbedtls_md5_context *ctx, const unsigned char data[64])
{
    MMCAU_MD5_HashN(data, 1, ctx->state);
}

#endif /* MBEDTLS_FREESCALE_MMCAU_MD5 */

#endif /* MBEDTLS_MD5_C */

/******************************************************************************/
/*************************** SHA1 *********************************************/
/******************************************************************************/

#if defined(MBEDTLS_SHA1_C)

#if defined(MBEDTLS_FREESCALE_LTC_SHA1)
#include "mbedtls/sha1.h"

/* Implementation that should never be optimized out by the compiler */
static void mbedtls_zeroize(void *v, size_t n)
{
    volatile unsigned char *p = v;
    while (n--)
        *p++ = 0;
}

void mbedtls_sha1_init(mbedtls_sha1_context *ctx)
{
    memset(ctx, 0, sizeof(mbedtls_sha1_context));
}

void mbedtls_sha1_free(mbedtls_sha1_context *ctx)
{
    if (ctx == NULL)
        return;

    mbedtls_zeroize(ctx, sizeof(mbedtls_sha1_context));
}

void mbedtls_sha1_clone(mbedtls_sha1_context *dst, const mbedtls_sha1_context *src)
{
    memcpy(dst, src, sizeof(mbedtls_sha1_context));
}

/*
 * SHA-1 context setup
 */
void mbedtls_sha1_starts(mbedtls_sha1_context *ctx)
{
    LTC_HASH_Init(LTC_INSTANCE, ctx, kLTC_Sha1, NULL, 0);
}

void mbedtls_sha1_process(mbedtls_sha1_context *ctx, const unsigned char data[64])
{
    LTC_HASH_Update(ctx, data, 64);
}

/*
 * SHA-1 process buffer
 */
void mbedtls_sha1_update(mbedtls_sha1_context *ctx, const unsigned char *input, size_t ilen)
{
    LTC_HASH_Update(ctx, input, ilen);
}

/*
 * SHA-1 final digest
 */
void mbedtls_sha1_finish(mbedtls_sha1_context *ctx, unsigned char output[20])
{
    LTC_HASH_Finish(ctx, output, 0);
}

#elif defined(MBEDTLS_FREESCALE_MMCAU_SHA1)

#include "mbedtls/sha1.h"

void mbedtls_sha1_process(mbedtls_sha1_context *ctx, const unsigned char data[64])
{
    MMCAU_SHA1_HashN(data, 1, ctx->state);
}

#elif defined(MBEDTLS_FREESCALE_LPC_SHA1)
#include "mbedtls/sha1.h"

/* Implementation that should never be optimized out by the compiler */
static void mbedtls_zeroize(void *v, size_t n)
{
    volatile unsigned char *p = v;
    while (n--)
        *p++ = 0;
}

void mbedtls_sha1_init(mbedtls_sha1_context *ctx)
{
    memset(ctx, 0, sizeof(mbedtls_sha1_context));
}

void mbedtls_sha1_free(mbedtls_sha1_context *ctx)
{
    if (ctx == NULL)
        return;

    mbedtls_zeroize(ctx, sizeof(mbedtls_sha1_context));
}

void mbedtls_sha1_clone(mbedtls_sha1_context *dst, const mbedtls_sha1_context *src)
{
    memcpy(dst, src, sizeof(mbedtls_sha1_context));
}

/*
 * SHA-1 context setup
 */
void mbedtls_sha1_starts(mbedtls_sha1_context *ctx)
{
    SHA_Init(SHA_INSTANCE, ctx, kSHA_Sha1);
}

void mbedtls_sha1_process(mbedtls_sha1_context *ctx, const unsigned char data[64])
{
    SHA_Update(SHA_INSTANCE, ctx, data, 64);
}

/*
 * SHA-1 process buffer
 */
void mbedtls_sha1_update(mbedtls_sha1_context *ctx, const unsigned char *input, size_t ilen)
{
    SHA_Update(SHA_INSTANCE, ctx, input, ilen);
}

/*
 * SHA-1 final digest
 */
void mbedtls_sha1_finish(mbedtls_sha1_context *ctx, unsigned char output[20])
{
    size_t outputSize = 20;
    SHA_Finish(SHA_INSTANCE, ctx, output, &outputSize);
}

#endif /* MBEDTLS_FREESCALE_LPC_SHA1 */
#endif /* MBEDTLS_SHA1_C */

/******************************************************************************/
/*************************** SHA256********************************************/
/******************************************************************************/

#if defined(MBEDTLS_SHA256_C)

#if defined(MBEDTLS_FREESCALE_LTC_SHA256)
#include "mbedtls/sha256.h"

/* Implementation that should never be optimized out by the compiler */
static void mbedtls_zeroize_sha256(void *v, size_t n)
{
    volatile unsigned char *p = v;
    while (n--)
        *p++ = 0;
}

void mbedtls_sha256_init(mbedtls_sha256_context *ctx)
{
    memset(ctx, 0, sizeof(mbedtls_sha256_context));
}

void mbedtls_sha256_free(mbedtls_sha256_context *ctx)
{
    if (ctx == NULL)
        return;

    mbedtls_zeroize_sha256(ctx, sizeof(mbedtls_sha256_context));
}

void mbedtls_sha256_clone(mbedtls_sha256_context *dst, const mbedtls_sha256_context *src)
{
    memcpy(dst, src, sizeof(*dst));
}

/*
 * SHA-256 context setup
 */
void mbedtls_sha256_starts(mbedtls_sha256_context *ctx, int is224)
{
    if (is224)
    {
        LTC_HASH_Init(LTC_INSTANCE, ctx, kLTC_Sha224, NULL, 0);
    }
    else
    {
        LTC_HASH_Init(LTC_INSTANCE, ctx, kLTC_Sha256, NULL, 0);
    }
}

void mbedtls_sha256_process(mbedtls_sha256_context *ctx, const unsigned char data[64])
{
    LTC_HASH_Update(ctx, data, 64);
}

/*
 * SHA-256 process buffer
 */
void mbedtls_sha256_update(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen)
{
    LTC_HASH_Update(ctx, input, ilen);
}

/*
 * SHA-256 final digest
 */
void mbedtls_sha256_finish(mbedtls_sha256_context *ctx, unsigned char output[32])
{
    LTC_HASH_Finish(ctx, output, 0);
}

#elif defined(MBEDTLS_FREESCALE_MMCAU_SHA256)

#include "mbedtls/sha256.h"

void mbedtls_sha256_process(mbedtls_sha256_context *ctx, const unsigned char data[64])
{
    MMCAU_SHA256_HashN(data, 1, ctx->state);
}

#elif defined(MBEDTLS_FREESCALE_CAU3_SHA256)

#include "mbedtls/sha256.h"

void mbedtls_sha256_process(mbedtls_sha256_context *ctx, const unsigned char data[64])
{
    CAU3_WRAP_SHA256_Update(data, 1, ctx->state, MBEDTLS_CAU3_COMPLETION_SIGNAL);
}

#elif defined(MBEDTLS_FREESCALE_LPC_SHA256)
#include "mbedtls/sha256.h"

/* Implementation that should never be optimized out by the compiler */
static void mbedtls_zeroize_sha256(void *v, size_t n)
{
    volatile unsigned char *p = v;
    while (n--)
        *p++ = 0;
}

void mbedtls_sha256_init(mbedtls_sha256_context *ctx)
{
    memset(ctx, 0, sizeof(mbedtls_sha256_context));
}

void mbedtls_sha256_free(mbedtls_sha256_context *ctx)
{
    if (ctx == NULL)
        return;

    mbedtls_zeroize_sha256(ctx, sizeof(mbedtls_sha256_context));
}

void mbedtls_sha256_clone(mbedtls_sha256_context *dst, const mbedtls_sha256_context *src)
{
    memcpy(dst, src, sizeof(*dst));
}

/*
 * SHA-256 context setup
 */
void mbedtls_sha256_starts(mbedtls_sha256_context *ctx, int is224)
{
    if (!is224) /* SHA-224 not supported */
    {
        SHA_Init(SHA_INSTANCE, ctx, kSHA_Sha256);
    }
}

void mbedtls_sha256_process(mbedtls_sha256_context *ctx, const unsigned char data[64])
{
    SHA_Update(SHA_INSTANCE, ctx, data, 64);
}

/*
 * SHA-256 process buffer
 */
void mbedtls_sha256_update(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen)
{
    SHA_Update(SHA_INSTANCE, ctx, input, ilen);
}

/*
 * SHA-256 final digest
 */
void mbedtls_sha256_finish(mbedtls_sha256_context *ctx, unsigned char output[32])
{
    size_t outputSize = 32;
    SHA_Finish(SHA_INSTANCE, ctx, output, &outputSize);
}
#endif /* MBEDTLS_FREESCALE_LPC_SHA256 */
#endif /* MBEDTLS_SHA1_C */

/* Entropy poll callback for a hardware source */
#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)

#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
#include "fsl_trng.h"
#elif defined(FSL_FEATURE_SOC_RNG_COUNT) && (FSL_FEATURE_SOC_RNG_COUNT > 0)
#include "fsl_rnga.h"
#elif defined(FSL_FEATURE_SOC_LPC_RNG_COUNT) && (FSL_FEATURE_SOC_LPC_RNG_COUNT > 0)
#include "fsl_rng.h"
#endif

int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
    status_t result = kStatus_Success;

#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
#ifndef TRNG0
#define TRNG0 TRNG
#endif
    result = TRNG_GetRandomData(TRNG0, output, len);
#elif defined(FSL_FEATURE_SOC_RNG_COUNT) && (FSL_FEATURE_SOC_RNG_COUNT > 0)
    result = RNGA_GetRandomData(RNG, (void *)output, len);
#elif defined(FSL_FEATURE_SOC_LPC_RNG_COUNT) && (FSL_FEATURE_SOC_LPC_RNG_COUNT > 0)
    uint32_t rn;
    size_t length;
    int i;

    length = len;

    while (length > 0)
    {
        rn = RNG_GetRandomData();

        if (length >= sizeof(uint32_t))
        {
            memcpy(output, &rn, sizeof(uint32_t));
            length -= sizeof(uint32_t);
            output += sizeof(uint32_t);
        }
        else
        {
            memcpy(output, &rn, length);
            output += length;
            len = 0U;
        }

        /* Discard next 32 random words for better entropy */
        for (i = 0; i < 32; i++)
        {
            RNG_GetRandomData();
        }
    }

    result = kStatus_Success;
#endif
    if (result == kStatus_Success)
    {
        *olen = len;
        return 0;
    }
    else
    {
        return result;
    }
}

#endif

/******************************************************************************/
/*************************** FreeRTOS ********************************************/
/******************************************************************************/
#if USE_RTOS && defined(FSL_RTOS_FREE_RTOS)
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>

/*---------HEAP_3 calloc --------------------------------------------------*/

void *pvPortCalloc(size_t num, size_t size)
{
    void *pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = calloc(num, size);
        traceMALLOC(pvReturn, xWantedSize);
    }
    (void)xTaskResumeAll();

#if (configUSE_MALLOC_FAILED_HOOK == 1)
    {
        if (pvReturn == NULL)
        {
            extern void vApplicationMallocFailedHook(void);
            vApplicationMallocFailedHook();
        }
    }
#endif

    return pvReturn;
}
#endif /* USE_RTOS && defined(FSL_RTOS_FREE_RTOS)*/
