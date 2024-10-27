#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<windows.h> 
#include<stdbool.h>
#include<conio.h>
#include<time.h>
#define Max_books 1000   //���洢ͼ������ 
#define Max_pass 6       //���볤��Ϊ6λ 

//����ṹ��
typedef struct books{
	char bookName[50];     //���� 
	char autherName[30];   //������ 
	char isbn[20];         //ISBN���
	char pub_unit[30];     //���浥λ 
	char pub_time[30];     //����ʱ�� 
	float price;           //���� 
	struct books *next;    //ָ���� 
}Books;

typedef struct user{
	char username[10];
	char password[Max_pass];
}User; 

//���ϵͳʱ��
void getTime(void)
{
	time_t tt;
    time(&tt);
    printf ( "��ǰ����ʱ��Ϊ: %s\n", ctime(&tt));
} 

//��¼����
void login(void)
{
	FILE *fp;
	if((fp=fopen("userInfo.txt","r"))==NULL)
	{
		printf("�޷���ȷ���û���Ϣ�ļ���\n���顰userInfo.txt���ļ���\n");
		exit(0);
	}
	User login;
	char name[10];
	char pass[6];
	int i=0; 
	fscanf(fp,"%s %s",login.username,login.password);
	printf("\t************************\n");
	printf("\t    ͼ����Ϣ����ϵͳ    \n");
	printf("\t************************\n");
	printf("\n�������û�����");
	scanf("%s",name); 
	printf("���������룺"); 
	
//	�����Ǻ���ʾģ��begin 
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
//  �����Ǻ���ʾģ��end 
	
	if(strcmp(name,login.username)==0)
	{
		if(strcmp(pass,login.password)==0)
		{
			fclose(fp);
			return; 
		}
		else
		{
			printf("\n�������\n");
			exit(0);
		}
	}
	else
	{
		printf("�û������ڣ�\n");
		exit(0); 
	}
}

//������˵� 
void mainTable(void)
{
	system("cls");
	getTime();
	printf("\t************************\n");
	printf("\t��ӭʹ��ͼ����Ϣ����ϵͳ\n");
	printf("\t************************\n");
	printf("\t     1.¼��ͼ����Ϣ     \n");
	printf("\t     2.���ͼ����Ϣ     \n");
	printf("\t     3.ͼ����Ϣ��ѯ     \n");
	printf("\t     4.ͼ����Ϣɾ��     \n");
	printf("\t     5.ͼ����Ϣ�޸�     \n");
	printf("\t     6.׷��ͼ����Ϣ     \n");
	printf("\t     7.����ͼ����Ϣ     \n");
	printf("\t     8.�����ⲿ����     \n");
	printf("\t     9.�޸��û�����     \n");
	printf("\t     0.�˳�����ϵͳ     \n");
	printf("\t************************\n");
	printf("\n˵����\n�ù���ϵͳ�ṩ���ֳ�ʼ����ʽ���ֱ���1��8������ֻ��ִ��һ��������ʼ�����ݺ������Ҫ������Ϣ������ͨ������6\n");
} 

//���ISBN�Ƿ��ظ� 
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

//¼��ͼ����Ϣ
void insert(Books *head)
{
    int num;
    int i; 
    system("cls");
    printf("\t************************\n");
	printf("\t    ¼��ͼ����Ϣģ��    \n");
	printf("\t************************\n");
    printf("������Ҫ¼���ͼ������(����0�˳���ģ��)��");
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
            printf("�ڴ����ʧ�ܣ�\\\\\\\\n");
            exit(1);
        }
        printf("�������%d�����������", i + 1);
        scanf("%s", q->bookName);
        printf("�������%d��������ߣ�", i + 1);
        scanf("%s", q->autherName);
        bool is_input_correct = false;
        do{
            printf("�������%d�����ISBN��", i + 1);
            scanf("%s", q->isbn);
            if (is_isbn_unique(head, q->isbn)) 
			{
                is_input_correct = true;
            } 
			else
			{
                printf("\n�������ISBN�Ѿ����ڣ�ÿ�����ISBN��Ψһ�ģ����������룡\n");
            }
        } while (!is_input_correct);
        printf("�������%d����ĳ��浥λ��", i + 1);
        scanf("%s", q->pub_unit);
        printf("�������%d����ĳ���ʱ�䣺", i + 1);
        scanf("%s", q->pub_time);
        printf("�������%d����ĵ���(������������֣�)��", i + 1);
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

//���ͼ����Ϣ
void shows(Books *head)
{
	system("cls");
	int count=0;
	char choice; 
	printf("\t************************\n");
	printf("\t    ���ͼ����Ϣģ��    \n");
	printf("\t************************\n");
	Books *temp=head->next;
	printf("����\t\t����\t\tISBN\t\t���浥λ\t\t����ʱ��\t����\t\t\n");
	printf("****************************************************************************************\n");
	while(temp!=NULL)
	{
		printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
		temp=temp->next;
		count++;
	}
	printf("****************************************************************************************\n");
	printf("�ִ�ͼ����%d�� ���洢����Ϊ%d\n",count,Max_books);
	system("pause");
}

//��������ͨ�ú���
void find(Books *head,char input[])
{
	if(head==NULL)
	{
		printf("�������ڣ�\n");
		return;
	}
	else
	{
		int count=0; 
		printf("��ѯ������£�\n");
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
			printf("û����ص��鼮��Ϣ��\n");
		}
		system("pause");
	}
} 

//ͼ����Ϣ��ѯ 
void selects(Books *head)
{
	system("cls");
	int choice; 
	char input[50];
	printf("\t************************\n");
	printf("\t    ��ѯͼ����Ϣģ��    \n");
	printf("\t************************\n");
	printf("\t    1.ʹ��ISBN��ѯ      \n");
	printf("\t    2.ʹ��������ѯ      \n");
	printf("\t    3.ʹ����������ѯ    \n");
	printf("\t    0.�˳���ģ��        \n");
	printf("\t************************\n");
	do{
		printf("��ѡ��Ҫִ�еĲ�����");
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
					printf("������Ҫ��ѯ�鼮��ISBN��ţ�");
					scanf("%s",input);
					find(head,input);
					break;
				case 2:
					printf("������Ҫ��ѯ�鼮��������");
					scanf("%s",input);
					find(head,input);
					break;
				case 3:
					printf("������Ҫ��ѯ�鼮����������");
					scanf("%s",input);
					find(head,input);
					break;
				default:
					printf("��Ч�Ĳ�����\n");
					break;
			}
		}
	}while(1);
}

//ͼ����Ϣɾ��
void deletes(Books *head)
{
	char input[50];
	system("cls");
	printf("\t************************\n");
	printf("\t    ɾ��ͼ����Ϣģ��    \n");
	printf("\t************************\n");
	printf("\n�������鼮��ISBN�����ʵ�־�ȷɾ����");
	scanf("%s",input); 
	if(head==NULL)
	{
		printf("�������ڣ�\n");
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
				printf("��ѯ�������鼮��Ϣ��\n");
				printf("%s\t%s\t%s\t%s\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
				printf("\n�Ƿ�Ҫɾ���Ȿ�鼮��Ϣ��Y(y)orN(n)");
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
			printf("���޴��飡\n");
			system("pause");
		}
	}
}

//�޸�����ͨ�ú���
int change(Books *temp)
{
	char input[50];
	float price; 
	int choice;
	printf("\t1.�޸�����\n");
	printf("\t2.�޸�������\n");
	printf("\t3.�޸�ISBN���\n");
	printf("\t4.�޸ĳ��浥λ\n");
	printf("\t5.�޸ĳ���ʱ��\n");
	printf("\t6.�޸ĵ���\n");
	printf("\t0.�˳��޸�\n");
	do{
		printf("��ѡ��Ҫ�޸ĵ����ݣ�");
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
					printf("��������ȷ��������");
					scanf("%s",input); 
					strcpy(temp->bookName,input);
					return 1;
				case 2:
					printf("��������ȷ����������");
					scanf("%s",input); 
					strcpy(temp->autherName,input);
					return 1;
				case 3:
					printf("��������ȷ��ISBN��ţ�");
					scanf("%s",input); 
					strcpy(temp->isbn,input);
					return 1;
				case 4:
					printf("��������ȷ�ĳ��浥λ��");
					scanf("%s",input); 
					strcpy(temp->pub_unit,input);
					return 1;
				case 5:
					printf("��������ȷ�ĳ���ʱ�䣺");
					scanf("%s",input); 
					strcpy(temp->pub_time,input);
					return 1;
				case 6:
					printf("��������ȷ�ĵ��ۣ�");
					scanf("%f",&price); 
					temp->price=price;
					return 1;
				default:
					printf("��Ч�Ĳ�����\n");
					break;
			}
		}
	}while(choice);
	return 0;
} 

//ͼ����Ϣ�޸�
void alter(Books *head)
{
	char input[50]; 
	system("cls");
	printf("\t************************\n");
	printf("\t    �޸�ͼ����Ϣģ��    \n");
	printf("\t************************\n");
	printf("\n������Ҫ�޸��鼮��ISBN��������");
	scanf("%s",input);
	if(head==NULL)
	{
		printf("�������ڣ�\n");
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
				printf("��ѯ������ͼ����Ϣ��\n");
				printf("%s\t%s\t%s\t%s\t%s\t\t%.1f\t\n",temp->bookName,temp->autherName,temp->isbn,temp->pub_unit,temp->pub_time,temp->price);
				printf("\n");
				if(change(temp)==1)
				{
					printf("�޸ĳɹ���\n");
				}
				else
				{
					printf("�޸�ʧ�ܣ�\n");
				} 
				
			}
			temp=temp->next;
		}
		if(count==0)
		{
			printf("���޴��飡\n");
			system("pause");
		}
	}
}

//׷��ͼ����Ϣ
void addInfo(Books *head)
{
	system("cls");
	printf("\t************************\n");
	printf("\t    ׷��ͼ����Ϣģ��    \n");
	printf("\t************************\n");
	printf("\n˵������ģ��ÿ��ֻ������һ�����ݣ������������Զ��ŵ�ԭ���������һ�����棡\n");
	if(head==NULL)
	{
		printf("�������ڣ�\n");
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
		printf("�����������鼮��������");
		scanf("%s",newInfo->bookName);
		printf("�����������鼮����������");
		scanf("%s",newInfo->autherName);
		printf("�����������鼮��ISBN��ţ�");
		scanf("%s",newInfo->isbn);		
		printf("�����������鼮�ĳ��浥λ��");
		scanf("%s",newInfo->pub_unit);
		printf("�����������鼮�ĳ���ʱ�䣺");
		scanf("%s",newInfo->pub_time);
		printf("�����������鼮�ĵ��ۣ�");
		scanf("%f",&newInfo->price);
		newInfo->next=NULL;
	}
} 

//����ͼ����Ϣ
void download(Books *head)
{
	system("cls");
	printf("\t************************\n");
	printf("\t    ����ͼ����Ϣģ��    \n");
	printf("\t************************\n");
	printf("\n"); 
	FILE *fp;
	if((fp=fopen("booksInfo.txt","w+"))==NULL)
	{
		printf("�޷����ļ���\n");
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
		printf("\nͼ����Ϣ�ѳɹ�������\n��򿪡�booksInfo.txt���ļ��鿴��\n");
		system("pause");
	} 
}

//�����ⲿ���� 
void import(Books *head)
{
	system("cls");
	printf("\t************************\n");
	printf("\t    �����ⲿ����ģ��    \n");
	printf("\t************************\n");
	printf("\n˵����\n��ȷ���ⲿ�����ļ��ĸ�ʽ��ȷ\n"); 
	FILE *fp;
	if((fp=fopen("books.txt","r"))==NULL)
	{
		printf("û���ҵ���books.txt��,���������ļ�!\n");
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
		printf("\n���ⲿ����Դ�ɹ���\n��ʼ���룡\n");
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
		printf("\n���ݵ���ɹ���\n");
		system("pause");
	}
}

//�޸��û�����
void changepass(void)
{
    FILE *fp;
    User login;
    char newpass[6];
    char choice;
    if((fp=fopen("userInfo.txt","r"))==NULL)
    {
        printf("�޷���ȷ���û���Ϣ�ļ���\n���顰userInfo.txt���ļ���\n");
        return;
    }
    fscanf(fp, "%s %s", login.username, login.password);
    fclose(fp);

    system("cls");
    printf("\t************************\n");
    printf("\t    ����ͼ����Ϣģ��    \n");
    printf("\t************************\n");
    printf("\n�������µ�����(6λ)��");
    scanf("%s", newpass);
    printf("\n�Ƿ��޸����룿Y(y) or N(n)");
    scanf(" %c", &choice);
    if(choice == 'Y' || choice == 'y')
    {
        FILE *fp2 = fopen("userInfo.txt", "w"); 
        if (fp2 == NULL) 
		{
            printf("�޷����ļ���д�룡\n");
            return;
        }
        fprintf(fp2, "%s %s", login.username, newpass); 
        fclose(fp2);
        printf("\n�����޸ĳɹ���\n���µ�¼�Բ鿴\n");
        exit(0);
    }
    else
    {
        printf("\n�����޸�ʧ��\n");
        return;
    }
}

//������ 
int main(void)
{
	getTime();
	
	login();
	
	Books *head=(Books *)malloc(sizeof(Books)); 
	head->next=NULL;
	
	int choice;   //Ҫִ�еĲ��� 
	do{
		mainTable();
		printf("\n��ѡ��Ҫִ�еĲ�����");
		scanf("%d",&choice); 
		if(choice==0)
		{
			printf("\n�˳�ͼ����Ϣ����ϵͳ��\n");
			printf("\n��л����ʹ��\nDesigned and written by WIsteria\n");
			exit(0);
		}
		else
		{
			switch(choice)
			{
				case 1:
					insert(head);      //¼��ͼ����Ϣ 
					break;
				case 2:
					shows(head);       //���ͼ����Ϣ 
					break;
				case 3:
					selects(head);     //��ѯͼ����Ϣ 
					break;
				case 4:
					deletes(head);     //ɾ��ͼ����Ϣ 
					break;
				case 5:
					alter(head);       //�޸�ͼ����Ϣ 
					break;
				case 6:
					addInfo(head);     //׷��ͼ����Ϣ 
					break;
				case 7:
					download(head);    //����ͼ����Ϣ 
					break;
				case 8:
					import(head);      //�����ⲿ���� 
					break;
				case 9:
					changepass();      //�޸ĵ�¼���� 
					break; 
				default:
					printf("��Ч�Ĳ�����\n");
					break;
			}
		}
	}while(choice);	
	return 0;
}
