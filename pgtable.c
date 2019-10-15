#include "x86info/pgtable.h"

static uint64_t walk1_lm_cr3(const union x86_cr3 *cr3, const union x86_cr4 *cr4, const struct x86_pg_walk_lm_ops *ops) {
    if (ops->cr3_callback && !ops->cr3_callback(cr3, cr4)) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (cr4->f.pcide) {
        return cr3->f.pcid.fpml4;
    } else {
        return cr3->f.no_pcid.fpml4;
    }
}

static uint64_t walk1_lm_pml4e(const union x86_pml4e *pml4e, const struct x86_pg_walk_lm_ops *ops) {
    if (ops->pml4e_callback && !ops->pml4e_callback(pml4e)) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (pml4e->f.present) {
        return pml4e->f.fpdpt;
    } else {
        return X86_LM_INVALID_ADDRESS;
    }
}

static uint64_t walk1_lm_pdpte(const union x86_pdpte *pdpte, const struct x86_pg_walk_lm_ops *ops, bool *out_ps) {
    if (ops->pdpte_callback && !ops->pdpte_callback(pdpte)) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (pdpte->f.present) {
        *out_ps = pdpte->f.ps;
        if (pdpte->f.ps) {
            return pdpte->f._ps.ps1gb.a1gb << 18;
        } else {
            return pdpte->f._ps.pd.fpd;
        }
    } else {
        return X86_LM_INVALID_ADDRESS;
    }
}

static uint64_t walk1_lm_pde(const union x86_pde *pde, const struct x86_pg_walk_lm_ops *ops, bool *out_ps) {
    if (ops->pde_callback && !ops->pde_callback(pde)) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (pde->f.present) {
        *out_ps = pde->f.ps;
        if (pde->f.ps) {
            return pde->f._ps.ps2mb.a2mb << 9;
        } else {
            return pde->f._ps.pt.fpt;
        }
    } else {
        return X86_LM_INVALID_ADDRESS;
    }
}

static uint64_t walk1_lm_pte(const union x86_pte *pte, const struct x86_pg_walk_lm_ops *ops) {
    if (ops->pte_callback && !ops->pte_callback(pte)) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (pte->f.present) {
        return pte->f.fp;
    } else {
        return X86_LM_INVALID_ADDRESS;
    }
}

uint64_t x86_pg_walk_lm(uint64_t va, uint64_t _cr3, uint64_t _cr4, const struct x86_pg_walk_lm_ops *ops) {
    uint64_t pml4_idx = (va >> 39) & 0x1ff;
    uint64_t pdpt_idx = (va >> 30) & 0x1ff;
    uint64_t pd_idx = (va >> 21) & 0x1ff;
    uint64_t pt_idx = (va >> 12) & 0x1ff;
    uint64_t offset = va & 0xfff;

    if (!ops->phys_read) {
        return X86_LM_INVALID_ADDRESS;
    }

    union x86_cr3 cr3 = {.v = _cr3};
    union x86_cr4 cr4 = {.v = _cr4};

    uint64_t fpml4 = walk1_lm_cr3(&cr3, &cr4, ops);
    if (fpml4 == X86_LM_INVALID_ADDRESS) {
        return X86_LM_INVALID_ADDRESS;
    }

    union x86_pml4e pml4e;
    if (!ops->phys_read(&pml4e.v, (fpml4 << 12) + pml4_idx * 8, 8)) {
        return X86_LM_INVALID_ADDRESS;
    }

    uint64_t fpdpt = walk1_lm_pml4e(&pml4e, ops);
    if (fpdpt == X86_LM_INVALID_ADDRESS) {
        return X86_LM_INVALID_ADDRESS;
    }

    union x86_pdpte pdpte;
    if (!ops->phys_read(&pdpte.v, (fpdpt << 12) + pdpt_idx * 8, 8)) {
        return X86_LM_INVALID_ADDRESS;
    }

    bool out_ps;
    uint64_t fpd = walk1_lm_pdpte(&pdpte, ops, &out_ps);
    if (fpd == X86_LM_INVALID_ADDRESS) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (out_ps) {
        return (fpd << 12) | (pd_idx << 21) | (pt_idx << 12) | offset;
    }

    union x86_pde pde;
    if (!ops->phys_read(&pde.v, (fpd << 12) + pd_idx * 8, 8)) {
        return X86_LM_INVALID_ADDRESS;
    }

    uint64_t fpt = walk1_lm_pde(&pde, ops, &out_ps);
    if (fpt == X86_LM_INVALID_ADDRESS) {
        return X86_LM_INVALID_ADDRESS;
    }
    if (out_ps) {
        return (fpt << 12) | (pt_idx << 12) | offset;
    }

    union x86_pte pte;
    if (!ops->phys_read(&pte.v, (fpt << 12) + pt_idx * 8, 8)) {
        return X86_LM_INVALID_ADDRESS;
    }

    uint64_t fp = walk1_lm_pte(&pte, ops);
    if (fp == X86_LM_INVALID_ADDRESS) {
        return X86_LM_INVALID_ADDRESS;
    }
    return (fp << 12) | offset;
}