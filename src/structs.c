#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "parser.h"
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

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "interface.h"
// #include "avl.h"


// typedef struct Colaborador{
// int id;
// char* username;
// }Colaborador;

// typedef struct Artigo{
// int id;
// char* titulo;
// int idRevisao;
// char* dataRevisao;
// Colaborador c;
// char* texto;
// }Artigo;


// typedef struct TCD_istruct{
// avl_table backup[3];	

// } TCD_istruct;


// TAD_istruc init(){

// TAD_istruc ret = malloc(sizeof(TCD_istruct));
// //(*ret).header=malloc(sizeof(char)*20);
	

	

// 	return ret;
// }

// TAD_istruc load(TAD_istruc qa , int nsnaps , char* snaps_paths[]){

// }

//  long all_articles(TAD_istruct qs){

//  }

//  long unique_articles(TAD_istruct qs){

//  }

//  long all_revisions(TAD_istruct qs){

//  }

//  long* top_10_contributors(TAD_istruct qs){

//  }

//  char* contributor_name(long contributor_id, TAD_istruct qs){

//  }

//  long* top_20_largest_articles(TAD_istruct qs){

//  }

//  char* article_title(long article_id, TAD_istruct qs){
//  }

//  long* top_N_articles_with_more_words(int n, TAD_istruct qs){

//  }
 
//  char** titles_with_prefix(char* prefix, TAD_istruct qs){

//  }

//  char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){

//  }
