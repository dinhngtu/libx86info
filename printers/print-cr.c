#include <stdio.h>

#include "x86info/printers/cr.h"
#include "x86info/util.h"

bool x86_print_cr0(const union x86_cr0 *cr0) {
    printf("cr0 =%016" PRIx64 "\n", cr0->v);
    printf("        PCN    AW    NETEMP\n");
    printf("        GDW    MP    ETSMPE\n");
    char pe = num2char(cr0->f.pe);
    char mp = num2char(cr0->f.mp);
    char em = num2char(cr0->f.em);
    char ts = num2char(cr0->f.ts);
    char et = num2char(cr0->f.et);
    char ne = num2char(cr0->f.ne);

    char wp = num2char(cr0->f.wp);
    char am = num2char(cr0->f.am);

    char nw = num2char(cr0->f.nw);
    char cd = num2char(cr0->f.cd);
    char pg = num2char(cr0->f.pg);
    printf("        %c%c%c    %c%c    %c%c%c%c%c%c\n", pg, cd, nw, am, wp, ne, et, ts, em, mp, pe);
    printf("\n");
    return true;
}

bool x86_print_cr3(const union x86_cr3 *cr3, const union x86_cr4 *cr4) {
    printf("cr3 =%016" PRIx64 "\n", cr3->v);
    if (cr4->f.pcide) {
        uint64_t fpml4 = cr3->f.pcid.fpml4;
        uint64_t pcid = cr3->f.pcid.pcid & 0xfff;
        printf("        pml4______     PCID\n");
        printf("        %010" PRIx64 "     %03" PRIx64 "\n", fpml4, pcid);
        printf("\n");
    } else {
        uint64_t fpml4 = cr3->f.no_pcid.fpml4;
        char pwt = num2char(cr3->f.no_pcid.pwt);
        char pcd = num2char(cr3->f.no_pcid.pcd);
        printf("                        CW\n");
        printf("        pml4______      DT\n");
        printf("        %010" PRIx64 "      %c%c\n", fpml4, pcd, pwt);
        printf("\n");
    }
    return true;
}

bool x86_print_cr4(const union x86_cr4 *cr4) {
    printf("cr4 =%016" PRIx64 "\n", cr4->v);
    printf("        PSS XPF SV UXFPPMPPDTPV\n");
    printf("        KAE SCG MM IMXCGCASESVM\n");
    printf("        EPP VIB XX PMSEEEEE DIE\n");
    char vme = num2char(cr4->f.vme);
    char pvi = num2char(cr4->f.pvi);
    char tsd = num2char(cr4->f.tsd);
    char de = num2char(cr4->f.de);
    char pse = num2char(cr4->f.pse);
    char pae = num2char(cr4->f.pae);
    char mce = num2char(cr4->f.mce);
    char pge = num2char(cr4->f.pge);
    char pce = num2char(cr4->f.pce);
    char osfxsr = num2char(cr4->f.osfxsr);
    char osxmmexcpt = num2char(cr4->f.osxmmexcpt);
    char umip = num2char(cr4->f.umip);

    char vmxe = num2char(cr4->f.vmxe);
    char smxe = num2char(cr4->f.smxe);

    char fsgsbase = num2char(cr4->f.fsgsbase);
    char pcide = num2char(cr4->f.pcide);
    char osxsave = num2char(cr4->f.osxsave);

    char smep = num2char(cr4->f.smep);
    char smap = num2char(cr4->f.smap);
    char pke = num2char(cr4->f.pke);
    printf(
        "        %c%c%c %c%c%c %c%c %c%c%c%c%c%c%c%c%c%c%c%c\n",
        pke,
        smap,
        smep,
        osxsave,
        pcide,
        fsgsbase,
        smxe,
        vmxe,
        umip,
        osxmmexcpt,
        osfxsr,
        pce,
        pge,
        mce,
        pae,
        pse,
        de,
        tsd,
        pvi,
        vme);
    printf("\n");
    return true;
}