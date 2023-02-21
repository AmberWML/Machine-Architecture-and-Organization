#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void reverse_arr1(int *arr, long size){
  int *tmp = malloc(sizeof(int)*size);
  for(long i=0; i<size; i++){
    tmp[i] = arr[size-i-1];
  }
  for(long i=0; i<size; i++){
    arr[i] = tmp[i];
  }
  free(tmp);
}

void reverse_arr2(int *arr, long size){
  for(long i=0; i<size/2; i++){
    int tmp = arr[i];
    arr[i] = arr[size-i-1];
    arr[size-i-1] = tmp;
  }
}

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <minsize> <maxsize>\n",argv[0]);
    return 1;
  }
  int minsize = atoi(argv[1]);
  int maxsize = atoi(argv[2]);

  for(long s=minsize; s<=maxsize; s++){
    long size = 1 << s;

    int *arr1 = malloc(sizeof(int)*size);
    int *arr2 = malloc(sizeof(int)*size);
    for(long i=0; i<size; i++){
      arr1[i] = i;
      arr2[i] = i;
    }

    reverse_arr1(arr1,size);

    reverse_arr2(arr2,size);

    // Check answer
    for(long i=0; i<size; i++){
      assert(arr1[i] == size-i-1);
      assert(arr2[i] == size-i-1);
    }

    free(arr1);
    free(arr2);
  }

  return 0;
}
