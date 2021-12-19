#include "util.h"
<<<<<<< HEAD
=======
#include <string.h>
>>>>>>> rpi funcionando

void ulltoa(uint64_t num, char* str)
{
	uint64_t sum = num;
	int i = 0;
	int digit;
	do
	{
		digit = sum % 10;
		str[i++] = '0' + digit;
		sum /= 10;
	}while (sum);
	str[i--] = '\0';

    int j = 0;
    char ch;
    for (; i > j ; i--, j++)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
<<<<<<< HEAD
	return 0;
=======
>>>>>>> rpi funcionando
}