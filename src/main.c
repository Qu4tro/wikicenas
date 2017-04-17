#include <stdio.h>
#include "interface.h"

int main(){
  argv++;
  argc--;

  TAD_istruct qs = init();
  qs = load(qs, argc, argv);

  printf("%d\n", all_articles(qs));
  printf("%d\n", unique_articles(qs));
  printf("%d\n", all_revisions(qs));

  qs = clean(qs);
}
