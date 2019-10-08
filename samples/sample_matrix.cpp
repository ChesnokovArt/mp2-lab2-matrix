// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sample_matrix.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (20.04.2015)
//
// ������������ ����������������� �������

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
		cout << "������������ �������� ��������� ������������� ����������� ������"
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
		// ����������� ��������� �������
		TMatrix<int> *m1, *m2;
		char ch;
		int sz;
		do
		{
			cout << "������� ������ �������: ";
			cin >> sz;
			m1 = new TMatrix<int>(sz);
			m2 = new TMatrix<int>(sz);
			cout << "��������� ������ �������" << endl;
			cin >> *m1;
			cout << "��������� ������ �������" << endl;
			cin >> *m2;
			cout << "����� �������� ��������� � ���������?" << endl
				<< "1) �������" << endl
				<< "2) �������" << endl;
			cin >> sz;
			switch (sz)
			{
			case 1:
				cout << "���������:" << endl << (*m1) + (*m2) << endl;
				break;
			case 2:
				cout << "���������:" << endl << (*m1) - (*m2) << endl;
				break;
			}
			cout << "n - ����������, q - �����" << endl;
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
			cout << "������������ ��������� � ��������� ������� (q ����� �����)";
			break;
		case Invalid_Operation:
			cout << "������������ �������� (q ����� �����)";
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
