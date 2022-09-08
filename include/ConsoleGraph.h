//����� ��������� �������� � �������

#pragma once

#include "tuple"
#include "vector"
#include "cmath"
#include "iostream"
#include "Windows.h"
#include "algorithm"
#include "Special.h"

using namespace std;

class ConsoleGraph
{
private:

	HDC hdc;																			//������ - �������� �����
	HPEN Pen;																			//������ - ����
	vector<int> Zero_W;																	//���� Box
	vector<int> Zero_G;																	//���� ������ Box

	void Scale_correct(double*, double*, double*, double*);								//������ ���������������
	void Graph_type(int,int);															//��� ������� (����� �� ���������)

public:

	int Height;
	int Weight;
	int Frame;																			//���������� �� Box �� �������
	string Zero = "None";
	string Type = "Line";																//��� �������: "Dot"/"Line"
	string Scale = "Different";															//��� ���������������: "Different"/"Even"
	int Part = 1;																		//������������ ��������
	vector<int> Number;																	//���������� �������� � ����� {Row,Column}

	ConsoleGraph(int = 750, int = 450, vector<int> = {1,1});							//�����������(Weight,Height,{Row,Column})
	ConsoleGraph& plot(tuple<vector<double>, vector<double>>, int = 1, int = 1);		//���������({x,y},Row,Column)
	void Box(int, int);																	//������� �������(Row,Column)

};

