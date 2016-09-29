#!/bin/sh
export STAGING_DIR=./build
export BUILD_DIR=./build
export ARCH=arm
export CROSS_COMPILE=/work/jerry/openwrt/staging_dir/toolchain-arm_cortex-a9+neon_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-uclibcgnueabi- 
#make O=$PWD/mx6adcs_eimnor_config clean
make O=$PWD/mx6adcs_eimnor_config mx6adcs_eimnor_defconfig 
make O=$PWD/mx6adcs_eimnor_config 2>&1 | tee mk.log
 
