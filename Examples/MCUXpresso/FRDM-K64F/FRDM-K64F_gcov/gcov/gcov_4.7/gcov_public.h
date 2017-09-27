#ifndef __GCOV_PUBLIC_H__
#define __GCOV_PUBLIC_H__

struct gcov_info;
typedef long long gcov_type;

void __gcov_init(struct gcov_info *info);
void __gcov_flush(void);
void __gcov_merge_add(gcov_type *counters, unsigned int n_counters);
unsigned int convert_to_gcda(char *buffer, struct gcov_info *info);

#endif
