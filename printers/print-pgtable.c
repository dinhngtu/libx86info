#include <stdio.h>

#include "x86info/printers/pgtable.h"
#include "x86info/util.h"

bool x86_print_pml4e(const union x86_pml4e *pml4e) {
    printf("pml4=%016" PRIx64 "\n", pml4e->v);
    char present = num2char(pml4e->f.present);
    printf("      X                ACWURP\n");
    printf("      D pdpt______      DTSW \n");
    if (pml4e->f.present) {
        uint64_t fpdpt = pml4e->f.fpdpt;
        char rw = pml4e->f.rw ? 'w' : 'r';
        char us = pml4e->f.us ? 'u' : 's';
        char pwt = num2char(pml4e->f.pwt);
        char pcd = num2char(pml4e->f.pcd);
        char a = num2char(pml4e->f.a);
        char xd = pml4e->f.xd ? '1' : 'x';
        printf("      %c %010" PRIx64 "     %c%c%c%c%c%c\n", xd, fpdpt, a, pcd, pwt, us, rw, present);
        printf("\n");
    } else {
        printf("      ? ??????????     ?????0\n");
        printf("\n");
    }
    return 1;
}

bool x86_print_pdpte(const union x86_pdpte *pdpte) {
    printf("pdpt=%016" PRIx64 "\n", pdpte->v);
    char present = num2char(pdpte->f.present);
    printf("      X            PGPDACWURP\n");
    printf("      D pd________ A S  DTSW \n");
    if (pdpte->f.present) {
        char rw = pdpte->f.rw ? 'w' : 'r';
        char us = pdpte->f.us ? 'u' : 's';
        char pwt = num2char(pdpte->f.pwt);
        char pcd = num2char(pdpte->f.pcd);
        char a = num2char(pdpte->f.a);
        char d = num2char(pdpte->f.d);
        char ps = num2char(pdpte->f.ps);
        if (pdpte->f.ps) {
            char g = num2char(pdpte->f._ps.ps1gb.g);
            char pat = num2char(pdpte->f._ps.ps1gb.pat);
            uint64_t fp = pdpte->f._ps.ps1gb.a1gb << 18;
            char xd = pdpte->f._ps.ps1gb.xd ? '1' : 'x';
            printf(
                "      %c %010" PRIx64 " %c%c%c%c%c%c%c%c%c%c\n", xd, fp, pat, g, ps, d, a, pcd, pwt, us, rw, present);
            printf("\n");
        } else {
            uint64_t fpd = pdpte->f._ps.pd.fpd;
            char xd = pdpte->f._ps.pd.xd ? '1' : 'x';
            printf("      %c %010" PRIx64 " XX%c%c%c%c%c%c%c%c\n", xd, fpd, ps, d, a, pcd, pwt, us, rw, present);
            printf("\n");
        }
    } else {
        printf("      ? ?????????? ?????????0\n");
        printf("\n");
    }
    return true;
}

bool x86_print_pde(const union x86_pde *pde) {
    printf("pde =%016" PRIx64 "\n", pde->v);
    char present = num2char(pde->f.present);
    printf("      X            PGPDACWURP\n");
    printf("      D pt________ A S  DTSW \n");
    if (pde->f.present) {
        char rw = pde->f.rw ? 'w' : 'r';
        char us = pde->f.us ? 'u' : 's';
        char pwt = num2char(pde->f.pwt);
        char pcd = num2char(pde->f.pcd);
        char a = num2char(pde->f.a);
        char d = num2char(pde->f.d);
        char ps = num2char(pde->f.ps);
        if (pde->f.ps) {
            char g = num2char(pde->f._ps.ps2mb.g);
            char pat = num2char(pde->f._ps.ps2mb.pat);
            uint64_t fp = pde->f._ps.ps2mb.a2mb << 9;
            char xd = pde->f._ps.ps2mb.xd ? '1' : 'x';
            printf(
                "      %c %010" PRIx64 " %c%c%c%c%c%c%c%c%c%c\n", xd, fp, pat, g, ps, d, a, pcd, pwt, us, rw, present);
            printf("\n");
        } else {
            uint64_t fpt = pde->f._ps.pt.fpt;
            char xd = pde->f._ps.pt.xd ? '1' : 'x';
            printf("      %c %010" PRIx64 " XX%c%c%c%c%c%c%c%c\n", xd, fpt, ps, d, a, pcd, pwt, us, rw, present);
            printf("\n");
        }
    } else {
        printf("      ? ?????????? ?????????0\n");
        printf("\n");
    }
    return true;
}

bool x86_print_pte(const union x86_pte *pte) {
    printf("pte =%016" PRIx64 "\n", pte->v);
    char present = num2char(pte->f.present);
    printf("      X             GPDACWURP\n");
    printf("      D frame_____   A  DTSW \n");
    if (pte->f.present) {
        char rw = pte->f.rw ? 'w' : 'r';
        char us = pte->f.us ? 'u' : 's';
        char pwt = num2char(pte->f.pwt);
        char pcd = num2char(pte->f.pcd);
        char a = num2char(pte->f.a);
        char d = num2char(pte->f.d);
        char pat = num2char(pte->f.pat);
        char g = num2char(pte->f.g);
        uint64_t fp = pte->f.fp;
        char xd = pte->f.xd ? '1' : 'x';
        printf("      %c %010" PRIx64 "  %c%c%c%c%c%c%c%c%c\n", xd, fp, g, pat, d, a, pcd, pwt, us, rw, present);
        printf("\n");
    } else {
        printf("      ? ?????????? ?????????0\n");
        printf("\n");
    }
    return true;
}