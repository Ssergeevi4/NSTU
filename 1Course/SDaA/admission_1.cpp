
/*1. Условие задачи
Для указанного ниже представления списка, опишите на Си соответствующий тип список (считать тип информационной
части элементов простым), определите переменную L (и, если надо, вспомогательные переменные) и напишите 
последовательность операторов для обмена местами первого и последнего элементов непустого списка L:
*/

#include <stdio.h>
#include <locale.h>

int main()
{
   setlocale(LC_ALL, "");
   char k;
   struct list
   {
      list* next;
      char elem;
   }*L;
   list* p, * pr, * last, * first, * second;
   L = new list;
   printf_s("Введите элементы списка: ");
   last = L;
   while ((k = getchar()) != '\n')
   {
      last->next = new list;
      last = last->next;
      last->elem = k;
   }
   last->next = NULL;
   pr = L;
   pr = pr->next;
   while (pr->next != last)
   {
      pr = pr->next;
   }
   first = L;
   first = first->next;
   second = first->next;
   pr->next = first;
   first->next = NULL;
   L->next = last;
   last->next = second;
   p = L;
   p = p->next;
   printf_s("Изменённый список: ");
   for (p; p != NULL; p = p->next)
      printf_s("%c", p->elem);
   return 0;
}


