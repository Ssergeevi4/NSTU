#include <stdio.h>
#include <conio.h>
#include <locale.h>

void main()
{
	setlocale(LC_CTYPE, "Russian");

	int a = 0;
		printf_s("Введите число a: ");
	if (!scanf_s("%d", &a))
	{
		printf_s("введено не число!");
		_getch();
		return;
	}
	
	if (a > 0)
	{
		if (a > 0)
		{
			a = a + 1;
			printf_s("Число a - положмтельное, a = %d\n", a);
		}
	}

		else if (a < 0)
		{
			a = a - 2;
			printf_s("Число a - отрицательное, a = %d\n", a);
		}
		else if (a == 0)
	
		
		{
			a = 10;
			printf_s("Число a - равно нулю, a = %d\n", a);
		}

	_getch();
	return;
	
}
