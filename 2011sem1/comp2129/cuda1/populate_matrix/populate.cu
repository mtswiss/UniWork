#include <cuda.h>
#include <stdio.h>

#define N (32)
#define BLOCK (8)

__global__
void
matrixFill(float *matrix) {
  const int x = threadIdx.x + blockDim.x*blockIdx.x; 
  const int y = threadIdx.y + blockDim.y*blockIdx.y;
  const int i = N*y + x;
  matrix[i] = blockIdx.y;
}


int
main(void) {
  float h_matrix[N][N];
  float *d_matrix;
  unsigned int i, j;

  cudaMalloc(&d_matrix, N * N * sizeof(float));
  
  dim3 dimg(N/BLOCK, N/BLOCK);
  dim3 dimb(BLOCK, BLOCK);
  matrixFill<<<dimg, dimb>>>(d_matrix);

  cudaMemcpy(h_matrix, d_matrix, N * N * sizeof(float), cudaMemcpyDeviceToHost);
  
  for (i = 0; i != N; ++i) {
    for (j = 0; j != N; ++j)
      printf("%02.0f ", h_matrix[j][i]);
    printf("\n");
  }

  return 0;
}
