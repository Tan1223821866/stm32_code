
#include <stdio.h>
//#define _CRT_SECURE_NO_WARNINGS

char arrayOfDigit[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char arrayOfIndex[8] = { '0 ', '0 ', 's', 'b', 'q', 'w', 'y', 'y' };

char data_buf[18] = { 0 };
int data_indexs;
int data_length;

void printGroupOf4(int *pStart, int *pEnd)  // printGroupOf4(pStr, pStr + numberLength - 5);
{
	int index = pEnd - pStart + 1; // 确定位数,用于在数字后加入“十、百、千”

	// 过滤字符串最前面的‘0’
	while (pStart <= pEnd && *pStart == 0){
		++pStart;
		--index;
	}
	// 此时pStart可能“所处位置”与“字符串相应的形式”：千位(yxxx)、百位(0yxx)、十位(00yx)、个位(000y)，
	// 或者直接退出(0000),当中y表示非零的整数，x表示未知的整数
	while (pStart <= pEnd && *pStart !== 0)
	{
		if ((data_length == 2 && *pStart == '1') || (data_length == 6 && *pStart == '1')){   // 处理读整10,10万的问题
	//		printf("%c\t\%c\n", *pStart, *(pStart + 1));
			data_buf[data_indexs++] = arrayOfIndex[index];
			data_length = 0;  // 长度清0
		}
		else
		{
			if (data_length == 0 || data_length != 2 || data_length != 6){
				data_buf[data_indexs++] = arrayOfDigit[*pStart - '0'];
			}
			data_buf[data_indexs++] = arrayOfIndex[index];
			data_length = 0;  // 长度清0
		}
		++pStart;
		--index;
		if (pStart > pEnd){
			return;
		}
	}
	
	// 设置标记。确定是否应该输出‘零’
	int flag = 0;
	while (pStart <= pEnd && *pStart == '0'){
		++pStart;
		--index;
		flag = 1;
	}
	if (flag == 1 && pStart <= pEnd){
		data_buf[data_indexs++] = arrayOfDigit[0];// arrayOfDigit[*pStart - '0'];
	}
	// 打印最后面的转换后的字符串序列。此时pStart，要么到达非零的十位，要么直接到达了个位
	while (pStart <= pEnd && *pStart != '0')// 4位中中间有0才处理
	{
		data_buf[data_indexs++] = arrayOfDigit[*pStart - '0'];
		data_buf[data_indexs++] = arrayOfIndex[index];
		++pStart;
		--index;
		if (pStart > pEnd){
			return;
		}
	}
}


void digitToChinese(int *Pdata,int length)
{
	memset(data_buf, 0, sizeof(data_buf));
	data_indexs = 0;
	data_length = length;
		// 处理中间四位
	if (length > 4)
	{
		printGroupOf4(pStr, pStr + length - 5);
		data_buf[data_indexs++] = arrayOfIndex[5];
		if (*(pStr + length - 4) == '0'){																						// 千位为0
			if ((*(pStr + length - 3) != '0') || (*(pStr + length - 2) != '0') || (*(pStr + length - 1) != '0')){ // 百，十，个其中有一个不为零，输出中间的零值
				data_buf[data_indexs++] = arrayOfDigit[0];
			}
		}
		else if (length >5){							// 十万以上,而且万位为0，然后期间添加0
			if (*(pStr + length - 5) == '0'){
				data_buf[data_indexs++] = arrayOfDigit[0];
			}
		}
		pStr = pStr + length - 4;
		length = 4;
	}

	// 处理最后四位
	printGroupOf4(pStr, pStr + length - 1);
}




void digitToChinese(char *pStr)
{
	memset(data_buf, 0, sizeof(data_buf));
	data_indexs = 0;

	if (!pStr)
		return;

	int numberLength = strlen(pStr);
	data_length = numberLength;
	printf("输入字符的长度：%d\n", data_length);
	/*
	// 检查符号位
	if (pStr[0] == '-'){
		cout << "负";
		++pStr;
		--numberLength;
	}
	else if (pStr[0] == '+'){
		++pStr;
		--numberLength;
	}

	// 过滤字符串前面的0
	while (*pStr == '0'){
		++pStr;
		--numberLength;
		number++;
	}
	printf("%d\n", number);
	// 检查后面的数字是否合法
	for (int i = 0; i<numberLength; ++i){
		if (pStr[i] > '9' || pStr[i] < '0')
		{
			cout << "输入字符串不合法!" << endl;
			return;
			}
		}

		// 当输入为0时
		if (numberLength == 0){
		cout << arrayOfDigit[0];
		return;
	}

	if (numberLength > 12){
	//	printf("输入数字超出表示范围（千亿级）");
	cout << "输入数字超出表示范围（千亿级）" << endl;
	return;
	}
	*/
	// 处理前四位
	/*	
	if (numberLength > 8)
	{
			printGroupOf4(pStr, pStr + numberLength - 9);
			data_buf[data_indexs++] = arrayOfIndex[6];       // 亿
			//data_indexs++;
			//cout << arrayOfIndex[6];
			if (*(pStr + numberLength - 8) == '0') // 千万位为0
			if ((*(pStr + numberLength - 7) != '0') || (*(pStr + numberLength - 6) != '0') || (*(pStr + numberLength - 5) != '0')){ // 百，十，个其中有一个不为零，输出中间的零值
			data_buf[data_indexs++] = arrayOfDigit[0];
			//	data_indexs++;
			//cout << arrayOfDigit[0];
		}

		pStr = pStr + numberLength - 8;
		numberLength = 8;
	}
	*/
	// 处理中间四位
	if (numberLength > 4)
	{
		printGroupOf4(pStr, pStr + numberLength - 5);
		data_buf[data_indexs++] = arrayOfIndex[5];
		if (*(pStr + numberLength - 4) == '0'){																						// 千位为0
			if ((*(pStr + numberLength - 3) != '0') || (*(pStr + numberLength - 2) != '0') || (*(pStr + numberLength - 1) != '0')){ // 百，十，个其中有一个不为零，输出中间的零值
				data_buf[data_indexs++] = arrayOfDigit[0];
			}
		}
		else if (numberLength >5){							// 十万以上,而且万位为0，然后期间添加0
			if (*(pStr + numberLength - 5) == '0'){
				data_buf[data_indexs++] = arrayOfDigit[0];
			}
		}
		pStr = pStr + numberLength - 4;
		numberLength = 4;
	}

	// 处理最后四位
	printGroupOf4(pStr, pStr + numberLength - 1);
	data_buf[data_indexs++] = arrayOfIndex[7];			  // 输出元
	printf("%s", data_buf);
	printf("\n");
	printf("\n");
}

int main(void)
{
	char p[20];
	while (1)
	{
		printf("请输入小于12位的数字：");
		//	cout << "请输入小于12位的数字：" << endl;
				scanf("%s", p);
		//cin >> p;

		digitToChinese(p);

	}
	return 0;
}
