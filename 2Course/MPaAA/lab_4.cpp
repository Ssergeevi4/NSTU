#include <mpi.h> 
#include <stdio.h> 
#include <iostream> 
 
int main(int argc, char** argv) 
{ 
setlocale(LC_ALL, "Russian"); 
int rank, size; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
printf("Процесс #%d из общего колличества равного %d \n", rank, size); 
MPI_Finalize(); 
return 0; 
} 
 /*
Вводимое значение в run.bat: 
chcp 1251 
c: 
cd C:\Users\Sergeevi4\source\repos\04040404\x64\Release 
mpiexec.exe -n 10 04040404.exe */
