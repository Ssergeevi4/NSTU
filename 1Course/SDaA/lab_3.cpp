#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

struct treeNode {
   struct treeNode* leftPtr; //указатель на левое поддерево
   int data; //значение в узле
   struct treeNode* rightPtr; //указывает на правое поддерево
};

typedef struct treeNode TreeNode; //синоним
typedef TreeNode* TreeNodePtr; //синоним

//прототипы
void insertNode(TreeNodePtr* treePtr, int value);
int preOrder(TreeNodePtr treePtr);
int Leaves(TreeNodePtr rootPtr);

int main(void)
{
   setlocale(LC_CTYPE, "Russian");
   int i; //счетчик для цикла 1-10
   int item; //переменная для случайных значений
   TreeNodePtr rootPtr = NULL;
   TreeNodePtr LeavesPtr = NULL;

   srand(time(NULL));
   puts("Число, помещаемое в дерево:");

   for (i = 1; i <= 12; i++) {
      item = rand() % 99;
      printf("%3d", item);
      insertNode(&rootPtr, item);
   }

   //обход дерева с предварительной выборкой(прямой) preOrder
   puts("\n\nПредварительный обход:");

   printf("\nЧисло ветвей: %3d \n", preOrder(rootPtr));
   printf("Число листьев: %3d \n", Leaves(rootPtr));
   system("pause");
   return 0; //показывает завершение
}

//вставить узел в дерево
void insertNode(TreeNodePtr* treePtr, int value)
{
   //если дерево пусто
   if (*treePtr == NULL) {
      *treePtr = (TreeNode*)malloc(sizeof(TreeNode));

      //если память выделана,присвоить данные
      if (*treePtr != NULL) {
         (*treePtr)->data = value;
         (*treePtr)->leftPtr = NULL;
         (*treePtr)->rightPtr = NULL;
      }
      else {
         printf("%d не вставленно. Не достаточно памяти. \n", value);
         free(*treePtr);
      }
   }

   //дерево не пусто
   else {

      //вставляемые данные меньше, чем в текущем узле
      if (value < (*treePtr)->data) {
         insertNode(&((*treePtr)->leftPtr), value);
      }

      //вставляемые данные больше, чем в текущем узле
      else if (value > (*treePtr)->data) {
         insertNode(&((*treePtr)->rightPtr), value);
      }
      else {//дубликаты инорируются
         printf("%s", " - дубликат");
      }
   }
}
//обход дерева с предварительной выборкой
int preOrder(TreeNodePtr treePtr)
{
   static int nRet = 0;
   //если дерево не пусто обойти его
   if (treePtr != NULL) {
      ++nRet;
      printf("%3d", treePtr->data);
      preOrder(treePtr->leftPtr);
      preOrder(treePtr->rightPtr);
   }
   //_getch();
   return nRet;
}

//подсчет листьев
int Leaves(TreeNodePtr rootPtr)
{
   static int nRet = 0;
   if (rootPtr != NULL)
   {
      if ((rootPtr->leftPtr == NULL) && (rootPtr->rightPtr == NULL))
         nRet++;
      Leaves(rootPtr->leftPtr);
      Leaves(rootPtr->rightPtr);
   }
   return nRet;
}
