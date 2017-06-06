#include "interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "TCD.h"
#include "parser.h"
#include "tst.h"

TAD_istruct init(){
    TAD_istruct t = TCDinit();
    return t;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]){
    qs = parseBackup(nsnaps, snaps_paths, qs);
    postprocess(qs);
    
    return qs;
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
    return peek_n(qs -> colaboradoresTop, 10);
}

char* contributor_name(long contributor_id, TAD_istruct qs){
    Colaborador c =  g_hash_table_lookup(qs -> colaboradoresHT,
                                         GINT_TO_POINTER(contributor_id));
    if (c == NULL){
        return NULL; 
    }
    return colabUsername(c);
}

long* top_20_largest_articles(TAD_istruct qs){
    return peek_n(qs -> artigosTopB, 20);
}

char* article_title(long article_id, TAD_istruct qs){
    Artigo a = g_hash_table_lookup(qs -> artigosHT,
                                   GINT_TO_POINTER(article_id));
    if (a == NULL){
        return NULL; 
    }
    return artigoTitulo(a);
}

long* top_N_articles_with_more_words(int n, TAD_istruct qs){
    return peek_n(qs -> artigosTopW, n);
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
    return revisionTimestamp(r);
}

TAD_istruct clean(TAD_istruct qs){
    return freeTCD(qs);
}

