#pragma once

#include <stdbool.h>

#include "x86info/arch/cr.h"

bool x86_print_cr0(const union x86_cr0 *cr0);
bool x86_print_cr3(const union x86_cr3 *cr3, const union x86_cr4 *cr4);
bool x86_print_cr4(const union x86_cr4 *cr4);