#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <time.h>
#define OK        1
#define ERROR     0
//结构体类型的定义
//改成单链表的一个节点类型，包含data和next域
typedef struct student
{
	int num;//学号
	char name[20];         //姓名
	int phoneNumber;  //手机号
	char gender;            //性别
	int age;               //年龄
	struct student *next;
}St;
/*typedef struct activity
{
	char activity[20];    //活动名字

	struct activity *next;
}Ac;*/
void Home()
{
    printf("                          ************欢迎来到社团管理系统！！！******************");
    printf("                                       请选择要执行的操作：\n");
    printf("                         |             1、增加成员信息                            |\n");
    printf("                         |             2、删除成员信息                            |\n");
    printf("                         |             3、查询成员信息                            |\n");
    printf("                         |             4、创建活动信息                            |\n");
    printf("                         |             5、修改活动信息                            |\n");
    printf("                         |             6、显示成员信息                            |\n");
    printf("                         |             0、退出系统                                |\n");
    printf("                          ************请输入您的选择：0-6之间的整数：************\n");
}
St *InitText()
{
   //s指向头结点
    FILE *file;//文件指针，通过file来操作文件
    St *s,*st,*s1;
    //初始化file
    s=(St *)malloc(sizeof(St));
    s->next=NULL;
    s1=s;//保持s1不动，始终指向头结点
    //1 打开文件
    file=fopen("D:\\file1.txt","r");
    if(file==NULL)
    {
        printf("打开文件失败\n");
        return 0;
    }
    //2 读文件
    while(1)
    {
    //(1)创建一个学生节点st
    st=(St *)malloc(sizeof(St));
    //(2)将文件中第一个学生的信息读到该节点stu中
    //EOF若读入为空，则结束
    if(fscanf(file,"%d %s %d %s %d ",&st->num,st->name,st->phoneNumber,st->gender,st->age)==EOF)
    {
        free(st);//动态回收点st所占的存储空间
        break;
    }
    //（3）节点st的next为空
      st->next=NULL;
      //头结点指向该节点gst
      s->next=st;
      s=st;
    }
    //3 关闭文件
    fclose(file);
    return s1;//返回头指针
}
void Login()//函数首部
//函数体
{
    //定义变量。数组，结构体等
    //用字符数组来存储字符串
    char username[20],password[20];
    int t=0;
    //赋初值通过等于号或键盘录入
    printf("                            *******************欢迎登陆社团管理系统*******************\n");
    printf("                           ·请输入用户名和密码：\n");
    printf("                            **********************************************************\n");
    while(1)
    {
    printf("                           ·请输入用户名：\n");
    //整型scanf("%d",&a);
   // scanf("%s",username);//数组名表示第一个元素的地址
   gets(username);
   printf("                           ·请输入密码：\n");
   gets(password);
    //计算
    //字符串比较函数strcmp(string cmpare)
    //格式：strcmp(字符串1，字符串2）==0则相等，否则不等
    if(strcmp(username,"root")==0&&strcmp(password,"123")==0)
    {
            printf("登陆成功\n");
        break;
    }
    else
        printf("用户名或密码输入错误，请重新输入！\n");
        t++;
		if(t==3)
        {
            printf("错误次数过多，系统自动退出！");
            exit(OK);
        }
    //输出或将值返回到调用该函数的主函数
    //printf("%s\n",username);
    //puts(username);
    }
}
void insert1(St *st)
{
    FILE *file;
    //1 打开文件
    file=fopen("D:\\file1.txt","a");
    if(file==NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    //2 写文件
    fprintf(file,"%d,%s,%d,%s,%d\n",st->num,st->name,st->phoneNumber,st->gender,st->age);
    //3 关闭文件
    fclose(file);
}
//在文件任意位置前插入一条学生信息
//将原文件内容清空，单链表中的内容重新在文件中写一遍

void insert2(St *h)
{
    St *st=h->next;
    FILE *file;
    //1 打开文件
    file=fopen("D:\\file1.txt","w");//w时将原文件的内容清空
    if(file==NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    //2 写文件
    while(st!=NULL)
    {
    fprintf(file,"%d,%s,%d,%s,%d\n",st->num,st->name,st->phoneNumber,st->gender,st->age);
    st=st->next;
    }
    //3 关闭文件
    fclose(file);
}
int isrepeatnum(St *h,int tnum)
{
    //从第一个学生开始扫描，只要不为空，则一直扫
    //为空，则停止扫描
    //对每个学生节点来说，判断所给的学号是否与该节点的学号相等，若相等，返回0直直接结束
    //否则扫描下一个学生节点，扫描完后都不相等，返回1
    St *st;//学生节点
    st=h->next;//初始化第一个学生
    while(st!=NULL)
    {
        if(tnum==st->num)
        return 0;
        else
            st=st->next;
    }
    return 1;
}
void add1(St *h,int tnum,char *tname,char *tgender,int tage,int tphoneNumber)
{
    St *newnode,*p;
    p=h;
    if(isrepeatnum(h,tnum)==0)
    {
        printf("学号重复，不能添加！\n");
        return ;
    }
    //1 创建新节点enwnode,next为空
    newnode=(St *)malloc(sizeof(St));
    newnode->next=NULL;
    //2 将形参的值依次赋值给新节点
    newnode->num=tnum;
    newnode->phoneNumber=tphoneNumber;
    newnode->age=tage;
    strcpy(newnode->name,tname);//字符串之间的赋值语句
    strcpy(newnode->gender,tgender);
    //3 找最后一个节点，让p指针指向他
    //只要学生节点不为空，就让p指向该学生
    while(p->next!=NULL)
    {
        p=p->next;
    }
    //4 让最后一个节点的p的next指向新节点newnode
    p->next=newnode;
    //5 在文件中插入该学生的信息
    insert1(newnode);
    printf("成功插入学生信息！\n");

}

void add2(St *h,int tnum,char *tname,char *tgender,int tage,int tphoneNumber,int pos)
 {
      St *newnode,*p;
      p=h;
    int count=1;
    if(isrepeatnum(h,tnum)==0)
    {
        printf("学号重复，不能添加！\n");
        return ;
    }
    //1 创建新节点enwnode,next为空
    newnode=(St *)malloc(sizeof(St));
    newnode->next=NULL;
    //2 将形参的值依次赋值给新节点
    newnode->num=tnum;
    newnode->phoneNumber=tphoneNumber;
    newnode->age=tage;
    strcpy(newnode->name,tname);//字符串之间的赋值语句
    strcpy(newnode->gender,tgender);
    //3 找pos位置前的一个节点，让p指针指向他
    //只要学生节点不为空，就让p指向该学生
    while(count<pos)
    {
        p=p->next;
        count++;
    }
    //4 让插入位置前的一个节点next指向新节点newnode
    newnode->next=p->next;
    p->next=newnode;
    //5 在文件中插入该学生的信息
    insert2(h);//传递头指针，单链表中所有节点信息重新写到文件中
    printf("成功插入学生信息！\n");
 }

void add(St *h)//形参的类型、个数和实参保持一致
{
    int n,tnum,tphoneNumber,tage,pos;
    char tname[20],tgender[20];
    printf("请输入1或2(1代表插入到最后，2代表插入到任意位置，输入其他值返回到主界面。)\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1:
            printf("\n请输入新成员的个人信息：\n\t学号\t姓名\t电话\t年龄\t性别\n");
            scanf("%d %s %d %d %s",&tnum,tname,tphoneNumber,tage,tgender);
            add1(h,tnum,tname,tphoneNumber,tage,tgender);
            break;
        case 2:
            printf("请输入要插入的位置：\n");
            scanf("%d",&pos);
            printf("在第%d个元素前插入！！\n",pos);
            printf("\n请输入新成员的个人信息：\n\t学号\t姓名\t电话\t年龄\t性别\n");
            scanf("%d %s %d %d %s",&tnum,tname,tphoneNumber,tage,tgender);
            add2(h,tnum,tname,tphoneNumber,tage,tgender,pos);
                break;
            default:printf("按任意键返回\n");
    }

}
//按学号删除学生信息
void del1(St *h,int tnum)
{
    St *pre;//当前节点的前驱结点
    St *st;//当前节点
    int isfound=0;//0表示没有找到学生信息，没有删除
    pre=h;
    st=h->next;
    while(st!=NULL)
    {
        if(st->num==tnum)
        {
            pre->next=st->next;
            free(st);
            isfound=1;
            break;
        }
        else
        {
            pre=pre->next;
            st=st->next;
        }
    }

    if(isfound==1)
    {
        insert2(h);
        printf("删除成功！\n");
    }
    else
        printf("没有找到该成员的信息！\n");

}
void del2(St *h,char *tname)
{
    St *pre;//当前节点的前驱结点
    St *st;//当前节点
    int isfound=0;//0表示没有找到学生信息，没有删除
    pre=h;
    st=h->next;
    while(st!=NULL)
    {
        if(strcmp(st->name,tname)==0)
        {
            pre->next=st->next;
            free(st);
            isfound++;//统计删除学生姓名为tname的个数
            st=pre->next;//注意，stu指向被删节点的下一个节点
        }
        else
        {
            pre=pre->next;
            st=st->next;
        }
    }

    if(isfound!=0)
    {
        insert2(h);
        printf("删除了%d个姓名为%s的成员！\n",isfound,tname);
    }
    else
        printf("没有找到该学生的信息！\n");

}
//成员信息的删除
void del(St *h)
{
    int n,tnum;
    char tname[20];
    printf("请输入1或2（1代表按学号删除，2代表按姓名删除，输入其他值返回主界面）\n");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        printf("请输入要删除的学生的学号：\n");
        scanf("%d",&tnum);
        del1(h,tnum);
        break;
    case 2:
        printf("请输入要删除的学生的姓名：\n");
        scanf("%s",tname);
        del2(h,tname);
        break;
        default:;
    }
}
St *query1(St *h,int tnum)//不带返回值
{
    St *st;
    st=h->next;
    while(st!=NULL)
    {
        if(st->num==tnum)
        {
            printf("********************");
            printf("学号：%d\n",st->num);
            printf("姓名：%s\n",st->name);
            printf("电话号：%s\n",st->phoneNumber);
            printf("性别：%s\n",st->gender);
            printf("年龄：%d\n",st->age);
            printf("********************");
            return;
        }
        else
            st=st->next;
    }
    printf("学号不存在，没有该成员！！");
}
void query2(St *h,char *tname)
{
    St *st;//学生结点
    int isfound=0;//计数，查找学生姓名为tname的个数
    st=h->next;
    while(st!=NULL)
    {
        if(strcmp(st->name,tname)==0)
        {
            isfound++;//统计找到学生姓名为tname的个数
            if(isfound==1)
            printf("*******************\n");
            printf("学号：%d\n",st->num);
            printf("姓名：%s\n",st->name);
            printf("电话号：%s\n",st->phoneNumber);
            printf("性别：%s\n",st->gender);
            printf("年龄：%d\n",st->age);
            printf("********************");
            st=st->next;//注意，st指向被删节点的下一个节点
        }
            st=st->next;
    }
    if(isfound!=0)
    {
        printf("查询到%d个姓名为%s的学生！\n",isfound,tname);
        printf("*******************\n");
    }
    else
        printf("查找失败，没有叫%s的学生！\n");
}
void query(St *h)
{
    int n,tnum;
    char tname[20];
    St *st;
    printf("请输入1或2（1代表按学号查找，2代表按姓名查找，输入其他值则返回主界面）\n");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        printf("请输入要查询的学生的学号：\n");
        scanf("%d",&tnum);
        //查询结果为学生的全部信息，即一个学生节点
        //若能查到，打印该学生的信息，若查不到，则没有该学生
        st=query1(h,tnum);
        if(st!=NULL)
        {
            printf("********************");
            printf("学号：%d\n",st->num);
            printf("姓名：%s\n",st->name);
            printf("电话号：%s\n",st->phoneNumber);
            printf("性别：%s\n",st->gender);
            printf("年龄：%d\n",st->age);
            printf("********************");
        }
        else
            printf("学号不存在，没有该学生！！");
        break;
    case 2:
        printf("请输入要查询的学生的姓名：\n");
        scanf("%s",tname);
        query2(h,tname);
        break;
        default:printf("按任意键返回\n");
    }
}
void show1(St *h)
{
    //只要学生节点不为空，则打印其信息到显示器上
    St *st=h->next;
    while(st!=NULL)
    {
        printf("%d,%s,%d,%s,%d\n",st->num,st->name,st->phoneNumber,st->gender,st->age);
        st=st->next;
    }
}

int main()
{
    int choice;
    St *head;
    //Ac *B;
    //head=InitText();
    Login();
    while(1)
    {
    Home();
    scanf("%d",&choice);
    if(choice==0)
        break;
     switch(choice)
     {
        case 1:add(head);break;//A为实参
        case 2:del(head);break;
        case 3:query(head);break;
        case 4:printf("hello");break;
        case 5:printf("hello");break;
        case 6:show1(head);break;
        default:printf("输入错误！请按任意键返回\n");
     }
    }
    return 0;
}
