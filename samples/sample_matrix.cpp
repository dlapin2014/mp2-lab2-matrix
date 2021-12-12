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
    setlocale(LC_ALL, "Russian");

    TVector <int> a(1, 2); // a = 001
    a[2] = 1;

    TVector <int> b(2, 1); // b = 022
    b[1] = 2;
    b[2] = 2;

    cout << a - b;

  /*cout << "Введите размеры матриц a и b ";
  int a_size, b_size;
  cin >> a_size >> b_size;
  TMatrix<int> a(a_size), b(b_size);

  if (a_size != b_size)
      cout << "Невозможно сложить и вычесть матрицы разного размера" << endl;
  else {

      cout << "Введите матрицу А" << endl;
      cin >> a;

      cout << "Введите матрицу B" << endl;
      cin >> b;

      cout << "Matrix a + b = " << endl << a + b << endl;
      cout << "Matrix a - b = " << endl << a - b << endl;
  }*/
}
//---------------------------------------------------------------------------
