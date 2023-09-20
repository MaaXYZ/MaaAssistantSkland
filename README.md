<div align="center">

<img alt="LOGO" src="https://cdn.jsdelivr.net/gh/MaaAssistantArknights/design@main/logo/maa-logo_512x512.png" width="256" height="256" />

# MaaAssistantSkland

MAS 是指 Maa Assistant Skland

基于MAA全新架构的 森空岛 小助手

图像技术 + 模拟控制，解放双手！

由 [MaaFramework](https://github.com/MaaAssistantArknights/MaaFramework) 强力驱动！

</div>

## 适配情况

目前仅适配了 `1280x720 320dpi` 和 `1920x1080 480dpi` 分辨率，其他分辨率尚待测试

## How to use

> 1. [下载](https://github.com/MaaAssistantArknights/MaaAssistantSkland/releases) 对应平台的压缩包
> 2. 将压缩包解压到没有中文的目录下

### 基本说明

1. 请根据 [模拟器支持情况](https://maa.plus/docs/1.3-模拟器支持.html)，进行对应的操作。
2. 按照 [适配情况](#适配情况) 修改模拟器分辨率，一般在模拟器`设置`-`显示`中进行修改。

### 直接使用 

> 以 Windows 用户为主，其他系统请照葫芦画瓢。

1. 首次使用，双击打开 `MAS_CLI.exe` 或 通过 CMD 执行 `MAS_CLI.exe`
2. 等待扫描设备（设备越多等待时间越长）
3. 选择需要连接的设备
4. 开始使用吧！

   - 后续使用除非需要连接的设备不存在，否则无需再次选择设备

### 作为MAA结束后脚本使用

> 以 Windows 用户为主，其他系统请照葫芦画瓢。

1. 先按照 [直接使用](#直接使用) 进行操作
2. 在MAA目录下新建一个文本文件，在其中填入以下内容

    ```bat
    @echo off
    cd D:/Software/MAS
    MAS_CLI.exe
    ```

   - 注意：`D:/Software/MAS` 请替换成你自己的 MAS 目录

3. 将文本文件重命名为 `finish.bat`

    - 如果重命名后没有弹出修改扩展名的二次确认对话框，且文件图标没有变化，请自行搜索“Windows如何显示文件扩展名”。

4. 在MAA `设置`-`游戏设置`-`结束后脚本` 中填入 `finish.bat`
5. 开始使用吧！


## How to build

**如果你要编译源码才看这节，否则直接 [下载](https://github.com/MaaAssistantArknights/MaaAssistantSkland/releases) 即可**

_欢迎大佬们来带带~_

1. 下载 MaaFramework 的 [Release 包](https://github.com/MaaAssistantArknights/MaaFramework/releases)，解压到 `deps` 文件夹中
2. 配置 cmake

    - Windows  

    ```bash
    cmake --preset "MSVC 2022"
    ```

    - Linux / macOS

    ```bash
    cmake --preset "NinjaMulti"
    ```

3. 使用 cmake 构建工程  

    ```bash
    cmake --build build --config Release
    cmake --install build --prefix install
    ```

    生成的二进制及相关资源文件在 `install` 目录下

## 开发相关

- `tools/CropRoi` 可以用来裁剪图片和获取 ROI
- Pipeline 协议请参考 [MaaFramework 的文档](https://github.com/MaaAssistantArknights/MaaFramework/blob/main/docs/zh_cn/3.3-%E4%BB%BB%E5%8A%A1%E6%B5%81%E6%B0%B4%E7%BA%BF%E5%8D%8F%E8%AE%AE.md)

## Join us

用户交流 QQ 群：[MAA 使用 & 粥游交流 QQ 群](https://ota.maa.plus/MaaAssistantArknights/api/qqgroup/index.html)<br>
技术 & 吹水群（舟无关）：[内卷地狱！(QQ 群)](https://jq.qq.com/?_wv=1027&k=ypbzXcA2)<br>
