#pragma once

#include <inttypes.h>

union x86_cr0 {
    uint64_t v;
    struct {
        // Protection Enable
        int pe : 1;
        // Monitor Coprocessor
        int mp : 1;
        // Emulation
        int em : 1;
        // Task Switched
        int ts : 1;
        // Extension Type
        int et : 1;
        // Numeric Error
        int ne : 1;
        int rsvd1 : 10;
        // Write Protect
        int wp : 1;
        int rsvd2 : 1;
        // Alignment Mask
        int am : 1;
        int rsvd3 : 10;
        // Not Write-through
        int nw : 1;
        // Cache Disable
        int cd : 1;
        // Paging
        int pg : 1;
    } __attribute__((packed)) f;
};

union x86_cr3 {
    uint64_t v;
    union {
        struct {
            int ign1 : 3;
            // Page-level write-through
            int pwt : 1;
            // Page-level cache disable
            int pcd : 1;
            int ignored : 7;
            uint64_t fpml4 : 40;
            int rsvd1 : 12;
        } __attribute__((packed)) no_pcid;
        struct {
            uint64_t pcid : 12;
            uint64_t fpml4 : 40;
            int rsvd1 : 12;
        } __attribute__((packed)) pcid;
    } f;
};

union x86_cr4 {
    uint64_t v;
    struct {
        // Virtual-8086 Mode Extensions
        int vme : 1;
        // Protected-Mode Virtual Interrupts
        int pvi : 1;
        // Time Stamp Disable
        int tsd : 1;
        // Debugging Extensions
        int de : 1;
        // Page Size Extensions
        int pse : 1;
        // Physical Address Extensions
        int pae : 1;
        // Machine-Check Enable
        int mce : 1;
        // Page Global Enable
        int pge : 1;
        // Performance-Monitoring Counter Enable
        int pce : 1;
        // Operating System Support for FXSAVE and FXRSTOR instructions
        int osfxsr : 1;
        // Operating System Support for Unmasked SIMD Floating-Point Exceptions
        int osxmmexcpt : 1;
        // User-Mode Instruction Prevention
        int umip : 1;
        int rsvd1 : 1;
        // VMX-Enable Bit
        int vmxe : 1;
        // SMX-Enable Bit
        int smxe : 1;
        int rsvd2 : 1;
        // FSGSBASE-Enable Bit
        int fsgsbase : 1;
        // PCID-Enable Bit
        int pcide : 1;
        // XSAVE and Processor Extended States-Enable Bit
        int osxsave : 1;
        int rsvd3 : 1;
        // SMEP-Enable Bit
        int smep : 1;
        // SMAP-Enable Bit
        int smap : 1;
        // Protection-Key-Enable Bit
        int pke : 1;
        uint64_t rsvd4 : 41;
    } __attribute__((packed)) f;
};