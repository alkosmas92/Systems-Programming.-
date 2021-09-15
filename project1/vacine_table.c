#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "skip_list.h"
#include "types.h"


Slist * simple_list_create(){
  Slist* S= (Slist *)malloc(sizeof(Slist));
  return S;
}

void insert_simple_list(Slist *S , record *rec){
  while(S->next!=NULL){
      S=S->next;
  }
  if(S->next==NULL){
    S->rec=malloc(sizeof(record));
    memcpy(S->rec , rec , sizeof(record));
    S->next=(Slist *)malloc(sizeof(Slist));
  }

}

void print_simple_list(Slist *S ){
  FILE* fp;
  fp = fopen("log.txt", "w");
  char* data[30] ;
    while(S->next!=NULL){
      printf("IS ID IS %s\n",S->rec->id );
      //printf("IS ID IS %s\n",S->rec->ios );
      fputs(S->rec->id, fp);
      fputs("\n", fp);
      S=S->next;
    }
    fclose(fp);


    // return EXIT_SUCCESS;

}
