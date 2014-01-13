#if 0
#include "Platform.h"
#include "Quiz.h"
#include <stdio.h>
#include <stdlib.h>
#include "FRTOS1.h"
#include "CLS1.h"

#define check_list(n) \
  liste = gen_list##n(); \
  CLS1_SendStr("List ", CLS1_GetStdio()->stdOut); \
  CLS1_SendNum8u(n, CLS1_GetStdio()->stdOut); \
  CLS1_SendStr((has_loop(liste)) ? " Loop\r\n" : " No Loop\r\n", CLS1_GetStdio()->stdOut);

// Struktur ///////////////////////////////////////////////////
struct node_t {
  int val;
  struct node_t *next;
};

// Listen /////////////////////////////////////////////////////
static struct node_t* create_node(int val) {
  struct node_t *node = (struct node_t*) FRTOS1_pvPortMalloc(sizeof(node));
  node->val = val;
  node->next = NULL;
  
  return node;
}

static struct node_t* gen_list1() {
  struct node_t *first = create_node(1);
  struct node_t *second = create_node(5);
  
  first->next = second;
  
  return first;
}

static struct node_t* gen_list2() {
  struct node_t *first = create_node(1);
  struct node_t *second = create_node(5);
  
  first->next = second;
  second->next = first; // Loop!!
  
  return first;
}

static struct node_t* gen_list3() {
  struct node_t *first = create_node(1);
  struct node_t *second = create_node(5);
  struct node_t *third = create_node(10);
  
  first->next = second;
  second->next = third;
  third->next = first;    // Loop!!
  
  return first;
}

static struct node_t* gen_list4() {
  struct node_t *first = create_node(1);
  struct node_t *second = create_node(5);
  struct node_t *third = create_node(10);
  struct node_t *fourth = create_node(15);
  struct node_t *fifth = create_node(20);
  
  first->next = second;
  second->next = third;
  third->next = fourth;
  fourth->next = fifth;
  
  return first;
}

static struct node_t* gen_list5() {
  int i;
  struct node_t *first = create_node(1);
  struct node_t *cur, *prev;

  for (i=0, prev = first; i < 100; i++, prev = cur) {
    cur = create_node(i);
    prev->next = cur;
  }
  
  return first;
}

static struct node_t* gen_list6() {
  int i;
  struct node_t *first = create_node(1);
  struct node_t *cur, *prev;

  for (i=0, prev = first; i < 100; i++, prev = cur) {
    cur = create_node(i);
    prev->next = cur;
  }
  cur->next = first;  // Loop!!
  
  return first;
}

static struct node_t* gen_list7() {
  int i;
  struct node_t *first = create_node(1);
  struct node_t *cur, *prev, *mid;

  for (i=0, prev = first; i < 100; i++, prev = cur) {
    cur = create_node(i);
    if (i == 50) mid = cur;
    prev->next = cur;
  }
  cur->next = mid; // Loop!!

  return first;
}


// Die Magie //////////////////////////////////////////////////
#if 0
/* only works for true circular lists (e.g. no internal loop back) */
int has_loop(struct node_t *liste) {
  struct node_t *first;
  
  first = liste;
  for(;;) {
    if (liste==NULL) { /* end of list or empty list */
      return 0; /* no loop */
    }
    liste = liste->next;
    if (liste==first) { /* loop found */
      return 1; /* loop! */
    }
  }
}
#elif 0
/*!
 * \brief Checks if a linked list contains a loop.
 * Precondition: node ID's are > 0
 * @param liste List to check
 * @return 1 if list has loop, zero otherwise
 */
static int has_loop(struct node_t *liste) {
  struct node_t *curr;
  int hasLoop = 0;
  
  /* step 1: mark every node */
  curr = liste;
  while(curr!=NULL) {
    if (curr->val<0) { /* node already visited? There is a loop! */
      hasLoop = 1;
      break; /* exit loop */
    }
    curr->val = -curr->val; /* negate to mark node */
    curr = curr->next;
  }
  
  /* step 2: un-mark  */
  curr = liste;
  while(curr!=NULL) {
    if (curr->val>0) { /* finished un-marking */
      break;
    }
    curr->val = -curr->val; /* restore old value */
    curr = curr->next;
  }
  return hasLoop; /* no loop */
}
#else
/*!
 * \brief Checks if a linked list contains a loop.
 * Idea: move two pointers: a 'fast' and a 'slow' one. The fast one is twice as fast as the slow one.
 *       If there is a loop, both pointers will end up in that loop.
 *       And the fast one will 'hit' the slow one in this loop. 
 * \param list List to check
 * \return 1 if list has loop, zero otherwise
 */
static int has_loop(struct node_t *list) {
  struct node_t *slow, *fast;
  
  if (list==NULL || list->next==NULL) { /* special case */
    return 0; /* no loop */
  }
  slow = list;
  fast = list->next;
  while(slow!=fast) {
    if (slow!=NULL) {
      slow = slow->next;
    }
    if (fast!=NULL) {
      fast = fast->next;
      if (fast!=NULL) {
        fast = fast->next;
      }
    }
  }
  return slow!=NULL; /* loop */
}
#endif

// Los gehts //////////////////////////////////////////////////
int QUIZ_Run(void) {
  struct node_t *liste;
  
  CLS1_SendStr("Loop Detection\r\n", CLS1_GetStdio()->stdOut);
  
  check_list(1);
  check_list(2);
  check_list(3);
  check_list(4);
  check_list(5);
  check_list(6);
  check_list(7);
  
  return 0;
}

#if 0
void Number(void) 
{
  uint32_t sum[NUMBERS>>16];
  bool foundZero = FALSE;
  
  /* init */
  for(i=0;i<(NUMBERS>>16);i++) {
    sum[i]=0;
  }
  /* sum it! */
  while (!feof(file) && fread(&num, sizeof(int), 1, file) > 0) {
    sum[num>>16]+=(num&0xffff);
    if (num==0) {
      foundZero = TRUE;
    }
  }
  missing = 0;
  if (!foundZero) { /* special case */
    missing=0;
  } else {
    for(i=0;i<(NUMBERS>>16)-1;i++) {
      if (sum[i]!=(0xFFFF+1)/2*0xFFFF) {
        missing = sum[i]-(0xFFFF+1)/2*0xFFFF;
        break;
      }
    }
    if (missing==0) { /* check last index */
      if (sum[NUMBERS>>16]!=((NUMBERS&0xffff)+1)/2*(NUMBERS&0xffff)) {
        missing = sum[NUMBERS>>16]-((NUMBERS&0xffff)+1)/2*(NUMBERS&0xffff);
      }
    }
  }
}
#endif
#if 0
#include <stdio.h>
#include <stdlib.h>

#define NUMBERS 4000000

int main(int argc, char *argv[]) {
  FILE *file;
  unsigned int num, missing = 0;
  unsigned int min, max, mid, lower, upper;
  
  if (argc < 2) {
   printf("Missing Filename\n");
   exit(1);
  }
  
  // Open File
  file = fopen(argv[1], "r+");
  if (file == NULL) {
   printf("Datei '%s' nicht gefunden\n", argv[1]);
   exit(2);
  }
  
  /////////////////////////////////////////////////
  //     .
  //   ...
  // ..................  Add magic here
  //   ...
  //     .
  
  min = 0; max = NUMBERS; lower = 1; upper = 1;
  
  while ((lower+upper) > 1) {
    mid = (min + max)/2;
    lower = 0; upper = 0;
    
    //printf("min: %u  max: %u\n", min, max);
    
    rewind(file);
    while (!feof(file) && fread(&num, sizeof(int), 1, file) > 0) {
      if (num < min || num > max) {
  // ignore
      } else if (num <= mid) {
  lower++;
      } else {
  upper++;
      }
    }
    
    //printf("lower: %u  upper: %u\n", lower, upper);
    
    if (lower <= upper) {
      max = mid;
    } else {
      min = mid;
    }
    
  }
  
  fclose(file);
  
  missing = (lower == 1) ? max : min;
  
  // Solution
  printf("%s: Missing number: %u\n", argv[1], missing);

 return 0;
}
#endif
#endif /* 0 */