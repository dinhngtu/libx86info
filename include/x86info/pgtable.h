#pragma once

#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>

#include "arch/cr.h"
#include "arch/pgtable.h"

#define X86_LM_INVALID_ADDRESS UINT64_MAX

struct x86_pg_walk_lm_ops {
    bool (*phys_read)(void *out, uint64_t pa, size_t size);
    bool (*cr3_callback)(const union x86_cr3 *cr3, const union x86_cr4 *cr4);
    bool (*pml4e_callback)(const union x86_pml4e *pml4e);
    bool (*pdpte_callback)(const union x86_pdpte *pdpte);
    bool (*pde_callback)(const union x86_pde *pde);
    bool (*pte_callback)(const union x86_pte *pte);
};

uint64_t x86_pg_walk_lm(uint64_t va, uint64_t cr3, uint64_t cr4, const struct x86_pg_walk_lm_ops *ops);