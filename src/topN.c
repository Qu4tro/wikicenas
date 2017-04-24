#include "topN.h"

typedef struct node_t {
    pqueue_pri_t pri;
    long val;
    size_t pos;
} node_t;

struct PriorityQueue {
    int capacity;
    node_t** nodes;
    pqueue_t* minpq;
    pqueue_t* maxpq;
};

int cmp_pri_min(pqueue_pri_t next, pqueue_pri_t curr) {
  return (next > curr);
}

int cmp_pri_max(pqueue_pri_t next, pqueue_pri_t curr) {
  return !(cmp_pri_min(next, curr));
}

pqueue_pri_t get_pri(void *a) { return ((node_t *)a)->pri; }

void set_pri(void *a, pqueue_pri_t pri) { ((node_t *)a)->pri = pri; }

size_t get_pos(void *a) { return ((node_t *)a)->pos; }

void set_pos(void *a, size_t pos) { ((node_t *)a)->pos = pos; }

PriorityQueue pqinit(int capacity) {

    PriorityQueue pq;
    node_t** ns = malloc((capacity + 1) * sizeof(node_t));

    if (!(pq = malloc(sizeof(struct PriorityQueue))))
        return NULL;

    pq -> capacity = capacity;
    pq -> minpq =
        pqueue_init(10, cmp_pri_min, get_pri, set_pri, get_pos, set_pos);
    pq -> maxpq =
        pqueue_init(10, cmp_pri_max, get_pri, set_pri, get_pos, set_pos);
    pq -> nodes = ns;


    return pq;
}

long* peek_all(PriorityQueue pq){
    return peek_n(pq, pqueue_size(pq -> minpq));
}

long* peek_n(PriorityQueue pq, int n){
    long* vals = malloc(n * sizeof(long));
    node_t** nodes = malloc(n * sizeof(node_t));
    for(int i = 0; i < n; i++){
        nodes[i] = pqueue_pop(pq -> maxpq);
        vals[i] = nodes[i] -> val;
    }
    for(int i = 0; i < n; i++){
        pqueue_insert(pq -> maxpq, nodes[i]);
    }

    free(nodes);
    return vals;
}


void enqueue(PriorityQueue pq, long val, pqueue_pri_t pri){
    int size = pqueue_size(pq -> minpq);
    pq -> nodes[size] = malloc(sizeof(node_t));
    pq -> nodes[size] -> pri = pri;
    pq -> nodes[size] -> val = val;
    pqueue_insert(pq -> minpq, pq -> nodes[size]);
    pqueue_insert(pq -> maxpq, pq -> nodes[size]);

    if (size + 1 > pq -> capacity){
        pq -> nodes[size] = pqueue_pop(pq -> minpq);
        int r = pqueue_remove(pq -> minpq, pq -> nodes[size]);
        assert(r == 0);
    }
}