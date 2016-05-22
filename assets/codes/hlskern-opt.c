float tmp_LUT, tmp_DSP, tmp; 
#pragma HLS resource variable=tmp_LUT core=FAddSub_nodsp
#pragma HLS resource variable=tmp_DSP core=FAddSub_fulldsp
for (k = 0; k < LUT_RANGE; k ++) {
  res = ALPHA * A[i][k] * B[k][j];
  tmp_LUT = res + sum;
  sum = tmp_LUT;
}
for (k = LUT_RANGE; k < DSP_RANGE; k ++) {
  res = ALPHA * A[i][k] * B[k][j];
  tmp_DSP = res + sum;
  sum = tmp_DSP;
}
for (k = DSP_RANGE; k < DIM; k ++) {
  res = ALPHA * A[i][k] * B[k][j];
  tmp_DSP = res + sum;
  sum = tmp_DSP;
}
