from isomerNum import quickCount
from isomerNum import listAll
n = int(input("请输入碳的个数："))
w = str(input("请输入取代基或键的名称："))

print("\n测试列出一个键标记的烃...")
try:
    print(listAll.lsAlkene(n,w))
except:
    print("调用失败！")
else:
    print("调用成功！")

print("\n测试列出单取代烃...")
try:
    print(listAll.lsMonosub(n,w))
except:
    print("调用失败！")
else:
    print("调用成功！")
    
print("\n测试计算单取代烃...")
try:
    print(quickCount.alkyl(n))
except:
    print("调用失败！")
else:
    print("调用成功！")

print("\n测试计算一个键标记的烃...")
try:
    print(quickCount.monoAlkene(n))
except:
    print("调用失败！")
else:
    print("调用成功！")

print("\n测试计算烷烃...")
try:
    print(quickCount.alkane(n))
except:
    print("调用失败！")
else:
    print("调用成功！")
    
print("\n测试计算环烷烃...")
try:
    print(quickCount.cycloAlk(n))
except:
    print("调用失败！")
else:
    print("调用成功！")

input("\n可以对比数组个数与计算数据是否一致以检验正确性...\n\n按回车继续...")
