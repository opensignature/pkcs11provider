#!/bin/bash

# set default values
export PKCS11MODULE=${PKCS11MODULE:-libopencryptoki.so};
export PKCS11SLOTID=${PKCS11SLOTID:-0};
export PKCS11USERPIN=${PKCS11USERPIN:-87654321};
export PKCS11OBJECTS=${PKCS11OBJECTS:-token};
export PKCS11RSAKEYGEN=${PKCS11RSAKEYGEN:-X9.31:PKCS#1};
