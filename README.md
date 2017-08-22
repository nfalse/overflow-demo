# stack-overflow-demo
这是一个阐述栈溢出原理的测试程序
# 原理说明
作者很懒，还没有阐述原理。
# 代码说明
代码执行顺序:
	main -> funcA -> funcB -> exit；
	
1、funcA为系统正常调用函数；

2、由于strcpy以'\0'结束符号，str的长度大于tmp，所以tmp会溢出；

3、因为溢出部分使用了funcB的地址，所以funcB的地址覆盖了funcA的返回地址，在funcA执行结束后继续执行funcB；

	注意: x64操作系统的地址空间是 8 bytes
# 程序测试
$gcc -o overflow overflow.c

启动程序:

$./overflow

运行结果：

 正常代码调用

 恶意代码被调用

