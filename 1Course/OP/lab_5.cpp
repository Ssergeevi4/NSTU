#include <stdio.h> 
#include <math.h> 
#include <locale.h> 
#include <conio.h> 
 
void Mean(float X, float Y, float& AMean, float& GMean) { 
 
AMean = (X + Y) / 2; 
GMean = sqrt(X * Y); 
} 
 
void Print(float X, float Y, float AMean, float GMean) { 
printf("Среднее арифметическое (%f, %f) = %f\n", X, Y, AMean); 
printf("Среднее геометрическое (%f, %f) = %f\n\n", X, Y, GMean); 
} 
 
int main() { 
float A, B, C, D, AMean, GMean; 
setlocale(LC_CTYPE, ""); 
scanf_s("%f %f %f %f", &A, &B, &C, &D); 
Mean(A, B, AMean, GMean); 
Print(A, B, AMean, GMean); 
Mean(A, C, AMean, GMean); 
Print(A, C, AMean, GMean); 
Mean(A, D, AMean, GMean); 
Print(A, D, AMean, GMean); 
_getch(); 
return 0; 
} 
