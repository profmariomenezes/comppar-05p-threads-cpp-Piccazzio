#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

void matrix_multiply_blocking(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int block_size) {
    int n = A.size(); 

    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                for (int ii = i; ii < min(i + block_size, n); ++ii) {
                    for (int jj = j; jj < min(j + block_size, n); ++jj) {
                        for (int kk = k; kk < min(k + block_size, n); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

void generate_matrix(vector<vector<int>>& matrix, int n) {
    matrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100;  
        }
    }
}

void print_matrix(const vector<vector<int>>& matrix, int n) {
    int limit = min(n, 10);  
    for (int i = 0; i < limit; ++i) {
        for (int j = 0; j < limit; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    if (n > 10) {
        cout << "..." << endl;  
    }
}

int main() {
    int n = 512; 
    int block_size = 32; 
    
    vector<vector<int>> A, B, C;

    generate_matrix(A, n);
    generate_matrix(B, n);
    C.resize(n, vector<int>(n, 0));  

    cout << "Matriz A :" << endl;
    print_matrix(A, n);
    cout << "Matriz B :" << endl;
    print_matrix(B, n);

    auto start = chrono::high_resolution_clock::now();
    matrix_multiply_blocking(A, B, C, block_size);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Tempo de execução sem otimização: " << duration.count() << " segundos." << endl;

    cout << "Matriz C (resultado da multiplicação):" << endl;
    print_matrix(C, n);

    start = chrono::high_resolution_clock::now();
    matrix_multiply_blocking(A, B, C, block_size);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Tempo de execução com otimização máxima: " << duration.count() << " segundos." << endl;

    cout << "Matriz C (resultado da multiplicação com otimização):" << endl;
    print_matrix(C, n);

    return 0;
}