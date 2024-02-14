#include <stdio.h> 
#include <conio.h> 
#include <locale.h> 
#include <windows.h> 

const UCHAR Nmax = 100;  

int main() 
{ 
   int A[Nmax], D, N; 
   setlocale(0, ""); 
   printf_s("A: "); 
   scanf_s("%i", &A[0]); 
   printf_s("D: "); 
   scanf_s("%i", &D); 
   printf_s("N: "); 
   scanf_s("%i", &N); 
   if (N < Nmax) 
   for (int i = 1; i < N; ++i) 
   {  
      A[i] = A[0] + i * D; 
      printf("%i : %i\n", i + 1, A[i]); 
   }    

   else printf_s("Недопустимый размер N"); 
   _getch(); 
   return 0; 
} 
