#include "boards.h"
#include "uf2/configkeys.h"

/*
 * bootloaderConfig：放在 .bootloaderConfig 段的「板级配置表」。
 * UF2 升级工具/上位机会读它来核验目标板（VID+PID）、flash/RAM 大小、UF2 家族等。
 * 改这里的【数值】会影响升级校验，故只加注释、不改值。
 */
__attribute__((used, section(".bootloaderConfig")))
const uint32_t bootloaderConfig[] =
{
  /* CF2 START */
  CFG_MAGIC0, CFG_MAGIC1,                       // 魔数（配置表头标识）
  5, 100,                                       // 已用条目数 / 总条目数

  204, 0x80000,                                 // FLASH_BYTES：512KB flash
  205, 0x20000,                                 // RAM_BYTES：128KB RAM
  208, (USB_DESC_VID << 16) | USB_DESC_UF2_PID, // 板 ID = USB 的 VID+PID；UF2 升级时据此校验
  209, 0x621e937a,                              // UF2_FAMILY：nRF52833 家族标识
  210, 0x20,                                    // PINS_PORT_SIZE = PA_32（P0 共 32 脚）

  0, 0, 0, 0, 0, 0, 0, 0
  /* CF2 END */
};
