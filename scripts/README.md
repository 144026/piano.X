# `scripts` 目录

一些bash脚本，<font color="red">在`git-bash.exe`中运行即可</font>

## `scripts/bench`

测试`xc8`将non-reentrant函数复制一份后，额外占用的程序空间大小。

1. 请先找到MPLAB的`make`所在目录，然后写入`.mplab_makepath`文件，例如
```bash
cd scripts/bench
echo "C:\usr\Program Files (x86)\Microchip\MPLABX\v5.20\gnuBins\GnuWin32\bin" > .mplab_makepath
```

2. 确保`xc8`编译器已经加入到`PATH`环境变量中，例如:
```bash
# 检查xc8编译器是否在PATH中
echo $PATH
```

3. 在顶层目录下(包含`Makefile`的目录)，运行脚本，bench结果位于`build/bench`，例如
```bash
# bench单个文件
scripts/bench/bench.sh src/lcd.c

# 批量bench目录下的每一个文件
scripts/bench/bench-all.sh src/
```