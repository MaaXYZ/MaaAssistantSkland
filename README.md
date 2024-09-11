<div align="center">

<img alt="LOGO" src="https://cdn.jsdelivr.net/gh/MaaAssistantArknights/design@main/logo/maa-logo_512x512.png" width="256" height="256" />

# MaaAssistantSkland

![MaaFramework](https://img.shields.io/badge/MaaFramework-v1.8.9-blue)
![Pipeline](https://img.shields.io/badge/Pipeline-%23454545?logo=codecademy&logoColor=%23FFFFFF&color=%23454545)

MAS 是指 Maa Assistant Skland

基于MAA全新架构的 森空岛 小助手

图像技术 + 模拟控制，解放双手！

由 [MaaFramework](https://github.com/MaaXYZ/MaaFramework) 强力驱动！

</div>

## 适配情况

目前仅适配了 `1280x720 320dpi` 和 `1920x1080 480dpi` 分辨率，其他分辨率尚待测试

## How to use

> 1. [下载](https://github.com/MaaXYZ/MaaAssistantSkland/releases) 对应平台的压缩包
> 2. 将压缩包解压到没有中文的目录下

### 基本说明

1. 请根据 [模拟器支持情况](https://maa.plus/docs/1.3-模拟器支持.html)，进行对应的操作。
2. 按照 [适配情况](#适配情况) 修改模拟器分辨率，一般在模拟器`设置`-`显示`中进行修改。

### 直接使用 

> 以 Windows 用户为主，其他系统请照葫芦画瓢。

1. 使用前，前往[森空岛官网](https://www.skland.com/)下载森空岛APP
2. 在模拟器上安装并登录森空岛APP
3. 首次使用，打开模拟器，双击打开 `MaaPiCli.exe` 或 通过 CMD 执行 `MaaPiCli.exe`
4. 选择ADB（本教程以 `Auto detect` 为例）
4. 等待扫描设备（设备越多等待时间越长）
5. 选择需要连接的设备
6. 开始使用吧！

> 添加 `-d` 参数可跳过交互直接运行任务，如 `./MaaPiCli.exe -d`

### 作为MAA结束后脚本使用

> 以 Windows 用户为主，其他系统请照葫芦画瓢。

1. 先按照 [直接使用](#直接使用) 进行操作
2. 在MAA目录下新建一个文本文件，在其中填入以下内容

    ```bat
    @echo off
    cd D:/Software/MAS
    MaaPiCli.exe -d
    ```

    > 注意：`D:/Software/MAS` 请替换成你自己的 MAS 目录
  
    如果一天只希望执行一次，可以修改成

    ```bat
    @echo off
    cd D:/Software/MAS
    set "date_file=last_run_date.txt"
    if not exist "%date_file%" (
        MaaPiCli.exe -d
        echo %date% > "%date_file%"
        exit
    )

    set /p last_run_date=<"%date_file%"
    set "last_run_date=%last_run_date: =%"

    set current_date=%date%
    set "current_date=%current_date: =%"

    if %current_date% neq %last_run_date% (
        MaaPiCli.exe -d
        echo %current_date% > "%date_file%"
    )
    exit
    ```

    > 注意：`D:/Software/MAS` 请替换成你自己的 MAS 目录

3. 将文本文件重命名为 `finish.bat`

    > 如果重命名后没有弹出修改扩展名的二次确认对话框，且文件图标没有变化，请自行搜索“Windows如何显示文件扩展名”。

4. 在MAA `设置`-`连接设置`-`结束后脚本` 中填入 `finish.bat`
5. 开始使用吧！


## How to build

**如果你要编译源码才看这节，否则直接 [下载](https://github.com/MaaXYZ/MaaAssistantSkland/releases) 即可**

_欢迎大佬们来带带~_

0. 完整克隆本项目及子项目

    ```bash
    git clone --recursive https://github.com/MaaXYZ/MaaAssistantSkland.git
    ```

1. 下载 MaaFramework 的 [Release 包](https://github.com/MaaXYZ/MaaFramework/releases)，解压到 `deps` 文件夹中
2. 安装

    ```bash
    python install.py
    ```

    安装的二进制及相关资源文件在 `install` 目录下

## 开发相关

- `deps/tools/ImageCropper` 可以用来裁剪图片和获取 ROI
- Pipeline 协议请参考 [MaaFramework 的文档](https://github.com/MaaXYZ/MaaFramework/blob/main/docs/zh_cn/3.1-%E4%BB%BB%E5%8A%A1%E6%B5%81%E6%B0%B4%E7%BA%BF%E5%8D%8F%E8%AE%AE.md)

## Join us

用户交流 QQ 群：[MAA 使用 & 粥游交流 QQ 群](https://ota.maa.plus/MaaAssistantArknights/api/qqgroup/index.html)<br>
技术（舟无关）：[内卷地狱！(QQ 群)](https://jq.qq.com/?_wv=1027&k=ypbzXcA2)<br>
