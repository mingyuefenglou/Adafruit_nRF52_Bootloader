/*
 * 板级配置：nini_nrf52833_5883_rx ——【接收端 receiver】的 Adafruit UF2 bootloader
 * 芯片 nRF52833（512KB flash / 128KB RAM），SoftDevice s140 7.3.0。
 * 引脚速览（与固件 dts 一致，三颗 LED【共阴】接法，高电平点亮——新板焊对，
 * 不移植旧板绿蓝对调补偿）：
 *   蓝 P0.29（LED_PRIMARY，BL 状态灯）/ 绿 P0.30 / 红 P0.28（呼吸信标）；
 *   DFU 按键 = SW0 P0.03。
 * USB：VID 0x1209 / PID 0x7693（pid.codes 已为 SlimeVR 注册）。
 * 说明：本板文件由我们注入，上游 Adafruit/jitingcn 仓库不含。
 */

#ifndef _NINI_NRF52833_5883_RX_H
#define _NINI_NRF52833_5883_RX_H

#define UICR_REGOUT0_VALUE UICR_REGOUT0_VOUT_3V3   // 片内稳压器输出挡位 3.3V（沿旧 v2_rx 板，UICR 一次性烧写）

#define _PINNUM(port, pin)    ((port)*32 + (pin))

/*------------------------------------------------------------------*/
/* LED
 *------------------------------------------------------------------*/
#define LEDS_NUMBER       3
#define LED_PRIMARY_PIN   _PINNUM(0, 29) // 蓝灯（BL 状态：DFU 中快闪）——共阴高电平点亮
#define LED_SECONDARY_PIN _PINNUM(0, 30) // 绿灯
#define LED_THIRDARY_PIN  _PINNUM(0, 28) // 红灯（由三灯 patch 驱动为慢呼吸信标）
#define LED_STATE_ON      1   // 1=高电平点亮（共阴接法 / 拉电流驱动），与固件 dts 的 GPIO_ACTIVE_HIGH 一致

/*------------------------------------------------------------------*/
/* BUTTON
 *------------------------------------------------------------------*/
#define BUTTONS_NUMBER    1
#define BUTTON_DFU        _PINNUM(0, 3)   // 主 DFU 按键 SW0：复位时按住 → 进 UF2 bootloader（U 盘模式）
#define BUTTON_PULL       NRF_GPIO_PIN_PULLUP   // 按键默认上拉（按下拉低）

//--------------------------------------------------------------------+
// BLE OTA
//--------------------------------------------------------------------+
// BLE OTA 广播的设备信息（OTA 时主机看到的厂商/型号名）
#define BLEDIS_MANUFACTURER   "NiNi_Unicorn & MINGYUE"
#define BLEDIS_MODEL          "NiNi_Unicorn & MINGYUE smol slime 5883 receiver"

//--------------------------------------------------------------------+
// USB
//--------------------------------------------------------------------+
#define USB_DESC_VID           0x1209   // pid.codes 厂商号，与各 slimenrf 兄弟板一致
#define USB_DESC_UF2_PID       0x7693   // UF2 U 盘模式 PID
#define USB_DESC_CDC_ONLY_PID  0x7693   // CDC-only 模式 PID（与 UF2 模式同值，沿用兄弟板惯例）

//------------- UF2（板子进 bootloader 后枚举成的 U 盘信息）-------------//
#define UF2_PRODUCT_NAME      "NiNi_Unicorn & MINGYUE smol slime 5883 receiver"
#define UF2_VOLUME_LABEL      "NINISLIME"   // U 盘卷标
#define UF2_BOARD_ID          "nRF52833-smol"
#define UF2_INDEX_URL         "https://docs.slimevr.dev/smol-slimes/firmware/smol-flashing-firmware.html"

#endif
