#include "Task.h"
#include <iostream>

using namespace std;

int main() {	
	cout << "Base task" << endl << endl;

	int m, n;
	cout << "Enter a row count ";
	cin >> m;
	cout << "Enter a column count ";
	cin >> n;
	double **matrix1 = new double*[m];
	for (int i = 0; i < n; i++)
		matrix1[i] = new double[n];

	cout << "Enter matrix" << endl;
	for (int i = 0; i < m; i++) {
		cout << i << " row" << endl;
		for (int j = 0; j < n; j++) {
			cin >> matrix1[i][j];			
		}		
	}

	cout << "Min:" << min_base_task(matrix1, m, n) << endl;
	cout << "Prod:" << prod_base_task(matrix1, m, n) << endl;



	cout << endl << "Medium task" << endl << endl;

	int k;
	cout << "Enter n from n*n matrix size ";
	cin >> k;	
	double **matrix2 = new double*[k];
	for (int i = 0; i < n; i++)
		matrix2[i] = new double[k];

	cout << "Enter matrix" << endl;
	for (int i = 0; i < k; i++) {
		cout << i << " row" << endl;
		for (int j = 0; j < k; j++) {
			cin >> matrix2[i][j];
		}
	}

	cout << "Max:" <<max_medium_task(matrix2, k) << endl;
	cout << "Sum:" << sum_medium_task(matrix2, k) << endl;

	return 0;
}