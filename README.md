# 有机物同分异构体计算

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](http://choosealicense.com/licenses/mit/)

## 仓库简介

本仓库为南开大学 C++ 程序设计基础（上）课程大作业。目标是提供分子式较为简单的有机化合物（单取代烃、烷烃、单烯烃等）同分异构体列举以及数目的计算。

## 安装及调试

### 安装步骤（自行从源码安装）

安装条件：需有配置好的 VC、GCC 等 C/C++ 编译器。在命令提示符 cmd（或终端）中利用 `cd` 命令进入当前目录（有 setup.py 文件的部分）进行操作。

1. **仅构建**：使用命令 `python setup.py build` （或 `python3`）构建成链接库（.so、.dll 等），与需调用的 .py 文件放一起即可使用。
2. **直接安装**：使用 `python setup.py install` 直接安装，则无需在同一目录下即可导入。注意安装时开启权限（Windows 下使用管理员权限打开 cmd，Linux、MacOS 加 sudo 等）。
3. **使用包管理器 pip 等安装**：使用 `python setup.py bdist_wheel` 打包成 `.whl` 文件，并在生成的 `dist` 文件夹中使用 `pip install name`，name 为生成的文件名。

完成后可双击 test.py 文件（或使用命令行）测试是否调用成功。

### 安装步骤（从包安装）

仓库提供了某些 Python 版本的 wheel 文件，找到对应的 Python 版本与操作系统版本，下载后使用 pip 等安装。如果版本不对应，则需自行编译安装。

### 导入方法

库名为 isomerNum，由两个子模块 listAll、quickCount 组成，可以使用

`from isomerNum import quickCount`  
`from isomerNum import listAll`

导入。可供调用的具体函数如下：

1. quickCount.alkyl(int number-of-carbon) # 烷基（单取代烃），返回值为具体数值
2. quickCount.alkane(int number-of-carbon) # 烷烃，返回值为具体数值
3. quickCount.monoAlkene(int number-of-carbon) # 一个键标记的烷（烯、炔、醚），返回值为具体数值
4. quickCount.cycloAlk(int number-of-carbon) # 单环烷烷烃，返回值为具体数值
4. listAll.lsAlkene(int number-of-carbon, str name-of-substituent) # 烷基（单取代烃），返回值为 SMILES 字符串列表
5. listAll.lsMonosub(int number-of-carbon, str name-of-substituent) # 一个键标记的烷（烯、炔、醚），返回值为 SMILES 字符串列表

## C++ Python 库 isomerNum 部分架构

### ln_listAll.cpp / ln_quickCount.cpp

与 Python 交互的部分，定义了子模块 listAll、quickCount 中的函数与完全用 C++ 写的函数间的关系，如何调用及实现。

### listAll.cpp / listAll.h

listAll 中所有函数函数对应的代码部分。

### quickCount.cpp / quickCount.h

quickCount 中所有函数函数对应的代码部分。

## Python 展示界面部分架构

根据输入的分子式及所需条件展示，可以用来进行 isomerNum 库的调试。使用 RDKit 库将 SMILES 结构式转化为图形。

## 需要改进的部分

1. 利用 mySQL 等数据库录入已计算的数据，实现运算的加速；
2. 利用波利亚计数定理等实现算法的优化；
3. 提供更多种类化合物同分异构题的计算及展示；
4. 考虑立体异构（旋光异构及几何异构）；
5. 利用大数计算实现更多碳数时的计算。

*TODO:* 列举时烷基的深度属性 `depth` 可以用来快速判断烷烃是否重复。

## 贡献者

1. Python 界面展示：**蒙洋**
2. listAll 和 quickCount 除了环烷烃的部分及链接库接口维护：**曹博涵**
3. quickCount 环烷烃的部分：**江柔**
4. 说明文档（论文）：**何晴雨**

