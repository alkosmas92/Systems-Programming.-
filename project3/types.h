typedef struct name_ {
    unsigned int bits;
}bloom_filter;


typedef struct ios_hash_play{
  char name_ios[20];
  int * bloom;
  bloom_filter *array_bloom;
  struct ios_hash *next;
}ios_hash;

typedef struct my_num{
  int prime;
  char country[25];
}my_num;

typedef struct my_size{
  int flow;
}my_size;





// int int_to_int(int k);
// unsigned long djb2(unsigned char *);
// unsigned long sdbm(unsigned char *);
// unsigned long hash_i(unsigned char *, unsigned int );
