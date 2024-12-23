﻿#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int q = 3;

double** interactive_edit(double** matr, int m_size) {
point2:;
	int row, col;
	cout << "Введите номер строки элемента матрицы, который хотите заменить: ";
	cin >> row;
	if (row > m_size) {
		cout << "Нет такой строки." << endl;
		goto point2;
	}
point3:;
	cout << "Введите номер столбца элемента, который хотите заменить: ";
	cin >> col;
	if (col > m_size) {
		cout << "Нет такого столбца." << endl;
		goto point3;
	}
	cout << "Текущее значение [" << row << "][" << col << "]-го элемента: " << matr[row - 1][col - 1] << "." << endl;
	cout << "Введите новое значение [" << row << "][" << col << "]-го элемента: ";
	cin >> matr[row - 1][col - 1];
	return matr;
}

double average_arifm_column(double** matr, int m_size, int num_column) {
	double sum = 0, q = 0;
	for (int i = 0; i < m_size; i++) {
		sum += matr[i][num_column];
		q++;
	}
	return sum / q;
}

void matrix_to_disp(double** A, int m_size)
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size - 1; j++)
			cout << setw(3)<<A[i][j] << " ";
		cout <<setw(3)<< A[i][m_size - 1] << endl;
	}
}

double** declaration_of_matrix(int m_size) {
	double** matrix = new double* [m_size];
	for (int i = 0; i < m_size; i++) {
		matrix[i] = new double[m_size];
	}
	return matrix;
}

void delete_matrix(double** matrix, int m_size) {
	for (int i = 0; i < m_size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

double** input_matrix(double** matrix, int m_size, string name) {
	int num;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			cout << endl << "Введите [" << i + 1 << "][" << j + 1 << "]-й элемент матрицы " << name << " ";
			cin >> num;
			matrix[i][j] = num;
		}
	}
	return matrix;
}

void matrixes_in(double** A, double** B, double** C, int a_size, int b_size, int c_size, string a_name, string b_name, string c_name) {
	cout << "Ввод элементов матрицы " <<a_name<<"."<< endl;
	A = input_matrix(A, a_size, a_name);
	cout << "Ввод элементов матрицы " << b_name << "."<<endl;
	B = input_matrix(B, b_size, b_name);
	cout << "Ввод элементов матрицы " << c_name <<"."<< endl;
	C = input_matrix(C, c_size, c_name);
}

int arifm_count(double** A, double** B, double** C, int a_size, int b_size, int c_size) {
	double* A_arifm = new double[a_size];
	double* B_arifm = new double[b_size];
	for (int i = 0; i < a_size; i++) {
		A_arifm[i] = average_arifm_column(A, a_size, i);
	}
	for (int i = 0; i < b_size; i++) {
		B_arifm[i] = average_arifm_column(B, b_size, i);
	}
	int elements = 0;
	for (int i = 0; i < c_size; i++) {
		for (int j = 0; j < c_size; j++) {
			if (j <= a_size - 1 && j <= b_size - 1) {
				if (C[i][j] > A_arifm[j] && C[i][j] > B_arifm[j])
					elements++;
			}
			else continue;
		}
	}
	delete[] A_arifm;
	delete[] B_arifm;
	return elements;
}

void equal_matrix(int** matrix1, int** matrix2, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix1[i][j] = matrix2[i][j];
}

void file_out(double** A[], int sizes[], string names[], int elements) {
	ofstream out;
	out.open("output.txt");
	if (out.is_open()) {
		for (int i = 0; i < q; i++) {
			out << "Матрица " << names[i] << endl;
			for (int j = 0; j < sizes[i]; j++) {
				for (int k = 0; k < sizes[i] - 1; k++)
					out << A[i][j][k] << " ";
				out << A[i][j][sizes[i] - 1] << endl;
			}
		}
		out << "Количество элементов матрицы С, превосходящих среднее арифметическое соответствующих столбцов матриц А и В:" << elements << endl;
	}
	out.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int command = 0, A_matr_size=0, B_matr_size=0, C_matr_size=0, elements=0;
	bool matr_input = false, a_count = false;
	string file_name;
	string names[3] = { "A", "B", "C" };
	double** A = declaration_of_matrix(A_matr_size);
	double** B = declaration_of_matrix(B_matr_size);
	double** C = declaration_of_matrix(C_matr_size);
	while (command != 7) {
	begin:;
		cout << "Введите команду:" << endl;
		cout << "1 - консольный ввод данных о матрицах A, B и C;" << endl;
		cout << "2 - файловый ввод данных о матрицах А, В и С;" << endl;
		cout << "3 - консольное (интерактивное) редактирование элементов матриц;" << endl;
		cout << "4 - подсчет количества элементов матрицы С, превышающих среднее арифметическое соответствующих столбцов матриц А и В;" << endl;
		cout << "5 - консольный вывод текущих данных о матрицах;" << endl;
		cout << "6 - файловый вывод данных о матрицах;" << endl;
		cout << "7 - выход из программы." << endl;
		cin >> command;
		if (command != 1 && command != 2 && command != 3 && command != 4 && command != 5 && command != 6&&command!=7) {
			cout << "Введена некорректная команда." << endl;
			goto begin;
		}
		switch (command) {
		case 1:
		{
			cout << "Введите размер матрицы А:" << endl;
			cin >> A_matr_size;
			A = declaration_of_matrix(A_matr_size);
			cout << "Введите размер матрицы В:" << endl;
			cin >> B_matr_size;
			B = declaration_of_matrix(B_matr_size);
			cout << "Введите размер матрицы С:" << endl;
			cin >> C_matr_size;
			C = declaration_of_matrix(C_matr_size);
			matrixes_in(A, B, C, A_matr_size, B_matr_size, C_matr_size, "A", "B", "C");
			matr_input = true;
			break;
		}
		case 2:
		{
			cout << "Чтобы ввести данные матриц из файла, создайте файл формата .txt в папке с программой." << endl;
			cout << "Файл должен содержать следующие данные:" << endl;
			cout << "1 - размер матрицы А;" << endl;
			cout << "2 - ввод элементов матрицы А через пробел;" << endl;
			cout << "3 - размер матрицы В;" << endl;
			cout << "4 - ввод элементов матрицы B через пробел;" << endl;
			cout << "5 - размер матрицы C;" << endl;
			cout << "6 - ввод элементов матрицы C через пробел;" << endl;
			cout << "Примечание: можно вводить элементы матриц построчно." << endl;
			cout << "Введите имя файла в формате <<file.txt>>: "; 
			cin >> file_name;
			ifstream in(file_name);
			if (in.is_open()) {
				in >> A_matr_size;
				A = declaration_of_matrix(A_matr_size);
				for (int i = 0; i < A_matr_size; i++) {
					for (int j = 0; j < A_matr_size; j++) {
						in >> A[i][j];
					}
				}
				in >> B_matr_size;
				B = declaration_of_matrix(B_matr_size);
				for (int i = 0; i < B_matr_size; i++) {
					for (int j = 0; j < B_matr_size; j++) {
						in >> B[i][j];
					}
				}
				in >> C_matr_size;
				C = declaration_of_matrix(C_matr_size);
				for (int i = 0; i < C_matr_size; i++) {
					for (int j = 0; j < C_matr_size; j++) {
						in >> C[i][j];
					}
				}

			}
			in.close();
			matr_input = true;
			cout << "Матрицы успешно записаны." << endl;
			break;
		}
		case 3:
		{
			string m_name;
		point:;
			cout << "Какую матрицу вы хотите отредактирвоать (А, В, С)?" << endl;
			cin >> m_name;
			if (m_name == "A")
				interactive_edit(A, A_matr_size);
			else if (m_name == "B")
				interactive_edit(B, B_matr_size);
			else if (m_name == "C")
				interactive_edit(C, C_matr_size);
			else {
				cout << "Введено некорректное название матрицы." << endl;
				goto point;
			}
			break;
		}
		case 4:
		{
			elements = arifm_count(A, B, C, A_matr_size, B_matr_size, C_matr_size);
			cout << "Количество элементов матрицы С, превышающих среднее арифметическое соответствующих столбцов матриц А и В: " << elements << endl;
			a_count = true;
			break;
		}
		case 5:
		{
			if (!matr_input)
				cout << "Вы ещё не ввели матрицы." << endl;
			else
			{
				cout << "Матрица А:" << endl;
				matrix_to_disp(A, A_matr_size);
				cout << "Матрица В:" << endl;
				matrix_to_disp(B, B_matr_size);
				cout << "Матрица С:" << endl;
				matrix_to_disp(C, C_matr_size);
			}
			break;
		}
		case 6:
		{
			if (matr_input) {
				double** matrixes[3] = { A, B, C };
				int sizes[3] = { A_matr_size, B_matr_size, C_matr_size };
				if (!a_count)
					elements = arifm_count(A, B, C, A_matr_size, B_matr_size, C_matr_size);
				file_out(matrixes, sizes, names, elements);
				cout << "Матрицы успешно записаны." << endl;
				break;
			}
			else {
				cout << "Данные о матрицах отсутствуют." << endl;
				break;
			}
		}
		}
	}
	delete_matrix(A, A_matr_size);
	delete_matrix(B, B_matr_size);
	delete_matrix(C, C_matr_size);
}
