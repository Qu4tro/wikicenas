#ifndef TTREE_H
#define TTREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct TTNode TTNode;

TTNode* create_node(char w, bool t);
TTNode* insert_node(const char *string, TTNode *node);
TTNode *find_node(TTNode* _node, const char *string);
bool contains(TTNode* _node, const char *string);

char** find_by_prefix(TTNode* root, const char *pattern);

#endif
