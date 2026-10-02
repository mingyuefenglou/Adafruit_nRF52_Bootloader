# Adafruit nRF52 Bootloader

> NiNi SlimeVR 追踪器/接收器的 UF2 + BLE OTA 引导加载器 —— 基于 jitingcn 分支维护，新增 nRF52833 两板与三灯状态指示。

[![build](https://github.com/mingyuefenglou/Adafruit_nRF52_Bootloader/actions/workflows/githubci.yml/badge.svg?branch=NiNi_Slime_5883)](https://github.com/mingyuefenglou/Adafruit_nRF52_Bootloader/actions/workflows/githubci.yml)
![MCU](https://img.shields.io/badge/MCU-nRF52833-333333)
![toolchain](https://img.shields.io/badge/toolchain-arm--none--eabi--gcc-blue)
![license](https://img.shields.io/badge/license-upstream-lightgrey)

基于 [jitingcn/Adafruit\_nRF52\_Bootloader](https://github.com/jitingcn/Adafruit_nRF52_Bootloader)（master @ 37cb910，其上又源自 [adafruit/Adafruit\_nRF52\_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)）维护。

## 特性

| 模块 | 说明 |
|---|---|
| **引导** | UF2（USB MSC 拖放刷机）+ BLE OTA（S140 SoftDevice）双 DFU 通道 |
| **新增板** | `nini_nrf52833`（追踪器）· `nini_nrf52833_rx`（接收器），三共阴 LED（GPIO 经 1kΩ 限流） |
| **灯语** | 🔴 无通讯（呼吸）/ 🟢 有通讯（呼吸）/ 🔵 写入中（10Hz 快闪）/ 写完全彩闪烁 1.2s 进 APP——状态一眼可辨 |
| **加固** | Receiver 断电必进 BL 修复：RESETREAS 早清 · 按键仅信引脚复位+去抖 · 60s 兜底超时 · 写完全彩闪烁反馈 |

## 分支说明

| 分支 | 用途 |
|---|---|
| `main` | 稳定发布线——验证通过的版本（日常刷机用这里） |
| `NiNi_Slime_5883` | 开发线——板级定制与功能开发在此进行，验证后合入 `main` |
| `dev` | jitingcn 上游镜像（本仓不在此开发）——跟进上游更新、比对差异、合并上游修复 |

开发流程：在 `NiNi_Slime_5883` 提交 → 上板验证 → 合入 `main` 发布。

## 本仓新增板

| 板 | 用途 |
|---|---|
| `nini_nrf52833` | 追踪器 |
| `nini_nrf52833_rx` | 接收器 |

两板均为三颗共阴 LED（GPIO 经 1kΩ 限流；红/绿/蓝引脚映射见各板 `board.h`）。

## LED 状态指示

三灯分工：**红**=无通讯、**绿**=有通讯、**蓝**=写入中（语义统一，一眼可辨）。无通讯/有通讯用**三角呼吸**（暗光不刺眼），写入态高频快闪（明确"在写，别拔"）。

| BL 状态 | 灯表现 |
|---|---|
| 上电未与电脑通讯（充电器/纯供电/枚举前） | 🔴 **红呼吸** 3s 三角，峰 25% |
| 与电脑建立通讯（OS 认卷/读写活动） | 🟢 **绿呼吸** 3s 三角，峰 50% |
| 写入 UF2 中 | 🔵 **蓝 10Hz 快闪**（50/50ms，清晰可辨，别拔） |
| 写入完成 | 🌈 **全彩闪烁 1.2s**（150ms 亮/灭 ×4）→ 自动进 APP（APP 无效则回红等待） |
| BLE OTA | 广播中=🔴 红、已连接=🟢 绿（绿=有通讯，与 UF2 一致） |

亮度依据：REGOUT0=3.3V、限流 1kΩ → 红峰值电流 ~1.1mA、绿/蓝 ~0.2mA（红电气为绿蓝 4-5 倍），故红峰压到 25%、绿峰给到 50%，两态观感才平衡。

## 本仓加固（Receiver 断电必进 BL 修复）

修复「接收器断电后每次上电都进 BL 而非 APP、须重刷 UF2」的问题，四重防护：

1. **早清 RESETREAS**：启动早期快照并清除复位原因寄存器（W1C），杜绝残留 RESETPIN 位被后续误判。
2. **按键去抖 + 仅信引脚复位**：DFU 按键（P0.03）只在「本次为引脚复位」时经多次采样去抖后才采信——USB 插入的上电毛刺不再被当成「按住进 DFU」。
3. **兜底超时**：存在有效 APP 时，按键/双击进入的 DFU 也有 60s 无 USB 枚举则自动跳 APP 的超时，误触发可自愈（全新无 APP 的板仍无限等待刷机）。
4. **写完全彩闪烁 1.2s**：UF2 写完且 APP 有效时，以完成时刻为起点全彩同亮同灭闪 4 次（150ms 亮/灭，1.2s）再进 APP——"刷好了"的可见反馈。

> 改动后 deliberate 进 DFU 的手势仍可用：按住按键再点按复位、或双击复位。

## 编译

GNU Make + `arm-none-eabi-gcc`（13.x），需先 `git submodule update --init`：

```bash
rm -rf _build/build-*                            # BL 改动后须干净重编
make BOARD=nini_nrf52833 all -j$(nproc) -k       # 追踪器；接收器用 nini_nrf52833_rx
# 产物：_build/build-<板>/ 下 3 个 hex（bare / nosd / s140_7.3.0）与对应 update-*.uf2
# 注：nrfutil zip 报 Error 127 为已知无害（BLE 升级包恒缺），加 -k 让 UF2 目标照常生成
```

---

本仓基于 [jitingcn/Adafruit\_nRF52\_Bootloader](https://github.com/jitingcn/Adafruit_nRF52_Bootloader)（其上源自 [adafruit/Adafruit\_nRF52\_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)）维护。
Adafruit 原版文档（官方板卡清单、nrfutil DFU 说明等）与本项目无关，完整内容请见上游仓库；许可沿袭上游（见仓库 `LICENSE`）。
