
typedef struct {
  char id[20];
  char first_name[20];
  char last_name[20];
  char country[20];
  char age[20];
  char ios[20];
  char vacine[20];
  char date[20];
  char extraDate[20];
  int request;
  int check_coin;
  int line;
  int id_head;
  int find;
  struct skip_node * position;
  struct record *next;
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
