#include "surface.h"
#include "tools.h"
#include <stdio.h>
#include <getch.h>
#include "teacher.h"
#include "student.h"
#include "admin.h"
#include "stdlib.h"

void run(void)
{
 	//debug("%s\n",__func__);
 	for(;;)
 	{
 		system("clear");
 		//选择登录的角色   学生/老师/校长
 		//login();
 		//id 密码 验证    从txt文件中匹配
 		
 		//登录成功以后不同的角色有不同的操作界面
        switch(login())
        {
        	case 1:
        		run_stu();
        		anykey_continue();  	
        		break;
        	case 2:
        		run_tch();
        		anykey_continue();	
        		break;
        	case 3:
        		run_admin();
        		anykey_continue();		
        		break;
        	case 65:
        		exit(0);
        }
        
        
		
 	}
}

char login(void)
{
	printf("--------登录角色--------\n");
	printf("| 1.学生               |\n");
	printf("| 2.教师               |\n");
	printf("| 3.校长               |\n");
	printf("| q.退出               |\n");
	printf("-----------------------\n");
	char cmd = getch()-'0';
	return cmd;
}





