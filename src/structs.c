#include "structs.h"

Colaborador novoColaborador(int id, char* username){

}

void novaContribuicao(Colaborador c){

}

Artigo novoArtigo(int id, char* titulo){
    
}

void contagemArtigo(Artigo a, int nBytes, int nPalavras){

}

Revisao novaRevisao(int id, int idArtigo, char* timestamp){

}


TCD_istruct initTCD(){
    TCD_istruct t = malloc(sizeof(struct TCD_istruct));
    t -> nArtigos = 0;
    t -> nRevisoes = 0;
    /* t -> artigosHT = g_hash_table_new(g_int_hash, g_int_equal); */
    /* t -> colaboradoresHT = g_hash_table_new(g_int_hash, g_int_equal); */
}


/*
typedef struct TCD_istruct {
    size_t nArtigos;
    size_t nRevisoes;
    // hashtable colabs #usernname
    // hashtable artigo #titulo
    // trie      artigo #Nome
    // pheap     colabs #nContribuicoes
    // pheap     artigo #nBytes
    // pheap     artigo #nPalavras
} TCD_istruct;

*/
