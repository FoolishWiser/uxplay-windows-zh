# 免费 AirPlay 到你的 Windows PC
“免费”既指自由，也指免费啤酒！

> [!NOTE]
> *关于此版本*
>
> 本仓库是 `uxplay-windows` 的 **二创分支（二次创作版本）**，在原版基础上增加了以下特性：
> - **界面汉化** – 所有用户界面文本均已完全中文化，为中文用户提供更友好的操作体验。
> - **SMTC 支持** – 集成了 Windows 系统媒体传输控制（System Media Transport Controls），你可以在任务栏媒体控件或系统弹出的媒体控制面板中查看当前播放内容，并直接进行播放/暂停、上一首/下一首等控制。

## 安装
从 [**Releases**](https://github.com/leapbtw/uxplay-windows/releases/latest) 下载最新版本的 uxplay-windows。

安装后，通过其[系统托盘图标](https://www.odu.edu/sites/default/files/documents/win10-system-tray.pdf)控制 uxplay-windows！右键单击即可启动或停止 AirPlay。  
你还可以将其设置为开机自启动。

## 自定义设备名称
默认情况下，程序在网络上显示的名称为 `uxplay-windows`（与原版一致）。如果你希望自定义名称，请按照以下步骤操作：
1. 打开程序，点击「编辑 UxPlay 参数（高级）」按钮，系统将打开 `arguments.txt` 文件。
2. 在文件中找到 `-n uxplay-windows -nh`，将其修改为 `-n 你的名称 -nh`（例如 `-n ZYT的Windows -nh`）。
3. 保存文件并重启程序，新名称即生效。

## 常见问题 — 请阅读！
> [!NOTE]
> *什么是 uxplay-windows？*
>
> [uxplay-windows](.) 是一款允许你通过 AirPlay 将视频流传输到 Windows PC 的软件。  
> 它将 [UxPlay](https://github.com/FDH2/UxPlay/) 转变为一款功能完整的 Windows 10/11 应用程序，让那些可能觉得编译 UxPlay 有困难的人使用起来更加方便。
>
> 大多数其他实现与 `uxplay-windows` 相同功能的软件通常是付费且非自由的。


> [!TIP]
> *我的 \<Apple 设备\> 无法连接到我的 PC！！！*
> 1. 检查 `uxplay-windows.exe` 是否正在运行：右键单击系统托盘图标并重新启动它。
> 2. 在 iPhone/iPad/Mac 上关闭 Wi-Fi 和蓝牙，等待几秒钟后重新连接。可能需要尝试几次。
> 3. 作为最后的手段，关闭 uxplay-windows，打开任务管理器，在“服务”选项卡中重新启动 `Bonjour Service`。然后重新打开 uxplay-windows 并重试。

> [!IMPORTANT]
> *为什么安装时 Windows Defender 会发出警告？*
>
> ![alt text](https://raw.githubusercontent.com/leapbtw/uxplay-windows/refs/heads/main/stuff/defender.png "defender")
>
> 只需点击“更多信息”，它就会允许你安装。这是因为可执行文件未签名。如果你不信任此软件，你可以自己构建它！见下文。
>
> 如果 Windows 防火墙提示，请**允许** uxplay-windows 以确保其正常运行。


> [!NOTE]
>  *我如何自己构建此软件？*
>
> 请参阅 [BUILDING.md](./docs/BUILDING.md)

<br>

## 待办事项
- 添加更新检查器

## 已知问题
~~当 PC 从睡眠状态唤醒时，uxplay 会出错~~  
~~你可以通过终止 uxplay-windows.exe、重新启动 Bonjour Service 并重新启动 uxplay.exe 来解决此问题。另外，重启 PC 也可能解决此问题。~~  
显然，从 Bonjour PS 切换到 mDNSResponder 已经修复了这个问题？:)

## 报告问题
请在此仓库中报告与 GitHub Actions 构建系统相关的问题。对于本软件其他部分的问题，请在它们各自的仓库中报告。

## 许可证
请查看 [LICENSE](./docs/LICENSE.rtf)。
