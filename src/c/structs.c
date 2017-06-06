#include "structs.h"
  
#define max(a, b) ((a) > (b) ? (a) : (b))

struct Colaborador{
    idW_t id;
    idW_t nContribuicoes;
    char* username;
};

struct Artigo {
    idW_t id;
    char* titulo;

    size_t nBytes;
    size_t nPalavras;
};


struct Revisao {
    idW_t id;
    idW_t idArtigo;
    char* timestamp;
};



/* ################################################################################ */
/* #################################### Artigo #################################### */
/* ################################################################################ */

idW_t artigoID(Artigo a){
    return a -> id;
}

char* artigoTitulo(Artigo a){
    return a -> titulo;
}

long numberBytes(Artigo a){
    return a -> nBytes;
}

long numberWords(Artigo a){
    return a -> nPalavras;
}

Artigo novoArtigo(idW_t id, char* titulo){
    assert(id >= 0);
    assert(titulo != NULL);

    Artigo a = malloc(sizeof(struct Artigo));
    a -> id = id;
    a -> titulo = titulo;

    return a;
}

void updateArtigo(Artigo a, Artigo new){
    assert(a != NULL);

    a -> titulo = new -> titulo;
    a -> nBytes = max(a -> nBytes, new -> nBytes);
    a -> nPalavras = max(a -> nPalavras, new -> nPalavras);
}

void contagemArtigo(Artigo a, long nBytes, long nPalavras){
    assert(a != NULL);
    assert(nBytes > 0);
    assert(nPalavras > 0);

    a -> nBytes = nBytes;
    a -> nPalavras = nPalavras;
}

void freeArtigo(gpointer p){
    Artigo a = p;
    free(a -> titulo);
    free(a);
}


/* ################################################################################ */
/* ################################### Revisao #################################### */
/* ################################################################################ */

Revisao novaRevisao(long id, long idArtigo, char* timestamp){
    assert(id >= 0);
    assert(timestamp != NULL);

    Revisao r = malloc(sizeof(struct Revisao));
    r -> id = id;
    r -> idArtigo = idArtigo;
    r -> timestamp = timestamp;

    return r;
}

idW_t revisaoID(Revisao r){
    return r -> id;
}

char* revisionTimestamp(Revisao r){
    return r -> timestamp;
}

void updateRevisao(Revisao r2, Revisao r1){
    r2 -> timestamp = r1 -> timestamp;
}

void freeRevisao(gpointer p){
    Revisao r = p;
    free(r -> timestamp);
    free(r);
}

/* ################################################################################ */
/* ################################# Colaborador ################################## */
/* ################################################################################ */

char* colabUsername(Colaborador c){
    return c -> username;
}

long colabContribuicoes(Colaborador c){
    return c -> nContribuicoes;
}

idW_t colabID(Colaborador c){
    return c -> id;
}

Colaborador novoColaborador(idW_t id, char* username){
    assert(id >= 0);
    assert(username != NULL);

    Colaborador c = malloc(sizeof(struct Colaborador));
    c -> id = id;
    c -> username = username;
    c -> nContribuicoes = 1;
    
    return c;
}


void setUsername(Colaborador c2, Colaborador c1){
    c2 -> username = c1 -> username;
}

void incContribuicoes(Colaborador c){
    c -> nContribuicoes += 1;
}

void freeContribuidor(gpointer p){
    Colaborador c = p;
    free(c -> username);
    free(c);
}
