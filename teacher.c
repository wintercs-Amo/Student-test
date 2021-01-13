#include <stdio.h>
#include <string.h>
#include <getch.h>
#include <stdlib.h>
#include "teacher.h"
#include "student.h"
#include "grade.h"
#include "tools.h"

Grade grade[256] = {};
int stui = 0;
int gradei = 0;
int teai = 0;
int stuleavei = 0;

int tch_face(void)
{
	printf("----------教师操作----------\n");
	printf("|                          |\n");
	printf("| 1.添加学生信息           |\n");
	printf("| 2.批量添加学生信息       |\n");
	printf("| 3.删除学生               |\n");
	printf("| 4.查找学生               |\n");
	printf("| 5.修改学生信息           |\n");
	printf("| 6.录入学生成绩           |\n");
	printf("| 7.批量录入学生成绩       |\n");
	printf("| 8.重置学生密码           |\n");
	printf("| 9.显示在校学生           |\n");
	printf("| 0.解锁学生账户           |\n");
	printf("| d.显示已删除学生         |\n");
	printf("| q.退出                   |\n");
	printf("---------------------------\n");
	int cmd = getch()-'0';
	return cmd;
}

// 按任任意键继续
void anykey_con(void)
{
	puts(" ");
	puts("按任意键继续...");
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓冲区、防止垃圾值导致getch()失效
	getch();
}

//显示学生信息-全部信息
void showstu(Student* stu,int cnt)
{
	printf("----------学生表----------\n");
	for(int i=0;i<cnt;i++)
	{
		if(stu[i].ver != -1)
		printf("姓名：%s 性别：%s 学号：%s 密码：%s \n语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f 验证位：%hhd\n\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver);
	}
}

//显示离校学生信息-全部信息
void showstuleave(Student* stu,int cnt)
{
	printf("----------学生表----------\n");
	for(int i=0;i<cnt;i++)
	{
		printf("姓名：%s 性别：%s 学号：%s 密码：%s \n语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f 验证位：%hhd\n\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver);
	}
}

//显示学生信息-部分 只包括成绩
void showstupart(Student* stu,int cnt)
{
	printf("----------学生表----------\n");
	for(int i=0;i<cnt;i++)
	{
		if(stu[i].ver != -1)
		printf("姓名：%s 性别：%s 学号：%s \n语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f\n\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].chn,stu[i].math,stu[i].eng);
	}
}

//重写stuatschool.txt文件
void cover(Student* stu,int cnt)
{
	FILE* fp = fopen("./stuatschool.txt","w");
	if(NULL == fp)
	{
		perror("fopen");
	}
	for(int i=0;i<cnt;i++)
	{
		fprintf(fp,"%s %s %s %s %f %f %f %hhd %d\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver,stu[i].times);
	}
	fclose(fp);
	fp = NULL;
}

//读取需导入成绩 从txt文档中读入成绩
void readgrade(void)
{
	FILE * fp = fopen("./grade.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		//return 0;
	}
	//Grade grade[256] = {};
	int ret,i=0,jud=1;
	while((ret = fgetc(fp) != EOF))
	{
		if(jud == 1)
		{
			fseek(fp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(fp,"%s %d %d %d",grade[i].sid,&grade[i].chn,&grade[i].math,&grade[i].eng);
		i++;
	}
	gradei = i-1;
	fclose(fp);
	fp = NULL;
}

//从stuatschool.txt读入学生信息
void readstu(Student* stu)
{
	FILE * fp = fopen("./stuatschool.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		return;
	}
	int ret,i=0,jud=1;
	while((ret = fgetc(fp) != EOF))
	{
		if(jud == 1)
		{
			fseek(fp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(fp,"%s %s %s %s %f %f %f %d %d",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,&stu[i].chn,&stu[i].math,&stu[i].eng,&stu[i].ver,&stu[i].times);
		i++;
	}
	stui = i-1;
	fclose(fp);
	fp = NULL;
}

//从stuleaveschool.txt读入学生信息
void readstuleave(Student* stu)
{
	FILE * fp = fopen("./stuleaveschool.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		return;
	}
	int ret,i=0,jud=1;
	while((ret = fgetc(fp) != EOF))
	{
		if(jud == 1)
		{
			fseek(fp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(fp,"%s %s %s %s %f %f %f %d %d",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,&stu[i].chn,&stu[i].math,&stu[i].eng,&stu[i].ver,&stu[i].times);
		i++;
	}
	stuleavei = i-1;
	fclose(fp);
	fp = NULL;
}

//从teacher.txt中读入老师信息
void readtea(Teacher* tea)
{
	FILE * frp = fopen("./tch.txt","r");
	if(frp == NULL)
	{
		perror("fopen");
		return;
	}
	int ret,i=0,jud=1;
	while((ret = fgetc(frp) != EOF))
	{
		if(jud == 1)
		{
			fseek(frp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(frp,"%s %s %d %s %hhd",tea[i].name,tea[i].sex,&tea[i].id,tea[i].pwd,&tea[i].ver);
		i++;
	}
	teai = i-1;
	fclose(frp);
	frp = NULL;
}

// 改变teacher.txt的信息后 重新写入txt中
void covertea(Teacher* tea)
{
	FILE * fwp = fopen("./tch.txt","w");
	if(fwp == NULL)
	{
		perror("fopen");
		return;
	}
	for(int i = 0; i<teai; i++)
	{
		if(tea[i].ver != 2)
		fprintf(fwp,"%s %s %d %s %hhd\n",tea[i].name,tea[i].sex,tea[i].id,tea[i].pwd,tea[i].ver);
	}
	fclose(fwp);
	fwp = NULL;
}

//将密码被锁定的老师信息放到 tealock.txt中
void movetealock(Teacher* tea,int lock)
{
	FILE * fp = fopen("./tchlock.txt","a");
	if(fp == NULL)
	{
		perror("fopen");
	}
	fprintf(fp,"%s %s %d %s %hhd\n",tea[lock].name,tea[lock].sex,tea[lock].id,tea[lock].pwd,tea[lock].ver);
	fclose(fp);
	fp = NULL;
	printf("三次密码错误锁定帐号，由校长解锁!\n");
}

//将被删除学生放到 stuleaveschool.txt中
void movestuleave(Student* stu,int leave)
{
	FILE * fp = fopen("./stuleaveschool.txt","a");
	if(fp == NULL)
	{
		perror("fopen");
		return;
	}
	fprintf(fp,"%s %s %s %s %f %f %f %hhd %d\n",stu[leave].name,stu[leave].sex,stu[leave].sid,stu[leave].pwd,stu[leave].chn,stu[leave].math,stu[leave].eng,stu[leave].ver,stu[leave].times);
	fclose(fp);
	fp = NULL; 
}

//判断学生是否存在！
int stuexist(Student* stu,char* id)
{
	int loc=-1,j;
	for(j=0;j<stui;j++)
	{
		if(strcmp(id,stu[j].sid) == 0)
		{
			loc = j;
			if(stu[loc].ver == -1)
			{
				printf("该生信息已删除,不能对其进行修改！");
				return -1;
			}
			else return loc;
		}
	}
	if(j == stui && loc ==-1) 
	{
		printf("你输入的学号不存在,请查看！\n");		
	}
	return loc;
}

//老师登录三次验证
int forceModify_tea(void)
{
	Teacher tea[256] = {};
	readtea(tea);
	int k_id,i;
	printf("请输入教师id号：\n");
    	scanf("%d",&k_id);
	for(i = 0; i<teai; i++)
	{
		if(tea[i].id == k_id)
		break;
	}
	if(i != teai)
	{
		if(tea[i].ver == 0)
		{
			printf("第一次登陆强制修改密码！\n");
			printf("请输入新密码：\n");
			scanf("%s",tea[i].pwd); 
			tea[i].ver = 1;
		}
	}
	if(i == teai)
	{
		printf("没有这个教师ID，请重试！\n");
		scanf("%*c");
		scanf("%*c");
		return -10;
	}
	return k_id;
}

//登录验证
int check_tea(int id)
{
	char k_pwd[15];
	int j;
	Teacher tea[256] = {};
	readtea(tea);
	system("clear");
	printf("------教师登录------\n");
	printf("请输入密码：\n");
	scanf("%*c");
	coverKey(k_pwd);	//	隐藏密码
	for(j=0;j<teai;j++)
	{
    		if(tea[j].id == id)
    		{
    			if(!strcmp(tea[j].pwd,k_pwd)) break;
    			else
    			{
    				printf("密码不正确！\n");
				return j;
    			}
    		}
	}
	return -1;
}

//单个添加学生
void add_stu(void) 
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	int newid = stui;
	printf("请输入需要添加学生的姓名：\n");
	scanf("%s",stu[newid].name);
	printf("请输入需要添加学生的性别：\n");
	scanf("%s",stu[newid].sex);
	int newsid = 1000+newid;
	sprintf(stu[newid].sid,"%d",newsid); //自动添加id
	strcpy(stu[newid].pwd,"123456");
	printf("请输入需要添加学生的语文成绩：\n");
	scanf("%f",&stu[newid].chn);
	printf("请输入需要添加学生的数学成绩：\n");
	scanf("%f",&stu[newid].math);
	printf("请输入需要添加学生的英语成绩：\n");
	scanf("%f",&stu[newid].eng);
	cover(stu,stui+1);
	printf("学生信息添加成功！\n");
}

//批量添加学生
void add_stu_v(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	int count = 0;
	printf("请输入要添加的学生个数：\n");
	scanf("%d",&count);
	for(int i=0;i<count;i++)
	{
		int newid = stui+i;
		int now = i+1;
		printf("\n");
		printf("请输入第%d个学生的姓名：\n",now);
		scanf("%s",stu[newid].name);
		printf("请输入第%d个学生的性别：\n",now);
		scanf("%s",stu[newid].sex);
		int newsid = 1000+newid;
		sprintf(stu[newid].sid,"%d",newsid);
		strcpy(stu[newid].pwd,"123456");
		printf("请输入第%d个学生的语文成绩：\n",now);
		scanf("%f",&stu[newid].chn);
		printf("请输入第%d个学生的数学成绩：\n",now);
		scanf("%f",&stu[newid].math);
		printf("请输入第%d个学生的英语成绩：\n",now);
		scanf("%f",&stu[newid].eng);
		printf("第%d个学生信息添加成功！\n",now);	
	}
	cover(stu,stui+count);
}


//删除学生
void del_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char id[20],sid[20];
	printf("请输入要删除的学生学号：\n");
	scanf("%s",id);
	printf("请再次输入要删除的学生学号：\n");
	scanf("%s",sid);
	if(strcmp(id,sid) == 0)
	{
		int loc = stuexist(stu,id);
		if(loc!=-1)
		{
			stu[loc].ver = -1;
			movestuleave(stu,loc);
			printf("该学生信息删除成功,可在离校学生表中查看！\n");
		}
		cover(stu,stui);
		return;
	}
	else
	{
		printf("前后两次输入需要删除学号不同！请查看！\n");
		return;
	}
	return;
}

//找学生(按学号) 找到的是基本信息
void find_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char id[20];
	printf("请输入你要查看信息的学号:\n");
	scanf("%s",id);
	int loc = stuexist(stu,id);
	if(loc != -1)
	{
		printf("姓名：%s 性别：%s 学号：%s\n语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f\n",stu[loc].name,stu[loc].sex,stu[loc].sid,stu[loc].chn,stu[loc].math,stu[loc].eng);
	}
	return;
}

//修改学生基础信息和分数 	
void modify_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char id[20];
	printf("请输入您要修改信息的学生学号:\n");
	scanf("%s",id);
	int loc = stuexist(stu,id);
	if(loc != -1)
	{
		printf("-----该生当前成信息为-----\n");
		printf("姓名：%s 性别：%s 学号：%s 密码： %s\n语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f\n",stu[loc].name,stu[loc].sex,stu[loc].sid,stu[loc].pwd,stu[loc].chn,stu[loc].math,stu[loc].eng);
		printf("-------------------------\n");
		printf("请输入学生姓名：\n");
		scanf("%s",stu[loc].name);
		printf("请输入学生性别：\n");
		scanf("%s",stu[loc].sex);
		printf("请输入学生密码：\n");
		scanf("%s",stu[loc].pwd);
		printf("请输入你的语文成绩：\n");
		scanf("%f",&stu[loc].chn);
		printf("请输入你的数学成绩：\n");
		scanf("%f",&stu[loc].math);
		printf("请输入你的英语成绩：\n");
		scanf("%f",&stu[loc].eng);
		printf("修改信息成功！\n");	
	}
	cover(stu,stui);
	return;
}

//单个录入成绩
void add_sco(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char id[20];
	printf("请输入你要录入成绩的学号:\n");
	scanf("%s",id);
	int loc = stuexist(stu,id);
	if(loc != -1)
	{
		printf("请输入你的语文成绩：\n");
		scanf("%f",&stu[loc].chn);
		printf("请输入你的数学成绩：\n");
		scanf("%f",&stu[loc].math);
		printf("请输入你的英语成绩：\n");
		scanf("%f",&stu[loc].eng);
		printf("录入成绩成功！\n");	
	}
	cover(stu,stui);
	return;
}

//批量录入成绩
void add_sco_v(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	readgrade();
	printf("请将学生成绩按照 学号 语文 数学 英语的格式放入grade.txt中！\n");
	int scount = 1,fcount = 0,j;
	for(int i=0;i<gradei;i++)
	{
		for(j=0;j<stui;j++)
		{
			if(strcmp(grade[i].sid,stu[j].sid) == 0)
			{
				printf("成功修改成绩次数：%d\n",scount++);
				stu[j].chn = grade[i].chn;
				stu[j].math = grade[i].math;
				stu[j].eng = grade[i].eng;
				break;
			}
			else 
			{	
				fcount = 1;
			}
		}
		if(fcount == 1 && j == stui) 
		{
			printf("grade.txt成绩表的第%d行学生学号不存在，请查看学生表中是否有该学生信息！\n",i+1);
			fcount = 0;
		}
	}
	cover(stu,stui);
	printf("成功导入%d个学生的成绩！\n",scount-1);
	return;
}

//重置密码
void change_pwd(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char id[20];
	printf("请输入您需要重置密码的学生学号:\n");
	scanf("%s",id);
	int loc = stuexist(stu,id);
	if(loc != -1)
	{
		strcpy(stu[loc].pwd,"123456");
		printf("该生密码已重置，默认为（123456）\n");
	}
	cover(stu,stui);
	return;
}

//从stuatschool.txt中显示在读学生信息显示的文件	
void show_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	showstu(stu,stui);
	return;
}

//从stuleaveschool.txt显示删除学生信息   
void show_stu_del(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstuleave(stu);
	showstuleave(stu,stuleavei);
	return;
}

//解锁学生账户
void unlock_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char id[20];
	printf("请输入您需要重置账户的学生学号:\n");
	scanf("%s",id);
	int loc = stuexist(stu,id);
	if(loc != -1)
	{
		stu[loc].ver = 0;
		strcpy(stu[loc].pwd,"123456");
		printf("该生账户已解锁，且密码已重置（默认123456）！\n");
	}
	cover(stu,stui);
	return;
	
}

//按钮函数
void run_tch(void)
{
	int teacnt = 0,lock = 0;
	while(teacnt < 3)
	{
		int fm = forceModify_tea();
		if(fm == -10)
		{
			return;
		}
		lock = check_tea(fm);
		if(lock == -1)
		{
			//进入页面
			for(;;)
			{
				system("clear");
				switch(tch_face())
				{
					case 0:
						unlock_stu();
						anykey_con();
						break;
					case 1:
						add_stu();
						anykey_con();
						break;
					case 2:
						add_stu_v();
						anykey_con();
						break;
					case 3:
						del_stu();
						anykey_con();
						break;
					case 4:
						find_stu();
						anykey_con();
						break;
					case 5:
						modify_stu();
						anykey_con();
						break;
					case 6:
						add_sco();
						anykey_con();
						break;
					case 7:
						add_sco_v();
						anykey_con();
						break;
					case 8:
						change_pwd();
						anykey_con();
						break;
					case 9:
						show_stu();
						anykey_con();
						break;
					case 52:
						show_stu_del();
						anykey_con();
						break;
					case 65:
						exit(0);
				}
			}
		}
		else
		{
			teacnt++;
		}
	}
	Teacher tea[256] = {};
	readtea(tea);
	tea[lock].ver = 2;
	covertea(tea);
	movetealock(tea,lock);
	return;
}

