#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateMatrix(vector<vector<int>> &matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 10; 
        }
    }
}

void printMatrix(const vector<vector<int>> &matrix) {
    for (const auto &row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, int M, int N, int X) {
    vector<vector<int>> C(M, vector<int>(X, 0));
    
    for (int i = 0; i < M; ++i) {        
        for (int j = 0; j < X; ++j) {    
            for (int k = 0; k < N; ++k) { 
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main() {
    srand(time(0)); 

    int M = 3, N = 3, X = 3; 
    
    vector<vector<int>> A(M, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(X));
    
    generateMatrix(A, M, N);
    generateMatrix(B, N, X);
    
    cout << "Matriz A:" << endl;
    printMatrix(A);
    
    cout << "\nMatriz B:" << endl;
    printMatrix(B);
    
    vector<vector<int>> C = multiplyMatrices(A, B, M, N, X);
    
    cout << "\nMatriz C (Resultado):" << endl;
    printMatrix(C);
    
    return 0;
}