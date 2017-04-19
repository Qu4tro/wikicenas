#include "parser.h"

bool space(char c){
    return (c == ' ' || c == '\n' || c == '\t');
}

void parseText(xmlNodePtr textNode, Artigo a){
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

    contagemArtigo(a, nBytes, nWords);
}

void parseContributor(xmlNodePtr contributor, TCD_istruct* TCD){
    assert(xmlStrcmp(contributor -> name, (const xmlChar *) "contributor") == 0);

    xmlNodePtr curr = contributor -> xmlChildrenNode;
    if (xmlStrcmp(curr -> name, (const xmlChar *) "ip") == 0){
        return;
    }
    
    char* username = strdup((char*) xmlNodeGetContent(curr));
    curr = curr -> next;
    int id = atoi((char*) xmlNodeGetContent(curr));


    Colaborador c = novoColaborador(id, username);
    inserirColaborador(c, TCD);
}

void parseRevision(xmlNodePtr revision, Artigo a, TCD_istruct* TCD){
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
                r = novaRevisao(id, a -> id, timestamp);
                inserirRevisao(r, TCD);
                
            } else if (find_i == 2){
                parseContributor(curr, TCD);
            } else if (find_i == 3){
                parseText(curr, a);
            }
            find_i += 1;
        } 
        xmlFree(text);
    }

    assert(find_i == 3);
}

void parsePage(xmlNodePtr page, TCD_istruct* TCD) {
    if (xmlStrcmp(page -> name, (const xmlChar *) "page") != 0){
        printf("%s\n", (char*) page -> name);
    }
    assert(xmlStrcmp(page -> name, (const xmlChar *) "page") == 0);

    xmlNodePtr curr;
    xmlChar* text;
    Artigo a;
    char* title;
    int id;

    int i = 0;
    for(curr = page -> xmlChildrenNode; curr != NULL; curr = curr -> next){
        text = xmlNodeGetContent(curr);

        if (i == 0){
            title = strdup((char*) text);
        } else if (i == 2){
            id = atoi((char*) text);
            a = novoArtigo(id, title);
        } else if (xmlStrcmp(curr -> name, (const xmlChar *) "revision") == 0) {
            parseRevision(curr, a, TCD);
        }

        xmlFree(text);
        inserirArtigo(a, TCD);
        i++;
    }
} 

void parseBackup(char* xml_filename, TCD_istruct* TCD) {
    xmlDocPtr doc;  
    xmlNodePtr page;

    int nArtigos = 0;

    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(xml_filename);
    if (doc == NULL ) {
        fprintf(stderr,"xmlParseFile NULL");
        return;
    }

    page = xmlDocGetRootElement(doc) -> xmlChildrenNode -> next; 
    for(; page != NULL; page = page -> next){
        parsePage(page, TCD);
        nArtigos++;
    }

    xmlFreeDoc(doc);
    xmlCleanupParser(); 
}

int main(int argc, char** argv){
    parseBackup(argv[1], NULL);
}
