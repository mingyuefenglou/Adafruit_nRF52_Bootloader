# Adafruit nRF52 Bootloader

基于 [jitingcn/Adafruit\_nRF52\_Bootloader](https://github.com/jitingcn/Adafruit_nRF52_Bootloader)（master @ 37cb910，其上又源自 [adafruit/Adafruit\_nRF52\_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)）维护。

## 分支说明

| 分支 | 用途 |
|---|---|
| `main` | 稳定发布线——验证通过的版本（日常刷机用这里） |
| `NiNi_Slime_5883` | 开发线——板级定制与功能开发在此进行，验证后合入 `main` |
| `dev` | jitingcn 上游镜像（本仓不在此开发）——跟进上游更新、比对差异、合并上游修复 |

开发流程：在 `NiNi_Slime_5883` 提交 → 上板验证 → 合入 `main` 发布。

## 本仓新增板

|板|用途|
|-|-|
|`nini_nrf52833_5883`|追踪器|
|`nini_nrf52833_5883_rx`|接收器|

两板均为三颗共阴 LED。

## LED 状态指示（定型）

蓝=主状态灯三态；红/绿不参与（错误场景红快闪）。

| BL 状态 | 蓝灯表现 |
|---|---|
| 进 DFU、U 盘未挂载 | 柔和呼吸 3s 周期（等待感） |
| U 盘挂载成功 | 60% 常亮（就绪，拖文件） |
| 写入 UF2 中 | 5Hz 硬快闪（在写，别拔） |
| 写入完成 | 渐灭 → 重启 |
| 错误（CRC 失败等） | 蓝灭，红快闪 |
| BLE OTA（未连/已连/传输） | 同 DFU 三态对应 |

## 编译

GNU Make + `arm-none-eabi-gcc`（13.x），需先 `git submodule update --init`：

```bash
make BOARD=nini_nrf52833_5883 all
# 产物：build/build-<板>/ 下 3 个 hex（bare / nosd / s140_7.3.0）
# update-*.uf2 需显式：make BOARD=<板> _build/build-<板>/update-<板>_bootloader_nosd.uf2 ...
```

\---

本仓基于 [jitingcn/Adafruit\_nRF52\_Bootloader](https://github.com/jitingcn/Adafruit_nRF52_Bootloader)（其上源自 [adafruit/Adafruit\_nRF52\_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)）维护。
Adafruit 原版文档（官方板卡清单、nrfutil DFU 说明等）与本项目无关，完整内容请见上游仓库；许可沿袭上游（见仓库 `LICENSE`）。

