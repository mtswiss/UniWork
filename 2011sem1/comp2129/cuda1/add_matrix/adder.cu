#include <cuda.h>
#include <stdio.h>

#define N (32)
#define BLOCK (8)

__global__ void
matrix_add(const float *a, const float *b, float *c) {
  const int x = threadIdx.x + blockIdx.x*blockDim.x;
  const int y = threadIdx.y + blockIdx.y*blockDim.y;
  const int i = y*N + x;
  c[i] = a[i] + b[i]; 
}

void
print_matrix(const float *m, const int w, const int h) {
  int x, y;
  for (y = 0; y != h; ++y) {
    for (x = 0; x != w; ++x)
      printf("%02.0f ", m[y*w + x]);
    printf("\n");
  }
}

void
create_matrix_d(float **m, int w, int h) {
  cudaMalloc(m, w * h * sizeof(float));
  cudaMemset(*m, 0, w * h * sizeof(float));
}

void
create_matrix_h(float **m, int w, int h) {
  *m = (float *) malloc(w * h * sizeof(float));
  memset(*m, 0, w * h * sizeof(float));
}


int
main(void) {
  float *h_a, *h_b, *h_c;
  float *d_a, *d_b, *d_c;
  int x, y;
  
  create_matrix_h(&h_a, N, N);
  create_matrix_h(&h_b, N, N);
  create_matrix_h(&h_c, N, N);

  create_matrix_d(&d_a, N, N);
  create_matrix_d(&d_b, N, N);
  create_matrix_d(&d_c, N, N);
  
  for (y = 0; y != N; ++y) {
    for (x = 0; x != N; ++x) {
      h_a[y*N + x] = y*N + x;
      h_b[y*N + x] = 1;
    }
  }
  
  cudaMemcpy(d_a, h_a, N*N*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, N*N*sizeof(float), cudaMemcpyHostToDevice);
  
  dim3 dimb(BLOCK, BLOCK);
  dim3 dimg(N/BLOCK, N/BLOCK);

  matrix_add<<<dimg, dimb>>>(d_a, d_b, d_c);

  cudaMemcpy(h_c, d_c, N*N*sizeof(float), cudaMemcpyDeviceToHost);

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

  printf("first matrix\n");
  print_matrix(h_a, N, N);
  printf("second matrix\n");
  print_matrix(h_b, N, N);
  printf("resultant matrix\n");
  print_matrix(h_c, N, N);

  return 0;
}


