/**
 * \file rsa.h
 *
 * \brief The RSA public-key cryptosystem
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
#ifndef MBEDTLS_RSA_H
#define MBEDTLS_RSA_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "bignum.h"
#include "md.h"

#if defined(MBEDTLS_THREADING_C)
#include "threading.h"
#endif

/*
 * RSA Error codes
 */
#define MBEDTLS_ERR_RSA_BAD_INPUT_DATA                    -0x4080  /**< Bad input parameters to function. */
#define MBEDTLS_ERR_RSA_INVALID_PADDING                   -0x4100  /**< Input data contains invalid padding and is rejected. */
#define MBEDTLS_ERR_RSA_KEY_GEN_FAILED                    -0x4180  /**< Something failed during generation of a key. */
#define MBEDTLS_ERR_RSA_KEY_CHECK_FAILED                  -0x4200  /**< Key failed to pass the library's validity check. */
#define MBEDTLS_ERR_RSA_PUBLIC_FAILED                     -0x4280  /**< The public key operation failed. */
#define MBEDTLS_ERR_RSA_PRIVATE_FAILED                    -0x4300  /**< The private key operation failed. */
#define MBEDTLS_ERR_RSA_VERIFY_FAILED                     -0x4380  /**< The PKCS#1 verification failed. */
#define MBEDTLS_ERR_RSA_OUTPUT_TOO_LARGE                  -0x4400  /**< The output buffer for decryption is not large enough. */
#define MBEDTLS_ERR_RSA_RNG_FAILED                        -0x4480  /**< The random generator failed to generate non-zeros. */

/*
 * RSA constants
 */
#define MBEDTLS_RSA_PUBLIC      0
#define MBEDTLS_RSA_PRIVATE     1

#define MBEDTLS_RSA_PKCS_V15    0
#define MBEDTLS_RSA_PKCS_V21    1

#define MBEDTLS_RSA_SIGN        1
#define MBEDTLS_RSA_CRYPT       2

#define MBEDTLS_RSA_SALT_LEN_ANY    -1

/*
 * Example RSA keys, for selftest and benchmark purposes
 */

#define RSA_PRIVATE_KEY_1024                                            \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"MIICWwIBAAKBgQDA0UszjREl+JklUyevaN8fb0Gp13Dzb4pY3MCoJK15BWoeoUFA\r\n"  \
"IVvuI0C8bRm/i1OO4BN9tSRrRjW+S89YbYy1C73PUgKZSejjnEFA4chcSOKOhZlM\r\n"  \
"6K7+Pcrcx+sdiDu1DheODMiSFhoxt+H6IUvBEGkI5AWFu5MDP7wlU/AZfQIDAQAB\r\n"  \
"AoGAU6o9HEhIuZYuNZDodmdl8YjgECdIfojWmgpnmk4X65xa2KGV45LWBfXMADbC\r\n"  \
"5mc5QZSfQHuaKuYTKdhRRwh59c9VPwYhN8hdgFzbJS9KfJTDuKhsZrdomHRN2fHK\r\n"  \
"Jn5MrbVCeZPbYS0M1PzVgEz/BGRp4Ik3RAxTlt+XBtunHA0CQQDz6Gor3gFTdCWM\r\n"  \
"XtrWEfMW+arWvPUBlOhw3U0YgpWqdea36YeXd9DEIIKn9bQU4g0SjkpO7jd/ccBm\r\n"  \
"zM89dfjXAkEAymB11gLDd0JZhUCk155uBucaZeez/VNucEgvjWDphRInqJg+2JW2\r\n"  \
"gSgXNFeSTY9iKlLdBL1zYdywOXM3fd6RywJAIqFYGbxeodO21RROq+BGjHeMWwrf\r\n"  \
"Godi7Utue9FmoJo21NvyZX4chQw8oM5Q8DocMwtC36wQ8yZac/4WWpqaZwJAbMIy\r\n"  \
"EXUivrC1k1sOO6I01xjTovhGTlnL/COPCpeOZ6k+DujivVqX3glBjyuQwIXR55To\r\n"  \
"mmeF3o3PVtCIfehiyQJATsyRPJ1FOYIlIywMSaGHqSpVoebWbDQ6BhYOOvmx5/Zd\r\n"  \
"Tun1+7WrtPoxM+LQumgPEdx7VDq2L4SetYB/Md1OSQ==\r\n"                      \
"-----END RSA PRIVATE KEY-----\r\n"

#define RSA_PRIVATE_KEY_2048                                            \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"MIIEogIBAAKCAQEA2dwVr+IMGEtA2/MCP6fA5eb/6B18Bq6e7gw8brNPkm3E6LyR\r\n"  \
"4DnMJVxZmw3bPDKBDoKzfntkMESi/Yw5UopLtVfjGfWeQWPClqffLZBsZ60BRAsg\r\n"  \
"/g+ID5tgzxSuxzftypK59uexOVCAm7hCKZHGO3DbI7bLY27j7VAgEP7d/yuaz5Fx\r\n"  \
"Kl/vu7shqrBoz6ABJVJD3KC8nUiMRUCXRINmxbyUUjA4DnicZv6+xrGKr36r6M8h\r\n"  \
"VYLa5msKc8WzbnBWzpUsrpb4/r7ML+qp92gdSfVJ8/bLiU7h2C7faDA59uaqrFK9\r\n"  \
"xmDdx7FaWhGQs3LWW6w1UNgkPS0FDYUslpsnsQIDAQABAoIBAC7IJNwM5V3+IuJY\r\n"  \
"T35Nzo1PyloUosJokvY5KGz5Ejg2XBdCDu0gXCcVqqQyGIbXrYDpLhQV+RCoXHun\r\n"  \
"tdN0oQdC5SB47s/J1Uo2qCUHo0+sBd6PqTkFKsl3KxWssk9TQjvCwC412IefMs69\r\n"  \
"hW+ZvwCanmQP56LleApIr2oW4KLfW8Ry/QfZlua+dizctdN7+H1mWwgZQTY9T27J\r\n"  \
"6RtGRA5NVkKVPzIHVJfdpKoO7xGg1g06aEbPB/VmGvZaaFWWnaf7uRvFjLZecBLu\r\n"  \
"QSx2DA/GDjirlDYj99PJb7DtB4xRtKzsyw0o+xapC8w6OtIl/3xFt9moCu2jGrsx\r\n"  \
"vpjHdfECgYEA7fSACRseIs9gAIVX8wq6gayTpA47DHYWAD6IQfIj35SJ+AgsvbFF\r\n"  \
"4AmrwDhcJVPmDy1N4nLBfyGAMt/2CfiYkdkW6QFX/ULRMMBL/G7kWV8hYQDICB2g\r\n"  \
"xaMRN1lPCmFq6BkSWjwIYTnYDFBDWVm1GVT8TMtJoM8Erej9qC0PeFUCgYEA6mF3\r\n"  \
"bigO3t8f5sig+XepaftEUbkJMzo72TVRnIR2ycdR2ihelPQ+25g9dwV0ZA5XXhBS\r\n"  \
"DKOABWjMM739Mwmy9v26Dlmu9R01zHQktMvtEAyfz7lk2NF0aMuj8285OJUBf9bz\r\n"  \
"Cq3MjtMCD+4CZ6iaEqCdUKOuxfpx5cWVJV+qve0CgYBhD1YaYMFOGaBjFgDl1f51\r\n"  \
"Xltqk5NqZdBbkSYrIAWZ8RDF5y+4wFJsLAWuhk6vuyUgE66tK3nZzWRpXAkT0B8L\r\n"  \
"fq1lpXKqj1KcvBNCiEkEW1VWJ+dvyAYIF5eyJ++hoFLnETL3M32HivyhKSwPihPg\r\n"  \
"nVW8TT9fJJIYDe1JZ/fjcQKBgHJfv7UsrR0LSvkG3K8AOtbx+8PZhOjPuRbk0v+L\r\n"  \
"EKCkuIe5/XW4vtfQMeZb7hFJgk7vrepm+vkoy8VQKDf4urGW3W1VTHBmobM01hi4\r\n"  \
"DuYvEul+Mf0wMRtWjJolo4m+BO5KiW2jpFfqFm6JmfjVqOIAKOSKC6am8V/MDF0h\r\n"  \
"kyN9AoGAT9oOiEXMolbkDZw/QCaBiRoAGlGlNYUkJ+58U6OjIZLISw6aFv+Y2uE0\r\n"  \
"mEImItjuYZtSYKblWikp6ldPoKlt9bwEFe3c6IZ8kJ3+xyEyAGrvjXjEY7PzP6dp\r\n"  \
"Ajbjp9X9uocEBv9W/KsBLdQ7yizcL/toHwdBO4vQqmqTvAc5IIw=\r\n"              \
"-----END RSA PRIVATE KEY-----\r\n"

#define RSA_PRIVATE_KEY_4096                                            \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"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\r\n"  \
"-----END RSA PRIVATE KEY-----\r\n" 

/*
 * The above constants may be used even if the RSA module is compile out,
 * eg for alternative (PKCS#11) RSA implemenations in the PK layers.
 */
#if defined(MBEDTLS_RSA_C)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          RSA context structure
 */
typedef struct
{
    int ver;                    /*!<  always 0          */
    size_t len;                 /*!<  size(N) in chars  */

    mbedtls_mpi N;                      /*!<  public modulus    */
    mbedtls_mpi E;                      /*!<  public exponent   */

    mbedtls_mpi D;                      /*!<  private exponent  */
    mbedtls_mpi P;                      /*!<  1st prime factor  */
    mbedtls_mpi Q;                      /*!<  2nd prime factor  */
    mbedtls_mpi DP;                     /*!<  D % (P - 1)       */
    mbedtls_mpi DQ;                     /*!<  D % (Q - 1)       */
    mbedtls_mpi QP;                     /*!<  1 / (Q % P)       */

    mbedtls_mpi RN;                     /*!<  cached R^2 mod N  */
    mbedtls_mpi RP;                     /*!<  cached R^2 mod P  */
    mbedtls_mpi RQ;                     /*!<  cached R^2 mod Q  */

    mbedtls_mpi Vi;                     /*!<  cached blinding value     */
    mbedtls_mpi Vf;                     /*!<  cached un-blinding value  */

    int padding;                /*!<  MBEDTLS_RSA_PKCS_V15 for 1.5 padding and
                                      RSA_PKCS_v21 for OAEP/PSS         */
    int hash_id;                /*!<  Hash identifier of mbedtls_md_type_t as
                                      specified in the mbedtls_md.h header file
                                      for the EME-OAEP and EMSA-PSS
                                      encoding                          */
#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t mutex;    /*!<  Thread-safety mutex       */
#endif
}
mbedtls_rsa_context;

/**
 * \brief          Initialize an RSA context
 *
 *                 Note: Set padding to MBEDTLS_RSA_PKCS_V21 for the RSAES-OAEP
 *                 encryption scheme and the RSASSA-PSS signature scheme.
 *
 * \param ctx      RSA context to be initialized
 * \param padding  MBEDTLS_RSA_PKCS_V15 or MBEDTLS_RSA_PKCS_V21
 * \param hash_id  MBEDTLS_RSA_PKCS_V21 hash identifier
 *
 * \note           The hash_id parameter is actually ignored
 *                 when using MBEDTLS_RSA_PKCS_V15 padding.
 *
 * \note           Choice of padding mode is strictly enforced for private key
 *                 operations, since there might be security concerns in
 *                 mixing padding modes. For public key operations it's merely
 *                 a default value, which can be overriden by calling specific
 *                 rsa_rsaes_xxx or rsa_rsassa_xxx functions.
 *
 * \note           The chosen hash is always used for OEAP encryption.
 *                 For PSS signatures, it's always used for making signatures,
 *                 but can be overriden (and always is, if set to
 *                 MBEDTLS_MD_NONE) for verifying them.
 */
void mbedtls_rsa_init( mbedtls_rsa_context *ctx,
               int padding,
               int hash_id);

/**
 * \brief          Set padding for an already initialized RSA context
 *                 See \c mbedtls_rsa_init() for details.
 *
 * \param ctx      RSA context to be set
 * \param padding  MBEDTLS_RSA_PKCS_V15 or MBEDTLS_RSA_PKCS_V21
 * \param hash_id  MBEDTLS_RSA_PKCS_V21 hash identifier
 */
void mbedtls_rsa_set_padding( mbedtls_rsa_context *ctx, int padding, int hash_id);

/**
 * \brief          Generate an RSA keypair
 *
 * \param ctx      RSA context that will hold the key
 * \param f_rng    RNG function
 * \param p_rng    RNG parameter
 * \param nbits    size of the public key in bits
 * \param exponent public exponent (e.g., 65537)
 *
 * \note           mbedtls_rsa_init() must be called beforehand to setup
 *                 the RSA context.
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 */
int mbedtls_rsa_gen_key( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 unsigned int nbits, int exponent );

/**
 * \brief          Check a public RSA key
 *
 * \param ctx      RSA context to be checked
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 */
int mbedtls_rsa_check_pubkey( const mbedtls_rsa_context *ctx );

/**
 * \brief          Check a private RSA key
 *
 * \param ctx      RSA context to be checked
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 */
int mbedtls_rsa_check_privkey( const mbedtls_rsa_context *ctx );

/**
 * \brief          Check a public-private RSA key pair.
 *                 Check each of the contexts, and make sure they match.
 *
 * \param pub      RSA context holding the public key
 * \param prv      RSA context holding the private key
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 */
int mbedtls_rsa_check_pub_priv( const mbedtls_rsa_context *pub, const mbedtls_rsa_context *prv );

/**
 * \brief          Do an RSA public key operation
 *
 * \param ctx      RSA context
 * \param input    input buffer
 * \param output   output buffer
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           This function does NOT take care of message
 *                 padding. Also, be sure to set input[0] = 0 or assure that
 *                 input is smaller than N.
 *
 * \note           The input and output buffers must be large
 *                 enough (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_public( mbedtls_rsa_context *ctx,
                const unsigned char *input,
                unsigned char *output );

/**
 * \brief          Do an RSA private key operation
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Needed for blinding)
 * \param p_rng    RNG parameter
 * \param input    input buffer
 * \param output   output buffer
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The input and output buffers must be large
 *                 enough (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_private( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 const unsigned char *input,
                 unsigned char *output );

/**
 * \brief          Generic wrapper to perform a PKCS#1 encryption using the
 *                 mode from the context. Add the message padding, then do an
 *                 RSA operation.
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Needed for padding and PKCS#1 v2.1 encoding
 *                               and MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param ilen     contains the plaintext length
 * \param input    buffer holding the data to be encrypted
 * \param output   buffer that will hold the ciphertext
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_pkcs1_encrypt( mbedtls_rsa_context *ctx,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng,
                       int mode, size_t ilen,
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief          Perform a PKCS#1 v1.5 encryption (RSAES-PKCS1-v1_5-ENCRYPT)
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Needed for padding and MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param ilen     contains the plaintext length
 * \param input    buffer holding the data to be encrypted
 * \param output   buffer that will hold the ciphertext
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_rsaes_pkcs1_v15_encrypt( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode, size_t ilen,
                                 const unsigned char *input,
                                 unsigned char *output );

/**
 * \brief          Perform a PKCS#1 v2.1 OAEP encryption (RSAES-OAEP-ENCRYPT)
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Needed for padding and PKCS#1 v2.1 encoding
 *                               and MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param label    buffer holding the custom label to use
 * \param label_len contains the label length
 * \param ilen     contains the plaintext length
 * \param input    buffer holding the data to be encrypted
 * \param output   buffer that will hold the ciphertext
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_rsaes_oaep_encrypt( mbedtls_rsa_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng,
                            int mode,
                            const unsigned char *label, size_t label_len,
                            size_t ilen,
                            const unsigned char *input,
                            unsigned char *output );

/**
 * \brief          Generic wrapper to perform a PKCS#1 decryption using the
 *                 mode from the context. Do an RSA operation, then remove
 *                 the message padding
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param olen     will contain the plaintext length
 * \param input    buffer holding the encrypted data
 * \param output   buffer that will hold the plaintext
 * \param output_max_len    maximum length of the output buffer
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used) otherwise
 *                 an error is thrown.
 */
int mbedtls_rsa_pkcs1_decrypt( mbedtls_rsa_context *ctx,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng,
                       int mode, size_t *olen,
                       const unsigned char *input,
                       unsigned char *output,
                       size_t output_max_len );

/**
 * \brief          Perform a PKCS#1 v1.5 decryption (RSAES-PKCS1-v1_5-DECRYPT)
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param olen     will contain the plaintext length
 * \param input    buffer holding the encrypted data
 * \param output   buffer that will hold the plaintext
 * \param output_max_len    maximum length of the output buffer
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used) otherwise
 *                 an error is thrown.
 */
int mbedtls_rsa_rsaes_pkcs1_v15_decrypt( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode, size_t *olen,
                                 const unsigned char *input,
                                 unsigned char *output,
                                 size_t output_max_len );

/**
 * \brief          Perform a PKCS#1 v2.1 OAEP decryption (RSAES-OAEP-DECRYPT)
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param label    buffer holding the custom label to use
 * \param label_len contains the label length
 * \param olen     will contain the plaintext length
 * \param input    buffer holding the encrypted data
 * \param output   buffer that will hold the plaintext
 * \param output_max_len    maximum length of the output buffer
 *
 * \return         0 if successful, or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used) otherwise
 *                 an error is thrown.
 */
int mbedtls_rsa_rsaes_oaep_decrypt( mbedtls_rsa_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng,
                            int mode,
                            const unsigned char *label, size_t label_len,
                            size_t *olen,
                            const unsigned char *input,
                            unsigned char *output,
                            size_t output_max_len );

/**
 * \brief          Generic wrapper to perform a PKCS#1 signature using the
 *                 mode from the context. Do a private RSA operation to sign
 *                 a message digest
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Needed for PKCS#1 v2.1 encoding and for
 *                               MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer that will hold the ciphertext
 *
 * \return         0 if the signing operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 *
 * \note           In case of PKCS#1 v2.1 encoding, see comments on
 * \note           \c mbedtls_rsa_rsassa_pss_sign() for details on md_alg and hash_id.
 */
int mbedtls_rsa_pkcs1_sign( mbedtls_rsa_context *ctx,
                    int (*f_rng)(void *, unsigned char *, size_t),
                    void *p_rng,
                    int mode,
                    mbedtls_md_type_t md_alg,
                    unsigned int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig );

/**
 * \brief          Perform a PKCS#1 v1.5 signature (RSASSA-PKCS1-v1_5-SIGN)
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer that will hold the ciphertext
 *
 * \return         0 if the signing operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_rsassa_pkcs1_v15_sign( mbedtls_rsa_context *ctx,
                               int (*f_rng)(void *, unsigned char *, size_t),
                               void *p_rng,
                               int mode,
                               mbedtls_md_type_t md_alg,
                               unsigned int hashlen,
                               const unsigned char *hash,
                               unsigned char *sig );

/**
 * \brief          Perform a PKCS#1 v2.1 PSS signature (RSASSA-PSS-SIGN)
 *
 * \param ctx      RSA context
 * \param f_rng    RNG function (Needed for PKCS#1 v2.1 encoding and for
 *                               MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer that will hold the ciphertext
 *
 * \return         0 if the signing operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 *
 * \note           The hash_id in the RSA context is the one used for the
 *                 encoding. md_alg in the function call is the type of hash
 *                 that is encoded. According to RFC 3447 it is advised to
 *                 keep both hashes the same.
 */
int mbedtls_rsa_rsassa_pss_sign( mbedtls_rsa_context *ctx,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng,
                         int mode,
                         mbedtls_md_type_t md_alg,
                         unsigned int hashlen,
                         const unsigned char *hash,
                         unsigned char *sig );

/**
 * \brief          Generic wrapper to perform a PKCS#1 verification using the
 *                 mode from the context. Do a public RSA operation and check
 *                 the message digest
 *
 * \param ctx      points to an RSA public key
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer holding the ciphertext
 *
 * \return         0 if the verify operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 *
 * \note           In case of PKCS#1 v2.1 encoding, see comments on
 *                 \c mbedtls_rsa_rsassa_pss_verify() about md_alg and hash_id.
 */
int mbedtls_rsa_pkcs1_verify( mbedtls_rsa_context *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng,
                      int mode,
                      mbedtls_md_type_t md_alg,
                      unsigned int hashlen,
                      const unsigned char *hash,
                      const unsigned char *sig );

/**
 * \brief          Perform a PKCS#1 v1.5 verification (RSASSA-PKCS1-v1_5-VERIFY)
 *
 * \param ctx      points to an RSA public key
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer holding the ciphertext
 *
 * \return         0 if the verify operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int mbedtls_rsa_rsassa_pkcs1_v15_verify( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode,
                                 mbedtls_md_type_t md_alg,
                                 unsigned int hashlen,
                                 const unsigned char *hash,
                                 const unsigned char *sig );

/**
 * \brief          Perform a PKCS#1 v2.1 PSS verification (RSASSA-PSS-VERIFY)
 *                 (This is the "simple" version.)
 *
 * \param ctx      points to an RSA public key
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param sig      buffer holding the ciphertext
 *
 * \return         0 if the verify operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 *
 * \note           The hash_id in the RSA context is the one used for the
 *                 verification. md_alg in the function call is the type of
 *                 hash that is verified. According to RFC 3447 it is advised to
 *                 keep both hashes the same. If hash_id in the RSA context is
 *                 unset, the md_alg from the function call is used.
 */
int mbedtls_rsa_rsassa_pss_verify( mbedtls_rsa_context *ctx,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng,
                           int mode,
                           mbedtls_md_type_t md_alg,
                           unsigned int hashlen,
                           const unsigned char *hash,
                           const unsigned char *sig );

/**
 * \brief          Perform a PKCS#1 v2.1 PSS verification (RSASSA-PSS-VERIFY)
 *                 (This is the version with "full" options.)
 *
 * \param ctx      points to an RSA public key
 * \param f_rng    RNG function (Only needed for MBEDTLS_RSA_PRIVATE)
 * \param p_rng    RNG parameter
 * \param mode     MBEDTLS_RSA_PUBLIC or MBEDTLS_RSA_PRIVATE
 * \param md_alg   a MBEDTLS_MD_XXX (use MBEDTLS_MD_NONE for signing raw data)
 * \param hashlen  message digest length (for MBEDTLS_MD_NONE only)
 * \param hash     buffer holding the message digest
 * \param mgf1_hash_id message digest used for mask generation
 * \param expected_salt_len Length of the salt used in padding, use
 *                 MBEDTLS_RSA_SALT_LEN_ANY to accept any salt length
 * \param sig      buffer holding the ciphertext
 *
 * \return         0 if the verify operation was successful,
 *                 or an MBEDTLS_ERR_RSA_XXX error code
 *
 * \note           The "sig" buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 *
 * \note           The hash_id in the RSA context is ignored.
 */
int mbedtls_rsa_rsassa_pss_verify_ext( mbedtls_rsa_context *ctx,
                               int (*f_rng)(void *, unsigned char *, size_t),
                               void *p_rng,
                               int mode,
                               mbedtls_md_type_t md_alg,
                               unsigned int hashlen,
                               const unsigned char *hash,
                               mbedtls_md_type_t mgf1_hash_id,
                               int expected_salt_len,
                               const unsigned char *sig );

/**
 * \brief          Copy the components of an RSA context
 *
 * \param dst      Destination context
 * \param src      Source context
 *
 * \return         0 on success,
 *                 MBEDTLS_ERR_MPI_ALLOC_FAILED on memory allocation failure
 */
int mbedtls_rsa_copy( mbedtls_rsa_context *dst, const mbedtls_rsa_context *src );

/**
 * \brief          Free the components of an RSA key
 *
 * \param ctx      RSA Context to free
 */
void mbedtls_rsa_free( mbedtls_rsa_context *ctx );

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int mbedtls_rsa_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_RSA_C */

#endif /* rsa.h */
