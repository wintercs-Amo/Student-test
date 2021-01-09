#include "teacher.h"
#include "tools.h"
#include "stu.h"
#include "grade.h"
#include <stdio.h>
#include <string.h>


Grade grade[256] = {};
int stui = 0;
int gradei = 0;
int teai = 0;

//显示学生信息
void showstu(Student* stu,int cnt)
{
	printf("----------学生表----------\n");
	for(int i=0;i<cnt;i++)
	{
		if(stu[i].ver != -1)
		printf("姓名：%s 性别：%s 学号：%s 密码：%s 语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f 验证位：%d 安全位：%d\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver,stu[i].times);
	}
}

//重写stuaischool.txt文件
void cover(Student* stu,int cnt)
{
	FILE* fp = fopen("./stuatschool.txt","w");
	if(NULL == fp)
	{
		perror("fopen");
	}
	for(int i=0;i<cnt;i++)
	{
		fprintf(fp,"%s %s %s %s %f %f %f %d %d\n",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,stu[i].chn,stu[i].math,stu[i].eng,stu[i].ver,stu[i].times);
	}
	fclose(fp);
	fp == NULL;
}

//重写stuaischool.txt文件
void covertea(Teacher* tea,int cnt)
{
	FILE* fp = fopen("./teacher.txt","w");
	if(NULL == fp)
	{
		perror("fopen");
	}
	for(int i=0;i<cnt;i++)
	{
		fprintf(fp,"%s %s %s %s %d %d\n",tea[i].name,tea[i].sex,tea[i].tid,tea[i].pwd,tea[i].ver,tea[i].times);
	}
	fclose(fp);
	fp == NULL;
}

//读取需导入成绩
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
	fp == NULL;
}

//读入学生信息
void readstu(Student* stu)
{
	FILE * fp = fopen("./stuatschool.txt","r");
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
		fscanf(fp,"%s %s %s %s %f %f %f %d %d",stu[i].name,stu[i].sex,stu[i].sid,stu[i].pwd,&stu[i].chn,&stu[i].math,&stu[i].eng,&stu[i].ver,&stu[i].times);
		i++;
	}
	stui = i-1;
	fclose(fp);
	fp == NULL;
}

//读入老师信息
void readtea(Teacher* tea)
{
	FILE * fp = fopen("./teacher.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
	}
	int ret,i=0,jud=1;
	while((ret = fgetc(fp) != EOF))
	{
		if(jud == 1)
		{
			fseek(fp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(fp,"%s %s %s %s %d %d",tea[i].name,tea[i].sex,tea[i].tid,tea[i].pwd,&tea[i].ver,&tea[i].times);
		i++;
	}
	teai = i-1;
	fclose(fp);
	fp == NULL;
}

//显示老师信息
void showtea(Teacher* tea,int cnt)
{
	printf("----------教师表----------\n");
	for(int i=0;i<cnt;i++)
	{
		if(tea[i].ver != -1)
		printf("姓名：%s 性别：%s 工号：%s 密码：%s 验证位：%d 安全位：%d\n",tea[i].name,tea[i].sex,tea[i].tid,tea[i].pwd,tea[i].ver,tea[i].times);
	}
}
//老师登录 
int modify_pwd(void)
{
	debug("%s\n",__func__);
	Teacher tea[256]={};
	readtea(tea);
	char tid[20];
	char tpwd[6];
	char newpwd[6];
	int loc=-1,j;
	printf("请输入你的工号：\n");
	scanf("%s",tid);
	for(j=0;j<teai;j++)
	{
		if(strcmp(tid,tea[j].tid) == 0)
		{
			loc = j;
			break;
		}
	}
	if(j == teai && loc ==-1) 
	{
		printf("你输入的工号有误,请查看！\n");		
	}
	if(loc != -1)
	{
		if(tea[loc].times>2)
		{
			printf("您的账户已锁定！\n");
			return 0;
		}
		printf("请输入你的密码：\n");
		scanf("%s",tpwd);
		if(strcmp(tpwd,tea[loc].pwd) == 0)
		{
			printf("登录成功！\n");
			if(tea[loc].ver == 0)
			{
				printf("\n");
				printf("由于您是初次登录，请输入新密码：\n");
				scanf("%s",newpwd);
				strcpy(tea[loc].pwd,newpwd);
				tea[loc].ver = 1;
				printf("密码修改成功！\n");
			}
		}
		else
		{
			printf("密码有误！请检查密码输入\n");
			tea[loc].times++;
		}
	}
	covertea(tea,teai);
}

//2、添加学生,学生学号自动生成，	---老师独有
void add_stu(void) //学生学号自动按顺序生成，
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	int newid = stui;
	printf("请输入你的姓名：\n");
	scanf("%s",stu[newid].name);
	printf("请输入你的性别：\n");
	scanf("%s",stu[newid].sex);
	int newsid = 1000+newid;
	sprintf(stu[newid].sid,"%d",newsid);
	strcpy(stu[newid].pwd,"123456");
	printf("请输入你的语文成绩：\n");
	scanf("%f",&stu[newid].chn);
	printf("请输入你的数学成绩：\n");
	scanf("%f",&stu[newid].math);
	printf("请输入你的英语成绩：\n");
	scanf("%f",&stu[newid].eng);
	cover(stu,stui+1);
	printf("学生信息添加成功！\n");
}

//批量添加学生信息
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

//删除学生，删除后保存文本->del_stu.txt  --tools中
void del_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	printf("请输入要删除的学生学号：\n");
	char delid[20];
	int loc=-1,j;
	scanf("%s",delid);
	for(j=0;j<stui;j++)
	{
		if(strcmp(delid,stu[j].sid) == 0)
		{
			loc = j;
			break;
		}
	}
	if(j == stui && loc ==-1) 
	{
		printf("你输入的学号有误,请查看！\n");		
	}
	if(loc != -1)
	{
		stu[loc].ver = -1;
		FILE* dp = fopen("./stuleaveschool.txt","a");
		if(dp == NULL)
		{
			perror("fopen");
		}
		fprintf(dp,"%s %s %s %s %f %f %f %d %d\n",stu[loc].name,stu[loc].sex,stu[loc].sid,stu[loc].pwd,stu[loc].chn,stu[loc].math,stu[loc].eng,stu[loc].ver,stu[loc].times);
		printf("该学生信息删除成功！\n");
	}
	cover(stu,stui);
}

//找学生(按学号) 找到的是基本信息
void find_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	//showstu(stu,stui);
	char csid[20];
	int loc=-1,j;
	printf("请输入你要查看信息的学号:\n");
	scanf("%s",csid);
	for(j=0;j<stui;j++)
	{
		if(strcmp(csid,stu[j].sid) == 0)
		{
			loc = j;
			break;
		}
	}
	if(j == stui && loc ==-1) 
	{
		printf("你输入的学号有误请查看！\n");		
	}
	if(loc != -1)
	{
		printf("姓名：%s 性别：%s 学号：%s 密码：%s 语文成绩：%6.2f 数学成绩：%6.2f 英语成绩：%6.2f 验证位：%d 安全位：%d\n",stu[loc].name,stu[loc].sex,stu[loc].sid,stu[loc].pwd,stu[loc].chn,stu[loc].math,stu[loc].eng,stu[loc].ver,stu[loc].times);
	}
}

//修改学生基础信息和分数 ---老师独有	
void modify_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	//showstu(stu,stui);
	char csid[20];
	int loc=-1,j;
	printf("请输入你要修改信息的学号:\n");
	scanf("%s",csid);
	for(j=0;j<stui;j++)
	{
		if(strcmp(csid,stu[j].sid) == 0)
		{
			loc = j;
			break;
		}
	}
	if(j == stui && loc ==-1) 
	{
		printf("你输入的学号有误请查看！\n");
		
	}
	if(loc != -1)
	{
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
}

//录入成绩，单个
void add_sco(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	showstu(stu,stui);
	char csid[20];
	int loc=-1,j;
	printf("请输入你要录入成绩的学号:\n");
	scanf("%s",csid);
	for(j=0;j<stui;j++)
	{
		if(strcmp(csid,stu[j].sid) == 0)
		{
			loc = j;
			break;
		}
	}
	if(j == stui && loc ==-1) 
	{
		printf("你输入的学号有误请查看！\n");
		
	}
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
}

//批量录入成绩
void add_sco_v(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	readgrade();
	int scount = 1,fcount = 0,j;
	for(int i=0;i<gradei;i++)
	{
		for(j=0;j<stui;j++)
		{
			if(strcmp(grade[i].sid,stu[j].sid) == 0)
			{
				printf("匹配成功次数：%d\n",scount++);
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
			printf("成绩表的第%d行学生学号不存在，请查看学生表中是否有该学生信息！\n",i+1);
			fcount = 0;
		}
	}
	cover(stu,stui);
}

//重置密码			--在tools中
int change_pwd(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	char csid[20],opwd[6],npwd[6];
	int loc=-1,j;
	printf("请输入你的学号:\n");
	scanf("%s",csid);
	for(j=0;j<stui;j++)
	{
		if(strcmp(csid,stu[j].sid) == 0)
		{
			loc = j;
			break;
		}
	}
	if(j == stui && loc ==-1) 
	{
		printf("你输入的学号有误请查看！\n");
		
	}
	if(loc != -1)
	{
		printf("请输入你的旧密码：\n");
		scanf("%s",opwd);
		if(strcmp(opwd,stu[loc].pwd) == 0)
		{
			printf("请输入你的新密码：(6位数字)\n");
			scanf("%s",npwd);
			strcpy(stu[loc].pwd,npwd);
			printf("密码修改成功！\n");
		}
		else
		{
			printf("你输入的旧密码有误！\n");
			return 2;
		}
	}
	cover(stu,stui);
}


//显示在读学生信息显示的文件		--在tools中
void show_stu(void)
{
	debug("%s\n",__func__);
	Student stu[256] = {};
	readstu(stu);
	showstu(stu,stui);
}

//显示删除学生信息    访问del.txt
void show_stu_del(void)
{
	debug("%s\n",__func__);
	FILE* fp = fopen("./stuleaveschool.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
	}
	Student stu[256] = {};
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
	i = i-1;
	showstu(stu,i);
	fclose(fp);
	fp == NULL;
}

int main()
{
	//show_stu_del();//ok
	//show_stu();//ok
	//change_pwd();//ok
	//add_sco_v();//ok
	//add_sco();//ok
	//modify_stu();//ok
	//find_stu();//ok
	//stu_add();//ok
	//add_stu_v();//ok
	//del_stu();//ok
	modify_pwd();//ok
	return 0;
}

































