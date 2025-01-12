﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
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
    TVector(const TVector& v);// конструктор копирования
    ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);// доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector& v);// присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр
  TVector  operator-() const;
  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if(s > MAX_VECTOR_SIZE || si > MAX_VECTOR_SIZE) throw invalid_argument("too large vector");
    if(s < 0) throw invalid_argument("vector with negative length");
    if(si<0) throw invalid_argument("vector with negative start index");
    


    Size = s;
    StartIndex = si;
    pVector = new ValType[Size];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    int real_pos = pos - StartIndex;
    
    if (real_pos >= Size) { throw invalid_argument("too large position"); }
    if (real_pos < 0) throw invalid_argument("negative position");
    return pVector[real_pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex)
        return false;
    else
        for (int i = 0; i < Size; i++)
            if (v.pVector[i] != pVector[i])
                return false;

    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    if (v == *this)
        return false;
    else
        return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this != &v) {

        StartIndex = v.StartIndex;

        if (Size != v.Size) {
            delete[] pVector;
            Size = v.Size;
            pVector = new ValType[Size];
        }
        for (int i = 0; i < Size; i++) {
            pVector[i] = v.pVector[i];
        }

    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType> TVector<ValType>::operator-() const{
    TVector temp(*this);
    for (int i = 0; i < Size; i++)
        temp.pVector[i] = -temp.pVector[i];
    return temp;

}


template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector temp(Size, StartIndex);
    for (int i = 0; i < Size; i++)
        temp.pVector[i] = pVector[i] + val;

    return temp;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector temp(Size, StartIndex);
    temp = *this + (-val);

    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector temp(Size, StartIndex);
    for (int i = 0; i < Size; i++)
        temp.pVector[i] = pVector[i] * val;

    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{

    if ((StartIndex + Size)!=(v.Size + v.StartIndex)) throw invalid_argument("cant_add_vectors_with_not_equal_size");
    if (StartIndex < v.StartIndex) {
        TVector temp(Size, StartIndex);
        for (int i = 0; i < v.StartIndex - StartIndex; i++)
            temp.pVector[i] = pVector[i];
        for (int i = v.StartIndex - StartIndex; i < Size; i++)
            temp.pVector[i] = pVector[i] + v.pVector[i - (v.StartIndex - StartIndex)];
        return temp;
    }
    else {
        TVector temp(v.Size, v.StartIndex);
        for (int i = 0; i < StartIndex - v.StartIndex; i++)
            temp.pVector[i] = v.pVector[i];
        for (int i = StartIndex - v.StartIndex; i < v.Size; i++)
            temp.pVector[i] = pVector[i - (StartIndex - v.StartIndex)] + v.pVector[i];
        return temp;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if ((StartIndex + Size) != (v.Size + v.StartIndex)) throw invalid_argument("cant_substract_vectors_with_not_equal_size");
    if (StartIndex < v.StartIndex) {
        TVector temp(Size, StartIndex);
        for (int i = 0; i < v.StartIndex - StartIndex; i++)
            temp.pVector[i] = pVector[i];
        for (int i = v.StartIndex - StartIndex; i < Size; i++)
            temp.pVector[i] = pVector[i] - v.pVector[i - (v.StartIndex - StartIndex)];
        return temp;
    }
    else {
        TVector temp(v.Size, v.StartIndex);
        for (int i = 0; i < StartIndex - v.StartIndex; i++)
            temp.pVector[i] = -v.pVector[i];
        for (int i = StartIndex - v.StartIndex; i < v.Size; i++)
            temp.pVector[i] = pVector[i-(StartIndex - v.StartIndex)] - v.pVector[i];
        return temp;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if ((StartIndex + Size) != (v.Size + v.StartIndex)) throw invalid_argument("cant_multiply_vectors_with_not_equal_size");
    ValType s = 0;
    if (StartIndex < v.StartIndex) {
        for (int i = v.StartIndex - StartIndex; i < Size; i++)
            s += pVector[i] * v.pVector[i - (v.StartIndex - StartIndex)];
    }
    else {
        for (int i = StartIndex - v.StartIndex; i < v.Size; i++)
            s += pVector[i - (StartIndex - v.StartIndex)] * v.pVector[i];
    }

    return s;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int s = 10);
  TMatrix(const TMatrix &mt) = default;                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  //bool operator==(const TMatrix &mt) const = default;      // сравнение
  //bool operator!=(const TMatrix &mt) const = default;      // сравнение
  //TMatrix& operator= (const TMatrix &mt);        // присваивание
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
    if (Size > MAX_MATRIX_SIZE) throw invalid_argument("too large matrix");
    for (int i = 0; i < Size; i++)
        pVector[i] = TVector<ValType>(Size - i, i);
} /*-------------------------------------------------------------------------*/

/*template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {

}*/

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {
}

//template <class ValType> // сравнение
//bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
//{
//} /*-------------------------------------------------------------------------*/

//template <class ValType> // сравнение
//bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
//{
//} /*-------------------------------------------------------------------------*/

//template <class ValType> // присваивание
//TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
//{
//} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{

    if (Size != mt.Size) throw invalid_argument("cant_add_matrix_with_not_equal_size");

    TVector temp(Size);
    temp = this->TVector::operator+(mt);

    return TMatrix(temp);

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{

    if (Size != mt.Size) throw invalid_argument("cant_substract_matrix_with_not_equal_size");

    TVector temp(Size);
    temp = this->TVector::operator-(mt);

    return TMatrix(temp);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
