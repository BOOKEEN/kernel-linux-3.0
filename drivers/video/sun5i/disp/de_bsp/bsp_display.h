
#ifndef __EBSP_DISPLAY_H__
#define __EBSP_DISPLAY_H__

#define __LINUX_OSAL__
//#define __MELIS_OSAL__
//#define __WINCE_OSAL__
//#define __BOOT_OSAL__

#ifdef __LINUX_OSAL__
#include "linux/kernel.h"
#include "linux/mm.h"
#include <asm/uaccess.h>
#include <asm/memory.h>
#include <asm/unistd.h>
#include "linux/semaphore.h"
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/dma-mapping.h>
#include <linux/fb.h>
#include <linux/sched.h>   //wake_up_process()
#include <linux/kthread.h> //kthread_create()��kthread_run()
#include <linux/err.h> //IS_ERR()��PTR_ERR()
#include <linux/delay.h>
#include <linux/platform_device.h>
#include "asm-generic/int-ll64.h"
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/cdev.h>
#include <mach/sys_config.h>
#include <mach/clock.h>
#include <mach/aw_ccu.h>
#include <mach/system.h>
#include <linux/types.h>
#include <linux/timer.h>

typedef unsigned int __hdle;

#include <linux/drv_display.h>
#include "../OSAL/OSAL.h"

#if 1
#define OSAL_PRINTF(msg...) {printk(KERN_WARNING "[DISP] ");printk(msg);}
#define __inf(msg...)       
#define __msg(msg...)       
#define __wrn(msg...)       {printk(KERN_WARNING "[DISP WRN] file:%s,line:%d:    ",__FILE__,__LINE__);printk(msg);}
#define __here__
#else
#define OSAL_PRINTF(msg...) {printk(KERN_WARNING "[DISP] ");printk(msg);}
#define __inf(msg...)       {printk(KERN_WARNING "[DISP] ");printk(msg);}
#define __msg(msg...)       {printk(KERN_WARNING "[DISP] file:%s,line:%d:    ",__FILE__,__LINE__);printk(msg);}
#define __wrn(msg...)       {printk(KERN_WARNING "[DISP WRN] file:%s,line:%d:    ",__FILE__,__LINE__);printk(msg);}
#define __here__            {printk(KERN_WARNING "[DISP] file:%s,line:%d\n",__FILE__,__LINE__);}
#endif


#endif//end of define __LINUX_OSAL__

#ifdef __MELIS_OSAL__
#include "string.h"
#include "D:/winners/eBase/eBSP/BSP/sun_20/common_inc.h"
#endif

#ifdef __BOOT_OSAL__
#define OSAL_PRINTF wlibc_uprintf

#include "egon2.h"
#include "string.h"
#include "../OSAL/OSAL_De.h"
#endif


typedef struct
{
	__u32 base_image0;
	__u32 base_image1;
	__u32 base_scaler0;
	__u32 base_scaler1;
	__u32 base_lcdc0;
	__u32 base_lcdc1;
	__u32 base_tvec0;
	__u32 base_tvec1;
	__u32 base_pioc;
	__u32 base_sdram;
	__u32 base_ccmu;
	__u32 base_pwm;
	__u32 base_iep;
    __u32 base_tp;

	void (*tve_interrup) (__u32 sel);
	__s32 (*hdmi_set_mode)(__disp_tv_mode_t mode);
	__s32 (*Hdmi_open)(void);
	__s32 (*Hdmi_close)(void);
	__s32 (*hdmi_mode_support)(__disp_tv_mode_t mode);
	__s32 (*hdmi_get_HPD_status)(void);
	__s32 (*hdmi_set_pll)(__u32 pll, __u32 clk);
	__s32 (*disp_int_process)(__u32 sel);
        __s32 (*hdmi_suspend)(void);
        __s32 (*hdmi_resume)(void);
}__disp_bsp_init_para;

typedef enum {
    EINK_STBY_ACT_NORMAL        = 0,
    EINK_STBY_ACT_UPDATE        = 1,
} Eink_stby_act_e;

typedef struct
{
    __u32 width;
    __u32 height;
    __pixel_rgbfmt_t    pixelfmt;
}__eink_init_para;

extern __s32 BSP_disp_clk_on(__u32 type);
extern __s32 BSP_disp_clk_off(__u32 type);
extern __s32 BSP_disp_init(__disp_bsp_init_para * para);
extern __s32 BSP_disp_exit(__u32 mode);
extern __s32 BSP_disp_open(void);
extern __s32 BSP_disp_close(void);
extern __s32 BSP_disp_print_reg(__bool b_force_on, __u32 id);
extern __s32 BSP_disp_cmd_cache(__u32 sel);
extern __s32 BSP_disp_cmd_submit(__u32 sel);
extern __s32 BSP_disp_set_bk_color(__u32 sel, __disp_color_t *color);
extern __s32 BSP_disp_get_bk_color(__u32 sel, __disp_color_t *color);
extern __s32 BSP_disp_set_color_key(__u32 sel, __disp_colorkey_t *ck_mode);
extern __s32 BSP_disp_get_color_key(__u32 sel, __disp_colorkey_t *ck_mode);
extern __s32 BSP_disp_set_palette_table(__u32 sel, __u32 *pbuffer, __u32 offset, __u32 size);
extern __s32 BSP_disp_get_palette_table(__u32 sel, __u32 * pbuffer, __u32 offset,__u32 size);
extern __s32 BSP_disp_get_screen_height(__u32 sel);
extern __s32 BSP_disp_get_screen_width(__u32 sel);
extern __s32 BSP_disp_get_output_type(__u32 sel);
extern __s32 BSP_disp_get_frame_rate(__u32 sel);
extern __s32 BSP_disp_gamma_correction_enable(__u32 sel);
extern __s32 BSP_disp_gamma_correction_disable(__u32 sel);
extern __s32 BSP_disp_set_bright(__u32 sel, __u32 bright);
extern __s32 BSP_disp_get_bright(__u32 sel);
extern __s32 BSP_disp_set_contrast(__u32 sel, __u32 contrast);
extern __s32 BSP_disp_get_contrast(__u32 sel);
extern __s32 BSP_disp_set_saturation(__u32 sel, __u32 saturation);
extern __s32 BSP_disp_get_saturation(__u32 sel);
extern __s32 BSP_disp_set_hue(__u32 sel, __u32 hue);
extern __s32 BSP_disp_get_hue(__u32 sel);
extern __s32 BSP_disp_capture_screen(__u32 sel, __disp_capture_screen_para_t * para);
extern __s32 BSP_disp_set_screen_size(__u32 sel, __disp_rectsz_t * size);
extern __s32 BSP_disp_set_output_csc(__u32 sel, __u32 out_type, __u32 drc_en);
extern __s32 BSP_disp_de_flicker_enable(__u32 sel, __bool b_en);
extern __s32 BSP_disp_store_image_reg(__u32 sel, __u32 addr);
extern __s32 BSP_disp_restore_image_reg(__u32 sel, __u32 addr);
extern __s32 BSP_disp_store_scaler_reg(__u32 sel, __u32 addr);
extern __s32 BSP_disp_restore_scaler_reg(__u32 sel, __u32 addr);
extern __s32 BSP_disp_restore_lcdc_reg(__u32 sel);
extern __s32 BSP_disp_restore_tvec_reg(__u32 sel);

extern __s32 BSP_disp_layer_request(__u32 sel, __disp_layer_work_mode_t mode);
extern __s32 BSP_disp_layer_release(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_open(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_close(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_framebuffer(__u32 sel, __u32 hid,__disp_fb_t *fbinfo);
extern __s32 BSP_disp_layer_get_framebuffer(__u32 sel, __u32 hid,__disp_fb_t*fbinfo);
extern __s32 BSP_disp_layer_set_src_window(__u32 sel, __u32 hid,__disp_rect_t *regn);
extern __s32 BSP_disp_layer_get_src_window(__u32 sel, __u32 hid,__disp_rect_t *regn);
extern __s32 BSP_disp_layer_set_screen_window(__u32 sel, __u32 hid,__disp_rect_t* regn);
extern __s32 BSP_disp_layer_get_screen_window(__u32 sel, __u32 hid,__disp_rect_t *regn);
extern __s32 BSP_disp_layer_wait_reg_load(__u32 sel);
extern __s32 BSP_disp_layer_set_para(__u32 sel, __u32 hid, __disp_layer_info_t * layer_para);
extern __s32 BSP_disp_layer_get_para(__u32 sel, __u32 hid, __disp_layer_info_t * layer_para);
extern __s32 BSP_disp_layer_set_top(__u32 sel, __u32  handle);
extern __s32 BSP_disp_layer_set_bottom(__u32 sel, __u32  handle);
extern __s32 BSP_disp_layer_set_alpha_value(__u32 sel, __u32 hid,__u8 value);
extern __s32 BSP_disp_layer_get_alpha_value(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_alpha_enable(__u32 sel, __u32 hid, __bool enable);
extern __s32 BSP_disp_layer_get_alpha_enable(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_pipe(__u32 sel, __u32 hid,__u8 pipe);
extern __s32 BSP_disp_layer_get_pipe(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_get_piro(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_colorkey_enable(__u32 sel, __u32 hid, __bool enable);
extern __s32 BSP_disp_layer_get_colorkey_enable(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_smooth(__u32 sel, __u32 hid, __disp_video_smooth_t  mode);
extern __s32 BSP_disp_layer_get_smooth(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_bright(__u32 sel, __u32 hid, __u32 bright);
extern __s32 BSP_disp_layer_set_contrast(__u32 sel, __u32 hid, __u32 contrast);
extern __s32 BSP_disp_layer_set_saturation(__u32 sel, __u32 hid, __u32 saturation);
extern __s32 BSP_disp_layer_set_hue(__u32 sel, __u32 hid, __u32 hue);
extern __s32 BSP_disp_layer_enhance_enable(__u32 sel, __u32 hid, __bool enable);
extern __s32 BSP_disp_layer_get_bright(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_get_contrast(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_get_saturation(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_get_hue(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_get_enhance_enable(__u32 sel, __u32 hid);

extern __s32 BSP_disp_layer_vpp_enable(__u32 sel, __u32 hid, __bool enable);
extern __s32 BSP_disp_layer_get_vpp_enable(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_luma_sharp_level(__u32 sel, __u32 hid, __u32 level);
extern __s32 BSP_disp_layer_get_luma_sharp_level(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_chroma_sharp_level(__u32 sel, __u32 hid, __u32 level);
extern __s32 BSP_disp_layer_get_chroma_sharp_level(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_white_exten_level(__u32 sel, __u32 hid, __u32 level);
extern __s32 BSP_disp_layer_get_white_exten_level(__u32 sel, __u32 hid);
extern __s32 BSP_disp_layer_set_black_exten_level(__u32 sel, __u32 hid, __u32 level);
extern __s32 BSP_disp_layer_get_black_exten_level(__u32 sel, __u32 hid);

extern __s32 BSP_disp_scaler_get_smooth(__u32 sel);
extern __s32 BSP_disp_scaler_set_smooth(__u32 sel, __disp_video_smooth_t  mode);
extern __s32 BSP_disp_scaler_request(void);
extern __s32 BSP_disp_scaler_release(__u32 handle);
extern __s32 BSP_disp_scaler_start(__u32 handle,__disp_scaler_para_t *scl);

extern __s32 BSP_disp_hwc_enable(__u32 sel, __bool enable);
extern __s32 BSP_disp_hwc_set_pos(__u32 sel, __disp_pos_t *pos);
extern __s32 BSP_disp_hwc_get_pos(__u32 sel, __disp_pos_t *pos);
extern __s32 BSP_disp_hwc_set_framebuffer(__u32 sel, __disp_hwc_pattern_t *patmem);
extern __s32 BSP_disp_hwc_set_palette(__u32 sel, void *palette,__u32 offset, __u32 palette_size);

extern __s32 BSP_disp_video_set_fb(__u32 sel, __u32 hid, __disp_video_fb_t *in_addr);
extern __s32 BSP_disp_video_get_frame_id(__u32 sel, __u32 hid);
extern __s32 BSP_disp_video_get_dit_info(__u32 sel, __u32 hid, __disp_dit_info_t * dit_info);
extern __s32 BSP_disp_video_start(__u32 sel, __u32 hid);
extern __s32 BSP_disp_video_stop(__u32 sel, __u32 hid);

extern __s32 BSP_disp_lcd_open_before(__u32 sel);
extern __s32 BSP_disp_lcd_open_after(__u32 sel);
extern __lcd_flow_t * BSP_disp_lcd_get_open_flow(__u32 sel);
extern __s32 BSP_disp_lcd_close_befor(__u32 sel);
extern __s32 BSP_disp_lcd_close_after(__u32 sel);
extern __lcd_flow_t * BSP_disp_lcd_get_close_flow(__u32 sel);
extern __s32 BSP_disp_lcd_xy_switch(__u32 sel, __s32 mode);
extern __s32 BSP_disp_set_gamma_table(__u32 sel, __u32 *gamtbl_addr,__u32 gamtbl_size);
extern __s32 BSP_disp_lcd_set_bright(__u32 sel, __u32  bright, __u32 from_iep);
extern __s32 BSP_disp_lcd_get_bright(__u32 sel);
extern __s32 BSP_disp_lcd_set_src(__u32 sel, __disp_lcdc_src_t src);
extern void TCON_open(__u32 sel);
extern void TCON_close(__u32 sel);
extern __s32 LCD_PWM_EN(__u32 sel, __bool b_en);
extern __s32 LCD_BL_EN(__u32 sel, __bool b_en);
extern __s32 BSP_disp_lcd_user_defined_func(__u32 sel, __u32 para1, __u32 para2, __u32 para3);
extern __s32 pwm_set_para(__u32 channel, __pwm_info_t * pwm_info);
extern __s32 pwm_get_para(__u32 channel, __pwm_info_t * pwm_info);
extern __s32 BSP_disp_get_timming(__u32 sel, __disp_tcon_timing_t * tt);
extern __u32 BSP_disp_get_cur_line(__u32 sel);
extern __s32 BSP_disp_close_lcd_backlight(__u32 sel);
extern void LCD_delay_ms(__u32 ms);

extern __s32 BSP_disp_tv_open(__u32 sel);
extern __s32 BSP_disp_tv_close(__u32 sel);
extern __s32 BSP_disp_tv_set_mode(__u32 sel, __disp_tv_mode_t tv_mod);
extern __s32 BSP_disp_tv_get_mode(__u32 sel);
extern __s32 BSP_disp_tv_get_interface(__u32 sel);
extern __s32 BSP_disp_tv_auto_check_enable(__u32 sel);
extern __s32 BSP_disp_tv_auto_check_disable(__u32 sel);
extern __s32 BSP_disp_tv_set_src(__u32 sel, __disp_lcdc_src_t src);
extern __s32 BSP_disp_tv_get_dac_status(__u32 sel, __u32 index);
extern __s32 BSP_disp_tv_set_dac_source(__u32 sel, __u32 index, __disp_tv_dac_source source);
extern __s32 BSP_disp_tv_get_dac_source(__u32 sel, __u32 index);

extern __s32 BSP_disp_hdmi_open(__u32 sel);
extern __s32 BSP_disp_hdmi_close(__u32 sel);
extern __s32 BSP_disp_hdmi_set_mode(__u32 sel, __disp_tv_mode_t  mode);
extern __s32 BSP_disp_hdmi_get_mode(__u32 sel);
extern __s32 BSP_disp_hdmi_check_support_mode(__u32 sel, __u8  mode);
extern __s32 BSP_disp_hdmi_get_hpd_status(__u32 sel);
extern __s32 BSP_disp_hdmi_set_src(__u32 sel, __disp_lcdc_src_t src);
extern __s32 BSP_disp_set_hdmi_func(__disp_hdmi_func * func);
extern __s32 BSP_disp_hdmi_suspend(void);
extern __s32 BSP_disp_hdmi_resume(void);

extern __s32 BSP_disp_vga_open(__u32 sel);
extern __s32 BSP_disp_vga_close(__u32 sel);
extern __s32 BSP_disp_vga_set_mode(__u32 sel, __disp_vga_mode_t  mode);
extern __s32 BSP_disp_vga_get_mode(__u32 sel);
extern __s32 BSP_disp_vga_set_src(__u32 sel, __disp_lcdc_src_t src);

extern __s32 BSP_disp_sprite_init(__u32 sel);
extern __s32 BSP_disp_sprite_exit(__u32 sel);
extern __s32 BSP_disp_sprite_open(__u32 sel);
extern __s32 BSP_disp_sprite_close(__u32 sel);
extern __s32 BSP_disp_sprite_alpha_enable(__u32 sel);
extern __s32 BSP_disp_sprite_alpha_disable(__u32 sel);
extern __s32 BSP_disp_sprite_get_alpha_enable(__u32 sel);
extern __s32 BSP_disp_sprite_set_alpha_vale(__u32 sel, __u32 alpha);
extern __s32 BSP_disp_sprite_get_alpha_value(__u32 sel);
extern __s32 BSP_disp_sprite_set_format(__u32 sel, __disp_pixel_fmt_t format, __disp_pixel_seq_t pixel_seq);
extern __s32 BSP_disp_sprite_set_palette_table(__u32 sel, __u32 *buffer, __u32 offset, __u32 size);
extern __s32 BSP_disp_sprite_set_order(__u32 sel, __s32 hid,__s32 dst_hid);
extern __s32 BSP_disp_sprite_get_top_block(__u32 sel);
extern __s32 BSP_disp_sprite_get_bottom_block(__u32 sel);
extern __s32 BSP_disp_sprite_get_block_number(__u32 sel);
extern __s32 BSP_disp_sprite_block_request(__u32 sel, __disp_sprite_block_para_t *para);
extern __s32 BSP_disp_sprite_block_release(__u32 sel, __s32 hid);
extern __s32 BSP_disp_sprite_block_set_screen_win(__u32 sel, __s32 hid, __disp_rect_t * scn_win);
extern __s32 BSP_disp_sprite_block_get_srceen_win(__u32 sel, __s32 hid, __disp_rect_t * scn_win);
extern __s32 BSP_disp_sprite_block_set_src_win(__u32 sel, __s32 hid, __disp_rect_t * scn_win);
extern __s32 BSP_disp_sprite_block_get_src_win(__u32 sel, __s32 hid, __disp_rect_t * scn_win);
extern __s32 BSP_disp_sprite_block_set_framebuffer(__u32 sel, __s32 hid, __disp_fb_t * fb);
extern __s32 BSP_disp_sprite_block_get_framebufer(__u32 sel, __s32 hid,__disp_fb_t *fb);
extern __s32 BSP_disp_sprite_block_set_top(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_set_bottom(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_get_pre_block(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_get_next_block(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_get_prio(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_open(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_close(__u32 sel, __u32 hid);
extern __s32 BSP_disp_sprite_block_set_para(__u32 sel, __u32 hid,__disp_sprite_block_para_t *para);
extern __s32 BSP_disp_sprite_block_get_para(__u32 sel, __u32 hid,__disp_sprite_block_para_t *para);

extern __s32 BSP_disp_iep_deflicker_enable(__u32 sel, __bool en);
extern __s32 BSP_disp_iep_get_deflicker_enable(__u32 sel);
extern __s32 BSP_disp_iep_drc_enable(__u32 sel, __bool en);
extern __s32 BSP_disp_iep_get_drc_enable(__u32 sel);
extern __s32 BSP_disp_iep_set_demo_win(__u32 sel, __u32 mode, __disp_rect_t *regn)	;

extern __s32 Disp_eink_init(__u32 sel, __eink_init_para* para);
extern __s32 Disp_eink_exit(__u32 sel);
extern __s32 Disp_eink_set_mode(__u32 sel, __eink_update_mode mode);
//20130417, yuanlian. add coordinate supported.
extern __s32 Disp_eink_update(__u32 sel, __u32 fb_id, __u32 mode, __u32 coordinate[]);
extern __s32 Disp_eink_set_temperature(__u32 sel, __u32 temperature);   //only for test

//add by heyihang. 2012-12-17
extern void Disp_eink_set_stby_act(Eink_stby_act_e act);

//add by heyihang. 2012-12-17
extern Eink_stby_act_e Disp_eink_get_stby_act(void);

//add by heyihang.2012-12-25
extern __s32 Disp_eink_get_update_status(__u32 sel);

//add by heyihang.2012-12-27
extern __u32 Disp_eink_get_all_zero_buf(void);

//add by heyihang. 2013-1-12
extern void Disp_eink_stby_act_lock(void);
extern void Disp_eink_stby_act_unlock(void);

extern __s32 Disp_eink_set_3v3(void);

#ifdef __LINUX_OSAL__
__s32 Display_set_fb_timming(__u32 sel);
#endif

#endif
