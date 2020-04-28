#include "a.h"

int Add(int left, int right)
{
	return left + right;
}

/*
函数模板编译：
 1. 在实例化前--只是对函数模板进行简单的语法检测
 2. 在实例化时--
*/
//template<class T>
//T Sub(const T& left, const T& right)
//{
//	return left - right;
//}
//
//void TestFunc()
//{
//	Sub(1, 2);  // 对实参类型进行推演，根据推演结果生成处理具体类型的代码，Sub<int>
//	Sub(1.0, 2.0); // Sub<double>
//	//Sub('a', 'b');
//}