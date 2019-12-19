
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int  length;
int input_data[] = { 4,2,3,4,5,6,7,8 };
const int Digit[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int danwei[8] = { 0 , 0 , 10, 100, 1000, 10000, 100000, 1010 };

int  data_buf[12] = { 0 };
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
	while (pStart <= pEnd && *pStart != 0)
	{
		if ((data_length == 2 && *pStart == 1) || (data_length == 6 && *pStart == 1)){   // 处理读整10,10万的问题
			printf("ggggggg");
			data_buf[data_indexs++] = danwei[index];
			data_length = 0;  // 长度清0
		}
		else
		{
			if (data_length == 0 || data_length != 2 || data_length != 6){
				data_buf[data_indexs++] = Digit[*pStart];
				printf("打印输入的非零数值：%d\n", Digit[*pStart]);
			}
			data_buf[data_indexs++] = danwei[index];
			data_length = 0;  // 长度清0
		}
		++pStart;
		--index;
		if (pStart > pEnd){
			return;
		}
	}
	printf("打印输入的非零最后的数值：%d\n", data_buf[data_indexs]);
	// 设置标记。确定是否应该输出‘零’
	int flag = 0;
	while (pStart <= pEnd && *pStart == 0){
		++pStart;
		--index;
		flag = 1;
		printf("进入中间0判断:%d\n",flag);
	}
	if (flag == 1 && pStart <= pEnd){ // <=
		data_buf[data_indexs++] = Digit[0];// Digit[*pStart - '0'];
		printf("打印输入的零数值：%d\n", data_buf[data_indexs]);
	}
	// 打印最后面的转换后的字符串序列。此时pStart，要么到达非零的十位，要么直接到达了个位
	while (pStart <= pEnd && *pStart != 0)// 4位中中间有0才处理
	{
		printf("打印输出最终数值：%d\n", data_buf[data_indexs]);
		data_buf[data_indexs++] = Digit[*pStart];
		data_buf[data_indexs++] = danwei[index];
		++pStart;
		--index;
		if (pStart > pEnd){
			return;
		}
	}
}

void digitToChinese(int *pStr, int number_length)
{
	memset(data_buf, 0, sizeof(data_buf));
	data_indexs = 0;

	if (!pStr)
		return;
	data_length = number_length;

	// 处理中间四位
	if (number_length > 4)
	{
		printGroupOf4(pStr, pStr + number_length - 5);
		if (*(pStr+number_length - 5) != 0){ // 将后面的0消除
			data_indexs--;     
		}
		
		data_buf[data_indexs++] = danwei[5];
		if (*(pStr + number_length - 4) == 0){																						// 千位为0
			if ((*(pStr + number_length - 3) != 0) || (*(pStr + number_length - 2) != 0) || (*(pStr + number_length - 1) != 0)){ // 百，十，个其中有一个不为零，输出中间的零值
				data_buf[data_indexs++] = Digit[0];
			}
		}
		else if (number_length >5){							// 十万以上,而且万位为0，然后期间添加0
			if (*(pStr + number_length - 5) == 0){
				data_buf[data_indexs++] = Digit[0];
			}
		}
		pStr = pStr + number_length - 4;
		number_length = 4;
	}

	// 处理最后四位
	printGroupOf4(pStr, pStr + number_length - 1);
	//	data_buf[data_indexs++] = danwei[7];			      // 输出元
	if (*(pStr+number_length - 1) != 0){
		data_indexs--;                                        // 将后面的0消除
	}
	int i = 0;
	for (i = 0; i < data_indexs; i++){
		printf("%d\n", data_buf[i]);
	}
	printf("\n");
	printf("最终数据长度：%d",data_indexs);
	printf("\n");
	printf("\n");
}


int main(void)
{
	//char p[20];
	length = sizeof(input_data) / 4;
	printf("输出数据的长度：%d\n",length);
/*	int i;
	for (i = 0; i < 10; i++){
		if (scanf("%d", &input_data[i])<0);
		length++;
		break;
	}
	printf("输出数据的长度：%d\n", length);
	*/
	digitToChinese(input_data,length);

	/*
	while (1)
	{
	//	printf("请输入小于12位的数字：");
		//	cout << "请输入小于12位的数字：" << endl;
	//	scanf("%s",p);
		//cin >> p;
	//	digitToChinese(p);
	}
	*/
	return 0;
}afdfffdaf