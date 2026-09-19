# board.mk —— nini_nrf52833_5883（追踪器 tracker 的 bootloader）编译选项
# 由顶层 Makefile 经 `-include src/boards/$(BOARD)/board.mk` 自动引入
# （板按 src/boards/<板名>/ 目录自动发现，无需在 Makefile/boards.c 里注册）。
# 注意：赋值行不得带行内 `#` 注释（make 会把 # 前的空格计入变量值）。

MCU_SUB_VARIANT = nrf52833
USB = 1
UF2_ENABLED = 1
