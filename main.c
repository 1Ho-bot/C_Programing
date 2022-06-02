#define _CRT_SECURE_NO_WARNINGS //보안 문제로 에러뜨는거 수정.
#include <stdio.h> //표준 입력 라이브러리.
#include <string.h> //문자열 비교 함수를 쓰기 위한 라이브러리.
#include <math.h> //표준편차를 구하기 위한 루트함수 라이브러리.
#include <stdlib.h> //동적 배열을 만들어주기 위한 라이브러리.
#define SIZE 150 //배열의 크기를 150으로 자주 쓰기때문에 정의해줌.

void readData(); //iris.csv에서 데이터를 읽어오는 함수.
void writeData(float setosa[], float versicolor[], float virginica[]); //txt파일에 계산한 데이터를 넣기 위한 함수.
float average(float value[]); //전체 평균을 구하는 함수.
float* flowerAvg(char flower[]); //꽃마다의 평균, 표준편차를 구하기 위한 함수. 매개변수로 꽃의 이름을 써줘야한다.

typedef struct { //iris 구조체 생성.
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char variety[15];
} IRIS;

IRIS data[SIZE]; //IRIS타입의 data배열 생성.
float s_length[SIZE], s_width[SIZE], p_length[SIZE], p_width[SIZE]; //전체 평균을 구하기 위한 float 변수.
char header[5][20]; //iris.csv의 첫 줄을 저장하는 2차원 배열.

int main(void) {
	readData();
	writeData(flowerAvg("Setosa"), flowerAvg("Versicolor"), flowerAvg("Virginica"));
	//varietyAvg함수의 값을 writeData의 매개변수로 준다. call by reference방식.
}

void readData() { //iris.csv에서 데이터를 읽어오는 함수.
	FILE* iris_file = fopen("iris.csv", "r"); //iris.csv를 읽기전용으로 열어 iris_file에 넣어줌.

	fgets(header, sizeof(header), iris_file); //첫번째 한 줄을 읽어 header배열에 저장.
	//printf("%s", header); //header 출력.

	//fscanf를 사용하여 iris.csv 파일의 실수와 문자열을 ,(쉼표)를 기점으로 나눠서 한 줄씩 읽어서 data[i].데이터에 넣어줌.
	for (int i = 0; i < SIZE; i++) {
		fscanf(iris_file, "%f, %f, %f, %f, %s", &data[i].sepal_length, &data[i].sepal_width,
			&data[i].petal_length, &data[i].petal_width, &data[i].variety);
		s_length[i] = data[i].sepal_length; //데이터의 전체 평균을 구하기 위해 변수에 데이터의 값을 다 더해서 대입해줌.
		s_width[i] = data[i].sepal_width;
		p_length[i] = data[i].petal_length;
		p_width[i] = data[i].petal_width;
	}

	fclose(iris_file); //파일을 닫아줌.
}

float average(float value[]) { //전체 평균을 구하는 함수 매개변수로 전체 float 값을 줘야함.
	float avg = 0; //나눈값을 저장하는 변수.
	for (int i = 0; i < SIZE; i++) {
		avg += value[i]; //매개변수 배열을 avg 변수에 다 더해줌.
	}
	return avg /= SIZE; //avg를 150으로 나눠서 반환해줌.
}

float* flowerAvg(char flower[]) { //꽃마다의 평균, 표준편차를 구하기 위한 포인터 함수.
	float s_length = 0, s_width = 0, p_length = 0, p_width = 0; //꽃받침, 꽃잎 가로세로 평균을 구하기 위한 변수.
	float* flower_data = (float*)malloc(sizeof(float) * 8); //데이터를 넣어줄 배열 생성.
	int count = 0; //평균을 구하기 위해 데이터의 갯수를 저장하는 변수.

	for (int i = 0; i < SIZE; i++) { //각각의 데이터를 변수에 더해주고 count를 1씩 증가.
		if (strcmp(data[i].variety, flower) == 0) {
			s_length += data[i].sepal_length;
			s_width += data[i].sepal_width;
			p_length += data[i].petal_length;
			p_width += data[i].petal_width;
			count++;
		}
	}
	//각 꽃들의 꽃받침, 꽃잎의 평균 구하기.
	s_length /= count;
	s_width /= count;
	p_length /= count;
	p_width /= count;

	//flower_data에 평균 값 넣어주기.
	flower_data[0] = s_length;
	flower_data[1] = s_width;
	flower_data[2] = p_length;
	flower_data[3] = p_width;
	//표준편차를 넣어줄 변수 선언 초기화.
	float s_length_dispersion = 0, s_width_dispersion = 0, p_length_dispersion = 0, p_width_dispersion = 0;

	for (int i = 0; i < SIZE; i++) { //분산을 구하기 위해 거듭제곱 math라이브러리를 pow함수를 사용해 다 더한다.
		if (strcmp(data[i].variety, flower) == 0) {
			s_length_dispersion += pow(data[i].sepal_length - s_length, 2);
			s_width_dispersion += pow(data[i].sepal_width - s_width, 2);
			p_length_dispersion += pow(data[i].petal_length - p_length, 2);
			p_width_dispersion += pow(data[i].petal_width - p_width, 2);
		}
	}

	//math라이브러리의 루트함수 sqrt를 사용해 표준편차를 구한다.
	flower_data[4] = sqrt(s_length_dispersion / count);
	flower_data[5] = sqrt(s_width_dispersion / count);
	flower_data[6] = sqrt(p_length_dispersion / count);
	flower_data[7] = sqrt(p_width_dispersion / count);
	return flower_data; //flower_data배열의 주소를 반환해줌.
}

void writeData(float setosa[], float versicolor[], float virginica[]) { //데이터를 txt파일을 생성해 작성하는 함수.
	FILE* write_file = fopen("result.txt", "w"); //result.txt파일을 쓰기전용으로 열어준다. 없을 시 폴더에 생성.
	char flower_str[][25] = { "sepal_length의 평균", "sepal_width의 평균", "petal_length의 평균", "petal_width의 평균",
	"sepal_length의 표준편차", "sepal_width의 표준편차", "petal_length의 표준편차", "petal_width의 표준편차" };
	//파일에 작성 시 데이터 값 구분을 위해 출력해 줄 문자열을 생성.

	fprintf(write_file, "%s\n", header[0]); //header에 읽어둔 iris.csv의 첫번째 줄의 값을 입력해줌.

	for (int i = 0; i < SIZE; i++) { //원본데이터를 result.txt파일에 입력.
		fprintf(write_file, "%d : %.2f %.2f %.2f %.2f %s\n", i + 1, data[i].sepal_length, data[i].sepal_width, 
			data[i].petal_length, data[i].petal_width, data[i].variety);
	}

	fprintf(write_file, "\n%s %.2f\n", "sepal_length의 평균 :", average(s_length));
	fprintf(write_file, "%s %.2f\n", "sepal_width의 평균 :", average(s_width));
	fprintf(write_file, "%s %.2f\n", "petal_length의 평균 :", average(p_length));
	fprintf(write_file, "%s %.2f\n\n", "petal_width의 평균 :", average(p_width));
	//fprintf함수를 통해 result.txt 파일에 꽃받이, 꽃잎의 전체 가로세로의 평균을 한 줄 씩 입력.
	for (int i = 0; i < 8; i++) { //setosa의 가로세로 평균과 표준편차 입력.
		fprintf(write_file, "Setosa %s %.2f\n", flower_str[i], setosa[i]);
	}
	fputs("\n", write_file);
	for (int i = 0; i < 8; i++) { //Versicolor의 가로세로 평균과 표준편차 입력.
		fprintf(write_file, "Versicolor %s %.2f\n", flower_str[i], versicolor[i]);
	}
	fputs("\n", write_file);
	for (int i = 0; i < 8; i++) { //Virginica의 가로세로 평균과 표준편차 입력.
		fprintf(write_file, "Virginica %s %.2f\n", flower_str[i], virginica[i]);
	}

	fclose(write_file); //파일을 닫아줌.
}