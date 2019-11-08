#!/bin/sh

LIBDIR=lib
OUTDIR=out

rm -rf $OUTDIR; mkdir -p $OUTDIR

#################
# build libs
#################
LIBS="libgfx900 libgfx906 libgfx908"

for o in $LIBS
do
echo "generating ${o}..."
 "/opt/rocm/hcc/bin/clang-10" -cc1 -D__KALMAR_HC__=1 -D__HCC_HC__=1 -famp-is-device -fno-builtin -fno-common -O2 -triple amdgcn--amdhsa-hcc -aux-triple x86_64-unknown-linux-gnu -S -disable-free -disable-llvm-verifier -main-file-name mfma_inline_asm.cpp -mrelocation-model pic -pic-level 1 -mthread-model posix -mframe-pointer=all -fmath-errno -no-integrated-as -mconstructor-aliases -fuse-init-array -coverage-notes-file /root/mfma_hip_inline_asm/mfma_inline_asm.gcno -resource-dir /opt/rocm/hcc/lib/clang/10.0.0 -I/opt/rocm/hcc/bin/../include -I/opt/rocm/hcc/bin/../hcc/include -isystem /opt/rocm/hcc/include -isystem /opt/rocm/hip/include/hip/hcc_detail/cuda -isystem /opt/rocm/hsa/include -isystem /opt/rocm/hip/include -D __HIPCC__ -D HIP_VERSION_MAJOR=2 -D HIP_VERSION_MINOR=8 -D HIP_VERSION_PATCH=19361 -D __HIP_ARCH_GFX906__=1 -D __HIP_ARCH_GFX908__=1 -internal-isystem /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0 -internal-isystem /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/x86_64-linux-gnu/c++/5.4.0 -internal-isystem /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/x86_64-linux-gnu/c++/5.4.0 -internal-isystem /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/backward -internal-isystem /usr/local/include -internal-isystem /opt/rocm/hcc/lib/clang/10.0.0/include -internal-externc-isystem /usr/include/x86_64-linux-gnu -internal-externc-isystem /include -internal-externc-isystem /usr/include -Wno-deprecated-register -std=c++amp -fdeprecated-macro -fno-dwarf-directory-asm -fdebug-compilation-dir /root/mfma_hip_inline_asm -ferror-limit 19 -fmessage-length 0 -fobjc-runtime=gcc -fcxx-exceptions -fexceptions -fdiagnostics-show-option -fcolor-diagnostics -famp -fhsa-ext -fgpu-rdc -emit-llvm-bc -o ${LIBDIR}/${o}.bc -x hc-kernel ${LIBDIR}/${o}.cpp
done

make clean
rm -rf dump-*
HCC_EXTRA_LIBRARIES_GFX900=$PWD/$LIBDIR/libgfx900.bc HCC_EXTRA_LIBRARIES_GFX906=$PWD/$LIBDIR/libgfx906.bc HCC_EXTRA_LIBRARIES_GFX908=$PWD/$LIBDIR/libgfx908.bc KMDUMPISA=1 make 

