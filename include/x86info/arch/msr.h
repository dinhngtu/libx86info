#pragma once

#include <inttypes.h>

union x86_efer {
    uint64_t v;
    struct {
        // SYSCALL Enable
        int sce : 1;
        int rsvd1 : 7;
        // IA-32e Mode Enable
        int lme : 1;
        int rsvd2 : 1;
        // IA-32e Mode Active
        int lma : 1;
        // Execute Disable Bit Enable
        int nxe : 1;
        uint64_t rsvd3 : 52;
    } __attribute__((packed)) f;
};