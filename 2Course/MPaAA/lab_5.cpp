#include <stdio.h> 
#include <mpi.h> 
#include <iostream> 
#include <vector> 
 
using namespace std; 
 
int main(int argc, char** argv) 
{ 
   int rank, size; 
   MPI_Init(&argc, &argv); 
   MPI_Comm_size(MPI_COMM_WORLD, &size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
   setlocale(LC_ALL, "Russian"); 
   if (rank != 0) 
   { 
      int n = 100000; 
      double* vector = new double[n]; 
#pragma omp parallel for num_threads(4)  
      for (int i = 0; i < n; i++) 
      { 
         vector[i] = i % 11; 
      } 
 
      double norma = 0; 
#pragma omp parallel for num_threads(4) reduction(+:norma) 
      for (int i = 0; i < n; i++) 
      { 
         norma += vector[i] * vector[i]; 
      } 
      norma = sqrt(norma); 
 
      MPI_Send(&norma, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); 
   } 
   if (rank == 0) 
   { 
      double nvec = 0; 
      MPI_Request req; 
      MPI_Status status; 
      for (int i = 1; i < size; i++) 
      { 
         MPI_Irecv(&nvec, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &req); 
         for (int flag = 0; !flag;) 
         { 
            MPI_Test(&req, &flag, &status); 
            if (flag) 
            { 
               std::cout << "Процесс: " << i << " Норма: " << nvec << endl; 
            } 
         } 
      } 
 
   } 
   MPI_Finalize(); 
   return 0; 
} 
