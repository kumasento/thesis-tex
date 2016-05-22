void gemm_accel(float A[BLK_M*BLK_K], float B[BLK_N*BLK_K], float C[BLK_M*BLK_N], float ALPHA, float R[BLK_M*BLK_N]) {
  int i, j, k;
  float A_buf[BLK_M][BLK_K], B_buf[BLK_K][BLK_N], C_buf[BLK_M][BLK_N];
  A_RowCopy: for (i = 0; i < BLK_M; i ++) 
    A_ColCopy: for (j = 0; j < BLK_K; j ++)
    #pragma HLS pipeline II=1              
      A_buf[i][j] = ALPHA * A[i*BLK_K+j];  
  B_RowCopy: for (i = 0; i < BLK_K; i ++)  
    B_ColCopy: for (j = 0; j < BLK_N; j ++)
    #pragma HLS pipeline II=1              
      B_buf[i][j] = B[i*BLK_N+j];          
  C_RowCopy: for (i = 0; i < BLK_M; i ++)  
    C_ColCopy: for (j = 0; j < BLK_N; j ++)
    #pragma HLS pipeline II=1              
      C_buf[i][j] = C[i*BLK_N+j];
  gemm_accel_kernel(A_buf,B_buf,C_buf,ALPHA,R);
}
