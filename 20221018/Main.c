#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 10
//id, �̸�, �߰� ����, �⸻ ���� == inputData.
//�������� -> ��� ����
typedef struct student {
	int id; //�л��� �й�
	char name[20]; //�л��� �̸�
	int middle_score; //�߰� ����
	int final_score; //�⸻ ����
} STUDENT;

void StudentRegister(STUDENT* studentDB, int* min_num);
void StudentScoreView(STUDENT* studentDB, int* min_num, int find_num);
void SaveStudentDB(STUDENT* studentDB, int* min_num);

void main() {
	STUDENT studentDB[SIZE];
	int min_num = 0;
	FILE* fp = NULL;
	int selcet_task = 0;
	int selcet_num = 0;

	printf("������ ��ϵ� �й�\n");
	if (fp = fopen("StudentDB.dat", "rb") == NULL) {
		fp = fopen("StudentDB.dat", "wb");
	}
	else {
		fp = fopen("StudentDB.dat", "rb");
		for (int i = 0; i < SIZE; i++) {
			if (fread(&studentDB[i], sizeof(STUDENT), 1, fp) != NULL) {
				printf("%s �л� �й� : %d\n", studentDB[i].name, studentDB[i].id);
				min_num++;
			}
		}
	}
	fclose(fp);
	

	while (1) {
		printf("�л� ���� ���� ��� ���α׷�(1.�л� ���� ��� 2.�л� ���� ���� �׿� ����.����\n>>> ");
		scanf("%d", &selcet_task);
		switch (selcet_task) {
		case 1:
			StudentRegister(studentDB, &min_num);
			break;
		case 2:
			printf("��ȸ�Ͻ÷��� �л��� ��ȣ�� �Է����ּ��� >>> ");
			scanf("%d", &selcet_num);
			StudentScoreView(studentDB, &min_num, selcet_num);
			break;
		default:
			exit(1);
			SaveStudentDB(studentDB, &min_num);
			break;
		}
	}
}
void StudentRegister(STUDENT* studentDB, int* min_num) {
	printf("�л��� ������ ����ϰڽ��ϴ�.\n�й��� �Է����ּ��� >>> ");
	scanf("%d", &studentDB[*min_num].id);
	printf("�л��� �̸��� �Է����ּ��� >>> ");
	scanf("%s", studentDB[*min_num].name);
	printf("�л��� �߰����� ������ �Է����ּ��� >>> ");
	scanf("%d", &studentDB[*min_num].middle_score);
	printf("�л��� �⸻���� ������ �Է����ּ��� >>> ");
	scanf("%d", &studentDB[*min_num].final_score);
	printf("%s �л��� ������ �ԷµǾ����ϴ�.\n", studentDB[*min_num].name);
	*min_num = *min_num + 1;
	SaveStudentDB(studentDB, min_num);
}

void StudentScoreView(STUDENT* studentDB, int* min_num, int find_num) {
	for (int i = 0; i < *min_num; i++) {
		if (studentDB[i].id == find_num) {
			printf("%s �л��� �߰� ������ %d�� �⸻ ������ %d�� ��� ������ %d���Դϴ�.\n", studentDB[i].name,
				studentDB[i].middle_score, studentDB[i].final_score, (studentDB[i].middle_score + studentDB[i].final_score) / 2);
			break;
		}
	}
}

void SaveStudentDB(STUDENT* studentDB, int* min_num) {
	FILE* fp = fopen("StudentDB.dat", "wb");
	fwrite(studentDB, sizeof(STUDENT), *min_num, fp);
	fclose(fp);
}