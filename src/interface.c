#include "interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "parser.h"

#include "tst.h"

void TODO(TAD_istruct qs, int n){
    int x = qs -> artigosLidos;
    x += n;
}

TAD_istruct init(){
    TAD_istruct t = malloc(sizeof(struct TCD_istruct));
    t -> artigosLidos = 0;
    t -> artigosHT = g_hash_table_new(g_direct_hash, g_direct_equal);
    t -> artigosTT = create_node(' ', true);
    t -> artigosTopW = pqinit(20);

    t -> colaboradoresTop = pqinit(10);
    t -> colaboradoresHT = g_hash_table_new(g_direct_hash, g_direct_equal);

    t -> revisoesHT = g_hash_table_new(g_direct_hash, g_direct_equal);

    return t;
}

TAD_istruct load(TAD_istruct qs , int nsnaps , char* snaps_paths[]){
    for(int i = 0; i < nsnaps; i++){
        parseBackup(snaps_paths[i], qs);
    }
    
    return NULL;
}

long all_articles(TAD_istruct qs){
    return qs -> artigosLidos;
}

long unique_articles(TAD_istruct qs){
    return g_hash_table_size(qs -> artigosHT);
}

long all_revisions(TAD_istruct qs){
    return g_hash_table_size(qs -> revisoesHT);
}

long* top_10_contributors(TAD_istruct qs){
    return peek_all(qs -> colaboradoresTop);
}

char* contributor_name(long contributor_id, TAD_istruct qs){
    Colaborador c =  g_hash_table_lookup(qs -> colaboradoresHT,
                                         GINT_TO_POINTER(contributor_id));
    if (c == NULL){
        return NULL; 
    }
    return c -> username;
}

long* top_20_largest_articles(TAD_istruct qs){
    return peek_all(qs -> artigosTopW);
}

char* article_title(long article_id, TAD_istruct qs){
    Artigo a = g_hash_table_lookup(qs -> artigosHT,
                                   GINT_TO_POINTER(article_id));
    if (a == NULL){
        return NULL; 
    }
    return a -> titulo;
}

long* top_N_articles_with_more_words(int n, TAD_istruct qs){
    TODO(qs, n);
    return NULL;
    /* return peek_n(qs -> artigosTopB, n); */
}
 
char** titles_with_prefix(char* prefix, TAD_istruct qs){
    return find_by_prefix(qs -> artigosTT, prefix);
}

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
    article_id += 1;
    Revisao r =  g_hash_table_lookup(qs -> revisoesHT,
                                     GINT_TO_POINTER(revision_id));
    if (r == NULL){
        return NULL; 
    }
    return r -> timestamp;
}

TAD_istruct clean(TAD_istruct qs){
    TODO(qs, 0);
    return NULL;
}

