#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "skip_list.h"


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

void initiaze_ios_table(ios_hash *H , record * my_rec ,  int tsize ){
  char vac[20]="YES";
  strcpy(H->name_ios,my_rec->ios);
  printf("my_rec ios is %s\n", H->name_ios);
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
                printf("MAYBE\n" );
                return;
            }
            else{
              printf("NOT VACINATED\n" );
              return;
            }
        }

        H=H->next;
      }
      printf("NOT INFORMATION\n" );
    }

ios_hash * create_hash_ios( int size){
  ios_hash *H=malloc(sizeof(ios_hash));
  H->next=NULL;
  return H;
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



void print_hash_table(ios_hash *H){
  //H=H->next;
  while (H->next!=NULL){
    printf("the name is %s\n",H->name_ios);
    H=H->next;
  }
//  printf("the name_ios is %s\n",H->name_ios);
}




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
