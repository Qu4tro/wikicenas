#include "tst.h"

struct TTNode {
  char word;
  struct TTNode *lChild;
  struct TTNode *rChild;
  struct TTNode *mChild;
  bool endWord;
};

TTNode *create_node(char w, bool t) {
    TTNode *_node = (struct TTNode *)malloc(sizeof(struct TTNode));
    _node->word = w;
    _node->lChild = NULL;
    _node->mChild = NULL;
    _node->rChild = NULL;
    _node-> endWord = t;

    return _node;
}

TTNode *insert_node(const char *string, TTNode *node) {
    unsigned i = strlen(string);

    if (NULL == node)
        node = create_node(string[0], false);

    if (string[0] < node->word)
        node->lChild = insert_node(string, node->lChild);

    else if (string[0] > node->word)
        node->rChild = insert_node(string, node->rChild);

    else {

        if (i == 1) {
            node-> endWord = true;
            return node;
        } else
            node->mChild = insert_node(++string, node->mChild);
    }

    return node;
}

TTNode* find_node(TTNode* _node, const char *string) {
    unsigned i = 0;

    while (i < strlen(string)) {
        if (NULL == _node)
            break;
        if (string[i] < _node->word)
            _node = _node->lChild;
        else if (string[i] > _node->word)
            _node = _node->rChild;
        else {
            if (i++ == strlen(string) - 1)
                return _node;
            else
                _node = _node->mChild;
        }
    }

    return NULL;
}

bool contains(TTNode* _node, const char *string) {
    TTNode* found = find_node(_node, string);
    return found -> endWord;
}

void print_array(char** strings){
    for(int i = 0; strings[i]; i++){
        printf("%s\n", strings[i]);
    }
}

void deep_search(const char *pattern, TTNode *start, GList** l) {
    if (start -> endWord){
        char *_pattern = malloc(strlen(pattern) + 2);
        sprintf(_pattern, "%s%c", pattern, start->word);
        *l = g_list_append(*l, _pattern);
    }

    if (start -> mChild != NULL) {
        char *_pattern = malloc(strlen(pattern) + 2);
        sprintf(_pattern, "%s%c", pattern, start->word);
        deep_search(_pattern, start->mChild, l);
    }

    if (start -> rChild != NULL)
        deep_search(pattern, start->rChild, l);

    if (start -> lChild != NULL)
        deep_search(pattern, start->lChild, l);
}

char** find_by_prefix(TTNode* root, const char *pattern) {
    TTNode *current = find_node(root, pattern);
    if (NULL == current){
        return NULL;
    }

    GList* list = NULL;
    deep_search(pattern, current->mChild, &list);

    char** TODO = malloc(sizeof(char*) * (1 + g_list_length(list)));
    unsigned i;
    for(i = 0; i < g_list_length(list); i++){
        TODO[i] = strdup((char*) g_list_nth_data(list, i));
    }
    TODO[i] = NULL;

    return TODO;
}
