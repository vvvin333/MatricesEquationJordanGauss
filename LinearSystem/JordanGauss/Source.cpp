#include<iostream>
#include<locale>
#include<time.h>
using namespace std;

void showMatrix(float** matr, int n, int m)//вывод матрицы 
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%6.2f\t", matr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

float sumMatrix(float** matr1, int n, float** matr2, int m)// сложение матриц
{
	return 0;
}

float** multiplicationMatrix(float** matr1, int n, float** matr2, int m) //умножение матриц
{
	return 0;
}


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int n, m, chooseA, chooseB;
	printf("Введите размерность матрицы A: ->");
	scanf_s("%d", &n);
	printf("%d\n", n);
	printf("Задать значения элементов матрицы А вручную (1) или случайным образом (2)? ->");
	scanf_s("%d", &chooseA);
	printf("%d\n", chooseA);
	printf("Введите количество столбцов матрицы B: ->");
	scanf_s("%d", &m);
	printf("%d\n", m);
	printf("Задать значения элементов матрицы B вручную (1) или случайным образом (2)? ->");
	scanf_s("%d", &chooseB);
	printf("%d\n", chooseB);
	if (((chooseA != 1) && (chooseA != 2)) || ((chooseB != 1) && (chooseB != 2)))
	{
		printf("Ошибка! Попробуйте еще раз.");
		return 0;
	}
	float** A = new float* [n];//создание А
	for (int i = 0; i < n; i++)
		A[i] = new float[n];
	float** cA = new float* [n];// копия А
	for (int i = 0; i < n; i++)
		cA[i] = new float[n];

	float** B = new float* [n];// создание В
	for (int i = 0; i < n; i++)
		B[i] = new float[m];
	float** cB = new float* [n];//копия В
	for (int i = 0; i < n; i++)
		cB[i] = new float[m];

	float** E = new float* [n];// создание Единичной
	for (int i = 0; i < n; i++)
		E[i] = new float[n];
	for (int i = 0; i < n; i++)//заполнение Единичной
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				E[i][j] = 1;
			else
				E[i][j] = 0;
		}
	}

	switch (chooseA)//заполнение А 
	{
	case 1://вручную
		printf("Введите матрицу A :\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				printf("A["); printf("%d", i); printf("]["); printf("%d", j); printf("] = ");
				scanf_s("%f", &A[i][j]);
			}
		}
		/*float A[4][4] = {{1, 0, 2, -1},
					  { 3, 0, 0, 5 },
					  { 2, 1, 4, -3 },
					  { 1, 0, 5, 0 } };*/
		break;
	case 2://случайно
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				A[i][j] = rand() % 100 - 50;
			}
		}
		break;
	default:
		printf("Ошибка! Попробуйте еще раз.");
		return 0;
	}
	switch (chooseB)//заполнение В
	{
	case 1://вручную
		printf("Введите матрицу B :\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				printf("A["); printf("%d", i); printf("]["); printf("%d", j); printf("] = ");
				scanf_s("%f", &B[i][j]);
			}
		}
		/*float B[4][4] = {{1, 0, 2, -1},
					  { 3, 0, 0, 5 },
					  { 2, 1, 4, -3 },
					  { 1, 0, 5, 0 } };*/
		break;
	case 2://случайно
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				B[i][j] = rand() % 100 - 50;
			}
		}
		break;
	default:
		printf("Ошибка! Попробуйте еще раз.");
		return 0;

	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				E[i][j] = 1;
			else
				E[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) //копии матриц
		for (int j = 0; j < n; j++)
			cA[i][j] = A[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cB[i][j] = B[i][j];
	printf("матрица A =\n");
	showMatrix(cA, n, n);
	printf("матрица B =\n");
	showMatrix(cB, n, m);
	bool flag = true;
	for (int i = 0; i < n; i++) //проверка на нулевые столбцы
	{
		flag = true;
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] != 0)
				flag = false;
		}
		if (flag)
		{
			printf("Матрица вырожденная, определитель равен 0!");
			return 0;
		}
	}
	float det = 1; //преобразование А и вычисление определителя
	for (int i = 0; i < n; i++)
	{
		int imax = i;
		for (int j = i + 1; j < n; j++)
			if (fabs(A[j][i]) > fabs(A[imax][i]))
				imax = j;

		float eps = 0.0001;
		if (fabs(A[imax][i]) < eps)
		{
			printf("Матрица вырожденная, определитель равен 0!");
			return 0;
		}
		if (i != imax)
		{
			det *= -1;
			for (int j = 0; j < n; j++)
			{
				float temp = A[i][j];
				A[i][j] = A[imax][j];
				A[imax][j] = temp;

				temp = E[i][j];
				E[i][j] = E[imax][j];
				E[imax][j] = temp;
			}
		}

		float t = A[i][i];
		det *= t;
		for (int j = 0; j < n; j++)
		{
			A[i][j] /= t;
			E[i][j] /= t;
		}
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			float d1 = A[j][i];
			for (int k = 0; k < n; k++)
			{
				A[j][k] -= A[i][k] * d1;
				E[j][k] -= E[i][k] * d1;
			}
		}


	}
	printf("det(A) = ");
	printf("%6.2f\n\n", det);
	printf("A^(-1) = \n");
	showMatrix(E, n, n);

}
