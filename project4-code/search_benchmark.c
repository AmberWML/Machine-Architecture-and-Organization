

#include <stdlib.h>
#include "search.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <error.h>

int main(int argc, char *argv[]){
  int run_linear_array = 0;
  int run_linear_list  = 0;
  int run_binary_array = 0;
  int run_binary_tree = 0;
  printf("LENGTH SEARCHES");
  // char algs_string[12];
  // char str1[10];
  // char str2[10];
  // char str3[10];
  // char str4[10];

  
  // strcpy(str1,'a');
  // strcpy(str2,'b');
  // strcpy(str3,'l');
  // strcpy(str4,'t');
  if(argc == 5){
    // strcpy(algs_string,argv[4]);
  		for(int i=0; i<sizeof(argv[4]);i++){
  			if(argv[4][i]=='a'){
  				run_linear_array = 1;
		  		printf("       array");
		  	}else if(argv[4][i]=='b'){
		  		run_binary_array = 1;
		  		printf("      binary");
		  	}else if(argv[4][i] == 'l'){
		  		run_linear_list = 1;
		  		printf("        list");
		  	}else if(argv[4][i] == 't'){
		  		run_binary_tree = 1;
		  		printf("        tree");}
  		}
      printf("\n");

  }
  else if(argc == 4){
      
      printf("       array");
      printf("        list");
      printf("      binary");
      printf("        tree");
      run_linear_list = 1;
  	  run_binary_array = 1;
  	  run_binary_tree = 1;
  	  run_linear_array = 1;
      printf("\n");
    }
  // int *array = make_evens_array();
  // list_t *list = make_evens_list();
  // bst_t *tree = make_evens_tree();
  //./search_benchmark <minpow> <maxpow> <repeats> [which]
  int minpower = atoi(argv[1]);
  int maxpower = atoi(argv[2]);
  int repeats = atoi(argv[3]);
  // int cur_search_size = cur_search_size * 2;
  int len = 1;
  
  for(int i=minpower; i<=maxpower; i++){
  	
  	len = 1<<i;
  	printf("%5d", len);
  	printf("%10d", len*2*repeats);
  	if(run_linear_list){
      int j=0;
      int k=0;
  		// run loops to time linear search in a list
  		double time = 0;
  		list_t* list = make_evens_list(len);
  		clock_t begin, end;
  		begin = clock();
  		while(j<repeats){
  			while(k<len*2){
  			 linkedlist_search(list, len, k);
  			 k++;
  			}
  		  j++;
  		}
  		end = clock();
  		time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  		printf("  ");
  		printf("%9.4e", time);
  		list_free(list);
  	}
  	if(run_linear_array){
      int j=0;
      int k=0;
  		// run loops to time linear search in an array
  		double time = 0;
  		int* arr = make_evens_array(len);
  		clock_t begin, end;
  		begin = clock();// current cpu moment
  		
  		while(j<repeats){
  			while(k<len*2){
  			 linear_array_search(arr, len, k);
  			 k++;
  			}
  		  j++;
  		}
 
  		end = clock(); // later moment

  		time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  		printf("  ");
  		printf("%9.4e", time);
  		free(arr);
  	}
  	
  	
  	if(run_binary_tree){
      int j=0;
      int k=0;
  		// run loops to time linear search in a list
  		double time = 0;
  		bst_t* tree = make_evens_tree(len);
  		clock_t begin, end;
  		begin = clock();
  		while(j<repeats){
  			while(k<len*2){
  			 binary_tree_search(tree, len, k);
  			 k++;
  			}
  		  j++;
  		}
  		end = clock();
  		time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  		printf("  ");
  		printf("%9.4e", time);
  		bst_free(tree);
  	}
  	if(run_binary_array){
      int j=0;
      int k=0;
  		// run loops to time linear search in an array
  		double time = 0;
  		int* barr = make_evens_array(len);
  		clock_t begin, end;
  		begin = clock();
  		while(j<repeats){
  			while(k<len*2){
  			 binary_array_search(barr, len, k);
  			 k++;
  			}
  		  j++;
  		}
  		end = clock();
  		time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  		printf("  ");
  		printf("%9.4e", time);
  		free(barr);
  	}
  	printf("\n");
  }
 

  return 0;

}
