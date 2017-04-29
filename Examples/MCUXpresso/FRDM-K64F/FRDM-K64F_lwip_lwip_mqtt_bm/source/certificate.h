/*
 * certificate.h
 *
 *  Created on: 19.04.2017
 *      Author: Erich Styger
 */

#ifndef CERTIFICATE_H_
#define CERTIFICATE_H_

#include <stddef.h> /* for size_t */

/* own local mosquitto server certificate */
extern const char mbedtls_m2mqtt_srv_crt[];
extern const size_t mbedtls_m2mqtt_srv_crt_len;

/* mosquitto test server certificate */
extern const char mbedtls_mosquitto_test_ca_crt[];
extern const size_t mbedtls_mosquitto_test_ca_crt_len;

/* Azure server certificate */
extern const char mbedtls_azure_ca_crt[];
extern const size_t mbedtls_azure_ca_crt_len;

#endif /* CERTIFICATE_H_ */
