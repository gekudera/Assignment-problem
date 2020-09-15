
#include <stdlib.h>
#include <stdio.h>
#include <fstream> 
#include <iostream>
#include <cstring> 
#include <ctime>
#include <string>
#include <stack> 
using namespace std;

void print(int** S, int size, int* V, int* U)
{
	cout << "___________________________" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << "   " << S[i][j];
			}
			cout << "| " << V[i] << endl;
		}
		cout << "---------------------------" << endl << "U: ";
		for (int j = 0; j < size; j++)
		{
			cout << U[j] << "   ";
		}
		cout << endl;
}

void printSimple(int** S, int size)
{
	cout << "___________________________" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << "   " << S[i][j];
		}
		cout << "|"<<endl;
	}
	cout << "---------------------------" << endl;
}

int countWords() //функция считает size 
{
	string Matrix_str;
	ifstream Matrix_F;
	Matrix_F.open("input.txt");
	if (Matrix_F.is_open())
	{
		getline(Matrix_F, Matrix_str);
	}
	//cout « Matrix_str « endl;
	Matrix_str += ' ';
	int i = 0, count_word = 0;
	while (Matrix_str[i])
	{
		if (Matrix_str[i] != ' ' && Matrix_str[i + 1] == ' ') count_word++;
		i++;
	}
	Matrix_F.close();
	return count_word;
}

int FirstSimpleMatrix(int** In, int** S, int size, int* V)
{
	int max, index;
	for (int i = 0; i < size; i++)
	{
		max = 0;
		int index;
		for (int j = 0; j < size; j++)
		{
			if (In[i][j] >= max)
			{
				max = In[i][j];
				index = j;
			}
		}
		S[i][index] = 1;
		V[i] = max;
		for (int j = 0; j < size; j++)
		{
			if ((In[i][j] == max)&&(j!=index))
			{
				S[i][j] = 1;
			}
		}
	}
	return 0;
}

int SimpleMatrix(int** In, int** S, int size, int* U, int* V)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (In[i][j] == (V[i] + U[j]))
				S[i][j] = 1;
			else S[i][j] = 0;
		}
	}
	return 0;
}


int poisk(int** S, int size, int* Solution, int* V, int* U)
{
	for (int i = 0; i < size; i++)
		Solution[i] = -1;
	int a = 0, b = 0, bezrab = 0, first = 0, noone, count = 0;
	int flag1 = 0;//флаг чтобы он находил только 1 единичку в строчее
	int flag3 = 0;
	int flag2 = 0;
	int flag4 = 0;
	int* remember = new int[size];
	int* works = new int[size]; //для записи выбранных работ(чтобы их не выбирали 2 раз)
	for (int i = 0; i < size; i++)
		works[i] = -1;
	int** S1 = new int* [size]; //матрица 5х5 для записи пройденных цепочек
	for (int i = 0; i < size; i++)
	{
		S1[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			S1[i][j] = 0;
	}


	stack <int> steck;  // создаем стек


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			if ((S[i][j] == 1) && (a == 0))
			{
				for (int k = 0; k < size; k++)
				{
					if (Solution[k] == j) //проверка на то, что этот столбец еще не взят
					{
						b++;
					}
				}
				if (b == 0)
				{
					Solution[i] = j;
					a = 1;
					cout << i + 1 << " работник взял " << j + 1 << " работу" << endl;
				}
			}
			b = 0;
		}
		a = 0;
		if (Solution[i] == -1)
		{
			cout << i + 1 << " работник не нашёл работу!" << endl;
			bezrab = i;
			first = i;
			V[bezrab] = V[bezrab] - 1;
			steck.push(bezrab);
		}
	}
	int* Solution1 = new int[size];
	for (int i = 0; i < size; i++)
		Solution1[i] = Solution[i]; //создаем копию



	//ПЕРЕНАЗНАЧЕНИЕ
	cout << endl << "ЦЕПОЧКА ПЕРЕНАЗНАЧЕНИЙ: " << endl;
	count = 1;
	while ((!steck.empty()) && (flag2 == 0))
	{
		noone = 0;
		flag1 = 0;
		flag2 = 1;
		flag4 = 0;
		for (int j = 0; j < size; j++)
		{
			flag3 = 0;
			for (int m = 0; m < size; m++)
			{
				if (works[m] == j)
					flag3 = 1;
			}
			if ((S[steck.top()][j] == 1) && (flag1 == 0) && (flag3 == 0) && (S1[steck.top()][j] != 1))
			{
				flag1 = 1;
				Solution1[steck.top()] = j;
				works[count] = j;
				U[j] = U[j] + 1;
				b = j;
				count++;
				cout << "J" << steck.top() + 1 << " на R" << j + 1;
				S1[steck.top()][j] = 1;
				noone = 2;
				for (int i = 0; i < size; i++)
				{
					if ((Solution[i] == Solution1[steck.top()]) && (i != steck.top()))
					{
						steck.push(i);
						V[steck.top()] = V[steck.top()] - 1;
						Solution1[i] = -2;
						cout << " -> Теперь J" << steck.top() + 1 << " ищет работу!! ";
						if (steck.top() == first)
						{
							cout << "Цепочка замкнулась, шаг назад" << endl << endl;;
							steck.pop();  // удаляем верхний элемент
							break;
						}
					}
				}
			}

		}
		if (noone == 0)
		{
			a = 0;
			for (int i = 0; i < size; i++)
			{
				if ((S[i][b] == 0) && (i != steck.top()))
				{
					a++;
				}
			}
			if (a == 4)
			{
				flag4 = 1;
				cout << " Цепь замкнулась для " << steck.top()+1 << endl;
					steck.pop();
			}
			if (flag4 == 0)
			{
				if (!steck.empty())
				{
					cout << "J" << steck.top() + 1 << " больше ничего не может. Переходим на шаг назад" << endl; // выводим верхний элемент
					works[count] = -1;
					count--;
					flag2 = 0;
					Solution1[steck.top()] = Solution[steck.top()];
					for (int j = 0; j < size; j++)
					{
						S1[steck.top()][j] = 0;
					}
					steck.pop();  // удаляем верхний элемент
				}
				else
				{
					break;
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			if (Solution1[i] < 0)
				flag2 = 0;
		}

	}

	for (int i = 0; i < size; i++)
		Solution[i] = Solution1[i];

	cout << endl << "НАЗНАЧЕНИЕ:" << endl;
	if (flag2 == 1)
	{
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << "работник на " << Solution[i] + 1 << "работу" << endl;
		}
	}
	else
	{
		cout << "Невозможно распределить работников по работам!" << endl;
	}
	return 0;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int size = countWords();
	int fl = 0;
	int Cmax = 0;
	cout << "Размер матрицы = " << size << endl;
	int** In = new int* [size]; //входнаяя матрица
	for (int i = 0; i < size; i++)
	{
		In[i] = new int[size];
	}
	int** S = new int* [size]; //простейшая матрица
	for (int i = 0; i < size; i++)
	{
		S[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			S[i][j] = 0;
	}
	int* Solution = new int[size];
	for (int i = 0; i < size; i++)
	{
		Solution[i] = -1;
	}
	int* U = new int[size];
	for (int i = 0; i < size; i++)
	{
		U[i] = 0;
	}
	int* V = new int[size];
	for (int i = 0; i < size; i++)
	{
		V[i] = 0;
	}
	ifstream in("input.txt", ios::in | ios::binary);

	if (!in) return 1; //Если ошибка открытия файла, то завершаем программу

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			in >> In[i][j];
		}
	}
	in.close(); //Закрываем файл
	FirstSimpleMatrix(In, S, size, V);
	cout << "Матрица из файла: " << endl;
	print(In, size, V, U);
	cout << endl << endl;
	cout << "Формируем простейшую матрицу: " << endl;
	FirstSimpleMatrix(In, S, size, V);
	printSimple(S, size);
	poisk(S, size, Solution, V, U);
	
	while (fl == 0)
	{
		fl = 1;
		print(In, size, V, U);
		SimpleMatrix(In, S, size, U, V);
		printSimple(S, size);
		poisk(S, size, Solution, V, U);
		for (int i = 0; i < size; i++)
		{
			if (Solution[i] < 0)
				fl = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Solution[i] == j)
				Cmax = Cmax + In[i][j];
		}
	}

	cout << "Cmax = " << Cmax << endl;
}