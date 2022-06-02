#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 150

void readData();
void writeData(float setosa[], float versicolor[], float virginica[]);
float average(float value[]);
float* varietyAvg(char variety[]);

typedef struct { //iris 구조체 생성
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char varitey[10];
} IRIS;

IRIS data[SIZE]; //IRIS타입의 data배열 생성
float s_length[SIZE], s_width[SIZE], p_length[SIZE], p_width[SIZE];

int main(void) {
	readData();
	writeData(varietyAvg("Setosa"), varietyAvg("Versicolor"), varietyAvg("Virginica"));
}

void readData() { //iris.csv에서 데이터를 읽어오는 함수
	char header[5][20]; //iris.csv의 첫 줄을 저장하는 2차원 배열
	FILE* iris_file = fopen("iris.csv", "r"); //iris.csv를 읽기전용으로 열어 iris_file에 넣어줌

	fgets(header, sizeof(header), iris_file); //첫번째 한 줄을 읽어 header배열에 저장
	printf("%s", header); //header 출력

	//fscanf를 사용하여 iris.csv 파일의 실수와 문자열을 ,(쉼표)를 기점으로 나눠서 한 줄씩 읽어서 data[i].데이터에 넣어줌.
	for (int i = 0; i < SIZE; i++) {
		fscanf(iris_file, "%f, %f, %f, %f, %s", &data[i].sepal_length, &data[i].sepal_width,
			&data[i].petal_length, &data[i].petal_width, &data[i].varitey);
		s_length[i] = data[i].sepal_length;
		s_width[i] = data[i].sepal_width;
		p_length[i] = data[i].petal_length;
		p_width[i] = data[i].petal_width;
	}

	for (int i = 0; i < SIZE; i++) {
		printf("%d : %.1f %.1f %.1f %.1f %s\n", i, data[i].sepal_length, data[i].sepal_width,
			data[i].petal_length, data[i].petal_width, data[i].varitey);
	}

	fclose(iris_file);
}

float average(float value[]) {
	float avg = 0;

	for (int i = 0; i < SIZE; i++) {
		avg += value[i];
	}
	return avg /= SIZE;
}

float* varietyAvg(char variety[]) {
	float s_length = 0, s_width = 0, p_length = 0, p_width = 0;
	float* flower_data = (float*)malloc(sizeof(float) * 8);
	int count = 0;

	for (int i = 0; i < SIZE; i++) {
		if (strcmp(data[i].varitey, variety) == 0) {
			s_length += data[i].sepal_length;
			s_width += data[i].sepal_width;
			p_length += data[i].petal_length;
			p_width += data[i].petal_width;
			count++;
		}
	}
	s_length /= count;
	s_width /= count;
	p_length /= count;
	p_width /= count;

	flower_data[0] = s_length;
	flower_data[1] = s_width;
	flower_data[2] = p_length;
	flower_data[3] = p_width;

	float s_length_dispersion = 0, s_width_dispersion = 0, p_length_dispersion = 0, p_width_dispersion = 0;

	for (int i = 0; i < count; i++) {
		s_length_dispersion += pow(data[i].sepal_length - s_width, 2);
		s_width_dispersion += pow(data[i].sepal_width - s_width, 2);
		p_length_dispersion += pow(data[i].petal_length - p_length, 2);
		p_width_dispersion += pow(data[i].petal_width - p_width, 2);
	}
	flower_data[4] = sqrt(s_length_dispersion / count);
	flower_data[5] = sqrt(s_width_dispersion / count);
	flower_data[6] = sqrt(p_length_dispersion / count);
	flower_data[7] = sqrt(p_width_dispersion / count);
	return flower_data;
}

void writeData(float setosa[], float versicolor[], float virginica[]) {
	FILE* write_file = fopen("result.txt", "w");
	char flower_str[][25] = { "sepal_length의 평균", "sepal_width의 평균", "petal_length의 평균", "petal_width의 평균",
	"sepal_length의 표준편차", "sepal_width의 표준편차", "petal_length의 표준편차", "petal_width의 표준편차"};

	fprintf(write_file, "%s %.2f\n", "sepal_length의 평균 :", average(s_length));
	fprintf(write_file, "%s %.2f\n", "sepal_width의 평균 :", average(s_width));
	fprintf(write_file, "%s %.2f\n", "petal_length의 평균 :", average(p_length));
	fprintf(write_file, "%s %.2f\n\n", "petal_width의 평균 :", average(p_width));

	for (int i = 0; i < 8; i++) {
		fprintf(write_file, "Setosa %s %.2f\n", flower_str[i], setosa[i]);
	}
	fputs("\n", write_file);
	for (int i = 0; i < 8; i++) {
		fprintf(write_file, "Versicolor %s %.2f\n", flower_str[i], versicolor[i]);
	}
	fputs("\n", write_file);
	for (int i = 0; i < 8; i++) {
		fprintf(write_file, "Virginica %s %.2f\n", flower_str[i], virginica[i]);
	}

	fclose(write_file);
}