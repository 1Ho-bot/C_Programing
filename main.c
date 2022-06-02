#define _CRT_SECURE_NO_WARNINGS //���� ������ �����ߴ°� ����.
#include <stdio.h> //ǥ�� �Է� ���̺귯��.
#include <string.h> //���ڿ� �� �Լ��� ���� ���� ���̺귯��.
#include <math.h> //ǥ�������� ���ϱ� ���� ��Ʈ�Լ� ���̺귯��.
#include <stdlib.h> //���� �迭�� ������ֱ� ���� ���̺귯��.
#define SIZE 150 //�迭�� ũ�⸦ 150���� ���� ���⶧���� ��������.

void readData(); //iris.csv���� �����͸� �о���� �Լ�.
void writeData(float setosa[], float versicolor[], float virginica[]); //txt���Ͽ� ����� �����͸� �ֱ� ���� �Լ�.
float average(float value[]); //��ü ����� ���ϴ� �Լ�.
float* flowerAvg(char flower[]); //�ɸ����� ���, ǥ�������� ���ϱ� ���� �Լ�. �Ű������� ���� �̸��� ������Ѵ�.

typedef struct { //iris ����ü ����.
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char variety[15];
} IRIS;

IRIS data[SIZE]; //IRISŸ���� data�迭 ����.
float s_length[SIZE], s_width[SIZE], p_length[SIZE], p_width[SIZE]; //��ü ����� ���ϱ� ���� float ����.
char header[5][20]; //iris.csv�� ù ���� �����ϴ� 2���� �迭.

int main(void) {
	readData();
	writeData(flowerAvg("Setosa"), flowerAvg("Versicolor"), flowerAvg("Virginica"));
	//varietyAvg�Լ��� ���� writeData�� �Ű������� �ش�. call by reference���.
}

void readData() { //iris.csv���� �����͸� �о���� �Լ�.
	FILE* iris_file = fopen("iris.csv", "r"); //iris.csv�� �б��������� ���� iris_file�� �־���.

	fgets(header, sizeof(header), iris_file); //ù��° �� ���� �о� header�迭�� ����.
	//printf("%s", header); //header ���.

	//fscanf�� ����Ͽ� iris.csv ������ �Ǽ��� ���ڿ��� ,(��ǥ)�� �������� ������ �� �پ� �о data[i].�����Ϳ� �־���.
	for (int i = 0; i < SIZE; i++) {
		fscanf(iris_file, "%f, %f, %f, %f, %s", &data[i].sepal_length, &data[i].sepal_width,
			&data[i].petal_length, &data[i].petal_width, &data[i].variety);
		s_length[i] = data[i].sepal_length; //�������� ��ü ����� ���ϱ� ���� ������ �������� ���� �� ���ؼ� ��������.
		s_width[i] = data[i].sepal_width;
		p_length[i] = data[i].petal_length;
		p_width[i] = data[i].petal_width;
	}

	fclose(iris_file); //������ �ݾ���.
}

float average(float value[]) { //��ü ����� ���ϴ� �Լ� �Ű������� ��ü float ���� �����.
	float avg = 0; //�������� �����ϴ� ����.
	for (int i = 0; i < SIZE; i++) {
		avg += value[i]; //�Ű����� �迭�� avg ������ �� ������.
	}
	return avg /= SIZE; //avg�� 150���� ������ ��ȯ����.
}

float* flowerAvg(char flower[]) { //�ɸ����� ���, ǥ�������� ���ϱ� ���� ������ �Լ�.
	float s_length = 0, s_width = 0, p_length = 0, p_width = 0; //�ɹ�ħ, ���� ���μ��� ����� ���ϱ� ���� ����.
	float* flower_data = (float*)malloc(sizeof(float) * 8); //�����͸� �־��� �迭 ����.
	int count = 0; //����� ���ϱ� ���� �������� ������ �����ϴ� ����.

	for (int i = 0; i < SIZE; i++) { //������ �����͸� ������ �����ְ� count�� 1�� ����.
		if (strcmp(data[i].variety, flower) == 0) {
			s_length += data[i].sepal_length;
			s_width += data[i].sepal_width;
			p_length += data[i].petal_length;
			p_width += data[i].petal_width;
			count++;
		}
	}
	//�� �ɵ��� �ɹ�ħ, ������ ��� ���ϱ�.
	s_length /= count;
	s_width /= count;
	p_length /= count;
	p_width /= count;

	//flower_data�� ��� �� �־��ֱ�.
	flower_data[0] = s_length;
	flower_data[1] = s_width;
	flower_data[2] = p_length;
	flower_data[3] = p_width;
	//ǥ�������� �־��� ���� ���� �ʱ�ȭ.
	float s_length_dispersion = 0, s_width_dispersion = 0, p_length_dispersion = 0, p_width_dispersion = 0;

	for (int i = 0; i < SIZE; i++) { //�л��� ���ϱ� ���� �ŵ����� math���̺귯���� pow�Լ��� ����� �� ���Ѵ�.
		if (strcmp(data[i].variety, flower) == 0) {
			s_length_dispersion += pow(data[i].sepal_length - s_length, 2);
			s_width_dispersion += pow(data[i].sepal_width - s_width, 2);
			p_length_dispersion += pow(data[i].petal_length - p_length, 2);
			p_width_dispersion += pow(data[i].petal_width - p_width, 2);
		}
	}

	//math���̺귯���� ��Ʈ�Լ� sqrt�� ����� ǥ�������� ���Ѵ�.
	flower_data[4] = sqrt(s_length_dispersion / count);
	flower_data[5] = sqrt(s_width_dispersion / count);
	flower_data[6] = sqrt(p_length_dispersion / count);
	flower_data[7] = sqrt(p_width_dispersion / count);
	return flower_data; //flower_data�迭�� �ּҸ� ��ȯ����.
}

void writeData(float setosa[], float versicolor[], float virginica[]) { //�����͸� txt������ ������ �ۼ��ϴ� �Լ�.
	FILE* write_file = fopen("result.txt", "w"); //result.txt������ ������������ �����ش�. ���� �� ������ ����.
	char flower_str[][25] = { "sepal_length�� ���", "sepal_width�� ���", "petal_length�� ���", "petal_width�� ���",
	"sepal_length�� ǥ������", "sepal_width�� ǥ������", "petal_length�� ǥ������", "petal_width�� ǥ������" };
	//���Ͽ� �ۼ� �� ������ �� ������ ���� ����� �� ���ڿ��� ����.

	fprintf(write_file, "%s\n", header[0]); //header�� �о�� iris.csv�� ù��° ���� ���� �Է�����.

	for (int i = 0; i < SIZE; i++) { //���������͸� result.txt���Ͽ� �Է�.
		fprintf(write_file, "%d : %.2f %.2f %.2f %.2f %s\n", i + 1, data[i].sepal_length, data[i].sepal_width, 
			data[i].petal_length, data[i].petal_width, data[i].variety);
	}

	fprintf(write_file, "\n%s %.2f\n", "sepal_length�� ��� :", average(s_length));
	fprintf(write_file, "%s %.2f\n", "sepal_width�� ��� :", average(s_width));
	fprintf(write_file, "%s %.2f\n", "petal_length�� ��� :", average(p_length));
	fprintf(write_file, "%s %.2f\n\n", "petal_width�� ��� :", average(p_width));
	//fprintf�Լ��� ���� result.txt ���Ͽ� �ɹ���, ������ ��ü ���μ����� ����� �� �� �� �Է�.
	for (int i = 0; i < 8; i++) { //setosa�� ���μ��� ��հ� ǥ������ �Է�.
		fprintf(write_file, "Setosa %s %.2f\n", flower_str[i], setosa[i]);
	}
	fputs("\n", write_file);
	for (int i = 0; i < 8; i++) { //Versicolor�� ���μ��� ��հ� ǥ������ �Է�.
		fprintf(write_file, "Versicolor %s %.2f\n", flower_str[i], versicolor[i]);
	}
	fputs("\n", write_file);
	for (int i = 0; i < 8; i++) { //Virginica�� ���μ��� ��հ� ǥ������ �Է�.
		fprintf(write_file, "Virginica %s %.2f\n", flower_str[i], virginica[i]);
	}

	fclose(write_file); //������ �ݾ���.
}