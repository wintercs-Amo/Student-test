#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <string.h>
#include "student.h"
#include "tools.h"

//控制面板
int stu_face(void)
{
	printf("-----------------------\n");
	printf("| 1.查询成绩           |\n");
	printf("| 2.修改密码           |\n");
	printf("| 3.查看个人信息       |\n");
	printf("| q.退出               |\n");
	printf("-----------------------\n");
	int cmd = getch()-'0';
	return cmd;
}


//分数排序，按高到低
int compare(const void* a,const void* b)
{
	return *(int*)b - *(int*)a;
}
void write_stu(Student stu[],int stui)
{
	FILE * fwp = fopen("./stuatschool.txt","w");
	if(fwp == NULL)
	{
		perror("fopen");
	}
	for(int i = 0; i<stui; i++)
	{
		if(stu[i].ver != 2)
		fprintf(fwp,"%s %s %s %s %f %f %f %d %d\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver,stu[i].times);
	}
	fclose(fwp);
	fwp = NULL;
}

//读在校学生个数，并将其写到结构体中
int read_stu(Student stu[])
{
	FILE * frp = fopen("./stuatschool.txt","r");
	if(frp == NULL)
	{
		perror("fopen");
		return 0;
	}
	int ret,i=0,jud=1;
    while((ret = fgetc(frp) != EOF))
    {
    	if(jud == 1)
		{
			fseek(frp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(frp,"%s %s %s %s %f %f %f %d %d",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,&stu[i].chn,&stu[i].math,&stu[i].eng,&stu[i].ver,&stu[i].times);
    	i++;
    }
	fclose(frp);
	frp = NULL;
	return i-1;
}


//	移到被锁定的学生文件
void add_stu_lock(Student stu[],int lock)
{
	FILE * fap = fopen("./stulock.txt","a");
	if(fap == NULL)
	{
		perror("fopen");
	}
	fprintf(fap,"%s %s %s %s %f %f %f %d %d\n",stu[lock].name,stu[lock].sex,stu[lock].sid,stu[lock].pwd,stu[lock].chn,stu[lock].math,stu[lock].eng,stu[lock].ver,stu[lock].times);
	fclose(fap);
	fap = NULL;
	return;
}

//强制改密码，	
int forceModify_stu(void)
{
	Student stu[256] = {};
	int stui = read_stu(stu);
	printf("请输入你的id号：\n");
	char k_id[20] = {};
    scanf("%s",k_id);
    int i=0;
	for(i = 0; i<stui; i++)
	{
		if(!strcmp(stu[i].sid,k_id))
		break;
	}
	if(i != stui)
	{
		if(stu[i].ver == 0)
		{
			FILE * fwp = fopen("./stuatschool.txt","w");
			if(fwp == NULL)
			{
				perror("fopen");
				return 0;
			}
			printf("第一次登陆强制修改密码！\n");
			printf("请输入新密码：\n");
			scanf("%s",stu[i].pwd);
			stu[i].ver = 1;
		rewind(fwp);
		for(int i = 0; i<stui; i++)
		{
			fprintf(fwp,"%s %s %s %s %f %f %f %d %d\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver,stu[i].times);
		} 
		fclose(fwp);
		fwp = NULL;
		}
	}
	if(i == stui)
	{
		printf("没有这个ID，请重试！\n");
		scanf("%*c");
		scanf("%*c");
		return -10;
	}
	int id = atoi(k_id); 
	return id;
	
}

//登录验证
int check_stu(int id)
{
	char k_pwd[15];
    system("clear");
	printf("------学生登录------\n");
    printf("请输入密码：\n");
    scanf("%*c");   
    coverKey(k_pwd);
	Student stu[256] = {};
	int stui=read_stu(stu);
    char k_id[20] = {};
    sprintf(k_id,"%d",id);
	int j=0;
	for(j=0;j<stui;j++)
	{
    	if(!strcmp(stu[j].sid,k_id))
    	{

    		if(!strcmp(stu[j].pwd,k_pwd))
    		{
    			
    			break;
    		}
    		else
    		{
    			printf("\n密码不正确！\n");
				return j;
    		}
    	}
	}
	if(j == stui)
    	printf("没有这个id！\n");
	return -1;
}


//分数查询
void score(void)
{
	char k_id[20]={};
	printf("请输入你的id号：\n");
    scanf("%s",k_id);
    system("clear");
    Student stu[256] = {};
    int stui=read_stu(stu);
    //分数集
    float cavg=0,mavg=0,eavg=0;
    int cmax=0,cmin=100;
    int mmax=0,mmin=100;
    int emax=0,emin=100;
	//分数数组，用于排名
	int c[20]={};
	int m[20]={};
	int e[20]={};
    for(int j=0;j<stui;j++)
    {
    	//平均分
    	cavg+=stu[j].chn;
    	mavg+=stu[j].math;
    	eavg+=stu[j].eng;
    	//最高分
    	if(cmax<stu[j].chn)
    		cmax = stu[j].chn;
    	if(mmax<stu[j].math)
    		mmax = stu[j].math;
    	if(emax<stu[j].eng)
    		emax = stu[j].eng;
    	//最低分
    	if(cmin>stu[j].chn)
    		cmin = stu[j].chn;
    	if(mmin>stu[j].math)
    		mmin = stu[j].math;
    	if(emin>stu[j].eng)
    		emin = stu[j].eng;
    	//分数数组---排名用
    	c[j]=stu[j].chn;
    	m[j]=stu[j].math;
    	e[j]=stu[j].eng;
    }
    qsort(c,stui,sizeof(int),compare);		//使用qsort将成绩数组排序，从高到低排
    qsort(m,stui,sizeof(int),compare);
    qsort(e,stui,sizeof(int),compare);
    int z=0,k=0,x=0,y=0;					//利用双层循环锁定该同学的成绩排名
	for( z=0;z<stui;z++)
	{
		if(!strcmp(k_id,stu[z].sid))
		{
			for(k=0;k<stui;k++)
			{
				if(stu[z].chn == c[k])
				{
					printf("语文成绩：%d 语文排名：%d\n",c[k],k+1);
					k = -1;
					break;
				}
			}
			
			for(x=0;x<stui;x++)
			{
				if(stu[z].math == m[x])
				{
					printf("数学成绩：%d 数学排名：%d\n",m[x],x+1);
					x = -1;
					break;
				}
			}
			
			for(y=0;y<stui;y++)
			{
				if(stu[z].eng == e[y])
				{	
					printf("英语成绩：%d 英语排名：%d\n\n",e[y],y+1);
					y = -1;
					break;
				}
			}
    	}
	}
	if(k == -1 && x == -1 && y == -1)		//得到该同学的所以成绩或排名后，输出班级的最高，最低，平均分
	{
		printf("语文->最高分:%d 最低分:%d 平均分:%.1f \n",cmax,cmin,cavg/(stui));
		printf("数学->最高分:%d 最低分:%d 平均分:%.1f\n",mmax,mmin,mavg/(stui));
		printf("英语->最高分:%d 最低分:%d 平均分:%.1f \n\n",emax,emin,eavg/(stui));
 	}
 	else
 	{
 		printf("ID有误！\n");
 	}
	anykey_continue();
}
//学生重置密码  
void stuModify(void)
{
	Student stu[256] = {};	
	int stui = read_stu(stu);
	char stuid[20];
	printf("请输入你的id：\n");
	scanf("%s",stuid);
	scanf("%*c");
	int i=0;
	for(i = 0; i<stui; i++)
	{
		if(!strcmp(stuid,stu[i].sid))
		{
			printf("请输入新密码：\n");
			scanf("%s",stu[i].pwd);
			scanf("%*c");
			printf("密码修改成功！\n");
    		anykey_continue();
			break;
		}
	}
	write_stu(stu,stui);
	return;
}

//    4、查看个人信息
void show_self(void)
{
	char k_id[20]={};
	printf("请输入你的id:\n");
	scanf("%s",k_id);
	Student stu[256] = {};	
	int stui=read_stu(stu);
	int j=0;
	for(j=0;j<stui;j++)
	{
		if(!strcmp(stu[j].sid,k_id))
		{
			printf("姓名：%s\n性别：%s\nID：%s\n密码：%s\n",stu[j].name,stu[j].sex,stu[j].sid,stu[j].pwd);
			scanf("%*c");
			anykey_continue();
			break;
		}
	}
	return;
}

void run_stu(void)
{
	//forceModify_stu();
	int stucnt = 0,lock = 0;
	while(stucnt < 3)
	{
		int fm = forceModify_stu();
		if(fm == -10)
		{
			return;
		}
		lock = check_stu(fm);
		if(lock == -1)
		{
			//进入页面
			for(;;)
			{
				system("clear");
				switch(stu_face())
				{
					case 1:
						//分数查询 
						score();
					break;
					case 2:
						//修改密码
						stuModify();
					break;
					case 3:
						//查询个人信息，显示
						show_self();
					break;
					case 65:
						//退出
						exit(0);
				}
			}
		}
		else
		{
			stucnt++;
		}
	}
	Student stu[256] = {};
	int stui = read_stu(stu);
	stu[lock].ver = 2;
	write_stu(stu,stui);
	add_stu_lock(stu,lock);
	printf("三次密码错误锁定帐号，由教师解锁!\n");
	exit(0);
}




