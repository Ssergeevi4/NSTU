#include <stdio.h>
#include <conio.h>
#include <locale.h>

/* Дано целое число N (>0). Сформировать и вывести целочисленный массив размера N, содержащий N первых положительных нечетных чисел: 1, 3, 5, ... . */

int main()
{
   setlocale(LC_CTYPE, "Russian");
   int N, i;
   printf_s("Введите число N:");
   scanf_s("%d", &N); // заполняем массив значениями:
   int a[N] // наш массив из N элементов
      a[0] = 1;
   printf_s("%-3d", a[0]);
   for (i = 1, a[0] = 1; i < N; i++)
   {
      a[i] = a[i - 1] + 2;
      printf_s("%-3d", a[i]); // выводим значение на экран
   }
}
