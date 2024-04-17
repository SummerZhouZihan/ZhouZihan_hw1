#ifndef ALGEBRA_H
#define ALGEBRA_H

#define MAX_MATRIX_SIZE 100

typedef struct Matrix {
    int rows; // 矩阵的行数
    int cols; // 矩阵的列数
    double data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];  // 矩阵的数据
} Matrix;

/**
 * @brief 创建矩阵
 * @param rows 矩阵的行数
 * @param cols 矩阵的列数
 * @return 初始化后的矩阵
*/
Matrix create_matrix(int rows, int cols);

/**
 * @brief 矩阵加法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a + b, 如果a和b的行数或列数不相等，会给出错误提示"Error: Matrix a and b must have the same rows and cols.\n"并返回一个空矩阵
*/
Matrix add_matrix(Matrix a, Matrix b);

/**
 * @brief 矩阵减法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a - b，如果a和b的行数或列数不相等，会给出错误提示"Error: Matrix a and b must have the same rows and cols.\n"并返回一个空矩阵
*/
Matrix sub_matrix(Matrix a, Matrix b);

/**
 * @brief 矩阵乘法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a * b，如果a的列数不等于b的行数，会给出错误提示"Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n"并返回一个空矩阵
*/
Matrix mul_matrix(Matrix a, Matrix b);

/**
 * @brief 矩阵数乘
 * @param a 矩阵a
 * @param k 数k
 * @return a * k
*/
Matrix scale_matrix(Matrix a, double k);

/**
 * @brief 矩阵转置
 * @param a 矩阵a
 * @return a的转置矩阵
*/


Matrix transpose_matrix(Matrix *a);

int inversion_number(int *array, int N);
/**
 *这是在数组中查找指定元素
 *找到返回true，找不到返回false
*/

int find(int *array,int N , int value);

/**
 *计算行列式的辅助函数
*/
void dfs(float *res,Matrix m ,int i ,int j ,int *cols);

/**
 * @brief 矩阵的行列式
 * @param a 矩阵a
 * @return a的行列式, 如果a不是方阵，会给出错误提示"Error: The matrix must be a square matrix.\n"并返回0
*/
double det_matrix(Matrix a);


/*
 *余子式
*/
float confactor(Matrix m, int i, int j);


/*
 *代数余子式
*/
float algebraic_confactor(Matrix m, int i, int j);


/**
 * @brief 矩阵的逆
 * @param a 矩阵a
 * @return a的逆矩阵, 如果a不是方阵或a的行列式为0，会给出错误提示"Error: The matrix must be a square matrix.\n"并返回一个空矩阵，如果a的逆矩阵不存在，会给出错误提示"Error: The matrix is singular.\n"并返回一个空矩阵。
*/
Matrix inv_matrix(Matrix a);


/*
 *交换两行
*/
void row_trans_swap(Matrix *m, int i, int j);

/**
 *两行相减
*/
void row_trans_sub(Matrix *m, int i, int j, float multiple);

/**
 *把矩阵通过变换行，转化为阶梯型
*/
void row_echelon(Matrix *m);

/**
 *交换两列
*/
void col_trans_swap(Matrix *m, int i, int j);

/**
 * 两列相减
*/
void col_trans_sub(Matrix *m, int i , int j ,float multiple);

/**
 * @brief 矩阵的秩
 * @param a 矩阵a
 * @return a的秩
*/
int rank_matrix(Matrix a);

/**
 * @brief 矩阵的迹
 * @param a 矩阵a
 * @return a的迹，如果a不是方阵，会给出错误提示"Error: The matrix must be a square matrix.\n"并返回0
*/
double trace_matrix(Matrix a);

/**
 * @brief 打印矩阵，格式为：按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
 * @param a 矩阵a
*/
void print_matrix(Matrix a);

#endif