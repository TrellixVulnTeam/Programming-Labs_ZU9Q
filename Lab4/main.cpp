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
	double **matrix = new double*[m];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];

	cout << "Enter matrix" << endl;
	for (int i = 0; i < m; i++) {
		cout << i << " row" << endl;
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];			
		}		
	}

	cout << "Min:" << min_base_task(matrix, m, n) << endl;
	cout << "Prod:" << prod_base_task(matrix, m, n) << endl;


	cout << endl << "Medium task" << endl << endl;

	int k;
	cout << "Enter n from n*n matrix size ";
	cin >> k;


	cout << "Max:" <<max_medium_task() << endl;
	cout << "Sum:" << sum_medium_task() << endl;

	return 0;
}