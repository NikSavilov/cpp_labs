#include <iostream>
#include <fstream>

using namespace std;
class Matrix {
private:
    int **matrix_;
    int i_, j_;
public:
    // Constructor
    Matrix(int X, int Y, int default_n){
        i_ = X;
        j_ = Y;
        matrix_ = new int*[i_];
        for ( int h = 0; h < i_; h++){
            matrix_[h] = new int[j_];
        }
        for (int s = 0; s < i_; s++){
            for ( int h = 0; h < j_; h++){
                matrix_[s][h] = default_n;
            }
        }
    }
    // Copy constructor
    Matrix(const Matrix &obj){
        i_ = obj.i_;
        j_ = obj.j_;
        matrix_ = new int*[i_];
        for ( int h = 0; h < i_; h++){
            matrix_[h] = new int[j_];
        }
        for ( int s = 0; s < i_; s++){
            for ( int h = 0; h < j_; h++){
                matrix_[s][h] = obj.matrix_[s][h];
            }
        }
    }
    // Var
    int i() const {
        return i_;
    }
    int j() const {
        return j_;
    }
    int *matrix(int i, int j) const {
        return &matrix_[i][j];
    }
    // Printer
    void PrintMatrix(){
        for (int s = 0; s < i_; s++){
            for ( int h = 0; h < j_; h++){
                cout << matrix_[s][h] << ' ';
            }
            cout << endl;
        }
    }
    // Reload
    Matrix&operator += (const Matrix &matrix2){
        for (int s = 0; s < i_; s++){
            for (int h = 0; h < j_; h++){
                this->matrix_[s][h] = this->matrix_[s][h] + *matrix2.matrix(s,h);
            }
        }
        return *this;
    }
    Matrix&operator += (int number){
        for (int s = 0; s < i_; s++){
            for (int h = 0; h < j_; h++){
                this->matrix_[s][h] += number;
            }
        }
        return *this;
    }
    Matrix&operator -= (const Matrix &matrix2){
        for (int s = 0; s < i_; s++){
            for (int h = 0; h < j_; h++){
                this->matrix_[s][h] -= *matrix2.matrix(s,h);
            }
        }
        return *this;
    }
    Matrix&operator -= (int number){
        for (int s = 0; s < i_; s++){
            for (int h = 0; h < j_; h++){
                this->matrix_[s][h] -= number;
            }
        }
        return *this;
    }
    Matrix operator + (int num) {
        Matrix tmp(*this);
        tmp += num;
        tmp.i_ = this->i_;
        tmp.j_ = this->j_;
        return tmp;
    }
    Matrix operator + (const Matrix &matrix2){
        Matrix tmp(*this);
        tmp.i_ = matrix2.i_;
        tmp.j_ = matrix2.j_;
        for (int s = 0; s < tmp.i_; s++){
            for (int h = 0; h < tmp.j_; h++){
                tmp.matrix_[s][h] += matrix2.matrix_[s][h];
            }
        }
        return tmp;
    }
    Matrix operator = (const Matrix &obj){
        for (int s = 0; s < obj.i_; s++){
            for (int h = 0; h < obj.j_; h++){
                this->matrix_[s][h] = obj.matrix_[s][h];
            }
        }
        this->i_ = obj.i_;
        this->j_ = obj.j_;
    }
    int operator = (const int num) {
        *this = num;
    }
    Matrix T(){
        Matrix tmp(this->j(),this->i(),0);
        for (int i = 0; i < tmp.i(); i++)
            for (int j = 0; j < tmp.j(); j++)
            {
                *tmp.matrix(i,j) = *this->matrix(j,i);
            }
        return tmp;
    }
    Matrix operator * (const Matrix &obj2){
        Matrix tmp(this->i(),obj2.j(),0);
        for (int row = 0; row < obj2.i(); row++) {
            for (int col = 0; col < obj2.j(); col++) {
                for (int s = 0; s < this->j(); s++){
                    *tmp.matrix(row,col) += *this->matrix(row,s) * *obj2.matrix(s,col);
                }
            }
        }
        return tmp;
    }
    ~Matrix(){
        /*хз чо не работает
        for (int h = 0; h < i_; h++){
            delete(matrix_[h]);
        }
        delete(matrix_);*/
    }
};
std::istream& operator>>(std::istream& is, Matrix& obj)
{
    int i, j;
    is >> i >> j;
    if (i != obj.i() or j != obj.j()){
        cout << "Reading error." << endl;
        return is;
    }
    for (int row = 0; row < obj.i(); row++) {
        for (int col = 0; col < obj.j(); col++) {
            is >> *obj.matrix(row,col);
        }
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, Matrix& obj)
{
    for (int row = 0; row < obj.i(); row++) {
        for (int col = 0; col < obj.j(); col++) {
            os << *obj.matrix(row,col) << " ";
        }
        os << endl;
    }
    return os;
}

int main() {
    string path = "matrix.txt";
    Matrix matrix1 = Matrix(3,3,1); // create matrix using file
    Matrix matrix2 = Matrix(3,3,1);

    cout << "-------  m1 -------" << endl;
    matrix1.PrintMatrix(); // check if matrix's been read normally

    matrix1 += 6;
    cout << "-------  m1 +=6  -------" << endl;
    matrix1.PrintMatrix();

    Matrix matrix3(matrix1);
    matrix3 = matrix1 + 3;
    cout << "------- m3 = m1 + 3 -------" << endl;
    matrix3.PrintMatrix();

    matrix2 = matrix1 + matrix3;
    cout << "-------  m2 = m1 + m3 -------" << endl;
    matrix2.PrintMatrix();

    *matrix1.matrix(2,1) = 3;
    matrix1.PrintMatrix();

    matrix1.T().PrintMatrix();

    (matrix1.T() * matrix1).PrintMatrix();

    ifstream is("matrix.txt");
    is >> matrix1;
    cout << matrix1;


    //matrix1.~Matrix(); // destruct matrix
    //matrix2.~Matrix(); // destruct matrix
    return 0;
}