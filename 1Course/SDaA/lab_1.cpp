#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct list { char info; list* next; };
struct listok { int strok; int nom; listok* next; };

int poisk(list* t, char sm, listok* w);

int main()
{
   char ch;

   list* d = NULL; list* c = NULL; list* begin = NULL; listok* now = NULL;
   FILE* fp;
   fopen_s(&fp, "text.txt", "r");
   if (fp == NULL) { printf("error"); }
   else {
      c = new list;
      begin = c;
      while (!feof(fp))
      {
         while (fscanf_s(fp, "%c", &ch) != EOF)
            if (ch != '.')
            {
               d = new list;
               (*d).info = ch;
               (*c).next = d;
               c = d;
            }
            else
            {
               d = new list;
               (*d).info = ch;
               (*c).next = d;
               c = d;
               (*c).next = NULL;
               c->info = '.';
            };
      };
   };
   fclose(fp);
   printf("Enter symbol:");
   scanf_s("%c", &ch);
   now = new listok;
   if (c != begin) poisk(begin, ch, now);
   now = now->next;
   FILE* in;
   fopen_s(&in, "text.txt", "a");
   while (now != NULL)
   {
      fprintf(in, "%d - %d\n", now->strok, now->nom);
      now = now->next;
   }
   fclose(in);
   _getch();
   return 0;
};

int poisk(list* t, char sm, listok* w)
{
   int i, j; listok* begin;
   i = 1;
   j = 0;
   begin = w;
   while (t->info != '.')
   {
      if (t->info == '\n')
      {
         i = i + 1;
         j = 0;
      }
      else
      {
         if (t->info == sm)
         {
            w->next = new listok;
            w->next->strok = i;
            w->next->nom = j;
            w = w->next;
         }
      }
      t = t->next;
      j = j + 1;
   }
   w->next = NULL;
   return 0;
};
