/*
 * certificate.c
 *
 *  Created on: 19.04.2017
 *      Author: Erich Styger Local
 */

#include "certificate.h"

/* m2mqtt_ca.crt: see
 * https://mcuoneclipse.com/2017/04/14/enable-secure-communication-with-tls-and-the-mosquitto-broker/
 */

#define M2MQTT_CA_CRT_RSA                                                 \
"-----BEGIN CERTIFICATE-----\r\n"                                         \
"MIIDejCCAmKgAwIBAgIJAIQ2QFZN83w2MA0GCSqGSIb3DQEBCwUAMFIxCzAJBgNV\r\n"    \
"BAYTAkNIMRQwEgYDVQQIDAtTd2l0emVybGFuZDEQMA4GA1UEBwwHTHVjZXJuZTEN\r\n"    \
"MAsGA1UECgwESFNMVTEMMAoGA1UECwwDVCZBMB4XDTE3MDQyMzA2NDAxMFoXDTI3\r\n"    \
"MDQyMTA2NDAxMFowUjELMAkGA1UEBhMCQ0gxFDASBgNVBAgMC1N3aXR6ZXJsYW5k\r\n"    \
"MRAwDgYDVQQHDAdMdWNlcm5lMQ0wCwYDVQQKDARIU0xVMQwwCgYDVQQLDANUJkEw\r\n"    \
"ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDptqaQ2IuY26JRH6eJH//Z\r\n"    \
"UUvBY054oJNI91uAMUR0Bzynu+G/VWtYfSquVgayndoEblSV2XTqpBC+CfktP59O\r\n"    \
"6vjpKA5rCo7doe0cofk1M5l8+PNSu0PRpLi0MvCDJGILKuAtJcWIPhKdHCs1rain\r\n"    \
"ywuw3ATA0xrt5epgo8XBejUP7MQXD4s7TZaKjEsXTH4OXGMu2bYqdUVGpfQJFqqU\r\n"    \
"/Iv0UIfOHYomkf729AmR2cSIW9Z4DGLkHmuVZyhkV1XH5qpKQkqCr+WpDL3mtfyb\r\n"    \
"UWe3wc0cwwa85zjn+YvbQgmXF1VJiEhfR0Cmxno5xxGwYnp68brX4kSEC05z6CTz\r\n"    \
"AgMBAAGjUzBRMB0GA1UdDgQWBBR17J3dUpHJH1+t4E278DJNHainAjAfBgNVHSME\r\n"    \
"GDAWgBR17J3dUpHJH1+t4E278DJNHainAjAPBgNVHRMBAf8EBTADAQH/MA0GCSqG\r\n"    \
"SIb3DQEBCwUAA4IBAQCRPfLmCAmZcoW6BBx1cG58l6hPYiIo+ErgauMhRan4wkmA\r\n"    \
"uuKH39D3M1TM++AqgM9MpNcjOmQS3eVR5tVkb3Rv8oxvQgrEc3SVVWmrnPjP7Ho/\r\n"    \
"/yBG5MQsa6WubI8Uw1ZT4jS2O7Keq3IQLmIEiKeOzguo9YMW+oAKVS3SlL6Cqdk9\r\n"    \
"Ss3iyLNlQtCz1CfsqoV3zEcP7tCaagvR2ACQUibpOX+mFVxSdU7PCt6Ay6zOr/lP\r\n"    \
"0mJeqfBlNLOT1gOUOROHsNFwKO14EABaA2mu7P5Yrhj6Ptt1vKmeq+pL+PAYNJM2\r\n"    \
"VgXhePJalUyAQKR+E+0fjsrGAYBXMZoR93GxNBJG\r\n"    \
"-----END CERTIFICATE-----\r\n"

const char mbedtls_m2mqtt_ca_crt[] = M2MQTT_CA_CRT_RSA;
const size_t mbedtls_m2mqtt_ca_crt_len = sizeof(mbedtls_m2mqtt_ca_crt);

#define MOSQUITTO_CA_CRT_RSA                                              \
"-----BEGIN CERTIFICATE-----\r\n"                                         \
"MIIC8DCCAlmgAwIBAgIJAOD63PlXjJi8MA0GCSqGSIb3DQEBBQUAMIGQMQswCQYD\r\n"    \
"VQQGEwJHQjEXMBUGA1UECAwOVW5pdGVkIEtpbmdkb20xDjAMBgNVBAcMBURlcmJ5\r\n"    \
"MRIwEAYDVQQKDAlNb3NxdWl0dG8xCzAJBgNVBAsMAkNBMRYwFAYDVQQDDA1tb3Nx\r\n"    \
"dWl0dG8ub3JnMR8wHQYJKoZIhvcNAQkBFhByb2dlckBhdGNob28ub3JnMB4XDTEy\r\n"    \
"MDYyOTIyMTE1OVoXDTIyMDYyNzIyMTE1OVowgZAxCzAJBgNVBAYTAkdCMRcwFQYD\r\n"    \
"VQQIDA5Vbml0ZWQgS2luZ2RvbTEOMAwGA1UEBwwFRGVyYnkxEjAQBgNVBAoMCU1v\r\n"    \
"c3F1aXR0bzELMAkGA1UECwwCQ0ExFjAUBgNVBAMMDW1vc3F1aXR0by5vcmcxHzAd\r\n"    \
"BgkqhkiG9w0BCQEWEHJvZ2VyQGF0Y2hvby5vcmcwgZ8wDQYJKoZIhvcNAQEBBQAD\r\n"    \
"gY0AMIGJAoGBAMYkLmX7SqOT/jJCZoQ1NWdCrr/pq47m3xxyXcI+FLEmwbE3R9vM\r\n"    \
"rE6sRbP2S89pfrCt7iuITXPKycpUcIU0mtcT1OqxGBV2lb6RaOT2gC5pxyGaFJ+h\r\n"    \
"A+GIbdYKO3JprPxSBoRponZJvDGEZuM3N7p3S/lRoi7G5wG5mvUmaE5RAgMBAAGj\r\n"    \
"UDBOMB0GA1UdDgQWBBTad2QneVztIPQzRRGj6ZHKqJTv5jAfBgNVHSMEGDAWgBTa\r\n"    \
"d2QneVztIPQzRRGj6ZHKqJTv5jAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBBQUA\r\n"    \
"A4GBAAqw1rK4NlRUCUBLhEFUQasjP7xfFqlVbE2cRy0Rs4o3KS0JwzQVBwG85xge\r\n"    \
"REyPOFdGdhBY2P1FNRy0MDr6xr+D2ZOwxs63dG1nnAnWZg7qwoLgpZ4fESPD3PkA\r\n"    \
"1ZgKJc2zbSQ9fCPxt2W3mdVav66c6fsb7els2W2Iz7gERJSX\r\n"    \
"-----END CERTIFICATE-----\r\n"

const char mbedtls_mosquitto_test_ca_crt[] = MOSQUITTO_CA_CRT_RSA;
const size_t mbedtls_mosquitto_test_ca_crt_len = sizeof(mbedtls_mosquitto_test_ca_crt);
