// optimized versions of matrix diagonal summing
#include "matvec.h"

// You can write several different versions of your optimized function
// in this file and call one of them in the last function.

int sumdiag_VER1(matrix_t mat, vector_t vec) {
  // OPTIMIZED CODE HERE
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  for(int i=0; i<vec.len; i++){                   // initialize vector of diagonal sums
    VSET(vec,i,0);                                // to all 0s
  }
  int row_num = mat.rows;
  int col_num = mat.cols;
  int j;
  for( int i=row_num-1; i>=0;i--){
  	for(j=0; j< col_num-2 ; j+=2){
  		int index = j-i + col_num- 1;
  		int el_ij = MGET(mat, i, j);                // get matrix element on diagonal
        int vec_d = VGET(vec, index);                   // retrieve current sum for diag
        VSET(vec, index, el_ij+vec_d);                  // add on back to the diagonal sum

        int index1 = j-i + col_num;
  		int el_ij1 = MGET(mat, i, j+1);                // get matrix element on diagonal
        int vec_d1 = VGET(vec, index1);                   // retrieve current sum for diag
        VSET(vec, index1, el_ij1+vec_d1);                  // add on back to the diagonal sum

  	}
  	//clean up
  	for(; j<col_num ; j++){
  		int index = j-i + col_num- 1;
  		int el_ij = MGET(mat, i, j);                // get matrix element on diagonal
        int vec_d = VGET(vec, index);                   // retrieve current sum for diag
        VSET(vec, index, el_ij+vec_d);                  // add on back to the diagonal sum
  	}
  }

  
  return 0;                                       // return success
}

int sumdiag_VER2(matrix_t mat, vector_t vec) {
  // OPTIMIZED CODE HERE
  return 0; 
}

int sumdiag_OPTM(matrix_t mat, vector_t vec) {
  // call your preferred version of the function
  
  return sumdiag_VER1(mat, vec);
}
