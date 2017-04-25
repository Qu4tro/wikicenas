#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"

#define MAX_COMMAND_LENGTH 20

void answer_query(TAD_istruct qs, char q, char* args){
    if (q == '0'){
        printf("%ld\n", all_articles(qs));
    } else if (q == '1'){
        printf("%ld\n", unique_articles(qs));
    } else if (q == '2'){
        printf("%ld\n", all_revisions(qs));
    } else if (q == '3'){
        long* t10 = top_10_contributors(qs);
        for(int i = 0; i < 10; i++){
            printf("%ld ", t10[i]);
        }
        printf("\n");
    } else if (q == '4'){
        char* name = contributor_name(atoi(args), qs);
        if (name != NULL){
            printf("%s\n", name);
        } else {
            printf("not found\n") ;
        }
    } else if (q == '5'){
        long* t20 = top_20_largest_articles(qs);
        for(int i = 0; i < 20; i++){
            printf("%ld ", t20[i]);
        }
        printf("\n");
    } else if (q == '6'){
        char* title = article_title(atoi(args), qs);
        if (title != NULL){
            printf("%s\n", title);
        } else {
            printf("not found\n") ;
        }
    } else if (q == '7'){
        int n = atoi(args);
        long* tN = top_N_articles_with_more_words(n, qs);
        for(int i = 0; i < n; i++){
            printf("%ld ", tN[i]);
        }
        printf("\n");
        /* long* top_N_articles_with_more_words(long n, TAD_istruct qs); */
    } else if (q == '8'){
        char** titles = titles_with_prefix(args, qs);
        if (titles)
            for(int i = 0; titles[i]; i++){
                printf("%s\n", titles[i]);
            }
    } else if (q == '9'){
        char *timestamp = article_timestamp(0, atoi(args), qs);
        if (timestamp != NULL){
            printf("%s\n", timestamp);
        } else {
            printf("not found\n") ;
        }
    }
}

int main(int argc, char** argv){
    argv++;
    argc--;

    setbuf(stdout, NULL);

    TAD_istruct qs = init();

    char* cmd = malloc(sizeof(char) * MAX_COMMAND_LENGTH);
    while (1){
        if (fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL){
            qs = clean(qs);
            break;
        }
        cmd[strlen(cmd) - 1] = '\0';

        if (cmd[0] == 'q'){
            printf("cleaning\n");
            qs = clean(qs);
            printf("quitting\n");
            break;
        } else if(cmd[0] == 'l'){
            printf("loading\n");
            qs = load(qs, argc, argv);
            printf("loaded\n");
        } else if (cmd[0] >= '0' && cmd[0] <= '9'){
            answer_query(qs, cmd[0], cmd + 1);
        } else if (cmd[0] == '\n'){
            ;
        } else {
            printf("unknown\n");
        }
    }

}
