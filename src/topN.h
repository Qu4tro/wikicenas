#ifndef TOPN_H
#define TOPN_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pqueue.h"

typedef struct PriorityQueue* PriorityQueue;

PriorityQueue pqinit(int capacity);

void enqueue(PriorityQueue pq, long val, pqueue_pri_t pri);

long* peek_n(PriorityQueue pq, int n);
long* peek_all(PriorityQueue pq);

#endif
