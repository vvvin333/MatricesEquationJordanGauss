#include<iostream>
#include<locale>
#include<time.h>
#include <format>

using namespace std;


/// <summary>
/// fill given matrix with random values
/// </summary>
/// <param name="matr">given matrix</param>
/// <param name="n"></param>
/// <param name="m"></param>
void fillingMatrixRandom(float** matr, int n, int m)//заполение матриц А и В рандомными числами
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matr[i][j] = rand() % 100 - 50;
		}
	}
}

void customFilling(float** matr, int n, char matrixName)
{
	printf("Введите матрицу %c :\n", matrixName);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%c[%d][%d] = ", matrixName, i, j);
			scanf_s("%f", &matr[i][j]);
		}
	}
}

void fillingMatrixCopy(float** matr, float** matr1, int n, int m) //копии матриц(заполнение)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matr1[i][j] = matr[i][j];
}

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

float** determinantAndChange(float** A, float** E, int n)//определитель и преобразования
{
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
	printf("%6.2f\n\n", det);

}

float** multiplicationMatrix(float** matr1, int n1, int m1, float** matr2, int n2, int m2) //умножение матриц
{
	if (m1 != n2)
		printf("Ошибка! умножение невозможно!");
	else
	{
		float** s = new float* [n1];
		for (int i = 0; i < n1; i++)
			s[i] = new float[m2];
		float eps = 0.0001;
		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < m2; j++)
			{
				s[i][j] = 0;
				for (int k = 0; k < m1; k++)
					s[i][j] += matr1[i][k] * matr2[k][j];
				if (fabs(s[i][j]) < eps)
					s[i][j] = 0;
			}
		}
		return s;
	}

}

void sumMatrix(float** matr1, int n1, int m1, float** matr2, int n2, int m2)// сложение матриц
{
	if ((n1 != n2) || (m1 != m2))
		printf("Ошибка!Размеры матриц не совпадают!");
	else
	{
		float** sum = new float* [n1];
		for (int i = 0; i < n1; i++)
			sum[i] = new float[m1];
		float eps = 0.0001;
		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < m1; j++)
			{
				sum[i][j] = 0;
				sum[i][j] = matr1[i][j] - matr2[i][j];
				if (fabs(sum[i][j]) < eps)
					sum[i][j] = 0;
				printf("%6.2f\t", sum[i][j]);
			}
			printf("\n");

		}
		printf("\n");
	}
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
	float** X = new float* [n];// создание X
	for (int i = 0; i < n; i++)
		X[i] = new float[m];
	float** T = new float* [n];// создание T
	for (int i = 0; i < n; i++)
		T[i] = new float[m];

	float** E = new float* [n];// создание Единичной
	for (int i = 0; i < n; i++)
	{
		E[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				E[i][j] = 1;
			else
				E[i][j] = 0;
		}
	}

	if (chooseA == 1)
	{
		customFilling(A, n, 'A');
	}
	else
	{
		fillingMatrixRandom(A, n, n);
	}
	if (chooseB == 1)
	{
		customFilling(B, n, 'B');
	}
	else
	{
		fillingMatrixRandom(B, n, m);
	}
	fillingMatrixCopy(A, cA, n, n);
	fillingMatrixCopy(B, cB, n, m);
	printf("матрица A =\n");
	showMatrix(cA, n, n);
	printf("матрица B =\n");
	showMatrix(cB, n, m);
	printf("det(A) =");
	determinantAndChange(A, E, n);
	printf("A^(-1) = \n");
	showMatrix(E, n, n);
	printf("X=A^(-1) * B\n");
	printf("X=\n");
	X = multiplicationMatrix(E, n, n, B, n, m);
	showMatrix(X, n, m);
	printf("Проверка:\n\n");
	printf("A*X =\n");
	showMatrix(multiplicationMatrix(cA, n, n, X, n, m), n, m);
	printf("A*X - B =\n");
	T = multiplicationMatrix(cA, n, n, X, n, m);
	sumMatrix(T, n, m, B, n, m);
	printf("A*A^(-1)=\n");
	showMatrix(multiplicationMatrix(cA, n, n, E, n, n), n, n);
	printf("A^(-1)*A =\n");
	showMatrix(multiplicationMatrix(E, n, n, cA, n, n), n, n);
	for (int i = 0; i < n; i++)
	{
		delete[]A[i];
		delete[]B[i];
		delete[]E[i];
		delete[]cA[i];
		delete[]cB[i];
		delete[]X[i];
		delete[]T[i];
	}
	delete[]A;
	delete[]B;
	delete[]E;
	delete[]cA;
	delete[]cB;
	delete[]X;
	delete[]T;
}