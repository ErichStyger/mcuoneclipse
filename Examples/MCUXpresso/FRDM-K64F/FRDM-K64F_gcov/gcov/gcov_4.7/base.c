/*
 * This code is based on the GCOV-related code of the Linux kernel (kept under
 * "kernel/gcov"). It basically uses the convert_to_gcda function to generate
 * the .gcda files information upon application completion, and dump it on the
 * host filesystem via GDB scripting.
 */


/*
 *  This code maintains a list of active profiling data structures.
 *
 *    Copyright IBM Corp. 2009
 *    Author(s): Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *
 *    Uses gcc-internal data definitions.
 *    Based on the gcov-kernel patch by:
 *		 Hubertus Franke <frankeh@us.ibm.com>
 *		 Nigel Hinds <nhinds@us.ibm.com>
 *		 Rajan Ravindran <rajancr@us.ibm.com>
 *		 Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *		 Paul Larson
 */
#include "gcov_support.h"
#if GCOV_USE_GCOV_4_7

#include <gcov_4.7/gcov_public.h>
#include <gcov_4.7/gcov.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tagGcovInfo {
    struct gcov_info *info;
    struct tagGcovInfo *next;
} GcovInfo;
GcovInfo *headGcov = NULL;



#include "McuUtility.h"

/*
 * helper method so that GDB can break here
 *  set $filename = tmp->info->filename
    set $dataBegin = buffer
    set $dataEnd = buffer + sizeInBytes
    eval "dump binary memory %s 0x%lx 0x%lx", $dataBegin, $dataEnd, $filename
    eval "echo dump binary memory %s 0x%lx 0x%lx", $dataBegin, $dataEnd, $filename
 * dump binary memory "C:\\Erich Styger\\Data\GitRepos\McuOnEclipse\Examples\MCUXpresso\FRDM-K64F//FRDM-K64F_gcov//Debug//source//pin_mux.gcda" 0x200026E8 0x200026F4
 */
void coverage_helper_breakme(struct gcov_info *info, uint32_t startAddr, size_t size) {
#if 0
  static unsigned char gdbBuf[512];

  McuUtility_strcpy(gdbBuf, sizeof(gdbBuf), (unsigned char*)"dump binary memory \"");
  McuUtility_strcat(gdbBuf, sizeof(gdbBuf), (unsigned char*)gcov_info_filename(info));
  McuUtility_strcat(gdbBuf, sizeof(gdbBuf), (unsigned char*)"\" 0x");
  McuUtility_strcatNum32Hex(gdbBuf, sizeof(gdbBuf), startAddr);
  McuUtility_strcat(gdbBuf, sizeof(gdbBuf), (unsigned char*)" 0x");
  McuUtility_strcatNum32Hex(gdbBuf, sizeof(gdbBuf), endAddr);
#else
  FILE *file = NULL;
  const char *fileName;

  fileName = gcov_info_filename(info);
  file = fopen (fileName, "wb");
  if (file!=NULL) {
    (void)fwrite((unsigned char*)startAddr, size, 1, file);
    fclose(file);
  }
#endif
}

/*
 * __gcov_init is called by gcc-generated constructor code for each object
 * file compiled with -fprofile-arcs.
 */
void __gcov_init(struct gcov_info *info)
{
    printf(
            "__gcov_init called for %s!\n", 
            gcov_info_filename(info));
    fflush(stdout);
    GcovInfo *newHead = malloc(sizeof(GcovInfo));
    if (!newHead) {
        puts("Out of memory error!");
        exit(1);
    }
    newHead->info = info;
    newHead->next = headGcov;
    headGcov = newHead;
}

void __gcov_flush(void)
{
    GcovInfo *tmp = headGcov;
    while(tmp) {
        char *buffer;
        unsigned sizeInBytes = convert_to_gcda(NULL, tmp->info);
        buffer = malloc(sizeInBytes);
        if (!buffer) {
            puts("Out of memory!");
            exit(1);
        }
        convert_to_gcda(buffer, tmp->info);
        printf("Sending %6d bytes for %s\n", sizeInBytes, gcov_info_filename(tmp->info));
        coverage_helper_breakme(tmp->info, (uint32_t)buffer, sizeInBytes);
        free(buffer);
        tmp = tmp->next;
    }
}

void __gcov_merge_add(gcov_type *counters, unsigned int n_counters)
{
    puts("__gcov_merge_add isn't called, right? Right? RIGHT?");
    fflush(stdout);
    exit(1);
}

#endif /* GCOV_USE_GCOV_4_7 */
