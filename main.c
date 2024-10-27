#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<windows.h> 
#include<stdbool.h>
#include<conio.h>
#include<time.h>
#define Max_books 1000   //最大存储图书数量 
#define Max_pass 6       //密码长度为6位 

//定义结构体
typedef struct books{
	char bookName[50];     //书名 
	char autherName[30];   //作者名 
	char isbn[20];         //ISBN编号
	char pub_unit[30];     //出版单位 
	char pub_time[30];     //出版时间 
	float price;           //单价 
	struct books *next;    //指针域 
}Books;

typedef struct user{
	char username[10];
	char password[Max_pass];
}User; 

//获得系统时间
void getTime(void)
{
	time_t tt;
    time(&tt);
    printf ( "当前本地时间为: %s\n", ctime(&tt));
} 

//登录功能
void login(void)
{
	FILE *fp;
	if((fp=fopen("userInfo.txt","r"))==NULL)
	{
		printf("无法正确打开用户信息文件！\n请检查“userInfo.txt”文件！\n");
		exit(0);
	}
	User login;
	char name[10];
	char pass[6];
	int i=0; 
	fscanf(fp,"%s %s",login.username,login.password);
	printf("\t************************\n");
	printf("\t    图书信息管理系统    \n");
	printf("\t************************\n");
	printf("\n请输入用户名：");
	scanf("%s",name); 
	printf("请输入密码："); 
	
//	密码星号显示模块begin 
    char ch; 
	while (1)
    {
        ch = getch();

        if (ch == 13)
            break;
        else if (ch == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else if (ch != ' ' && i < Max_pass)
        {
            printf("*");
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0'; 
//  密码星号显示模块end 
	
	if(strcmp(name,login.username)==0)
	{
		if(strcmp(pass,login.password)==0)
		{
			fclose(fp);
			return; 
		}
		else
		{
			printf("\n密码错误！\n");
			exit(0);
		}
	}
	else
	{
		printf("用户不存在！\n");
		exit(0); 
	}
}

//输出主菜单 
void mainTable(void)
{
	system("cls");
	getTime();
	printf("\t************************\n");
	printf("\t欢迎使用图书信息管理系统\n");
	printf("\t************************\n");
	printf("\t     1.录入图书信息     \n");
	printf("\t     2.浏览图书信息     \n");
	printf("\t     3.图书信息查询     \n");
	printf("\t     4.图书信息删除     \n");
	printf("\t     5.图书信息修改     \n");
	printf("\t     6.追加图书信息     \n");
	printf("\t     7.导出图书信息     \n");
	printf("\t     8.导入外部数据     \n");
	printf("\t     9.修改用户密码     \n");
	printf("\t     0.退出管理系统     \n");
	printf("\t************************\n");
	printf("\n说明：\n该管理系统提供两种初始化方式，分别是1与8，两者只能执行一个，当初始化数据后，如果想要增加信息，必须通过功能6\n");
} 

//检查ISBN是否重复 
bool is_isbn_unique(Books *head, const char *isbn) 
{
    Books *current = head->next;
    while (current != NULL) 
	{
        if (strcmp(current->isbn, isbn) == 0) 
		{
            return false;
        }
        current = current->next;
    }
    return true;
}

//录入图书信息
void insert(Books *head)
{
    int num;
    int i; 
    system("cls");
    printf("\t************************\n");
	printf("\t    录入图书信息模块    \n");
	printf("\t************************\n");
    printf("请输入要录入的图书数量(输入0退出该模块)：");
    scanf("%d", &num);
    if (num == 0)
	{
        system("cls");
        return;
    }
    for (i = 0; i < num; i++) 
	{
        Books *q = (Books *)malloc(sizeof(Books));
        if (q == NULL) 
		{
            printf("内存分配失败！\\\\\\\\n");
            exit(1);
        }
        printf("请输入第%d本书的书名：", i + 1);
        scanf("%s", q->bookName);
        printf("请输入第%d本书的作者：", i + 1);
        scanf("%s", q->autherName);
        bool is_input_correct = false;
        do{
            printf("请输入第%d本书的ISBN：", i + 1);
            scanf("%s", q->isbn);
            if (is_isbn_unique(head, q->isbn)) 
			{
                is_input_correct = true;
            } 
			else
			{
                printf("\n您输入的ISBN已经存在！每本书的ISBN是唯一的，请重新输入！\n");
            }
        } while (!is_input_correct);
        printf("请输入第%d本书的出版单位：", i + 1);
        scanf("%s", q->pub_unit);
        printf("请输入第%d本书的出版时间：", i + 1);
        scanf("%s", q->pub_time);
        printf("请输入第%d本书的单价(请务必输入数字！)：", i + 1);
        scanf("%f", &q->price);
        Books *p = head;
        while (p->next != NULL) 
		{
            p = p->next;
        }
        p->next = q;
        q->next = NULL;
    }
    system("cls");
}

//浏览图书信息
void shows(Books *head)
{
	system("cls");
	int count=0;
	char choice; 
	printf("\t************************\n");
	printf("\t    浏览图书信息模块    \n");
	printf("\t************************\n");
	Books *temp=head->next;
	printf("书名\t\t作者\t\tISBN\t\t出版单位\t\t出版时间\t单价\t\t\n");
	printf("****************************************************************************************\n");
	while(temp!=NULL)
	{
		printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
		temp=temp->next;
		count++;
	}
	printf("****************************************************************************************\n");
	printf("现存图书有%d本 最大存储容量为%d\n",count,Max_books);
	system("pause");
}

//查找数据通用函数
void find(Books *head,char input[])
{
	if(head==NULL)
	{
		printf("链表不存在！\n");
		return;
	}
	else
	{
		int count=0; 
		printf("查询结果如下：\n");
		Books *temp=head->next;
		while(temp!=NULL)
		{
			if(strcmp(temp->isbn,input)==0||strcmp(temp->bookName,input)==0||strcmp(temp->autherName,input)==0)
			{
				printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
				count++;
			}
			temp=temp->next;
		}
		if(count==0)
		{
			printf("没有相关的书籍信息！\n");
		}
		system("pause");
	}
} 

//图书信息查询 
void selects(Books *head)
{
	system("cls");
	int choice; 
	char input[50];
	printf("\t************************\n");
	printf("\t    查询图书信息模块    \n");
	printf("\t************************\n");
	printf("\t    1.使用ISBN查询      \n");
	printf("\t    2.使用书名查询      \n");
	printf("\t    3.使用作者名查询    \n");
	printf("\t    0.退出该模块        \n");
	printf("\t************************\n");
	do{
		printf("请选择要执行的操作：");
		scanf("%d",&choice);
		if(choice==0)
		{
			return;
		}
		else
		{
			switch(choice)
			{
				case 1:
					printf("请输入要查询书籍的ISBN编号：");
					scanf("%s",input);
					find(head,input);
					break;
				case 2:
					printf("请输入要查询书籍的书名：");
					scanf("%s",input);
					find(head,input);
					break;
				case 3:
					printf("请输入要查询书籍的作者名：");
					scanf("%s",input);
					find(head,input);
					break;
				default:
					printf("无效的操作！\n");
					break;
			}
		}
	}while(1);
}

//图书信息删除
void deletes(Books *head)
{
	char input[50];
	system("cls");
	printf("\t************************\n");
	printf("\t    删除图书信息模块    \n");
	printf("\t************************\n");
	printf("\n请输入书籍的ISBN编号以实现精确删除：");
	scanf("%s",input); 
	if(head==NULL)
	{
		printf("链表不存在！\n");
		return;
	}
	else
	{
		int count=0;
		Books *temp=head->next;
		Books *before=head;
		while(temp!=NULL)
		{
			if(strcmp(temp->isbn,input)==0)
			{
				count++;
				printf("查询到以下书籍信息：\n");
				printf("%s\t%s\t%s\t%s\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
				printf("\n是否要删除这本书籍信息？Y(y)orN(n)");
				char choice;
				scanf(" %c",&choice);
				if(choice=='Y'||choice=='y')
				{
					before->next=temp->next;
				}
			}
			temp=temp->next;
			before=before->next;
		}
		if(count==0)
		{
			printf("查无此书！\n");
			system("pause");
		}
	}
}

//修改数据通用函数
int change(Books *temp)
{
	char input[50];
	float price; 
	int choice;
	printf("\t1.修改书名\n");
	printf("\t2.修改作者名\n");
	printf("\t3.修改ISBN编号\n");
	printf("\t4.修改出版单位\n");
	printf("\t5.修改出版时间\n");
	printf("\t6.修改单价\n");
	printf("\t0.退出修改\n");
	do{
		printf("请选择要修改的内容：");
		scanf("%d",&choice);
		if(choice==0)
		{
			return 0;
		}
		else
		{
			switch(choice)
			{
				case 1:
					printf("请输入正确的书名：");
					scanf("%s",input); 
					strcpy(temp->bookName,input);
					return 1;
				case 2:
					printf("请输入正确的作者名：");
					scanf("%s",input); 
					strcpy(temp->autherName,input);
					return 1;
				case 3:
					printf("请输入正确的ISBN编号：");
					scanf("%s",input); 
					strcpy(temp->isbn,input);
					return 1;
				case 4:
					printf("请输入正确的出版单位：");
					scanf("%s",input); 
					strcpy(temp->pub_unit,input);
					return 1;
				case 5:
					printf("请输入正确的出版时间：");
					scanf("%s",input); 
					strcpy(temp->pub_time,input);
					return 1;
				case 6:
					printf("请输入正确的单价：");
					scanf("%f",&price); 
					temp->price=price;
					return 1;
				default:
					printf("无效的操作！\n");
					break;
			}
		}
	}while(choice);
	return 0;
} 

//图书信息修改
void alter(Books *head)
{
	char input[50]; 
	system("cls");
	printf("\t************************\n");
	printf("\t    修改图书信息模块    \n");
	printf("\t************************\n");
	printf("\n请输入要修改书籍的ISBN或书名：");
	scanf("%s",input);
	if(head==NULL)
	{
		printf("链表不存在！\n");
		return;
	}
	else
	{
		int count=0;
		Books *temp=head->next;
		while(temp!=NULL)
		{
			if(strcmp(temp->isbn,input)==0||strcmp(temp->bookName,input)==0)
			{
				count++;
				printf("查询到以下图书信息：\n");
				printf("%s\t%s\t%s\t%s\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
				printf("\n");
				if(change(temp)==1)
				{
					printf("修改成功！\n");
				}
				else
				{
					printf("修改失败！\n");
				} 
				
			}
			temp=temp->next;
		}
		if(count==0)
		{
			printf("查无此书！\n");
			system("pause");
		}
	}
}

//追加图书信息
void addInfo(Books *head)
{
	system("cls");
	printf("\t************************\n");
	printf("\t    追加图书信息模块    \n");
	printf("\t************************\n");
	printf("\n说明：该模块每次只能新增一条数据，且新增数据自动放到原有数据最后一条后面！\n");
	if(head==NULL)
	{
		printf("链表不存在！\n");
		return;
	}
	else
	{
		Books *newInfo=(Books *)malloc(sizeof(Books));
		Books *temp=head->next;
		Books *current=head;
		while(temp!=NULL)
		{
			temp=temp->next;
			current=current->next;
		} 
		current->next=newInfo;
		printf("请输入新增书籍的书名：");
		scanf("%s",newInfo->bookName);
		printf("请输入新增书籍的作者名：");
		scanf("%s",newInfo->autherName);
		printf("请输入新增书籍的ISBN编号：");
		scanf("%s",newInfo->isbn);		
		printf("请输入新增书籍的出版单位：");
		scanf("%s",newInfo->pub_unit);
		printf("请输入新增书籍的出版时间：");
		scanf("%s",newInfo->pub_time);
		printf("请输入新增书籍的单价：");
		scanf("%f",&newInfo->price);
		newInfo->next=NULL;
	}
} 

//导出图书信息
void download(Books *head)
{
	system("cls");
	printf("\t************************\n");
	printf("\t    导出图书信息模块    \n");
	printf("\t************************\n");
	printf("\n"); 
	FILE *fp;
	if((fp=fopen("booksInfo.txt","w+"))==NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	else
	{
		Books *temp=head->next;
		while(temp!=NULL)
		{
			fprintf(fp,"%s %s %s %s %s %.1f\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
			temp=temp->next;
		}
		fclose(fp);
		printf("\n图书信息已成功导出！\n请打开“booksInfo.txt”文件查看！\n");
		system("pause");
	} 
}

//导入外部数据 
void import(Books *head)
{
	system("cls");
	printf("\t************************\n");
	printf("\t    导入外部数据模块    \n");
	printf("\t************************\n");
	printf("\n说明：\n请确保外部数据文件的格式正确\n"); 
	FILE *fp;
	if((fp=fopen("books.txt","r"))==NULL)
	{
		printf("没有找到“books.txt”,请检查配置文件!\n");
		return;
	}
	else
	{
		char book[50];
		char auther[30];
		char Isbn[20];
		char pu[30];
		char pt[30];
		float money;
		printf("\n打开外部数据源成功！\n开始导入！\n");
		Books *temp=head;
		while(fscanf(fp,"%s %s %s %s %s %f",book,auther,Isbn,pu,pt,&money)!=EOF)
		{
			Books *n=(Books *)malloc(sizeof(Books));
			strcpy(n->bookName,book);
			strcpy(n->autherName,auther);
			strcpy(n->isbn,Isbn);
			strcpy(n->pub_unit,pu);
			strcpy(n->pub_time,pt);
			n->price=money;
			n->next=NULL;
			temp->next=n;
			temp=n;
		}
		printf("\n数据导入成功！\n");
		system("pause");
	}
}

//修改用户密码
void changepass(void)
{
    FILE *fp;
    User login;
    char newpass[6];
    char choice;
    if((fp=fopen("userInfo.txt","r"))==NULL)
    {
        printf("无法正确打开用户信息文件！\n请检查“userInfo.txt”文件！\n");
        return;
    }
    fscanf(fp, "%s %s", login.username, login.password);
    fclose(fp);

    system("cls");
    printf("\t************************\n");
    printf("\t    导出图书信息模块    \n");
    printf("\t************************\n");
    printf("\n请输入新的密码(6位)：");
    scanf("%s", newpass);
    printf("\n是否修改密码？Y(y) or N(n)");
    scanf(" %c", &choice);
    if(choice == 'Y' || choice == 'y')
    {
        FILE *fp2 = fopen("userInfo.txt", "w"); 
        if (fp2 == NULL) 
		{
            printf("无法打开文件以写入！\n");
            return;
        }
        fprintf(fp2, "%s %s", login.username, newpass); 
        fclose(fp2);
        printf("\n密码修改成功！\n重新登录以查看\n");
        exit(0);
    }
    else
    {
        printf("\n密码修改失败\n");
        return;
    }
}

//主函数 
int main(void)
{
	getTime();
	
	login();
	
	Books *head=(Books *)malloc(sizeof(Books)); 
	head->next=NULL;
	
	int choice;   //要执行的操作 
	do{
		mainTable();
		printf("\n请选择要执行的操作：");
		scanf("%d",&choice); 
		if(choice==0)
		{
			printf("\n退出图书信息管理系统！\n");
			printf("\n感谢您的使用\nDesigned and written by WIsteria\n");
			exit(0);
		}
		else
		{
			switch(choice)
			{
				case 1:
					insert(head);      //录入图书信息 
					break;
				case 2:
					shows(head);       //浏览图书信息 
					break;
				case 3:
					selects(head);     //查询图书信息 
					break;
				case 4:
					deletes(head);     //删除图书信息 
					break;
				case 5:
					alter(head);       //修改图书信息 
					break;
				case 6:
					addInfo(head);     //追加图书信息 
					break;
				case 7:
					download(head);    //导出图书信息 
					break;
				case 8:
					import(head);      //导入外部数据 
					break;
				case 9:
					changepass();      //修改登录密码 
					break; 
				default:
					printf("无效的操作！\n");
					break;
			}
		}
	}while(choice);	
	return 0;
}
