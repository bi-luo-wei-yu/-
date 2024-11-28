/*前言:基本要求完成于11.24，因暂时没有对进阶要求的思路，故先提交一遍（反正没说不能多次提交bushi)
 关于这份程序，我深知还有许多不足：
 1.函数注释不规范
 2.因为还没学会结构体（时间戳是单拎突击的），有些内容的完成并不高效，显得臃肿
 3.多文件目前只会跨文件写函数，整体代码很长
 4.进度条纯模拟的
 ……
 如果12.8号之前有新的思路，大概率会再提交一版，并把函数注释补全
 暂时先这样吧。
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define FILENAME "test_records.txt"
#define  MAX_QUESTIONS 30 //固定题目模式
#define MAX_MINUTE 900 //固定题目模式最大时间
#define LIMIT_MINUTE 180 //固定时间模式限定时间

#define u32 uint32_t
#define i32 int32_t

//函数声明
void process_bar(void);
void fixed_problem(void);
void fixed_time(void);
i32 add_sub(void);
i32 mul_div(void);
void save_test_result(char mode[], u32 problem, double score);

int main(void)
{
	u32 choice;

	do
	{
		//显示菜单
		puts("****主菜单****");
		puts("1、固定题目数量计算用时（满分1000分）");
		puts("2、固定时间计算做题数量（满分无上限）");
		puts("3、退出");
		puts("请选择一个选项:");
		scanf_s("%"SCNu32, &choice);

		//处理用户的选择
		switch (choice) {
		case 1:
			process_bar();
			fixed_problem();
			system("cls");
			puts("游戏已经玩完，返回主菜单重新选择");
			break;
		case 2:
			process_bar();
			fixed_time();
			system("cls");
			puts("游戏已经玩完，返回主菜单重新选择");
			break;
		case 3:
			puts("感谢游玩，再见！");
			break;
		default:
			puts("无效选择，请重新选择！");
			break;
		}

	} while (choice != 3);

	system("pause");
	return 0;
}

////进度条定义
void process_bar(void) {
	system("cls");
	const u32 total_steps = 100;//进度条长度

	puts("游戏加载中，请稍后：");

	for (u32 i = 0; i <= total_steps; i++) {
		printf("\r[");

		//打印进度条的完整部分
		for (u32 j = 0; j < i; j++) {
			printf("#");
		}
		for (u32 j = i; j < total_steps; j++) {
			printf(" ");
		}

		printf("]%"PRIu32"%%", (i * 100) / total_steps);
		//实际：（已经传输的数据量/文件总大小）* %100

		fflush(stdout);//确保进度条即时显示
		Sleep(100);//模拟
	}

	system("cls");
	puts("加载完成,游戏开始！");
}

////模式
//固定题目
void fixed_problem(void) {
	//模式
	char mode[] = "fixed problem";
	u32 problem = MAX_QUESTIONS;

	u32 right;//正确答案
	u32 input;//用户输入
	u32 metering = 1;//统计有效题数
	double right_answer = 0.0;//正确题数
	double score;

	//随机数生成
	i32(*func_array[])() = { add_sub , mul_div };
	srand(time(NULL));

	//计时
	clock_t start, end;
	double time_spent;

	start = clock();
	while (metering <= MAX_QUESTIONS) {

		//正确答案
		right = func_array[rand() % 2]();

		//卫语句，无效情况跳过
		if (right == -1) {
			continue;
		}

		//输入
		scanf_s("%d", &input);
		if (right == input) {
			right_answer++;
			printf("正确\n");
		}
		else {
			printf("错误\n");
		}

		metering++;//计次

		//限时
		if ((clock() - start) / CLOCKS_PER_SEC >= MAX_MINUTE) {
			printf("时间到！");
			break;
		}
	}
	end = clock();
	time_spent = (end - start) / CLOCKS_PER_SEC;

	score = right_answer * 100.0 / MAX_QUESTIONS + (MAX_MINUTE - time_spent);
	printf("\n成绩：%.1f\n", score);

	save_test_result(mode, problem, score);
	system("pause");
}
//固定时间
void fixed_time(void) {

	//模式
	char mode[] = "fixed time";
	u32 problem = 0;//题数

	u32 right;//正确答案
	u32 input;//用户输入
	u32 metering = 0;//统计有效题数
	double right_answer = 0.0;
	double score;

	//随机数生成
	i32(*func_array[])() = { add_sub , mul_div };
	srand(time(NULL));

	//计时
	clock_t start;

	start = clock();
	while (true) {

		//正确答案
		right = func_array[rand() % 2]();

		//卫语句
		if (right == -1) {
			continue;
		}

		//输入
		problem++;
		scanf_s("%d", &input);
		if (right == input) {
			right_answer++;
			printf("正确\n");
		}
		else {
			printf("错误\n");
		}

		//限时
		if ((clock() - start) / CLOCKS_PER_SEC >= LIMIT_MINUTE) {
			printf("时间到！");
			break;
		}

	}

	score = right_answer * 100.0 / problem * right_answer;
	printf("\n成绩：%.1f\n", score);

	save_test_result(mode, problem, score);
	system("pause");
}

////计算器主程序
//加减
i32 add_sub(void) {

	//生成随机数和随机符号
	u32 number1 = rand() % (100 - 0 + 1) + 0;
	u32 number2 = rand() % (100 - 0 + 1) + 0;
	char operators[] = { '+', '-' };//四则运算符定义
	char operator = operators[rand() % 2];//随机调用运算符

	switch (operator) {
	case '+':
		if (number1 + number2 <= 100) {
			printf("请输入结果：%d + %d = ", number1, number2);//提示语
			return number1 + number2;
			break;
		}
		else {
			return -1;//无效//跳过用的
			break;
		}
	case '-':
		if (number1 < number2) {
			return -1;
		}
		else {
			printf("请输入结果：%d - %d = ", number1, number2);//提示语
			return number1 - number2;
		}
	default:
		return -1;//无效
		break;
	}
}
//乘除
i32 mul_div(void) {

	//生成随机数和随机符号
	u32 number2 = rand() % 10 + 1;//1-10
	u32 number1 = rand() % ((10 - 0 + 1) + 0) * number2;

	char operators[] = { '*', '/' };//四则运算符定义
	char operator = operators[rand() % 2];//随机调用运算符


	switch (operator) {
	case '*':
		if (number1 <= 100) {
			printf("请输入结果：%d x %d = ", number1 / number2, number2);//提示语
			return number1;
			break;
		}
		else {
			return -1;//无效
			break;
		}
	case '/':
		if (number1 <= 100) {
			printf("请输入结果：%d / %d = ", number1, number2);//提示语
			return number1 / number2;
			break;
		}
		else {
			return -1;//无效
			break;
		}
	default:
		return -1;//无效
		break;
	}
}

//// 保存测试结果到文件
void save_test_result(char mode[], u32 problem, double score) {

	//获取当前时间戳
	time_t now = time(NULL);

	//转换成本地时间
	struct tm local_time;
	localtime_s(&local_time, &now);

	char local_time_str[80];
	strftime(local_time_str, sizeof(local_time_str), "%Y-%m-%d %H:%M:%S", &local_time);

	//存储数据
	FILE* file = fopen(FILENAME, "a");
	if (file) {
		fprintf(file, "date: %s", local_time_str);
		fprintf(file, "\tmode: %s", mode);
		fprintf(file, "\tproblem number: %u", problem);
		fprintf(file, "\tscore: %.1lf\n", score);
		fclose(file);
	}
	else {
		printf("无法打开文件保存结果。\n");
	}
}