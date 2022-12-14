/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c), 2022, KanOS Contributors */
#ifndef _INCLUDE_UAPI_X86_GDT_H__
#define _INCLUDE_UAPI_X86_GDT_H__

#define GDT_NULL 0
#define GDT_KERN_CODE_16 1
#define GDT_KERN_DATA_16 2
#define GDT_KERN_CODE_32 3
#define GDT_KERN_DATA_32 4
#define GDT_KERN_CODE_64 5
#define GDT_KERN_DATA_64 6
#define GDT_USER_CODE_64 7
#define GDT_USER_DATA_64 8

#endif /* _INCLUDE_UAPI_X86_GDT_H__ */
