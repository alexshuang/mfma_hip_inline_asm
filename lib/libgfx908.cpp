#include "hip/hip_runtime.h"

typedef float float32 __attribute__((ext_vector_type(32)));
typedef float float16 __attribute__((ext_vector_type(16))); 
typedef float mfma_float4 __attribute__((ext_vector_type(4)));
typedef __fp16 half4 __attribute__((ext_vector_type(4)));

extern "C" __device__ float32   __llvm_amdgcn_mfma_f32_32x32x1f32(float, float, float32, int, int, int) __asm("llvm.amdgcn.mfma.f32.32x32x1f32");
extern "C" __device__ float16 __llvm_amdgcn_mfma_f32_16x16x1f32(float, float, float16, int, int, int) __asm("llvm.amdgcn.mfma.f32.16x16x1f32");
extern "C" __device__ float4  __llvm_amdgcn_mfma_f32_4x4x1f32(float, float, float4, int, int, int) __asm("llvm.amdgcn.mfma.f32.4x4x1f32");
extern "C" __device__ float16 __llvm_amdgcn_mfma_f32_32x32x2f32(float, float, float16, int, int, int) __asm("llvm.amdgcn.mfma.f32.32x32x2f32");
extern "C" __device__ mfma_float4  __llvm_amdgcn_mfma_f32_16x16x4f32(float, float, mfma_float4, int, int, int) __asm("llvm.amdgcn.mfma.f32.16x16x4f32");

extern "C" __device__ float32   __llvm_amdgcn_mfma_f32_32x32x4f16(half4, half4, float32, int, int, int) __asm("llvm.amdgcn.mfma.f32.32x32x4f16");
extern "C" __device__ float16 __llvm_amdgcn_mfma_f32_16x16x4f16(half4, half4, float16, int, int, int) __asm("llvm.amdgcn.mfma.f32.16x16x4f16");
extern "C" __device__ mfma_float4  __llvm_amdgcn_mfma_f32_4x4x4f16(half4, half4, mfma_float4, int, int, int) __asm("llvm.amdgcn.mfma.f32.4x4x4f16");
extern "C" __device__ float16 __llvm_amdgcn_mfma_f32_32x32x8f16(half4, half4, float16, int, int, int) __asm("llvm.amdgcn.mfma.f32.32x32x8f16");
extern "C" __device__ mfma_float4  __llvm_amdgcn_mfma_f32_16x16x16f16(half4, half4, mfma_float4, int, int, int) __asm("llvm.amdgcn.mfma.f32.16x16x16f16");

// Device (Kernel) function, it must be void
__global__ void matrix_fp32(float* out, float* in, const int width) {
    int x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
    int y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;

    mfma_float4 in_C,out_D;
    float in_A, in_B;

    out_D = __llvm_amdgcn_mfma_f32_16x16x4f32(in_A, in_B,in_C,0,0,0 );
    out[x*width+y] = *(float*)&out_D;
}

__global__ void matrix_fp16(float* out, float* in, const int width) {
    int x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
    int y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;

    float16 in_C,out_D;
    half4 in_A, in_B;

    out_D = __llvm_amdgcn_mfma_f32_32x32x8f16(in_A, in_B,in_C,0,0,0 );
    out[x*width+y] = *(float*)&out_D;
}
