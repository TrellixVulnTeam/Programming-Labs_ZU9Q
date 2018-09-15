#include "Task.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {	
	cout << "Base task" << endl << endl;

	int m, n;
	cout << "Enter a row count ";
	cin >> m;
	cout << "Enter a column count ";
	cin >> n;
	double **matrix1 = new double*[m];
	for (int i = 0; i < m; i++)		
		matrix1[i] = new double[n];

	cout << "Enter matrix" << endl;
	for (int i = 0; i < m; i++) {
		cout << i + 1 << " row" << endl;
		for (int j = 0; j < n; j++) {
			cin >> matrix1[i][j];
		}		
	}

	cout << "Min:" << min_base_task(matrix1, m, n) << endl;
	cout << "Prod:" << prod_base_task(matrix1, m, n) << endl;
	for (int i = 0; i < n; i++)
		delete[] matrix1[i];	
	delete[] matrix1;


	cout << endl << "Medium task" << endl << endl;

	int k;
	cout << "Enter n from n*n matrix size ";
	cin >> k;	
	double **matrix2 = new double*[k];
	for (int i = 0; i < k; i++)
		matrix2[i] = new double[k];

	cout << "Enter matrix" << endl;
	for (int i = 0; i < k; i++) {
		cout << i + 1 << " row" << endl;
		for (int j = 0; j < k; j++) {
			cin >> matrix2[i][j];
		}
	}

	cout << "Max:" <<max_medium_task(matrix2, k) << endl;
	cout << "Sum:" << sum_medium_task(matrix2, k) << endl;
	for (int i = 0; i < k; i++)
		delete[] matrix2[i];
	delete[] matrix2;


	cout << endl << "Hard task" << endl;	

	srand(time(NULL));
	double **matrix3_1 = new double*[20];
	for (int i = 0; i < 20; i++)
		matrix3_1[i] = new double[20];
	for (int i = 0; i < 20; i++) {		
		for (int j = 0; j < 20; j++) {			
			matrix3_1[i][j] = rand() % 255 + 1;
		}
	}	

	double **matrix3_2 = new double*[2000];
	for (int i = 0; i < 2000; i++)
		matrix3_2[i] = new double[2000];
	for (int i = 0; i < 2000; i++) {
		for (int j = 0; j < 2000; j++) {
			matrix3_2[i][j] = 1 + rand() % 255;
		}
	}

	cout << matrix3_1[0][0] << endl;
	cout << matrix3_1[0][1] << endl;
	cout << matrix3_1[0][2] << endl;
	cout << matrix3_1[1][0] << endl;
	cout << matrix3_1[1][1] << endl;
	cout << matrix3_1[1][2] << endl;
	cout << matrix3_1[2][0] << endl;	
	cout << matrix3_1[2][1] << endl;
	cout << matrix3_1[2][2] << endl;
	cout << "Sobel20" << endl;
	auto sobel20 = grad_hard_task(matrix3_1, 20, 20);
	for (int i = 0; i < 20; i++) {
		cout << "Row " << i + 1 << endl;
		for (int j = 0; j < 20; j++) {
			cout << sobel20[i][j] << endl;
		}
	}

	cout << endl << "Sobel2000" << endl;
	auto sobel2000 = grad_hard_task(matrix3_2, 2000, 2000);
	/*for (int i = 0; i < 2000; i++) {
		cout << "Row " << i + 1 << endl;
		for (int j = 0; j < 2000; j++) {
			cout << sobel2000[i][j] << endl;
		}
	}*/
	
	for (int i = 0; i < 20; i++)
		delete[] matrix3_1[i];	
	delete[] matrix3_1;
	for (int i = 0; i < 20; i++)
		delete[] sobel20[i];
	delete[] sobel20;
	for (int i = 0; i < 2000; i++)
		delete[] matrix3_2[i];	
	delete[] matrix3_2;
	/*for (int i = 0; i < 20; i++)
		delete[] sobel2000[i];
	delete[] sobel2000;*/

	return 0;
}