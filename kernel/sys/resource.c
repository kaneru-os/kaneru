/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c), 2022, Kaneru Contributors */
#include <kaneru/kprintf.h>
#include <kaneru/resource.h>
#include <string.h>

static struct resource *resources = NULL;

int register_resource(struct resource *restrict r)
{
    if(find_resource(r->name)) {
        kprintf(KP_RESOURCE, "resource [%s] already exists", r->name);
        return -EBUSY;
    }

    r->next = resources;
    resources = r;
    
    return 0;
}

const struct resource *find_resource(const char *name)
{
    const struct resource *res;
    for(res = resources; res; res = res->next) {
        if(strncmp(res->name, name, sizeof(res->name)) != 0)
            continue;
        return res;
    }

    return NULL;
}

static volatile void *get_aligned_mmio(unsigned int flags, uintptr_t base, uintptr_t offset)
{
    if(flags & RESOURCE_MMIO_A_16)
        return &((volatile uint16_t *)base)[offset];
    if(flags & RESOURCE_MMIO_A_32)
        return &((volatile uint32_t *)base)[offset];
    return &((volatile uint8_t *)base)[offset];
}

int resource_read8(const struct resource *restrict r, uintptr_t offset, uint8_t *restrict val)
{
    volatile uint8_t *mmio_base;

    if(r->flags & RESOURCE_PMIO) {
        if(r->flags & RESOURCE_PMIO_SLOW)
            pmio_throttle();
        return pmio_read8(r->base + offset, val);
    }

    if(r->flags & RESOURCE_MMIO) {
        mmio_base = get_aligned_mmio(r->flags, r->base, offset);
        val[0] = mmio_base[0];
        return 0;
    }

    return -EIO;
}

int resource_read16(const struct resource *restrict r, uintptr_t offset, uint16_t *restrict val)
{
    volatile uint16_t *mmio_base;

    if(r->flags & RESOURCE_PMIO) {
        if(r->flags & RESOURCE_PMIO_SLOW)
            pmio_throttle();
        return pmio_read16(r->base + offset, val);
    }

    if(r->flags & RESOURCE_MMIO) {
        mmio_base = get_aligned_mmio(r->flags, r->base, offset);
        val[0] = mmio_base[0];
        return 0;
    }

    return -EIO;
}

int resource_read32(const struct resource *restrict r, uintptr_t offset, uint32_t *restrict val)
{
    volatile uint32_t *mmio_base;

    if(r->flags & RESOURCE_PMIO) {
        if(r->flags & RESOURCE_PMIO_SLOW)
            pmio_throttle();
        return pmio_read32(r->base + offset, val);
    }

    if(r->flags & RESOURCE_MMIO) {
        mmio_base = get_aligned_mmio(r->flags, r->base, offset);
        val[0] = mmio_base[0];
        return 0;
    }

    return -EIO;
}

int resource_write8(const struct resource *restrict r, uintptr_t offset, uint8_t val)
{
    volatile uint8_t *mmio_base;

    if(r->flags & RESOURCE_PMIO) {
        if(r->flags & RESOURCE_PMIO_SLOW)
            pmio_throttle();
        return pmio_write8(r->base + offset, val);
    }

    if(r->flags & RESOURCE_MMIO) {
        mmio_base = get_aligned_mmio(r->flags, r->base, offset);
        mmio_base[0] = val;
        return 0;
    }

    return -EIO;
}

int resource_write16(const struct resource *restrict r, uintptr_t offset, uint16_t val)
{
    volatile uint16_t *mmio_base;

    if(r->flags & RESOURCE_PMIO) {
        if(r->flags & RESOURCE_PMIO_SLOW)
            pmio_throttle();
        return pmio_write16(r->base + offset, val);
    }

    if(r->flags & RESOURCE_MMIO) {
        mmio_base = get_aligned_mmio(r->flags, r->base, offset);
        mmio_base[0] = val;
        return 0;
    }

    return -EIO;
}

int resource_write32(const struct resource *restrict r, uintptr_t offset, uint32_t val)
{
    volatile uint32_t *mmio_base;

    if(r->flags & RESOURCE_PMIO) {
        if(r->flags & RESOURCE_PMIO_SLOW)
            pmio_throttle();
        return pmio_write32(r->base + offset, val);
    }

    if(r->flags & RESOURCE_MMIO) {
        mmio_base = get_aligned_mmio(r->flags, r->base, offset);
        mmio_base[0] = val;
        return 0;
    }

    return -EIO;
}
