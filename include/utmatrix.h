// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

enum Exceptions
{
	Invalid_Index,
	Invalid_Operation
};

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
	  ValType DefaultValue = ValType();
	  for (int i = 0; i < v.GetStartIndex(); i++)
	  {
		  ValType temp;
		  in >> temp;
		  // попытка записать нестандартное значение в неиспользуемый индекс
		  if (temp != DefaultValue) throw Invalid_Operation;
	  }
      for (int i = v.GetStartIndex(); i < v.Size; i++)
      in >> v.pVector[i - v.GetStartIndex()];
      return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  ValType DefaultValue = ValType();
	  for (int i = 0; i < v.GetStartIndex(); i++)
	  {
		  out << DefaultValue << ' ';
	  }
      for (int i = v.GetStartIndex(); i < v.Size; i++)
      out << v.pVector[i - v.GetStartIndex()] << ' ';
      return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s < 0) || (s > MAX_VECTOR_SIZE) || (si < 0) 
		|| (si >= MAX_VECTOR_SIZE) || (si >= s))
		throw Invalid_Index;
	Size = s; 
	StartIndex = si;
	pVector = new ValType[s - si]();
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size - StartIndex]();
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i - StartIndex] = v.pVector[i - StartIndex];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
	pVector = nullptr;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < StartIndex) || (pos > Size)) throw Invalid_Index;
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size) return false;
    for (int i = StartIndex; i < Size; i++)
	{
		if (pVector[i] != v.pVector[i]) return false;
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !((*this) == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v) return *this;
	StartIndex = v.StartIndex;
	if (Size != v.Size)
	{
		delete[] pVector;
		pVector = new ValType[v.Size - v.StartIndex]();
		Size = v.Size;
	}
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i - StartIndex] = v.pVector[i - StartIndex];
	}
	return (*this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i - StartIndex] = pVector[i - StartIndex] + val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
	{
		res.pVector[i - StartIndex] = pVector[i - StartIndex] - val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
	{
		res.pVector[i - StartIndex] = pVector[i - StartIndex] * val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
		throw Invalid_Operation;
	TVector<ValType> res(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
	{
		res.pVector[i - StartIndex] = 
			pVector[i - StartIndex] + v.pVector[i -StartIndex];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
		throw Invalid_Operation;
	TVector<ValType> res(Size, StartIndex);
	for (int i = StartIndex; i < Size; i++)
	{
		res.pVector[i - StartIndex] =
			pVector[i - StartIndex] - v.pVector[i - StartIndex];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
		throw Invalid_Operation;
	int res = 0;
	for (int i = StartIndex; i < Size; i++)
	{
		res += pVector[i - StartIndex] * v.pVector[i - StartIndex];
	}
	return res;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE) throw Invalid_Index;
	Size = s;
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = TVector<ValType>(s, i);
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
{
	Size = mt.Size;
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt)
{
	Size = mt.Size;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (Size != mt.Size) return false;
	for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != mt.pVector[i]) return false;
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this == &mt) return *this;
	delete[] pVector;
	pVector = new TVector<ValType>[mt.Size]();
	Size = mt.Size;
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = mt.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size) throw Invalid_Operation;
	TMatrix<ValType> res(Size);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] + mt.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size) throw Invalid_Operation;
	TMatrix<ValType> res(Size);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] - mt.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
