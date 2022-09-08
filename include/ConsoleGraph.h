//Класс отрисовки графиков в консоле

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

	HDC hdc;																			//Объект - реальный экран
	HPEN Pen;																			//Объект - перо
	vector<int> Zero_W;																	//Нуль Box
	vector<int> Zero_G;																	//Нуль внутри Box

	void Scale_correct(double*, double*, double*, double*);								//Единое масштабирование
	void Graph_type(int,int);															//Тип графика (линия по умолчанию)

public:

	int Height;
	int Weight;
	int Frame;																			//Расстояние от Box до Графика
	string Zero = "None";
	string Type = "Line";																//Тип графика: "Dot"/"Line"
	string Scale = "Different";															//Вид масштабирования: "Different"/"Even"
	int Part = 1;																		//Отображаемые четверти
	vector<int> Number;																	//Количество графиков в форме {Row,Column}

	ConsoleGraph(int = 750, int = 450, vector<int> = {1,1});							//Конструктор(Weight,Height,{Row,Column})
	ConsoleGraph& plot(tuple<vector<double>, vector<double>>, int = 1, int = 1);		//Построить({x,y},Row,Column)
	void Box(int, int);																	//Коробка графика(Row,Column)

};

