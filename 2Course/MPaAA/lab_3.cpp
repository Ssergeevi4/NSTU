/* Написать параллельную программу умножения квадратных матриц . В таблице отобразить ускорение и норму матрицы  при использовании различного числа потоков. 
 */
#include <omp.h> 
#include <iostream> 
#include <locale.h> 
#include <Windows.h> 
#include <fstream> 
#include <limits.h> 
#include <ctime> 
 
using namespace std; 
const int N = 2500; 
 
double* parallel(double A[], double B[], double C[], double& time) 
{ 
   int n = 2; // Число потоков 
   int j = 0, p = 0 
   omp_set_num_threads(n); 
   unsigned int start_time = clock(); 
#pragma omp parallel for private(j, p) 
   for (int i = 0; i < N; i++) 
   { 
      for (j = 0; j < N; j++) 
      { 
         for (p = 0; p < N; p++) 
         { 
            C[i + j * N] += A[i + p * N] * B[p + j * N]; 
         } 
      } 
   } 
 
   unsigned int end_time = clock(); 
   time = end_time - start_time; 
   return C; 
} 
 
double* consistent(double A[], double B[], double C[], double& time) 
{ 
   unsigned int start_time = clock(); 
   for (unsigned int i = 0; i < N; i++) 
   { 
      for (unsigned int j = 0; j < N; j++) 
      { 
         for (unsigned int p = 0; p < N; p++) 
         { 
            C[i + j * N] += A[i + p * N] * B[p + j * N]; 
         } 
      } 
   } 
 
   unsigned int end_time = clock(); 
   time = end_time - start_time; 
   return C; 
} 
 
double norma_matric(double C[], double& norma) 
{ 
   for (unsigned int i = 0; i < N; i++) 
   { 
      for (unsigned int j = 0; j < N; j++) 
      { 
         norma += C[i + j * N] * C[i + j * N]; 
      } 
   } 
   norma = sqrt(norma); 
   return norma; 
} 
 
void main() 
{ 
   setlocale(LC_ALL, ""); 
   double* A = new double[N * N]; 
   double* B = new double[N * N]; 
   double* C = new double[N * N]; 
   unsigned int z = 0; 
   for (unsigned int i = 0; i < N; i++) 
   { 
      for (unsigned int j = 0; j < N; j++) 
      { 
         A[i + j * N] = z; 
         B[j + i * N] = z; 
         C[i + j * N] = 0; 
         z++; 
      } 
   } 
 
   double time_parallel = 0, time_consistent = 0, norma_parallel = 0, norma_consistent = 0; 
   cout << "Параллельная версия" << '\n'; 
   C = parallel(A, B, C, time_parallel); 
   norma_parallel = norma_matric(C, norma_parallel); 
   cout << "Затраченное время: " << time_parallel << '\n' << "Норма матрицы: " << norma_parallel; 
   for (unsigned int i = 0; i < N * N; i++) 
      C[i] = 0; 
   cout << '\n' << '\n' << "Последовательная версия" << '\n'; 
   C = consistent(A, B, C, time_consistent); 
   norma_consistent = norma_matric(C, norma_consistent); 
   cout << "Затраченное время: " << time_consistent << '\n' << "Норма матрицы: " << norma_consistent; 
   double uskor = time_consistent / time_parallel; 
   cout << '\n' << '\n' << "Ускорение: " << uskor; 
   system("pause"); 
} 
 
 /*
Параллельное решение СЛАУ с верхнетреугольной матрицей. Дана треугольная матрица  и вектор . Диагональные элементы матрицы  должны быть положительны и по модулю должны превосходить соответствующие внедиагональные элементы. Вектор правой части  получить умножением матрицы  на вектор  (для этого использовать последовательную версию программы матрично-векторного умножения). Далее запустить программу решения СЛАУ с верхнетреугольной матрицей  в последовательном и параллельном режиме (с различным числом потоков). Вывести в файл компоненты векторов  и . Убедиться, что они совпадают. В таблице необходимо отобразить ускорение и сравнивать норму полученного вектора решения  с нормой исходного вектора . 
 
 */
#include <omp.h> 
#include <iostream> 
#include <locale.h> 
#include <Windows.h> 
#include <fstream> 
#include <limits.h> 
#include <ctime> 
 
using namespace std; 
const int N = 2500; 
 
LONG64* umnozheniye_matritsy_na_vektor_consistent(double U[], double x[], LONG64 b[]) 
{ 
   for (unsigned int i = 0; i < N; i++) 
   { 
      b[i] = 0; 
      for (unsigned int j = 0; j < N; j++) 
      { 
         b[i] += U[i + j * N] * x[j]; 
      } 
   } 
   return b; 
} 
 
double* reshenie_SLAU_consistent(double U[], LONG64 b[], double y[], double& time) 
{ 
   unsigned int start_time = clock(); 
   for (int i = N - 1; i >= 0; i--) 
   { 
      y[i] = b[i] / U[i + i * N]; 
      for (int j = N - 1; j > i; j--) 
         y[i] = y[i] - U[i + j * N] * y[j] / U[i + i * N]; 
   } 
   unsigned int end_time = clock(); 
   time = end_time - start_time; 
   return y; 
} 
 
double* reshenie_SLAU_parallel(double U[], LONG64 b[], double y[], double& time) 
{ 
   int n = 2; //Коллчичисетво потоков 
   double c = 0; 
   unsigned int start_time = clock(); 
   for (int i = N - 1; i >= 0; i--) 
   { 
      y[i] = b[i] / U[i + i * N]; 
      c = 0; 
      omp_set_num_threads(n); 
#pragma omp parallel for reduction(-:c) 
      for (int j = N - 1; j > i; j--) 
         c += U[i + j * N] * y[j] / U[i + i * N]; 
      y[i] -= c; 
   } 
   unsigned int end_time = clock(); 
   time = end_time - start_time; 
   return y; 
} 
 
double norma_vektora_consistent(double y[]) 
{ 
   double norma = 0; 
   for (int i = 0; i < N; i++) 
   { 
      norma += y[i] * y[i]; 
   } 
   norma = sqrt(norma); 
   return norma; 
} 
 
void main() 
{ 
   setlocale(LC_ALL, ""); 
   double* U = new double[N * N], * y1 = new double[N], * y2 = new double[N], * x = new double[N]; 
   double time_parallel = 0, time_consistent = 0, norma_parallel = 0, norma_consistent = 0, norma_x = 0; 
   int c = -1, k = 0; 
   LONG64* b = new LONG64[N]; 
   for (unsigned int i = 0; i < N; i++) 
   { 
      c++; 
      x[i] = i; 
      b[i] = 0; 
      y1[i] = 0; 
      y2[i] = 0; 
      for (int j = N - 1; j >= 0; j--) 
      { 
         if (j >= c) 
         { 
            U[i + j * N] = k; 
            k++; 
         } 
         else 
             U[i + j * N] = 0; 
      } 
   } 
 
   b = umnozheniye_matritsy_na_vektor_consistent(U, x, b); 
   cout << "Последовательная версия" << '\n'; 
   y1 = reshenie_SLAU_consistent(U, b, y1, time_consistent); 
   cout << "Затраченное время: " << time_consistent << '\n'; 
   norma_consistent = norma_vektora_consistent(y1); 
   cout << "Норма вектора y: " << norma_consistent << '\n' << '\n' << "Параллельная версия" << '\n'; 
   y2 = reshenie_SLAU_parallel(U, b, y2, time_parallel); 
   cout << "Затраченное время: " << time_parallel << '\n'; 
   norma_parallel = norma_vektora_consistent(y2); 
   cout << "Норма вектора y: " << norma_parallel << '\n'; 
   norma_x = norma_vektora_consistent(x); 
   cout << '\n' << "Норма вектора x: " << norma_x << '\n'; 
   double uskor = time_consistent / time_parallel; 
   cout << "Ускорение: " << uskor; 
   ofstream fout("file.txt", ios::trunc); 
   fout << "Элементы вектора x: "; 
   for (unsigned int i = 0; i < N; i++) 
   { 
      fout << x[i] << ' '; 
   } 
   fout << "\nЭлементы вектора y1(последовательная версия): "; 
   for (unsigned int i = 0; i < N; i++) 
   { 
      fout << y1[i] << ' '; 
   } 
   fout << "\nЭлементы вектора y2(параллельная версия): "; 
   for (unsigned int i = 0; i < N; i++) 
   { 
      fout << y2[i] << ' '; 
   } 
   system("pause"); 
} 
