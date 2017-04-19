#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* #include <glib.h> */

typedef unsigned int id_t;

typedef struct Colaborador{
    id_t id;
    id_t nContribuicoes;
    char* username;
}* Colaborador;

Colaborador novoColaborador(int id, char* username);
/* void novaContribuicao(Colaborador c); */

typedef struct Artigo {
    id_t id;
    char* titulo;

    size_t nBytes;
    size_t nWords;
}* Artigo;

Artigo novoArtigo(int id, char* titulo);
void contagemArtigo(Artigo a, int nBytes, int nWords);

typedef struct Revisao {
    id_t id;
    id_t idArtigo;
    char* timestamp;
}* Revisao;
Revisao novaRevisao(int id, int idArtigo, char* timestamp);

typedef struct TCD_istruct {
    size_t nArtigos;
    size_t nRevisoes;
    /* GHashTable* artigosHT; */
    /* GHashTable* colaboradoresHT; */
    // hashtable artigo #titulo
    // hashtable colabs #usernname
    // trie      artigo #Nome
    // pheap     colabs #nContribuicoes
    // pheap     artigo #nBytes
    // pheap     artigo #nWords
}* TCD_istruct;


void inserirColaborador(Colaborador c, TCD_istruct* TCD);
void inserirRevisao(Revisao r, TCD_istruct* TCD);
void inserirArtigo(Artigo a, TCD_istruct* TCD);

#endif
