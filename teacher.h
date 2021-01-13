#ifndef TEACHER_H
#define TEACHER_H

//结构
typedef struct Teacher
{
    char name[20];
    char sex[5];
    int id;
    char pwd[15];
    char ver;
}Teacher;

//界面
int tch_face(void);
//按钮
void run_tch(void);

//教师登录验证
void movetealock(Teacher* tea,int lock);
int forceModify_tea(void);
int check_tea(int id);
//单个、批量添加学生
void add_stu(void);
void add_stu_v(void);
//删除学生
void del_stu(void);
//找学生(按学号) 找到的是基本信息
void find_stu(void);
//教师修改学生信息
void modify_stu(void);
//教师单个、批量添加学生成绩
void add_sco(void);
void add_sco_v(void);
//教师重置密码
void change_pwd(void);
//显示在校生信息
void show_stu(void);
//显示不在校生信息
void show_stu_del(void);
//解锁学生账户
void unlock_stu(void);


#endif//TEACHER_H
