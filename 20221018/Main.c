#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 10
//id, 이름, 중간 점수, 기말 점수 == inputData.
//성적보기 -> 평균 점수
typedef struct student {
	int id; //학생의 학번
	char name[20]; //학생의 이름
	int middle_score; //중간 점수
	int final_score; //기말 점수
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

	printf("정보가 등록된 학번\n");
	if (fp = fopen("StudentDB.dat", "rb") == NULL) {
		fp = fopen("StudentDB.dat", "wb");
	}
	else {
		fp = fopen("StudentDB.dat", "rb");
		for (int i = 0; i < SIZE; i++) {
			if (fread(&studentDB[i], sizeof(STUDENT), 1, fp) != NULL) {
				printf("%s 학생 학번 : %d\n", studentDB[i].name, studentDB[i].id);
				min_num++;
			}
		}
	}
	fclose(fp);
	

	while (1) {
		printf("학생 시험 정보 등록 프로그램(1.학생 정보 등록 2.학생 점수 보기 그외 조작.종료\n>>> ");
		scanf("%d", &selcet_task);
		switch (selcet_task) {
		case 1:
			StudentRegister(studentDB, &min_num);
			break;
		case 2:
			printf("조회하시려는 학생의 번호를 입력해주세요 >>> ");
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
	printf("학생의 정보를 등록하겠습니다.\n학번을 입력해주세요 >>> ");
	scanf("%d", &studentDB[*min_num].id);
	printf("학생의 이름을 입력해주세요 >>> ");
	scanf("%s", studentDB[*min_num].name);
	printf("학생의 중간시험 점수를 입력해주세요 >>> ");
	scanf("%d", &studentDB[*min_num].middle_score);
	printf("학생의 기말시험 점수를 입력해주세요 >>> ");
	scanf("%d", &studentDB[*min_num].final_score);
	printf("%s 학생의 정보가 입력되었습니다.\n", studentDB[*min_num].name);
	*min_num = *min_num + 1;
	SaveStudentDB(studentDB, min_num);
}

void StudentScoreView(STUDENT* studentDB, int* min_num, int find_num) {
	for (int i = 0; i < *min_num; i++) {
		if (studentDB[i].id == find_num) {
			printf("%s 학생의 중간 점수는 %d점 기말 점수는 %d점 평균 점수는 %d점입니다.\n", studentDB[i].name,
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