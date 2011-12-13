#include <assert.h>
#include <stdio.h>
#include <stdio.h>
#include <cuda.h>

__global__ void
matrix_multipy(float *M, float *I, float *R, int w){
	int x = threadIdx.x; 
	int y = threadIdx.y;
	float Rvalue = 0;
	for(int i = 0; i< w;i++){
		Rvalue += M[y*w + i] * I[i*w + x];
	}
	R[y*w + x] = Rvalue;
}

int
main(void) {
	int w, power;
	
	if(scanf("%d\n", &w) != 1 || w < 1){
		printf("error\n");
		return -1;
	}

	if(scanf("%d\n", &power) != 1 || power < 0){
		printf("error\n");
		return -1;
	}
	

	float *M = (float *)malloc(w * w * sizeof(float));
	float *I = (float *)malloc(w * w * sizeof(float));
	float *R = (float *)malloc(w * w * sizeof(float));

	float *dM, *dI, *dR;
	cudaMalloc(&dM, w*w*sizeof(float));
	cudaMalloc(&dI, w*w*sizeof(float));
	cudaMalloc(&dR, w*w*sizeof(float));

	
	if(power==0){
		int j, k =0;
		for(j = 0; j<w;j++){
			for(k = 0; k<w;k++){
				if(j==k)
					printf("%.3f ",1.0);
				else
					printf("%.3f ",0.0);
			}

			printf("\n");
		}

		free(M);
		free(I);
		free(R);
		return -1;
	}
			
	
	for(int i = 0; i < w*w; i++){
		float x;
		if(scanf("%f",&x) == 1){
			M[i] = x;
			I[i] = x;
		}
		else {
			printf("error\n");
			return -1;
		}
	}
	
	cudaMemcpy(dM, M, w*w*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dI, I, w*w*sizeof(float), cudaMemcpyHostToDevice);

	dim3 dimBlock (w,w);
	dim3 dimGrid(1);

	for(int i = 1; i<power; i++){
		matrix_multipy<<<dimGrid,dimBlock>>>(dM,dI,dR,w);
		cudaThreadSynchronize();
		cudaMemcpy(dI, dR, w*w*sizeof(float), cudaMemcpyDeviceToHost);
	}

	cudaMemcpy(R,dR,w*w*sizeof(float),cudaMemcpyDeviceToHost);
	
	for (int i = 0; i < w * w; i++) {
		if (power == 1)
			printf("%.3f ", M[i]);
		else
			printf("%.3f ", R[i]);
		if ((i + 1) % w == 0)
			printf("\n");
	}
	
	cudaFree(dR);
	cudaFree(dI);
	cudaFree(dR);
	free(M);
	free(I);
	free(R);
	
  return 0;
}

