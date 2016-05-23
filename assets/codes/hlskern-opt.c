float tmp_LUT, res_LUT, tmp; 
#pragma HLS resource variable=tmp_LUT core=FAddSub_nodsp
#pragma HLS resource variable=res_LUT core=FMul_nodsp
FullLoop: for (k = 0; k < GEMM_FULL_UPPER; k ++) {
  res = A[i][k] * B[k][j];
  tmp = sum + res;
  sum = dsp;
}
TmpLUTLoop: for (k = GEMM_FULL_UPPER; k < GEMM_TMPLUT_UPPER; k ++) {
  res = A[i][k] * B[k][j];
  tmp_LUT = sum + res;
  sum = tmp_LUT;
}
ResLUTLoop: for (k = GEMM_TMPLUT_UPPER; k < GEMM_RESLUT_UPPER; k ++) {
  res_LUT = A[i][k] * B[k][j];
  tmp = sum + res_LUT;
  sum = tmp;
}
FullLUTLoop: for (k = GEMM_RESLUT_UPPER; k < DIM_K; k ++) {
  res_LUT = A[i][k] * B[k][j];
  tmp_LUT = sum + res_LUT;
  sum = tmp_LUT;
}
