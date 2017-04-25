#ifndef TOPN_H
#define TOPN_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pqueue.h"

typedef struct PriQueue* PriQueue;
typedef struct PriQueue PriorityQueue;

PriQueue pqinit(int capacity);

void enqueue(PriQueue pq, long val, pqueue_pri_t pri);

long* peek_n(PriQueue pq, int n);
long* peek_all(PriQueue pq);

#endif
