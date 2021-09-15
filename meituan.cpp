#include<iostream>
#include<conio.h>
#include<cstring>
#include <stdlib.h>
#include<memory.h>
#include"md5.h"
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define MaxInt 32767
#define MVNum 1000
//#define OVERFLOW -1
using namespace std;
typedef int VerTexType;
typedef double ArcType;
typedef struct{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum,arcnum;
}AMGraph;//ͼ
using namespace std;
/*ȷ��ͼ�ж���λ��*/
int Locate(AMGraph *G,int v){
    for(int i=0;i<G->vexnum;i++)
        if(G->vexs[i]==v)
            return i;
    return -1;
}
struct User{
	char password[33],userID[7],telephone[15];
};//�û�
struct FoodInfo{
	char food_id[20];
	char food_name[50];
	char food_price[10];
};//��Ʒ��Ϣ
struct Shop{
	char shoptype[50];
	char shopID[20];
	char shopName[100];
	char shopPassword[35];
	char avgScore[5];
	char avePrice[5];
	char address[100];
	char phone[30];
	int foodNum;
	FoodInfo food[100];
	char Comment[10][1000];
	int CommentNum;
};//�̼���Ϣ
struct Distance{
	char shop1_ID[20];
	char shop2_ID[20];
	char shop1_Name[50];
	char shop2_Name[50];
	char distance[10];
};//�����̼�֮�ҵľ�����Ϣ
typedef struct{
	User *elem;
	int length;
}UserList;//�û���

typedef struct{
	Shop *elem;
	int length;
}ShopList;//�̼ұ�

struct HashTable{
	Shop *elem;
	bool hasElem[1000];
	bool isDelete[1000];
	int pos[1000];//��¼˳����е��±�
};//��ϣ��
struct HTInfo{
	char shopName[100];
	int pos;
};
typedef struct HTNode{
	HTInfo data;
	struct HTNode *next;
}HTNode,*HTList;
struct OrderInfo{
	char userID[7];
	char shopName[100];
	char date[20];
	bool isOut;
};//Ԥ����Ϣ
typedef struct QNode{
    OrderInfo data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;//����
struct BSTInfo{
	char shopName[100];
	int pos;
};
typedef struct BSTNode{
    BSTInfo data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;//����������
/*��ʼ������*/
int InitQueue(LinkQueue &Q){
    Q.front=Q.rear=new QNode;
    Q.front->next=NULL;
    return OK;
}
/*���*/
int EnQueue(LinkQueue &Q,OrderInfo e){
    QueuePtr p=new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;//���½��嵽��β
    Q.rear=p;
    return OK;
}
/*����*/
int DeQueue(LinkQueue &Q,OrderInfo &e){
    if(Q.front==Q.rear)
        return ERROR;
    QueuePtr p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;//ɾ�����һ��Ԫ��ʱ����Ҫͬʱ�ı�front��rear
    delete p;
    return OK;
}
/*��order.txt*/
void ReadOrder(LinkQueue &Q){
	FILE *fp;
	fp=fopen("order.txt","r");
	if(!fp)
		cout<<"order�ļ���ʧ�ܣ�"<<endl;
	int i=-1;
	char c;
	while(i<0 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		OrderInfo oi;
		char s[150];
		int i=0,x=0;
		fscanf(fp,"%s",&oi.userID);
		fseek(fp,1,1);
		fgets(s,150,fp);
		int n=strlen(s);
		for(i=n-1;s[i]!=' ';i--)
			x++;
		strncpy(oi.date,s+n-x,14);
		oi.date[x]='\0';//���һ��û�лس�,�������һ������date�����س�
		strncpy(oi.shopName,s,n-x);
		oi.shopName[n-x-1]='\0';
		oi.isOut=false;
		EnQueue(Q,oi);
	}
	QueuePtr p=Q.front->next;
	while(p){
		int n=strlen(p->data.date);
		if(p->next)
			p->data.date[n-1]='\0';//ȥ���س���
		p=p->next;
	}
	fclose(fp);
}
/*��order.txt��д��*/
void WriteOrder(LinkQueue Q){
	FILE *fp;
	fp=fopen("order.txt","w");
	setbuf(fp,NULL);
	if(!fp)
		cout<<"order�ļ���ʧ�ܣ�"<<endl;
	QueuePtr p=Q.front->next;
	fputs("�û��˺� �̼����� Ԥ��ʱ��\n",fp);
	fflush(fp);
	while(p){
		if(!p->data.isOut){
			fputs(p->data.userID,fp);
			fputc(' ',fp);
			fputs(p->data.shopName,fp);
			fputc(' ',fp);
			fputs(p->data.date,fp);
			if(p->next)
				fputc('\n',fp);
		}
		p=p->next;
	}
	fclose(fp);
}
/*MD5����*/
void getMD5(char password[],unsigned char decrypt[16]){
	unsigned char *encrypt=reinterpret_cast<unsigned char*>(password);
	MD5_CTX md5;
	MD5Init(&md5);         		
	MD5Update(&md5,encrypt,strlen((char *)encrypt));
	MD5Final(&md5,decrypt);
}
/*unsigned char*ת����char*/
void convertUnCharToStr(char* str, unsigned char* UnChar, int ucLen)
{
    int i = 0;
    for (i = 0; i < ucLen; i++)
    {
        //��ʽ����str,ÿunsigned char ת���ַ�ռ��λ��%xд��%Xд��
        sprintf(str + i * 2, "%02x", UnChar[i]);
    }
}
/*char*ת����unsigned char*/
void convertStrToUnChar(char* str, unsigned char* UnChar)
{
    int i = strlen(str), j = 0, counter = 0;
    char c[2];
    unsigned int bytes[2];
    for (j = 0; j < i; j += 2)
    {
        if (0 == j % 2)
        {
            c[0] = str[j];
            c[1] = str[j + 1];
            sscanf(c, "%02x" , &bytes[0]);
            UnChar[counter] = bytes[0];
            counter++;
        }
    }
    return;
}
/*����������������*/
void InsertBST(BSTree &T,BSTInfo e){
    if(!T){
        BSTree S=new BSTNode;
        S->data=e;
        S->lchild=NULL;
        S->rchild=NULL;
        T=S;
    }
	else if(((unsigned char)(e.shopName[0]-176*94)+(unsigned char)(e.shopName[1]-161))<=((unsigned char)(T->data.shopName[0]-176*94)+(unsigned char)(T->data.shopName[1]-161)))
        InsertBST(T->lchild,e);
    else
        InsertBST(T->rchild,e);
}
/*��������������*/
BSTree SearchBST(BSTree T,char shopName[],int &findnum3){
	findnum3++;
	if((!T)||strcmp(shopName,T->data.shopName)==0)
		return T;
	else if(((unsigned char)(shopName[0]-176*94)+(unsigned char)(shopName[1]-161))<=((unsigned char)(T->data.shopName[0]-176*94)+(unsigned char)(T->data.shopName[1]-161)))
		return SearchBST(T->lchild,shopName,findnum3);
	else
		return SearchBST(T->rchild,shopName,findnum3);
}
/*����ϣ��(����̽��)*/
void CreateHashTable(HashTable &H,ShopList L){
	memset(H.hasElem,false,1000);//��ϣ���ʼÿ��λ��û��Ԫ��
	memset(H.isDelete,false,1000);//��ϣ���ʼÿ��λ��û��ɾ����
	for(int i=1;i<=L.length;i++){
		int address=((unsigned char)(L.elem[i].shopName[0]-176)*94+(unsigned char)(L.elem[i].shopName[1]-161))%1000;
		if(!H.hasElem[address]){
			H.elem[address]=L.elem[i];
			H.pos[address]=i;
			H.hasElem[address]=true;
		}
		else{
			while(H.hasElem[address]){
				address++;
				address=address%1000;
			}
			H.elem[address]=L.elem[i];
			H.pos[address]=i;
			H.hasElem[address]=true;
		}
	}
}
/*��ϣ����(����̽��)*/
int SearchHashTable(HashTable H,char shopName[]){
	int address=((unsigned char)(shopName[0]-176)*94+(unsigned char)(shopName[1]-161))%1000,i=0;
	while(strcmp(H.elem[address].shopName,shopName)!=0)
	{
		address++;
		address=address%1000;
		i++;//����̽�����
		if((!H.hasElem[address])||i==1000)
			return -1;
	}
	return address;
}
/*��ʼ���û���*/
int InitUserList(UserList &L){
	L.elem=new User[MAXSIZE];//����ڴ����ʧ�ܣ�new()����NULL
	if(!L.elem)
		exit(OVERFLOW);
	L.length=0;
	return OK;
}
/*ȷ���û�����λ��*/
int InsertPosition(UserList L,User e){
	if(atoi(L.elem[1].userID)>atoi(e.userID))
		return 1;
	else{
		for(int i=1;i<=L.length;i++){
			if(atoi(L.elem[i].userID)<atoi(e.userID)&&atoi(L.elem[i+1].userID)>atoi(e.userID))
				return i+1;//���ҳɹ�������Ԫ�ص��±�i+1
			if(strcmp(L.elem[i].userID,e.userID)==0)
				return 0;
		}
	}
}
/*�û������*/
int UserListInsert(UserList &L,int i,User e){
	if(i<1||(L.length!=0&&i>L.length))//�ж�i�Ƿ�Ϸ�
		return ERROR;
	if(L.length==MAXSIZE)//�жϴ洢�ռ��Ƿ�����
		return ERROR;
	for(int j=L.length;j>=i;j--)
		L.elem[j+1]=L.elem[j];
	L.elem[i]=e;
	++L.length;
	return OK;
}
/*�û���ɾ��*/
int UserListDelete(UserList &L,int i){
	if(i<1||i>L.length)//�ж�i�Ƿ�Ϸ�
		return ERROR;
	if(L.length==0)
		return ERROR;
	for(int j=i;j<=L.length;j++)
		L.elem[j]=L.elem[j+1];
	--L.length;
	return OK;
}
/*��ʼ���̼ұ�*/
int InitShopList(ShopList &L){
	L.elem=new Shop[900];//����ڴ����ʧ�ܣ�new()����NULL
	if(!L.elem)
		exit(OVERFLOW);
	L.length=0;
	return OK;
}
/*�̼ұ����*/
int ShopListInsert(ShopList &L,int i,Shop e){
	if(i<1||(L.length!=0&&i>L.length))//�ж�i�Ƿ�Ϸ�
		return ERROR;
	if(L.length==MAXSIZE)//�жϴ洢�ռ��Ƿ�����
		return ERROR;
	for(int j=L.length-1;j>=i-1;j--)
		L.elem[j+1]=L.elem[j];
	L.elem[i-1]=e;
	++L.length;
	return OK;
}
/*�̼ұ�ɾ��*/
int ShopListDelete(ShopList &L,int i){
	if(i<1||i>L.length)//�ж�i�Ƿ�Ϸ�
		return ERROR;
	if(L.length==0)
		return ERROR;
	for(int j=i;j<=L.length;j++)
		L.elem[j]=L.elem[j+1];
	--L.length;
	return OK;
}
/*��ϣ�����ʼ��*/
int InitHTList(HTList &L){
	L=new HTNode;//���ɵ��½ڵ���Ϊͷ��㣬��ͷָ��Lָ��ͷ��㣻
	L->next=NULL;
	return OK;
}
/*��ϣ�������*/
int HTListLength(HTList L){
	HTList p;
	int i=0;
	p=L->next;//pָ���һ�����
	while(p){
		i++;
		p=p->next;
	}
	return i;
}
/*��ϣ�������*/
int HTListInsert(HTList &L,int i,HTInfo e){
	HTList p;
	p=L; //ָ��ͷ���
	int j=0;
	while(p&&j<(i-1)){
		p=p->next;
		j++;
	}
	if(!p||j>i-1)
		return ERROR;
	HTList s=new HTNode;
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}
/*��ϣ����ɾ��*/
int HTListDelete(HTList &L,int i){
	HTList p,q;
	p=L; //ָ��ͷ���
	int j=0;
	while(p->next&&j<(i-1)){
		p=p->next;
		j++;
	}
	if(!p->next||j>i-1)
		return ERROR;
	q=p->next;
	p->next=q->next;
	delete q;
	return OK;
}
/*����ϣ��(����ַ)*/
void CreateHashTable2(HTList H[1000],ShopList L){
	for(int i=1;i<=L.length;i++){
		int address=((unsigned char)(L.elem[i].shopName[0]-176)*94+(unsigned char)(L.elem[i].shopName[1]-161))%1000;
		HTList p;
		HTInfo e;
		strcpy(e.shopName,L.elem[i].shopName);
		e.pos=i;
		HTListInsert(H[address],1,e);
	}
}
/*��ϣ����(����ַ)*/
int SearchHashTable2(HTList H[1000],char shopName[]){
	int address=((unsigned char)(shopName[0]-176)*94+(unsigned char)(shopName[1]-161))%1000;
	if(HTListLength(H[address])==0)
		return -1;
	else{
		HTList p=H[address]->next;
		while(p){
			if(strcmp(p->data.shopName,shopName)==0)
				return address;
			p=p->next;
		}
		if(!p)
			return -1;
	}
}
/*�۰����*/
int Search_Bin(UserList L,char userID[],char password[]){
	int low=1,high=L.length,mid=0;
	while(low<=high){
		mid=(low+high)/2;
		if(strcmp(userID,L.elem[mid].userID)==0){
			strncpy(password,L.elem[mid].password,32);
			password[32]='\0';
			return mid;
		}
		else if(strcmp(userID,L.elem[mid].userID)==-1)
			high=mid-1;
		else
			low=mid+1;
	}
	return 0;
}
/*�鿴������Ϣ*/
int PrintSelfInfo(User u){
	FILE *fp;
	UserList L;
	InitUserList(L);
	int i=0;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[6]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	int j=Search_Bin(L,u.userID,u.password);
	cout<<"�û��˺�"<<"   "<<"��ϵ��ʽ"<<endl;
	cout<<L.elem[j].userID<<"     "<<L.elem[j].telephone<<endl;
	getch();
	return OK;
}
/*�޸ĸ�����Ϣ*/
int ModifySelfInfo(User u){
	FILE *fp;
	UserList L;
	char password[7];
	int flag=1;//������������Ƿ�һ��
	int flag2=1;
	InitUserList(L);
	int i=0;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	int j=Search_Bin(L,u.userID,u.password);
	int n=1;//��������������
	int n2=1;//��ǵ绰�������
	while(flag){
		cout<<"�����������������ϵ��ʽ"<<endl;
		cout<<"���루6λ��:";
		for(int i=0;i<6;i++)
		{
			fflush(stdin);
			L.elem[j].password[i]=getch();
			if(L.elem[j].password[i]!=13)
				cout<<"*";
		}
		L.elem[j].password[6]='\0';
		char passwordMD51[33];
		unsigned char decrypt1[16];
		getMD5(L.elem[j].password,decrypt1);
		convertUnCharToStr(passwordMD51,decrypt1,16);
		passwordMD51[32]='\0';
		cout<<endl;
		cout<<"�ٴ��������루6λ������ȷ��:";
		for(int i=0;i<6;i++)
		{
			fflush(stdin);
			password[i]=getch();
			if(password[i]!=13)
			cout<<"*";
		}
		password[6]='\0';
		char passwordMD52[33];
		unsigned char decrypt2[16];
		getMD5(password,decrypt2);
		convertUnCharToStr(passwordMD52,decrypt2,16);
		passwordMD51[32]='\0';
		cout<<endl;
		if(strcmp(passwordMD51,passwordMD52)==0){
			flag=0;
			strcpy(L.elem[j].password,passwordMD51);
		}
		else{
			cout<<"������������벻һ�£����������룡"<<endl;
			if(n!=3)
				cout<<"������"<<3-n<<"�λ���"<<endl;
			n++;
		}
		if(n>3){
			cout<<"�����Ѵ����ޣ��޸�ʧ�ܣ�"<<endl;
			break;
		}
	}
	if(n>3)
		return ERROR;
	while(flag2){
		cout<<"��ϵ��ʽ(11λ):";
		cin>>L.elem[j].telephone;
		int length=strlen(L.elem[j].telephone);
		int k=1;
		for(;k<=L.length;k++)
			if(strcmp(L.elem[k].telephone,L.elem[j].telephone)==0&&k!=j)
				break;
		if(k<=L.length){
			cout<<"�õ绰�Ѵ��ڣ�"<<endl;
			if(n2!=3)
				cout<<"������"<<3-n2<<"�λ��ᣡ"<<endl;
			n2++;
		}
		else if(length!=11){
			cout<<"�绰���Ϸ�������������!"<<endl;
			if(n2!=3)
				cout<<"������"<<3-n2<<"�λ��ᣡ"<<endl;
			n2++;
		}
		else
			flag2=0;
		if(n2>3){
			cout<<"�Ѵ���������!�޸�ʧ��!"<<endl;
			break;
		}
	}
	if(n2>3)
		return ERROR;
	fp=fopen("user.txt","w");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	
	fputs("�û��˺� ���� ��ϵ��ʽ\n",fp);//д���ͷ

	/*���µ�˳�������д���ļ�*/
	for(i=1;i<=L.length;i++){
		fputs(L.elem[i].userID,fp);
		fputc(' ',fp);
		fputs(L.elem[i].password,fp);
		fputc(' ',fp);
		fputs(L.elem[i].telephone,fp);
		if(i!=L.length)
			fputc('\n',fp);
	}
	cout<<"�޸ĳɹ���"<<endl;
	fclose(fp);
	return OK;
}
/*ע��������Ϣ*/
int DestroySelfInfo(User u){
	FILE *fp;
	UserList L;
	InitUserList(L);
	int i=0;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	int j=Search_Bin(L,u.userID,u.password);
	char yesno;
	cout<<"ȷ��ע�����˻���Ϣ��?(y/n)"<<endl;
	cin>>yesno;
	if((yesno=='y')||(yesno=='Y')){
		UserListDelete(L,j);
		fp=fopen("user.txt","w");
		if(!fp)
			cout<<"user�ļ���ʧ�ܣ�";
	
		fputs("�û��˺� ���� ��ϵ��ʽ\n",fp);//д���ͷ

		/*���µ�˳�������д���ļ�*/
		for(i=1;i<=L.length;i++){
			fputs(L.elem[i].userID,fp);
			fputc(' ',fp);
			fputs(L.elem[i].password,fp);
			fputc(' ',fp);
			fputs(L.elem[i].telephone,fp);
			if(i!=L.length)
				fputc('\n',fp);
		}
		LinkQueue Q;
		InitQueue(Q);
		ReadOrder(Q);
		LinkQueue Q1;
		InitQueue(Q1);
		QueuePtr p=Q.front->next;
		while(p){
			if(strcmp(p->data.userID,u.userID)==0){
				p->data.isOut=true;
				OrderInfo info;
				strcpy(info.date,p->data.date);
				strcpy(info.shopName,p->data.shopName);
				strcpy(info.userID,p->data.userID);
				EnQueue(Q1,info);
			}
				p=p->next;
		}
		WriteOrder(Q);
		cout<<"ע���ɹ���"<<endl;
		getch();
	}
	else{
		cout<<"����ȡ��ע��!"<<endl;
		return ERROR;
	}
	fclose(fp);
	return OK;
}
/*������Ϣ����*/
void SelfInfoManage(User u,int &isDelete){
	char choice;
	while(1){
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"----------------�û�ϵͳ:������Ϣ����---------------"<<endl;
		cout<<"1. �鿴������Ϣ"<<endl;
		cout<<"2. �޸ĸ�����Ϣ"<<endl;
		cout<<"3. ע��������Ϣ"<<endl;
		cout<<"4. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		fflush(stdin);
		cin>>choice;	
		switch(choice){
		case '1':PrintSelfInfo(u);break;
		case '2':ModifySelfInfo(u);break;
		case '3':
			isDelete=DestroySelfInfo(u);
			break;
		case '4':return;
		default:cout<<"�������,���������룡"<<endl;break;
		}
		if(isDelete)
			return;
	}
}
/*��shop.txt*/
void ReadShop(ShopList &L){
	FILE *fp;
	char label[20],a;
	int i=0,j=-1,k=-1;
	fp=fopen("shop.txt","r");
	if(!fp)
		cout<<"shop�ļ���ʧ�ܣ�"<<endl;
	while(!feof(fp)){
		fscanf(fp,"%s",&label);
		if(strcmp(label,"shoptype:")==0){
			L.elem[i].foodNum=j+1;
			L.elem[i].CommentNum=k+1;
			i++;//���̸���
			j=-1;
			k=-1;
			a=fgetc(fp);
			fgets(L.elem[i].shoptype,50,fp);
			int n=strlen(L.elem[i].shoptype);
			L.elem[i].shoptype[n-1]='\0';
			L.length++;
		}
		if(strcmp(label,"shopId:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].shopID,20,fp);
			int n=strlen(L.elem[i].shopID);
			L.elem[i].shopID[n-1]='\0';
		}
		if(strcmp(label,"shopName:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].shopName,100,fp);
			int n=strlen(L.elem[i].shopName);
			L.elem[i].shopName[n-1]='\0';
		}
		if(strcmp(label,"shopPassword:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].shopPassword,35,fp);
			int n=strlen(L.elem[i].shopPassword);
			L.elem[i].shopPassword[n-1]='\0';
		}
		if(strcmp(label,"avgScore:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].avgScore,5,fp);
			int n=strlen(L.elem[i].avgScore);
			L.elem[i].avgScore[n-1]='\0';
		}
		if(strcmp(label,"avePrice:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].avePrice,5,fp);
			int n=strlen(L.elem[i].avePrice);
			L.elem[i].avePrice[n-1]='\0';
		}
		if(strcmp(label,"address:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].address,100,fp);
			int n=strlen(L.elem[i].address);
			L.elem[i].address[n-1]='\0';
		}
		if(strcmp(label,"phone:")==0){
			a=fgetc(fp);
			fgets(L.elem[i].phone,30,fp);
			int n=strlen(L.elem[i].phone);
			L.elem[i].phone[n-1]='\0';
		}
		if(strcmp(label,"food_id:")==0){
			j++;
			fscanf(fp,"%s",&L.elem[i].food[j].food_id);
			fscanf(fp,"%s",&label);
			if(strcmp(label,"food_name:")==0){
				fscanf(fp,"%s",&L.elem[i].food[j].food_name);
				fscanf(fp,"%s",&label);
				if(strcmp(label,"food_price:")==0){
					a=fgetc(fp);
					fgets(L.elem[i].food[j].food_price,10,fp);
					int n=strlen(L.elem[i].food[j].food_price);
					L.elem[i].food[j].food_price[n-1]='\0';
				}
			}
		}
		char c=label[0];
		if(c=='C'){
			k++;
			fgets(L.elem[i].Comment[k],1000,fp);
		}
	}
	L.elem[i].foodNum=j+1;
	L.elem[i].CommentNum=k+1;
	for(int i=0;i<=L.length;i++){
		for(int j=0;j<L.elem[i].foodNum;j++)
		{
			int n1=strlen(L.elem[i].food[j].food_id);
			L.elem[i].food[j].food_id[n1-1]='\0';//ȥ������
			int n2=strlen(L.elem[i].food[j].food_name);
			L.elem[i].food[j].food_name[n2-1]='\0';//ȥ������
		}
	}
	fclose(fp);
}
/*��shop.txtд��*/
void WriteShop(ShopList L){
	FILE *fp;
	fp=fopen("shop.txt","w");
	setbuf(fp,NULL);
	if(!fp)
		cout<<"shop�ļ���ʧ��!"<<endl;
	for(int i=1;i<=L.length;i++){
		fputs("shoptype: ",fp);
		fflush(fp);
		fputs(L.elem[i].shoptype,fp);
		fputc('\n',fp);
		fputs("shopId: ",fp);
		fputs(L.elem[i].shopID,fp);
		fputc('\n',fp);
		fputs("shopName: ",fp);
		fputs(L.elem[i].shopName,fp);
		fputc('\n',fp);
		fputs("shopPassword: ",fp);
		fputs(L.elem[i].shopPassword,fp);
		fputc('\n',fp);
		fputs("avgScore: ",fp);
		fputs(L.elem[i].avgScore,fp);
		fputc('\n',fp);
		fputs("avePrice: ",fp);
		fputs(L.elem[i].avePrice,fp);
		fputc('\n',fp);
		fputs("address: ",fp);
		fputs(L.elem[i].address,fp);
		fputc('\n',fp);
		fputs("phone: ",fp);
		fputs(L.elem[i].phone,fp);
		fputc('\n',fp);
		for(int j=0;j<L.elem[i].foodNum;j++){
			fputs("food_id: ",fp);
			fputs(L.elem[i].food[j].food_id,fp);
			fputs(", ",fp);
			fputs("food_name: ",fp);
			fputs(L.elem[i].food[j].food_name,fp);
			fputs(", ",fp);
			fputs("food_price: ",fp);
			fputs(L.elem[i].food[j].food_price,fp);
			fputc('\n',fp);
		}
		for(int k=0;k<L.elem[i].CommentNum;k++){
			fputs("Comment",fp);
			fputc(char(k+48),fp);
			fputs(":",fp);
			fputs(L.elem[i].Comment[k],fp);
		}
	}
}
/*�Ͻ�˹���� ���·��*/
double ShortestPath_DIJ(AMGraph *G,HashTable H,char shop1_ID[],char shop2_ID[]){
    int n=G->vexnum;
    int v,k,j=0;
    bool S[MVNum];
    double D[MVNum];
	int Path[MVNum];
	int id1=atoi(shop1_ID);
	int id2=atoi(shop2_ID);
	int v0=Locate(G,id1);
	int v1=Locate(G,id2);
    for(v=0;v<n;v++){
        S[v]=false;
        D[v]=G->arcs[v0][v];
        if(D[v]<MaxInt)
            Path[v]=v0;
        else
            Path[v]=-1;
    }
    S[v0]=true;
    D[v0]=0;
    for(int i=1;i<n;i++)
    {
        int min=MaxInt;
        for(int w=0;w<n;w++)
            if(!S[w]&&D[w]<min){
                v=w;
                min=D[w];
            }
        S[v]=true;
        for(int w=0;w<n;w++)
            if(!S[w]&&(D[v]+G->arcs[v][w]<D[w])){
                D[w]=D[v]+G->arcs[v][w];
                Path[w]=v;
            }
    }
	return D[v1];
}
/*��distance.txt�ļ�*/
double FindPath(ShopList L,HashTable H,char shopName[]){
	FILE *fp;
	int i=0,j=1;
	char c;
	char shop1_Name[100],shop2_Name[100],shop1_ID[20],shop2_ID[20],distance[10];
	AMGraph *G=new AMGraph;
	/*�ѡ����ּӵ���ϣ��*/
	for(i=0;i<1000;i++){
		if(H.hasElem[i]){
			G->vexs[j]=atoi(H.elem[i].shopID);
			j++;
		}
	}
	G->vexnum=j-1;
	G->vexs[0]=atoi("512324");//�ѡ����֡��ӵ�ͼ��
	G->vexnum++;
	G->arcnum=0;
	for(i=0;i<G->vexnum;i++)
        for(int j=0;j<G->vexnum;j++)
            G->arcs[i][j]=MaxInt;
	fp=fopen("distance.txt","r");
	if(!fp)
		cout<<"distance�ļ���ʧ�ܣ�"<<endl;
	i=0;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	//char s[200];
	//int n=0;
	while(!feof(fp)){
		//fgets(s,200,fp);
		//n++;
		fscanf(fp,"%s",shop1_ID);
		for(int j=1;j<=L.length;j++){
			if(strcmp(shop1_ID,"512324")==0){
				strcpy(shop1_Name,"����");
				break;
			}
			else if(strcmp(L.elem[j].shopID,shop1_ID)==0){
				strcpy(shop1_Name,L.elem[j].shopName);
				break;
			}
		}
		fseek(fp,strlen(shop1_Name)+1,1);
		fscanf(fp,"%s",shop2_ID);
		for(int j=1;j<=L.length;j++){
			if(strcmp(L.elem[j].shopID,shop2_ID)==0){
				strcpy(shop2_Name,L.elem[j].shopName);
				break;
			}
		}
		fseek(fp,strlen(shop2_Name)+2,1);
		fscanf(fp,"%s",distance);
		int v1;
		if(strcmp(shop1_Name,"����")==0)
			v1=0;
		else
			v1=Locate(G,atoi(shop1_ID));
		int v2=Locate(G,atoi(shop2_ID));
		G->arcs[v1][v2]=atof(distance);
		G->arcs[v2][v1]=G->arcs[v1][v2];
		G->arcnum++;
	}
	int address=SearchHashTable(H,shopName);//��ϣ���в��Ҹ�shopName��Ӧ��shopID
	double length=ShortestPath_DIJ(G,H,"512324",H.elem[address].shopID);
	return length;
}
/*��ѯĳ���̼�*/
void SeekShop(){
	ShopList L;
	InitShopList(L);
	ReadShop(L);
	HashTable H;
	H.elem=new Shop[1000];
	memset(H.hasElem,false,1000);//��ϣ���ʼÿ��λ��û��Ԫ��
	memset(H.isDelete,false,1000);//��ϣ���ʼÿ��λ��û��ɾ����
	for(int i=1;i<=L.length;i++){
		int address=((unsigned char)(L.elem[i].shopName[0]-176)*94+(unsigned char)(L.elem[i].shopName[1]-161))%1000;
		if(!H.hasElem[address]){
			H.elem[address]=L.elem[i];
			H.hasElem[address]=true;
		}
		else{
			while(H.hasElem[address]){
				address++;
				address=address%1000;
			}
			H.elem[address]=L.elem[i];
			H.hasElem[address]=true;
		}
	}
	cout<<"�������̼�����:";
	char shopName[50];
	cin>>shopName;
	int n=strlen(shopName);
	shopName[n]='\0';
	int address=SearchHashTable(H,shopName);
	if(address==-1)
		cout<<"��Ǹ�����̼Ҳ����ڣ�"<<endl;
	else{
		cout<<"��Ʒ��Ϣ����:"<<endl;
		cout<<"�̼�����: "<<H.elem[address].shoptype<<endl;
		cout<<"����: "<<H.elem[address].avgScore<<endl;
		cout<<"ƽ������: "<<H.elem[address].avePrice<<endl;
		cout<<"��ַ: "<<H.elem[address].address<<endl;
		double length=FindPath(L,H,shopName);
		if(length!=0){
			cout<<"��̾���: ";
			printf("%.3f\n",FindPath(L,H,shopName));
		}
		else
			cout<<"�ӱ�������·�߿��Ե���!"<<endl;
		cout<<"��ϵ�绰: "<<H.elem[address].phone<<endl;
		cout<<"��ɫ��Ʒ: ";
		for(int i=0;i<H.elem[address].foodNum;i++){
			cout<<H.elem[address].food[i].food_name;
			if(i!=H.elem[address].foodNum-1)
				cout<<",";
		}
			cout<<endl;
		if(H.elem[address].CommentNum!=0){
			cout<<"����:"<<endl;
			for(int i=0;i<H.elem[address].CommentNum;i++)
				cout<<"������"<<i+1<<"��"<<H.elem[address].Comment[i];	
		}
		else
			cout<<"���̼��������ۣ�"<<endl;
		cout<<endl;
	}
}
/*������*/
int Partition(ShopList &L,int low,int high){
	L.elem[0]=L.elem[low];
	double pivotkey=atof(L.elem[low].avgScore);
	while(low<high){
		while(low<high&&(atof(L.elem[high].avgScore)>=pivotkey))
			high--;
		L.elem[low]=L.elem[high];
		while(low<high&&(atof(L.elem[low].avgScore)<=pivotkey))
			low++;
		L.elem[high]=L.elem[low];
	}
	L.elem[low]=L.elem[0];
	return low;
}
/*����*/
void Qsort(ShopList &L,int low,int high){
	if(low<high){
		int pivotloc=Partition(L,low,high);
		Qsort(L,low,pivotloc-1);
		Qsort(L,pivotloc+1,high);
	}
}
void QuickSort(ShopList &L){
	Qsort(L,1,L.length);
}
/*����next����ֵ*/
void get_next(char T[],int next[]){
	int i=0;
	next[0]=-1;
	int j=-1;
	while(i<strlen(T)){
		if(j==-1||T[i]==T[j]){
			i++;
			j++;
			next[i]=j;
		}
		else
			j=next[j];
	}
}
/*BF�㷨�ַ���ƥ��*/
int Index_BF(char S[],char T[],int pos){
	int i=pos,j=1;
	while(i<strlen(S)&&j<strlen(T)){
		if(S[i]==T[j]){
			i++;
			j++;
		}
		else{
			i=i-j+2;
			j=1;
		}
	}
	if(j>strlen(T)-1)
		return i-strlen(T)+1;
	else
		return -1;
}
/*BF�㷨�Ƽ�*/
void Introduce(){
	char shoptype[50],foodName[100],shopFeature[200];
	ShopList L;
	int i=0;
	InitShopList(L);
	cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
	cout<<"----------------�û�ϵͳ:�Ƽ�����(BF)---------------"<<endl;	
	cout<<"�������̼�����(����Ҫ���밴�س�): ";
	fflush(stdin);
	for(i=0;i<50;i++){
		shoptype[i]=getchar();
		if(shoptype[i]==10)
			break;
	}
	shoptype[i]='\0';
	cout<<"��������Ҫ����ɫ��(����Ҫ���밴�س�): ";
	fflush(stdin);
	for(i=0;i<100;i++){
		foodName[i]=getchar();
		if(foodName[i]==10)
			break;
	}
	foodName[i]='\0';
	bool format=true;
	while(format){
		int flag=0;
		cout<<"�������̼��ص�(����Ҫ���밴�س�): ";
		fflush(stdin);
		for(i=0;i<200;i++){
			shopFeature[i]=getchar();
			if(shopFeature[i]==10)
				break;
		}
		shopFeature[i]='\0';
		for(i=0;i<strlen(shopFeature);i++)
			if(shopFeature[i]==' '&&shopFeature[i+1]==' '){
				cout<<"��ʽ����!���������룡"<<endl;
				flag=1;
			}
		if(flag==0)
			format=false;
	}
	ReadShop(L);
	/*�����̼����ͽ����״�ɸѡ*/
	ShopList L1;//��ŷ����̼����͵ĵ���
	InitShopList(L1);
	if(shoptype[0]!=0){
		int j=1;
		for(i=1;i<=L.length;i++){
			if(Index_BF(L.elem[i].shoptype,shoptype,0)!=-1){
				L1.elem[j]=L.elem[i];
				L1.length++;
				j++;
			}
		}
	}
	else
		for(i=1;i<=L.length;i++){
			L1.elem[i]=L.elem[i];
			L1.length++;
		}
	/*������ɫ��Ʒ���еڶ���ɸѡ*/
	ShopList L2;//��ž��иò�Ʒ�ĵ���
	InitShopList(L2);
	if(foodName[0]!=0){
		int m=1;
		for(i=1;i<=L1.length;i++)
			for(int j=0;j<L1.elem[i].foodNum;j++)
				if(Index_BF(L1.elem[i].food[j].food_name,foodName,0)!=-1){
					L2.elem[m]=L1.elem[i];
					L2.length++;
					m++;
					break;
				}
	}
	else
		for(i=1;i<=L1.length;i++){
			L2.elem[i]=L1.elem[i];
			L2.length++;
		}
	/*�����̼��ص���е�����ɸѡ*/
	ShopList L3;//��ž��и��ص�ĵ���
	InitShopList(L3);
	int x=0;//��¼�ո����
	bool hasFeature[200];
	memset(hasFeature,false,200);//���ÿһ���ص����������Ƿ����
	for(i=0;i<strlen(shopFeature);i++)
		if(shopFeature[i]==' ')
			x++;
	if(shopFeature[0]!=0){
		char *f[200];
		int m=1;
		for(i=0;i<x;i++){
			if(i==0)
				f[i]=strtok(shopFeature," ");
			else
				f[i]=strtok(NULL," ");
		}
		if(x>=1)
			f[i]=strtok(NULL," ");	
		for(int j=1;j<=L2.length;j++){
			int flag=1;//��Ǹõ����Ƿ���������ص�
			for(int t=0;t<x+1;t++)
				for(int k=0;k<L2.elem[j].CommentNum;k++){
					if(x>=1)
							if(Index_BF(L2.elem[j].Comment[k],f[t],0)!=-1)
						{
							hasFeature[t]=true;//�����ص����������ҵ���Ѱ����һ���ص�
							break;
						}
					if(x==0)
							if(Index_BF(L2.elem[j].Comment[k],shopFeature,0)!=-1)
						{
							hasFeature[t]=true;//�����ص����������ҵ���Ѱ����һ���ص�
							break;
						}
				}
			for(int t=0;t<x+1;t++)
				if(!hasFeature[t]){
					flag=0;
					break;
				}
			if(flag){
				L3.elem[m]=L2.elem[j];
				L3.length++;
				m++;
			}
		}
	}
	else
		for(i=1;i<=L2.length;i++){
			L3.elem[i]=L2.elem[i];
			L3.length++;
		}
	QuickSort(L3);
	if(L3.length==0)
		cout<<"��δ�ҵ�����Ҫ����̼ң�"<<endl;
	else{
		cout<<"Ϊ���Ƽ������̼�: "<<endl;
		printf("%-55s %-20s %-5s %-10s %-65s %-30s\n","����","����","����","�˾�����","��ַ","��ϵ��ʽ");
		for(int i=L3.length;i>=1;i--)
			printf("%-55s %-20s %-5s %-10s %-65s %-30s\n",L3.elem[i].shopName,L3.elem[i].shoptype,L3.elem[i].avgScore,L3.elem[i].avePrice,L3.elem[i].address,L3.elem[i].phone);
	}
}
/*KMP�㷨�ַ���ƥ��*/
int Index_KMP(char S[],char T[],int pos){
	int i=pos;
	int j=0;
	int next[200];
	get_next(T,next);
	while(i<strlen(S)&&j<strlen(T)){
		if(j==0||S[i]==T[j]){
			i++;
			j++;
		}
		else
			j=next[j];
	}
	if(j>(strlen(T)-1))
		return i-strlen(T)+1;
	else
		return 0;
}
/*KMP�㷨�Ƽ�*/
void Introduce2(){
	char shoptype[50],foodName[100],shopFeature[200];
	ShopList L;
	int i=0;
	InitShopList(L);
	cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
	cout<<"---------------�û�ϵͳ:�Ƽ�����(KMP)---------------"<<endl;	
	cout<<"�������̼�����(����Ҫ���밴�س�): ";
	fflush(stdin);
	for(i=0;i<50;i++){
		shoptype[i]=getchar();
		if(shoptype[i]==10)
			break;
	}
	shoptype[i]='\0';
	cout<<"��������Ҫ����ɫ��(����Ҫ���밴�س�): ";
	fflush(stdin);
	for(i=0;i<100;i++){
		foodName[i]=getchar();
		if(foodName[i]==10)
			break;
	}
	foodName[i]='\0';
	bool format=true;
	while(format){
		int flag=0;
		cout<<"�������̼��ص�(����Ҫ���밴�س�): ";
		fflush(stdin);
		for(i=0;i<200;i++){
			shopFeature[i]=getchar();
			if(shopFeature[i]==10)
				break;
		}
		shopFeature[i]='\0';
		for(i=0;i<strlen(shopFeature);i++)
			if(shopFeature[i]==' '&&shopFeature[i+1]==' '){
				cout<<"��ʽ����!���������룡"<<endl;
				flag=1;
			}
		if(flag==0)
			format=false;
	}
	ReadShop(L);
	/*�����̼����ͽ����״�ɸѡ*/
	ShopList L1;//��ŷ����̼����͵ĵ���
	InitShopList(L1);
	if(shoptype[0]!=0){
		int j=1;
		for(i=1;i<=L.length;i++){
			if(Index_KMP(L.elem[i].shoptype,shoptype,0)!=0){
				L1.elem[j]=L.elem[i];
				L1.length++;
				j++;
			}
		}
	}
	else
		for(i=1;i<=L.length;i++){
			L1.elem[i]=L.elem[i];
			L1.length++;
		}
	/*������ɫ��Ʒ���еڶ���ɸѡ*/
	ShopList L2;//��ž��иò�Ʒ�ĵ���
	InitShopList(L2);
	if(foodName[0]!=0){
		int m=1;
		for(i=1;i<=L1.length;i++)
			for(int j=0;j<L1.elem[i].foodNum;j++)
				if(Index_KMP(L1.elem[i].food[j].food_name,foodName,0)!=0){
					L2.elem[m]=L1.elem[i];
					L2.length++;
					m++;
					break;
				}
	}
	else
		for(i=1;i<=L1.length;i++){
			L2.elem[i]=L1.elem[i];
			L2.length++;
		}
	/*�����̼��ص���е�����ɸѡ*/
	ShopList L3;//��ž��и��ص�ĵ���
	InitShopList(L3);
	int x=0;//��¼�ո����
	bool hasFeature[200];
	memset(hasFeature,false,200);//���ÿһ���ص����������Ƿ����
	for(i=0;i<strlen(shopFeature);i++)
		if(shopFeature[i]==' ')
			x++;
	if(shopFeature[0]!=0){
		char *f[200];
		int m=1;
		for(i=0;i<x;i++){
			if(i==0)
				f[i]=strtok(shopFeature," ");
			else
				f[i]=strtok(NULL," ");
		}
		if(x>=1)
			f[i]=strtok(NULL," ");	
		for(int j=1;j<=L2.length;j++){
			int flag=1;//��Ǹõ����Ƿ���������ص�
			for(int t=0;t<x+1;t++)
				for(int k=0;k<L2.elem[j].CommentNum;k++){
					if(x>=1)
							if(Index_KMP(L2.elem[j].Comment[k],f[t],0)!=0)
						{
							hasFeature[t]=true;//�����ص����������ҵ���Ѱ����һ���ص�
							break;
						}
					if(x==0)
							if(Index_KMP(L2.elem[j].Comment[k],shopFeature,0)!=0)
						{
							hasFeature[t]=true;//�����ص����������ҵ���Ѱ����һ���ص�
							break;
						}
				}
			for(int t=0;t<x+1;t++)
				if(!hasFeature[t]){
					flag=0;
					break;
				}
			if(flag){
				L3.elem[m]=L2.elem[j];
				L3.length++;
				m++;
			}
		}
	}
	else
		for(i=1;i<=L2.length;i++){
			L3.elem[i]=L2.elem[i];
			L3.length++;
		}
	QuickSort(L3);
	if(L3.length==0)
		cout<<"��δ�ҵ�����Ҫ����̼ң�"<<endl;
	else{
		cout<<"Ϊ���Ƽ������̼�: "<<endl;
		printf("%-55s %-20s %-5s %-10s %-65s %-30s\n","����","����","����","�˾�����","��ַ","��ϵ��ʽ");
		for(int i=L3.length;i>=1;i--)
			printf("%-55s %-20s %-5s %-10s %-65s %-30s\n",L3.elem[i].shopName,L3.elem[i].shoptype,L3.elem[i].avgScore,L3.elem[i].avePrice,L3.elem[i].address,L3.elem[i].phone);
	}
}
/*�Ƽ�����*/
void IntroduceModule(){
	char choice;
	while(1){
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"------------------�û�ϵͳ:�Ƽ�����-----------------"<<endl;	
		cout<<"1. BF�㷨"<<endl;
		cout<<"2. KMP�㷨"<<endl;
		cout<<"3. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		fflush(stdin);
		cin>>choice;
		switch(choice){
		case '1':Introduce();break;//���ò���BF�㷨���Ƽ�����
		case '2':Introduce2();break;//���ò���KMP�㷨���Ƽ�����
		case '3':return;
		}
	}
}
/*�鿴����Ԥ��*/
void PrintAllOrder(User u){
	LinkQueue Q;
	InitQueue(Q);
	ReadOrder(Q);
	int n=0;
	if(Q.front==Q.rear)
		cout<<"��Ǹ�������κ�Ԥ����Ϣ!"<<endl;
	else{
		QueuePtr p=Q.front->next;
		while(p){
			if(strcmp(p->data.userID,u.userID)==0&&n==0)
				cout<<"���û���Ԥ����Ϣ����:"<<endl;
			if(strcmp(p->data.userID,u.userID)==0){
				cout<<p->data.userID<<" "<<p->data.shopName<<" "<<p->data.date<<endl;
				n++;
			}
			p=p->next;
		}
		if(n==0)
			cout<<"��Ǹ�����û���Ԥ����Ϣ������!"<<endl;
	}
}
/*��ѯĳ��Ԥ��*/
void SearchOrder(User u){
	LinkQueue Q;
	InitQueue(Q);
	ReadOrder(Q);
	char shopName[100];
	bool isFound=false;
	QueuePtr p=Q.front->next;
	cout<<"�������̼�����: "<<endl;
	cin>>shopName;
	while(p){
		if((strcmp(p->data.userID,u.userID)==0)&&(strcmp(p->data.shopName,shopName)==0)){
			if(!isFound)
				cout<<"���û��ڴ��̼ҵ�Ԥ����Ϣ����:"<<endl;
			cout<<p->data.userID<<" "<<p->data.shopName<<" "<<p->data.date<<endl;
			isFound=true;
		}
		p=p->next;
	}
	if(!isFound)
		cout<<"��Ǹ�����û������ڴ��̼ҵ�Ԥ����Ϣ!"<<endl;
}
/*���Ԥ��*/
void AddOrder(User u){
	OrderInfo oi;
	LinkQueue Q;
	InitQueue(Q);
	ReadOrder(Q);
	strcpy(oi.userID,u.userID);
	cout<<"�������̼����ƺ�Ԥ��ʱ��: "<<endl;
	cin>>oi.shopName>>oi.date;
	oi.isOut=false;
	EnQueue(Q,oi);
	WriteOrder(Q);
	cout<<"Ԥ���ɹ���"<<endl;
}
/*Ԥ������*/
void Order(User u){
	char choice;
	while(1){
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"-----------------�û�ϵͳ:Ԥ������------------------"<<endl;
		cout<<"1. �鿴����Ԥ��"<<endl;
		cout<<"2. ��ѯĳ��Ԥ��"<<endl;
		cout<<"3. ���Ԥ��"<<endl;
		cout<<"4. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		fflush(stdin);
		cin>>choice;
		switch(choice){
		case '1':PrintAllOrder(u);break;
		case '2':SearchOrder(u);break;
		case '3':AddOrder(u);break;
		case '4':return;
		default:cout<<"�������,���������룡"<<endl;break;
		}
	}
}
/*�û���ϵͳ*/
void UserSystem(User u){
	char choice;
	while(1){
		int isDelete=0;
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"---------------------�û�ϵͳ-----------------------"<<endl;
		cout<<"1. ������Ϣ����"<<endl;
		cout<<"2. ��ѯ�̼�"<<endl;
		cout<<"3. Ԥ������"<<endl;
		cout<<"4. �Ƽ�����"<<endl;
		cout<<"5. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		fflush(stdin);
		cin>>choice;
		switch(choice){
		case '1':SelfInfoManage(u,isDelete);break;
		case '2':SeekShop();break;
		case '3':Order(u);break;
		case '4':IntroduceModule();break;
		case '5':return;
		default:cout<<"�������,���������룡"<<endl;break;
		}
		if(isDelete)
			return;
	}
}
/*�û�����MD5����*/
void setUserMD5(){
	FILE *fp;
	int i=0;
	UserList L;
	InitUserList(L);
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[6]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	fp=fopen("user.txt","w");
	setbuf(fp,NULL);
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	/*д���ͷ*/
	fputs("�û��˺� ���� ��ϵ��ʽ\n",fp);
	fflush(fp);
	/*���µ�˳�������д���ļ�*/
	for(i=1;i<=L.length;i++){
		unsigned char decrypt[16];
		getMD5(L.elem[i].password,decrypt);
		char password[33];
		convertUnCharToStr(password,decrypt,16);
		password[32]='\0';
		strcpy(L.elem[i].password,password);
		fputs(L.elem[i].userID,fp);
		fputc(' ',fp);
		fputs(L.elem[i].password,fp);
		fputc(' ',fp);
		fputs(L.elem[i].telephone,fp);
		if(i!=L.length)
			fputc('\n',fp);
	}
}
/*�û�ϵͳ��¼*/
int UserLogOn(){
	User u;
	char password[7],passwordMD5[33];
	FILE *fp;
	int i=0,j=0;
	UserList L;
	InitUserList(L);
	int flag=1;
	int n=1;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	cout<<"�˺�:";
	cin>>u.userID;
	j=Search_Bin(L,u.userID,u.password);
	if(j==0){
		cout<<"��Ǹ�����û������ڣ�"<<endl;
		cout<<"������������Ӧ���ּ�����ѡ��"<<endl;
		return ERROR;
	}
	else{
		while(flag){
			cout<<"����:";
			for(int i=0;i<6;i++)
			{
				fflush(stdin);
				password[i]=getch();
				if(password[i]!=13)
					cout<<"*";
			}
			password[6]='\0';
			unsigned char decrypt[16];
			getMD5(password,decrypt);
			convertUnCharToStr(passwordMD5,decrypt,16);
			passwordMD5[32]='\0';
			if(strcmp(u.password,passwordMD5)==0){
				cout<<endl<<"��¼�ɹ���"<<endl;
				flag=0;
				UserSystem(u);
			}
			else{
				cout<<endl<<"����������������룡"<<endl;
				if(n!=3)
					cout<<"������"<<3-n<<"�λ��ᣡ"<<endl;
				n++;
			}
			if(n>3){
				cout<<"�����Ѵ����ޣ���¼ʧ�ܣ�"<<endl;
				break;
			}
		}
	}
	fclose(fp);
	return OK;
}
/*�û�ϵͳע��*/
int UserRegist(){
	char password[7];
	int flag1=1,i=0;//����������������Ƿ�һ��
	int flag=1;//����˻��Ƿ�����Ϸ�
	int n1=1;//��������������
	int n2=1;//��ǵ绰�������
	int n=1;
	FILE *fp;
	UserList L;
	InitUserList(L);
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	cout<<"�����������˺š����롢��ϵ��ʽ:"<<endl;
	User u;
	while(flag){
		cout<<"�˺�:";
		cin>>u.userID;
		if(strlen(u.userID)!=6){
			cout<<"�˺Ų��Ϸ�������������!"<<endl;
			if(n!=3)
				cout<<"������"<<3-n<<"�λ��ᣡ"<<endl;
			n++;
		}
		else{
			flag=0;
		}
		if(n>3){
			cout<<"�Ѵ���������!ע��ʧ��!"<<endl;
			break;			
		}
	}
	int j=InsertPosition(L,u);
		if(j==0&&L.length!=0){
			cout<<"���û��Ѵ��ڣ������ظ�ע�ᣡ"<<endl;
				return ERROR;
		}
	while(flag1){
		cout<<"����(6λ):";
		for(int i=0;i<6;i++)
			{
				fflush(stdin);
				u.password[i]=getch();
				if(u.password[i]!=13)
					cout<<"*";
			}
			u.password[6]='\0';
		char passwordMD51[33];
		unsigned char decrypt1[16];
		getMD5(u.password,decrypt1);
		convertUnCharToStr(passwordMD51,decrypt1,16);
		passwordMD51[32]='\0';
		cout<<endl<<"���ٴ���������(6λ):";
		for(int i=0;i<6;i++)
		{
			fflush(stdin);
			password[i]=getch();
			if(password[i]!=13)
				cout<<"*";
		}
		password[6]='\0';
		char passwordMD52[33];
		unsigned char decrypt2[16];
		getMD5(password,decrypt2);
		convertUnCharToStr(passwordMD52,decrypt2,16);
		passwordMD52[32]='\0';
		if(strcmp(passwordMD51,passwordMD52)==0)
		{
			flag1=0;
			int flag2=1;//��ǵ绰�����Ƿ�Ϸ�
			while(flag2){
				cout<<endl<<"��ϵ��ʽ(11λ):";
				cin>>u.telephone;
				int length=strlen(u.telephone);
				int j=1;
				for(;j<=L.length;j++)
					if(strcmp(L.elem[j].telephone,u.telephone)==0)
						break;
				if(j<=L.length){
					cout<<"�õ绰�Ѵ��ڣ�"<<endl;
					if(n2!=3)
						cout<<"������"<<3-n2<<"�λ��ᣡ";
					n2++;
				}
				else if(length!=11){
					cout<<"�绰���Ϸ�������������!"<<endl;
					if(n2!=3)
						cout<<"������"<<3-n2<<"�λ��ᣡ";
					n2++;
				}
				else
					flag2=0;
				if(n2>3){
					cout<<"�Ѵ���������!ע��ʧ��!"<<endl;
					break;
				}
				strcpy(u.password,passwordMD51);
			}
			if(n2>3)
				break;
			int i=InsertPosition(L,u);
			UserListInsert(L,i,u);
			fp=fopen("user.txt","w");
			if(!fp)
				cout<<"user�ļ���ʧ�ܣ�";
			/*д���ͷ*/
			fputs("�û��˺� ���� ��ϵ��ʽ\n",fp);
			/*���µ�˳�������д���ļ�*/
			for(i=1;i<=L.length;i++){
				fputs(L.elem[i].userID,fp);
				fputc(' ',fp);
				fputs(L.elem[i].password,fp);
				fputc(' ',fp);
				fputs(L.elem[i].telephone,fp);
				if(i!=L.length)
					fputc('\n',fp);
			}
			cout<<"ע��ɹ���"<<endl;
			fclose(fp);
		}
		else{
			cout<<endl<<"�����������벻һ�£����������룡"<<endl;
			if(n1!=3)
				cout<<"������"<<3-n1<<"�λ��ᣡ"<<endl;
			n1++;
		}
		if(n1>3){
			cout<<"�Ѵ���������!ע��ʧ��!"<<endl;
			return ERROR;
		}	
		if(n2>3||n>3)
			return ERROR;
	}
	return OK;
}
/*�鿴�̼���Ϣ*/
void PrintShopInfo(char shopName[]){
	ShopList L;
	InitShopList(L);
	ReadShop(L);
	HashTable H;
	H.elem=new Shop[1000];
	CreateHashTable(H,L);
	int address=SearchHashTable(H,shopName);
	cout<<"�̼���Ϣ����:"<<endl;
	cout<<"�̼�����: "<<H.elem[address].shopName<<endl;
	cout<<"�̼�����: "<<H.elem[address].shoptype<<endl;
	cout<<"����: "<<H.elem[address].avgScore<<endl;
	cout<<"ƽ������: "<<H.elem[address].avePrice<<endl;
	cout<<"��ַ: "<<H.elem[address].address<<endl;
	cout<<"��ϵ�绰: "<<H.elem[address].phone<<endl;
	cout<<"��ɫ��Ʒ: ";
	for(int i=0;i<H.elem[address].foodNum;i++){
		cout<<H.elem[address].food[i].food_name;
		if(i!=H.elem[address].foodNum-1)
			cout<<",";
	}
	cout<<endl;
	if(H.elem[address].CommentNum!=0){
		cout<<"����:"<<endl;
		for(int i=0;i<H.elem[address].CommentNum;i++)
			cout<<"������"<<i+1<<"��"<<H.elem[address].Comment[i];	
	}
	else
		cout<<"���̼��������ۣ�"<<endl;
	getch();
}
/*�޸��̼���Ϣ*/
void ModifyShopInfo(char shopName[]){
	ShopList L;
	InitShopList(L);
	ReadShop(L);
	HashTable H;
	H.elem=new Shop[1000];
	CreateHashTable(H,L);
	int address=SearchHashTable(H,shopName);
	Shop p;
	char message[20];
	cout<<"�������̼���Ҫ�޸ĵ���Ϣ(�������޸ģ���ֱ�Ӱ��س���): "<<endl;
	fflush(stdin);
	cout<<"�̼�����: ";
	gets(p.shoptype);
	if(p.shoptype[0]!=0)
		strcpy(L.elem[H.pos[address]].shoptype,p.shoptype);
	cout<<"�̼�ID: ";
	gets(p.shopID);
	if(p.shopID[0]!=0)
		strcpy(L.elem[H.pos[address]].shopID,p.shopID);
	cout<<"�˾�����: ";
	gets(p.avePrice);
	if(p.avePrice[0]!=0)
		strcpy(L.elem[H.pos[address]].avePrice,p.avePrice);
	cout<<"��ַ: ";
	gets(p.address);
	if(p.address[0]!=0)
		strcpy(L.elem[H.pos[address]].address,p.address);
	cout<<"�绰: ";
	gets(p.phone);
	if(p.address[0]!=0)
		strcpy(L.elem[H.pos[address]].phone,p.phone);
	cout<<"��ɫ��: ";
	cout<<endl<<"��������Ҫ��Ʒ����(�������Ҫ,����0):";
	cin>>p.foodNum;
	if(p.foodNum!=0){
		L.elem[H.pos[address]].foodNum=p.foodNum;
		for(int i=0;i<p.foodNum;i++){
			fflush(stdin);
			cout<<"��ƷID: ";
			gets(p.food[i].food_id);
			strcpy(L.elem[H.pos[address]].food[i].food_id,p.food[i].food_id);
			cout<<"��Ʒ����: ";
			gets(p.food[i].food_name);
			strcpy(L.elem[H.pos[address]].food[i].food_name,p.food[i].food_name);
			cout<<"��Ʒ�۸�: ";
			gets(p.food[i].food_price);
			strcpy(L.elem[H.pos[address]].food[i].food_price,p.food[i].food_price);
		}
	}
	WriteShop(L);
	cout<<"�޸ĳɹ�!"<<endl;
}
/*ע���̼���Ϣ*/
int DeleteShopInfo(char shopName[]){
	ShopList L;
	InitShopList(L);
	ReadShop(L);
	HashTable H;
	H.elem=new Shop[1000];
	CreateHashTable(H,L);
	char yesno;
	cout<<"ȷ��Ҫע�����˻���(y/n)"<<endl;
	cin>>yesno;
	if((yesno=='y')||(yesno=='Y')){
		int address=SearchHashTable(H,shopName);
		ShopListDelete(L,H.pos[address]);
		WriteShop(L);
		LinkQueue Q;
		InitQueue(Q);
		ReadOrder(Q);
		LinkQueue Q1;
		InitQueue(Q1);
		QueuePtr p=Q.front->next;
		while(p){
			if(strcmp(p->data.shopName,shopName)==0){
				p->data.isOut=true;
				OrderInfo info;
				strcpy(info.date,p->data.date);
				strcpy(info.shopName,p->data.shopName);
				strcpy(info.userID,p->data.userID);
				EnQueue(Q1,info);
			}
				p=p->next;
		}
		WriteOrder(Q);
		cout<<"ע���ɹ�!"<<endl;
		return OK;
	}
	else{
		cout<<"����ȡ��ע����"<<endl;
		return ERROR;
	}
}
/*�̼���Ϣ����*/
void ShopManage(char shopName[],int &isDelete){
	cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
	cout<<"----------------�̼�ϵͳ:�̼���Ϣ����--------------"<<endl;
	cout<<"1. �鿴�̼���Ϣ"<<endl;
	cout<<"2. �޸��̼���Ϣ"<<endl;
	cout<<"3. ע���̼���Ϣ"<<endl;
	char choice;
	cin>>choice;
	switch(choice){
	case '1':PrintShopInfo(shopName);break;
	case '2':ModifyShopInfo(shopName);break;
	case '3':
		isDelete=DeleteShopInfo(shopName);break;
	default:
		cout<<"�������,���������룡"<<endl;break;
	}
}
/*��ʾ�̼ҵ�����Ԥ��*/
void PrintAllOrder2(char shopName[],LinkQueue Q){
	if(Q.front==Q.rear)
		cout<<"Ԥ����Ϣ������!"<<endl;
	else{
		QueuePtr p=Q.front->next;
		printf("%-10s %-60s %-20s\n","�û��˺�","�̼�����","Ԥ��ʱ��");
		while(p){
			if(strcmp(p->data.shopName,shopName)==0&&p->data.isOut==false)
				printf("%-10s %-60s %-20s\n",p->data.userID,p->data.shopName,p->data.date);
			p=p->next;
		}
	}
	getch();
}
/*��ѯĳ�û���Ԥ��*/
void SearchUserOrder(char shopName[],LinkQueue Q){
	char userID[20];
	cout<<"�������û��˺�: ";
	cin>>userID;
	if(Q.front==Q.rear)
		cout<<"Ԥ����Ϣ������!"<<endl;
	else{
		QueuePtr p=Q.front->next;
		int n=0;
		while(p){
			if(strcmp(p->data.userID,userID)==0)
				n++;
			p=p->next;
		}
		if(n!=0)
			printf("%-10s %-60s %-20s\n","�û��˺�","�̼�����","Ԥ��ʱ��");
		else{
			cout<<"��Ǹ�����û���Ԥ����Ϣ������!"<<endl;
			return;
		}
		p=Q.front->next;
		while(p){
			if((strcmp(p->data.shopName,shopName)==0)&&(strcmp(p->data.userID,userID)==0)&&p->data.isOut==false)
				printf("%-10s %-60s %-20s\n",p->data.userID,p->data.shopName,p->data.date);
			p=p->next;
		}
	}
	getch();
}
/*ɾ��Ԥ��*/
void DeleteOrder(char shopName[],LinkQueue &Q){
	LinkQueue Q1;
	InitQueue(Q1);
	QueuePtr p=Q.front->next;
	OrderInfo oi;
	int n=0;
	int flag=1,orderNum=0;//���ɾ�������Ƿ�Ϸ�
	while(flag){
		cout<<"��������Ҫ�����Ԥ������: ";
		cin>>n;
		if(n<0){
			cout<<"�������,���������룡"<<endl;
		}
		else if(n==0){
			cout<<"����ȡ��ɾ����"<<endl;
			break;
		}
		else
			flag=0;
	}
	if(n==0)
		return;
	int n2=n;
	while(p){
		if(strcmp(p->data.shopName,shopName)==0){
			if(n2>0)
				p->data.isOut=true;
			OrderInfo info;
			strcpy(info.date,p->data.date);
			strcpy(info.shopName,p->data.shopName);
			strcpy(info.userID,p->data.userID);
			EnQueue(Q1,info);
			n2--;
		}
		p=p->next;
	}
	printf("%-10s %-20s\n","�û��˺�","Ԥ��ʱ��");
	while(n>0){
		DeQueue(Q1,oi);
		printf("%-10s %-20s\n",oi.userID,oi.date);
		n--;
	}
	WriteOrder(Q);
	cout<<"����ɹ���"<<endl;
	getch();
}
/*Ԥ������*/
void Order2(char shopName[]){
	char choice;
	LinkQueue Q;
	InitQueue(Q);
	ReadOrder(Q);
	while(1){
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"------------------�̼�ϵͳ:Ԥ��ϵͳ-----------------"<<endl;
		cout<<"1. ��ʾ����Ԥ��"<<endl;
		cout<<"2. ��ѯĳ�û���Ԥ��"<<endl;
		cout<<"3. ɾ��Ԥ��"<<endl;
		cout<<"4. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		fflush(stdin);
		cin>>choice;
		switch(choice){
		case '1':PrintAllOrder2(shopName,Q);break;
		case '2':SearchUserOrder(shopName,Q);break;
		case '3':DeleteOrder(shopName,Q);break;
		case '4':return;break;
		default:cout<<"����������������룡"<<endl;break;
		}
		if(choice=='4')
			break;
	}
}
/*�˳�ϵͳ*/
void Exit()
{
	char yesno;
	void menu();
	cout<<"��ȷ��Ҫ�˳���?(y/n)";
	cin>>yesno;
	while(yesno=='n'||yesno=='N')
	{
		menu();
		cin>>yesno;
	}
	exit(0);
}
/*�̼�����MD5����*/
void setShopMD5(){
	ShopList L;
	InitShopList(L);
	ReadShop(L);
	for(int i=1;i<=L.length;i++){
		unsigned char decrypt[16];
		getMD5(L.elem[i].shopPassword,decrypt);
		char password[35];
		convertUnCharToStr(password,decrypt,16);
		password[33]='\0';
		strcpy(L.elem[i].shopPassword,password);
	}
	WriteShop(L);
}
/*�̼ҵ�¼*/
int ShopLogOn(char shopName[]){
	char shopPassword[35];
	int flag=1;//����Ƿ�������ȷ
	int n=1;//��¼�����������
	while(flag){
		cout<<"�������̼����ƺ�����"<<endl;
		cout<<"�̼�����: ";
		fflush(stdin);
		gets(shopName);
		cout<<"����:";
		int i=0;
		shopPassword[i]=getch();
		cout<<"*";
		while(shopPassword[i]!=13)
		{
			i++;
			fflush(stdin);
			shopPassword[i]=getch();
			if(shopPassword[i]!=13)
				cout<<"*";
		}
		shopPassword[i++]='\0';
		unsigned char decrypt[16];
		getMD5(shopPassword,decrypt);
		char shopPasswordMD5[35];
		convertUnCharToStr(shopPasswordMD5,decrypt,16);
		shopPasswordMD5[32]='\0';
		cout<<endl;
		ShopList L;
		InitShopList(L);
		ReadShop(L);
		HashTable H;
		H.elem=new Shop[1000];
		CreateHashTable(H,L);
		int address=SearchHashTable(H,shopName);
		if(address==-1){
			cout<<"��Ǹ�����̼Ҳ�����,���������룡"<<endl;
			if(n!=3)
				cout<<"������"<<3-n<<"�λ��ᣡ"<<endl;
			n++;
		}
		else if(strcmp(H.elem[address].shopPassword,shopPasswordMD5)!=0){
			cout<<"����������������룡"<<endl;
			if(n!=3)
				cout<<"������"<<3-n<<"�λ��ᣡ"<<endl;
			n++;
		}
		else{
			cout<<"��¼�ɹ���"<<endl;
			flag=0;
		}
		if(n>3)
		{
			cout<<"��������Ѵ����ޣ���¼ʧ�ܣ�"<<endl;
			return ERROR;
		}
	}
	return OK;
}
/*��ѯ�����û�*/
void PrintAllUser(UserList L){
	FILE *fp;
	int i=0;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	printf("%-10s %-30s\n","�û��˺�","��ϵ��ʽ");
	for(int i=1;i<=L.length;i++)
		printf("%-10s %-30s\n",L.elem[i].userID,L.elem[i].telephone);
}
/*��ѯĳ���û�*/
void SearchOneUser(UserList L){
	FILE *fp;
	char userID[100];
	int flag=0;//����û��Ƿ����
	int i=0;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	cout<<"������Ҫ��ѯ���û��˺�:";
	cin>>userID;
	for(int i=1;i<=L.length;i++)
		if(strcmp(L.elem[i].userID,userID)==0){
			cout<<"�û��˺�: "<<L.elem[i].userID<<endl;
			cout<<"��ϵ��ʽ: "<<L.elem[i].telephone<<endl;
			flag=1;
			break;
		}
	if(flag==0)
		cout<<"��Ǹ�����û������ڣ�"<<endl;
}
/*ɾ��ĳ���û�*/
void DeleteOneUser(UserList &L){
	FILE *fp;
	char userID[100];
	int flag=0;//����û��Ƿ����
	int i=0,j=1;
	fp=fopen("user.txt","r");
	if(!fp)
		cout<<"user�ļ���ʧ�ܣ�";
	int c;
	while(i<1 && (c=fgetc(fp))!=EOF)  
	{
	  if (c=='\n') i++;
	}//������ͷ
	while(!feof(fp)){
		fscanf(fp,"%s",&L.elem[i].userID);
		fscanf(fp,"%s",&L.elem[i].password);
		fscanf(fp,"%s",&L.elem[i].telephone);
		L.elem[i].userID[6]='\0';
		L.elem[i].password[32]='\0';
		L.elem[i].telephone[11]='\0';
		i++;
		L.length++;
	}//���û���Ϣ���뵽˳���
	fclose(fp);
	cout<<"������Ҫɾ�����û��˺�:";
	cin>>userID;
	for(;j<=L.length;j++)
		if(strcmp(L.elem[j].userID,userID)==0)
			break;
	if(j>L.length){
		cout<<"��Ǹ�����û������ڣ�"<<endl;
		return;
	}
	char yesno;
	cout<<"ȷ��Ҫɾ����(y/n)";
	cin>>yesno;
	if(yesno=='y'||yesno=='Y'){
		for(i=1;i<=L.length;i++)
		if(strcmp(L.elem[i].userID,userID)==0){
			flag=1;
			break;
		}
		if(flag==0)
			cout<<"���û������ڣ�"<<endl;
		else{
			UserListDelete(L,i);
			fp=fopen("user.txt","w");
			setbuf(fp,NULL);
			if(!fp)
				cout<<"user�ļ���ʧ�ܣ�";
			/*д���ͷ*/
			fputs("�û��˺� ���� ��ϵ��ʽ\n",fp);
			fflush(fp);
			/*���µ�˳�������д���ļ�*/
			for(i=1;i<=L.length;i++){
				fputs(L.elem[i].userID,fp);
				fputc(' ',fp);
				fputs(L.elem[i].password,fp);
				fputc(' ',fp);
				fputs(L.elem[i].telephone,fp);
				if(i!=L.length)
					fputc('\n',fp);
			}
			LinkQueue Q;
			InitQueue(Q);
			ReadOrder(Q);
			LinkQueue Q1;
			InitQueue(Q1);
			QueuePtr p=Q.front->next;
			while(p){
				if(strcmp(p->data.userID,userID)==0){
					p->data.isOut=true;
					OrderInfo info;
					strcpy(info.date,p->data.date);
					strcpy(info.shopName,p->data.shopName);
					strcpy(info.userID,p->data.userID);
					EnQueue(Q1,info);
				}
				p=p->next;
			}
			WriteOrder(Q);
			cout<<"ɾ���ɹ���"<<endl;
		}
	}
	else
		cout<<"����ȡ��ɾ����"<<endl;
}
/*�û�����*/
void BUserManage(){
	char choice;
	UserList L;
	InitUserList(L);
	cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
	cout<<"/-------------��̨����ϵͳ: �û�����---------------"<<endl;
	cout<<"1. ��ѯ�����û�"<<endl;
	cout<<"2. ��ѯĳ���û�"<<endl;
	cout<<"3. ɾ��ĳ���û�"<<endl;
	cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
	cin>>choice;
	switch(choice){
	case '1':PrintAllUser(L);break;
	case '2':SearchOneUser(L);break;
	case '3':DeleteOneUser(L);break;
	default:
		cout<<"�������,���������룡"<<endl;
	}
}
/*����̽�ⷨASL*/
double get_ASL(HashTable H,ShopList L){
	int findnum=0;
	for(int i=1;i<=L.length;i++){
		int address=((unsigned char)(L.elem[i].shopName[0]-176)*94+(unsigned char)(L.elem[i].shopName[1]-161))%1000;
		//int num=findnum;
		findnum++;
		while(strcmp(H.elem[address].shopName,L.elem[i].shopName)!=0)
		{
			address++;
			address=address%1000;
			findnum++;
		}
		//cout<<"��"<<i<<"��:"<<findnum-num<<endl;
	}
	double ASL=findnum*1.0/L.length;
	return ASL;
}
/*��ѯ�����̼�(����̽��)*/
void PrintAllShop(HashTable H){
	printf("%-12s %-42s %-20s %-10s %-10s %-60s %-30s\n","shopID","shopName","shopType","avgScore","avePrice","address","phone");
	for(int i=0;i<1000;i++)
		if(H.hasElem[i])
			printf("%-12s %-42s %-20s %-10s %-10s %-60s %-30s\n",H.elem[i].shopID,H.elem[i].shopName,H.elem[i].shoptype,H.elem[i].avgScore,H.elem[i].avePrice,H.elem[i].address,H.elem[i].phone);
}
/*��ѯĳ���̼�(����̽��)*/
void SearchOneShop(HashTable H){
	char shopName[100];
	cout<<"������Ҫ��ѯ���̼�����:";
	cin>>shopName;
	int address=SearchHashTable(H,shopName);
	if(address==-1)
		cout<<"��Ǹ�����̼Ҳ�����!"<<endl;
	else{
		cout<<"shopID: "<<H.elem[address].shopID<<endl;
		cout<<"shopName: "<<H.elem[address].shopName<<endl;
		cout<<"shopType: "<<H.elem[address].shoptype<<endl;
		cout<<"avgScore: "<<H.elem[address].avgScore<<endl;
		cout<<"avePrice: "<<H.elem[address].avePrice<<endl;
		cout<<"address: "<<H.elem[address].address<<endl;
		cout<<"phone: "<<H.elem[address].phone<<endl;
	}
}
/*ɾ��ĳ���̼�(����̽��)*/
void DeleteOneShop(HashTable H,ShopList L){
	char shopName[100];
	cout<<"������Ҫɾ�����̼�����:";
	cin>>shopName;
	char yesno;
	cout<<"ȷ��Ҫɾ����?(y/n)";
	cin>>yesno;
	if((yesno=='y')||(yesno=='Y')){
		int address=SearchHashTable(H,shopName);
		if(address==-1)
			cout<<"��Ǹ�����̼Ҳ�����!"<<endl;
		else{
			ShopListDelete(L,H.pos[address]);
			WriteShop(L);
			LinkQueue Q;
			InitQueue(Q);
			ReadOrder(Q);
			LinkQueue Q1;
			InitQueue(Q1);
			QueuePtr p=Q.front->next;
			while(p){
				if(strcmp(p->data.shopName,shopName)==0){
					p->data.isOut=true;
					OrderInfo info;
					strcpy(info.date,p->data.date);
					strcpy(info.shopName,p->data.shopName);
					strcpy(info.userID,p->data.userID);
					EnQueue(Q1,info);
				}
					p=p->next;
			}
			cout<<"ɾ���ɹ���"<<endl;
		}
	}
	else
		cout<<"����ȡ��ɾ����"<<endl;
}
/*�̼ҹ���(����̽��)*/
void BShopManage(){
	char choice;
	while(1){
		ShopList L;
		InitShopList(L);
		ReadShop(L);
		HashTable H;
		H.elem=new Shop[1000];
		memset(H.hasElem,false,1000);//��ϣ���ʼÿ��λ��û��Ԫ��
		memset(H.isDelete,false,1000);//��ϣ���ʼÿ��λ��û��ɾ����
		CreateHashTable(H,L);
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"/----------��̨����ϵͳ: �̼ҹ���(����̽��)---------"<<endl;
		cout<<"����̽�ⷨ��ASL: ";
		printf("%.2f\n",get_ASL(H,L));
		cout<<"1. ��ѯ�����̼�"<<endl;
		cout<<"2. ��ѯĳ���̼�"<<endl;
		cout<<"3. ɾ��ĳ���̼�"<<endl;
		cout<<"4. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		cin>>choice;
		switch(choice){
		case '1':PrintAllShop(H);break;
		case '2':SearchOneShop(H);break;
		case '3':DeleteOneShop(H,L);break;
		case '4':return;
		default:
			cout<<"�������,���������룡"<<endl;
		}
	}
}
/*����ַ��ASL*/
double get_ASL2(HTList H[1000],ShopList L){
	int findnum2=0;
	for(int i=1;i<=L.length;i++){
		int address=((unsigned char)(L.elem[i].shopName[0]-176)*94+(unsigned char)(L.elem[i].shopName[1]-161))%1000;
		HTList p=H[address]->next;
		while(p){
			findnum2++;
			if(strcmp(p->data.shopName,L.elem[i].shopName)==0)
				break;
			p=p->next;
		}
	}
	double ASL2=findnum2*1.0/L.length;
	return ASL2;
}
/*��ѯ�����̼�(����ַ)*/
void PrintAllShop2(HTList H[1000],ShopList L){
	printf("%-12s %-42s %-20s %-10s %-10s %-60s %-30s\n","shopID","shopName","shopType","avgScore","avePrice","address","phone");
	for(int i=0;i<1000;i++){
		if(HTListLength(H[i])!=0){
			HTList p=H[i]->next;
			while(p){
				printf("%-12s %-42s %-20s %-10s %-10s %-60s %-30s\n",L.elem[p->data.pos].shopID,L.elem[p->data.pos].shopName,L.elem[p->data.pos].shoptype,L.elem[p->data.pos].avgScore,L.elem[p->data.pos].avePrice,L.elem[p->data.pos].address,L.elem[p->data.pos].phone);
				p=p->next;
			}
		}
	}
}
/*��ѯĳ���̼�(����ַ)*/
void SearchOneShop2(HTList H[1000],ShopList L){
	char shopName[100];
	cout<<"������Ҫ��ѯ���̼�����:";
	cin>>shopName;
	int address=SearchHashTable2(H,shopName);
	if(address==-1)
		cout<<"��Ǹ�����̼Ҳ�����!"<<endl;
	else{
		HTList p=H[address]->next;
		while(p){
			if(strcmp(L.elem[p->data.pos].shopName,shopName)==0){
				cout<<"shopID: "<<L.elem[p->data.pos].shopID<<endl;
				cout<<"shopName: "<<L.elem[p->data.pos].shopName<<endl;
				cout<<"shopType: "<<L.elem[p->data.pos].shoptype<<endl;
				cout<<"avgScore: "<<L.elem[p->data.pos].avgScore<<endl;
				cout<<"avePrice: "<<L.elem[p->data.pos].avePrice<<endl;
				cout<<"address: "<<L.elem[p->data.pos].address<<endl;
				cout<<"phone: "<<L.elem[p->data.pos].phone<<endl;
				break;
			}
			p=p->next;
		}
	}
}
/*ɾ��ĳ���̼�(����ַ)*/
void DeleteOneShop2(HTList H[1000],ShopList L){
	char shopName[100];
	cout<<"������Ҫɾ�����̼�����:";
	cin>>shopName;
	char yesno;
	cout<<"ȷ��Ҫɾ����?(y/n)";
	cin>>yesno;
	if((yesno=='y')||(yesno=='Y')){
		int address=SearchHashTable2(H,shopName);
		if(address==-1)
			cout<<"��Ǹ�����̼Ҳ�����!"<<endl;
		else{
			HTList p=H[address]->next;
			while(p){
				if(strcmp(L.elem[p->data.pos].shopName,shopName)==0){
					ShopListDelete(L,p->data.pos);
					WriteShop(L);
					LinkQueue Q;
					InitQueue(Q);
					ReadOrder(Q);
					LinkQueue Q1;
					InitQueue(Q1);
					QueuePtr p=Q.front->next;
					while(p){
						if(strcmp(p->data.shopName,shopName)==0){
							p->data.isOut=true;
							OrderInfo info;
							strcpy(info.date,p->data.date);
							strcpy(info.shopName,p->data.shopName);
							strcpy(info.userID,p->data.userID);
							EnQueue(Q1,info);
						}
							p=p->next;
					}
					cout<<"ɾ���ɹ���"<<endl;
					break;
				}
				p=p->next;
			}
		}
	}
	else
		cout<<"����ȡ��ɾ����"<<endl;

}
/*�̼ҹ���(����ַ)*/
void BShopManage2(){
	char choice;
	while(1){
		ShopList L;
		InitShopList(L);
		ReadShop(L);
		HTList H[1000];
		for(int i=0;i<1000;i++)
			InitHTList(H[i]);
		CreateHashTable2(H,L);
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"/----------��̨����ϵͳ: �̼ҹ���(����ַ)-----------"<<endl;
		cout<<"����ַ����ASL: ";
		printf("%.2f\n",get_ASL2(H,L));
		cout<<"1. ��ѯ�����̼�"<<endl;
		cout<<"2. ��ѯĳ���̼�"<<endl;
		cout<<"3. ɾ��ĳ���̼�"<<endl;
		cout<<"4. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		cin>>choice;
		switch(choice){
		case '1':PrintAllShop2(H,L);break;
		case '2':SearchOneShop2(H,L);break;
		case '3':DeleteOneShop2(H,L);break;
		case '4':return;
		default:
			cout<<"�������,���������룡"<<endl;
		}
	}
}
/*����������ASL*/
double get_ASL3(BSTree T,ShopList L){
	int findnum3=0;
	for(int i=1;i<=L.length;i++)
		SearchBST(T,L.elem[i].shopName,findnum3);
	double ASL3=findnum3*1.0/L.length;
	return ASL3;
}
/*�����������������*/
void Traverse(BSTree T,int &i,ShopList L){
    if(T){
        Traverse(T->lchild,++i,L);
		printf("%-12s %-42s %-20s %-10s %-10s %-60s %-30s\n",L.elem[T->data.pos].shopID,L.elem[T->data.pos].shopName,L.elem[T->data.pos].shoptype,L.elem[T->data.pos].avgScore,L.elem[T->data.pos].avePrice,L.elem[T->data.pos].address,L.elem[T->data.pos].phone);
        Traverse(T->rchild,++i,L);
    }
}
/*��ѯ�����̼�(����������)*/
void PrintAllShop3(BSTree T,ShopList L){
	int i=1;
	printf("%-12s %-42s %-20s %-10s %-10s %-60s %-30s\n","shopID","shopName","shopType","avgScore","avePrice","address","phone");
	Traverse(T,i,L);
}
/*��ѯĳ���̼�(����������)*/
void SearchOneShop3(BSTree T,ShopList L){
	char shopName[100];
	cout<<"������Ҫ��ѯ���̼�����:";
	cin>>shopName;
	int findnum3=0;
	BSTree b=SearchBST(T,shopName,findnum3);
	if(b==NULL)
		cout<<"��Ǹ�����̼Ҳ�����!"<<endl;
	else{
		cout<<"shopID: "<<L.elem[b->data.pos].shopID<<endl;
		cout<<"shopName: "<<L.elem[b->data.pos].shopName<<endl;
		cout<<"shopType: "<<L.elem[b->data.pos].shoptype<<endl;
		cout<<"avgScore: "<<L.elem[b->data.pos].avgScore<<endl;
		cout<<"avePrice: "<<L.elem[b->data.pos].avePrice<<endl;
		cout<<"address: "<<L.elem[b->data.pos].address<<endl;
		cout<<"phone: "<<L.elem[b->data.pos].phone<<endl;
	}
}
/*ɾ��ĳ���̼�(����������)*/
void DeleteOneShop3(BSTree &T,ShopList &L){
	char shopName[100];
	cout<<"������Ҫɾ�����̼�����:";
	cin>>shopName;
	char yesno;
	cout<<"ȷ��Ҫɾ����?(y/n)";
	cin>>yesno;
	int findnum3=0;
	if((yesno=='y')||(yesno=='Y')){
		BSTree b=SearchBST(T,shopName,findnum3);
		if(b==NULL)
			cout<<"��Ǹ�����̼Ҳ�����!"<<endl;
		else{
			ShopListDelete(L,b->data.pos);
			WriteShop(L);
			LinkQueue Q;
			InitQueue(Q);
			ReadOrder(Q);
			LinkQueue Q1;
			InitQueue(Q1);
			QueuePtr p=Q.front->next;
			while(p){
				if(strcmp(p->data.shopName,shopName)==0){
					p->data.isOut=true;
					OrderInfo info;
					strcpy(info.date,p->data.date);
					strcpy(info.shopName,p->data.shopName);
					strcpy(info.userID,p->data.userID);
					EnQueue(Q1,info);
				}
					p=p->next;
			}
			cout<<"ɾ���ɹ���"<<endl;
		}
	}
	else
		cout<<"����ȡ��ɾ����"<<endl;
}
/*�̼ҹ���(����������)*/
void BShopManage3(){
	char choice;
	while(1){
		ShopList L;
		InitShopList(L);
		ReadShop(L);
		BSTree T=NULL;
		for(int i=1;i<=L.length;i++){
			BSTInfo e;
			strcpy(e.shopName,L.elem[i].shopName);
			e.pos=i;
			InsertBST(T,e);
		}
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"/--------��̨����ϵͳ: �̼ҹ���(����������)---------"<<endl;
		cout<<"��������������ASL: ";
		printf("%.2f\n",get_ASL3(T,L));
		cout<<"1. ��ѯ�����̼�"<<endl;
		cout<<"2. ��ѯĳ���̼�"<<endl;
		cout<<"3. ɾ��ĳ���̼�"<<endl;
		cout<<"4. ������һ��"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		cin>>choice;
		switch(choice){
		case '1':PrintAllShop3(T,L);break;
		case '2':SearchOneShop3(T,L);break;
		case '3':DeleteOneShop3(T,L);break;
		case '4':return;
		default:
			cout<<"�������,���������룡"<<endl;
		}
	}
}
/*�̼ҹ���ģ��*/
void BShopManageModule(){
	char choice;
	while(1){
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"/--------------��̨����ϵͳ: �̼ҹ���---------------"<<endl;
		cout<<"1. ����̽�ⷨ"<<endl;
		cout<<"2. ����ַ��"<<endl;
		cout<<"3. ������������"<<endl;
		cout<<"4. ������һ��"<<endl;
		fflush(stdin);
		cin>>choice;
		switch(choice){
		case '1':BShopManage();break;
		case '2':BShopManage2();break;
		case '3':BShopManage3();break;
		case '4':return;
		default:
			cout<<"�������,���������룡"<<endl;
		}
	}
}
/*�˵�*/
void menu(){
	char choice;
	while(1){
		cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
		cout<<"1. �û�ϵͳ"<<endl;
		cout<<"2. �̼�ϵͳ"<<endl;
		cout<<"3. ��̨����ϵͳ"<<endl;
		cout<<"4. �˳�ϵͳ"<<endl;
		cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
		fflush(stdin);
		cin>>choice;
		if(choice=='1'){
			while(1){
				char choice1;
				int flag1=0;//flag1����Ƿ��˳�
				cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
				cout<<"--------------------�û���¼ϵͳ--------------------"<<endl;
				cout<<"1. ��¼"<<endl;
				cout<<"2. ע��"<<endl;
				cout<<"3. ������һ��"<<endl;
				cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
				fflush(stdin);
				cin>>choice1;
				if((choice1!='1')&&(choice1!='2')&&(choice1!='3')){
					cout<<"�������,���������룡"<<endl;
					continue;
				}
				switch(choice1){
				case '1':UserLogOn();break;
				case '2':UserRegist();break;
				case '3':
					flag1=1;
					break;
				}
				if(flag1==1)
					break;//������һ��
			}
		}
		else if(choice=='2'){
			char shopName[100];
			bool isLogOn=ShopLogOn(shopName);
			while(isLogOn){
				char choice2;
				cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
				cout<<"---------------------�̼�ϵͳ---------------------"<<endl;
				cout<<"1. �̼���Ϣ����"<<endl;
				cout<<"2. Ԥ������"<<endl;
				cout<<"3. ������һ��"<<endl;
				cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
				fflush(stdin);
				cin>>choice2;
				if((choice2!='1')&&(choice2!='2')&&(choice2!='3')){
					cout<<"�������,���������룡"<<endl;
					continue;
				}
				int flag2=0;//flag2����Ƿ��˳�
				int isDelete=0;
				switch(choice2){
				case '1':ShopManage(shopName,isDelete);break;
				case '2':Order2(shopName);break;
				case '3':
					flag2=1;
					break;
				}
				if(flag2==1||isDelete==1)
					break;//������һ��		
			}
		}
		else if(choice =='3'){
			while(1){
				char choice3;
				int flag3=0;//flag3����Ƿ��˳�
				cout<<"/*************���Ų͹�Ԥ��������Ϣϵͳ*************/"<<endl;
				cout<<"---------------------��̨����ϵͳ------------------"<<endl;
				cout<<"1. �û�����"<<endl;
				cout<<"2. �̼ҹ���"<<endl;
				cout<<"3. ������һ��"<<endl;
				cout<<"��������Ӧ�����ּ�����ѡ��"<<endl;
				fflush(stdin);
				cin>>choice3;
				if((choice3!='1')&&(choice3!='2')&&(choice3!='3')){
					cout<<"�������,���������룡"<<endl;
					continue;
				}
				switch(choice3){
				case '1':BUserManage();break;
				case '2':BShopManageModule();break;
				case '3':
					flag3=1;
					break;
				}
				if(flag3==1)
					break;//������һ��			
			}
		}
		else if(choice=='4')
			Exit();
		else
			cout<<"�������,���������룡"<<endl;
	}
}
int main(){
	//setUserMD5();//�û��������
	//setShopMD5();//�̼��������
	menu();
	return 0;
}