#include "structs.h"

/* ################################################################################ */
/* #################################### Artigo #################################### */
/* ################################################################################ */

Artigo novoArtigo(int id, char* titulo){
    assert(id >= 0);
    assert(titulo != NULL);

    Artigo a = malloc(sizeof(struct Artigo));
    a -> id = id;
    a -> titulo = titulo;

    return a;
}

void contagemArtigo(Artigo a, int nBytes, int nPalavras){
    assert(a != NULL);
    assert(nBytes > 0);
    assert(nPalavras > 0);

    a -> nBytes = nBytes;
    a -> nPalavras = nPalavras;
}

void inserirArtigo(Artigo a1, TCD_istruct TCD){
    assert(a1 != NULL);

    Artigo a2;
    a2 = g_hash_table_lookup(TCD -> artigosHT, GINT_TO_POINTER(a1 -> id));

    if (a2 == NULL){
        g_hash_table_insert(TCD -> artigosHT, GINT_TO_POINTER(a1 -> id), a1);
        insert_node(a1 -> titulo, TCD -> artigosTT);
    } else {
        a2 -> titulo = a1 -> titulo;
        if (a2 -> nBytes < a1 -> nBytes){
            a2 -> nBytes = a1 -> nBytes;
        }
        if (a2 -> nPalavras < a1 -> nPalavras){
            a2 -> nPalavras = a1 -> nPalavras;
        }
    }

    TCD -> artigosLidos += 1;
}

/* ################################################################################ */
/* ################################### Revisao #################################### */
/* ################################################################################ */

Revisao novaRevisao(int id, int idArtigo, char* timestamp){
    assert(id >= 0);
    assert(timestamp != NULL);

    Revisao r = malloc(sizeof(struct Revisao));
    r -> id = id;
    r -> idArtigo = idArtigo;
    r -> timestamp = timestamp;

    return r;
}

void inserirRevisao(Revisao r1, TCD_istruct TCD){
    assert(r1 != NULL);

    Revisao r2;
    r2 = g_hash_table_lookup(TCD -> revisoesHT, GINT_TO_POINTER(r1 -> id));

    if (r2 == NULL){
        g_hash_table_insert(TCD -> revisoesHT, GINT_TO_POINTER(r1 -> id), r1);
    } else {
        r2 -> timestamp = r1 -> timestamp;
    }
}

/* ################################################################################ */
/* ################################# Colaborador ################################## */
/* ################################################################################ */

Colaborador novoColaborador(int id, char* username){
    assert(id >= 0);
    assert(username != NULL);

    Colaborador c = malloc(sizeof(struct Colaborador));
    c -> id = id;
    c -> username = username;
    c -> nContribuicoes = 1;
    
    return c;
}

void inserirContribuicao(Colaborador c1, id_t revisaoID, TCD_istruct TCD){
    assert(c1 != NULL);

    Colaborador c2;
    c2 = g_hash_table_lookup(TCD -> colaboradoresHT, GINT_TO_POINTER(c1 -> id));

    if (c2 == NULL){
        g_hash_table_insert(TCD -> colaboradoresHT, GINT_TO_POINTER(c1 -> id), c1);
    } else {
        c2 -> username = c1 -> username;
        if (g_hash_table_lookup(TCD -> revisoesHT, GINT_TO_POINTER(revisaoID)) == NULL){
            c2 -> nContribuicoes += 1;
        }
    }
}

/* ################################################################################ */
/* ##################################### TCD ###################################### */
/* ################################################################################ */

TCD_istruct initTCD(){
    TCD_istruct t = malloc(sizeof(struct TCD_istruct));
    t -> artigosLidos = 0;
    t -> artigosHT = g_hash_table_new(g_direct_hash, g_direct_equal);
    t -> colaboradoresHT = g_hash_table_new(g_direct_hash, g_direct_equal);
    t -> revisoesHT = g_hash_table_new(g_direct_hash, g_direct_equal);
}
