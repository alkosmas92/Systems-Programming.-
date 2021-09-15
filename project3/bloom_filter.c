#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#define MAX 80
#define PORT 8080
#define POOL_SIZE 6
#define SA struct sockaddr


#include "skip_list.h"


unsigned long djb2(unsigned char *str) {
      unsigned long hash = 5381;
      int c;
      while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
      }
      return hash;
}

unsigned long sdbm(unsigned char *str) {
	unsigned long hash = 0;
	int c;

	while (c = *str++) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

unsigned long hash_i(unsigned char *str, unsigned int i) {
	return djb2(str) + i*sdbm(str) + i*i;
}

int str_cut(char *str, int begin, int len)
  {
      int l = strlen(str);

      if (len < 0) len = l - begin;
      if (begin + len > l) len = l - begin;
      memmove(str + begin, str + begin + len, l - len + 1);

      return len;
  }

void date(char* my_date) {
  int d[3];
  char a[10];
  char b[10];
  char c[10];
  char buffer[40];

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  d[0]=t->tm_mon+1;
  d[1]=t->tm_mday;
  d[2]=t->tm_year+1900;


   sprintf(my_date, "%d-%d-%d", d[1], d[0], d[2]);
  return 0;
}



void printMenu(void) {
	printf("\n Your options:\n");
	printf("\n /travelRequest citizenID date countryFrom countryTo virusName\n");
	printf("\n /travelStats virusName date1 date2 [country]\n");
	printf("\n /addVaccinationRecords country \n");
	printf("\n /searchVaccinationStatus citizenID\n");
  printf("\n /exit<space>\n\n\n");

}


void SetBit(ios_hash* A,unsigned long  k_atoi , char *id ,int check , int size ){

     char all1[20]="60";
    //k_atoi = k_atoi/31;            // i = array index (use: A->arrary_bloom[i].bits)
      while(k_atoi>size){
        k_atoi=k_atoi/32;
      }
      int pos = k_atoi%31;          // pos = bit position in A->arrary_bloom[i].bits
      unsigned int flag = 1;   // flag = 0000.....00001
      flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)
      A->bloom[k_atoi] = A->bloom[k_atoi] | flag;      // Set the bit at the k-th position in A[i]

  }

void ClearBit(ios_hash* A, int k_atoi){

      int i = k_atoi/32;
      int pos = k_atoi%31;
      unsigned int flag = 1;  // flag = 0000.....00001
      flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)
      flag = ~flag;           // flag = 1111...101..111
      A->bloom[k_atoi] = A->bloom[k_atoi] & flag;      // Set the bit at the k-th position in A[i]
}

int TestBit(ios_hash* A ,unsigned long k_atoi){

      int pos = k_atoi%31;
      unsigned int flag = 1;  // flag = 0000.....00001

      flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)
      if(   A->bloom[k_atoi]  & flag )      // Test the bit at the k-th position in A[i]
         return 1;
      else
         return 0;
 }

void initiaze_ios_for(ios_hash *H , char * ios ,  int tsize ){
  // if(H->next==NULL){
  //   printf("EIMAI NAYULLL\n" );
  // }
  // if(H->next!=NULL){
  //   printf("DENNN EIMAI NAYULLL\n" );
  // }
  while (H->next!=NULL){
    if(strcmp(H->name_ios,ios)==0){
      break;
    }
    H=H->next;
  }
  if(H->next==NULL){
      strcpy(H->name_ios,ios);
      // printf("my_rec ios is %s\n", H->name_ios);
      H->bloom=malloc(tsize * sizeof(int));
      for(int k=0 ; k<tsize ; k++){
        H->bloom[k]=0;
      }
      H->next=malloc(sizeof(ios_hash));
      H=H->next;
      H->next=NULL;
    }
  // printf("H->insideee is %d\n",H->bloom[30] );




}

void initiaze_ios_table(ios_hash *H , record * my_rec ,  int tsize ){
  char vac[20]="YES";
  strcpy(H->name_ios,my_rec->ios);
  // printf("my_rec ios is %s\n", H->name_ios);
  H->bloom=malloc(tsize * sizeof(int));
  for(int k=0 ; k<tsize ; k++){
    H->bloom[k]=0;
  }

  if(strcmp(my_rec->vacine,vac)==0){
      int i = 0 , check=0;
      int K = 16;
      for (i = 0 ; i < K ; i++) {
        unsigned long lim=hash_i(my_rec->id,i);
        SetBit(H ,lim , my_rec->id , check ,  tsize );
      }
  }

  H->next=malloc(sizeof(ios_hash));
  H=H->next;
  H->next=NULL;
}


ios_hash * create_hash_ios( int size){
  ios_hash *H=malloc(sizeof(ios_hash));
  H->next=NULL;
  return H;
}
void destractor_ios_hash(ios_hash *H , int tsize){

    while(H->next!=NULL){
      for(int k=0 ; k<tsize ; k++){
        free(H->bloom[k]);
      }
      free(H->name_ios);
      free(H);
      H=H->next;
    }
    // free(H);
    //free(L);
  }

void insert_to_array_bloom(ios_hash *H , record *my_rec , int tsize ){
   char vac[20]="YES";
   if(strcmp(my_rec->vacine,vac)==0){

      int i = 0;
      int K = 15;
      int check=0;
      for (i = 0 ; i < K ; i++) {
        int lim=hash_i(my_rec->id,i);
        SetBit(H ,lim , my_rec->id , check ,  tsize );
      }
    }
}

int search_for_bloom(int i , char *my_id , ios_hash *H , int size){
  int count=0;
  int K=15;
  for(int m=0 ; m < K ; m++){
    unsigned long lim=hash_i(my_id , m);
      while(lim>size){
        lim=lim/32;
      }
        if( TestBit(H,lim)){
          count+=1;
        }
        else{
          return 0;
        }
    }
    if(count==15){
      return 1;
    }
}

int vacine_check(ios_hash * H , char * my_id , char * ios , int size  ){
  //H=H->next;
  int i,K=15 ,count=0 ,m, final;
  int lim;

  while(H->next!=NULL){     //des gia veltiowsi
    count=0;
    m=0;
    i=0;
        if(strcmp(H->name_ios,ios)==0){
            if(search_for_bloom(i , my_id , H , size)){
                // printf("MAYBE\n" );
                return 0;
            }
            else{
              // printf("NOT VACINATED\n" );
              return 1;
            }
        }

        H=H->next;
      }
      printf("NOT INFORMATION\n" );
      return 1;
    }

void insert_hash_ios(ios_hash *H , int size ,record *my_rec){
    while(H->next!=NULL){
      if(strcmp(H->name_ios,my_rec->ios)==0){
        insert_to_array_bloom(H ,  my_rec , size);
        break;

      }
      H=H->next;
    }
    if(H->next==NULL){
      initiaze_ios_table(H, my_rec ,size);
    }
}

void put_the_broke(char * broke , char* record){
  if (broke==NULL) {
     strcpy(record,"");

   }
  else if(strlen(broke)==1){
     strcpy(record,"");
  }

  else{
    strcpy(record,broke);
  }

}

void read_file(ios_hash *H , Slist *A ,char* filename, int size  ){
 int zip=0; FILE *ptr;
 int vac=0; int rec_no=0;

 record *my_rec=malloc(sizeof(record));
   ptr = fopen(filename,"r");
   if(ptr==NULL)
     {
     }
   char *line = NULL;
          size_t  lenght;
          ssize_t  test;
    char id[20];
    char date1[14];
    char month1[14];
    char date2[14];
    char month2[14];
    char date3[14];
    char month3[14];
    char date4[14];
    char month4[14];
    char year[14];

  while((test = getline(&line, &lenght , ptr)) != -1){
    rec_no=0;
   char check[]=" ";
   char *broke = strtok(line,check);
      if(broke==NULL){
          broke = strtok(line,check);
      }
       strcpy(my_rec->id , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->first_name , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->last_name , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->country , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->age , broke);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->ios , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->vacine , broke);
       if(strcmp(my_rec->vacine,"YES")==0){
           broke=strtok(NULL,check);
           if(broke!=NULL){
             strcpy(my_rec->date , broke);


             strcpy(date1 , broke);
             strcpy(month1 , broke);
             strcpy(date2 , broke);
             strcpy(month2 , broke);
             strcpy(date3 , broke);
             strcpy(month3 , broke);

             strcpy(year , broke);

             if(strlen(year)==9){
               str_cut(date1,1,9);
               str_cut(date2,0,2);
               str_cut(date2,1,7);
               strcpy(month1,date2);

             }
             if(strlen(year)==10){
               str_cut(date1,1,10);
               str_cut(date2,0,1);
               str_cut(date2,1,9);
               if(strcmp(date2,"-")==0){

                 str_cut(date3,0,2);
                 str_cut(date3,2,8);
                 strcpy(month1,date3);

               }
               else{
                  strncat(date1, &date2, strlen(date2)+1);
                 str_cut(date3,0,3);
                 str_cut(date3,1,7);
                 strcpy(month1,date3);

               }

             }
             if(strlen(year)==11){
               str_cut(date1,2,10);
               str_cut(month1,0,3);
               str_cut(month1,2,7);
             }

           strcpy(year,(my_rec->date  + strlen(my_rec->date) - 5) );
           char result[15] = {0};
           snprintf(result, sizeof(result), "%s %s %s",year,month1,date1);
           strcpy(my_rec->extraDate,result);
           //printf("final date is %s \n",result   );
          }
        }

    else{
      broke=strtok(NULL,check);
        if(broke!=NULL){
          printf("ERROR RECORD HAVE PROBLEM NO INSERT\n" );
          rec_no=1;
        }
    }

        //  vac=vaccineStatus_check(HA , my_rec->id , my_rec->ios);
        // if(vac==0 && rec_no!=1){

          insert_hash_ios(H , size , my_rec);
          // initiaze_table_vacine(HA , my_rec );
          insert_simple_list(A ,my_rec);


        // }
      }
  }

void read_file_w(ios_hash *H , Slist *A ,char* filename, int size  ){
 int zip=0; FILE *ptr;
 int vac=0; int rec_no=0;

 record *my_rec=malloc(sizeof(record));
   ptr = fopen(filename,"r");
   if(ptr==NULL)
     {
     }
   char *line = NULL;
          size_t  lenght;
          ssize_t  test;
    char id[20];
    char date1[14];
    char month1[14];
    char date2[14];
    char month2[14];
    char date3[14];
    char month3[14];
    char date4[14];
    char month4[14];
    char year[14];

  while((test = getline(&line, &lenght , ptr)) != -1){
    rec_no=0;
   char check[]=" ";
   char *broke = strtok(line,check);
      if(broke==NULL){
          broke = strtok(line,check);
      }
       strcpy(my_rec->id , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->first_name , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->last_name , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->country , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->age , broke);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->ios , broke);
       broke=strtok(NULL,check);
       if(broke==NULL){
          broke = strtok(line,check);
       }
       strcpy(my_rec->vacine , broke);
       if(strcmp(my_rec->vacine,"YES")==0){
           broke=strtok(NULL,check);
           if(broke!=NULL){
             strcpy(my_rec->date , broke);


             strcpy(date1 , broke);
             strcpy(month1 , broke);
             strcpy(date2 , broke);
             strcpy(month2 , broke);
             strcpy(date3 , broke);
             strcpy(month3 , broke);

             strcpy(year , broke);

             if(strlen(year)==9){
               str_cut(date1,1,9);
               str_cut(date2,0,2);
               str_cut(date2,1,7);
               strcpy(month1,date2);

             }
             if(strlen(year)==10){
               str_cut(date1,1,10);
               str_cut(date2,0,1);
               str_cut(date2,1,9);
               if(strcmp(date2,"-")==0){

                 str_cut(date3,0,2);
                 str_cut(date3,2,8);
                 strcpy(month1,date3);

               }
               else{
                  strncat(date1, &date2, strlen(date2)+1);
                 str_cut(date3,0,3);
                 str_cut(date3,1,7);
                 strcpy(month1,date3);

               }

             }
             if(strlen(year)==11){
               str_cut(date1,2,10);
               str_cut(month1,0,3);
               str_cut(month1,2,7);
             }

           strcpy(year,(my_rec->date  + strlen(my_rec->date) - 5) );
           char result[15] = {0};
           snprintf(result, sizeof(result), "%s %s %s",year,month1,date1);
           strcpy(my_rec->extraDate,result);
           //printf("final date is %s \n",result   );
          }
        }

    else{
      broke=strtok(NULL,check);
        if(broke!=NULL){
          printf("ERROR RECORD HAVE PROBLEM NO INSERT\n" );
          rec_no=1;
        }
    }

        //  vac=vaccineStatus_check(HA , my_rec->id , my_rec->ios);
        // if(vac==0 && rec_no!=1){

          insert_hash_ios(H , size , my_rec);
          // initiaze_table_vacine(HA , my_rec );
          insert_simple(A ,my_rec);


        // }
      }
  }

void print_hash_table(ios_hash *H,int size_bf){
  //H=H->next;
  printf("EKSOOOOO\n" );
  while (H->next!=NULL){

    printf("OLEEEEE\n" );
    printf("the name is %s\n",H->name_ios);
    printf("size_bf os %d\n",size_bf );
    for(int k=0 ; k<size_bf ; k++){
      	printf("????????????table[%d] H->outtttinsideee is %d\n" ,k , H->bloom[k] );
    }

    H=H->next;
  }
//  printf("the name_ios is %s\n",H->name_ios);
}
skip_node * constractor_node(){
  skip_node *S=malloc(sizeof(skip_node));
  S->next=NULL;
  S->up=NULL;
  S->down=NULL;
  S->previous=NULL;
  S->rec=malloc(sizeof(skip_node));
  strcpy(S->rec->id ,"0");
  return S;
}

skip_node * constractor_skip_list(skip_node *HEAD){

  skip_node *S=malloc(sizeof(skip_node));
  skip_node *HELP_UP=malloc(sizeof(skip_node));
  skip_node *HELP_DOWN=malloc(sizeof(skip_node));
  char num_id[20];
  S=HEAD;
  int i=0;
  while(i<=9){
    if(i==0){
      S->down=NULL;
      S->next=NULL;
      S->rec=malloc(sizeof(record));
      sprintf(num_id, "%d",i*(-1));
      strcpy(S->rec->id,num_id);
      S->rec->line=i*(-1);
      S->rec->id_head=0;

    }
    else{
      S->next=NULL;
      S->up=malloc(sizeof(skip_node));
      S=S->up;
      S->down=HELP_DOWN;
      S->rec=malloc(sizeof(record));
      strcpy(S->rec->id,num_id);
      S->rec->line=i*(-1);
      S->rec->id_head=0;
    }

    i=i+1;
    HELP_DOWN=S;
  }
  S->up=NULL;
  S->next=NULL;
  S->down=HELP_DOWN;

  return S;
}

void constractor_array_pos(skip_node** k_pos ,skip_node* S){
  for(int i=0 ; i<=9 ; i++){
    k_pos[i]=malloc(sizeof(skip_node));
    k_pos[i]->rec=malloc(sizeof(record));
    if(i!=0){
      k_pos[i]->rec->check_coin=-1;
    }
  }
  int i=0;
  while(i<=8 || S->up!=NULL){
    k_pos[i] = S;
    S=S->up;
    i=i+1;
  }

}

int my_rand(){
  int k=rand()%2;
  return k;
}

record * find_the_rec(skip_node *S, char* id ,char *ios ){
  // printf("0000000000000\n" );
    while (S->down!=NULL) {
        skip_node * TEMP=malloc(sizeof(skip_node));
          while(S->next!=NULL){
              // printf("1111111111111\n" );
                  int s_rec_id=atoi(S->rec->id);
                  int my_rec_id=atoi(id);
                  // printf("my_rec_id1 is %d\n",my_rec_id );
                  // printf("s_rec_id1 is %d\n",s_rec_id);
                      if(my_rec_id <= s_rec_id){
                        // printf("1111111111111.111111111111\n" );
                          if(my_rec_id == s_rec_id){
                              S->rec->find=1;
                              return S->rec;
                            }
                          else{
                            TEMP=TEMP->down;
                            return find_the_rec( TEMP ,id ,ios);
                          }
                      }
                TEMP=S;
              S=S->next;
          }
          if(S->next==NULL){
            // printf("222222222222222\n" );
            int s_rec_id=atoi(S->rec->id);
            int my_rec_id=atoi(id);
            // printf("my_rec_id1 is %d\n",my_rec_id );
            // printf("s_rec_id1 is %d\n",s_rec_id);
            // if(my_rec_id <= s_rec_id){
              // printf("22222222222222.111111111111\n" );

                if(my_rec_id == s_rec_id){
                    S->rec->find=1;
                    return S->rec;
                  }
                else{
                  TEMP=TEMP->down;
                  return find_the_rec( TEMP ,id ,ios);
                }
              // }
              // else{}
          }
      }
      if(S->down==NULL){
        // printf("33333333333333333\n" );
        while(S->next!=NULL){
          // printf("33333333333333333.11111111111\n" );
                int s_rec_id=atoi(S->rec->id);
                int my_rec_id=atoi(id);
                // printf("my_rec_id1 is %d\n",my_rec_id );
                // printf("s_rec_id1 is %d\n",s_rec_id);
                    if(my_rec_id <= s_rec_id){
                        if(my_rec_id == s_rec_id){
                            S->rec->find=1;
                            return S->rec;
                          }
                        else{
                          record* rec=malloc(sizeof(record));
                          rec->find=0;
                          return rec;
                        }
                    }
            S=S->next;
        }
        if(S->next==NULL){
          // printf("33333333333333333.2222222222222\n" );
          int s_rec_id=atoi(S->rec->id);
          int my_rec_id=atoi(id);
          // printf("my_rec_id1 is %d\n",my_rec_id );
          // printf("s_rec_id1 is %d\n",s_rec_id);
              if(my_rec_id == s_rec_id){
                  // printf("vrethike %s\n", S->rec->id );
                  S->rec->find=1;
                  return S->rec;
                }
                else{
                  record* rec=malloc(sizeof(record));
                  rec->find=0;
                  return rec;
                }
        }
      }
  }

record * find_the_rec_no(skip_node *S, char* id ){
  // printf("0000000000000\n" );
    while (S->down!=NULL) {
        skip_node * TEMP=malloc(sizeof(skip_node));
          while(S->next!=NULL){
              // printf("1111111111111\n" );
                  int s_rec_id=atoi(S->rec->id);
                  int my_rec_id=atoi(id);
                  // printf("my_rec_id1 is %d\n",my_rec_id );
                  // printf("s_rec_id1 is %d\n",s_rec_id);
                      if(my_rec_id <= s_rec_id){
                        // printf("1111111111111.111111111111\n" );
                          if(my_rec_id == s_rec_id){
                              S->rec->find=1;
                              printf("FIRST ID %s\n",id );
                              printf(" on %s \n", S->rec->date );
                              printf(" on %s \n", S->rec->id );
                              printf(" on %s \n", S->rec->country );
                              //return S->rec;
                            }
                          else{
                            TEMP=TEMP->down;
                            return find_the_rec_no( TEMP ,id );
                          }
                      }
                TEMP=S;
              S=S->next;
          }
          if(S->next==NULL){
            // printf("222222222222222\n" );
            int s_rec_id=atoi(S->rec->id);
            int my_rec_id=atoi(id);
            // printf("my_rec_id1 is %d\n",my_rec_id );
            // printf("s_rec_id1 is %d\n",s_rec_id);
            // if(my_rec_id <= s_rec_id){
              // printf("22222222222222.111111111111\n" );

                if(my_rec_id == s_rec_id){
                    S->rec->find=1;
                    //return S->rec;
                    printf("FIRST ID %s\n",id );
                    printf(" on %s \n", S->rec->date );
                    printf(" on %s \n", S->rec->id );
                    printf(" on %s \n", S->rec->country );
                  }
                else{
                  TEMP=TEMP->down;
                  return find_the_rec_no( TEMP ,id );
                }
              // }
              // else{}
          }
      }
      if(S->down==NULL){
        // printf("33333333333333333\n" );
        while(S->next!=NULL){
          // printf("33333333333333333.11111111111\n" );
                int s_rec_id=atoi(S->rec->id);
                int my_rec_id=atoi(id);
                // printf("my_rec_id1 is %d\n",my_rec_id );
                // printf("s_rec_id1 is %d\n",s_rec_id);
                    if(my_rec_id <= s_rec_id){
                        if(my_rec_id == s_rec_id){
                            S->rec->find=1;
                            // return S->rec;
                            printf("FIRST ID %s\n",id );
                            printf(" on %s \n", S->rec->date );
                            printf(" on %s \n", S->rec->id );
                            printf(" on %s \n", S->rec->country );
                          }
                        else{
                          record* rec=malloc(sizeof(record));
                          rec->find=0;
                          return rec;
                        }
                    }
            S=S->next;
        }
        if(S->next==NULL){
          // printf("33333333333333333.2222222222222\n" );
          int s_rec_id=atoi(S->rec->id);
          int my_rec_id=atoi(id);
          // printf("my_rec_id1 is %d\n",my_rec_id );
          // printf("s_rec_id1 is %d\n",s_rec_id);
              if(my_rec_id == s_rec_id){
                  // printf("vrethike %s\n", S->rec->id );
                  S->rec->find=1;
                  // return S->rec;
                  printf("FIRST ID %s\n",id );
                  printf(" on %s \n", S->rec->date );
                  printf(" on %s \n", S->rec->id );
                  printf(" on %s \n", S->rec->country );
                }
                else{
                  record* rec=malloc(sizeof(record));
                  rec->find=0;
                  // printf("FIRST ID %s\n",id );
                  // // return rec;
                  // printf(" on %s \n", S->rec->date );
                  // printf(" on %s \n", S->rec->id );
                  // printf(" on %s \n", S->rec->country );
                }
        }
      }
  }

skip_node * find_the_first_null_node(skip_node *S){
    if(S->next==NULL){
      return S;
    }
    while(S->up!=NULL){
      if(S->next==NULL){
        return S->down;
      }
      S=S->up;
    }
    if(S->up==NULL){
      return S;
    }
  }

int compare_date(char *current_date , char * rec_date){
  char date1[14];
  char month1[14];
  char date2[14];
  char month2[14];
  char date3[14];
  char month3[14];
  char date4[14];
  char month4[14];
  char year1[14];


  strcpy(date1 , current_date);
  strcpy(month1 , current_date);
  strcpy(date2 , current_date);
  strcpy(month2 , current_date);
  strcpy(date3 , current_date);
  strcpy(month3 , current_date);

  strcpy(year1 , current_date);
  // printf("strlen is %d\n",strlen(year1) );

  if(strlen(year1)==8){
    str_cut(date1,1,7);
    str_cut(date2,0,2);
    str_cut(date2,1,6);
    strcpy(month1,date2);

  }
  if(strlen(year1)==9){
    str_cut(date1,1,9);
    str_cut(date2,0,1);
    str_cut(date2,1,8);
    if(strcmp(date2,"-")==0){

      str_cut(date3,0,2);
      str_cut(date3,2,7);
      strcpy(month1,date3);

    }
    else{
       strncat(date1, &date2, strlen(date2)+1);
      str_cut(date3,0,3);
      str_cut(date3,1,8);
      strcpy(month1,date3);

    }

  }
  if(strlen(year1)==11){
    str_cut(date1,2,9);
    str_cut(month1,0,3);
    str_cut(month1,2,8);
  }
  // if(strlen(year1)==11){
  //   str_cut(date1,2,10);
  //   str_cut(month1,0,3);
  //   str_cut(month1,2,7);
  // }

   strcpy(year1,(year1  + strlen(year1) - 4) );

  char date_1[14];
  char month_1[14];
  char date_2[14];
  char month_2[14];
  char date_3[14];
  char month_3[14];
  char date_4[14];
  char month_4[14];
  char year_1[14];


  strcpy(date_1 , rec_date);
  strcpy(month_1 , rec_date);
  strcpy(date_2 , rec_date);
  strcpy(month_2 , rec_date);
  strcpy(date_3 , rec_date);
  strcpy(month_3 , rec_date);

  strcpy(year_1 , rec_date);

  if(strlen(year_1)==9){
    str_cut(date_1,1,9);
    str_cut(date_2,0,2);
    str_cut(date_2,1,7);
    strcpy(month_1,date_2);

  }
  if(strlen(year_1)==10){
    str_cut(date_1,1,10);
    str_cut(date_2,0,1);
    str_cut(date_2,1,9);
    if(strcmp(date_2,"-")==0){

      str_cut(date_3,0,2);
      str_cut(date_3,2,8);
      strcpy(month_1,date_3);

    }
    else{
       strncat(date_1, &date_2, strlen(date_2)+1);
      str_cut(date_3,0,3);
      str_cut(date_3,1,7);
      strcpy(month_1,date_3);

    }

  }
  if(strlen(year_1)==11){
    str_cut(date_1,2,10);
    str_cut(month_1,0,3);
    str_cut(month_1,2,7);
  }

  strcpy(year_1,(year_1  + strlen(year_1) - 5) );

  // printf("DATE current_date %s\n", current_date );
  // printf("### date %s month %s year %s \n",date1 ,month1 ,year1 );
  // printf("DATE rec %s\n", rec_date );
  // printf("@@@ date %s month %s year %s \n", date_1 , month_1 , year_1  );
  int yeac1=atoi(year1);
  int yea_1=atoi(year_1);
  int monc1=atoi(month1);
  int mon_1=atoi(month_1);
  int datc1=atoi(date1);
  int dat_1=atoi(date_1);
  // printf("disciunt is %d\n",yeac1-yea_1 );

  if(yeac1-yea_1>=2){
    return 0;
  }
  else if(yeac1-yea_1==1){
    monc1=monc1+12;
    // printf("YESSS\n" );
    if(monc1 - mon_1 >= 7){
      return 0;
    }
    else if(monc1 - mon_1 <= 5 ){
      return 1;
    }
    else if(monc1 - mon_1 == 6 ){
      if(datc1 >= dat_1){
        return 0;
      }
      else{
        return 1;
      }
    }
  }
  else if(yeac1-yea_1==0){
    if(monc1 - mon_1 >= 7){
      return 0;
    }
    else if(monc1 - mon_1 <= 5 ){
      return 1;
    }
    else if(monc1 - mon_1 == 6 ){
      if(datc1 >= dat_1){
        return 0;
      }
      else{
        return 1;
      }
    }
  }
  else if(yeac1-yea_1<0){
    return 1;

  }
}

int compare_date_range(char *current_date , char * rec_date){
  char date1[14];
  char month1[14];
  char date2[14];
  char month2[14];
  char date3[14];
  char month3[14];
  char date4[14];
  char month4[14];
  char year1[14];


  strcpy(date1 , current_date);
  strcpy(month1 , current_date);
  strcpy(date2 , current_date);
  strcpy(month2 , current_date);
  strcpy(date3 , current_date);
  strcpy(month3 , current_date);

  strcpy(year1 , current_date);
   // printf("strlen is %d\n",strlen(year1) );

  if(strlen(year1)==8){
    str_cut(date1,1,7);
    str_cut(date2,0,2);
    str_cut(date2,1,6);
    strcpy(month1,date2);

  }
  if(strlen(year1)==9){
    str_cut(date1,1,9);
    str_cut(date2,0,1);
    str_cut(date2,1,8);
    if(strcmp(date2,"-")==0){

      str_cut(date3,0,2);
      str_cut(date3,2,7);
      strcpy(month1,date3);

    }
    else{
       strncat(date1, &date2, strlen(date2)+1);
      str_cut(date3,0,3);
      str_cut(date3,1,8);
      strcpy(month1,date3);

    }

  }
  if(strlen(year1)==10){
    str_cut(date1,2,9);
    str_cut(month1,0,3);
    str_cut(month1,2,8);
  }


   strcpy(year1,(year1  + strlen(year1) - 4) );

  char date_1[14];
  char month_1[14];
  char date_2[14];
  char month_2[14];
  char date_3[14];
  char month_3[14];
  char date_4[14];
  char month_4[14];
  char year_1[14];


  strcpy(date_1 , rec_date);
  strcpy(month_1 , rec_date);
  strcpy(date_2 , rec_date);
  strcpy(month_2 , rec_date);
  strcpy(date_3 , rec_date);
  strcpy(month_3 , rec_date);

  strcpy(year_1 , rec_date);

  if(strlen(year_1)==8){
    str_cut(date_1,1,8);
    str_cut(date_2,0,2);
    str_cut(date_2,1,6);
    strcpy(month_1,date_2);

  }
  if(strlen(year_1)==9){
    str_cut(date_1,1,9);
    str_cut(date_2,0,1);
    str_cut(date_2,1,7);
    if(strcmp(date_2,"-")==0){

      str_cut(date_3,0,2);
      str_cut(date_3,2,7);
      strcpy(month_1,date_3);

    }
    else{
       strncat(date_1, &date_2, strlen(date_2)+1);
      str_cut(date_3,0,3);
      str_cut(date_3,1,6);
      strcpy(month_1,date_3);

    }

  }
  if(strlen(year_1)==10){
    str_cut(date_1,2,9);
    str_cut(month_1,0,3);
    str_cut(month_1,2,8);
  }

  strcpy(year_1,(year_1  + strlen(year_1) - 4) );

  // // printf("DATE current_date %s\n", current_date );
  // // printf("### date %s month %s year %s \n",date1 ,month1 ,year1 );
  // // printf("DATE rec %s\n", rec_date );
  // // printf("@@@ date %s month %s year %s \n", date_1 , month_1 , year_1  );
 int yeac1=atoi(year1);
  int yea_1=atoi(year_1);
  int monc1=atoi(month1);
  int mon_1=atoi(month_1);
  int datc1=atoi(date1);
  int dat_1=atoi(date_1);
  //printf("disciunt is %d\n",yeac1-yea_1 );
  yeac1 = (yeac1*365) + (monc1*30) + datc1;
  yea_1 = (yea_1*365) + (mon_1*30) + dat_1;
  // printf("yeaccc 1oo%d\n",yeac1 );
  // printf("yeaccc 2oo%d\n",yea_1 );
  if(yeac1-yea_1>=0){
    // printf("000000\n" );
    return 0;
  }
  else{
    // printf("1111111111\n" );
    return 1;
  }

}

int check_for_empty(char * ch){
    if ((ch != NULL) && (ch[0] == '\0')) {
        return 1;
    }
    else if (strlen(ch)<=1){
      return 1;
    }
    else{
      return 0;
    }
  }

int vaccineStatus(HList* H , char *id , char *ios , char * current_date ){
    int check=0;

      if(!check_for_empty(ios)){
        while(H->next!=NULL){
            if(strcmp(H->type , ios)==0){
              // printf("H->typEEEEEEEEEEEEEEe is %s and %s \n",H->type ,ios );
              record * rec=malloc(sizeof(record));
              skip_node * S=malloc(sizeof(skip_node));
               S=find_the_first_null_node(H->type->yes);
               rec=find_the_rec(S , id , ios);
               if(rec->find==1){
                    check=1;
                    // char current_date[20];
                    // date(current_date);
                    int result = compare_date(current_date , rec->date);

                    if(result==1){
                      printf("REQUEST REJECTED – YOU WILL NEED ANOTHER VACCINATION BEFORE TRAVEL DATE\n" );
                      printf("id is ##### %s\n",rec->id );
                      return 1;
                    }
                    if(result==0){
                      printf("REQUEST ACCEPTED – HAPPY TRAVELS\n" );
                      printf("id is ##### %s\n",rec->id );
                      printf("id is ##55555### %s\n",rec->age );
                      return 0;
                    }

               }
               S=find_the_first_null_node(H->type->no);
               rec=find_the_rec(S , id , ios);
               if(rec->find==1){
                 check=1;
                 printf("REQUEST REJECTED – YOU ARE NOT VACCINATED  \n" );
                 printf("id is ##### %s\n",rec->id );
                 return 1;
               }
            }
            H=H->next;
         }

       }
       else{
         while(H->next!=NULL){
               record * rec=malloc(sizeof(record));
               skip_node * S=malloc(sizeof(skip_node));
                S=find_the_first_null_node(H->type->yes);
                rec=find_the_rec(S , id , ios);
                if(rec->find==1){
                     check=1;
                     // char current_date[20];
                     // date(current_date);
                     int result = compare_date(current_date , rec->date);

                     if(result==1){
                       printf("REQUEST REJECTED – YOU WILL NEED ANOTHER VACCINATION BEFORE TRAVEL DATE\n" );
                       printf("id is ##### %s\n",rec->id );
                       return 1;
                     }
                     if(result==0){
                       printf("REQUEST ACCEPTED – HAPPY TRAVELS\n" );
                       printf("id is ##### %s\n",rec->id );
                       printf("id is ##55555### %s\n",rec->age );
                       return 0;
                     }

                }
                S=find_the_first_null_node(H->type->no);
                rec=find_the_rec(S , id , ios);
                if(rec->find==1){
                  check=1;
                  printf("REQUEST REJECTED – YOU ARE NOT VACCINATED  \n" );
                  printf("id is ##### %s\n",rec->id );
                  return 1;
                }

             H=H->next;
          }
       }
       if(check==0){
         printf("NOT INFORMATION\n" );

       }
   }

record* vaccineStatus_info(HList* H , char *id ){
 int check=0;

 record * rec=malloc(sizeof(record));

     while(H->next!=NULL){
       printf("H->typEEEEEEEEEEEEEEe is  and %s  \n" ,H->type->name );

           skip_node * S=malloc(sizeof(skip_node));
            S=find_the_first_null_node(H->type->yes);
            find_the_rec_no(S , id );
            // // rec=find_the_rec_no(S , id );
            // if(rec->find==1){
            //      check=1;
            //
            //       printf(" on %s \n", rec->date );
            //       printf(" on %s \n", rec->id );
            //       printf(" on %s \n", rec->country );
            //     //  return rec;
            // }
            S=find_the_first_null_node(H->type->no);
            // rec=
            find_the_rec_no(S , id );
            // if(rec->find==1){
            //   check=1;
            //   printf("NOOO vacinated from  \n" );
            //   printf(" on %s \n", rec->date );
            //   printf(" on %s \n", rec->id );
            //   printf(" on %s \n", rec->country );
            //   //return rec;
            // }

         H=H->next;
      }
      rec->find=0;
      return rec;
    }

skip_node * initiaze_skip_node(skip_node *S ,record * my_rec){
  S->rec=malloc(sizeof(record));
  strcpy(S->rec->first_name , my_rec->first_name);
  strcpy(S->rec->last_name , my_rec->last_name);
  strcpy(S->rec->id , my_rec->id);
  strcpy(S->rec->ios , my_rec->ios);
  strcpy(S->rec->country , my_rec->country);
  strcpy(S->rec->age , my_rec->age);
  strcpy(S->rec->vacine , my_rec->vacine);
  strcpy(S->rec->date , my_rec->date);
  strcpy(S->rec->extraDate , my_rec->extraDate);
  S->rec->check_coin=malloc(sizeof(int));
  S->rec->check_coin=my_rand();
  S->rec->position=malloc(sizeof(skip_node));
  S->rec->position=my_rec->position;
  S->rec->line=my_rec->line;

  return S;

}


skip_node * find_the_first_line(skip_node *S, record* my_rec ,skip_node **k_pos){


    while (S->down!=NULL) {
        skip_node * TEMP=malloc(sizeof(skip_node));
          while(S->next!=NULL){

                  int s_rec_id=atoi(S->rec->id);
                  int my_rec_id=atoi(my_rec->id);
              if(my_rec_id < s_rec_id){
                     int  num_line=TEMP->rec->line*(-1);
                     k_pos[num_line]=TEMP;
                    TEMP=TEMP->down;

                    return find_the_first_line( TEMP ,my_rec, k_pos);
                }
                TEMP=S;
              S=S->next;
          }
          if(S->next==NULL){
            int s_rec_id=atoi(S->rec->id);
            int my_rec_id=atoi(my_rec->id);
                if(my_rec_id < s_rec_id){
                  // k_pos=retain_position(TEMP , TEMP ,k_pos);
                   int  num_line=TEMP->rec->line*(-1);
                   k_pos[num_line]=TEMP;
                   TEMP=TEMP->down;
                   return find_the_first_line( TEMP  ,my_rec ,  k_pos);
                }
                else{
                  int  num_line=TEMP->rec->line*(-1);
                  k_pos[num_line]=S;
                  S=S->down;
                   skip_node *L=malloc(sizeof(skip_node));
                   L=S->down;
                   if(L!=NULL){
                 }
                  return find_the_first_line( S , my_rec , k_pos);
                }
          }
      }
      if(S->down==NULL){
        return S;
      }

}

skip_node * insert_node_for_up(skip_node *S ,skip_node * TEMP_POSITION , record* my_rec ){
  S->next=constractor_node();
  record *temp_record = malloc(sizeof(record));
  temp_record->position=malloc(sizeof(skip_node));
  temp_record->position=S->next;
  S=S->next;
  S->down=my_rec->position;
  S->next=NULL;
  my_rec->position=temp_record->position;
  S=initiaze_skip_node(S , my_rec);
  TEMP_POSITION->up=malloc(sizeof(skip_node));
  TEMP_POSITION->up=S;
  return S;

}


skip_node* insert_node(skip_node *S , record * my_rec){
  if(S->next==NULL){
  }
    S->next=constractor_node();
    my_rec->position=malloc(sizeof(skip_node));
    my_rec->position=S->next;
    my_rec->line=S->rec->line;
    S=S->next;
    S=initiaze_skip_node(S,my_rec);

    S->next=NULL;

    return S;
  }

skip_node* give_node(skip_node *TEMP , skip_node **k_pos){
      int  num_line=TEMP->rec->line*(-1);
      return k_pos[num_line];

  }

skip_node * up_the_list(skip_node *START , skip_node *S,record * my_rec , skip_node ** k_pos){

     char i[20];
     char k[20];
     strcpy(i,"0");
     strcpy(k,"-2");
     skip_node *S_TEMP=malloc(sizeof(skip_node));
     skip_node *S_NEXT=malloc(sizeof(skip_node));
     S_TEMP=S;



     if( START->next==NULL && START->rec->id_head==0 ){
           skip_node *T=malloc(sizeof(skip_node));
           T=START;
           my_rec->line = T->rec->line;

           T->next=malloc(sizeof(skip_node));
           T=T->next;
           T->down=S;
           T->rec=malloc(sizeof(record));
          initiaze_skip_node(T,my_rec);
          S_TEMP->up=T;
          return START;

         }
      else {
        skip_node *DEEP=malloc(sizeof(skip_node));
        skip_node *TEMP=malloc(sizeof(skip_node));

        S=give_node(START , k_pos);
        int num_id=S->rec->line;

        while(S->next!=NULL){
          if(S->rec->id!=NULL){
           int s_rec_id=atoi(S->rec->id);
          int my_rec_id=atoi(my_rec->id);
              if(my_rec_id < s_rec_id){
                      TEMP=initiaze_skip_node(TEMP,my_rec);
                      TEMP->rec->line=num_id;
                      TEMP->next=DEEP->next;
                      DEEP->next=TEMP;
                      TEMP->down=malloc(sizeof(skip_node));
                      TEMP->down=my_rec->position;
                      S_TEMP->up=malloc(sizeof(skip_node));
                      S_TEMP->up=TEMP;
                      // skip_node *NAI=malloc(sizeof(skip_node));
                      // NAI=my_rec->position;

                        break;
                    }
            }

            DEEP=S;
           S=S->next;
        }
        if(S->next==NULL){
          if (S->rec!=NULL) {
             int s_rec_id=atoi(S->rec->id);
            int my_rec_id=atoi(my_rec->id);
                if(my_rec_id < s_rec_id){
                    TEMP=initiaze_skip_node(TEMP,my_rec);
                    TEMP->rec->line=num_id;
                    TEMP->next=DEEP->next;
                    DEEP->next=TEMP;
                    //print_node(TEMP);
                    TEMP->down=malloc(sizeof(skip_node));
                    TEMP->down=my_rec->position;
                    S_TEMP->up=malloc(sizeof(skip_node));
                    S_TEMP->up=TEMP;
                    S_NEXT=S_TEMP->up;
                  }
                else{
                  TEMP=insert_node_for_up(S , S_TEMP , my_rec); //kanw initiaze tin swsti thesi
                }
          }
        }
        if(TEMP->rec->check_coin==1 ){                       //if have START(between 0 or 1 is 0) so do then
            int pos = TEMP->rec->line*(-1)+1;
            if(pos<8){
              return  up_the_list( k_pos[pos] , TEMP , my_rec , k_pos);
            }
          }



      else{

        //return START;
      }

    }
   }

skip_node * down_the_list(skip_node *HEAD ,skip_node *S , record *my_rec ,skip_node **k_pos){

  S=HEAD;

  char i[20];  char k[20];  strcpy(i,"-2"); strcpy(k,"1");


  S=find_the_first_null_node(HEAD);
  S=find_the_first_line(S, my_rec , k_pos);



  if(S->down==NULL){ // if you are in last level , you can this
    skip_node *S_TEMP=malloc(sizeof(skip_node));
    skip_node *DEEP=malloc(sizeof(skip_node));
    skip_node *TEMP=malloc(sizeof(skip_node));
    S_TEMP=S;                               //retain the first node which you start, as you start the up level from here
    DEEP=S;                    //retain the node before you go to next node so you have the correct index
    while(S->next!=NULL){                //during which you read the item inside the list if you do not find smaller than new record go to end
      int s_rec_id=atoi(S->rec->id);
      int my_rec_id=atoi(my_rec->id);
      if(my_rec_id < s_rec_id){                //compere the new record with every item in list
        initiaze_skip_node(TEMP,my_rec);  // if have correct situasion initiaze the new record TEMP
        TEMP->rec->line=0;
        my_rec->position=malloc(sizeof(skip_node));
        TEMP->next=DEEP->next;          //put the correct place as have shorted list
        DEEP->next=TEMP;
        my_rec->position=TEMP;
        break;
      }
      DEEP=S;                    //retain the node before you go to next node so you have the correct index
      S=S->next;
    }
    if(S->next==NULL){            // if you go the end without you find smaller item than items's in list then
    int s_rec_id=atoi(S->rec->id);
    int my_rec_id=atoi(my_rec->id);
    if(my_rec_id < s_rec_id){                        //compere the new record with last item in list
      initiaze_skip_node(TEMP,my_rec);            // if have correct situasion initiaze the new record TEMP
      TEMP->rec->line=0;
      my_rec->position=malloc(sizeof(skip_node));
      TEMP->next=DEEP->next;                       //put the correct place as have shorted list
      DEEP->next=TEMP;
      my_rec->position=TEMP;
    }

    else{
      TEMP=insert_node(S,my_rec);              //kanw initiaze tin swsti thesi
    }
  }

  if(TEMP->rec->check_coin==1 ){                       //if have head(between 0 or 1 is 0) so do then

    skip_node* START=malloc(sizeof(skip_node));
    START=S_TEMP->up;
    if(START->next==NULL){
    }
    return up_the_list(S_TEMP->up ,TEMP , my_rec ,k_pos);

  }
  else{

    return HEAD;
  }
}
}

void print_to_skip_list( skip_node *S){
  //S=S->next;
    while (S->next!=NULL) {

      printf("idd is %s  check ios %s rec line %d and date %s\n",S->rec->id ,S->rec->ios ,S->rec->line ,S->rec->date);
      S=S->next;
    }
    printf("iddd is %s  check coin %s rec line %d and date %s\n",S->rec->id ,S->rec->ios , S->rec->line ,S->rec->date);


}

void print_ssimple_list(Slist *S ){
  FILE* fp;
  fp = fopen("log.txt", "w");
  char* data[30] ;

    while(S->next!=NULL){
      printf("IS ID IS %s\n",S->rec->id );
      // Generate whatever you want logged here, "data" is just an example
      // strcpy(data , S)
      // This lines writes the info in "data" to the file pointer specified
      fputs(S->rec->id, fp);

      // Always remember to close your files
      // fclose(fp);

      return EXIT_SUCCESS;
      //printf("IS ID IS %s\n",S->rec->ios );

      S=S->next;
    }

    printf("IS ID IS %s\n",S->rec->id );
    fputs(S->rec->id, fp);

    // Always remember to close your files
    fclose(fp);

}

void print_up_list( skip_node *S){
  print_to_skip_list(S);
  printf("\n" );
  S=S->up;
    while (S->up!=NULL && S->next!=NULL) {

      print_to_skip_list(S);
      printf("\n" );
      S=S->up;
    }
    //print_to_skip_list(S);
    printf("\n" );
    printf("\n" );
}

void print_CList(CList* H){
  HList* V=malloc(sizeof(HList));

  while(H->next!=NULL){
    V=H->flag->next;
    while(V->next!=NULL){
      print_up_list(V->type->yes);
      print_up_list(V->type->no);
      V=V->next;
    }
    print_up_list(V->type->yes);
    print_up_list(V->type->no);
    H=H->next;
  }

}

void print_CList_check(CList* H ,char* my_country , char *my_virus){
  HList* V=malloc(sizeof(HList));

  while(H->next!=NULL){
   if(strcmp(H->flag->name_country , my_country)==0){
      V=H->flag->next;
      while(V->next!=NULL){
        print_to_skip_list(V->type->yes);
        //print_to_skip_list(V->type->no);
        V=V->next;
      }
      print_to_skip_list(V->type->yes);
    //print_to_skip_list(V->type->no);
      H=H->next;
    }
  }
  if(strcmp(H->flag->name_country , my_country)==0){
    V=H->flag->next;
    while(V->next!=NULL){
      print_up_list(V->type->yes);
      print_up_list(V->type->no);
      V=V->next;
    }
    print_up_list(V->type->yes);
    print_up_list(V->type->no);
    H=H->next;
  }
}

HList * list_node_create(){
  HList* L=(HList *)malloc(sizeof(HList));
  L->type=malloc(sizeof(Virus));
  L->type->yes=malloc(sizeof(skip_node));
  L->type->no=malloc(sizeof(skip_node));
  constractor_skip_list(L->type->yes);
  constractor_skip_list(L->type->no);
  L->type->count_no=0;
  L->type->count_yes=0;

  L->next=NULL;
  return L;
}

Slist * simple_list_create(){
  Slist* S= (Slist *)malloc(sizeof(Slist));
  // S->next=NULL;
  return S;
}
Slist * simple_list_create_n(){
  Slist* S= (Slist *)malloc(sizeof(Slist));
   S->next=NULL;
  return S;
}

int find_simple_list_request(Slist *S , record* my_rec){
  // printf("kalisperaaa %s\n",my_rec->country );
  int s,i_d,num=0 , result=1;

    while(S->next!=NULL){
      s=atoi(S->rec->id);
      i_d=atoi(my_rec->id);

      if(s==i_d){
        // printf("kalisperaaa %d\n",s );
        if(strcmp(my_rec->country , S->rec->country)==0){
          // printf("kalisperaaa %s\n", S->rec->country);
         if(strcmp(my_rec->vacine , S->rec->ios)==0 ){
          // printf("ID IS %s\n",S->rec->ios );
            if(strcmp(S->rec->vacine,"YES")==0){
                result = compare_date(my_rec->date , S->rec->date);
                  if(result==0){
                    printf("REQUEST ACCEPTED – HAPPY TRAVELS\n" );
                    return 0;
                  }
                  else{
                    printf("REQUEST REJECTED – YOU WILL NEED ANOTHER VACCINATION BEFORE TRAVEL DATE\n" );
                    return 1;
                  }
            }
            else{
            printf("REQUEST REJECTED – YOU ARE NOT VACCINATED  \n" );
            return 1;
            }
          }
          // else{
          //   printf("NOT RESULT WITH THIS INFORMATION\n" );
          //   return 1;
          // }

        }
        // else{
        //   printf("NOT RESULT WITH THIS INFORMATION\n" );
        //   return 1;
        // }

      }
      // else{
      //   printf("NOT RESULT WITH THIS INFORMATION\n" );
      //   return 1;
      // }
      S=S->next;
    }
    if(s==i_d){
      num++;
    }
    return num;
}

int find_simple_list_num(Slist *S , char * id ){
  int s,i_d,num=0;
    while(S->next!=NULL){
      s=atoi(S->rec->id);
      i_d=atoi(id);

      if(s==i_d){
          num++;
      }

      S=S->next;
    }
    if(s==i_d){
      num++;
    }
    return num;
}

Slist* find_simple_list_rec(Slist *S , char * id  ){

  record *my_rec=malloc(sizeof(record));
  int s,i_d,num=0;
    while(S->next!=NULL){
      s=atoi(S->rec->id);
      i_d=atoi(id);

      if(s==i_d){
          // strcpy(my_rec->id,S->rec->id);
          // strcpy(my_rec->first_name,S->rec->first_name);
          // strcpy(my_rec->last_name,S->rec->last_name);
          // strcpy(my_rec->age,S->rec->age);
          // strcpy(my_rec->ios,S->rec->ios);
          // strcpy(my_rec->vacine,S->rec->vacine);

          //printf("RECC ID %s\n",my_rec->id );
          // insert_simple(TEMP_L , my_rec);
          return S;
      }

      S=S->next;
    }
    if(s==i_d){
      num++;
    }

}

int print_simple_list(Slist *S , char * so){
    while(S->next!=NULL){
      //printf("IS ID IS %s\n",S->rec->directory );
      if(strcmp(S->rec->directory,so)==0){
        return 0;
        break;
      }
      //printf("IS ID IS %s\n",S->rec->ios );

      S=S->next;
    }
    return 1;
    // printf("IS ID IS %s\n",S->rec->directory );
}

void print_list(Slist *S ){
    while(S->next!=NULL){
      printf("IS ID IS %s\n",S->rec->ios );
      printf("IS ID IS %s\n",S->rec->countryto );
    //  printf("IS ID IS %s\n",S->rec->directory );
      // printf("IS ID IS %s\n",S->rec->first_name );
      // printf("IS ID IS %s\n",S->rec->last_name );

      S=S->next;
    }
}

void insert_simple_list(Slist *S , record *rec){

  // printf("I AM ID %s\n" , S->rec->id );

  while(S->next!=NULL){
     // printf("I AM ID %s\n" , S->rec->id );
      S=S->next;
    }
    if(S->next==NULL){
      S->rec=malloc(sizeof(record));
      memcpy(S->rec , rec , sizeof(record));
      S->next=(Slist *)malloc(sizeof(Slist));
      // printf("I AM ID %s\n" , S->rec->id );
      // S->next=NULL;
    }



}

void insert_simple(Slist *S , record *rec){

  while(S->next!=NULL){
    // printf("I AM ID %s\n" , S->rec->id );
      S=S->next;
  }
  if(S->next==NULL){
    S->rec=malloc(sizeof(record));
    memcpy(S->rec , rec , sizeof(record));
    S->next=(Slist *)malloc(sizeof(Slist));
    S=S->next;
    S->next=NULL;
  }
}
void insert_simple_country(Slist *S , record *rec){

  while(S->next!=NULL){
    if(strcmp(rec->countryto , S->rec->countryto )==0 && strcmp(rec->ios , S->rec->ios )==0){
      return 0;
    }

      S=S->next;
  }
  if(S->next==NULL){
    S->rec=malloc(sizeof(record));
    strcpy(S->rec->countryto , rec->countryto);
    strcpy(S->rec->ios , rec->ios );
    // memcpy(S->rec , rec , sizeof(record));
    S->next=(Slist *)malloc(sizeof(Slist));
    S=S->next;
    S->next=NULL;
  }
}

void destractor_simple(Slist *S){

  while(S->next!=NULL){
    free(S->rec->id);
    free(S->rec->first_name);
    free(S->rec->last_name);
    free(S->rec->country);
    free(S->rec->countryto);
    free(S->rec->countryfrom);
    free(S->rec->age);
    free(S->rec->ios);
    free(S->rec->vacine);
    free(S->rec->date);
    free(S->rec->extraDate);
    free(S->rec->directory);
     free(S->rec);
    // printf("I AM ID %s\n" , S->rec->id );
    S=S->next;
  }


}

void result_simple_list(Slist *S ,char* virus , char* date1 , char* date2){
  int d1,d2,accept ,reject,sum ;
  accept=0 ,reject=0 ; sum=0;
    while(S->next!=NULL){
      sum+=1;
      if(strcmp(S->rec->ios, virus)==0){
      //  printf("IS ID IS %s\n",S->rec->id );
        d2=compare_date_range(date2, S->rec->date );
        d1=compare_date_range( S->rec->date , date1 );
        if(!d1 && !d2 ){
          if(S->rec->request==0){
            accept+=1;
          }
        // printf("IS ID1 IS %d\n",d1 );
        // printf("IS ID2 IS %d\n",d2 );
        }
      }

      S=S->next;
    }
    printf("TOTAL REQUESTS %d\n",sum );
    printf("ACCEPTED %d\n", accept );
    printf("REJECTED %d\n", sum - accept );

}
void result_simple_list_country(Slist *S ,char* virus , char* date1 , char* date2 ,char* country){
  int d1,d2,accept ,reject,sum ;
  accept=0 ,reject=0 ; sum=0;
    while(S->next!=NULL){
      if(strcmp(S->rec->countryto, country)==0){
        sum+=1;
        if(strcmp(S->rec->ios, virus)==0){

          d2=compare_date_range(date2, S->rec->date );
          d1=compare_date_range( S->rec->date , date1 );
          if(!d1 && !d2 ){
            if(S->rec->request==0){
              accept+=1;
            }
          }
         }
        }

      S=S->next;
    }

    printf("TOTAL REQUESTS %d\n",sum );
    printf("ACCEPTED %d\n", accept );
    printf("REJECTED %d\n", sum - accept );

}
void result_simple_list_country_log(Slist *HELP , Slist *S_country  ,  char* virus ,  char *log_file){
	Slist * S=simple_list_create_n();
  FILE *fp;

  char my_str[30];

  int d1,d2,accept ,reject,sum ;
  int accept_c ,reject_c,sum_c ;
  accept=0 ,reject=0 ; sum=0;
  while(S_country->next!=NULL){
    accept_c=0 ,reject_c=0 ; sum_c=0;
    S=HELP;
    while(S->next!=NULL){
      if( strcmp(S->rec->countryto, S_country->rec->countryto)==0  /*&& strcmp(S->rec->ios, S_country->rec->ios)==0*/ ){
        sum+=1;
        sum_c+=1;

         if(S->rec->request==0){
           accept_c+=1;
           accept+=1;
         }

         }
      S=S->next;
        }

        fp = fopen(log_file, "a+");
        fprintf(fp,"--------- COUNTRY  " );
        fputs(S_country->rec->countryto,fp );
        fprintf(fp,"-------\n" );
        fprintf(fp,"TOTAL REQUESTS " );
        sprintf(my_str, "%d", sum_c);
        fputs(my_str,fp );
        fprintf(fp,"\n" );
        fprintf(fp,"ACCEPTED " );
        sprintf(my_str, "%d", accept_c);
        fputs(my_str,fp );
        fprintf(fp,"\n" );
        fprintf(fp,"REJECTED ");
        sprintf(my_str, "%d",sum_c-accept_c);
        fputs(my_str,fp );
        fprintf(fp,"\n" );
        fclose(fp);
        S_country=S_country->next;
    }
    fp = fopen(log_file, "a+");
    fprintf(fp,"---------FINALLY RESULT---------  " );
    fprintf(fp,"\n" );
    fprintf(fp,"TOTAL REQUESTS " );
    sprintf(my_str, "%d", sum);
    fputs(my_str,fp );
    fprintf(fp,"\n" );
    fprintf(fp,"ACCEPTED " );
    sprintf(my_str, "%d", accept);
    fputs(my_str,fp );
    fprintf(fp,"\n" );
    fprintf(fp,"REJECTED ");
    sprintf(my_str, "%d",sum-accept);
    fputs(my_str,fp );
    fprintf(fp,"\n" );
    fclose(fp);



  }




CList * list_country_node_create(){
  CList* L=(CList *)malloc(sizeof(CList));
  L->flag=malloc(sizeof(Country));
  L->flag->next=list_node_create();
  HList* H=malloc(sizeof(HList));
  H=L->flag->next;
  H->type->count_no=0;
  H->type->count_yes=0;
  L->flag->count_population=0;
  L->flag->count_vacite_population=0;

  L->next=NULL;
  return L;
}

void print_pos(skip_node ** pos){
  int i=0;
    while (i<=8 ) {

      i+=1;
    }

}

void initiaze_table_vacine(HList * V ,record* my_rec   ){
  // constractor_array_pos( V->type->k_pos_no , V->type->yes );
  // constractor_array_pos( V->k_pos_yes , V->type->no );
  skip_node* S=malloc(sizeof(skip_node));
  while(V->next!=NULL){
      if(strcmp(V->type->name , my_rec->ios)==0){
        if(strcmp(my_rec->vacine,"YES")==0){
          constractor_array_pos( V->type->k_pos_yes , V->type->yes );
          down_the_list(V->type->yes , S ,my_rec , V->type->k_pos_yes);
          V->type->count_yes+=1;
        }
        else{
          constractor_array_pos( V->type->k_pos_no , V->type->no );
          down_the_list(V->type->no , S ,my_rec , V->type->k_pos_no);
          V->type->count_no+=1;
        }
        break;
      }
    V=V->next;
  }
  if(V->next==NULL){
      strcpy(V->type->name , my_rec->ios );
      if(strcmp(my_rec->vacine,"YES")==0){
        constractor_array_pos( V->type->k_pos_yes , V->type->yes );
        down_the_list(V->type->yes , S ,my_rec , V->type->k_pos_yes);
        V->type->count_yes+=1;
      }
      else{
        constractor_array_pos( V->type->k_pos_no , V->type->no );
        down_the_list(V->type->no , S ,my_rec , V->type->k_pos_no);
        V->type->count_no+=1;
      }
      V->next=list_node_create();
      V=V->next;
      if(V->next==NULL){
      }
  }
}

void initiaze_county_table_vacine(CList * V ,record* my_rec   ){
  HList* H=malloc(sizeof(HList));
  // constractor_array_pos( V->type->k_pos_no , V->type->yes );
  // constractor_array_pos( V->k_pos_yes , V->type->no );
  skip_node* S=malloc(sizeof(skip_node));
  while(V->next!=NULL){
     if(strcmp(V->flag->name_country , my_rec->country)==0){
       V->flag->count_population+=1;
         H=V->flag->next;
          while(H->next!=NULL){
            if(strcmp(H->type->name , my_rec->ios)==0){
              if(strcmp(my_rec->vacine,"YES")==0){
                constractor_array_pos( H->type->k_pos_yes , H->type->yes );
                down_the_list(H->type->yes , S ,my_rec , H->type->k_pos_yes);
                  H->type->count_yes+=1;
                  V->flag->count_vacite_population+=1;

              }
              else{
                constractor_array_pos( H->type->k_pos_no , H->type->no );
                down_the_list(H->type->no , S ,my_rec , H->type->k_pos_no);
                  H->type->count_no+=1;
              }
              break;
              }

            H=H->next;
          }
          if(H->next==NULL){
              strcpy(H->type->name , my_rec->ios );
              if(strcmp(my_rec->vacine,"YES")==0){
                constractor_array_pos( H->type->k_pos_yes , H->type->yes );
                down_the_list(H->type->yes , S ,my_rec , H->type->k_pos_yes);
                H->type->count_yes+=1;
                V->flag->count_vacite_population+=1;

                }
              else{
                constractor_array_pos( H->type->k_pos_no , H->type->no );
                down_the_list(H->type->no , S ,my_rec , H->type->k_pos_no);
                H->type->count_no+=1;
                 }
                H->next=list_node_create();
                H=H->next;
              }
          //initiaze_table_vacine(H,my_rec);
              break;
            }
           V=V->next;
   }

  if(V->next==NULL){
          H=V->flag->next;
          V->flag->count_population+=1;
          strcpy(V->flag->name_country , my_rec->country);
          strcpy(H->type->name , my_rec->ios );
          if(strcmp(my_rec->vacine,"YES")==0){
            constractor_array_pos( H->type->k_pos_yes , H->type->yes );
            down_the_list(H->type->yes , S ,my_rec , H->type->k_pos_yes);
            H->type->count_yes+=1;
            V->flag->count_vacite_population+=1;

          }
          else{
            constractor_array_pos( H->type->k_pos_no , H->type->no );
            down_the_list(H->type->no , S ,my_rec , H->type->k_pos_no);
            H->type->count_no+=1;
          }
          H->next=list_node_create();
          H=H->next;
          V->next=list_country_node_create();
          V=V->next;

          // V->flag->next=list_node_create();
          // V->flag->next=V->flag->type->next;

       }

}

void print_HList(HList* H){
    while(H->next!=NULL){
         print_up_list(H->type->yes);
         print_up_list(H->type->no);
          H=H->next;
    }
}

void request_CList(CList* H , char* country){
  HList* V=malloc(sizeof(HList));

  if(!check_for_empty(country)){
    printf("DEN EIAMI EMPTY\n" );

    // while(H->next!=NULL){
    //     V=H->flag->next;
    //     if(strcmp(country , V- ))
    //     while(V->next!=NULL){
    //          print_up_list(V->type->yes);
    //          print_up_list(V->type->no);
    //           V=V->next;
    //         }
    //         print_up_list(V->type->yes);
    //         print_up_list(V->type->no);
    //       H=H->next;
    //   }
  }
  else{
    printf("EIAMI EMPTY\n" );
  }

}
