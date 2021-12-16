#include <iostream>
using namespace std;

void main()
{
	int colPos, rowPos;
	int i, j, k, razm;
	double max;
	double temp;
	int m_nCols;
	int m_nRows;
	double** array;
	double* parray;
	unsigned int* ListVar;
	double* x;
	cout << "Enter size N: ";
	cin >> razm;
	cout << "Enter elements:\n";

	m_nRows = razm;
	m_nCols = m_nRows + 1;
	parray = new double[m_nRows * m_nCols];
	array = new double* [m_nRows];
	for (i = 0; i < m_nRows; i++)
	{
		*(array + i) = parray + i * m_nCols;
	}

	ListVar = new unsigned int[m_nCols - 1];
	for (j = 0; j < m_nCols - 1; j++)
		ListVar[j] = j + 1;

	x = new double[razm];

	for (i = 0; i < m_nRows - 1; i++)
		x[i] = i + 1;

	for (i = 0; i < razm; i++)
		for (j = 0; j < (razm + 1); j++)
			cin >> array[i][j];
	for (k = 0; k < m_nRows - 1; k++)
	{
		colPos = rowPos = k;
		max = array[k][k];
		for (i = k; i < m_nRows; i++)
			for (j = k + 1; j < m_nCols - 1; j++)
				if (abs(array[i][j]) > max)
				{
					max = array[i][j];
					rowPos = i;
					colPos = j;
				}

		for (i = 0; i < m_nRows; i++)
		{
			temp = array[i][k];
			array[i][k] = array[i][colPos];
			array[i][colPos] = temp;
		}

		for (j = 0; j < m_nCols; j++)
		{
			temp = array[k][j];
			array[k][j] = array[rowPos][j];
			array[rowPos][j] = temp;
		}

		temp = ListVar[k];
		ListVar[k] = ListVar[colPos];
		ListVar[colPos] = temp;

		for (j = m_nCols - 1; j >= 0; j--)
		{
			array[k][j] /= array[k][k];

		}
		for (j = 0; j < m_nCols; j++)
			array[k][j];
		for (i = k + 1; i < m_nRows; i++)
			for (j = m_nCols - 1; j >= 0; j--)
				array[i][j] -= array[k][j] * array[i][k];
	}

	double s = 0;
	x[m_nRows - 1] = array[m_nRows - 1][m_nCols - 1] /
		array[m_nRows - 1][m_nCols - 2];
	for (i = m_nRows - 2; i >= 0; i--)
	{
		s = 0;
		for (k = i + 1; k < m_nRows; k++)
			s += array[i][k] * x[k];
		x[i] = array[i][m_nCols - 1] - s;
	}
	cout << "Solution:\n";
	for (i = 0; i < m_nRows; i++)
		cout << "X" << i + 1 << "=" << x[i] << endl;
}