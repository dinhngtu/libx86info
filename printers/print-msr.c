#include <stdio.h>

#include "x86info/printers/msr.h"
#include "x86info/util.h"

bool x86_print_efer(const union x86_efer *efer) {
    printf("efer=%016" PRIx64 "\n", efer->v);
    printf("        N L L   S\n");
    printf("        X M M   C\n");
    printf("        E A E   E\n");
    char sce = num2char(efer->f.sce);
    char lme = num2char(efer->f.lme);
    char lma = num2char(efer->f.lma);
    char nxe = num2char(efer->f.nxe);
    printf("        %c %c %c   %c\n", nxe, lma, lme, sce);
    printf("\n");
    return true;
}