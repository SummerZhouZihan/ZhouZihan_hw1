#include "algebra.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

/**
 *矩阵加法
*/
Matrix add_matrix(Matrix a, Matrix b)
{
    if(a.rows != b.rows || a.cols != b.cols){
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0,0);
    }
    Matrix result;
    result = create_matrix(a.rows,a.cols);
    for(int i=0 ;i < result.rows ; i++){
        for(int j=0;j< result.cols ;j++){
            result.data[i][j] += a.data[i][j]+b.data[i][j];
        }
    }
    return result;
}
/**
 *矩阵减法
*/
Matrix sub_matrix(Matrix a, Matrix b)
{
    if(a.rows != b.rows || a.cols != b.cols){
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0,0);
    }
    Matrix result;
    result = create_matrix(a.rows,a.cols);
    for(int i = 0;i < result.rows ; i++){
        for(int j=0;j < result.cols; j++){
            result.data[i][j] += a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}
/**
 *矩阵乘法
*/
Matrix mul_matrix(Matrix a, Matrix b)
{
    if(a.cols != b.rows){
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0,0);
    }
    Matrix result;
    result = create_matrix(a.rows,b.cols);
    for(int i = 0; i< result.rows ; i++){
        for(int j=0; j < result.cols ;j++){
            for(int k = 0; k < a.cols ;k++){
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}
/**
 *矩阵数乘
*/
Matrix scale_matrix(Matrix a, double k)
{
    Matrix result;
    result = create_matrix(a.rows,a.cols);
    for(int i=0;i < result.rows;i++){
        for(int j=0;j< result.cols;j++){
            result.data[i][j]=k*a.data[i][j];
        }
    }
    return result;
}
/**
 *矩阵转置
 *这个感觉要寄
*/
Matrix transpose_matrix(Matrix *a)
{
    Matrix temp = *a;
    *a = create_matrix(a->cols,a->rows);
    for(int i = 0;i< temp.rows ; i++){
        for(int j =0; j < temp.cols; j++){
            a->data[i][j] = temp.data[i][j];
        }
    }

}


int inversion_number(int *array, int N){
    int res = 0;
    for(int i = 0; i < N - 1; i++){
        for(int j = i + 1; j < N; j++){
            if(array[i] > array[j]){
                res++;
            }
        }
    }
    return res;
}
/**
 *这是在数组中查找指定元素
 *找到返回true，找不到返回false
*/
int find(int *array,int N , int value){
    for(int i = 0; i < N; i++){
        if(value == array[i]){
            return 1;
        }
    }
    return 0;
}
/**
 *计算行列式的辅助函数
 *res用于保存行列式的值，m保存矩阵，i记录当前行，j记录当前列，cols记录哪些列已被选择
 *使用了递归
*/
void dfs(float *res,Matrix m ,int i ,int j ,int *cols){
    if(i == m.rows){
        float temp = 1;
        for(int k = 0; k < m.rows; k++){
            temp = temp * m.data[k][cols[k]];
        }
        *res = *res + pow(-1, inversion_number(cols, m.rows)) * temp;
    }

    for(int p = 0; p < m.cols; p++){
        if(!find(cols, i, p)){
            cols[i] = p;
            dfs(res, m, i + 1, 0, cols);
        }
    }
}

/**
 *行列式
 *我引进了三个辅助函数
 *良好的精神状态，我要爆炸了
*/
double det_matrix(Matrix a) {
    if(a.rows != a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    float res = 0;
    int *cols = (int *)malloc(sizeof(int)*a.rows);
    for(int k=0;k < a.rows;k++){
        cols[k] = 0;
    }
    for(int k = 0;k< a.rows ; k++){
        cols[0] = k;
        dfs(&res, a , 1 , 0 , cols);
    }
    return res;
}

/**
 *余子式
 *这里默认是方阵
*/
float confactor(Matrix m, int i, int j){
    Matrix remains;
    remains = create_matrix(m.rows - 1, m.cols - 1);
    for(int p = 0; p < remains.rows; p++){
        for(int q = 0; q < remains.cols; q++){
            if(p < i && q < j){
                remains.data[p][q] = m.data[p][q];
            }
            else if(p < i && q >= j){
                remains.data[p][q] = m.data[p][q + 1];
            }
            else if(p >= i && q < j){
                remains.data[p][q] = m.data[p + 1][q];
            }
            else if(p >= i && q >= j){
                remains.data[p][q] = m.data[p + 1][q + 1];
            }
        }
    }
    return det_matrix(remains);
}

/**
 *代数余子式
*/
float algebraic_confactor(Matrix m, int i, int j){  
    return confactor(m, i, j)*pow(-1, i+j);
}

/**
 *逆矩阵
 *当a不是方阵或者
*/
Matrix inv_matrix(Matrix a)
{
    if(a.cols != a.rows){
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0,0);
    }else if (det_matrix(a) == 0 ){
        printf("Error: The matrix is singular.\n");
        return create_matrix(0,0);
    }
    Matrix res;
    res = create_matrix(a.rows,a.cols);
    for(int i=0; i<=res.rows ; i++){
        for(int j=0; j < res.cols ;j++){
            res.data[i][j] = algebraic_confactor(a, j, i) / det_matrix(a);
        }
    }
    return res;
}

/*
 *交换两行
*/
void row_trans_swap(Matrix *m, int i, int j){
    float temp;
    for(int k = 0; k < m->cols; k++){
        temp = m->data[i][k];
        m->data[i][k] = m->data[j][k];
        m->data[j][k] = temp;
    }
}

/**
 *两行相减
 *存在浮点数的精度问题
 *__FLT_EPSILON__表示浮点数所能识别的最小值
*/
void row_trans_sub(Matrix *m, int i, int j, float multiple){
    for(int k = 0; k < m->cols; k++){
        m->data[i][k] -= m->data[j][k] * multiple;
        if(fabs(m->data[i][k]) < __FLT_EPSILON__){
            m->data[i][k] = 0;
        }
    }
}

/**
 *交换两列
*/
void col_trans_swap(Matrix *m, int i, int j){
    float temp;
    for(int k = 0; k < m->cols; k++){
        temp = m->data[k][i];
        m->data[k][i] = m->data[k][j];
        m->data[k][j] = temp;
    }
}

/**
 * 两列相减
*/
void col_trans_sub(Matrix *m, int i , int j ,float multiple){
    for(int k = 0;k < m->cols; k++){
        m->data[k][i] -= m->data[k][j] * multiple;
        if(fabs(m->data[k][i])< __FLT_EPSILON__){
            m->data[k][i] = 0;
        }
    }
}

/**
 *把矩阵通过变换行，转化为阶梯型
*/
void row_echelon(Matrix *m){
    int i=0;
    int j=0;

    if(m->rows < m->cols){
        transpose_matrix(m);
    }
    while (i < m->rows && j< m->cols){
        /**
         *如果首位不是0的情况，希望把它变成1
        */
        if (m->data[i][j] !=0){
            float divisor = m->data[i][j];
            for(int k=j;k < m->cols;k++){
                m->data[i][k] /= divisor;
                if(fabs(m->data[i][k]) < __FLT_EPSILON__){
                    m->data[i][k] = 0;
                }
            }
            for(int k = i +1;k < m->rows;k++){
                row_trans_sub(m,k,i,m->data[k][j]);
            }
            i++;
            j++;
        }
        else{
            int k;
            /**
             *向下寻找不为0的项
            */
            for (k = i + 1 ;k < m->rows; k++ ){
                if(m->data[k][j] != 0 ){
                    break;
                }
            }
            /**
             * 在这一列中不存在，到下一列去寻找
            */
            if(k >= m->rows){
                j++;
                continue;
            }
            /**
             * 存在这样的行k，就交换i行和k行
            */
            row_trans_swap(m,i,k);
            float divisor = m->data[i][j];
            for(int k=j;k < m->cols;k++){
                m->data[i][k] /= divisor;
                if(fabs(m->data[i][k]) < __FLT_EPSILON__){
                    m->data[i][k] = 0;
                }
            }
            for(int k = i +1;k < m->rows;k++){
                row_trans_sub(m,k,i,m->data[k][j]);
            }
            i++;
            j++;

        }
        


    }
    {
        /* code */
    }
    
}

/**
 *矩阵的秩 
 *天哪要用高斯消元.哎呦我吐了
 *首先将矩阵转化为行阶梯型，再寻找对角线有多少不为0的数
*/
int rank_matrix(Matrix a)
{
    row_echelon(&a);
    int i=0;
    int j=0;
    while(i < a.rows && j < a.cols){
        if(a.data[i][j] == 0){
            break;
        }
        i++;
        j++;
    }
    return i;
}
/*
 *矩阵的迹
*/
double trace_matrix(Matrix a)
{
    if(a.cols != a.rows){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    double result=0.0;
    int i=0;
    int j=0;
    while(i < a.rows && j < a. cols){
        result += a.data[i][j];
        i++;
        j++;
    }
    return result;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}