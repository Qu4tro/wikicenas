#include "TCD.h"

TCD_istruct TCDinit(){
    TCD_istruct t = malloc(sizeof(struct TCD_istruct));
    t -> artigosLidos = 0;
    t -> artigosHT = g_hash_table_new(g_direct_hash, g_direct_equal);
    t -> artigosTT = create_node(' ', true);
    t -> artigosTopB = pqinit(20);
    t -> artigosTopW = pqinit(-1);

    t -> colaboradoresTop = pqinit(10);
    t -> colaboradoresHT = g_hash_table_new(g_direct_hash, g_direct_equal);

    t -> revisoesHT = g_hash_table_new(g_direct_hash, g_direct_equal);

    return t;
}

void inserirArtigo(Artigo a1, TCD_istruct TCD){
    assert(a1 != NULL);

    Artigo a2;
    a2 = g_hash_table_lookup(TCD -> artigosHT, GINT_TO_POINTER(artigoID(a1)));

    if (a2 == NULL){
        g_hash_table_insert(TCD -> artigosHT, GINT_TO_POINTER(artigoID(a1)), a1);
    } else {
        updateArtigo(a2, a1);
        free(a1);
    }

    TCD -> artigosLidos += 1;
}

void inserirRevisao(Revisao r1, TCD_istruct TCD){
    assert(r1 != NULL);

    Revisao r2;
    r2 = g_hash_table_lookup(TCD -> revisoesHT, GINT_TO_POINTER(revisaoID(r1)));

    if (r2 == NULL){
        g_hash_table_insert(TCD -> revisoesHT, GINT_TO_POINTER(revisaoID(r1)), r1);
    } else {
        updateRevisao(r2, r1);
        free(r1);
    }
}


void inserirContribuicao(Colaborador c1, id_t revisaoID, TCD_istruct TCD){
    assert(c1 != NULL);

    Colaborador c2;
    c2 = g_hash_table_lookup(TCD -> colaboradoresHT, GINT_TO_POINTER(colabID(c1)));

    if (c2 == NULL){
        g_hash_table_insert(TCD -> colaboradoresHT, GINT_TO_POINTER(colabID(c1)), c1);
    } else {
        setUsername(c2, c1);
        if (g_hash_table_lookup(TCD -> revisoesHT, GINT_TO_POINTER(revisaoID)) == NULL){
            incContribuicoes(c2);
        }
        free(c1);
    }
}


void add2ttree(gpointer key, gpointer value, gpointer user_data) {
    Artigo artigo = value;
    TCD_istruct TCD = user_data;

    insert_node(artigoTitulo(artigo), TCD -> artigosTT);
}

void addA2pheap(gpointer key, gpointer value, gpointer user_data) {
    Artigo artigo = value;
    TCD_istruct TCD = user_data;

    enqueue(TCD -> artigosTopB, artigoID(artigo), numberBytes(artigo));
    enqueue(TCD -> artigosTopW, artigoID(artigo), numberWords(artigo));
}

void addC2pheap(gpointer key, gpointer value, gpointer user_data) {
    Colaborador c = value;
    TCD_istruct TCD = user_data;

    enqueue(TCD -> colaboradoresTop, colabID(c), colabContribuicoes(c));
}

void postprocess(TCD_istruct TCD){
    g_hash_table_foreach(TCD -> artigosHT, add2ttree, TCD);
    g_hash_table_foreach(TCD -> artigosHT, addA2pheap, TCD);
    g_hash_table_foreach(TCD -> colaboradoresHT, addC2pheap, TCD);
}

