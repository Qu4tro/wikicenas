#include "structs.h"


struct Colaborador{
    id_t id;
    id_t nContribuicoes;
    char* username;
};

struct Artigo {
    id_t id;
    char* titulo;

    size_t nBytes;
    size_t nPalavras;
};


struct Revisao {
    id_t id;
    id_t idArtigo;
    char* timestamp;
};



/* ################################################################################ */
/* #################################### Artigo #################################### */
/* ################################################################################ */

id_t artigoID(Artigo a){
    return a -> id;
}

char* artigoTitulo(Artigo a){
    return a -> titulo;
}

int numberBytes(Artigo a){
    return a -> nBytes;
}

int numberWords(Artigo a){
    return a -> nPalavras;
}

Artigo novoArtigo(int id, char* titulo){
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
    a -> nBytes = new -> nBytes;
    a -> nPalavras = new -> nPalavras;
}

void contagemArtigo(Artigo a, int nBytes, int nPalavras){
    assert(a != NULL);
    assert(nBytes > 0);
    assert(nPalavras > 0);

    a -> nBytes = nBytes;
    a -> nPalavras = nPalavras;
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

id_t revisaoID(Revisao r){
    return r -> id;
}

char* revisionTimestamp(Revisao r){
    return r -> timestamp;
}

void updateRevisao(Revisao r2, Revisao r1){
    r2 -> timestamp = r1 -> timestamp;
}

/* ################################################################################ */
/* ################################# Colaborador ################################## */
/* ################################################################################ */

char* colabUsername(Colaborador c){
    return c -> username;
}

int colabContribuicoes(Colaborador c){
    return c -> nContribuicoes;
}

id_t colabID(Colaborador c){
    return c -> id;
}

Colaborador novoColaborador(int id, char* username){
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
