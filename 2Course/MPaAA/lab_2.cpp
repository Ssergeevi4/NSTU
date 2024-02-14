/* Написать подпрограмму параллельного вычисления скалярного произведения . Протестировать её на векторе малого размера. Сравнить результат и время выполнения программы последовательной и параллельной версии. Заполнить таблицу. 
 
Текст программы  */
#include <iostream> 
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <omp.h> 
 
 
using namespace std; 
 
int main() 
{ 
    int SIZE = 10; 
    setlocale(LC_ALL, "Russian"); 
    double *vecX = NULL; 
    if (vecX == NULL) 
    vecX = new double[SIZE]; 
    double *vecY = NULL; 
    if (vecY == NULL) 
    vecY = new double[SIZE]; 
 
    for (int i = 0; i < SIZE; i++){ 
        vecX[i] = (1 +rand() % 9); 
    } 
 
    for (int i = 0; i < SIZE; i++){ 
        vecY[i] = (1 + rand() % 9); 
    } 
 
    double result = 0; 
    cout << "Скалярное произведение X * Y = "; 
    #pragma omp parallel num_threads(2) 
    #pragma omp for reduction(+:result) 
        for (int i = 0; i < SIZE; i++) 
            result += vecX[i] * vecY[i]; 
 
    cout << result << endl; 
    delete[] vecX; 
    delete[] vecY; 
 
    unsigned int end_time = clock(); 
    cout << "Время выполнения подпрограммы: " << end_time << " миллисекунд."; 
    system("pause"); 
    return 0; 
} 
 
/* 
 Написать параллельную подпрограмму вычисления евклидовой нормы вектора . 
Написать параллельную подпрограмм умножения матрицы на вектор y=Ax. Здесь элементы матрицы A и вектора x считают известными (вы их задаете сами), а элементы вектора y необходимо вычислить в подпрограмме. Протестировать её на векторе малого размера. Заполнить таблицу, аналогичную п.1, при этом сравнивать норму вектора-результата y, полученную при использовании различного числа потоков.  
 
 
Текст программы */
 
#include <iostream> 
#include <ctime> 
#include <omp.h> 
#include <cmath> 
 
 
using namespace std; 
 
int main(int argc, const char* argv[]) 
{ 
   setlocale(LC_ALL, "Russian");                    
 
 
   for (int SIZE = 10; SIZE <= 10000; SIZE *= 10)  
   { 
      double s = 0; 
      double* matrix = NULL; 
      if (matrix == NULL) 
         matrix = new double[SIZE * SIZE];          
      for (int i = 0; i < SIZE; i++) {                
         matrix[i] = rand() % 11;                   
      } 
      double* vector = new double[SIZE];                  
      if (vector == NULL) 
         vector = new double[SIZE]; 
      for (int j = 0; j < SIZE; j++) {               
         vector[j] = rand() % 11;                    
      } 
 
      double* vector_out = new double[SIZE]; 
      for (int i = 0; i < SIZE; i++) 
      { 
         vector_out[i] = 0; 
         for (int j = 0; j < SIZE; j++) { 
            vector_out[i] += matrix[i] * vector[j]; 
         } 
      } 
 
#pragma omp parallel num_threads(2) 
#pragma omp for reduction(+:s) 
      srand(time(NULL));                            
      for (int i = 0; i < SIZE; ++i) { 
         s += pow(vector_out[i], 2);  
      } 
      cout << "Сумма в степени:" << endl; 
      for (int i = 0; i < 1; ++i) { 
         cout << s << ' '; 
      } 
      cout << endl; 
 
      cout << "Конечный ответ:" << endl; 
    for (int i = 0; i < 1; i++) { 
        s= sqrt(s);  
        cout << s << ' '; 
      } 
 
      if (matrix) { 
         delete[]matrix; 
         delete[]vector; 
         delete[]vector_out; 
      } 
      
      unsigned int end_time = clock(); 
      cout << "\n Время выполнения подпрограммы: " << end_time << " миллисекунд.""\n"; 
      cout << endl; 
   } 
 
   system("pause"); 
 
} 
