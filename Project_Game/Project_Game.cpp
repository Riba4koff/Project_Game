﻿#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

//0 - пустая клеточка
//1 - Х (крестик)
//2 - 0 (нолик)


void Show_arr(int arr[3][3], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << arr[j][i] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
bool WhoWin(int arr[3][3], int SIZE, int value)
{
	for (int i = 0; i < SIZE; i++)
	{
		int cnt = 0;
		int cnt2 = 0;
		for (int j = 0; j < SIZE; j++)
		{
			if (arr[j][i] == value)
				cnt++;
			if (arr[i][j] == value)
				cnt2++;
		}
		if (cnt == 3 || cnt2 == 3 || ((arr[0][0] == value && arr[1][1] == value && arr[2][2] == value) || (arr[0][2] == value && arr[1][1] == value && arr[2][0] == value)))
		{
			return true;
			break;
		}
	}
	return false;
}
bool is_Draw(int arr[3][3], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 0)
				return false;
		}
	}
	return true;
}


void moves_computer(int arr[3][3], int SIZE)
{
	bool move = true; //move - проверкана то, был ли выполнен ход компьютером, если да, то move = false и ни в один ход он больше не зайдет.
	int x = 0;
	int y = 0;
	//компьютер блокирует любую победную ситуацию горизонтали (1 1 2) (2 1 1) (1 2 1) // 1 - ход игрока, 2 - ход компьютерa
	if (move)
	{
		for (int y = 0; y < SIZE; y++)
		{
			if (arr[x][y] == 1 && arr[x + 1][y] == 1 && arr[x + 2][y] == 0)
			{
				arr[x + 2][y] = 2;
				move = false;
			}
			else if (arr[x][y] == 0 && arr[x + 1][y] == 1 && arr[x + 2][y] == 1)
			{
				arr[x][y] = 2;
				move = false;
			}
			else
				if (arr[x][y] == 1 && arr[x + 1][y] == 0 && arr[x + 2][y] == 1)
				{
					arr[x + 1][y] = 2;
					move = false;
				}
		}
	}
	//компьютер блокирует любую победную ситуацию в вертикали
	if (move)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (arr[x][y] == 1 && arr[x][y + 1] == 1 && arr[x][y + 2] == 0)
			{
				arr[x][y + 2] = 2;
				move = false;
			}
			else if (arr[x][y] == 0 && arr[x][y + 1] == 1 && arr[x][y + 2] == 1)
			{
				arr[x][y] = 2;
				move = false;
			}
			else
				if (arr[x][y] == 1 && arr[x][y + 1] == 0 && arr[x][y + 2] == 1)
				{
					arr[x][y + 1] = 2;
					move = false;
				}

		}
	}
	//компьютер блокирует любую победную ситуацию в диагонали
	if (move)
	{
		if (arr[0][0] == 1 && arr[1][1] == 0 && arr[2][2] == 1)
		{
			arr[1][1] = 2;
			move = false;
		}
		else if (arr[0][2] == 1 && arr[1][1] == 0 && arr[2][0] == 1)
		{
			arr[1][1] = 2;
			move = false;
		}
		else if (arr[0][0] == 1 && arr[1][1] == 1 && arr[2][2] == 0)
		{
			arr[2][2] = 2;
			move = false;
		}
		else if (arr[0][0] == 0 && arr[1][1] == 1 && arr[2][0] == 1)
		{
			arr[0][0] = 2;
			move = false;
		}
		else if (arr[2][0] == 1 && arr[1][1] == 1 && arr[0][2] == 0)
		{
			arr[0][2] = 2;
			move = false;
		}
		else
			if (arr[0][2] == 1 && arr[1][1] == 1 && arr[2][0] == 0)
			{
				arr[2][0] = 2;
				move = false;
			}
	}
	if (move)
	{
		do
		{
			x = rand() % 3;
			y = rand() % 3;
		} while (arr[x][y] != 0);
		arr[x][y] = 2;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	const int SIZE = 3;
	//  x  y 
	int arr[SIZE][SIZE]{};
	int x = 0, y = 0;
	bool flag = true;

	Show_arr(arr, SIZE);

	while (flag)
	{
		cout << "Ваш ход!\nВведите координаты x y: ";
		cin >> x >> y;
		cout << "\n";

		int temp = arr[x][y];
		bool draw = true;
		int counter = 0;


		//Проверка на заполненную клетку
		while (temp != 0)
		{
			cout << "Клетка занята!\nПовторите попытку";
			cout << "\nВведите координаты x y: ";
			cin >> x >> y;
			temp = arr[x][y];
			cout << "\n";
		}

		arr[x][y] = 1;

		Show_arr(arr, SIZE);

		if (WhoWin(arr, SIZE, 1)) //функция проверки победы игрока. параметр 1 - это крестик, т.е. ход игрока
		{
			cout << "вы победили!\n";
			break;
		}

		if (is_Draw(arr, SIZE))
		{
			cout << "ничья!\n\n";
			break;
		}

		cout << "ход компьютера\n\n";



		moves_computer(arr, SIZE);


		Show_arr(arr, SIZE);

		//if (WhoWin(arr, SIZE, 2)) //Функция проверки победы компьютера. Параметр 2 - это нолик, т.е. ход компьютера
		//{
		//	cout << "Вы проиграли\n";
		//	break;
		//}

		//if (is_Draw(arr, SIZE))
		//{
		//	cout << "Ничья!\n\n";
		//	break;
		//}


	}



	return 0;
}