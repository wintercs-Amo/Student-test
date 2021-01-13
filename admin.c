#include "admin.h"
#include "tools.h"
#include <stdio.h>
#include "teacher.h"
#include <getch.h>
#include <string.h>
#include <stdlib.h>

//主页面
int admin_face(void)
{
	printf("-----------------------\n");
	printf("| 1.设置自己的密码     |\n");
	printf("| 2.修改教师密码       |\n");
	printf("| 3.添加老师           |\n");
	printf("| 4.删除教师           |\n");
	printf("| 5.显示在职教师       |\n");
	printf("| 6.显示离职教师       |\n");
	printf("| 7.解锁老师	       |\n");
	printf("| 8.退出	       |\n");
	printf(" -----------------------\n");
	int cmd = getch()-'0';
	return cmd;
}

//	读入在职教师文件
int readtch(Teacher tch[])
{
	FILE * frp = fopen("./tch.txt","r");
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
		fscanf(frp,"%s %s %d %s %hhd",tch[i].name,tch[i].sex,&tch[i].id,tch[i].pwd,&tch[i].ver);
		i++;
	}
	int tchi = i-1;
	fclose(frp);
	frp = NULL;
	return tchi;
}
//	重写在职老师文件
void write_tch(Teacher tch[],int tchi) 
{
	FILE * fwp = fopen("./tch.txt","w");
	if(fwp == NULL)
	{
		perror("fopen");
	}
	for(int i = 0; i<tchi; i++)
	{
		if(tch[i].ver == 0 && tch[i].ver == 1)
		fprintf(fwp,"%s %s %d %s %hhd\n",tch[i].name,tch[i].sex,tch[i].id,tch[i].pwd,tch[i].ver);
	}
	fclose(fwp);
	fwp = NULL;
}
//	读取离职教师文件
int readtch_leave(Teacher tch[])
{
	FILE * frp = fopen("./tchleave.txt","r");
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
		fscanf(frp,"%s %s %d %s %hhd",tch[i].name,tch[i].sex,&tch[i].id,tch[i].pwd,&tch[i].ver);
		i++;
	}
	int tchi = i-1;
	fclose(frp);
	frp = NULL;
	return tchi;
}

//读取被锁定的教师文件
int readtch_lock(Teacher tch[])		
{
	FILE * frp = fopen("./tchlock.txt","r");
	if(frp == NULL)
	{
		perror("fopen");
	}
	int ret,i=0,jud=1;
	while((ret = fgetc(frp) != EOF))
	{
		if(jud == 1)
		{
			fseek(frp,-1,SEEK_CUR);
			jud = 0;
		}
		fscanf(frp,"%s %s %d %s %hhd",tch[i].name,tch[i].sex,&tch[i].id,tch[i].pwd,&tch[i].ver);
		i++;
	}
	int tchi = i-1;
	fclose(frp);
	frp = NULL;
	return tchi;
}

//重写被锁定的教师文件
void write_unLock_tch(Teacher tch[], int tchi)
{
	int i = 0;
	FILE * fwp = fopen("./tchlock.txt","w");
	if(fwp == NULL)
	{
		perror("fopen");
	}
	for(i = 0; i<tchi; i++)
	{
		if(tch[i].ver != 0)
		{
			scanf("%*c");
			fprintf(fwp,"%s %s %d %s %hhd\n",tch[i].name,tch[i].sex,tch[i].id,tch[i].pwd,tch[i].ver);
		}
	}
	fclose(fwp);
	fwp = NULL;
}
	
//移到离职教师文件
void add_tch_leave(Teacher tch[],int tchi)
{
	FILE * fap = fopen("./tchleave.txt","a");
	if(fap == NULL)
	{
		perror("fopen");
	}
	for(int i = 0; i<tchi; i++)
	{
		if(tch[i].ver == -1)
		{
			fprintf(fap,"%s %s %d %s %hhd\n",tch[i].name,tch[i].sex,tch[i].id,tch[i].pwd,tch[i].ver);
		}
	}
	fclose(fap);
	fap = NULL;
	return;
}	
	
//读取校长文件
void read_ad(struct Admin *ad)
{
	FILE * fp = fopen("./ad.txt","r");
	if(fp == NULL)
	{
		perror("fopen");
		return;
	}
	fscanf(fp,"%d %s %hhd",&ad->id,ad->pwd,&ad->ver);
	fclose(fp);
	fp = NULL;
	return;
}

//重写校长文件
void write_ad(struct Admin *ad)
{
		FILE * fwp = fopen("./ad.txt","w");
		if(fwp == NULL)
		{
			perror("fopen");
			return;
		}
		fprintf(fwp,"%d %s %hhd\n",ad->id,ad->pwd,ad->ver);
		fclose(fwp);
		fwp = NULL;
		return;
}



//强制改密码，		--tools中
void forceModify_ad(void)
{
	Admin ad = {};
	read_ad(&ad);	//	读入校长
	if(ad.ver == 0)
	{

		printf("第一次登陆强制修改密码！\n");
		printf("请输入新密码: ");
		coverKey(ad.pwd);	//	隐藏密码
		ad.ver = 1;
		write_ad(&ad);		//	重写校长
		printf("修改成功！\n");
		anykey_continue();
	}
	return;
}

//登录验证
int check_ad(void)
{
	int k_id;		//	定义验证密码
	char k_pwd[15];
    Admin ad = {};
    read_ad(&ad);	//	读入校长文件
	printf("------校长登录------\n");
    printf("请输入id号：");
    scanf("%d",&k_id);
    scanf("%*c");
    printf("请输入密码：");
    coverKey(k_pwd);	//	隐藏密码
	if(ad.id == k_id)
    {
		if(strcmp(ad.pwd,k_pwd))    	
    	{
    		printf("\n密码不正确！\n");
    		anykey_continue();
			return 0;
    	}
    }
    else
    {
    	printf("没有这个ID,请重试!\n");
    	anykey_continue();
    	return 0;
    }
    return 1;
}


//修改自己的密码
void adModify(void)
{
	Admin ad = {};
	read_ad(&ad);		//	读入校长文件
	char oldpwd[15] = {};	
	strcpy(oldpwd,ad.pwd);
	FILE * fwp = fopen("./ad.txt","w");
	if(fwp == NULL)
	{
		perror("fopen");
		return;
	}
	printf("请输入新密码：");
	coverKey(ad.pwd);	//	隐藏密码
	char repwd[15] = {};
	printf("\n");
	fflush(stdout);
	printf("请再输一遍：\n");
	coverKey(repwd);	//	隐藏密码
	if(!strcmp(repwd,ad.pwd))
	{	
		fprintf(fwp,"%d %s %hhd\n",ad.id,ad.pwd,ad.ver);
		printf("修改成功！\n");
		anykey_continue();
	}
	else
	{
		fprintf(fwp,"%d %s %hhd\n",ad.id,oldpwd,ad.ver);
		printf("两次密码不相同，请重试！\n");
		scanf("%*c");
		return;
	}
	fclose(fwp);
	fwp = NULL;
}

//重置教师密码   --tools中
void tchModify(void)
{
	int i = 0,tchi = 0;
	Teacher tch[256] = {};
	tchi = readtch(tch);	//	读取在职教师文件，返回教师数量
	long tchid = 0;
	printf("请输入要修改密码的老师ID：");
	scanf("%ld",&tchid);
	for(i = 0; i<tchi; i++)
	{
		if(tchid == tch[i].id)
		{
			printf("请输入新密码：");
			scanf("%s",tch[i].pwd);
			break;
		}
	}
	if(i == tchi)
	{
		printf("输入的ID错误，请重试！\n");
		anykey_continue();
		return;
	}
	write_tch(tch,tchi);		//	重写在职老师文件
	printf("修改成功！\n");
	anykey_continue();
}

//添加教师		--tools中
void addtch(void)
{
	FILE * fap = fopen("./tch.txt","a");
	if(NULL == fap)
	{
		perror("fopen kk");
		return;
	}
	Teacher tch = {.pwd = "123456",.ver = 0};
	printf("输入要添加的教师姓名：");
	scanf("%s",tch.name);
	printf("输入要添加的教师性别：");
	scanf("%s",tch.sex);
	printf("输入要添加的教师ID：");
	scanf("%d",&tch.id);
	fprintf(fap,"%s %s %d %s %hhd\n",tch.name,tch.sex,tch.id,tch.pwd,tch.ver);
	fclose(fap);
	fap = NULL;
	printf("添加成功！\n");
	anykey_continue();
	return;
}

//删除教师    del_tch.txt  --tools中
void deltch(void)
{
	int tchi = 0, i = 0;
	Teacher tch[256] = {};
	tchi = readtch(tch);		//	读入在职教师文件
	int tchid = 0;
	printf("请输入要删除的老师ID：");
	scanf("%d",&tchid);
	for(i = 0; i<tchi; i++)
	{
		if(tchid == tch[i].id)
		{
			tch[i].ver = -1;
			break;
		}
	}
	if(i == tchi)
	{
		printf("输入的ID错误，请重试！\n");
		anykey_continue();
		return;
	}
	write_tch(tch,tchi);		//	重写在职教师文件
	add_tch_leave(tch,tchi);	//	移到离职教师文件
	printf("删除成功！");
	anykey_continue();
}


//显示在职教师的txt文件    --tools中
void show_tch_stay(void)
{
	int tchi = 0;
	Teacher tch[256] = {};
	tchi = readtch(tch);
	for(int i = 0; i<tchi; i++)
	{
		printf("姓名：%s 	性别：%s	 ID：%d\n",tch[i].name,tch[i].sex,tch[i].id);
	}
	anykey_continue();

}

//显示离职教师文件  del_tch.txt
void show_tch_del(void)
{
	int tchi = 0;
	Teacher tch[256] = {};
	tchi = readtch_leave(tch);
	for(int i = 0; i<tchi; i++)
	{
		printf("姓名：%s 	性别：%s	 ID：%d\n",tch[i].name,tch[i].sex,tch[i].id);
	}
	anykey_continue();
}

//移到被锁定教师文件
void add_tch_lock(Teacher tch[],int i)
{
	FILE * fap = fopen("./tch.txt","a");
	if(NULL == fap)
	{
		perror("fopen");
		return;
	}
	fprintf(fap,"%s %s %d %s %hhd\n",tch[i].name,tch[i].sex,tch[i].id,tch[i].pwd,tch[i].ver);
	fclose(fap);
	fap = NULL;
	return;
}

//解锁老师
void unLock_tch(void)
{
	int i = 0,tchi = 0;
	Teacher tch[256] = {};
	tchi = readtch_lock(tch);	//读取被锁定的教师文件
	int tchid = 0;
	printf("请输入要解锁的教师ID：");
	scanf("%d",&tchid);
	for(i = 0; i<tchi; i++)
	{
		if(tch[i].id == tchid)
		{
			tch[i].ver = 0;
			break;
		}
	}
	if(i == tchi)
	{
		printf("ID有误!\n");
		anykey_continue();
		return;
	}
	add_tch_lock(tch,i);
	write_unLock_tch(tch,tchi);		//重写被锁定的教师文件
	printf("解锁成功！\n");
	anykey_continue();
}

void run_admin(void)
{
	forceModify_ad();	//	强制修改密码
	if(check_ad())		//	如果登入成功
	{
		for(;;)
		{
			system("clear");
			switch(admin_face())
			{
				case 1:
					adModify();
				break;
				case 2:
					tchModify();
				break;
				case 3:
					addtch();
				break;
				case 4:
					deltch();
				break;
				case 5:
					show_tch_stay();
				break;
				case 6:
					show_tch_del();
				break;
				case 7:
					unLock_tch();
				break;
				case 8:
					exit(0);
			}
		}
	}
}
