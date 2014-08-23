#include <string.h>
#include <stdio.h>

int i;
char buf[32];

int main(void) {
  strcpy(buf, "hello");
  strcat(buf, "world");
  i = strlen(buf);
  sprintf(buf, "hello");
  for(;;) {
    i++;
  }
  return 0; /* should not get here */
}
