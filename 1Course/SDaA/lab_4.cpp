#include <stdio.h>
#include <string.h>

const int N = 10000;
int num = 0;

struct table
{
   char code[9];
   char name[255];
   int numb;
};

void table_add(table* t, char* code, char* name, int numb)
{
   int flag = 0;
   for (int i = 0; i < num && !flag; i++)
      if (!strcmp(code, t[i].code))
      {
         flag++;
         t[i].numb += numb;
      }
   if (!flag)
   {
      strcpy_s(t[num].code, code);
      strcpy_s(t[num].name, name);
      t[num].numb = numb;
      num++;
   }
}

void hash_add(table* t, char* code, char* name, int numb)
{
   int sym = 0, hash;
   for (int i = 0; i < 9; i++)
      sym += name[i];
   hash = sym % N;
   for (int i = 1; i < N && strlen(t[hash].code); i++)
      hash = (sym + i) % N;
   if (!strlen(t[hash].code))
   {
      strcpy_s(t[hash].code, code);
      strcpy_s(t[hash].name, name);
      t[hash].numb = numb;
   }
}

int main()
{
   table* t = new table[N];
   FILE* f;
   fopen_s(&f, "work.txt", "r");
   int numb;
   char name[255], code[9];
   while (fscanf_s(f, "%s %s %d", code, sizeof(code), name, sizeof(name), &numb) != EOF &&
      num < N)
      table_add(t, code, name, numb);
   fclose(f);
   table* t2 = new table[N];

   for (int i = 0; i < N; i++)
   {
      t2[i].code[0] = '\0';
      t2[i].name[0] = '\0';
      t2[i].numb = 0;
   }

   for (int i = 0; i < num; i++)
      hash_add(t2, t[i].code, t[i].name, t[i].numb);
   fopen_s(&f, "table.txt", "w");
   fprintf_s(f, "|Шифр |Наименование |Количество |");
   for (int i = 0; i < N; i++)
      if (t2[i].code[0] != '\0')
         fprintf(f, "\n|%8s| %12s| %10d|", t2[i].code, t2[i].name, t2[i].numb);
   delete[] t;
   delete[] t2;
   return 0;
}
