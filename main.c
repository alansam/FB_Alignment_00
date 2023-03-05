#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>

typedef unsigned char byte;
typedef struct node1 node1;
struct node1 {
  int id;
  union {
    double xx[4];
    struct {
      double x1;
      double x2;
      double x3;
      double x4;
    };
  };
  double length;
  node1 * next_node;
};

typedef struct node2 node2;
struct __attribute__((__packed__)) node2 {
  union {
    double xx[4];
    struct {
      double x1;
      double x2;
      double x3;
      double x4;
    };
  };
  double length;
  node2 * next_node;
  int id;
};

void n1(node1 *, size_t, size_t);
void n2(node2 *, size_t, size_t);
void s1(node1 *, bool);
void s2(node2 *, bool);

/*
 *  MARK:  main()
 */
int main(int argc, char const * argv[]) {
  node1 anchor1[] = {
    {
      .id = 100,
      .x1 = 1.1, .x2 = 1.2, .x3 = 1.3, .x4 = 1.4,
      .length = 10.24,
      .next_node = NULL,
    },
    {
      .id = 101,
      .xx = { 1.101, 1.201, 1.301, 1.401, },
      .length = 10.24 * 2.,
      .next_node = NULL,
    },
  };
  size_t const anchor1_e = sizeof anchor1 / sizeof *anchor1;
  size_t const anchor1_sz = sizeof anchor1[0];
  size_t const cumlt1 = sizeof anchor1[0].id
                      + sizeof anchor1[0].xx
                      + sizeof anchor1[0].length
                      + sizeof anchor1[0].next_node;
  anchor1[0].next_node = &anchor1[1];
  anchor1[1].next_node = &anchor1[0];

  node2 anchor2[] = {
    {
      .id = 200,
      .xx = { 2.102, 2.202, 2.302, 2.402, },
      .length = 40.96,
      .next_node = NULL,
    },
    {
      .id = 202,
      .x1 = 2.1, .x2 = 2.2, .x3 = 2.3, .x4 = 2.4,
      .length = 40.96 * 2.,
      .next_node = NULL,
    },
  };
  size_t const anchor2_e  = sizeof anchor2 / sizeof *anchor2;
  size_t const anchor2_sz = sizeof anchor2[0];
  size_t const cumlt2 = sizeof anchor2[0].xx
                      + sizeof anchor2[0].length
                      + sizeof anchor2[0].next_node
                      + sizeof anchor2[0].id;
  anchor2[0].next_node = &anchor2[1];
  anchor2[1].next_node = &anchor2[0];

  for (size_t e_ = 0ul; e_ < anchor1_e; ++e_) {
    n1(&anchor1[e_], anchor1_sz, cumlt1);
  }
  for (size_t e_ = 0ul; e_ < anchor2_e; ++e_) {
    n2(&anchor2[e_], anchor2_sz, cumlt2);
  }

  s1(&anchor1[0], true);
  s1(&anchor1[1], false);
  s2(&anchor2[0], false);
  s2(&anchor2[1], true);

  return 0;
}

/*
 *  MARK:  n1()
 */
void n1(node1 * nd1, size_t nd1_sz, size_t cumlt1) {

  puts("~~~~~~~~~~ anchor1: ~~~~~~~~~~");

  printf("sizes  : %5zu,%5zu\n", nd1_sz, cumlt1);
  printf("alignof: %5zu\n", alignof(node1));
  printf("starting addr: %18p\n", nd1);
  putchar('\n');
  printf(".id          : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->id,
         sizeof(nd1->id));
  printf(".xx          : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->xx,
         sizeof(nd1->xx));
  printf("[\n");
  printf(".x1          : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->x1,
         sizeof(nd1->x1));
  printf(".x2          : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->x2,
         sizeof(nd1->x2));
  printf(".x3          : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->x3,
         sizeof(nd1->x3));
  printf(".x4          : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->x4,
         sizeof(nd1->x4));
  printf("]\n");
  printf(".length      : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->length,
         sizeof(nd1->length));
  printf(".next_node   : %1$18p:%2$5zu, %2$04zx\n",
         &nd1->next_node,
         sizeof(nd1->next_node));
  printf("cumulative sz: %1$24zu, %1$04zx\n",
         cumlt1);
  printf("calc sz      : %1$24zu, %1$04zx\n",
         nd1_sz);
  printf("last byte    : %18p\n",
         (uint8_t *) &nd1->next_node + sizeof(nd1->next_node) - 1);
  printf("next byte    : %18p\n",
         (uint8_t *) &nd1->next_node + sizeof(nd1->next_node));
  putchar('\n');

  puts("~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
  puts("addresses & sizes:");
  printf("%1$18p\n%2$18p\n%3$18zx %3$5zu\n",
         (uint8_t *) nd1 + sizeof(node1),
         nd1,
         sizeof(node1));
  printf("%1$18p\n%2$18p\n%3$18zx %3$5zu\n",
         (uint8_t *) nd1 + sizeof(node1) - 1,
         nd1,
         sizeof(node1) - 1);
  printf("%1$5zu, %1$04zx\n",
         nd1 + sizeof(node1) - nd1);
  putchar('\n');

  return;
}

/*
 *  MARK:  n1()
 */
void n2(node2 * nd2, size_t nd2_sz, size_t cumlt2) {

  puts("~~~~~~~~~~ anchor2: ~~~~~~~~~~");

  printf("sizes  : %5zu,%5zu\n", nd2_sz, cumlt2);
  printf("alignof: %5zu\n", alignof(node2));
  printf("starting addr: %18p\n", nd2);
  putchar('\n');
  printf(".xx          : %1$18p:%2$5zu, %2$04zx\n",
         (void *) &nd2->xx,
         sizeof nd2->xx);
  printf("[\n");
  printf(".x1          : %1$18p:%2$5zu, %2$04zx\n",
         &nd2->x1,
         sizeof(nd2->x1));
  printf(".x2          : %1$18p:%2$5zu, %2$04zx\n",
         &nd2->x2,
         sizeof(nd2->x2));
  printf(".x3          : %1$18p:%2$5zu, %2$04zx\n",
         &nd2->x3,
         sizeof(nd2->x3));
  printf(".x4          : %1$18p:%2$5zu, %2$04zx\n",
         &nd2->x4,
         sizeof(nd2->x4));
  printf("]\n");
  printf(".length      : %1$18p:%2$5zu, %2$04zx\n",
         (void *) &nd2->length,
         sizeof nd2->length);
  printf(".next_node   : %1$18p:%2$5zu, %2$04zx\n",
         (void *) &nd2->next_node,
         sizeof nd2->next_node);
  printf(".id          : %1$18p:%2$5zu, %2$04zx\n",
         (void *) &nd2->id,
         sizeof nd2->id);
  printf("cumulative sz: %1$24zu, %1$04zx\n",
         cumlt2);
  printf("calc sz      : %1$24zu, %1$04zx\n",
         nd2_sz);
  printf("last byte    : %18p\n",
         (uint8_t *) &nd2->id + sizeof nd2->id - 1);
  printf("next byte    : %18p\n",
         (uint8_t *) &nd2->id + sizeof nd2->id);
  putchar('\n');

  puts("~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
  puts("addresses & sizes:");
  printf("%1$18p\n%2$18p\n%3$18zx %3$5zu\n",
         (uint8_t *) nd2 + sizeof(node2),
         nd2,
         sizeof(node2));
  printf("%1$18p\n%2$18p\n%3$18zx %3$5zu\n",
         (uint8_t *) nd2 + sizeof(node2) - 1,
         nd2,
         sizeof(node2) - 1);
  printf("%1$5zu, %1$04zx\n",
         nd2 + sizeof(node2) - nd2);
  putchar('\n');

  return;
}

/*
 *  MARK:  s1()
 */
void s1(node1 * nd1, bool array) {

  puts("~~~~~~~~~~ anchor1: ~~~~~~~~~~");

  printf("address         : %p\n", nd1);
  printf("alignment       : %6zu\n", alignof(node1));
  printf("ID              : %6d\n", nd1->id);
  if (array) {
    printf("xx[]            : ");
    for (size_t x_ = 0ul; x_ < 4; ++x_) {
      printf("%6.3f", nd1->xx[x_]);
    }
  }
  else {
    printf("x1 through x4]  : ");
    printf("%6.3f", nd1->x1);
    printf("%6.3f", nd1->x2);
    printf("%6.3f", nd1->x3);
    printf("%6.3f", nd1->x4);
  }
  putchar('\n');
  printf("length          : %6.3f\n", nd1->length);
  printf("next_node       : %p\n", nd1->next_node);
  putchar('\n');

  return;
}

/*
 *  MARK:  s1()
 */
void s2(node2 * nd2, bool array) {
  puts("~~~~~~~~~~ anchor2: ~~~~~~~~~~");

  printf("address         : %p\n", nd2);
  printf("alignment       : %6zu\n", alignof(node2));
  printf("ID              : %6d\n", nd2->id);
  if (array) {
    printf("xx[]            : ");
    for (size_t x_ = 0ul; x_ < 4; ++x_) {
      printf("%6.3f", nd2->xx[x_]);
    }
  }
  else {
    printf("x1 through x4]  : ");
    printf("%6.3f", nd2->x1);
    printf("%6.3f", nd2->x2);
    printf("%6.3f", nd2->x3);
    printf("%6.3f", nd2->x4);
  }

  putchar('\n');
  printf("length          : %6.3f\n", nd2->length);
  printf("next_node       : %p\n", nd2->next_node);
  putchar('\n');

  return;
}
