#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <time.h>
#define OK        1
#define ERROR     0
//�ṹ�����͵Ķ���
//�ĳɵ������һ���ڵ����ͣ�����data��next��
typedef struct student
{
	int num;//ѧ��
	char name[20];         //����
	int phoneNumber;  //�ֻ���
	char gender;            //�Ա�
	int age;               //����
	struct student *next;
}St;
/*typedef struct activity
{
	char activity[20];    //�����

	struct activity *next;
}Ac;*/
void Home()
{
    printf("                          ************��ӭ�������Ź���ϵͳ������******************");
    printf("                                       ��ѡ��Ҫִ�еĲ�����\n");
    printf("                         |             1�����ӳ�Ա��Ϣ                            |\n");
    printf("                         |             2��ɾ����Ա��Ϣ                            |\n");
    printf("                         |             3����ѯ��Ա��Ϣ                            |\n");
    printf("                         |             4���������Ϣ                            |\n");
    printf("                         |             5���޸Ļ��Ϣ                            |\n");
    printf("                         |             6����ʾ��Ա��Ϣ                            |\n");
    printf("                         |             0���˳�ϵͳ                                |\n");
    printf("                          ************����������ѡ��0-6֮���������************\n");
}
St *InitText()
{
   //sָ��ͷ���
    FILE *file;//�ļ�ָ�룬ͨ��file�������ļ�
    St *s,*st,*s1;
    //��ʼ��file
    s=(St *)malloc(sizeof(St));
    s->next=NULL;
    s1=s;//����s1������ʼ��ָ��ͷ���
    //1 ���ļ�
    file=fopen("D:\\file1.txt","r");
    if(file==NULL)
    {
        printf("���ļ�ʧ��\n");
        return 0;
    }
    //2 ���ļ�
    while(1)
    {
    //(1)����һ��ѧ���ڵ�st
    st=(St *)malloc(sizeof(St));
    //(2)���ļ��е�һ��ѧ������Ϣ�����ýڵ�stu��
    //EOF������Ϊ�գ������
    if(fscanf(file,"%d %s %d %s %d ",&st->num,st->name,st->phoneNumber,st->gender,st->age)==EOF)
    {
        free(st);//��̬���յ�st��ռ�Ĵ洢�ռ�
        break;
    }
    //��3���ڵ�st��nextΪ��
      st->next=NULL;
      //ͷ���ָ��ýڵ�gst
      s->next=st;
      s=st;
    }
    //3 �ر��ļ�
    fclose(file);
    return s1;//����ͷָ��
}
void Login()//�����ײ�
//������
{
    //������������飬�ṹ���
    //���ַ��������洢�ַ���
    char username[20],password[20];
    int t=0;
    //����ֵͨ�����ںŻ����¼��
    printf("                            *******************��ӭ��½���Ź���ϵͳ*******************\n");
    printf("                           ���������û��������룺\n");
    printf("                            **********************************************************\n");
    while(1)
    {
    printf("                           ���������û�����\n");
    //����scanf("%d",&a);
   // scanf("%s",username);//��������ʾ��һ��Ԫ�صĵ�ַ
   gets(username);
   printf("                           �����������룺\n");
   gets(password);
    //����
    //�ַ����ȽϺ���strcmp(string cmpare)
    //��ʽ��strcmp(�ַ���1���ַ���2��==0����ȣ����򲻵�
    if(strcmp(username,"root")==0&&strcmp(password,"123")==0)
    {
            printf("��½�ɹ�\n");
        break;
    }
    else
        printf("�û�������������������������룡\n");
        t++;
		if(t==3)
        {
            printf("����������࣬ϵͳ�Զ��˳���");
            exit(OK);
        }
    //�����ֵ���ص����øú�����������
    //printf("%s\n",username);
    //puts(username);
    }
}
void insert1(St *st)
{
    FILE *file;
    //1 ���ļ�
    file=fopen("D:\\file1.txt","a");
    if(file==NULL)
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    //2 д�ļ�
    fprintf(file,"%d,%s,%d,%s,%d\n",st->num,st->name,st->phoneNumber,st->gender,st->age);
    //3 �ر��ļ�
    fclose(file);
}
//���ļ�����λ��ǰ����һ��ѧ����Ϣ
//��ԭ�ļ�������գ��������е������������ļ���дһ��

void insert2(St *h)
{
    St *st=h->next;
    FILE *file;
    //1 ���ļ�
    file=fopen("D:\\file1.txt","w");//wʱ��ԭ�ļ����������
    if(file==NULL)
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    //2 д�ļ�
    while(st!=NULL)
    {
    fprintf(file,"%d,%s,%d,%s,%d\n",st->num,st->name,st->phoneNumber,st->gender,st->age);
    st=st->next;
    }
    //3 �ر��ļ�
    fclose(file);
}
int isrepeatnum(St *h,int tnum)
{
    //�ӵ�һ��ѧ����ʼɨ�裬ֻҪ��Ϊ�գ���һֱɨ
    //Ϊ�գ���ֹͣɨ��
    //��ÿ��ѧ���ڵ���˵���ж�������ѧ���Ƿ���ýڵ��ѧ����ȣ�����ȣ�����0ֱֱ�ӽ���
    //����ɨ����һ��ѧ���ڵ㣬ɨ����󶼲���ȣ�����1
    St *st;//ѧ���ڵ�
    st=h->next;//��ʼ����һ��ѧ��
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
        printf("ѧ���ظ���������ӣ�\n");
        return ;
    }
    //1 �����½ڵ�enwnode,nextΪ��
    newnode=(St *)malloc(sizeof(St));
    newnode->next=NULL;
    //2 ���βε�ֵ���θ�ֵ���½ڵ�
    newnode->num=tnum;
    newnode->phoneNumber=tphoneNumber;
    newnode->age=tage;
    strcpy(newnode->name,tname);//�ַ���֮��ĸ�ֵ���
    strcpy(newnode->gender,tgender);
    //3 �����һ���ڵ㣬��pָ��ָ����
    //ֻҪѧ���ڵ㲻Ϊ�գ�����pָ���ѧ��
    while(p->next!=NULL)
    {
        p=p->next;
    }
    //4 �����һ���ڵ��p��nextָ���½ڵ�newnode
    p->next=newnode;
    //5 ���ļ��в����ѧ������Ϣ
    insert1(newnode);
    printf("�ɹ�����ѧ����Ϣ��\n");

}

void add2(St *h,int tnum,char *tname,char *tgender,int tage,int tphoneNumber,int pos)
 {
      St *newnode,*p;
      p=h;
    int count=1;
    if(isrepeatnum(h,tnum)==0)
    {
        printf("ѧ���ظ���������ӣ�\n");
        return ;
    }
    //1 �����½ڵ�enwnode,nextΪ��
    newnode=(St *)malloc(sizeof(St));
    newnode->next=NULL;
    //2 ���βε�ֵ���θ�ֵ���½ڵ�
    newnode->num=tnum;
    newnode->phoneNumber=tphoneNumber;
    newnode->age=tage;
    strcpy(newnode->name,tname);//�ַ���֮��ĸ�ֵ���
    strcpy(newnode->gender,tgender);
    //3 ��posλ��ǰ��һ���ڵ㣬��pָ��ָ����
    //ֻҪѧ���ڵ㲻Ϊ�գ�����pָ���ѧ��
    while(count<pos)
    {
        p=p->next;
        count++;
    }
    //4 �ò���λ��ǰ��һ���ڵ�nextָ���½ڵ�newnode
    newnode->next=p->next;
    p->next=newnode;
    //5 ���ļ��в����ѧ������Ϣ
    insert2(h);//����ͷָ�룬�����������нڵ���Ϣ����д���ļ���
    printf("�ɹ�����ѧ����Ϣ��\n");
 }

void add(St *h)//�βε����͡�������ʵ�α���һ��
{
    int n,tnum,tphoneNumber,tage,pos;
    char tname[20],tgender[20];
    printf("������1��2(1������뵽���2������뵽����λ�ã���������ֵ���ص������档)\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1:
            printf("\n�������³�Ա�ĸ�����Ϣ��\n\tѧ��\t����\t�绰\t����\t�Ա�\n");
            scanf("%d %s %d %d %s",&tnum,tname,tphoneNumber,tage,tgender);
            add1(h,tnum,tname,tphoneNumber,tage,tgender);
            break;
        case 2:
            printf("������Ҫ�����λ�ã�\n");
            scanf("%d",&pos);
            printf("�ڵ�%d��Ԫ��ǰ���룡��\n",pos);
            printf("\n�������³�Ա�ĸ�����Ϣ��\n\tѧ��\t����\t�绰\t����\t�Ա�\n");
            scanf("%d %s %d %d %s",&tnum,tname,tphoneNumber,tage,tgender);
            add2(h,tnum,tname,tphoneNumber,tage,tgender,pos);
                break;
            default:printf("�����������\n");
    }

}
//��ѧ��ɾ��ѧ����Ϣ
void del1(St *h,int tnum)
{
    St *pre;//��ǰ�ڵ��ǰ�����
    St *st;//��ǰ�ڵ�
    int isfound=0;//0��ʾû���ҵ�ѧ����Ϣ��û��ɾ��
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
        printf("ɾ���ɹ���\n");
    }
    else
        printf("û���ҵ��ó�Ա����Ϣ��\n");

}
void del2(St *h,char *tname)
{
    St *pre;//��ǰ�ڵ��ǰ�����
    St *st;//��ǰ�ڵ�
    int isfound=0;//0��ʾû���ҵ�ѧ����Ϣ��û��ɾ��
    pre=h;
    st=h->next;
    while(st!=NULL)
    {
        if(strcmp(st->name,tname)==0)
        {
            pre->next=st->next;
            free(st);
            isfound++;//ͳ��ɾ��ѧ������Ϊtname�ĸ���
            st=pre->next;//ע�⣬stuָ��ɾ�ڵ����һ���ڵ�
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
        printf("ɾ����%d������Ϊ%s�ĳ�Ա��\n",isfound,tname);
    }
    else
        printf("û���ҵ���ѧ������Ϣ��\n");

}
//��Ա��Ϣ��ɾ��
void del(St *h)
{
    int n,tnum;
    char tname[20];
    printf("������1��2��1����ѧ��ɾ����2��������ɾ������������ֵ���������棩\n");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        printf("������Ҫɾ����ѧ����ѧ�ţ�\n");
        scanf("%d",&tnum);
        del1(h,tnum);
        break;
    case 2:
        printf("������Ҫɾ����ѧ����������\n");
        scanf("%s",tname);
        del2(h,tname);
        break;
        default:;
    }
}
St *query1(St *h,int tnum)//��������ֵ
{
    St *st;
    st=h->next;
    while(st!=NULL)
    {
        if(st->num==tnum)
        {
            printf("********************");
            printf("ѧ�ţ�%d\n",st->num);
            printf("������%s\n",st->name);
            printf("�绰�ţ�%s\n",st->phoneNumber);
            printf("�Ա�%s\n",st->gender);
            printf("���䣺%d\n",st->age);
            printf("********************");
            return;
        }
        else
            st=st->next;
    }
    printf("ѧ�Ų����ڣ�û�иó�Ա����");
}
void query2(St *h,char *tname)
{
    St *st;//ѧ�����
    int isfound=0;//����������ѧ������Ϊtname�ĸ���
    st=h->next;
    while(st!=NULL)
    {
        if(strcmp(st->name,tname)==0)
        {
            isfound++;//ͳ���ҵ�ѧ������Ϊtname�ĸ���
            if(isfound==1)
            printf("*******************\n");
            printf("ѧ�ţ�%d\n",st->num);
            printf("������%s\n",st->name);
            printf("�绰�ţ�%s\n",st->phoneNumber);
            printf("�Ա�%s\n",st->gender);
            printf("���䣺%d\n",st->age);
            printf("********************");
            st=st->next;//ע�⣬stָ��ɾ�ڵ����һ���ڵ�
        }
            st=st->next;
    }
    if(isfound!=0)
    {
        printf("��ѯ��%d������Ϊ%s��ѧ����\n",isfound,tname);
        printf("*******************\n");
    }
    else
        printf("����ʧ�ܣ�û�н�%s��ѧ����\n");
}
void query(St *h)
{
    int n,tnum;
    char tname[20];
    St *st;
    printf("������1��2��1����ѧ�Ų��ң�2�����������ң���������ֵ�򷵻������棩\n");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        printf("������Ҫ��ѯ��ѧ����ѧ�ţ�\n");
        scanf("%d",&tnum);
        //��ѯ���Ϊѧ����ȫ����Ϣ����һ��ѧ���ڵ�
        //���ܲ鵽����ӡ��ѧ������Ϣ�����鲻������û�и�ѧ��
        st=query1(h,tnum);
        if(st!=NULL)
        {
            printf("********************");
            printf("ѧ�ţ�%d\n",st->num);
            printf("������%s\n",st->name);
            printf("�绰�ţ�%s\n",st->phoneNumber);
            printf("�Ա�%s\n",st->gender);
            printf("���䣺%d\n",st->age);
            printf("********************");
        }
        else
            printf("ѧ�Ų����ڣ�û�и�ѧ������");
        break;
    case 2:
        printf("������Ҫ��ѯ��ѧ����������\n");
        scanf("%s",tname);
        query2(h,tname);
        break;
        default:printf("�����������\n");
    }
}
void show1(St *h)
{
    //ֻҪѧ���ڵ㲻Ϊ�գ����ӡ����Ϣ����ʾ����
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
        case 1:add(head);break;//AΪʵ��
        case 2:del(head);break;
        case 3:query(head);break;
        case 4:printf("hello");break;
        case 5:printf("hello");break;
        case 6:show1(head);break;
        default:printf("��������밴���������\n");
     }
    }
    return 0;
}
