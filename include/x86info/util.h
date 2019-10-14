#pragma once

#include <inttypes.h>

static inline char num2char(uint64_t val) {
    return val ? '1' : '0';
}

static inline uint64_t mask(uint64_t val, int pos) {
    return val & (1 << pos);
}

static inline char bit2char(uint64_t val, int pos) {
    return num2char(mask(val, pos));
}