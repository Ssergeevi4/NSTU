#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <time.h> 
#include <mpi.h> 
 
int ProcNum = 0, ProcRank = 0; 
 
// Функция выделения памяти и инициализации данных 
void Declaration(double*& A, double*& B, 
double*& C, double*& pProcRows, double*& pProcC, 
int& Size, int& RowNum) 
{ 
int RestRows;                                         // Количество строк, которые еще не распределены 
int i, j; 
MPI_Bcast(&Size, 1, MPI_INT, 0, MPI_COMM_WORLD); 
RestRows = Size; 
for (i = 0; i < ProcRank; i++) 
RestRows = RestRows - RestRows / (ProcNum - i); 
RowNum = RestRows / (ProcNum - ProcRank); 
B = new double[Size]; 
C = new double[Size]; 
pProcRows = new double[RowNum * Size]; 
pProcC = new double[RowNum]; 
if (ProcRank == 0) { 
A = new double[Size * Size]; 
srand(time(NULL)); 
for (i = 0; i < Size; i++) { 
B[i] = rand() % 46; 
for (j = 0; j < Size; j++) 
A[i * Size + j] = rand() % 46; 
} 
} 
} 
 
// Распределение данных между процессами 
void Allocation(double* A, double* pProcRows, double* B, 
int Size, int RowNum) { 
int* pSendNum;                                        // Количество элементов, отправленных в процесс 
int* pSendInd;                                        // Индекс первого элемента данных, отправленных процессу 
int RestRows = Size; 
MPI_Bcast(B, Size, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
 
// Выделяем память для временных объектов 
pSendInd = new int[ProcNum]; 
pSendNum = new int[ProcNum]; 
 
// Определение расположения строк матрицы для текущего процесса 
RowNum = (Size / ProcNum); 
pSendNum[0] = RowNum * Size; 
pSendInd[0] = 0; 
for (int i = 1; i < ProcNum; i++) { 
RestRows -= RowNum; 
RowNum = RestRows / (ProcNum - i); 
pSendNum[i] = RowNum * Size; 
pSendInd[i] = pSendInd[i - 1] + pSendNum[i - 1]; 
} 
MPI_Scatterv(A, pSendNum, pSendInd, MPI_DOUBLE, pProcRows, 
pSendNum[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD); 
delete[] pSendNum; 
delete[] pSendInd; 
} 
 
// Функция для сбора финального вектора 
void ResultReplication(double* pProcC, double* C, int Size, 
int RowNum) { 
int i; 
int* pReceiveNum;                                     // Количество элементов, которые отправляет текущий процесс 
int* pReceiveInd;                                     // Индекс первого элемента из текущего процесса в финальном векторе 
int RestRows = Size; 
pReceiveNum = new int[ProcNum]; 
pReceiveInd = new int[ProcNum]; 
 
// Определение расположения блока вектора результатов текущего процесса 
pReceiveInd[0] = 0; 
pReceiveNum[0] = Size / ProcNum; 
for (i = 1; i < ProcNum; i++) { 
RestRows -= pReceiveNum[i - 1]; 
pReceiveNum[i] = RestRows / (ProcNum - i); 
pReceiveInd[i] = pReceiveInd[i - 1] + pReceiveNum[i - 1]; 
} 
MPI_Allgatherv(pProcC, pReceiveNum[ProcRank], MPI_DOUBLE, C, 
pReceiveNum, pReceiveInd, MPI_DOUBLE, MPI_COMM_WORLD); 
delete[] pReceiveNum; 
delete[] pReceiveInd; 
} 
 
void ParallelCalculation(double* pProcRows, double* B, double* 
pProcC, int Size, int RowNum) { 
int i, j; 
for (i = 0; i < RowNum; i++) { 
pProcC[i] = 0; 
for (j = 0; j < Size; j++) 
pProcC[i] += pProcRows[i * Size + j] * B[j]; 
} 
} 
 
// Функция завершения вычислительного процесса 
void Delete(double* A, double* B, double* C, 
double* pProcRows, double* pProcC) { 
if (ProcRank == 0) 
delete[] A; 
delete[] B; 
delete[] C; 
delete[] pProcRows; 
delete[] pProcC; 
} 
void main(int argc, char* argv[]) { 
double* A;                                            // Исходная матрица 
double* B;                                            // Исходный вектор 
double* C;                                            // Вектор для умножения матрицы на вектор 
int Size = 10;                                        // Размеры исходной матрицы и вектора 
 
 
double* pProcRows; 
double* pProcC; 
int RowNum; 
MPI_Init(&argc, &argv); 
MPI_Comm_size(MPI_COMM_WORLD, &ProcNum); 
MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); 
Declaration(A, B, C, pProcRows, pProcC, 
Size, RowNum); 
Allocation(A, pProcRows, B, Size, RowNum); 
ParallelCalculation(pProcRows, B, pProcC, Size, RowNum); 
ResultReplication(pProcC, C, Size, RowNum); 
if (ProcRank == 0) { 
for (int i = 0; i < Size; i++) 
printf_s("%.0f ", C[i]); 
printf_s("\n"); 
for (int i = 0; i < Size; i++) { 
C[i] = 0; 
for (int j = 0; j < Size; j++) 
C[i] += A[i * Size + j] * B[j]; 
} 
for (int i = 0; i < Size; i++) 
printf_s("%.0f ", C[i]); 
printf_s("\n"); 
} 
Delete(A, B, C, pProcRows, pProcC); 
MPI_Finalize(); 
system("pause"); 
} 
 /*
 Вывод 
5427 4985 5305 4398 5113 4174 2828 4870 4026 2896 
5427 4985 5305 4398 5113 4174 2828 4870 4026 2896 */
