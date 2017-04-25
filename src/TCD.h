#ifndef TCD_H
#define TCD_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "structs.h"

typedef struct TCD_istruct* TCD_istruct;
struct TCD_istruct {
    size_t artigosLidos;

    GHashTable* artigosHT;
    TTNode*     artigosTT;
    PriorityQueue* artigosTopW;
    PriorityQueue* artigosTopB;

    GHashTable* colaboradoresHT;
    PriorityQueue* colaboradoresTop;

    GHashTable* revisoesHT;
};


TCD_istruct TCDinit();

void inserirContribuicao(Colaborador c1, id_t revisaoID, TCD_istruct TCD);
void inserirRevisao(Revisao r, TCD_istruct TCD);
void inserirArtigo(Artigo a, TCD_istruct TCD);

void postprocess(TCD_istruct TCD);

#endif
