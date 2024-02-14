#include <stdio.h>
#include <conio.h>
#include <locale.h>
const int N = 10;

struct stack
{
   int arr[N];
   int count;

};

//Изначальная очистка стека
void Initial(stack* ps)
{

   ps->count = 0;

}

//Проверка стека на пустоту
int Empty(stack* ps)
{

   if (ps->count == 0)
      return 1;
   else
      return 0;

}

//Функция взятия элемента из стека
void Take(stack* ps, int* result)
{
   *result = (ps->arr)[(ps->count) - 1];
   ps->count--;
}

// Функция проверки заполненности стека
int Full(stack* ps)
{

   if (ps->count == N)
      return 1;
   else
      return 0;

}

// Функция добавление элемента в стек
void Add(stack* ps)
{
   scanf_s("%d", &(ps->arr[ps->count]));

   ps->count++;
}

//Функция просмотра стека
void Show(stack* ps)
{
   for (int i = 0; i < ps->count; i++)
      printf(" %d", ps->arr[i]);
}

// Вывод команд для работы со стеком
void main()
{
   stack s;
   setlocale(LC_ALL, "Russian");
   Initial(&s);
   int otv;
   int m = 0;
   printf_s("Введите «1» для добавления элемента в вершину стека\n");
   printf_s("Введите «2» для взятия элемента из стека\n");
   printf_s("Введите «3» для вывода элемента стека\n");
   printf_s("Введите «4» для проверки пустоты стека\n");
   printf_s("Введите «5» для проверки заполненности стека\n");
   printf_s("Введите «0» для выхода\n");   printf_s("0. Выход\n");
   printf_s(" Что требуется выполнить? Введите цифру: ");


   do
   {

      scanf_s("%d", &otv);
      switch (otv)
      {
      case 1:

         if (Full(&s) == 1)
            printf_s("Стек полный\n");
         else
         {
            Add(&s);
            printf_s("Элемент добавлен в стек\n");
         }
         break;

      case 2:
         if (!Empty(&s))

         {
            Take(&s, &m);
            printf_s("Из стека извлечён элемент: %d \n", m);
         }
         break;

      case 3:

         if (Empty(&s) == 1)
            printf_s("Стек пуст\n");
         else
         {
            printf_s("Элементы стека");
            Show(&s);
            printf_s("\n");
         }
         break;

      case 4:

         if (Empty(&s) == 1)
            printf_s("Стек пуст\n");
         else
            printf_s("В стеке %d элемента\n", s.count);
         break;

      case 5:

         if (Full(&s) == 1)
            printf_s("Стек полный\n");
         else
            printf_s("Есть возможность добавить %d элементов\n", N - s.count);
         break;

      case 0:

         break;

      default:
         printf_s("Ошибка");
         break;

      }
   } while (otv != 0);
   _getch();

}
