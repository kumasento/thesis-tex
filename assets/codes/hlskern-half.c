void gemm_accel(float A[DIM*VEC], float B[DIM*VEC], float C[DIM*DIM], float ALPHA, float R[DIM*DIM]) {
  int i, j;
#ifdef GEMM_HALF_DATA
#include "hls_half.h"
#define data_t half
#else 
#define data_t float
#endif
  data_t A_buf[DIM][VEC], B_buf[VEC][DIM], C_buf[DIM][DIM];
  for (i = 0; i < DIM; i ++)
    for (j = 0; j < DIM; j ++) {
    #pragma HLS pipeline II=1
      if (j < VEC) A_buf[i][j] = ALPHA * A[i*VEC+j];
      if (i < VEC) B_buf[i][j] = B[i*DIM+j];
      C_buf[i][j] = C[i*DIM+j];
    }
  gemm_accel_kernel(A_buf,B_buf,C_buf,ALPHA,R);
}
