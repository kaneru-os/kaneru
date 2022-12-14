/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c), 2022, Kaneru Contributors */
#include <limits.h>
#include <stdlib.h>

unsigned long strtoul(const char *restrict s, const char **restrict endptr, int base)
{
    unsigned long r;
    strtoxx_ctx_t ctx = { 0 };
    ctx.base = base;
    ctx.sign = '+';
    
    strtoxx_init(s, &ctx);
    if(!ctx.s) {
        if(endptr)
            *endptr = NULL;
        return 0;
    }

    ctx.error = (uintmax_t)(ULONG_MAX);
    ctx.limval = (uintmax_t)(ULONG_MAX / ctx.base);
    ctx.limdigit = (int)(ULONG_MAX % ctx.base);

    r = (unsigned long)strtoxx_main(&ctx);
    if(ctx.sign != '+')
        r = -r;
    
    if(endptr)
        *endptr = ctx.s ? ctx.s : s;
    return r;
}
