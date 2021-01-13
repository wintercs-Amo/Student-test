#include "tools.h"
#include <stdio.h>
#include <getch.h>

void anykey_continue(void)
{
	puts("按任意按键继续...");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
}

//隐藏密码
void coverKey(char ch[])
{
		char c;
		int j;
		j=0;
		while(1)
		{
			c=getch();
			if(c==10)
			{
				ch[j]=0;
				break;
			}
			printf("*");
			ch[j]=c;
			j++;
		}
		return;
}
