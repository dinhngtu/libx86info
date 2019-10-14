#pragma once

#include <stdbool.h>

#include "x86info/arch/msr.h"

bool x86_print_efer(const union x86_efer *efer);