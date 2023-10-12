#ifndef __GCOV_PUBLIC_H__
#define __GCOV_PUBLIC_H__

struct gcov_info;
typedef long long gcov_type;

void __gcov_init(struct gcov_info *info);
#if __GNUC__ < 11
  void __gcov_flush(void);
#else
  void __gcov_dump(void);
#endif
void __gcov_merge_add(gcov_type *counters, unsigned int n_counters);
unsigned int convert_to_gcda(char *buffer, struct gcov_info *info);

#endif
