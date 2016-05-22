void gemm_accel_kernel(float A[BLK_M][BLK_K], float B[BLK_K][BLK_N], float C[BLK_M][BLK_N], float ALPHA, float R[BLK_M*BLK_N]) {
#pragma HLS inline
#pragma HLS array_partition variable=A block factor=16 dim=2
#pragma HLS array_partition variable=B block factor=16 dim=1
  int i, j, k;
  float sum;
  Row: for (i = 0; i < BLK_M; i ++) {
    Col: for (j = 0; j < BLK_N; j ++) {
    #pragma HLS pipeline II=1
      sum = C[i][j];
      Prod: for (k = 0; k < BLK_K; k ++)
        sum += ALPHA * A[i][k] * B[k][j];
      R[i*DIM+j] = sum;
    }
  }
}
