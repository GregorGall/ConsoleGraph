#include "ConsoleGraph.h"

ConsoleGraph::ConsoleGraph(int W, int H, vector<int> N)
{
	Frame = 10;
	Height = H;
	Weight = W;
	Number = N;
	Zero_W.push_back(1);
	Zero_W.push_back(25);
	Zero_G.push_back(Zero_W[0] + Frame);
	Zero_G.push_back(Zero_W[1] + Height - Frame);

	hdc = GetDC(GetConsoleWindow());
	Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
}

ConsoleGraph& ConsoleGraph::plot(tuple<vector<double>, vector<double>> In, int Row, int Column, int RowNum, int ClmNum) {

	Box(Row, Column, RowNum, ClmNum);
	SelectObject(hdc, Pen);

	vector<double> X_acix;
	vector<double> Y_acix;
	vector<int> Zero_g;
	tie(X_acix, Y_acix) = In;
	
	//Установка нуля по номеру графика в сетке
	Zero_g.push_back(Zero_G[0] + (Column - 1) * Weight / Number[1]);				  
	Zero_g.push_back(Zero_G[1] - (Number[0] - Row - (RowNum - 1)) * Height / Number[0]);

	double Max_X = *max_element(X_acix.begin(), X_acix.end());
	double Min_X = *min_element(X_acix.begin(), X_acix.end());
	double Max_Y = minmax(Y_acix, "max");
	double Min_Y = minmax(Y_acix, "min");

	double PPX_unit = abs((ClmNum * Weight / Number[1] - 2*(double)Frame)/(Max_X - Min_X));
	double PPY_unit = abs((RowNum * Height / Number[0] - 2*(double)Frame)/(Max_Y - Min_Y));
	
	//Единое масштабирование
	if (Scale == "Even") {															 
		if (PPY_unit > PPX_unit) {
			Zero_g[1] -= 0.5 * (Max_Y - Min_Y) * (PPY_unit - PPX_unit);	
			PPY_unit = PPX_unit;
		}
		else {
			Zero_g[0] += 0.5 * (Max_X - Min_X) * (PPX_unit - PPY_unit);
			PPX_unit = PPY_unit;
		}
	}

	for (unsigned int i = 0; i < X_acix.size(); i++) {

		//Сдвиг нуля, обеспечивает отрисовку от края окна
		int x = (int)(Zero_g[0] + (X_acix[i] - Min_X) * PPX_unit);					 
		int y = (int)(Zero_g[1] - (Y_acix[i] - Min_Y) * PPY_unit);					 

		//Условие работы с inf
		if (isinf(Y_acix[i]))                                                        
		{ 
			if (Y_acix[i] < 0) { y = (int)(Zero_W[1] + Row * Height / Number[0] - Frame); }
			if (Y_acix[i] > 0) { y = (int)(Zero_W[1] + (Row - RowNum) * Height / Number[0] + Frame); }
		}
		
		//Условие работы с nan
		if (isnan(Y_acix[i]))                                                        
		{
			continue;
		}

		if (i == 0){MoveToEx(hdc,x,y,NULL);}
		Graph_type(x, y);

	}
	return *this;
}

void ConsoleGraph::Graph_type(int x, int y) {
	
	if (Type == "Line") {
		LineTo(hdc, x, y);
	}
	if (Type == "Dot") {
		
		int thick = 2;
		MoveToEx(hdc, x + thick, y + thick, NULL);

		for (int i = 0; i < 2 * thick; i++) {
			int X, Y;
			X = x + thick - i;
			Y = y - (int)(pow(-1, i)) * thick;
			LineTo(hdc, X, Y);
			MoveToEx(hdc, X - 1, Y, NULL);
		}

	}

}

void ConsoleGraph::Box(int Row, int Column, int RowNum, int ClmNum) {
	
	vector<int> Zero_w;
	Zero_w.push_back(Zero_W[0] + Weight * (Column - 1) / Number[1]);
	Zero_w.push_back(Zero_W[1] + Height * (Row - 1) / Number[0]);

	SelectObject(hdc, Pen);
	MoveToEx(hdc, Zero_w[0], Zero_w[1], NULL);
	LineTo(hdc, Zero_w[0] + Weight * ClmNum /Number[1], Zero_w[1]);
	LineTo(hdc, Zero_w[0] + Weight * ClmNum /Number[1], Height * RowNum /Number[0] + Zero_w[1]);
	LineTo(hdc, Zero_w[0], Height * RowNum /Number[0] + Zero_w[1]);
	LineTo(hdc, Zero_w[0], Zero_w[1]);
	
}
