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
"MIIDYDCCAkigAwIBAgIJAK3FvDgDSHiyMA0GCSqGSIb3DQEBCwUAMEUxCzAJBgNV\r\n"    \
"BAYTAkNIMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBX\r\n"    \
"aWRnaXRzIFB0eSBMdGQwHhcNMTcwNDE0MTcyNDIyWhcNMjcwNDEyMTcyNDIyWjBF\r\n"    \
"MQswCQYDVQQGEwJDSDETMBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UECgwYSW50\r\n"    \
"ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\r\n"    \
"CgKCAQEA0rbytbd2tf3PXMiUi8O/CgaBNr7OAWbSdtyDl8NTRMGT58PTFdc5ZhCO\r\n"    \
"23jAmgoor3gwdniHmQWiYcMINSjtM+z14JbnG23P7PXUoT89V8YLOPgsZiRYGIoP\r\n"    \
"Ba172GdddIh6qyj0lAWjGau0RuV93xl+rYx20J7HAb+nHmqmz/NTtmopcXe87GQ0\r\n"    \
"NFZH6xR2TBj6mq9Bnk5KNl+yvnNIz7l9uvKkHe8tlWt/quoFlKIdARHjkzfo/eN0\r\n"    \
"JzpgxO++cI6wkAc//AqfcwOfVhA2xUex2+RPLM6teDI+ZjlEBK5Fz3hMJpcFUyFS\r\n"    \
"AgRunSZNoYWJheIrUTXKqOF/GT0nzwIDAQABo1MwUTAdBgNVHQ4EFgQUZPgd2ZCV\r\n"    \
"dwEXIJqgjb5EEpf7lu0wHwYDVR0jBBgwFoAUZPgd2ZCVdwEXIJqgjb5EEpf7lu0w\r\n"    \
"DwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAREpAcqBk9w4kQCOo\r\n"    \
"2uPSbocUmNDNQxe80rXCzoaOa+RcFiDKqbOeky+6SwrO6+Q6uq5L0ynrrBuccXkO\r\n"    \
"YaEDvNAEjVi5p3pTZHeTLBapQ3KE+vbJQSTkMGNoMtaflERD1lt0JzMMT1sbHWsQ\r\n"    \
"Gq18Llv+k+Rw4FGxMY7jsCHaGIVZyb/xqwPOrOQAj3W0AmsiF54vPCSWs7l6QxAa\r\n"    \
"0ObtnshtECt13f7i8hb/qPWVMzh06gVIaS/kEWRzML01lUKdf9o+Wq7S8PSliSup\r\n"    \
"jsMfrRXVN83Y8QCThhlqSwnwgeUlWjad10L4hYke2rLkwMXAM4e4WWjirtw+Ok5b\r\n"    \
"iwb5pA==\r\n"                                                            \
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
