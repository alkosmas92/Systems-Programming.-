typedef struct  {
     int bits;
}bloom_filter;


typedef struct {
  char name_ios[20];
  bloom_filter *array_bloom;
  struct ios_hash *next;
}ios_hash;





int int_to_int(int k);
unsigned long djb2(unsigned char *);
unsigned long sdbm(unsigned char *);
unsigned long hash_i(unsigned char *, unsigned int );
