// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{
	try
	{
		TMatrix<int> a(5), b(5), c(5);
		int i, j;

		setlocale(LC_ALL, "Russian");
		cout << "Тестирование программ поддержки представления треугольных матриц"
			<< endl;
		for (i = 0; i < 5; i++)
			for (j = i; j < 5; j++)
			{
				a[i][j] = i * 10 + j;
				b[i][j] = (i * 10 + j) * 100;
			}
		c = a + b;
		cout << "Matrix a = " << endl << a << endl;
		cout << "Matrix b = " << endl << b << endl;
		cout << "Matrix c = a + b" << endl << c << endl;
		// модификация тестового примера
		TMatrix<int> *m1, *m2;
		char ch;
		int sz;
		do
		{
			cout << "Введите размер матрицы: ";
			cin >> sz;
			m1 = new TMatrix<int>(sz);
			m2 = new TMatrix<int>(sz);
			cout << "Заполните первую матрицу" << endl;
			cin >> *m1;
			cout << "Заполните вторую матрицу" << endl;
			cin >> *m2;
			cout << "Какое действие выполнить с матрицами?" << endl
				<< "1) сложить" << endl
				<< "2) вычесть" << endl;
			cin >> sz;
			switch (sz)
			{
			case 1:
				cout << "Результат:" << endl << (*m1) + (*m2) << endl;
				break;
			case 2:
				cout << "Результат:" << endl << (*m1) - (*m2) << endl;
				break;
			}
			cout << "n - продолжить, q - выйти" << endl;
			cin >> ch;
			delete m1;
			delete m2;
		} while (ch != 'q');
	}
	catch (Exceptions e)
	{
		switch (e)
		{
		case Invalid_Index:
			cout << "Некорректное обращение к элементам матрицы (q чтобы выйти)";
			break;
		case Invalid_Operation:
			cout << "Неккоректная операция (q чтобы выйти)";
			break;
		default:
			break;
		}
		char f;
		do
		{
			cin >> f;
		} while (f != 'q');
	}
  
}
//---------------------------------------------------------------------------
