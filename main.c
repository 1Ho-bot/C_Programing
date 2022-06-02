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

typedef struct { //iris ����ü ����
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char varitey[10];
} IRIS;

IRIS data[SIZE]; //IRISŸ���� data�迭 ����
float s_length[SIZE], s_width[SIZE], p_length[SIZE], p_width[SIZE];

int main(void) {
	readData();
	writeData(varietyAvg("Setosa"), varietyAvg("Versicolor"), varietyAvg("Virginica"));
}

void readData() { //iris.csv���� �����͸� �о���� �Լ�
	char header[5][20]; //iris.csv�� ù ���� �����ϴ� 2���� �迭
	FILE* iris_file = fopen("iris.csv", "r"); //iris.csv�� �б��������� ���� iris_file�� �־���

	fgets(header, sizeof(header), iris_file); //ù��° �� ���� �о� header�迭�� ����
	printf("%s", header); //header ���

	//fscanf�� ����Ͽ� iris.csv ������ �Ǽ��� ���ڿ��� ,(��ǥ)�� �������� ������ �� �پ� �о data[i].�����Ϳ� �־���.
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
	char flower_str[][25] = { "sepal_length�� ���", "sepal_width�� ���", "petal_length�� ���", "petal_width�� ���",
	"sepal_length�� ǥ������", "sepal_width�� ǥ������", "petal_length�� ǥ������", "petal_width�� ǥ������"};

	fprintf(write_file, "%s %.2f\n", "sepal_length�� ��� :", average(s_length));
	fprintf(write_file, "%s %.2f\n", "sepal_width�� ��� :", average(s_width));
	fprintf(write_file, "%s %.2f\n", "petal_length�� ��� :", average(p_length));
	fprintf(write_file, "%s %.2f\n\n", "petal_width�� ��� :", average(p_width));

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