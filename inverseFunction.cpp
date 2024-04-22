#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the determinant of a 2x2 matrix
int determinant2x2(int a, int b, int c, int d) {
    return a * d - b * c;
}

// Function to calculate the cofactor of a 3x3 matrix
int cofactor(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a * determinant2x2(e, f, h, i) -
           b * determinant2x2(d, f, g, i) +
           c * determinant2x2(d, e, g, h);
}

// Function to find the inverse of a 3x3 matrix
vector<vector<double>> inverse3x3(vector<vector<double>>& matrix) {
    int det = cofactor(matrix[0][0], matrix[0][1], matrix[0][2],
                       matrix[1][0], matrix[1][1], matrix[1][2],
                       matrix[2][0], matrix[2][1], matrix[2][2]);

    if (det == 0) {
        cout << "Matrix is singular, inverse does not exist." << endl;
        exit(1);
    }

    vector<vector<double>> inverse(3, vector<double>(3));
    inverse[0][0] = determinant2x2(matrix[1][1], matrix[1][2], matrix[2][1], matrix[2][2]) / double(det);
    inverse[0][1] = -determinant2x2(matrix[0][1], matrix[0][2], matrix[2][1], matrix[2][2]) / double(det);
    inverse[0][2] = determinant2x2(matrix[0][1], matrix[0][2], matrix[1][1], matrix[1][2]) / double(det);
    inverse[1][0] = -determinant2x2(matrix[1][0], matrix[1][2], matrix[2][0], matrix[2][2]) / double(det);
    inverse[1][1] = determinant2x2(matrix[0][0], matrix[0][2], matrix[2][0], matrix[2][2]) / double(det);
    inverse[1][2] = -determinant2x2(matrix[0][0], matrix[0][2], matrix[1][0], matrix[1][2]) / double(det);
    inverse[2][0] = determinant2x2(matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]) / double(det);
    inverse[2][1] = -determinant2x2(matrix[0][0], matrix[0][1], matrix[2][0], matrix[2][1]) / double(det);
    inverse[2][2] = determinant2x2(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]) / double(det);

    return inverse;
}

// Function to print a matrix
void printMatrix(vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<double>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 2, 9}};
    
    vector<vector<double>> inverse = inverse3x3(matrix);
    
    cout << "Original matrix:" << endl;
    printMatrix(matrix);
    
    cout << "\nInverse matrix:" << endl;
    printMatrix(inverse);
    
    return 0;
}
