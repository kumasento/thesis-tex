template<>
void caffe_cpu_gemm<float>(const CBLAS_TRANSPOSE TransA,
    const CBLAS_TRANSPOSE TransB, const int M, const int N, const int K,
    const float alpha, const float* A, const float* B, const float beta,
    float* C) {
  int lda = (TransA == CblasNoTrans) ? K : M;
  int ldb = (TransB == CblasNoTrans) ? N : K;
  int TA  = (TransA == CblasNoTrans) ? 0 : 1;
  int TB  = (TransB == CblasNoTrans) ? 0 : 1;
#ifdef SDS
  if (M >= 128 && N >= 128 && K >= 128) 
    gemm_sds(TA, TB, M, N, K, alpha,
        (float *)A, lda, (float *)B, ldb, beta, (float *)C, N);
  else
#endif
  cblas_sgemm(CblasRowMajor, TransA, TransB, M, N, K, alpha, A, lda, B,
      ldb, beta, C, N);
}
