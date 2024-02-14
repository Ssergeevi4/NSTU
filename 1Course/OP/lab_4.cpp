#include <conio.h> 
#include <stdio.h> 
#include <locale.h> 
#include <windows.h> 
 
int main() 
{ 
   setlocale(LC_CTYPE, "Russian"); 
 
   SetConsoleCP(1251); 
   SetConsoleOutputCP(1251); 
 
   char C; 
   printf("Введите символ: "); 
   scanf_s("%c", &C); 
   short num1 = (int)C - 1, num2 = (int)C + 1; 
   if (num1 > 0 && num2 < 255) 
   { 
      printf("Соседние символы: "); 
      printf("%c\t%c", (char)num1, (char)num2); 
   } 
   else printf("Ошибка символа: "); 
   _getch(); 
   return 0; 
} 
