void gemm_accel(float A[DIM*VEC], float B[DIM*VEC], float C[DIM*DIM], float ALPHA, float R[DIM*DIM]) {
  int i, j, k;
  float Ab[DIM][VEC], Bb[VEC][DIM], Cb[DIM][DIM];
  for (i = 0; i < DIM; i ++)
    for (j = 0; j < DIM; j ++) {
    #pragma HLS pipeline II=1
      if (j < VEC) Ab[i][j] = A[i*VEC+j];
      if (i < VEC) Bb[i][j] = B[i*DIM+j];
      Cb[i][j] = C[i*DIM+j];
    }
  gemm_accel_kernel(Ab,Bb,Cb,ALPHA,R);
}
