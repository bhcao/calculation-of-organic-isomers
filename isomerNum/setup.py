'''
函数列表：
int alkyl(int)
int monoAlkene(int)
int alkane(int)
'''

from distutils.core import setup, Extension
MOD = "isomerNum"
setup(name=MOD,ext_modules=[Extension(MOD,sources=["isomerNum.c","quickCount.c","listAll.c"])])
