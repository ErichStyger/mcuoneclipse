/*
 * certificate.h
 *
 *  Created on: 19.04.2017
 *      Author: Erich Styger
 */

#ifndef CERTIFICATE_H_
#define CERTIFICATE_H_

#include <stddef.h> /* for size_t */

extern const char mbedtls_m2mqtt_srv_crt[];
extern const size_t mbedtls_m2mqtt_srv_crt_len;

extern const char mbedtls_mosquitto_test_ca_crt[];
extern const size_t mbedtls_mosquitto_test_ca_crt_len;

#endif /* CERTIFICATE_H_ */
