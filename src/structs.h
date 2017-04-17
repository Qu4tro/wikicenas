#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int id_t;

typedef struct Colaborador{
    id_t id;
    id_t nContribuicoes;
    char* username;
} Colaborador;

typedef struct Artigo {
    id_t id;
    char* titulo;

    size_t nBytes;
    size_t nPalavras;
} Artigo;

typedef struct Revisao {
    id_t id;
    id_t idArtigo;
    char* timestamp;
} Revisao;

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
