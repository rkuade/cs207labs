#include <stdio.h>
#include "bloom.h"
#include <math.h>
#include <stdlib.h>

int arr2[100];
int arr3[100]; 
 
void generator(int *barr);
void generator2(bloom_filter_t *B, int *barr, int *carr);

void generator(int *barr)
{
  int i;
  for (i=0;i<100;i++)
    {
      barr[i]=(int)rand()*1000000./RAND_MAX;
    }
}

void generator2(bloom_filter_t *B, int *barr, int *carr)
{
  int i;
  int counter = 0;
  int counter2 = 0;
  generator(barr);
  generator(carr);
  for(i=0;i<100;i++)
    {
      bloom_add(B,barr[i]);
    }
  for(i=0;i<1000;i++)
    {
      counter += get_bit(B,i);
    }
  for(i=0;i<100;i++)
    {
      counter2 += bloom_check(B,carr[i]);
    }
  printf("N_HASHES = %d\n",N_HASHES);
  printf("Number of bits in the table = %d\n",counter);
  printf("Number of false positives = %d\n",counter2);

}

int main(int argc, char** argv)
{
  key_t i;
  index_t j = 1;
  int counter=0;
  index_t arra[6] = {0,1,2,3,13,97};
  bloom_filter_t *B;
  bloom_init(B,100);
  for(i=0;i<6;i++)
    {
      printf("hash1 = %llu, hash2 = %llu\n",hash1(B,arra[i]),hash2(B,arra[i]));
    }
  bloom_destroy(B);
  bloom_init(B,1000); 
  for(i=1;i<71;i++)
    {
      bloom_add(B,i);
    }
  for(i=0;i<1000;i++)
    {
      counter += get_bit(B,i);
    }
  printf("Number of bits in the table = %d\n",counter);
  bloom_destroy(B);
  bloom_init(B,1000);
  generator2(B,arr2,arr3);
  bloom_destroy(B);
}

void set_bit(bloom_filter_t *B, index_t i)
{
  index_t j = 1;
  (B->table[i/64])=B->table[i/64]|(j<<(i%64));
}

index_t get_bit(bloom_filter_t *B, index_t i)
{
  index_t j = 1;
  return (B->table[i/64]&(j<<(i%64)))>>(i%64);
}

index_t hash1(bloom_filter_t *B, key_t k)
{
  return k%B->size;
}
index_t hash2(bloom_filter_t *B, key_t k)
{
  return (B->size-1-k)%B->size;
}

void bloom_init(bloom_filter_t *B, index_t size_in_bits)
{
  int i;
  B->table = (index_t *) malloc(((int)ceil(size_in_bits/64.))*sizeof(index_t));
  for(i=0;i<size_in_bits/64+1;i++)
    {
      B->table[i] =0;
    }
  B->size = size_in_bits;
  B->count = 0;
}
void bloom_destroy(bloom_filter_t *B)
{
  free(B->table);
}
int bloom_check(bloom_filter_t *B, key_t k)
{
  index_t j;
  index_t i =1;
  i &= get_bit(B,hash1(B,k));
  for(j = 0; j<N_HASHES-1;j++)
    {
      i &= get_bit(B,(j*hash1(B,k)+(index_t)(pow(3.,j))*hash2(B,k))%B->size);
    }
  return i;
}
void bloom_add(bloom_filter_t *B, key_t k)
{
  index_t i;
  set_bit(B,hash1(B,k));
  for(i=0;i<N_HASHES-1;i++)
    {
      set_bit(B,(i*hash1(B,k)+(index_t)(pow(3.,i))*hash2(B,k))%B->size);
  
    }
  B->count++;
}
