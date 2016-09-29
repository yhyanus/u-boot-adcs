#!/bin/sh
export STAGING_DIR=./build
export BUILD_DIR=./build
export ARCH=arm
export CROSS_COMPILE=/work/jerry/openwrt/staging_dir/toolchain-arm_cortex-a9+neon_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-uclibcgnueabi- 
#mkdir mx6qpsabreauto_eimnor_config
#make O=$PWD/mx6qpsabreauto_eimnor_config menuconfig 
mkdir mx6adcs_eimnor_config
make O=$PWD/mx6adcs_eimnor_config menuconfig
 
