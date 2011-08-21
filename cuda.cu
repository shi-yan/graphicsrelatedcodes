// Device code
#include <cuda.h>
#include <cutil_inline.h>

extern "C" 
void callCuda();

// Variables
float* h_A;
float* h_B;
float* h_C;
float* d_A;
float* d_B;
float* d_C;
bool noprompt = false;

// Functions
void CleanupResources(void);
void RandomInit(float*, int);
void ParseArguments(int, char**);

__global__ void VecAdd(const float* A, const float* B, float* C, int N)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < N)
        C[i] = A[i] + B[i];
}

 void callCuda()
{
  
    printf("Vector Addition\n");
    int N = 50000;
    size_t size = N * sizeof(float);
    //ParseArguments(argc, argv);

    // Allocate input vectors h_A and h_B in host memory
    h_A = (float*)malloc(size);
    if (h_A == 0) CleanupResources();
    h_B = (float*)malloc(size);
    if (h_B == 0) CleanupResources();
    h_C = (float*)malloc(size);
    if (h_C == 0) CleanupResources();
    
    // Initialize input vectors
    RandomInit(h_A, N);
    RandomInit(h_B, N);

    // Allocate vectors in device memory
    cutilSafeCall( cudaMalloc((void**)&d_A, size) );
    cutilSafeCall( cudaMalloc((void**)&d_B, size) );
    cutilSafeCall( cudaMalloc((void**)&d_C, size) );

    // Copy vectors from host memory to device memory
    cutilSafeCall( cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice) );

    // Invoke kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
	
    cutilCheckMsg("kernel launch failure");


    // Copy result from device memory to host memory
    // h_C contains the result in host memory
    cutilSafeCall( cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost) );
    
    // Verify result
    int i;
    for (i = 0; i < N; ++i) {
        float sum = h_A[i] + h_B[i];
        if (fabs(h_C[i] - sum) > 1e-5)
            break;
    }

    CleanupResources();

}

void CleanupResources(void)
{
    // Free device memory
    if (d_A)
        cudaFree(d_A);
    if (d_B)
        cudaFree(d_B);
    if (d_C)
        cudaFree(d_C);

    // Free host memory
    if (h_A)
        free(h_A);
    if (h_B)
        free(h_B);
    if (h_C)
        free(h_C);

}

// Allocates an array with random float entries.
void RandomInit(float* data, int n)
{
    for (int i = 0; i < n; ++i)
        data[i] = rand() / (float)RAND_MAX;
}

// Parse program arguments
void ParseArguments(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--noprompt") == 0 ||
            strcmp(argv[i], "-noprompt") == 0)
        {
            noprompt = true;
            break;
        }
    }
}
