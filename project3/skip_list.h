#define POOL_SIZE 6


typedef struct{
    unsigned int bits;
}bloom_filter;


typedef struct{
  char name_ios[20];
  int * bloom;
  bloom_filter *array_bloom;
  struct ios_hash *next;
}ios_hash;

typedef struct {
  int prime;
  char country[25];
}my_num;

typedef struct {
  int flow;
}my_size;



typedef struct {
  char id[30];
  char first_name[20];
  char last_name[20];
  char country[30];
  char countryto[20];
  char countryfrom[20];
  char age[20];
  char ios[20];
  char vacine[20];
  char date[20];
  char extraDate[20];
  char directory[50];
  int request;
  int check_coin;
  int line;
  int id_head;
  int find;
  struct skip_node * position;
}record;


typedef struct {
  struct  skip_node *next;
  struct  skip_node *up;
  struct  skip_node *down;
  struct  skip_node *previous;
    record *rec;
    int check;
}skip_node;

typedef struct{
  char name[20];
  skip_node* yes;
  skip_node* no;
  skip_node *k_pos_no[10];
  skip_node *k_pos_yes[10];
  int count_no;
  int count_yes;
}Virus;

typedef struct {
  Virus* type;
  struct HList *next;
}HList;


typedef struct{
  char name_country[20];
  int count_vacite_population;
  int count_population;
  struct HList *next;
}Country;


typedef struct {
  Country *flag;
  struct Clist *next;
}CList;

typedef struct {
    record* rec;
    struct Slist *next;
}Slist;


typedef struct {
        int data[POOL_SIZE];
        int start;
        int end;
        int count;
} pool_t;

typedef struct {
  Slist * LC_DIR;
  Slist * A;
  ios_hash *H;
  char file[50];
  int size_bf;
}Sum_struct;


// skip_node *RETAIN=malloc(sizeof(skip_node));
// RETAIN=HEAD;
// HEAD->up=malloc(sizeof(skip_node));
// HEAD=HEAD->up;
// HEAD->next=malloc(sizeof(skip_node));
// HEAD=HEAD->next;
// HEAD=malloc(sizeof(skip_node));
// START=malloc(sizeof(skip_node));
// START->up=NULL;
//
//  START->rec=malloc(sizeof(record));
//  START->next=malloc(sizeof(skip_node));
//  START->down=malloc(sizeof(skip_node));
//  START=START_DOWN;
