[![build uxplay-windows](https://github.com/FoolishWiser/uxplay-windows-zh/actions/workflows/build-uxplay-windows.yml/badge.svg)](https://github.com/FoolishWiser/uxplay-windows-zh/actions/workflows/build-uxplay-windows.yml)

# 把 AirPlay 免费投到你的 Windows 电脑

"免费"既指**自由**，也指**免费啤酒**。

> [!NOTE]
> **关于本仓库（汉化版）**
>
> 本仓库是 [leapbtw/uxplay-windows](https://github.com/leapbtw/uxplay-windows) 的**汉化分支**，
> 代码基线跟随上游 `multi-arch` 分支（UxPlay 1.73.7），只做中文本地化，不改变原有功能与构建方式。
>
> 已汉化的部分：
> - 主窗口、托盘菜单、状态提示、确认/警告对话框
> - "当前日志"查看窗口
> - 安装包（MSI）的界面语言与快捷方式说明
> - UxPlay 参数说明（主界面上的"查看 UxPlay 参数说明"按钮）
> - 界面字体自动选用系统中文字体（微软雅黑 / 黑体），避免出现方块字
>
> 英文原文：[README.en.md](./README.en.md)。
> 上游更新后，可按[文末](#与上游同步)的方式合并，汉化内容集中在少数源文件中，冲突范围很小。

## 安装

从 [**Releases**](https://github.com/leapbtw/uxplay-windows/releases/latest) 下载原版安装包即可直接使用；
本汉化仓库的构建产物在 [Actions](https://github.com/FoolishWiser/uxplay-windows-zh/actions/workflows/build-uxplay-windows.yml)
里（每次推送到 `main` 会自动构建 x64 / ARM64 的便携 ZIP 与 MSI 安装包，下载 artifact 即可）。

安装完成后，请通过[系统托盘图标](https://www.odu.edu/sites/default/files/documents/win10-system-tray.pdf)控制 uxplay-windows：
右键托盘图标即可启动或停止 AirPlay。你也可以勾选"开机自动启动 uxplay-windows"。

## 自定义设备名称

默认情况下，设备在网络上显示为 `uxplay-windows`。想改成别的名字（例如"客厅的电脑"）：

1. 打开程序，点击"**编辑 UxPlay 启动参数（高级）**"，系统会用默认编辑器打开 `arguments.txt`；
2. 把其中 `-n uxplay-windows -nh` 改成 `-n 你的设备名 -nh`，例如 `-n 客厅的电脑 -nh`；
3. 保存后重启程序（右键托盘图标 → 重启），新名称即会生效。

## 常见问题（FAQ）

> [!IMPORTANT]
> **安装时 Windows Defender 为什么会报警？**
>
> ![defender](https://raw.githubusercontent.com/leapbtw/uxplay-windows/refs/heads/x64/stuff/defender.png)
>
> 点击 `更多信息` → `仍要运行` 即可继续安装。报警的原因是可执行文件没有代码签名。
> 如果你不信任这个软件，也可以按下面的说明自行构建。
>
> 如果 Windows 防火墙弹出提示，请**允许** uxplay-windows 通过，否则功能会受影响。

> [!TIP]
> **我的 iPhone / iPad / Mac 连不上电脑！**
>
> 1. 确认 `uxplay-windows.exe` 正在运行：右键托盘图标把它重启一次；
> 2. 在 iPhone/iPad/Mac 上关掉 Wi-Fi 和蓝牙，等几秒再重新打开并重连，可能需要多试几次；
> 3. 最后的手段：关闭 uxplay-windows，打开"任务管理器"→"服务"选项卡，重启 `Bonjour Service`，
>    然后重新打开 uxplay-windows 再试。

更多内容（排障、Wiki）请见上游的 [Wiki](https://github.com/leapbtw/uxplay-windows/wiki)。

## 高级配置

UxPlay 的启动参数从 `arguments.txt` 读取，优先级如下：

1. `%ProgramData%\uxplay-windows\arguments.txt`
2. `%APPDATA%\leapbtw\uxplay-windows\arguments.txt`
3. 内置默认值：`-n uxplay-windows -nh`

机器级文件存在时优先生效，方便管理员统一下发配置；不存在时，每个用户可以在 `%APPDATA%` 下维护自己的配置。

程序启动时会展开环境变量，例如：

```text
-n %COMPUTERNAME% -nh
```

完整的参数说明可以在程序主界面点"**查看 UxPlay 参数说明**"查看（汉化版已翻译）。

## 从源码构建

x64 与 ARM64 的构建由**一个** GitHub Actions 工作流全自动完成：

1. Fork 本仓库（或直接使用本仓库）；
2. 打开 **Actions** 标签页；
3. 选择 **build uxplay-windows** 并运行；
4. 下载 `uxplay-windows-x64` 或 `uxplay-windows-arm64`。

本地构建见 [BUILDING.md](./docs/BUILDING.md) 与 [DEVELOPERS-GUIDE.md](./docs/DEVELOPERS-GUIDE.md)。

## 与上游同步

```bash
git remote add upstream https://github.com/leapbtw/uxplay-windows.git   # 只需一次
git fetch upstream
git checkout main
git merge upstream/multi-arch     # 汉化改动集中在 src/*.cpp、product.wxs、stuff/、README 等少数文件
```

## 已知问题

- 有时刚把 iPhone 连上 uxplay-windows，画面会立刻卡住，断开后重连一次即可恢复；
  这大概率是上游 UxPlay 的问题，新版本中可能已修复。
- ~~电脑从睡眠唤醒后 uxplay 会异常~~：改用 mDNSResponder 之后该问题似乎已消失。

## 反馈问题

构建系统（GitHub Actions）相关的问题请在本仓库提；软件本身的问题请提到上游
[leapbtw/uxplay-windows](https://github.com/leapbtw/uxplay-windows) 或 [FDH2/UxPlay](https://github.com/FDH2/UxPlay/issues)。

## 许可证

请查看 [LICENSE](./docs/LICENSE.rtf)。
