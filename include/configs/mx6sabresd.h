/*
 * Copyright (C) 2012-2015 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Freescale i.MX6Q SabreSD board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MX6QSABRESD_CONFIG_H
#define __MX6QSABRESD_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>

#ifdef CONFIG_SPL
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#include "imx6_spl.h"
#endif

#define CONFIG_MACH_TYPE	3980
#define CONFIG_MXC_UART_BASE	UART1_BASE
#define CONFIG_CONSOLE_DEV		"ttymxc0"
#define CONFIG_MMCROOT			"/dev/mmcblk2p2"  /* SDHC3 */
#if defined(CONFIG_MX6QP)
#define CONFIG_DEFAULT_FDT_FILE	"imx6qp-sabresd.dtb"

#ifdef CONFIG_ADCS
#define PHYS_SDRAM_SIZE		(2u * 1024 * 1024 * 1024)
#define CONFIG_SYS_USE_NAND
#define CONFIG_SYS_USE_SPINOR
#define CONFIG_CMD_SATA
#else
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#endif
#elif defined(CONFIG_MX6Q)
#define CONFIG_DEFAULT_FDT_FILE	"imx6q-sabresd.dtb"
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6DL)
#define CONFIG_DEFAULT_FDT_FILE	"imx6dl-sabresd.dtb"
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6SOLO)
#define CONFIG_DEFAULT_FDT_FILE	"imx6dl-sabresd.dtb"
#define PHYS_SDRAM_SIZE		(512u * 1024 * 1024)
#endif

#include "mx6sabre_common.h"
#ifdef CONFIG_ADCS
#define CONFIG_CMD_GPIO 
#undef CONFIG_LDO_BYPASS_CHECK
#define CONFIG_MTD_UBI_BLOCK
#define CONFIG_MTD_DEVICE 
#define CONFIG_FLASH_CFI_MTD 
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_UBIFS
#define CONFIG_CMD_UBI 
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_CMD_EXT4
#define CONFIG_FS_EXT4
#define CONFIG_EXT4_WRITE
#define MTDIDS_DEFAULT "nand0=gpmi-nand"    /*,nor0=nor0" */
#define MTDPARTS_DEFAULT "mtdparts=gpmi-nand:64m(boot),16m(kernel),16m(dtb),-(rootfs)"
#undef CONFIG_MFG_ENV_SETTINGS
#define CONFIG_MFG_ENV_SETTINGS ""
#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS \
	"ethaddr=22:11:11:22:22:22\0" \
	"ipaddr=192.168.2.13\0" \
	"serverip=192.168.2.200\0" \
	"fdt_addr=0x18000000\0" \
	"fdt_high=0xffffffff\0"	  \
	"bootargs=console=" CONFIG_CONSOLE_DEV ",115200 ubi.mtd=4 "  \
		"root=ubi:rootfs rootfstype=ubifs "		     \
		"mtdparts=gpmi-nand:64m(boot),16m(kernel),16m(dtb),-(rootfs) video=mxcfb0:dev=lcd,XVGA,if=RGB24\0"\
	"bootcmd=bootz ${loadaddr} - ${fdt_addr}\0" \
	"ftpboot=tftp ${loadaddr} zImage;tftp ${fdt_addr} zImage.dtb;bootz ${loadaddr} - ${fdt_addr}\0" \
	"kernel_size=0x140000\0" \
	"fdt_size=0x10000\0" \
	"norboot=cp.l 8100000 ${loadaddr} ${kernel_size};cp.b 0x8f00000 ${fdt_addr} ${fdt_size};bootz ${loadaddr} - ${fdt_addr}\0" \
	"inst_kernel=tftp 12000000 zImage;cp.l 12000000 8100000 ${kernel_size};tftp 12000000 zImage.dtb;cp.b 12000000 0x8f00000 ${fdt_size};\0" \
	"inst_root=mtdparts default;ubi part rootfs;tftp 10000000 rootfs.img;ubi createvol rootfs; ubi write 10000000 rootfs ${filesize};\0" \
/*
setenv mtdids "nor0=nor0,nand0=gpmi-nand"
setenv mtdparts "mtdparts=nor0:1024k(ARMboot)ro,-(kernel);gpmi-nand:16m(boot),64m(kernel),16m(dtb),-(rootfs)"

setenv bootargs "console=ttymxc0,115200 rdinit=/linuxrc"
setenv bootargs "console=ttymxc0,115200 ubi.mtd=4 root=ubi:rootfs rootfstype=ubifs mtdparts=gpmi-nand:64m(boot),16m(kernel),16m(dtb),-(rootfs) video=mxcfb0:dev=lcd,XVGA,if=RGB24"
tftp 12000000 zImage;tftp 18000000 zImage.dtb;bootz 12000000 - 18000000

// write ubi fs to nand flash.
mtdparts default;ubi part rootfs;tftp 10000000 192.168.2.200:rootfs.img;ubi createvol rootfs; ubi write 10000000 rootfs 0x23ee000

*/
#else
#define CONFIG_SYS_FSL_USDHC_NUM	3
#define CONFIG_SYS_MMC_ENV_DEV		1	/* SDHC3 */
#define CONFIG_SYS_MMC_ENV_PART                0       /* user partition */
#endif

#ifdef CONFIG_SYS_USE_SPINOR
#define CONFIG_SF_DEFAULT_CS   0
#define CONFIG_MXC_SPI

#endif

/*
 * imx6 q/dl/solo pcie would be failed to work properly in kernel, if
 * the pcie module is iniialized/enumerated both in uboot and linux
 * kernel.
 * rootcause:imx6 q/dl/solo pcie don't have the reset mechanism.
 * it is only be RESET by the POR. So, the pcie module only be
 * initialized/enumerated once in one POR.
 * Set to use pcie in kernel defaultly, mask the pcie config here.
 * Remove the mask freely, if the uboot pcie functions, rather than
 * the kernel's, are required.
 */
/* #define CONFIG_CMD_PCI */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(3, 19)
#endif

#ifndef CONFIG_ADCS
/* PMIC */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR	0x08
#endif
/* USB Configs */
#define CONFIG_CMD_USB
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
/*
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
*/
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2 /* Enabled USB controller number */
#endif

#ifdef CONFIG_SYS_USE_EIMNOR


#undef CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_FLASH_BASE           WEIM_ARB_BASE_ADDR
#define CONFIG_SYS_FLASH_SECT_SIZE      (128 * 1024)
#define CONFIG_SYS_MAX_FLASH_BANKS 1    /* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT 256   /* max number of sectors on one chip */
#define CONFIG_SYS_FLASH_CFI            /* Flash memory is CFI compliant */
#define CONFIG_FLASH_CFI_DRIVER         /* Use drivers/cfi_flash.c */
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE /* Use buffered writes*/
#define CONFIG_SYS_FLASH_EMPTY_INFO
#endif


/* I2C Configs */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED		100000

/* NAND flash command */
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NAND_TRIMFFS

/* NAND stuff */
#define CONFIG_NAND_MXS
#define CONFIG_SYS_MAX_NAND_DEVICE     1
#define CONFIG_SYS_NAND_BASE           0x40000000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_ONFI_DETECTION

/* DMA stuff, needed for GPMI/MXS NAND support */
#define CONFIG_APBH_DMA
#define CONFIG_APBH_DMA_BURST
#define CONFIG_APBH_DMA_BURST8

/*#define CONFIG_SPLASH_SCREEN*/
/*#define CONFIG_MXC_EPDC*/

/*
 * SPLASH SCREEN Configs
 */
#if defined(CONFIG_SPLASH_SCREEN) && defined(CONFIG_MXC_EPDC)
	/*
	 * Framebuffer and LCD
	 */
	#define CONFIG_CMD_BMP
	#define CONFIG_LCD
	#define CONFIG_SYS_CONSOLE_IS_IN_ENV
	#undef LCD_TEST_PATTERN
	/* #define CONFIG_SPLASH_IS_IN_MMC			1 */
	#define LCD_BPP					LCD_MONOCHROME
	/* #define CONFIG_SPLASH_SCREEN_ALIGN		1 */

	#define CONFIG_WAVEFORM_BUF_SIZE		0x200000
#endif /* CONFIG_SPLASH_SCREEN && CONFIG_MXC_EPDC */

#endif                         /* __MX6QSABRESD_CONFIG_H */




 
 
 