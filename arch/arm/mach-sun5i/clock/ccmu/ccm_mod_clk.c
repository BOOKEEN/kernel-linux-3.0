/*
*********************************************************************************************************
*                                                    LINUX-KERNEL
*                                        ReuuiMlla Linux Platform Develop Kits
*                                                   Kernel Module
*
*                                    (c) Copyright 2006-2011, kevin.z China
*                                             All Rights Reserved
*
* File    : ccu_mod_clk.c
* By      : kevin.z
* Version : v1.0
* Date    : 2011-5-14 11:05
* Descript: module clock management for Reuuimllas chips.
* Update  : date                auther      ver     notes
*********************************************************************************************************
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <mach/clock.h>
#include <mach/dram.h>
#include "ccm_i.h"

#define make_mod_clk_inf(clk_id, clk_name)  {.id = clk_id, .name = clk_name, }

static __aw_ccu_clk_t aw_ccu_mod_clk[] =
{
    make_mod_clk_inf(AW_MOD_CLK_NONE        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_NFC         , "nfc"             ),
    make_mod_clk_inf(AW_MOD_CLK_MSC         , "msc"             ),
    make_mod_clk_inf(AW_MOD_CLK_SDC0        , "sdc0"            ),
    make_mod_clk_inf(AW_MOD_CLK_SDC1        , "sdc1"            ),
    make_mod_clk_inf(AW_MOD_CLK_SDC2        , "sdc2"            ),
    make_mod_clk_inf(AW_MOD_CLK_SDC3        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_TS          , "ts"              ),
    make_mod_clk_inf(AW_MOD_CLK_SS          , "ss"              ),
    make_mod_clk_inf(AW_MOD_CLK_SPI0        , "spi0"            ),
    make_mod_clk_inf(AW_MOD_CLK_SPI1        , "spi1"            ),
    make_mod_clk_inf(AW_MOD_CLK_SPI2        , "spi2"            ),
    make_mod_clk_inf(AW_MOD_CLK_PATA        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_IR0         , "ir0"             ),
    make_mod_clk_inf(AW_MOD_CLK_IR1         , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_I2S         , "i2s"             ),
    make_mod_clk_inf(AW_MOD_CLK_AC97        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SPDIF       , "spdif"           ),
    make_mod_clk_inf(AW_MOD_CLK_KEYPAD      , "key_pad"         ),
    make_mod_clk_inf(AW_MOD_CLK_SATA        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_USBPHY      , "usb_phy"     ),
    make_mod_clk_inf(AW_MOD_CLK_USBPHY0     , "usb_phy0"        ),
    make_mod_clk_inf(AW_MOD_CLK_USBPHY1     , "usb_phy1"        ),
    make_mod_clk_inf(AW_MOD_CLK_USBPHY2     , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_USBOHCI0    , "usb_ohci0"       ),
    make_mod_clk_inf(AW_MOD_CLK_USBOHCI1    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_GPS         , "com"             ),
    make_mod_clk_inf(AW_MOD_CLK_SPI3        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_DEBE0       , "de_image0"       ),
    make_mod_clk_inf(AW_MOD_CLK_DEBE1       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_DEFE0       , "de_scale0"       ),
    make_mod_clk_inf(AW_MOD_CLK_DEFE1       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_DEMIX       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_LCD0CH0     , "lcd0_ch0"        ),
    make_mod_clk_inf(AW_MOD_CLK_LCD1CH0     , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_CSIISP      , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_TVD         , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_LCD0CH1_S1  , "lcd0_ch1_s1"     ),
    make_mod_clk_inf(AW_MOD_CLK_LCD0CH1_S2  , "lcd0_ch1_s2"     ),
    make_mod_clk_inf(AW_MOD_CLK_LCD1CH1_S1  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_LCD1CH1_S2  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_CSI0        , "csi0"            ),
    make_mod_clk_inf(AW_MOD_CLK_CSI1        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_VE          , "ve"              ),
    make_mod_clk_inf(AW_MOD_CLK_ADDA        , "audio_codec" ),
    make_mod_clk_inf(AW_MOD_CLK_AVS         , "avs"             ),
    make_mod_clk_inf(AW_MOD_CLK_ACE         , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_LVDS        , "lvds"            ),
    make_mod_clk_inf(AW_MOD_CLK_HDMI        , "hdmi"            ),
    make_mod_clk_inf(AW_MOD_CLK_MALI        , "mali"            ),
    make_mod_clk_inf(AW_MOD_CLK_TWI0        , "twi0"            ),
    make_mod_clk_inf(AW_MOD_CLK_TWI1        , "twi1"            ),
    make_mod_clk_inf(AW_MOD_CLK_TWI2        , "twi2"            ),
    make_mod_clk_inf(AW_MOD_CLK_CAN         , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SCR         , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_PS20        , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_PS21        , "ps1"             ),
    make_mod_clk_inf(AW_MOD_CLK_UART0       , "uart0"           ),
    make_mod_clk_inf(AW_MOD_CLK_UART1       , "uart1"           ),
    make_mod_clk_inf(AW_MOD_CLK_UART2       , "uart2"           ),
    make_mod_clk_inf(AW_MOD_CLK_UART3       , "uart3"           ),
    make_mod_clk_inf(AW_MOD_CLK_UART4       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_UART5       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_UART6       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_UART7       , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AXI_DRAM    , "axi_dram"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_USB0    , "ahb_usb0"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_EHCI0   , "ahb_ehci0"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_OHCI0   , "ahb_ohci0"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SS      , "ahb_ss"          ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_DMA     , "ahb_dma"         ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_BIST    , "ahb_bist"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SDMMC0  , "ahb_sdc0"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SDMMC1  , "ahb_sdc1"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SDMMC2  , "ahb_sdc2"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SDMMC3  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_MS      , "ahb_msc"         ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_NAND    , "ahb_nfc"         ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SDRAM   , "ahb_sdramc"      ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_ACE     , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_EMAC    , "ahb_emac"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_TS      , "ahb_ts"          ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SPI0    , "ahb_spi0"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SPI1    , "ahb_spi1"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SPI2    , "ahb_spi2"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SPI3    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_PATA    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_SATA    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_GPS     , "ahb_com"         ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_VE      , "ahb_ve"          ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_TVD     , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_TVE0    , "ahb_tve0"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_TVE1    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_LCD0    , "ahb_lcd0"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_LCD1    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_CSI0    , "ahb_csi0"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_CSI1    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_HDMI    , "ahb_hdmi"        ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_DEBE0   , "ahb_de_image0"   ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_DEBE1   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_DEFE0   , "ahb_de_scale0"   ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_DEFE1   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_MP      , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_MALI    , "ahb_mali"        ),
    make_mod_clk_inf(AW_MOD_CLK_APB_ADDA    , "apb_audio_codec" ),
    make_mod_clk_inf(AW_MOD_CLK_APB_SPDIF   , "apb_spdif"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_AC97    , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_I2S     , "apb_i2s"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_PIO     , "apb_pio"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_IR0     , "apb_ir0"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_IR1     , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_KEYPAD  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_TWI0    , "apb_twi0"        ),
    make_mod_clk_inf(AW_MOD_CLK_APB_TWI1    , "apb_twi1"        ),
    make_mod_clk_inf(AW_MOD_CLK_APB_TWI2    , "apb_twi2"        ),
    make_mod_clk_inf(AW_MOD_CLK_APB_CAN     , "apb_can"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_SCR     , "apb_scr"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_PS20    , "apb_ps0"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_PS21    , "apb_ps1"         ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART0   , "apb_uart0"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART1   , "apb_uart1"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART2   , "apb_uart2"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART3   , "apb_uart3"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART4   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART5   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART6   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_APB_UART7   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_VE    , "sdram_ve"        ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_CSI0  , "sdram_csi0"      ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_CSI1  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_TS    , "sdram_ts"        ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_TVD   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_TVE0  , "sdram_tve0"      ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_TVE1  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_DEFE0 , "sdram_de_scale0" ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_DEFE1 , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_DEBE0 , "sdram_de_image0" ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_DEBE1 , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_DEMP  , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_ACE   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_EHCI1   , "mclk_none"       ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_OHCI1   , "mclk_none"       ),

    make_mod_clk_inf(AW_MOD_CLK_IEP         , "iep"             ),
    make_mod_clk_inf(AW_MOD_CLK_AHB_IEP     , "ahb_iep"         ),
    make_mod_clk_inf(AW_MOD_CLK_SDRAM_IEP   , "sdram_iep"       ),

};


static __aw_ccu_sys_clk_e mod_clk_get_parent(__aw_ccu_mod_clk_e id);
static __aw_ccu_clk_onff_e mod_clk_get_status(__aw_ccu_mod_clk_e id);
static __s64 mod_clk_get_rate(__aw_ccu_mod_clk_e id);
static __aw_ccu_clk_reset_e mod_clk_get_reset(__aw_ccu_mod_clk_e id);

static __s32 mod_clk_set_parent(__aw_ccu_mod_clk_e id, __aw_ccu_sys_clk_e parent);
static __s32 mod_clk_set_status(__aw_ccu_mod_clk_e id, __aw_ccu_clk_onff_e status);
static __s32 mod_clk_set_rate(__aw_ccu_mod_clk_e id, __s64 rate);
static __s32 mod_clk_set_reset(__aw_ccu_mod_clk_e id, __aw_ccu_clk_reset_e reset);


static inline __aw_ccu_sys_clk_e _parse_module0_clk_src(volatile __ccmu_module0_clk_t *reg)
{
    switch(reg->ClkSrc)
    {
        case 0:
            return AW_SYS_CLK_HOSC;
        case 1:
            return AW_SYS_CLK_PLL62;
        case 2:
            return AW_SYS_CLK_PLL5P;
        default:
            return AW_SYS_CLK_NONE;
    }
    return AW_SYS_CLK_NONE;
}


static inline __aw_ccu_sys_clk_e _parse_defemp_clk_src(volatile __ccmu_fedemp_clk_t *reg)
{
    switch(reg->ClkSrc)
    {
        case 0:
            return AW_SYS_CLK_PLL3;
        case 1:
            return AW_SYS_CLK_PLL7;
        case 2:
            return AW_SYS_CLK_PLL5P;
        default:
            return AW_SYS_CLK_NONE;
    }
    return AW_SYS_CLK_NONE;
}


static inline __s32 _set_module0_clk_src(volatile __ccmu_module0_clk_t *reg, __aw_ccu_sys_clk_e parent)
{
    switch(parent)
    {
        case AW_SYS_CLK_HOSC:
            reg->ClkSrc = 0;
            break;
        case AW_SYS_CLK_PLL62:
            reg->ClkSrc = 1;
            break;
        case AW_SYS_CLK_PLL5P:
            reg->ClkSrc = 2;
            break;
        default:
            return -1;
    }

    return 0;
}


static inline __s32 _set_defemp_clk_src(volatile __ccmu_fedemp_clk_t *reg, __aw_ccu_sys_clk_e parent)
{
    switch(parent)
    {
        case AW_SYS_CLK_PLL3:
            reg->ClkSrc = 0;
            break;
        case AW_SYS_CLK_PLL7:
            reg->ClkSrc = 1;
            break;
        case AW_SYS_CLK_PLL5P:
            reg->ClkSrc = 2;
            break;
        default:
            return -1;
    }

    return 0;
}


static inline __aw_ccu_clk_onff_e _get_module0_clk_status(volatile __ccmu_module0_clk_t *reg)
{
    return reg->SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
}


static inline __s32 _set_module0_clk_status(volatile __ccmu_module0_clk_t *reg, __aw_ccu_clk_onff_e status)
{
    reg->SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
    return 0;
}


static inline __aw_ccu_clk_onff_e _get_defemp_clk_status(volatile __ccmu_fedemp_clk_t *reg)
{
    return reg->SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
}


static inline __s32 _set_defemp_clk_status(volatile __ccmu_fedemp_clk_t *reg, __aw_ccu_clk_onff_e status)
{
    reg->SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
    return 0;
}


static inline __u32 _get_module0_clk_rate(volatile __ccmu_module0_clk_t *reg)
{
    return (1<<reg->ClkPreDiv) * (reg->ClkDiv+1);
}


static inline __s32 _set_module0_clk_rate(volatile __ccmu_module0_clk_t *reg, __u64 rate)
{
    if(rate > 16*8)
    {
        return -1;
    }
    else if(rate > 16*4)
    {
        reg->ClkPreDiv = 3;
        reg->ClkDiv    = (rate>>3)-1;
    }
    else if(rate > 16*2)
    {
        reg->ClkPreDiv = 2;
        reg->ClkDiv    = (rate>>2)-1;
    }
    else if(rate > 16*1)
    {
       reg->ClkPreDiv = 1;
        reg->ClkDiv    = (rate>>1)-1;
    }
    else if(rate > 0)
    {
        reg->ClkPreDiv = 0;
        reg->ClkDiv    = rate-1;
    }
    else
    {
        return -1;
    }

    return 0;
}



static __aw_ccu_sys_clk_e mod_clk_get_parent(__aw_ccu_mod_clk_e id)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
            return _parse_module0_clk_src(&aw_ccu_reg->NandClk);
        case AW_MOD_CLK_MSC:
            return _parse_module0_clk_src(&aw_ccu_reg->MsClk);
        case AW_MOD_CLK_SDC0:
            return _parse_module0_clk_src(&aw_ccu_reg->SdMmc0Clk);
        case AW_MOD_CLK_SDC1:
            return _parse_module0_clk_src(&aw_ccu_reg->SdMmc1Clk);
        case AW_MOD_CLK_SDC2:
            return _parse_module0_clk_src(&aw_ccu_reg->SdMmc2Clk);
        case AW_MOD_CLK_TS:
            return _parse_module0_clk_src(&aw_ccu_reg->TsClk);
        case AW_MOD_CLK_SS:
            return _parse_module0_clk_src(&aw_ccu_reg->SsClk);
        case AW_MOD_CLK_SPI0:
            return _parse_module0_clk_src(&aw_ccu_reg->Spi0Clk);
        case AW_MOD_CLK_SPI1:
            return _parse_module0_clk_src(&aw_ccu_reg->Spi1Clk);
        case AW_MOD_CLK_SPI2:
            return _parse_module0_clk_src(&aw_ccu_reg->Spi2Clk);
        case AW_MOD_CLK_IR0:
            return _parse_module0_clk_src(&aw_ccu_reg->Ir0Clk);
        case AW_MOD_CLK_I2S:
            return AW_SYS_CLK_PLL2;
        case AW_MOD_CLK_SPDIF:
            return AW_SYS_CLK_PLL2;
        case AW_MOD_CLK_KEYPAD:
        {
            switch(aw_ccu_reg->KeyPadClk.ClkSrc)
            {
                case 0:
                    return AW_SYS_CLK_HOSC;
                case 2:
                    return AW_SYS_CLK_LOSC;
                default:
                    return AW_SYS_CLK_NONE;
            }
            return AW_SYS_CLK_NONE;
        }
        case AW_MOD_CLK_USBPHY:
        case AW_MOD_CLK_USBPHY0:
        case AW_MOD_CLK_USBPHY1:
        case AW_MOD_CLK_USBOHCI0:
            return AW_SYS_CLK_PLL62;
        case AW_MOD_CLK_GPS:
            switch(aw_ccu_reg->GpsClk.ClkSrc)
            {
                case 0:
                    return AW_SYS_CLK_HOSC;
                case 1:
                    return AW_SYS_CLK_PLL62;
                case 2:
                    return AW_SYS_CLK_PLL7;
                default:
                    return AW_SYS_CLK_PLL4;
            }
        case AW_MOD_CLK_DEBE0:
            return _parse_defemp_clk_src(&aw_ccu_reg->DeBe0Clk);
        case AW_MOD_CLK_DEFE0:
            return _parse_defemp_clk_src(&aw_ccu_reg->DeFe0Clk);
        case AW_MOD_CLK_LCD0CH0:
        {
            switch(aw_ccu_reg->Lcd0Ch0Clk.ClkSrc)
            {
                case 0:
                    return AW_SYS_CLK_PLL3;
                case 1:
                    return AW_SYS_CLK_PLL7;
                case 2:
                    return AW_SYS_CLK_PLL3X2;
                case 3:
                    return AW_SYS_CLK_PLL7X2;
                default:
                    return AW_SYS_CLK_NONE;
            }
            return AW_SYS_CLK_NONE;
        }
        case AW_MOD_CLK_LCD0CH1_S1:
        case AW_MOD_CLK_LCD0CH1_S2:
        {
            switch(aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Src)
            {
                case 0:
                    return AW_SYS_CLK_PLL3;
                case 1:
                    return AW_SYS_CLK_PLL7;
                case 2:
                    return AW_SYS_CLK_PLL3X2;
                case 3:
                    return AW_SYS_CLK_PLL7X2;
                default:
                    return AW_SYS_CLK_NONE;
            }
            return AW_SYS_CLK_NONE;
        }
        case AW_MOD_CLK_CSI0:
        {
            switch(aw_ccu_reg->Csi0Clk.ClkSrc)
            {
                case 0:
                    return AW_SYS_CLK_HOSC;
                case 1:
                    return AW_SYS_CLK_PLL3;
                case 2:
                    return AW_SYS_CLK_PLL7;
                case 5:
                    return AW_SYS_CLK_PLL3X2;
                case 6:
                    return AW_SYS_CLK_PLL7X2;
                default:
                    return AW_SYS_CLK_NONE;
            }
            return AW_SYS_CLK_NONE;
        }
        case AW_MOD_CLK_VE:
            return AW_SYS_CLK_PLL4;
        case AW_MOD_CLK_ADDA:
            return AW_SYS_CLK_PLL2;
        case AW_MOD_CLK_AVS:
            return AW_SYS_CLK_HOSC;
        case AW_MOD_CLK_LVDS:
            return AW_SYS_CLK_NONE;
        case AW_MOD_CLK_HDMI:
        {
            switch(aw_ccu_reg->HdmiClk.ClkSrc)
            {
                case 0:
                    return AW_SYS_CLK_PLL3;
                case 1:
                    return AW_SYS_CLK_PLL7;
                case 2:
                    return AW_SYS_CLK_PLL3X2;
                case 3:
                    return AW_SYS_CLK_PLL7X2;
                default:
                    return AW_SYS_CLK_NONE;
            }
            return AW_SYS_CLK_NONE;
        }
        case AW_MOD_CLK_MALI:
        {
            switch(aw_ccu_reg->MaliClk.ClkSrc)
            {
                case 0:
                    return AW_SYS_CLK_PLL3;
                case 1:
                    return AW_SYS_CLK_PLL4;
                case 2:
                    return AW_SYS_CLK_PLL5P;
                default:
                    return AW_SYS_CLK_PLL7;
            }
            return AW_SYS_CLK_NONE;
        }

        case AW_MOD_CLK_TWI0:
        case AW_MOD_CLK_TWI1:
        case AW_MOD_CLK_TWI2:
        case AW_MOD_CLK_UART0:
        case AW_MOD_CLK_UART1:
        case AW_MOD_CLK_UART2:
        case AW_MOD_CLK_UART3:
            return AW_SYS_CLK_APB1;

        case AW_MOD_CLK_IEP:
        default:
            return AW_SYS_CLK_NONE;
    }
}


/*
*********************************************************************************************************
*                           mod_clk_get_status
*
*Description: get module clock on/off status;
*
*Arguments  : id    module clock id;
*
*Return     : result;
*               AW_CCU_CLK_OFF, module clock is off;
*               AW_CCU_CLK_ON,  module clock is on;
*
*Notes      :
*
*********************************************************************************************************
*/
static __aw_ccu_clk_onff_e mod_clk_get_status(__aw_ccu_mod_clk_e id)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
            return _get_module0_clk_status(&aw_ccu_reg->NandClk);
        case AW_MOD_CLK_MSC:
            return _get_module0_clk_status(&aw_ccu_reg->MsClk);
        case AW_MOD_CLK_SDC0:
            return _get_module0_clk_status(&aw_ccu_reg->SdMmc0Clk);
        case AW_MOD_CLK_SDC1:
            return _get_module0_clk_status(&aw_ccu_reg->SdMmc1Clk);
        case AW_MOD_CLK_SDC2:
            return _get_module0_clk_status(&aw_ccu_reg->SdMmc2Clk);
        case AW_MOD_CLK_TS:
            return _get_module0_clk_status(&aw_ccu_reg->TsClk);
        case AW_MOD_CLK_SS:
            return _get_module0_clk_status(&aw_ccu_reg->SsClk);
        case AW_MOD_CLK_SPI0:
            return _get_module0_clk_status(&aw_ccu_reg->Spi0Clk);
        case AW_MOD_CLK_SPI1:
            return _get_module0_clk_status(&aw_ccu_reg->Spi1Clk);
        case AW_MOD_CLK_SPI2:
            return _get_module0_clk_status(&aw_ccu_reg->Spi2Clk);
        case AW_MOD_CLK_IR0:
            return _get_module0_clk_status(&aw_ccu_reg->Ir0Clk);
        case AW_MOD_CLK_I2S:
            return aw_ccu_reg->I2sClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SPDIF:
            return aw_ccu_reg->SpdifClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_KEYPAD:
            return aw_ccu_reg->KeyPadClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_USBPHY:
            return aw_ccu_reg->UsbClk.PhySpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_USBPHY0:
            return aw_ccu_reg->UsbClk.UsbPhy0Rst? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_USBPHY1:
            return aw_ccu_reg->UsbClk.UsbPhy1Rst? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_USBOHCI0:
            return aw_ccu_reg->UsbClk.OHCI0SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_GPS:
            return aw_ccu_reg->GpsClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_DEBE0:
            return _get_defemp_clk_status(&aw_ccu_reg->DeBe0Clk);
        case AW_MOD_CLK_DEFE0:
            return _get_defemp_clk_status(&aw_ccu_reg->DeFe0Clk);
        case AW_MOD_CLK_LCD0CH0:
            return aw_ccu_reg->Lcd0Ch0Clk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_LCD0CH1_S1:
            return aw_ccu_reg->Lcd0Ch1Clk.SpecClk1Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_LCD0CH1_S2:
            return aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_CSI0:
            return aw_ccu_reg->Csi0Clk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_VE:
            return aw_ccu_reg->VeClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_ADDA:
            return aw_ccu_reg->AddaClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AVS:
            return aw_ccu_reg->AvsClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_LVDS:
            return AW_CCU_CLK_ON;
        case AW_MOD_CLK_HDMI:
            return aw_ccu_reg->HdmiClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_MALI:
            return aw_ccu_reg->MaliClk.SpecClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;

        case AW_MOD_CLK_TWI0:
        case AW_MOD_CLK_TWI1:
        case AW_MOD_CLK_TWI2:
        case AW_MOD_CLK_UART0:
        case AW_MOD_CLK_UART1:
        case AW_MOD_CLK_UART2:
        case AW_MOD_CLK_UART3:
            return AW_CCU_CLK_ON;

        case AW_MOD_CLK_AXI_DRAM:
            return aw_ccu_reg->AxiGate.SdramGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_USB0:
            return aw_ccu_reg->AhbGate0.Usb0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_EHCI0:
            return aw_ccu_reg->AhbGate0.Ehci0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_OHCI0:
            return aw_ccu_reg->AhbGate0.Ohci0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SS:
            return aw_ccu_reg->AhbGate0.SsGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_DMA:
            return aw_ccu_reg->AhbGate0.DmaGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_BIST:
            return aw_ccu_reg->AhbGate0.BistGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SDMMC0:
            return aw_ccu_reg->AhbGate0.Sdmmc0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SDMMC1:
            return aw_ccu_reg->AhbGate0.Sdmmc1Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SDMMC2:
            return aw_ccu_reg->AhbGate0.Sdmmc2Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_MS:
            return aw_ccu_reg->AhbGate0.MsGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_NAND:
            return aw_ccu_reg->AhbGate0.NandGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SDRAM:
            return aw_ccu_reg->AhbGate0.SdramGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_EMAC:
            return aw_ccu_reg->AhbGate0.EmacGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_TS:
            return aw_ccu_reg->AhbGate0.TsGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SPI0:
            return aw_ccu_reg->AhbGate0.Spi0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SPI1:
            return aw_ccu_reg->AhbGate0.Spi1Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_SPI2:
            return aw_ccu_reg->AhbGate0.Spi2Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_GPS:
            return aw_ccu_reg->AhbGate0.GpsGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_VE:
            return aw_ccu_reg->AhbGate1.VeGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_TVE0:
            return aw_ccu_reg->AhbGate1.Tve0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_LCD0:
            return aw_ccu_reg->AhbGate1.Lcd0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_CSI0:
            return aw_ccu_reg->AhbGate1.Csi0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_HDMI:
            return aw_ccu_reg->AhbGate1.HdmiDGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_DEBE0:
            return aw_ccu_reg->AhbGate1.DeBe0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_DEFE0:
            return aw_ccu_reg->AhbGate1.DeFe0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_MALI:
            return aw_ccu_reg->AhbGate1.MaliGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_ADDA:
            return aw_ccu_reg->Apb0Gate.AddaGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_SPDIF:
            return aw_ccu_reg->Apb0Gate.SpdifGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_I2S:
            return aw_ccu_reg->Apb0Gate.IisGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_PIO:
            return aw_ccu_reg->Apb0Gate.PioGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_IR0:
            return aw_ccu_reg->Apb0Gate.Ir0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_KEYPAD:
            return aw_ccu_reg->Apb0Gate.KeypadGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_TWI0:
            return aw_ccu_reg->Apb1Gate.Twi0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_TWI1:
            return aw_ccu_reg->Apb1Gate.Twi1Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_TWI2:
            return aw_ccu_reg->Apb1Gate.Twi2Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_UART0:
            return aw_ccu_reg->Apb1Gate.Uart0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_UART1:
            return aw_ccu_reg->Apb1Gate.Uart1Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_UART2:
            return aw_ccu_reg->Apb1Gate.Uart2Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_APB_UART3:
            return aw_ccu_reg->Apb1Gate.Uart3Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_VE:
            return aw_ccu_reg->DramGate.VeGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_CSI0:
            return aw_ccu_reg->DramGate.Csi0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_TS:
            return aw_ccu_reg->DramGate.TsGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_TVE0:
            return aw_ccu_reg->DramGate.Tve0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_DEFE0:
            return aw_ccu_reg->DramGate.DeFe0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_DEBE0:
            return aw_ccu_reg->DramGate.DeBe0Gate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;

        case AW_MOD_CLK_IEP:
            return aw_ccu_reg->IepClk.ClkGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_AHB_IEP:
            return aw_ccu_reg->AhbGate1.IepGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;
        case AW_MOD_CLK_SDRAM_IEP:
            return aw_ccu_reg->DramGate.IepGate? AW_CCU_CLK_ON : AW_CCU_CLK_OFF;

        default:
            return AW_CCU_CLK_ON;
    }
    return AW_CCU_CLK_ON;
}


/*
*********************************************************************************************************
*                           mod_clk_get_rate
*
*Description: get module clock rate;
*
*Arguments  : id    module clock id;
*
*Return     : module clock division;
*
*Notes      :
*
*********************************************************************************************************
*/
static __s64 mod_clk_get_rate(__aw_ccu_mod_clk_e id)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
            return _get_module0_clk_rate(&aw_ccu_reg->NandClk);
        case AW_MOD_CLK_MSC:
            return _get_module0_clk_rate(&aw_ccu_reg->MsClk);
        case AW_MOD_CLK_SDC0:
            return _get_module0_clk_rate(&aw_ccu_reg->SdMmc0Clk);
        case AW_MOD_CLK_SDC1:
            return _get_module0_clk_rate(&aw_ccu_reg->SdMmc1Clk);
        case AW_MOD_CLK_SDC2:
            return _get_module0_clk_rate(&aw_ccu_reg->SdMmc2Clk);
        case AW_MOD_CLK_TS:
            return _get_module0_clk_rate(&aw_ccu_reg->TsClk);
        case AW_MOD_CLK_SS:
            return _get_module0_clk_rate(&aw_ccu_reg->SsClk);
        case AW_MOD_CLK_SPI0:
            return _get_module0_clk_rate(&aw_ccu_reg->Spi0Clk);
        case AW_MOD_CLK_SPI1:
            return _get_module0_clk_rate(&aw_ccu_reg->Spi1Clk);
        case AW_MOD_CLK_SPI2:
            return _get_module0_clk_rate(&aw_ccu_reg->Spi2Clk);
        case AW_MOD_CLK_IR0:
            return _get_module0_clk_rate(&aw_ccu_reg->Ir0Clk);
        case AW_MOD_CLK_I2S:
            return (1 << aw_ccu_reg->I2sClk.ClkDiv);
        case AW_MOD_CLK_SPDIF:
            return (1 << aw_ccu_reg->SpdifClk.ClkDiv);
        case AW_MOD_CLK_KEYPAD:
            return (1 << aw_ccu_reg->KeyPadClk.ClkPreDiv) * (aw_ccu_reg->KeyPadClk.ClkDiv + 1);
        case AW_MOD_CLK_USBPHY:
        case AW_MOD_CLK_USBPHY0:
        case AW_MOD_CLK_USBPHY1:
        case AW_MOD_CLK_USBOHCI0:
            return 1;
        case AW_MOD_CLK_GPS:
            return aw_ccu_reg->GpsClk.DivM + 1;
        case AW_MOD_CLK_DEBE0:
            return aw_ccu_reg->DeBe0Clk.ClkDiv + 1;
        case AW_MOD_CLK_DEFE0:
            return aw_ccu_reg->DeFe0Clk.ClkDiv + 1;
        case AW_MOD_CLK_LCD0CH0:
            return 1;
        case AW_MOD_CLK_LCD0CH1_S1:
            return (aw_ccu_reg->Lcd0Ch1Clk.ClkDiv + 1) * (aw_ccu_reg->Lcd0Ch1Clk.SpecClk1Src + 1);
        case AW_MOD_CLK_LCD0CH1_S2:
            return aw_ccu_reg->Lcd0Ch1Clk.ClkDiv + 1;
        case AW_MOD_CLK_CSI0:
            return aw_ccu_reg->Csi0Clk.ClkDiv + 1;
        case AW_MOD_CLK_VE:
            return (aw_ccu_reg->VeClk.ClkDiv + 1);
        case AW_MOD_CLK_ADDA:
        case AW_MOD_CLK_AVS:
            return 1;
        case AW_MOD_CLK_LVDS:
            return 1;
        case AW_MOD_CLK_HDMI:
            return (aw_ccu_reg->HdmiClk.ClkDiv + 1);
        case AW_MOD_CLK_MALI:
            return (aw_ccu_reg->MaliClk.ClkDiv + 1);

        case AW_MOD_CLK_IEP:
        default:
            return 1;
    }
}


/*
*********************************************************************************************************
*                           mod_clk_get_reset
*
*Description: get module clock reset status;
*
*Arguments  : id    module clock id;
*
*Return     : result,
*               AW_CCU_CLK_RESET,   module clock reset valid;
*               AW_CCU_CLK_NRESET,  module clock reset invalid;
*
*Notes      :
*
*********************************************************************************************************
*/
static __aw_ccu_clk_reset_e mod_clk_get_reset(__aw_ccu_mod_clk_e id)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
        case AW_MOD_CLK_MSC:
        case AW_MOD_CLK_SDC0:
        case AW_MOD_CLK_SDC1:
        case AW_MOD_CLK_SDC2:
        case AW_MOD_CLK_TS:
        case AW_MOD_CLK_SS:
        case AW_MOD_CLK_SPI0:
        case AW_MOD_CLK_SPI1:
        case AW_MOD_CLK_SPI2:
        case AW_MOD_CLK_IR0:
        case AW_MOD_CLK_I2S:
        case AW_MOD_CLK_SPDIF:
        case AW_MOD_CLK_KEYPAD:
            return AW_CCU_CLK_NRESET;
        case AW_MOD_CLK_USBPHY:
        case AW_MOD_CLK_USBPHY0:
        case AW_MOD_CLK_USBPHY1:
            return AW_CCU_CLK_NRESET;
        case AW_MOD_CLK_USBOHCI0:
            return AW_CCU_CLK_NRESET;
        case AW_MOD_CLK_GPS:
            return aw_ccu_reg->GpsClk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_DEBE0:
            return aw_ccu_reg->DeBe0Clk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_DEFE0:
            return aw_ccu_reg->DeFe0Clk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_LCD0CH0:
            return aw_ccu_reg->Lcd0Ch0Clk.LcdReset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_LCD0CH1_S1:
            return AW_CCU_CLK_NRESET;
        case AW_MOD_CLK_LCD0CH1_S2:
            return aw_ccu_reg->Lcd0Ch0Clk.TveReset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_CSI0:
            return aw_ccu_reg->Csi0Clk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_VE:
            return aw_ccu_reg->VeClk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_ADDA:
        case AW_MOD_CLK_AVS:
            return AW_CCU_CLK_NRESET;
        case AW_MOD_CLK_LVDS:
            return aw_ccu_reg->LvdsClk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;
        case AW_MOD_CLK_HDMI:
            return AW_CCU_CLK_NRESET;
        case AW_MOD_CLK_MALI:
            return aw_ccu_reg->MaliClk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;

        case AW_MOD_CLK_IEP:
            return aw_ccu_reg->IepClk.Reset? AW_CCU_CLK_NRESET : AW_CCU_CLK_RESET;

        default:
            return AW_CCU_CLK_NRESET;
    }

}


/*
*********************************************************************************************************
*                           mod_clk_set_parent
*
*Description: set clock parent id for module clock;
*
*Arguments  : id        module clock id;
*             parent    parent clock id;
*
*Return     : result;
*               0,  set parent successed;
*              !0,  set parent failed;
*Notes      :
*
*********************************************************************************************************
*/
static __s32 mod_clk_set_parent(__aw_ccu_mod_clk_e id, __aw_ccu_sys_clk_e parent)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
            return _set_module0_clk_src(&aw_ccu_reg->NandClk, parent);
        case AW_MOD_CLK_MSC:
            return _set_module0_clk_src(&aw_ccu_reg->MsClk, parent);
        case AW_MOD_CLK_SDC0:
            return _set_module0_clk_src(&aw_ccu_reg->SdMmc0Clk, parent);
        case AW_MOD_CLK_SDC1:
            return _set_module0_clk_src(&aw_ccu_reg->SdMmc1Clk, parent);
        case AW_MOD_CLK_SDC2:
            return _set_module0_clk_src(&aw_ccu_reg->SdMmc2Clk, parent);
        case AW_MOD_CLK_TS:
            return _set_module0_clk_src(&aw_ccu_reg->TsClk, parent);
        case AW_MOD_CLK_SS:
            return _set_module0_clk_src(&aw_ccu_reg->SsClk, parent);
        case AW_MOD_CLK_SPI0:
            return _set_module0_clk_src(&aw_ccu_reg->Spi0Clk, parent);
        case AW_MOD_CLK_SPI1:
            return _set_module0_clk_src(&aw_ccu_reg->Spi1Clk, parent);
        case AW_MOD_CLK_SPI2:
            return _set_module0_clk_src(&aw_ccu_reg->Spi2Clk, parent);
        case AW_MOD_CLK_IR0:
            return _set_module0_clk_src(&aw_ccu_reg->Ir0Clk, parent);
        case AW_MOD_CLK_I2S:
            return (parent == AW_SYS_CLK_PLL2)? 0 : -1;
        case AW_MOD_CLK_SPDIF:
            return (parent == AW_SYS_CLK_PLL2)? 0 : -1;
        case AW_MOD_CLK_KEYPAD:
        {
            switch(parent)
            {
                case AW_SYS_CLK_HOSC:
                    aw_ccu_reg->KeyPadClk.ClkSrc = 0;
                    return 0;
                case AW_SYS_CLK_LOSC:
                    aw_ccu_reg->KeyPadClk.ClkSrc = 2;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_USBPHY:
        case AW_MOD_CLK_USBPHY0:
        case AW_MOD_CLK_USBPHY1:
        case AW_MOD_CLK_USBOHCI0:
        {
            if(parent == AW_SYS_CLK_PLL62)
            {
                return 0;
            }

            return -1;
        }
        case AW_MOD_CLK_DEBE0:
            return _set_defemp_clk_src(&aw_ccu_reg->DeBe0Clk, parent);
        case AW_MOD_CLK_DEFE0:
            return _set_defemp_clk_src(&aw_ccu_reg->DeFe0Clk, parent);
        case AW_MOD_CLK_LCD0CH0:
        {
            switch(parent)
            {
                case AW_SYS_CLK_PLL3:
                    aw_ccu_reg->Lcd0Ch0Clk.ClkSrc = 0;
                    return 0;
                case AW_SYS_CLK_PLL3X2:
                    aw_ccu_reg->Lcd0Ch0Clk.ClkSrc = 2;
                    return 0;
                case AW_SYS_CLK_PLL7:
                    aw_ccu_reg->Lcd0Ch0Clk.ClkSrc = 1;
                    return 0;
                case AW_SYS_CLK_PLL7X2:
                    aw_ccu_reg->Lcd0Ch0Clk.ClkSrc = 3;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_LCD0CH1_S1:
            return 0;
        case AW_MOD_CLK_LCD0CH1_S2:
        {
            switch(parent)
            {
                case AW_SYS_CLK_PLL3:
                    aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Src = 0;
                    return 0;
                case AW_SYS_CLK_PLL3X2:
                    aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Src = 2;
                    return 0;
                case AW_SYS_CLK_PLL7:
                    aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Src = 1;
                    return 0;
                case AW_SYS_CLK_PLL7X2:
                    aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Src = 3;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_CSI0:
        {
            switch(parent)
            {
                case AW_SYS_CLK_HOSC:
                    aw_ccu_reg->Csi0Clk.ClkSrc = 0;
                    return 0;
                case AW_SYS_CLK_PLL3:
                    aw_ccu_reg->Csi0Clk.ClkSrc = 1;
                    return 0;
                case AW_SYS_CLK_PLL7:
                    aw_ccu_reg->Csi0Clk.ClkSrc = 2;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_VE:
            return (parent == AW_SYS_CLK_PLL4)? 0 : -1;
        case AW_MOD_CLK_ADDA:
            return (parent == AW_SYS_CLK_PLL2)? 0 : -1;
        case AW_MOD_CLK_AVS:
            return (parent == AW_SYS_CLK_HOSC)? 0 : -1;
        case AW_MOD_CLK_HDMI:
        {
            switch(parent)
            {
                case AW_SYS_CLK_PLL3:
                {
                    aw_ccu_reg->HdmiClk.ClkSrc = 0;
                    return 0;
                }
                case AW_SYS_CLK_PLL3X2:
                {
                    aw_ccu_reg->HdmiClk.ClkSrc = 2;
                    return 0;
                }
                case AW_SYS_CLK_PLL7:
                {
                    aw_ccu_reg->HdmiClk.ClkSrc = 1;
                    return 0;
                }
                case AW_SYS_CLK_PLL7X2:
                {
                    aw_ccu_reg->HdmiClk.ClkSrc = 3;
                    return 0;
                }
                default:
                    return -1;
            }
        }
        case AW_MOD_CLK_MALI:
        {
            switch(parent)
            {
                case AW_SYS_CLK_PLL3:
                    aw_ccu_reg->MaliClk.ClkSrc = 0;
                    return 0;
                case AW_SYS_CLK_PLL4:
                    aw_ccu_reg->MaliClk.ClkSrc = 1;
                    return 0;
                case AW_SYS_CLK_PLL5P:
                    aw_ccu_reg->MaliClk.ClkSrc = 2;
                    return 0;
                case AW_SYS_CLK_PLL7:
                    aw_ccu_reg->MaliClk.ClkSrc = 3;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_GPS:
            switch(parent)
            {
                case AW_SYS_CLK_HOSC:
                    aw_ccu_reg->GpsClk.ClkSrc = 0;
                    return 0;
                case AW_SYS_CLK_PLL62:
                    aw_ccu_reg->GpsClk.ClkSrc = 1;
                    return 0;
                case AW_SYS_CLK_PLL7:
                    aw_ccu_reg->GpsClk.ClkSrc = 2;
                    return 0;
                case AW_SYS_CLK_PLL4:
                    aw_ccu_reg->GpsClk.ClkSrc = 3;
                    return 0;
                default:
                    return -1;
            }
        case AW_MOD_CLK_TWI0:
        case AW_MOD_CLK_TWI1:
        case AW_MOD_CLK_TWI2:
        case AW_MOD_CLK_UART0:
        case AW_MOD_CLK_UART1:
        case AW_MOD_CLK_UART2:
        case AW_MOD_CLK_UART3:
            return (parent == AW_SYS_CLK_APB1)? 0 : -1;

        case AW_MOD_CLK_LVDS:
        case AW_MOD_CLK_IEP:
        default:
            return (parent == AW_SYS_CLK_NONE)? 0 : -1;
    }
    return (parent == AW_SYS_CLK_NONE)? 0 : -1;
}


/*
*********************************************************************************************************
*                           mod_clk_set_status
*
*Description: set module clock on/off status;
*
*Arguments  : id        module clock id;
*             status    module clock on/off status;
*
*Return     : result
*               0,  set module clock on/off status successed;
*              !0,  set module clock on/off status failed;
*
*Notes      :
*
*********************************************************************************************************
*/
static __s32 mod_clk_set_status(__aw_ccu_mod_clk_e id, __aw_ccu_clk_onff_e status)
{
    volatile __dram_host_cfg_reg_t *dram_host = (__dram_host_cfg_reg_t *)DRAM_HOST_CFG_BASE;

    switch(id)
    {
        case AW_MOD_CLK_NFC:
            return _set_module0_clk_status(&aw_ccu_reg->NandClk, status);
        case AW_MOD_CLK_MSC:
            return _set_module0_clk_status(&aw_ccu_reg->MsClk, status);
        case AW_MOD_CLK_SDC0:
            return _set_module0_clk_status(&aw_ccu_reg->SdMmc0Clk, status);
        case AW_MOD_CLK_SDC1:
            return _set_module0_clk_status(&aw_ccu_reg->SdMmc1Clk, status);
        case AW_MOD_CLK_SDC2:
            return _set_module0_clk_status(&aw_ccu_reg->SdMmc2Clk, status);
        case AW_MOD_CLK_TS:
            return _set_module0_clk_status(&aw_ccu_reg->TsClk, status);
        case AW_MOD_CLK_SS:
            return _set_module0_clk_status(&aw_ccu_reg->SsClk, status);
        case AW_MOD_CLK_SPI0:
            return _set_module0_clk_status(&aw_ccu_reg->Spi0Clk, status);
        case AW_MOD_CLK_SPI1:
            return _set_module0_clk_status(&aw_ccu_reg->Spi1Clk, status);
        case AW_MOD_CLK_SPI2:
            return _set_module0_clk_status(&aw_ccu_reg->Spi2Clk, status);
        case AW_MOD_CLK_IR0:
            return _set_module0_clk_status(&aw_ccu_reg->Ir0Clk, status);
        case AW_MOD_CLK_I2S:
            aw_ccu_reg->I2sClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SPDIF:
            aw_ccu_reg->SpdifClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_KEYPAD:
        {
            aw_ccu_reg->KeyPadClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_USBPHY:
        {
            aw_ccu_reg->UsbClk.PhySpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_USBPHY0:
        {
            aw_ccu_reg->UsbClk.UsbPhy0Rst = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_USBPHY1:
        {
            aw_ccu_reg->UsbClk.UsbPhy1Rst = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_USBOHCI0:
            aw_ccu_reg->UsbClk.OHCI0SpecClkGate = ((status == AW_CCU_CLK_OFF)? 0 : 1);
            return 0;
        case AW_MOD_CLK_GPS:
        {
            aw_ccu_reg->GpsClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_DEBE0:
            return _set_defemp_clk_status(&aw_ccu_reg->DeBe0Clk, status);
        case AW_MOD_CLK_DEFE0:
            return _set_defemp_clk_status(&aw_ccu_reg->DeFe0Clk, status);
        case AW_MOD_CLK_LCD0CH0:
            aw_ccu_reg->Lcd0Ch0Clk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_LCD0CH1_S1:
            aw_ccu_reg->Lcd0Ch1Clk.SpecClk1Gate = (status == AW_CCU_CLK_ON)? 1 : 0;
            return 0;
        case AW_MOD_CLK_LCD0CH1_S2:
            aw_ccu_reg->Lcd0Ch1Clk.SpecClk2Gate = (status == AW_CCU_CLK_ON)? 1 : 0;
            return 0;
        case AW_MOD_CLK_CSI0:
            aw_ccu_reg->Csi0Clk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_VE:
            aw_ccu_reg->VeClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_ADDA:
            aw_ccu_reg->AddaClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AVS:
            aw_ccu_reg->AvsClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_LVDS:
            return 0;
        case AW_MOD_CLK_HDMI:
            aw_ccu_reg->HdmiClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_MALI:
            aw_ccu_reg->MaliClk.SpecClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;

        case AW_MOD_CLK_TWI0:
        case AW_MOD_CLK_TWI1:
        case AW_MOD_CLK_TWI2:
        case AW_MOD_CLK_UART0:
        case AW_MOD_CLK_UART1:
        case AW_MOD_CLK_UART2:
        case AW_MOD_CLK_UART3:
            return 0;

        case AW_MOD_CLK_AXI_DRAM:
            aw_ccu_reg->AxiGate.SdramGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_USB0:
            aw_ccu_reg->AhbGate0.Usb0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_EHCI0:
            aw_ccu_reg->AhbGate0.Ehci0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_OHCI0:
            aw_ccu_reg->AhbGate0.Ohci0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SS:
            aw_ccu_reg->AhbGate0.SsGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;

        case AW_MOD_CLK_AHB_DMA:
            aw_ccu_reg->AhbGate0.DmaGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_BIST:
            aw_ccu_reg->AhbGate0.BistGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SDMMC0:
            aw_ccu_reg->AhbGate0.Sdmmc0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SDMMC1:
            aw_ccu_reg->AhbGate0.Sdmmc1Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SDMMC2:
            aw_ccu_reg->AhbGate0.Sdmmc2Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_MS:
            aw_ccu_reg->AhbGate0.MsGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_NAND:
            aw_ccu_reg->AhbGate0.NandGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SDRAM:
            aw_ccu_reg->AhbGate0.SdramGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_EMAC:
            aw_ccu_reg->AhbGate0.EmacGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_TS:
            aw_ccu_reg->AhbGate0.TsGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SPI0:
            aw_ccu_reg->AhbGate0.Spi0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SPI1:
            aw_ccu_reg->AhbGate0.Spi1Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_SPI2:
            aw_ccu_reg->AhbGate0.Spi2Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_GPS:
            aw_ccu_reg->AhbGate0.GpsGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_VE:
            aw_ccu_reg->AhbGate1.VeGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_TVE0:
            aw_ccu_reg->AhbGate1.Tve0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_LCD0:
            aw_ccu_reg->AhbGate1.Lcd0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_CSI0:
            aw_ccu_reg->AhbGate1.Csi0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_HDMI:
            aw_ccu_reg->AhbGate1.HdmiDGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_DEBE0:
            aw_ccu_reg->AhbGate1.DeBe0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_DEFE0:
            aw_ccu_reg->AhbGate1.DeFe0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_MALI:
            aw_ccu_reg->AhbGate1.MaliGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;

        case AW_MOD_CLK_APB_ADDA:
            aw_ccu_reg->Apb0Gate.AddaGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_SPDIF:
            aw_ccu_reg->Apb0Gate.SpdifGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_I2S:
            aw_ccu_reg->Apb0Gate.IisGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_PIO:
            aw_ccu_reg->Apb0Gate.PioGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_IR0:
            aw_ccu_reg->Apb0Gate.Ir0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_KEYPAD:
            aw_ccu_reg->Apb0Gate.KeypadGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_TWI0:
            aw_ccu_reg->Apb1Gate.Twi0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_TWI1:
            aw_ccu_reg->Apb1Gate.Twi1Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_TWI2:
            aw_ccu_reg->Apb1Gate.Twi2Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_UART0:
            aw_ccu_reg->Apb1Gate.Uart0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_UART1:
            aw_ccu_reg->Apb1Gate.Uart1Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_UART2:
            aw_ccu_reg->Apb1Gate.Uart2Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_APB_UART3:
            aw_ccu_reg->Apb1Gate.Uart3Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_VE:
            dram_host[DRAM_HOST_VE].AcsEn = (status == AW_CCU_CLK_OFF)? 0 : 1;
            aw_ccu_reg->DramGate.VeGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_CSI0:
            dram_host[DRAM_HOST_CSI].AcsEn = (status == AW_CCU_CLK_OFF)? 0 : 1;
            aw_ccu_reg->DramGate.Csi0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_TS:
            dram_host[DRAM_HOST_TSDM].AcsEn = (status == AW_CCU_CLK_OFF)? 0 : 1;
            aw_ccu_reg->DramGate.TsGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_TVE0:
            aw_ccu_reg->DramGate.Tve0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_DEFE0:
            dram_host[DRAM_HOST_FE].AcsEn = (status == AW_CCU_CLK_OFF)? 0 : 1;
            aw_ccu_reg->DramGate.DeFe0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_DEBE0:
            dram_host[DRAM_HOST_BE].AcsEn = (status == AW_CCU_CLK_OFF)? 0 : 1;
            aw_ccu_reg->DramGate.DeBe0Gate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;

        case AW_MOD_CLK_IEP:
            aw_ccu_reg->IepClk.ClkGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_AHB_IEP:
            aw_ccu_reg->AhbGate1.IepGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;
        case AW_MOD_CLK_SDRAM_IEP:
            dram_host[DRAM_HOST_IEP].AcsEn = (status == AW_CCU_CLK_OFF)? 0 : 1;
            aw_ccu_reg->DramGate.IepGate = (status == AW_CCU_CLK_OFF)? 0 : 1;
            return 0;

        default:
            return -1;
    }
}


/*
*********************************************************************************************************
*                           mod_clk_set_rate
*
*Description: set module clock division;
*
*Arguments  : id    module clock id;
*             rate  module clock division;
*
*Return     : result
*               0,  set module clock rate successed;
*              !0,  set module clock rate failed;
*
*Notes      :
*
*********************************************************************************************************
*/
static __s32 mod_clk_set_rate(__aw_ccu_mod_clk_e id, __s64 rate)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
            return _set_module0_clk_rate(&aw_ccu_reg->NandClk, rate);
        case AW_MOD_CLK_MSC:
            return _set_module0_clk_rate(&aw_ccu_reg->MsClk, rate);
        case AW_MOD_CLK_SDC0:
            return _set_module0_clk_rate(&aw_ccu_reg->SdMmc0Clk, rate);
        case AW_MOD_CLK_SDC1:
            return _set_module0_clk_rate(&aw_ccu_reg->SdMmc1Clk, rate);
        case AW_MOD_CLK_SDC2:
            return _set_module0_clk_rate(&aw_ccu_reg->SdMmc2Clk, rate);
        case AW_MOD_CLK_TS:
            return _set_module0_clk_rate(&aw_ccu_reg->TsClk, rate);
        case AW_MOD_CLK_SS:
            return _set_module0_clk_rate(&aw_ccu_reg->SsClk, rate);
        case AW_MOD_CLK_SPI0:
            return _set_module0_clk_rate(&aw_ccu_reg->Spi0Clk, rate);
        case AW_MOD_CLK_SPI1:
            return _set_module0_clk_rate(&aw_ccu_reg->Spi1Clk, rate);
        case AW_MOD_CLK_SPI2:
            return _set_module0_clk_rate(&aw_ccu_reg->Spi2Clk, rate);
        case AW_MOD_CLK_IR0:
            return _set_module0_clk_rate(&aw_ccu_reg->Ir0Clk, rate);
        case AW_MOD_CLK_I2S:
        {
            switch(rate)
            {
                case 1:
                    aw_ccu_reg->I2sClk.ClkDiv = 0;
                    return 0;
                case 2:
                    aw_ccu_reg->I2sClk.ClkDiv = 1;
                    return 0;
                case 4:
                    aw_ccu_reg->I2sClk.ClkDiv = 2;
                    return 0;
                case 8:
                    aw_ccu_reg->I2sClk.ClkDiv = 3;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_SPDIF:
        {
            switch(rate)
            {
                case 1:
                    aw_ccu_reg->SpdifClk.ClkDiv = 0;
                    return 0;
                case 2:
                    aw_ccu_reg->SpdifClk.ClkDiv = 1;
                    return 0;
                case 4:
                    aw_ccu_reg->SpdifClk.ClkDiv = 2;
                    return 0;
                case 8:
                    aw_ccu_reg->SpdifClk.ClkDiv = 3;
                    return 0;
                default:
                    return -1;
            }
            return -1;
        }
        case AW_MOD_CLK_KEYPAD:
        {
            if(rate > 32*8)
            {
                return -1;
            }
            else if(rate > 32*4)
            {
                aw_ccu_reg->KeyPadClk.ClkPreDiv = 3;
                aw_ccu_reg->KeyPadClk.ClkDiv    = (rate>>3)-1;
            }
            else if(rate > 32*2)
            {
                aw_ccu_reg->KeyPadClk.ClkPreDiv = 2;
                aw_ccu_reg->KeyPadClk.ClkDiv    = (rate>>2)-1;
            }
            else if(rate > 32*1)
            {
                aw_ccu_reg->KeyPadClk.ClkPreDiv = 1;
                aw_ccu_reg->KeyPadClk.ClkDiv    = (rate>>1)-1;
            }
            else if(rate > 32*0)
            {
                aw_ccu_reg->KeyPadClk.ClkPreDiv = 0;
                aw_ccu_reg->KeyPadClk.ClkDiv    = rate-1;
            }
            else
            {
                return -1;
            }
            return 0;
        }
        case AW_MOD_CLK_DEBE0:
        {
            if((rate < 1) || (rate > 16))
            {
                return -1;
            }
            aw_ccu_reg->DeBe0Clk.ClkDiv = rate-1;
            return 0;
        }
        case AW_MOD_CLK_DEFE0:
        {
            if((rate < 1) || (rate > 16))
            {
                return -1;
            }
            aw_ccu_reg->DeFe0Clk.ClkDiv = rate-1;
            return 0;
        }
        case AW_MOD_CLK_LCD0CH1_S1:
        {
            if(rate == (aw_ccu_reg->Lcd0Ch1Clk.ClkDiv+1))
            {
                aw_ccu_reg->Lcd0Ch1Clk.SpecClk1Src = 0;
                return 0;
            }
            else if(rate == ((aw_ccu_reg->Lcd0Ch1Clk.ClkDiv+1)<<1))
            {
                aw_ccu_reg->Lcd0Ch1Clk.SpecClk1Src = 1;
                return 0;
            }

            return 0;
        }
        case AW_MOD_CLK_LCD0CH1_S2:
        {
            if((rate < 1) || (rate > 16))
            {
                return -1;
            }
            aw_ccu_reg->Lcd0Ch1Clk.ClkDiv = rate-1;
            return 0;
        }
        case AW_MOD_CLK_CSI0:
        {
            if((rate < 1) || (rate > 32))
            {
                return -1;
            }
            aw_ccu_reg->Csi0Clk.ClkDiv = rate-1;
            return 0;
        }
        case AW_MOD_CLK_VE:
        {
            if((rate < 1) || (rate > 8))
            {
                return -1;
            }
            aw_ccu_reg->VeClk.ClkDiv = rate-1;
            return 0;
        }
        case AW_MOD_CLK_HDMI:
        {
            if((rate < 1) || (rate > 16))
            {
                return -1;
            }
            aw_ccu_reg->HdmiClk.ClkDiv = rate-1;
            return 0;
        }
        case AW_MOD_CLK_MALI:
        {
            if((rate < 1) || (rate > 16))
            {
                return -1;
            }
            aw_ccu_reg->MaliClk.ClkDiv = rate-1;
            return 0;
        }

        case AW_MOD_CLK_GPS:
        {
            if((rate < 1) || (rate > 8))
                return -1;
            aw_ccu_reg->GpsClk.DivM = rate-1;
            return 0;
        }

        case AW_MOD_CLK_LCD0CH0:
        case AW_MOD_CLK_LVDS:
        case AW_MOD_CLK_ADDA:
        case AW_MOD_CLK_USBPHY:
        case AW_MOD_CLK_USBPHY0:
        case AW_MOD_CLK_USBPHY1:
        case AW_MOD_CLK_USBOHCI0:
        case AW_MOD_CLK_AVS:
        case AW_MOD_CLK_IEP:
        default:
            return (rate == 1)? 0 : -1;
    }
    return (rate == 1)? 0 : -1;
}


/*
*********************************************************************************************************
*                           mod_clk_set_reset
*
*Description: set module clock reset status
*
*Arguments  : id    module clock id;
*             reset module clock reset status;
*
*Return     : result;
*               0,  set module clock reset status successed;
*              !0,  set module clock reset status failed;
*
*Notes      :
*
*********************************************************************************************************
*/
static __s32 mod_clk_set_reset(__aw_ccu_mod_clk_e id, __aw_ccu_clk_reset_e reset)
{
    switch(id)
    {
        case AW_MOD_CLK_NFC:
        case AW_MOD_CLK_MSC:
        case AW_MOD_CLK_SDC0:
        case AW_MOD_CLK_SDC1:
        case AW_MOD_CLK_SDC2:
        case AW_MOD_CLK_TS:
        case AW_MOD_CLK_SS:
        case AW_MOD_CLK_SPI0:
        case AW_MOD_CLK_SPI1:
        case AW_MOD_CLK_SPI2:
        case AW_MOD_CLK_IR0:
        case AW_MOD_CLK_I2S:
        case AW_MOD_CLK_SPDIF:
        case AW_MOD_CLK_USBPHY:
        case AW_MOD_CLK_USBOHCI0:
            return (reset == AW_CCU_CLK_NRESET)? 0 : -1;
        case AW_MOD_CLK_USBPHY0:
        case AW_MOD_CLK_USBPHY1:
            return 0;

        case AW_MOD_CLK_GPS:
        {
            aw_ccu_reg->GpsClk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_DEBE0:
        {
            aw_ccu_reg->DeBe0Clk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_DEFE0:
        {
            aw_ccu_reg->DeFe0Clk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_LCD0CH0:
        {
            aw_ccu_reg->Lcd0Ch0Clk.LcdReset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_CSI0:
        {
            aw_ccu_reg->Csi0Clk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_VE:
        {
            aw_ccu_reg->VeClk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        }
        case AW_MOD_CLK_LVDS:
            aw_ccu_reg->LvdsClk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;
        case AW_MOD_CLK_MALI:
            aw_ccu_reg->MaliClk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;

        case AW_MOD_CLK_IEP:
            aw_ccu_reg->IepClk.Reset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;

        case AW_MOD_CLK_LCD0CH1_S2:
            aw_ccu_reg->Lcd0Ch0Clk.TveReset = (reset == AW_CCU_CLK_RESET)? 0 : 1;
            return 0;

        case AW_MOD_CLK_LCD0CH1_S1:
        case AW_MOD_CLK_ADDA:
        case AW_MOD_CLK_AVS:
        case AW_MOD_CLK_HDMI:
        default:
            return (reset == AW_CCU_CLK_NRESET)? 0 : -1;
    }
    return (reset == AW_CCU_CLK_NRESET)? 0 : -1;
}


/*
*********************************************************************************************************
*                           aw_ccu_get_mod_clk_cnt
*
*Description: get the count of the module clock.
*
*Arguments  : none
*
*Return     : count of the module clock;
*
*Notes      :
*
*********************************************************************************************************
*/
__s32 aw_ccu_get_mod_clk_cnt(void)
{
    return (__u32)AW_MOD_CLK_CNT;
}


/*
*********************************************************************************************************
*                           mod_clk_get_rate_hz
*
*Description: get module clock rate based on hz;
*
*Arguments  : id    module clock id;
*
*Return     : module clock division;
*
*Notes      :
*
*********************************************************************************************************
*/
static __s64 mod_clk_get_rate_hz(__aw_ccu_mod_clk_e id)
{
    __s64               tmpRate;
    __aw_ccu_clk_t      *tmpParent;

    tmpRate = mod_clk_get_rate(id);
    tmpParent = aw_ccu_get_sys_clk(mod_clk_get_parent(id));

    return ccu_clk_uldiv(tmpParent->rate, tmpRate);
}


/*
*********************************************************************************************************
*                           mod_clk_set_rate_hz
*
*Description: set module clock rate based on hz;
*
*Arguments  : id    module clock id;
*             rate  module clock division;
*
*Return     : result
*               0,  set module clock rate successed;
*              !0,  set module clock rate failed;
*
*Notes      :
*
*********************************************************************************************************
*/
static __s32 mod_clk_set_rate_hz(__aw_ccu_mod_clk_e id, __s64 rate)
{
    __aw_ccu_clk_t      *tmpParent;

    tmpParent = aw_ccu_get_sys_clk(mod_clk_get_parent(id));
    return mod_clk_set_rate(id, ccu_clk_uldiv((tmpParent->rate + (rate>>1)), rate));
}


/*
*********************************************************************************************************
*                           aw_ccu_get_mod_clk
*
*Description: get module clock information by clock id.
*
*Arguments  : id    module clock id;
*
*Return     : module clock handle, return NULL if get clock information failed;
*
*Notes      :
*
*********************************************************************************************************
*/
__aw_ccu_clk_t *aw_ccu_get_mod_clk(__aw_ccu_mod_clk_e id)
{
    __s32   tmpIdx = (__u32)id;

    /* check if clock id is valid   */
    if((id < AW_MOD_CLK_NONE) || (id >= AW_MOD_CLK_CNT))
    {
        CCU_ERR("ID is invalid when get module clock information!\n");
        return NULL;
    }

    /* query module clock information from hardware */
    aw_ccu_mod_clk[tmpIdx].parent = mod_clk_get_parent(id);
    aw_ccu_mod_clk[tmpIdx].onoff  = mod_clk_get_status(id);
    aw_ccu_mod_clk[tmpIdx].rate   = mod_clk_get_rate_hz(id);
    aw_ccu_mod_clk[tmpIdx].reset  = mod_clk_get_reset(id);
    aw_ccu_mod_clk[tmpIdx].hash   = ccu_clk_calc_hash(aw_ccu_mod_clk[tmpIdx].name);

    return &aw_ccu_mod_clk[tmpIdx];
}


/*
*********************************************************************************************************
*                           aw_ccu_set_mod_clk
*
*Description: set module clock parameters;
*
*Arguments  : clk   handle of module clock;
*
*Return     : error type.
*
*Notes      :
*
*********************************************************************************************************
*/
__aw_ccu_err_e aw_ccu_set_mod_clk(__aw_ccu_clk_t *clk)
{
    __aw_ccu_clk_t  tmpClk;

    if(!clk)
    {
        CCU_ERR("Clock handle is NULL when set system clock!\n");
        return AW_CCU_ERR_PARA_NULL;
    }

    /* backup old parameter */
    tmpClk.parent = mod_clk_get_parent(clk->id);
    tmpClk.onoff  = mod_clk_get_status(clk->id);
    tmpClk.reset  = mod_clk_get_reset(clk->id);
    tmpClk.rate   = mod_clk_get_rate_hz(clk->id);

    /* try to set new parameter */
    if(!mod_clk_set_parent(clk->id, clk->parent))
    {
        if(!mod_clk_set_rate_hz(clk->id, clk->rate))
        {
            if(!mod_clk_set_status(clk->id, clk->onoff))
            {
                if(!mod_clk_set_reset(clk->id, clk->reset))
                {
                    /* update managemer parameter  */
                    aw_ccu_mod_clk[(__u32)clk->id].parent = clk->parent;
                    aw_ccu_mod_clk[(__u32)clk->id].onoff  = clk->onoff;
                    aw_ccu_mod_clk[(__u32)clk->id].reset  = clk->reset;
                    aw_ccu_mod_clk[(__u32)clk->id].rate   = clk->rate;

                    return AW_CCU_ERR_NONE;
                }
                else
                {
                    CCU_ERR("set %s reset status to %d failed!\n", clk->name, clk->reset);
                }

                /* resetore on/off status */
                mod_clk_set_status(clk->id, tmpClk.onoff);
            }
            else
            {
                CCU_ERR("set %s on/off status to %d failed!\n", clk->name, clk->onoff);
            }

            /* restore clock rate */
            mod_clk_set_rate_hz(clk->id, tmpClk.rate);
        }
        else
        {
            CCU_ERR("set %s clock rate to %lld failed!\n", clk->name, clk->rate);
        }

        /* restore clock parent */
        mod_clk_set_parent(clk->id, tmpClk.parent);
    }
    else
    {
        CCU_ERR("set %s clock parent to (id = %d) failed!\n", clk->name, (__s32)clk->parent);
    }

    /* update clock manager paremter */
    aw_ccu_mod_clk[(__u32)clk->id].parent = tmpClk.parent;
    aw_ccu_mod_clk[(__u32)clk->id].onoff  = tmpClk.onoff;
    aw_ccu_mod_clk[(__u32)clk->id].reset  = tmpClk.reset;
    aw_ccu_mod_clk[(__u32)clk->id].rate   = tmpClk.rate;

    return AW_CCU_ERR_PARA_INVALID;
}

