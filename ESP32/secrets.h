#ifndef SECRETS_H
#define SECRETS_H

/***********************************************************************
 * secrets.h
 *
 * This file contains all sensitive configuration details for the
 * SafeHaven ESP32 + AWS IoT Core system. It includes:
 *  - Wi-Fi credentials
 *  - AWS IoT endpoint configuration
 *  - MQTT topic & client ID
 *  - TLS certificates for secure communication
 *
 * NOTE: This file should NEVER be committed to a public repository.
 ***********************************************************************/

/*********************
 * Wi-Fi Credentials *
 *********************/

// SSID of the Wi-Fi network your ESP32 should connect to
constexpr const char* WIFI_SSID = "JW's iPhone";

// Wi-Fi password (ensure it's correct and secure)
constexpr const char* WIFI_PASS = "123454321";


/***************************************
 * AWS IoT Core MQTT Configuration
 ***************************************/

// The AWS IoT Core endpoint for your registered IoT Thing.
// This is generated automatically when you create a Thing in AWS IoT Core.
constexpr const char* AWS_ENDPOINT = "axcxvonqetgd9-ats.iot.ca-central-1.amazonaws.com";

// Port for secure MQTT communication using TLS
// 8883 is the standard port for MQTT over TLS
constexpr int AWS_PORT = 8883;

// MQTT Topic to publish sensor telemetry data
// Must match subscriber topics on backend
constexpr const char* TOPIC = "sensors/safehavendata";

// MQTT Client ID - must be unique for every device connecting to AWS IoT
// Typically, this is the Thing name or a unique identifier
constexpr const char* CLIENT_ID = "Fariza's laptop";


/*****************************
 * TLS / Certificates
 *****************************/

/*
 * AWS IoT requires secure TLS connections.
 * This section provides:
 * 1) Root CA certificate (Amazon Root CA 1)
 * 2) Device certificate
 * 3) Device private key
 *
 * PROGMEM is used to store certificates in flash memory instead of RAM,
 * which is critical on memory-constrained devices like ESP32.
 */

// ---------------- Root CA ----------------
// Amazon Root CA 1
// Verifies that the AWS server is legitimate
const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// ---------------- Device Certificate ----------------
// Issued by AWS IoT for your specific Thing
// Used to authenticate the ESP32 device to AWS IoT Core
const char DEVICE_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUfR+BkO1mLVpURVTAM9ZpybE19q8wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDIyMDAzMTUz
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALzXRWrj/fO+oSfm9ByH
CpNapPi5hIGMW+n0nNluBY+j+uZeYTiSArTp1DW+WhmKPeDUP52n4vEYCeB8dkIk
+XzGdn9gP7eUWHytlwtJbDufPHKFuDCdGjgYmDiEv45jxyn6BfQqGY/+9nC9LQFH
2tVM2S8lecbK+3MBTif4BDp6gZ5hisvliQiUIjz9rIuxKb41M2Lg/oCnQWmQ2QvL
gSobeZzoAyicSLg7Nwocd1uGMmIaD/4h959R039LXmMriDfd5T+k+/YCPYVhxPdk
5TfFPPL49YD6m8o2oBJx5Nwgri3B9Egz8YB6q+qEjuaBKYzu2TMnU34Wui0V6k0T
WWkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUu4cAGpFJKeA+Mji/F2Hh87/TJPwwHQYD
VR0OBBYEFGycuGzVJJepkTNyboCWbqR/g5eRMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDhGeN+w7x2hQsUBlBnfhNdTk3A
YRZgh7Kt4i4m8SxiAThUX6PCeXRMN+QPq6CSZI9ADmPN2dg618M7kcLejm46rInn
B9Jlr9TLZar3ui99BVsL19m1SNSHh1eIi6HOEtyv6daTFIbnaLPMwD6UstSafFdv
v7DWYt0CVC4EnDKv3ZqlGqVW+tVIoKRoWET8h2Takxr58yNk/esVErU31C+4/roB
elZmBg8lK2FyqnCTGRV5UNNGUf7Ps3EwFfcGuQ2gzOFhmSUr6AvwrasDupnLWeHm
KA0PE5DBUQRiwIRc0dpZIaL6DctI4ZGz4kZI6xwgnveowBSM0+FFPUF94tma
-----END CERTIFICATE-----
)EOF";

// ---------------- Device Private Key ----------------
// Private key corresponding to the device certificate
// Must remain secret. ESP32 uses this to sign TLS connections.
const char PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAvNdFauP9876hJ+b0HIcKk1qk+LmEgYxb6fSc2W4Fj6P65l5h
OJICtOnUNb5aGYo94NQ/nafi8RgJ4Hx2QiT5fMZ2f2A/t5RYfK2XC0lsO588coW4
MJ0aOBiYOIS/jmPHKfoF9CoZj/72cL0tAUfa1UzZLyV5xsr7cwFOJ/gEOnqBnmGK
y+WJCJQiPP2si7EpvjUzYuD+gKdBaZDZC8uBKht5nOgDKJxIuDs3Chx3W4YyYhoP
/iH3n1HTf0teYyuIN93lP6T79gI9hWHE92TlN8U88vj1gPqbyjagEnHk3CCuLcH0
SDPxgHqr6oSO5oEpjO7ZMydTfha6LRXqTRNZaQIDAQABAoIBAQCA96wrAiYvzyMU
s0BIM1nfpOpCC8EZEJi9QRfVzrPxk5YIurA/CEjc8UzCn4u9IZJ897eynjP5X+du
7tF8/u98bbYD6+HYKHH+RDeBt9U5KtkHhZdza/e6E+Hxx4djYXVlj6F9TTtEAmag
PDJ+S2qCfgddkYSHZZ0wv9V2qoWIwXFbslMfCx5Tmm1zn4nbwV3pDXNttvRvxmrg
JdOovoMsU3L4FN7f2zcd3qCtuwalVQ9jE7xBY8KKgZagKvOPDrfw00CAsDZx3NAf
8PQDeVPPAv+kusa1w/TuhoT+gBnk6IDvraRjoddFR/yCp3wUmoU9Q3P0LGaKQLuA
FvqvQJ7ZAoGBAOCzTBnKzYRQhtVZum9G7vae5GFz3yjjL862CjU6WWlCalx5euCT
qaRUGMmUStKu0eEoPDs52cVq1pX6kftNp0jWgDBAwMrVbQXglEGo+E91sFNW36kl
dWOgC2E0OrtsU8x6iaEve3mgFevWw9pHcnEW38CX+C4C3uMcS+twi0azAoGBANcl
PjHoop7b/WqkHLEeTdo/f4MzpAgGHqzms4pOJPtHdUR4KHiRHXoMUQRGG3hnCm2e
Gke5p6JyI3LcfSY3K163FdZ3puTH7r3JvtwEAP23bVWk3s/2qAOEsPNomhBSWnGd
58HbIU3jTarAKnUn1W73BYmPV6v4KYraL8FOJo1zAoGBALBFd6m0Is1trpioL00k
REpME7UvhR06PELZI+DlyUZ9x5qL4g1TSX2US223W4szgYo0WivMEj6AtZ4qV2Lh
ZB4Lx7wS0CtOipxVtXhc6Y7MMGrwd7zlmdVxs/upUXm+XW7HojhEW4TqRMgiTrpp
2ilFXHplvVe7AMcBZ71nKJtpAoGBAKzAU9thT8q9HBPX6M3zZlHbcLjZ61kiCNmO
eRWRv7Ig47FxxhVheEi6wQbsgDxCiKYSMEntcgRHH92n27mmzOVFn3xRISpMu4+b
AezKLj2LXnhJZTuZc7k3f5pDIIoAhmz6fNA08t4GqSN1H+JodMGgCcs11RDZuAmt
PnE6HkyvAoGAdFrDu0bdWa5YxubmjBTg7+EUJfIRaVmyFASWGTlsi11UFVXOFJJ5
jHjKyQrxBYeZGm8/ZDhiBgZqdiFxauSOMfvsxhhlv/su6bx4Uwt68SOWEchnJIy1
eHqBZzFOiu230nyGfophKdI8FbZMjmfAXQh4PCkddbLLYshB9y3GUds=
-----END RSA PRIVATE KEY-----
)EOF";

#endif
