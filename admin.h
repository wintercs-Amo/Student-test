#ifndef ADMIN_H
#define ADMIN_H

typedef struct Admin
{
    int id;
    char pwd[15];
    char ver;
}Admin;



//------主页面
int admin_face(void);

//------强制改密码，		
void forceModify_ad(void);

//修改自己的密码
void adModify(void);

//------密码验证
int check_ad(void);

//重置教师密码   
void tchModify(void);

//添加教师		
void addtch(void);

//删除教师    del_tch.txt  
void deltch(void);

//显示在职教师的txt文件    
void show_tch_stay(void);

//显示离职教师文件  del_tch.txt
void show_tch_del(void);

void unLock_tch(void);

void run_admin(void);




#endif//ADMIN_H
