#include "hip/hip_runtime.h"

typedef float float32 __attribute__((ext_vector_type(32)));
typedef float float16 __attribute__((ext_vector_type(16))); 
typedef float mfma_float4 __attribute__((ext_vector_type(4)));
typedef __fp16 half4 __attribute__((ext_vector_type(4)));

// Device (Kernel) function, it must be void
__global__ void matrix_fp32(float* out, float* in, const int width) {
    int x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
    int y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;

    mfma_float4 in_C,out_D;
    float in_A, in_B;

	printf("%s: matrix_fp32 enter.\n", __FILE__);
}

__global__ void matrix_fp16(float* out, float* in, const int width) {
    int x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
    int y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;

    float16 in_C,out_D;
    half4 in_A, in_B;

	printf("%s: matrix_fp32 enter.\n", __FILE__);
}
