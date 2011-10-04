/* HashKit
 * Copyright (C) 2009 Brian Aker
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license.  See
 * the COPYING file in the parent directory for full text.
 */

#pragma once

#include <config.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <libhashkit-1.0/hashkit.h>
#include <libhashkit/is.h>

#ifdef __cplusplus
extern "C" {
#endif

HASHKIT_LOCAL
void md5_signature(const unsigned char *key, unsigned int length, unsigned char *result);

HASHKIT_LOCAL
int update_continuum(hashkit_st *hashkit);

#ifdef __cplusplus
}
#endif
