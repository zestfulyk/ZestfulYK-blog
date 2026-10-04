---
title: bash笔记--查找函数用法
date: 2026-10-04 11:20:03
tags: bash
---
# 使用bash查找函数用法

因为在编程时,显然会用到很多函数,这个时候我们就需要知道怎么快速查找到需要的函数用法

那么接下来我以查找`OpenCV`中的`namedWindow`来带大家操作一遍
# 进入文件夹

这个大家应该还算熟悉了,用法就是`cd`+文件夹名称

所以我们先进入opencv的源代码文件夹:

```bash
cd /d/opevcv/sources
```

>我放在D:盘了,操作时请根据实际修改路径
# 定位文件

## grep

**`grep`** 是 Linux/macOS 下最强大的文本搜索工具（Global Regular Expression Print）。它用于在文件中查找匹配特定模式的文本行

用法:

```bash
grep "查询内容" * -R
```

在bash中,`*`表示所有,我们在命令的最后加上`*`可以强制要求包含目录下的全部文件

**`-R`**（大写R，代表 Recursive）是**递归搜索**。告诉 `grep` 不仅要搜索当前目录，还要深入所有子目录（如 `modules/`, `apps/`, `doc/` 等）去查找

这样我们就能查找到所有信息了

然后查询:

```bash
grep "namedWindow(" * -R
```

但是发现得到很长一段内容

我们要查询的是用法,那么在大一我们学过,这种会放在hpp文件中,所以我们需要筛选hpp文件

那么怎么才能筛选出hpp文件呢?

输入

```bash
grep --help
```

来获取帮助

我们得到:

```bash
 -R, --dereference-recursive  likewise, but follow all symlinks
      --include=FILE_PATTERN  search only files that match FILE_PATTERN
      --exclude=FILE_PATTERN  skip files and directories matching FILE_PATTERN
      --exclude-from=FILE   skip files matching any file pattern from FILE
      --exclude-dir=PATTERN  directories that match PATTERN will be skipped.

```

这说明,我们可以通过include来限定hpp文件

前面提到过`*`表示全部,所以我们把include的关键词设置为`*.hpp`就可以了

因此我们再输入:

```bash
grep --include="*.h" "namedWindow(" -R *
```

> bash的指令要求是可以叠加的,无需在意顺序,反正参数往后面叠就行了

然后我们得到:

```bash
$ grep --include="*.hpp" "namedWindow" -R *
modules/core/include/opencv2/core/opengl.hpp:do this with namedWindow function or with other OpenGL toolkit (GLUT, for example).
modules/highgui/include/opencv2/highgui.hpp:        cv::namedWindow(windowName); // not required
modules/highgui/include/opencv2/highgui.hpp://! Flags for cv::namedWindow
modules/highgui/include/opencv2/highgui.hpp:The function namedWindow creates a window that can be used as a placeholder for images and
modules/highgui/include/opencv2/highgui.hpp:CV_EXPORTS_W void namedWindow(const String& winname, int flags = WINDOW_AUTOSIZE);
modules/highgui/include/opencv2/highgui.hpp:If you need to show an image that is bigger than the screen resolution, you will need to call namedWindow("", WINDOW_NORMAL) before the imshow.
modules/highgui/src/backend.hpp:    // namedWindow
modules/highgui/src/window_framebuffer.hpp:    // namedWindow
modules/highgui/src/window_winrt_bridge.hpp:    CvWindow*           namedWindow(cv::String name);
```

可以看出,我们需要的关键信息再highgui.cpp里面
# 打开对应文件

我们先进入这个文件夹

```bash
cd ./modules/highgui/include/opencv2/
```

接下来使用less指令打开这个文件并进行查找

> `less` 是 Linux/Git Bash 中最强大的文本查看器。它不会修改文件，而且支持高亮搜索。

```bash
less highgui.hpp
```

查找方式也很简单,输入`/`+关键字就行了

```bash
/namedWindow
```

最终,我们查找到用法:

```cpp
//! Flags for cv::namedWindow
enum WindowFlags {
       WINDOW_NORMAL     = 0x00000000, //!< the user can resize the window (no constraint) / also use to switch a fullscreen window to a normal size.
       WINDOW_AUTOSIZE   = 0x00000001, //!< the user cannot resize the window, the size is constrainted by the image displayed.
       WINDOW_OPENGL     = 0x00001000, //!< window with opengl support.

       WINDOW_FULLSCREEN = 1,          //!< change the window to fullscreen.
       WINDOW_FREERATIO  = 0x00000100, //!< the image expends as much as it can (no ratio constraint).
       WINDOW_KEEPRATIO  = 0x00000000, //!< the ratio of the image is respected.
       WINDOW_GUI_EXPANDED=0x00000000, //!< status bar and tool bar
       WINDOW_GUI_NORMAL = 0x00000010, //!< old fashious way
    };
```

退出输入`q`就可以(qiut的缩写)