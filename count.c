/*ǰ��:����Ҫ�������11.24������ʱû�жԽ���Ҫ���˼·�������ύһ�飨����û˵���ܶ���ύbushi)
 ������ݳ�������֪������಻�㣺
 1.����ע�Ͳ��淶
 2.��Ϊ��ûѧ��ṹ�壨ʱ����ǵ���ͻ���ģ�����Щ���ݵ���ɲ�����Ч���Ե�ӷ��
 3.���ļ�Ŀǰֻ����ļ�д�������������ܳ�
 4.��������ģ���
 ����
 ���12.8��֮ǰ���µ�˼·������ʻ����ύһ�棬���Ѻ���ע�Ͳ�ȫ
 ��ʱ�������ɡ�
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define FILENAME "test_records.txt"
#define  MAX_QUESTIONS 30 //�̶���Ŀģʽ
#define MAX_MINUTE 900 //�̶���Ŀģʽ���ʱ��
#define LIMIT_MINUTE 180 //�̶�ʱ��ģʽ�޶�ʱ��

#define u32 uint32_t
#define i32 int32_t

//��������
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
		//��ʾ�˵�
		puts("****���˵�****");
		puts("1���̶���Ŀ����������ʱ������1000�֣�");
		puts("2���̶�ʱ������������������������ޣ�");
		puts("3���˳�");
		puts("��ѡ��һ��ѡ��:");
		scanf_s("%"SCNu32, &choice);

		//�����û���ѡ��
		switch (choice) {
		case 1:
			process_bar();
			fixed_problem();
			system("cls");
			puts("��Ϸ�Ѿ����꣬�������˵�����ѡ��");
			break;
		case 2:
			process_bar();
			fixed_time();
			system("cls");
			puts("��Ϸ�Ѿ����꣬�������˵�����ѡ��");
			break;
		case 3:
			puts("��л���棬�ټ���");
			break;
		default:
			puts("��Чѡ��������ѡ��");
			break;
		}

	} while (choice != 3);

	system("pause");
	return 0;
}

////����������
void process_bar(void) {
	system("cls");
	const u32 total_steps = 100;//����������

	puts("��Ϸ�����У����Ժ�");

	for (u32 i = 0; i <= total_steps; i++) {
		printf("\r[");

		//��ӡ����������������
		for (u32 j = 0; j < i; j++) {
			printf("#");
		}
		for (u32 j = i; j < total_steps; j++) {
			printf(" ");
		}

		printf("]%"PRIu32"%%", (i * 100) / total_steps);
		//ʵ�ʣ����Ѿ������������/�ļ��ܴ�С��* %100

		fflush(stdout);//ȷ����������ʱ��ʾ
		Sleep(100);//ģ��
	}

	system("cls");
	puts("�������,��Ϸ��ʼ��");
}

////ģʽ
//�̶���Ŀ
void fixed_problem(void) {
	//ģʽ
	char mode[] = "fixed problem";
	u32 problem = MAX_QUESTIONS;

	u32 right;//��ȷ��
	u32 input;//�û�����
	u32 metering = 1;//ͳ����Ч����
	double right_answer = 0.0;//��ȷ����
	double score;

	//���������
	i32(*func_array[])() = { add_sub , mul_div };
	srand(time(NULL));

	//��ʱ
	clock_t start, end;
	double time_spent;

	start = clock();
	while (metering <= MAX_QUESTIONS) {

		//��ȷ��
		right = func_array[rand() % 2]();

		//����䣬��Ч�������
		if (right == -1) {
			continue;
		}

		//����
		scanf_s("%d", &input);
		if (right == input) {
			right_answer++;
			printf("��ȷ\n");
		}
		else {
			printf("����\n");
		}

		metering++;//�ƴ�

		//��ʱ
		if ((clock() - start) / CLOCKS_PER_SEC >= MAX_MINUTE) {
			printf("ʱ�䵽��");
			break;
		}
	}
	end = clock();
	time_spent = (end - start) / CLOCKS_PER_SEC;

	score = right_answer * 100.0 / MAX_QUESTIONS + (MAX_MINUTE - time_spent);
	printf("\n�ɼ���%.1f\n", score);

	save_test_result(mode, problem, score);
	system("pause");
}
//�̶�ʱ��
void fixed_time(void) {

	//ģʽ
	char mode[] = "fixed time";
	u32 problem = 0;//����

	u32 right;//��ȷ��
	u32 input;//�û�����
	u32 metering = 0;//ͳ����Ч����
	double right_answer = 0.0;
	double score;

	//���������
	i32(*func_array[])() = { add_sub , mul_div };
	srand(time(NULL));

	//��ʱ
	clock_t start;

	start = clock();
	while (true) {

		//��ȷ��
		right = func_array[rand() % 2]();

		//�����
		if (right == -1) {
			continue;
		}

		//����
		problem++;
		scanf_s("%d", &input);
		if (right == input) {
			right_answer++;
			printf("��ȷ\n");
		}
		else {
			printf("����\n");
		}

		//��ʱ
		if ((clock() - start) / CLOCKS_PER_SEC >= LIMIT_MINUTE) {
			printf("ʱ�䵽��");
			break;
		}

	}

	score = right_answer * 100.0 / problem * right_answer;
	printf("\n�ɼ���%.1f\n", score);

	save_test_result(mode, problem, score);
	system("pause");
}

////������������
//�Ӽ�
i32 add_sub(void) {

	//������������������
	u32 number1 = rand() % (100 - 0 + 1) + 0;
	u32 number2 = rand() % (100 - 0 + 1) + 0;
	char operators[] = { '+', '-' };//�������������
	char operator = operators[rand() % 2];//������������

	switch (operator) {
	case '+':
		if (number1 + number2 <= 100) {
			printf("����������%d + %d = ", number1, number2);//��ʾ��
			return number1 + number2;
			break;
		}
		else {
			return -1;//��Ч//�����õ�
			break;
		}
	case '-':
		if (number1 < number2) {
			return -1;
		}
		else {
			printf("����������%d - %d = ", number1, number2);//��ʾ��
			return number1 - number2;
		}
	default:
		return -1;//��Ч
		break;
	}
}
//�˳�
i32 mul_div(void) {

	//������������������
	u32 number2 = rand() % 10 + 1;//1-10
	u32 number1 = rand() % ((10 - 0 + 1) + 0) * number2;

	char operators[] = { '*', '/' };//�������������
	char operator = operators[rand() % 2];//������������


	switch (operator) {
	case '*':
		if (number1 <= 100) {
			printf("����������%d x %d = ", number1 / number2, number2);//��ʾ��
			return number1;
			break;
		}
		else {
			return -1;//��Ч
			break;
		}
	case '/':
		if (number1 <= 100) {
			printf("����������%d / %d = ", number1, number2);//��ʾ��
			return number1 / number2;
			break;
		}
		else {
			return -1;//��Ч
			break;
		}
	default:
		return -1;//��Ч
		break;
	}
}

//// ������Խ�����ļ�
void save_test_result(char mode[], u32 problem, double score) {

	//��ȡ��ǰʱ���
	time_t now = time(NULL);

	//ת���ɱ���ʱ��
	struct tm local_time;
	localtime_s(&local_time, &now);

	char local_time_str[80];
	strftime(local_time_str, sizeof(local_time_str), "%Y-%m-%d %H:%M:%S", &local_time);

	//�洢����
	FILE* file = fopen(FILENAME, "a");
	if (file) {
		fprintf(file, "date: %s", local_time_str);
		fprintf(file, "\tmode: %s", mode);
		fprintf(file, "\tproblem number: %u", problem);
		fprintf(file, "\tscore: %.1lf\n", score);
		fclose(file);
	}
	else {
		printf("�޷����ļ���������\n");
	}
}