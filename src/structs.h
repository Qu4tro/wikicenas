#ifndef STRUCTS_H
#define STRUCTS_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glib.h>
#include "tst.h"
#include "topN.h"

typedef unsigned int id_t;

typedef struct Artigo* Artigo;
typedef struct Revisao* Revisao;
typedef struct Colaborador* Colaborador;


Artigo novoArtigo(int id, char* titulo);
id_t artigoID(Artigo a);
char* artigoTitulo(Artigo a);
int numberWords(Artigo a);
int numberBytes(Artigo a);

void contagemArtigo(Artigo a, int nBytes, int nPalavras);
void updateArtigo(Artigo a1, Artigo a2);

Revisao novaRevisao(int id, int idArtigo, char* timestamp);
id_t revisaoID(Revisao r);
char* revisionTimestamp(Revisao r);
void updateRevisao(Revisao r2, Revisao r1);

char* colabUsername(Colaborador c);
int colabContribuicoes(Colaborador c);
id_t colabID(Colaborador c);
Colaborador novoColaborador(int id, char* username);
void setUsername(Colaborador c2, Colaborador c1);
void incContribuicoes(Colaborador c);

#endif
