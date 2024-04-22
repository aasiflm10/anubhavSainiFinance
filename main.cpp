#include <bits/stdc++.h>

using namespace std;

double sum(double a , double b){
    return a+b;
}

vector<vector<double>> getTranspose(vector<vector<double>>& matrix) {
    int m = matrix.size(); 
    int n = matrix[0].size();
        vector<vector<double>>arr(n,vector<double>(m,0));
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++)
        arr[j][i] = matrix[i][j];
    } 
    return arr;
}

// vector<vector<double>> multiplyMat(vector<vector<double>> &mat1, vector<vector<double>> &mat2)
// {
//     double R1 = mat1.size();
//     double R2 = mat2.size();
//     double C1 = mat1[0].size();
//     double C2 = mat2[0].size();
//     vector<vector<double>> rslt(R1, vector<double>(C2, 0));

//     for (double i = 0; i < R1; i++) {
//         for (double j = 0; j < C2; j++) {
//             rslt[i][j] = 0;

//             for (double k = 0; k < R2; k++) {
//                 rslt[i][j] += mat1[i][k] * mat2[k][j];
//             }
//         }
//     }

//     cout << "Multiplication of given two matrices is:\n";
//     for(double i = 0 ; i < R1; ++i)
//     {
//         for(double j = 0  ; j < C2; ++j)
//         {
//             cout<<rslt[i][j] << " ";
//         }
//         cout<<'\n';
//     }

//     return rslt;
// }

vector<vector<double>> multiplyMat(const vector<vector<double>>& mat1, const vector<vector<double>>& mat2) {
    int m = mat1.size();
    int n = mat1[0].size();
    int z = mat2[0].size();
    
    vector<vector<double>> result(m, vector<double>(z, 0));

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < z; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

double determinant2x2(double a, double b, double c, double d) {
    return a * d - b * c;
}

// Function to calculate the cofactor of a 3x3 matrix
double cofactor(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return a * determinant2x2(e, f, h, i) -
           b * determinant2x2(d, f, g, i) +
           c * determinant2x2(d, e, g, h);
}

// Function to find the inverse of a 3x3 matrix
vector<vector<double>> inverse3x3(vector<vector<double>>& matrix) {
    double det = cofactor(matrix[0][0], matrix[0][1], matrix[0][2],
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


vector<vector<double>> getBetaCapValues(vector<vector<double>> &matrix, vector<vector<double>> &y)
{
    vector<vector<double>> transpose = getTranspose(matrix);
    vector<vector<double>> newMatrix = multiplyMat(transpose, matrix);

    vector<vector<double>> inverse = inverse3x3(newMatrix);

    vector<vector<double>> inverseXtranspose = multiplyMat(inverse, transpose);

    vector<vector<double>> betaCapvalues = multiplyMat(inverseXtranspose, y);
    
    return betaCapvalues;
}

void printFun(vector<vector<double>>& matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < m ; ++j)
        {
            cout<<matrix[i][j] << "  ";
        }
        cout<<'\n';
    }
}

double getfinalAns(vector<vector<double>>& betaCap, vector<double>& arr)
{
    int n = arr.size();
    double finalAns = 0 ;
    for(int i = 0 ; i<n ; ++i)
    {
        finalAns += (betaCap[i][0]*arr[i]);
    }
    return finalAns;
}
int main() {

    //take 3*3 inputs
    int n = 0;
    cout<<"Enter the value of n: \n";
    cin>>n;
    vector<vector<double>> matrix(n ,vector<double>(n,0));

    cout<<"enter the values of matrix : \n";
    for(double i = 0 ; i < n ; ++i)
    {
        for(double j = 0 ; j < n ; ++j)
        {
            cin>>matrix[i][j];
        }
    }

    cout<<"The input you provided for the matrix is : \n";
    printFun(matrix);

    vector<vector<double>> y(n, vector<double>(1,0));
    cout<<"Enter the values of y (y is stock values):\n";
    for(double i  = 0 ; i < n ; ++i)
    {
        cin>>y[i][0];
    }
    cout<<"The input you provided for the y is : \n";
    printFun(y);

    vector<vector<double>> betaCap = getBetaCapValues(matrix, y);
    cout<<"BetaCap values are as follows\n";
    printFun(betaCap);

    vector<double> lastRow = matrix[2];
    double ans = getfinalAns(betaCap, lastRow);

    cout<<"The final Ans is : "<<ans<<'\n';
    return 0;
}