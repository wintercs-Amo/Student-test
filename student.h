#ifndef STUDENT_H
#define STUDENT_H

//结构
typedef struct Student
{
    char name[20];
    char sex[5];
    char sid[20];
    char pwd[15];
    float chn;    	//语文分
    float math;		//数学分
    float eng;	  	//英语分
    int ver;
    int times;
}Student;
int check_stu(int id);
void score(void);
void stuModify(void);
void show_self(void);
void run_stu(void);


#endif//STUDENT_H

