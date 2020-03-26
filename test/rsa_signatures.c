/*
 * Copyright 2020 IBM Corp.
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
 */

#include <openssl/core_names.h>
#include <openssl/evp.h>
#include <openssl/params.h>
#include <openssl/provider.h>
#include <openssl/rsa.h>

#include "test.h"

int main(int argc, char *argv[])
{
    OSSL_PROVIDER *prov = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *pkey = NULL;
    int rc;

    TEST_ENTRY(argc, argv);

    prov = OSSL_PROVIDER_load(NULL, "pkcs11");
    if (prov == NULL)
        TEST_EXIT_FAIL_MSG("%s", "OSSL_PROVIDER_load returned NULL");
    rc = OSSL_PROVIDER_available(NULL, "pkcs11");
    if (rc != 1)
        TEST_EXIT_FAIL_MSG("OSSL_PROVIDER_available returned %d", rc);


    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx)
        TEST_EXIT_FAIL_MSG("%s", "EVP_PKEY_CTX_new_id returned NULL");
    rc = EVP_PKEY_keygen_init(ctx);
    if (rc <= 0)
        TEST_EXIT_FAIL_MSG("EVP_PKEY_keygen_init returned %d", rc);
    /*
    rc = EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);
    if (rc <= 0)
        TEST_EXIT_FAIL_MSG("EVP_PKEY_CTX_set_rsa_keygen_bits returned %d", rc);
	*/
    rc = EVP_PKEY_keygen(ctx, &pkey);
    if (rc <= 0)
        TEST_EXIT_FAIL_MSG("EVP_PKEY_keygen returned %d", rc);

    rc = OSSL_PROVIDER_unload(prov);
    if (rc != 1)
        TEST_EXIT_FAIL_MSG("OSSL_PROVIDER_unload returned %d", rc);

    TEST_EXIT_SUCC();
}
