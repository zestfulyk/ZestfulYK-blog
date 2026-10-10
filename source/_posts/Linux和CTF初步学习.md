---
title: Linux和CTF初步学习
date: 2026-10-11 00:02:13
tags: 技术
---
# 环境

显然我是不可能给我的电脑搞双系统的,因为我不会,所以我是用windows的wsl下载了一个Ubuntu来使用


# 如何启动

打开`cmd`或者`powershell`,输入`wsl`就行了

```cmd
wsl
```

# Linux的文件结构

有根树,绝对路径必须是从`/`,也就是根节点出发来访问

如果你插入了一个U盘,那么必须要先连接这两颗树,把U盘挂在一个节点下面,相当于把自己的路径入口提供给系统访问,这个过程称之为**挂载**

Windows系统类似于森林,只要换一个树根就行

>Windows 常见是多盘符根，像多棵树；Linux 是单根树，根是 `/`。挂载就是把另一个文件系统的根“嫁接”到 Linux 目录树的某个目录上，作为入口。挂载后整体仍然是一棵以 `/` 为根的树，通过挂载点路径就能访问另一个文件系统

注意,挂载只是提供入口,但是不会把所有信息复制过来

比如,要用Linux访问Windows的内容,需要把盘挂载在这棵树上面,以贴合Linux的访问逻辑

# Windows中的WSL

按照我的理解,相当于一个电脑中同时运行了两个不同操作系统的电脑,然后通过电脑内部的本地局域网连接,从而实现访问

这样做,可以最大限度的保持Linux和Windows的内容

打开一个资源管理器,输入

```cmd
\\wsl$
```

你会发现进入了网络文件夹,里面就有你通过WSL下载的Ubuntu

里面的mnt(mount),就是挂载的地方,打开这个文件夹,你会看到一个名为c的文件夹,这个就是c盘的入口了,这就是挂载的意义

# 常规命令学习

## `pwd`

这个可以用于查看我在哪里

比如:

```powershell
zyk@0x7ffff:~$ pwd
/home/zyk
```

`~`表示的是家目录

相当于 Windows 里的 `C:\Users\你的用户名`(也就是你的“用户文件夹”或“我的文档”所在的地方)
在你的 Ubuntu 里,这个家目录就是你个人的专属空间

## echo

打印对应路径的绝对路径

```
zyk@0x7ffff:/$ echo ~
/home/zyk
```

## ls

list的缩写,就是列举当前文件夹下都有什么

```PowerShell
zyk@0x7ffff:/$ ls
bin   dev  home  lib    lost+found  mnt  proc  run   snap  sys  usr
boot  etc  init  lib64  media       opt  root  sbin  srv   tmp  var
```

## cp

复制文件,比如你需要用一些Linux的命令或者工具,那么就需要把文件从你的Windows转移到Ubuntu

举个例子,我要把我D盘中的一张图片复制到Ubuntu

```PowerShell
zyk@0x7ffff:/$ cd /mnt/d
zyk@0x7ffff:/mnt/d$ cd ctf
zyk@0x7ffff:/mnt/d/ctf$ ls
QR_code.png
zyk@0x7ffff:/mnt/d/ctf$ cp QR_code.png ~/
zyk@0x7ffff:/mnt/d/ctf$ cd ~
zyk@0x7ffff:~$ ls
QR_code.png
```

# 工具

## `binwalk`

用于扫描一个文件是否藏有其他东西,并且可以提取相关内容

### 用法

```PowerShell
binwalk -e 1.png
```
## `fcrackzip`

暴力破解zip压缩包密码的工具
### 常用参数

- `-b`或`--brute-force`:使用暴力破解算法
- `-D`或`--dictionary`:使用字典文件进行破解
- `-c`或`--charset`:指定用于破解的字符集,例如 `-c 'aA1!'`
- `-l`或`--length`:指定密码的长度范围,如 `-l 1-10`
- `-u`或`--use-unzip`:使用unzip命令来验证密码是否正确。

### 示例

使用暴力破解方法，指定字符集和密码长度来破解ZIP文件:

```PowerShell
fcrackzip -b -c 'aA1' -l 1-10 -u myzipfile.zip
```

使用字典文件来破解ZIP文件:

```PowerShell
fcrackzip -D -p mydictionary.txt -u myzipfile.zip
```

在这里,`-D` 表示使用字典文件,`-p`后面跟着字典文件的路径

## 示例1

```PowerShell
zyk@0x7ffff:~/_QR_code.png.extracted$ ls
1D7.zip
zyk@0x7ffff:~/_QR_code.png.extracted$ fcrackzip -b -c '1' -l 1-4 -u 1D7.zip
PASSWORD FOUND!!!!: pw == 7639
zyk@0x7ffff:~/_QR_code.png.extracted$ unzip -P 7639 1D7.zip
Archive:  1D7.zip
  inflating: 4number.txt
zyk@0x7ffff:~/_QR_code.png.extracted$ cat 4number.txt
CTF{vjpw_wnoei}
zyk@0x7ffff:~/_QR_code.png.extracted$
```

