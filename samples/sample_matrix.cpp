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
    setlocale(LC_ALL, "Russian");

    TVector <int> a(1, 2); // a = 001
    a[2] = 1;

    TVector <int> b(2, 1); // b = 022
    b[1] = 2;
    b[2] = 2;

    cout << a - b;

  /*cout << "������� ������� ������ a � b ";
  int a_size, b_size;
  cin >> a_size >> b_size;
  TMatrix<int> a(a_size), b(b_size);

  if (a_size != b_size)
      cout << "���������� ������� � ������� ������� ������� �������" << endl;
  else {

      cout << "������� ������� �" << endl;
      cin >> a;

      cout << "������� ������� B" << endl;
      cin >> b;

      cout << "Matrix a + b = " << endl << a + b << endl;
      cout << "Matrix a - b = " << endl << a - b << endl;
  }*/
}
//---------------------------------------------------------------------------
