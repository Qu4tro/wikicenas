#ifndef STRUCTS_H
#define STRUCTS_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glib.h>
#include "tst.h"
#include "topN.h"

typedef unsigned long idW_t;

typedef struct Artigo* Artigo;
typedef struct Revisao* Revisao;
typedef struct Colaborador* Colaborador;


Artigo novoArtigo(idW_t id, char* titulo);
idW_t artigoID(Artigo a);
char* artigoTitulo(Artigo a);
long numberWords(Artigo a);
long numberBytes(Artigo a);
void freeArtigo(gpointer p);

void contagemArtigo(Artigo a, long nBytes, long nPalavras);
void updateArtigo(Artigo a1, Artigo a2);

Revisao novaRevisao(long id, long idArtigo, char* timestamp);
idW_t revisaoID(Revisao r);
char* revisionTimestamp(Revisao r);
void updateRevisao(Revisao r2, Revisao r1);
void freeRevisao(gpointer p);

char* colabUsername(Colaborador c);
long colabContribuicoes(Colaborador c);
idW_t colabID(Colaborador c);
Colaborador novoColaborador(idW_t id, char* username);
void setUsername(Colaborador c2, Colaborador c1);
void incContribuicoes(Colaborador c);
void freeContribuidor(gpointer p);

#endif
