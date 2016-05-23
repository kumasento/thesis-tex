void gemm_accel(float A[DIM*DIM], float B[DIM*DIM], float C[DIM*DIM], float ALPHA, float R[DIM*DIM]) {
  int i, j;
  float A_buf[DIM][DIM], B_buf[DIM][DIM], C_buf[DIM][DIM];
  for (i = 0; i < DIM; i ++)
    for (j = 0; j < DIM; j ++) {
    #pragma HLS pipeline II=1
      A_buf[i][j] = ALPHA * A[i*VEC+j];
      B_buf[i][j] = B[i*DIM+j];
      C_buf[i][j] = C[i*DIM+j];
    }
  gemm_accel_kernel(A_buf,B_buf,C_buf,ALPHA,R);
}
