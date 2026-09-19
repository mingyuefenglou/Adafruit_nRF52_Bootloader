# Adafruit nRF52 Bootloader（含 NiNi 5883 板）

基于 [jitingcn/Adafruit_nRF52_Bootloader](https://github.com/jitingcn/Adafruit_nRF52_Bootloader)（master @ 37cb910，其上又源自 [adafruit/Adafruit_nRF52_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)）维护，为自研 5883 板加入两块板定义。

## 本仓新增板

| 板 | 用途 |
|---|---|
| `nini_nrf52833_5883` | 追踪器 |
| `nini_nrf52833_5883_rx` | 接收器 |

两板均为三颗共阴 LED（蓝为主状态灯、红为 2s 呼吸信标），复位时按住 SW0 或 500ms 内双击复位键进入 DFU。

## 编译

GNU Make + `arm-none-eabi-gcc`（13.x），需先 `git submodule update --init`：

```bash
make BOARD=nini_nrf52833_5883 all
# 产物：_build/build-<板>/ 下 3 个 hex（bare / nosd / s140_7.3.0）
# update-*.uf2 需显式：make BOARD=<板> _build/build-<板>/update-<板>_bootloader-_nosd.uf2 ...
```

---

本仓基于 [jitingcn/Adafruit_nRF52_Bootloader](https://github.com/jitingcn/Adafruit_nRF52_Bootloader)（其上源自 [adafruit/Adafruit_nRF52_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)）维护。
Adafruit 原版文档（官方板卡清单、nrfutil DFU 说明等）与本项目无关，完整内容请见上游仓库；许可沿袭上游（见仓库 `LICENSE`）。
