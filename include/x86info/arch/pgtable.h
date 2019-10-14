#pragma once

#include <inttypes.h>

union x86_pml4e {
    uint64_t v;
    struct {
        // Present
        int present : 1;
        // Read/write
        int rw : 1;
        // User/supervisor
        int us : 1;
        // Page-level write-through
        int pwt : 1;
        // Page-level cache disable
        int pcd : 1;
        // Accessed
        int a : 1;
        int ign1 : 1;
        // Reserved (PS)
        int rsvd1 : 1;
        int ign2 : 4;
        uint64_t fpdpt : 40;
        int ign3 : 11;
        // Execute-disable
        int xd : 1;
    } __attribute__((packed)) f;
};

union x86_pdpte {
    uint64_t v;
    struct {
        // Present
        int present : 1;
        // Read/write
        int rw : 1;
        // User/supervisor
        int us : 1;
        // Page-level write-through
        int pwt : 1;
        // Page-level cache disable
        int pcd : 1;
        // Accessed
        int a : 1;
        // Dirty
        int d : 1;
        // Page size
        int ps : 1;
        union {
            struct {
                // Global
                int g : 1;
                int ign1 : 3;
                // PAT
                int pat : 1;
                int rsvd1 : 17;
                uint64_t a1gb : 22;
                int ign2 : 7;
                // Protection key
                int pk : 4;
                // Execute-disable
                int xd : 1;
            } __attribute__((packed)) ps1gb;
            struct {
                int ign1 : 4;
                uint64_t fpd : 40;
                int ign2 : 11;
                // Execute-disable
                int xd : 1;
            } __attribute__((packed)) pd;
        } _ps;
    } __attribute__((packed)) f;
};

union x86_pde {
    uint64_t v;
    struct {
        // Present
        int present : 1;
        // Read/write
        int rw : 1;
        // User/supervisor
        int us : 1;
        // Page-level write-through
        int pwt : 1;
        // Page-level cache disable
        int pcd : 1;
        // Accessed
        int a : 1;
        // Dirty
        int d : 1;
        // Page size
        int ps : 1;
        union {
            struct {
                // Global
                int g : 1;
                int ign1 : 3;
                // PAT
                int pat : 1;
                int rsvd1 : 8;
                uint64_t a2mb : 31;
                int ign2 : 7;
                // Protection key
                int pk : 4;
                // Execute-disable
                int xd : 1;
            } __attribute__((packed)) ps2mb;
            struct {
                int ign1 : 4;
                uint64_t fpt : 40;
                int ign2 : 11;
                // Execute-disable
                int xd : 1;
            } __attribute__((packed)) pt;
        } _ps;
    } __attribute__((packed)) f;
};

union x86_pte {
    uint64_t v;
    struct {
        // Present
        int present : 1;
        // Read/write
        int rw : 1;
        // User/supervisor
        int us : 1;
        // Page-level write-through
        int pwt : 1;
        // Page-level cache disable
        int pcd : 1;
        // Accessed
        int a : 1;
        // Dirty
        int d : 1;
        // PAT
        int pat : 1;
        // Global
        int g : 1;
        int ign1 : 3;
        uint64_t fp : 40;
        int ign2 : 7;
        // Protection key
        int pk : 4;
        // Execute-disable
        int xd : 1;
    } __attribute__((packed)) f;
};