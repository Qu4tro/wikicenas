#include "parser.h"

bool space(char c){
    return (c == ' ' || c == '\n' || c == '\t');
}

void parseText(xmlNodePtr textNode){
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


    // printf("%d - %d\n", nBytes, nWords);
}

void parseContributor(xmlNodePtr contributor){
    assert(xmlStrcmp(contributor -> name, (const xmlChar *) "contributor") == 0);

    xmlNodePtr curr;
    xmlChar* text;

    curr = contributor -> xmlChildrenNode;
    if (xmlStrcmp(curr -> name, (const xmlChar *) "ip") == 0){
        return;
    }
    
    char* username = (char*) xmlNodeGetContent(curr);
    curr = curr -> next;
    int id = atoi((char*) xmlNodeGetContent(curr));


    // printf("%d - %s\n", id, username);
}

void parseRevision(xmlNodePtr revision){
    assert(xmlStrcmp(revision -> name, (const xmlChar *) "revision") == 0);

    int find_i = 0;

    xmlNodePtr curr;
    xmlChar* text;

    id_t id;
    char* timestamp;

    const xmlChar* find[] = {(const xmlChar*) "timestamp"
                            ,(const xmlChar*) "contributor"
                            ,(const xmlChar*) "text"
                            };

    curr = revision -> xmlChildrenNode;
    id = atoi((char*) xmlNodeGetContent(curr));

    for(; curr != NULL; curr = curr -> next){
        text = xmlNodeGetContent(curr);

        if (xmlStrcmp(curr -> name, find[find_i]) == 0){
            if (find_i == 0){
                timestamp = strdup((char*) text);
            } else if (find_i == 1){
                parseContributor(curr);
            } else if (find_i == 2){
                // parseText(curr);
            }
            find_i += 1;
        } 
        xmlFree(text);
    }

    assert(find_i == 3);
    // printf("%d - %s\n", id, timestamp);
}

void parsePage(xmlNodePtr page) {
    if (xmlStrcmp(page -> name, (const xmlChar *) "page") != 0){
        printf("%s\n", (char*) page -> name);
    }
    assert(xmlStrcmp(page -> name, (const xmlChar *) "page") == 0);

    xmlNodePtr curr;
    xmlChar* text;
    char* title;
    int id;

    int i = 0;
    for(curr = page -> xmlChildrenNode; curr != NULL; curr = curr -> next){
        text = xmlNodeGetContent(curr);

        if (i == 0){
            title = strdup((char*) text);
        } else if (i == 2){
            id = atoi((char*) text);
        } else if (xmlStrcmp(curr -> name, (const xmlChar *) "revision") == 0) {
            parseRevision(curr);
        }

        xmlFree(text);
        i++;
    }

    // printf("%d - %s\n", id, title);
} 

void parseBackup(char* xml_filename) {
    xmlDocPtr doc;  
    xmlNodePtr page;

    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(xml_filename);
    if (doc == NULL ) {
        fprintf(stderr,"xmlParseFile NULL");
        return;
    }

    page = xmlDocGetRootElement(doc) -> xmlChildrenNode -> next; 
    for(; page != NULL; page = page -> next){
        parsePage(page);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser(); 
}

/* int main(int argc, char** argv){ */
/*     parseBackup(argv[1]); */
/* } */
