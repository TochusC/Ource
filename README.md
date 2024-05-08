<div align="center">

<img src="docs/img/logo.png" style="margin-bottom: 0; height: 64%; width: 64%;">

<h1 style="margin-top: 0"> Ourse </h1>

### 可能是最最简陋的操作系统

[![version](https://img.shields.io/badge/Version-0.0.1-blue)](https://github.com/TochusC/ource)
[![course](https://img.shields.io/badge/UPC-OperatingSystem-blue)](https://www.upc.edu.cn/)

[![madewithlove](https://img.shields.io/badge/made_with-%E2%9D%A4-red?style=for-the-badge&labelColor=orange)](https://github.com/TochusC)


[**简体中文**](./README.md) 


[中国石油大学(华东)](https://upc.edu.cn/)-操作系统结课作业

</div>


![img.png](docs/img/001.png)

---
<div align="center">

### 仍在火热施工中🔨...


Ource操作系统参考自川合秀实编著，周自恒翻译的[30天自制操作系统](https://viterbi-web.usc.edu/~yudewei/main/sources/books/30%E5%A4%A9%E8%87%AA%E5%88%B6%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/)中的Haribote（纸娃娃）系统编写，所参考的中文源码来自[
yourtion的git仓库](https://github.com/yourtion/30dayMakeOS)。

感谢书籍编写者、译者、中文源码分享者的贡献！

</div>

## 项目结构📁
```angular2html
docs  # README相关文件
├── img 

projects  #《30天自制操作系统》的中文源码

release  # 发布版本
├──ource.iso # 发布的镜像文件（可用VMware Workstation等虚拟机软件运行）
├──ource.img # 发布的软盘镜像文件

tolset # 《30天自制操作系统》的工具集
├── ource_core # 操作系统核心代码
├── others # 其他工具


```


## 目前进度🚀


### 处理器管理

Ource OS是一个多任务操作系统，其通过**多级优先队列调度算法**实现任务的调度，采用**时间片轮转**的方式进行任务切换。
具有高优先级的任务将会被分配到更多的时间片，以保证其能够更快地完成任务。

### 内存管理

Ource OS采用**分段存储管理**的方式进行内存管理，将操作系统和应用程序分配在具有不同权限的段中，以便于管理和分配。

### 设备管理
Ource OS支持**键盘输入**，并通过**中断**的方式进行设备管理。

### 文件管理
Ource OS采用**FAT12**文件系统进行文件管理，目前仅支持文件的读取等操作。

### 支持的系统调用
- `api_putchar` 输出字符
- `api_putstr0` 输出字符串

## 如何运行❓
`release`文件夹中提供了`ource.iso`镜像文件，可用VMware Workstation等虚拟机软件运行。

![002.png](./docs/img/002.png)
