#include "parser.h"

bool space(char c){
    return (c == ' ' || c == '\n' || c == '\t');
}

void parseText(xmlNodePtr textNode, Artigo artigo){
    assert(xmlStrcmp(textNode -> name, (const xmlChar *) "text") == 0);

    char* text = (char*) xmlNodeGetContent(textNode);
    int nBytes;
    int nWords;
    bool inWord = false;

    int i;
    for(i = 0; text[i] != '\0'; i++){
        if (inWord == false && !space(text[i])){
            inWord = true;
            nWords += 1; 
        }
        if (inWord == true && space(text[i])){
            inWord = false;
        }
    }
    nBytes = i - 1;

    contagemArtigo(artigo, nBytes, nWords);
}

void parseContributor(xmlNodePtr contributor, id_t revisionID, TCD_istruct TCD){
    assert(xmlStrcmp(contributor -> name, (const xmlChar *) "contributor") == 0);

    xmlNodePtr curr = contributor -> xmlChildrenNode;
    if (xmlStrcmp(curr -> name, (const xmlChar *) "ip") == 0){
        return;
    }
    
    char* username = strdup((char*) xmlNodeGetContent(curr));
    curr = curr -> next;
    int id = atoi((char*) xmlNodeGetContent(curr));

    Colaborador c = novoColaborador(id, username);
    inserirContribuicao(c, revisionID, TCD);
}

void parseRevision(xmlNodePtr revision, Artigo artigo, TCD_istruct TCD){
    assert(xmlStrcmp(revision -> name, (const xmlChar *) "revision") == 0);

 
    const xmlChar* find[] = { (const xmlChar*) "id"
                            , (const xmlChar*) "timestamp"
                            , (const xmlChar*) "contributor"
                            , (const xmlChar*) "text"
                            };

    int find_i = 0;

    xmlChar* text;

    xmlNodePtr curr = revision -> xmlChildrenNode;
    id_t id = atoi((char*) xmlNodeGetContent(curr));
    char* timestamp;
    Revisao r;


    for(; curr != NULL; curr = curr -> next){
        text = xmlNodeGetContent(curr);

        if (xmlStrcmp(curr -> name, find[find_i]) == 0){

            if (find_i == 0){
                id = atoi((char*) text);

            } else if (find_i == 1){
                timestamp = strdup((char*) text);
                r = novaRevisao(id, artigoID(artigo), timestamp);
                inserirRevisao(r, TCD);
                
            } else if (find_i == 2){
                parseContributor(curr, id, TCD);
            } else if (find_i == 3){
                parseText(curr, artigo);
            }
            find_i += 1;
        } 
        xmlFree(text);
    }

    assert(find_i == 4);
}

void parsePage(xmlNodePtr page, TCD_istruct TCD) {
    assert(xmlStrcmp(page -> name, (const xmlChar *) "page") == 0);

    xmlNodePtr curr;
    xmlChar* text;
    Artigo artigo;
    char* title;
    int id;

    int i = 0;
    for(curr = page -> xmlChildrenNode; curr != NULL; curr = curr -> next){
        text = xmlNodeGetContent(curr);

        if (i == 0){
            title = strdup((char*) text);
        } else if (i == 2){
            id = atoi((char*) text);
            artigo = novoArtigo(id, title);
        } else if (xmlStrcmp(curr -> name, (const xmlChar *) "revision") == 0) {
            parseRevision(curr, artigo, TCD);
            inserirArtigo(artigo, TCD);
        }

        xmlFree(text);
        i++;
    }
} 

TCD_istruct parseBackup(char* xml_filename, TCD_istruct TCD) {
    xmlDocPtr doc;  
    xmlNodePtr page;

    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(xml_filename);
    if (doc == NULL ) {
        fprintf(stderr,"xmlParseFile NULL");
        return NULL;
    }

    page = xmlDocGetRootElement(doc) -> xmlChildrenNode -> next; 
    for(; page != NULL; page = page -> next){
        parsePage(page, TCD);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser(); 

    return TCD;
}

/* int main(int argc, char** argv){ */

/*     TCD_istruct TCD = init(); */
/*     parseBackup(argv[1], TCD); */
/*     printf("Size Artigos:\t%d\n", g_hash_table_size (TCD -> artigosHT)); */
/*     printf("Size Revisoes:\t%d\n", g_hash_table_size(TCD -> revisoesHT)); */
/*     printf("Size Contribuidor:\t%d\n", g_hash_table_size(TCD -> colaboradoresHT)); */
/* } */
