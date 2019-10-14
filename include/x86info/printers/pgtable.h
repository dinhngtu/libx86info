#pragma once

#include <stdbool.h>

#include "x86info/arch/cr.h"
#include "x86info/arch/pgtable.h"

bool x86_print_pml4e(const union x86_pml4e *pml4e);
bool x86_print_pdpte(const union x86_pdpte *pdpte);
bool x86_print_pde(const union x86_pde *pde);
bool x86_print_pte(const union x86_pte *pte);