/*******************************************************************************
 * Copyright 2016, 2017 ARM Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#ifndef TEST_TLS_PAL_TEST_UTILS_H_
#define TEST_TLS_PAL_TEST_UTILS_H_

#include "pal_network.h"
#include "pal_TLS.h"

typedef struct palTLSSocketTest{
    palSocket_t socket;
    palSocketAddress_t* socketAddress;
    palSocketLength_t addressLength;
    palTLSTransportMode_t transportationMode;
}palTLSSocketTest_t;

#define PAL_TLS_RESPONSE_WAIT_MS 5000
#define DTLS_SERVER_PORT_TIMEOUT 9 //Discard protocol

// This is a workaround for Linux PAL test compilation as credentials
// from mbed_cloud_dev_credentials.c are not included in the build.
#define PAL_TLS_TEST_SERVER_ADDRESS "127.0.0.1"
#ifndef PAL_TLS_TEST_SERVER_ADDRESS
// Use bootstrap server as test server by default
// Expect mbed_cloud_dev_credentials.c to be compiled
extern const char MBED_CLOUD_DEV_BOOTSTRAP_SERVER_URI[];
extern const uint8_t MBED_CLOUD_DEV_BOOTSTRAP_DEVICE_PRIVATE_KEY[];
extern const uint8_t MBED_CLOUD_DEV_BOOTSTRAP_SERVER_ROOT_CA_CERTIFICATE[];
extern const uint8_t MBED_CLOUD_DEV_BOOTSTRAP_DEVICE_CERTIFICATE[];

#define PAL_TLS_TEST_SERVER_ADDRESS_UDP MBED_CLOUD_DEV_BOOTSTRAP_SERVER_URI
#define PAL_TLS_TEST_SERVER_ADDRESS_TCP MBED_CLOUD_DEV_BOOTSTRAP_SERVER_URI
#define PAL_TLS_TEST_DEVICE_PRIVATE_KEY MBED_CLOUD_DEV_BOOTSTRAP_DEVICE_PRIVATE_KEY
#define PAL_TLS_TEST_SERVER_CA MBED_CLOUD_DEV_BOOTSTRAP_SERVER_ROOT_CA_CERTIFICATE
#define PAL_TLS_TEST_DEVICE_CERTIFICATE MBED_CLOUD_DEV_BOOTSTRAP_DEVICE_CERTIFICATE

// Bootstrap server responds to 'coap ping'

// confirmable empty message with id 0
const unsigned char coap_ping_message[] = {
    0x40, 0x00, 0x00, 0x00
};

// reset empty with message id 0
const unsigned char coap_ping_response[] = {
    0x70, 0x00, 0x00, 0x00
};

#define PAL_TLS_REQUEST_MESSAGE coap_ping_message
#define PAL_TLS_UDP_REQUEST_MESSAGE coap_ping_message
#define PAL_TLS_RESPONSE_MESSAGE coap_ping_response
#define PAL_TLS_RESPONSE_SIZE sizeof(coap_ping_response)

#else // #ifndef PAL_TLS_TEST_SERVER_ADDRESS

// Expect that pal test servers are in use
//ECC Key
const unsigned char g_pubKey[] =
{
  0x30, 0x82, 0x01, 0x99, 0x30, 0x82, 0x01, 0x3d, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x01, 0x01,
  0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x03, 0x02, 0x05, 0x00, 0x30, 0x29,
  0x31, 0x0c, 0x30, 0x0a, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x03, 0x50, 0x41, 0x4c, 0x31, 0x0c,
  0x30, 0x0a, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x03, 0x61, 0x72, 0x6d, 0x31, 0x0b, 0x30, 0x09,
  0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x49, 0x4c, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x33, 0x30,
  0x31, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x5a, 0x17, 0x0d, 0x32, 0x30, 0x31, 0x32,
  0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39, 0x5a, 0x30, 0x30, 0x31, 0x13, 0x30, 0x11, 0x06,
  0x03, 0x55, 0x04, 0x03, 0x13, 0x0a, 0x50, 0x41, 0x4c, 0x5f, 0x63, 0x6c, 0x69, 0x65, 0x6e, 0x74,
  0x31, 0x0c, 0x30, 0x0a, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x03, 0x61, 0x72, 0x6d, 0x31, 0x0b,
  0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x49, 0x4c, 0x30, 0x59, 0x30, 0x13, 0x06,
  0x07, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x02, 0x01, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03,
  0x01, 0x07, 0x03, 0x42, 0x00, 0x04, 0x18, 0x8f, 0xc6, 0x40, 0xf3, 0xf4, 0xbc, 0xd9, 0xed, 0x72,
  0x7e, 0x96, 0x8f, 0xcc, 0x56, 0x31, 0x6d, 0x72, 0x1d, 0x4e, 0xd8, 0xb2, 0xc1, 0x5b, 0xcb, 0xcf,
  0xd6, 0xc5, 0xdb, 0x1f, 0xdf, 0x99, 0x21, 0x01, 0xbc, 0x0c, 0x03, 0xb8, 0xa9, 0xbd, 0xd7, 0xb7,
  0x4f, 0x06, 0x8c, 0x5f, 0x6e, 0xe8, 0x64, 0xc9, 0x69, 0x46, 0x96, 0xf8, 0xfd, 0x14, 0xe5, 0xe3,
  0x5b, 0x8c, 0x92, 0x99, 0x04, 0xe6, 0xa3, 0x4d, 0x30, 0x4b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1d,
  0x13, 0x04, 0x02, 0x30, 0x00, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14,
  0xb8, 0x4f, 0xcc, 0xad, 0x6b, 0xad, 0xa1, 0x31, 0x75, 0x74, 0x57, 0xe3, 0x76, 0x9f, 0x5d, 0xc3,
  0x4f, 0xcf, 0x20, 0x53, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80,
  0x14, 0xfe, 0x53, 0x4c, 0xfa, 0x9a, 0xc7, 0x2f, 0x0c, 0x72, 0xbf, 0xaa, 0x47, 0xc5, 0x16, 0x92,
  0x67, 0x7f, 0x0e, 0x02, 0xef, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x03,
  0x02, 0x05, 0x00, 0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x21, 0x00, 0x97, 0x90, 0xa3, 0x5d, 0xab,
  0xee, 0x4f, 0x56, 0x12, 0x15, 0x0f, 0xbe, 0x3a, 0x39, 0x21, 0x54, 0x44, 0x67, 0x48, 0xf8, 0xb4,
  0x83, 0xbe, 0xda, 0x66, 0x62, 0xa0, 0xa5, 0x67, 0x1c, 0xf4, 0xba, 0x02, 0x20, 0x22, 0x41, 0x3f,
  0x52, 0x3a, 0xaa, 0x9d, 0x3c, 0xf1, 0x99, 0x7d, 0x2c, 0x04, 0x89, 0xff, 0xce, 0x80, 0x56, 0xd1,
  0x9c, 0xd9, 0x19, 0x06, 0xd3, 0xee, 0x41, 0x2b, 0x49, 0x76, 0x27, 0xfe, 0x4e
};

const uint8_t g_prvKey[] =
{
  0x30, 0x78, 0x02, 0x01, 0x01, 0x04, 0x21, 0x00, 0xac, 0xfb, 0x43, 0x6f, 0xa1, 0x3c, 0x2d, 0x1a,
  0x91, 0xd7, 0x58, 0xf8, 0x1f, 0x0f, 0xc5, 0x00, 0x11, 0xe1, 0x56, 0xe6, 0xed, 0x89, 0x96, 0x8b,
  0x12, 0xe6, 0x32, 0x70, 0x82, 0x06, 0x01, 0xed, 0xa0, 0x0a, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce,
  0x3d, 0x03, 0x01, 0x07, 0xa1, 0x44, 0x03, 0x42, 0x00, 0x04, 0x18, 0x8f, 0xc6, 0x40, 0xf3, 0xf4,
  0xbc, 0xd9, 0xed, 0x72, 0x7e, 0x96, 0x8f, 0xcc, 0x56, 0x31, 0x6d, 0x72, 0x1d, 0x4e, 0xd8, 0xb2,
  0xc1, 0x5b, 0xcb, 0xcf, 0xd6, 0xc5, 0xdb, 0x1f, 0xdf, 0x99, 0x21, 0x01, 0xbc, 0x0c, 0x03, 0xb8,
  0xa9, 0xbd, 0xd7, 0xb7, 0x4f, 0x06, 0x8c, 0x5f, 0x6e, 0xe8, 0x64, 0xc9, 0x69, 0x46, 0x96, 0xf8,
  0xfd, 0x14, 0xe5, 0xe3, 0x5b, 0x8c, 0x92, 0x99, 0x04, 0xe6
};


const char pal_test_cas[] =
{
  0x30, 0x82, 0x01, 0x98, 0x30, 0x82, 0x01, 0x3c, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x01, 0x01,
  0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x03, 0x02, 0x05, 0x00, 0x30, 0x29,
  0x31, 0x0c, 0x30, 0x0a, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x03, 0x50, 0x41, 0x4c, 0x31, 0x0c,
  0x30, 0x0a, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x03, 0x61, 0x72, 0x6d, 0x31, 0x0b, 0x30, 0x09,
  0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x49, 0x4c, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x33, 0x30,
  0x31, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x5a, 0x17, 0x0d, 0x32, 0x30, 0x31, 0x32,
  0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39, 0x5a, 0x30, 0x29, 0x31, 0x0c, 0x30, 0x0a, 0x06,
  0x03, 0x55, 0x04, 0x03, 0x13, 0x03, 0x50, 0x41, 0x4c, 0x31, 0x0c, 0x30, 0x0a, 0x06, 0x03, 0x55,
  0x04, 0x0a, 0x13, 0x03, 0x61, 0x72, 0x6d, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
  0x13, 0x02, 0x49, 0x4c, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x02,
  0x01, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07, 0x03, 0x42, 0x00, 0x04, 0xa4,
  0x26, 0x26, 0x29, 0x98, 0x43, 0x6c, 0xc2, 0x2c, 0xbe, 0x0a, 0x90, 0xe3, 0x78, 0x44, 0xa9, 0x15,
  0x0b, 0x02, 0x26, 0xf6, 0x14, 0xda, 0x36, 0x5b, 0x0f, 0x1d, 0x15, 0xb1, 0x56, 0x76, 0xec, 0x7f,
  0x59, 0x6b, 0x9d, 0x69, 0xd9, 0xd8, 0x16, 0x22, 0xf1, 0x90, 0x63, 0xa1, 0xd3, 0xb7, 0xd7, 0x32,
  0x31, 0x8d, 0xc7, 0xbe, 0x8f, 0xc8, 0x20, 0x5a, 0x9d, 0xfa, 0x03, 0x79, 0x7a, 0xcb, 0x7e, 0xa3,
  0x53, 0x30, 0x51, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x04, 0x08, 0x30, 0x06, 0x01, 0x01,
  0xff, 0x02, 0x01, 0x00, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0xfe,
  0x53, 0x4c, 0xfa, 0x9a, 0xc7, 0x2f, 0x0c, 0x72, 0xbf, 0xaa, 0x47, 0xc5, 0x16, 0x92, 0x67, 0x7f,
  0x0e, 0x02, 0xef, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14,
  0xfe, 0x53, 0x4c, 0xfa, 0x9a, 0xc7, 0x2f, 0x0c, 0x72, 0xbf, 0xaa, 0x47, 0xc5, 0x16, 0x92, 0x67,
  0x7f, 0x0e, 0x02, 0xef, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x03, 0x02,
  0x05, 0x00, 0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x21, 0x00, 0x97, 0xce, 0xc5, 0x3c, 0x94, 0xb5,
  0xd4, 0x3b, 0xec, 0x92, 0xed, 0x2b, 0x96, 0x3f, 0xdc, 0xae, 0x16, 0xd2, 0x02, 0x6a, 0xa6, 0x8d,
  0xf5, 0xb1, 0x5b, 0x61, 0x95, 0xfc, 0x4d, 0x17, 0x0e, 0xab, 0x02, 0x20, 0x40, 0x7b, 0x27, 0x11,
  0x83, 0x87, 0xfe, 0x62, 0xa2, 0x67, 0x7c, 0xa8, 0x8e, 0xd5, 0xf3, 0xdc, 0x62, 0xf9, 0x35, 0x91,
  0x0b, 0x43, 0x80, 0xc9, 0x12, 0x30, 0x2e, 0x66, 0x64, 0xbf, 0xf2, 0xcb
};

#define PAL_TLS_TEST_DEVICE_PRIVATE_KEY g_prvKey
#define PAL_TLS_TEST_SERVER_CA pal_test_cas
#define PAL_TLS_TEST_DEVICE_CERTIFICATE g_pubKey

// Local test server is http server in tcp cases
const unsigned char http_get_message[] = "GET / HTTP/1.0\r\n\r\n";

// Non-confirmable GET with payload '/helloWorld', used in udp cases
const unsigned char coap_helloworld_request[] = {
    0x50, 0x01, 0x57, 0x3e, 0xff, 0x2f, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x57, 0x6f, 0x72, 0x6c, 0x64
};

#define PAL_TLS_REQUEST_MESSAGE http_get_message
#define PAL_TLS_UDP_REQUEST_MESSAGE coap_helloworld_request
#undef PAL_TLS_RESPONSE_MESSAGE
#define PAL_TLS_RESPONSE_SIZE 256

#define PAL_TLS_TEST_SERVER_ADDRESS_UDP PAL_TLS_TEST_SERVER_ADDRESS":4422"
#define PAL_TLS_TEST_SERVER_ADDRESS_TCP PAL_TLS_TEST_SERVER_ADDRESS":5544"

#endif // #ifndef PAL_TLS_TEST_SERVER_ADDRESS

const uint16_t MAX_CERTIFICATE_SIZE = 1024;

const unsigned char g_psk[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};
const unsigned char g_psk_id[] = "Client_identity";

#endif /* TEST_TLS_PAL_TEST_UTILS_H_ */
