#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<algorithm>
#include <iostream>
using namespace std;
struct User{
	char name[20]; //�û���
	char passwd[7]; //����
};//�û�

struct Directory{
	char name[20]; //�û���
	char path[100]; //Ŀ¼�ľ���·��
	int level;//Ŀ¼���
	//int num;//Ŀ¼�����ļ�����
};//Ŀ¼

struct File{
	char name[20]; //�ļ���
	char owner[20];//�ļ�������
	char path[100];//�ļ��ľ���·��
	char content[1000];//�ļ�����
	char limit[5];//�ļ�Ȩ�ޣ�r--ֻ�� rw--�ɶ���д��
	char ctime[50];//�ļ�����ʱ��
	int state;
};//�ļ�

struct Active{
	char path[100];//�ļ�·��
	int n;//��ǰ�û���
};

/*�����û�*/
void ReadUser(User user[],int &UN){
	FILE *fp;
	fp=fopen("SystemData.txt","r");
	if(!fp)
		cout<<"�ļ���ʧ�ܣ�";
	while(!feof(fp)){
		fscanf(fp,"%s",&user[UN].name);
		if(strcmp(user[UN].name,"user")==0)
			continue;
		if(strcmp(user[UN].name,"directory")==0){
			memset(user[UN].name,0,20);
			break;
		}
		fscanf(fp,"%s",&user[UN].passwd);
		UN++;//�û�����+1
	}
	fclose(fp);
}

/*д���û�*/
void WriteUser(User user[],int UN){
	FILE *fp;
	fp=fopen("SystemData.txt","w");
	if(!fp)
		cout<<"�ļ���ʧ�ܣ�";
	fputs("user\n",fp);
	for(int i=0;i<UN;i++){
		fputs(user[i].name,fp);
		fputc(' ',fp);
		fputs(user[i].passwd,fp);
		fputc('\n',fp);
	}
	fclose(fp);
}

/*����Ŀ¼*/
void ReadDir(Directory dir[],int &DN){
	FILE *fp;
	int flag=0;//��־�Ƿ�ʼ��Ŀ¼����
	fp=fopen("SystemData.txt","r");
	if(!fp)
		cout<<"�ļ���ʧ�ܣ�"<<endl;
	char info[100];
	while(!feof(fp)){
		memset(info,0,100);
		fscanf(fp,"%s",&info);
		if(strcmp(info,"directory")==0){
			flag=1;
			continue;
		}
		if(flag==1&&strcmp(info,"file")!=0){
			strcpy(dir[DN].name,info);
			fscanf(fp,"%s",&dir[DN].path);
			fscanf(fp,"%d",&dir[DN].level);
			//fscanf(fp,"%d",&dir[DN].num);
			DN++;//Ŀ¼����+1
		}//����Ŀ¼���ֵ�û�ж����ļ�����
		if(strcmp(info,"file")==0)
			break;
	}
	fclose(fp);
}

/*д��Ŀ¼*/
void WriteDir(Directory dir[],int DN){
	FILE *fp;
	fp=fopen("SystemData.txt","a+");
	if(!fp)
		cout<<"�ļ���ʧ�ܣ�"<<endl;;
	fputs("directory\n",fp);
	for(int i=0;i<DN;i++){
		fputs(dir[i].name,fp);
		fputc(' ',fp);
		fputs(dir[i].path,fp);
		fputc(' ',fp);
		fprintf(fp,"%d",dir[i].level);
		//fputc(' ',fp);
		//fprintf(fp,"%d",dir[i].num);
		fputc('\n',fp);
	}
	fclose(fp);
}

/*�����ļ�*/
void ReadFile(File f[],int &FN){
	FILE *fp;
	int flag=0,length=0;//��־�Ƿ�ʼ���ļ�����
	fp=fopen("SystemData.txt","r");
	if(!fp)
		cout<<"�ļ���ʧ�ܣ�"<<endl;
	char info[100];
	while(!feof(fp)){
		memset(info,0,100);
		fscanf(fp,"%s",&info);
		if(strcmp(info,"file")==0){
			flag=1;
			continue;
		}
		if(flag==1){
			if(strcmp(info,"filename:")==0)
				fscanf(fp,"%s",&f[FN].name);
			else if(strcmp(info,"owner:")==0)
				fscanf(fp,"%s",&f[FN].owner);
			else if(strcmp(info,"path:")==0)
				fscanf(fp,"%s",&f[FN].path);
			else if(strcmp(info,"time:")==0){
				//fscanf(fp,"%s",&f[FN].ctime);
				fseek(fp,1,1);
				fgets(f[FN].ctime,50,fp);
				length=strlen(f[FN].ctime);
				f[FN].ctime[length-1]='\0';
			}
			else if(strcmp(info,"limit:")==0)
				fscanf(fp,"%s",&f[FN].limit);
			else if(strcmp(info,"content:")==0){
				//fscanf(fp,"%s",&f[FN].content);
				fseek(fp,1,1);
				fgets(f[FN].content,1000,fp);
				//length=strlen(f[FN].content);
				//f[FN].content[length-1]='\0';
			}
			else if(strcmp(info,"state:")==0){
				fscanf(fp,"%d",&f[FN].state);
				FN++;//�ļ�����+1
			}
		}
		if(strcmp(info,"file")==0)
			break;
	}
	for(int i=0;i<FN;i++)
		f[i].content[strlen(f[i].content)-1]='\0';
	fclose(fp);
}

/*д���ļ�*/
void WriteFile(File f[],int FN){
	FILE *fp;
	fp=fopen("SystemData.txt","a+");
	if(!fp)
		cout<<"�ļ���ʧ�ܣ�"<<endl;
	fputs("file\n",fp);
	for(int i=0;i<FN;i++){
		fputs("filename: ",fp);
		fputs(f[i].name,fp);
		fputc('\n',fp);
		fputs("owner: ",fp);
		fputs(f[i].owner,fp);
		fputc('\n',fp);
		fputs("path: ",fp);
		fputs(f[i].path,fp);
		fputc('\n',fp);
		fputs("time: ",fp);
		fputs(f[i].ctime,fp);
		fputc('\n',fp);
		fputs("limit: ",fp);
		fputs(f[i].limit,fp);
		fputc('\n',fp);
		fputs("content: ",fp);
		fputs(f[i].content,fp);
		fputc('\n',fp);
		fputs("state: ",fp);
		fprintf(fp,"%d",f[i].state);
		if(i!=FN-1)
			fputc('\n',fp);
	}
	fclose(fp);
}

/*�û���¼*/
void login(char name[],char passwd[]){
	int flag=0,flag2=0,n=0,UN=0;
	User user[20];
	while(flag==0){
		flag2=0;
		system("cls");
		cout<<endl<<"--------�û���¼--------"<<endl;
		cout<<"�û�����";
		cin>>name;
		cout<<"���룺";
		for(int i=0;i<6;i++)
		{
			fflush(stdin);
			passwd[i]=getch();
			if(passwd[i]!=13)
				cout<<"*";
		}
		passwd[6]='\0';
		ReadUser(user,UN);
		for(int j=0;j<UN;j++){
			if(strcmp(name,user[j].name)==0){
				if(strcmp(passwd,user[j].passwd)==0){
					cout<<endl<<"��¼�ɹ�!"<<endl;
					flag=1;//����Ƿ��¼�ɹ�
					getch();
				}
				else{
					n++;
					flag2=1;//�����Ϊ����������¼ʧ��
					if(n!=5)
						cout<<endl<<"����������������룡������"<<5-n<<"�λ��ᡭ"<<endl;
					else
						cout<<endl<<"�����Ѵ����ޣ�ϵͳ�����˳���"<<endl;
					getch();
				}
				break;
			}
		}
		if(flag==0&&flag2==0){
			n++;
			if(n!=5)
				cout<<endl<<"�û������ڣ����������룡������"<<5-n<<"�λ��ᡭ"<<endl;
			else
				cout<<endl<<"�����Ѵ����ޣ�ϵͳ�����˳���"<<endl;
			getch();
		}
		if(n==5)
			exit(0);
	}
}

/*�����ļ�*/
void create(char filename[],char fpath[],char name[]){
	User user[20];
	Directory dir[200];
	File f[500];
	char fpath2[100];
	int UN=0,DN=0,FN=0,flag1=0,flag2=0;
	time_t timep;
    time(&timep);
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(int i=0;i<DN;i++){
		if(strcmp(dir[i].path,fpath)==0){
			flag1=1;
			break;//����ļ�����Ŀ¼�Ƿ����
		}
	}
	if(flag1==0){
		cout<<"error: ���������ļ�����Ŀ¼��"<<fpath<<"��������"<<endl;
		return;
	}
	strcpy(fpath2,fpath);
	strcat(fpath2,"/");
	strcat(fpath2,filename);
	for(int i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath2)==0){
			cout<<"error: ���������ļ���"<<filename<<"���Ѵ���"<<endl;
			return;
		}
	}
	strcpy(f[FN].name,filename);
	strcpy(f[FN].path,fpath2);
	strcpy(f[FN].owner,name);
	strcpy(f[FN].limit,"rw");//�ļ�Ĭ�Ͽɶ���д
	strftime(f[FN].ctime, sizeof(f[FN].ctime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	strcpy(f[FN].content,"��");
	f[FN].state=0;
	FN++;
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*ɾ���ļ�*/
void del(char fpath[]){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag=0,i=0;
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(int j=i;j<FN;j++)
		f[j]=f[j+1];
	memset(f[FN-1].name,0,20);
	memset(f[FN-1].owner,0,20);
	memset(f[FN-1].path,0,100);
	memset(f[FN-1].ctime,0,50);
	memset(f[FN-1].limit,0,5);
	memset(f[FN-1].content,0,1000);
	f[FN-1].state=0;
	FN--;
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*�޸��ļ�Ȩ��*/
void chmod(char fpath[],char p[]){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag=0,i=0;
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	strcpy(f[i].limit,p);
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*���ļ�*/
void open(char fpath[],Active a[]){
	File f[500];
	int FN=0,flag=0,flag2=0,i=0,n=0;
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(int j=0;j<500;j++)
		if(a[j].path[0]!=0)
			n++;//���ļ�����
	for(int j=0;j<n;j++)
		if(strcmp(a[j].path,fpath)==0){
			cout<<"error: ���������ļ���"<<fpath<<"���Ѵ�"<<endl;
			return;
		}
	strcpy(a[n].path,fpath);
	a[n].n++;
}

/*�ر��ļ�*/
void close(char fpath[],Active a[]){
	File f[500];
	int FN=0,flag=0,flag2=0,i=0,j=0,n=0;
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(j=0;j<500;j++)
		if(a[j].path[0]!=0)
			n++;//���ļ�����
	for(j=0;j<n;j++)
		if(strcmp(a[j].path,fpath)==0){
			flag2=1;
			break;
		}
	if(flag2==0){
		cout<<"error: ���������ļ���"<<fpath<<"��δ��"<<endl;
		return;
	}
	a[j].n--;
	if(a[j].n==0){
		for(int k=j;k<n;k++)
			a[k]=a[k+1];
		memset(a[n-1].path,0,100);
		a[n-1].n=0;
	}
}

/*���ļ��ж���*/
void read(char fpath[],Active a[]){
	File f[500];
	int FN=0,flag=0,flag2=0,i=0,j=0,n=0,k=0;
	char *p;
	char content[1000];
	char c[50][50];
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(j=0;j<500;j++)
		if(a[j].path[0]!=0)
			n++;//���ļ�����
	for(j=0;j<n;j++)
		if(strcmp(a[j].path,fpath)==0){
			flag2=1;
			break;
		}
	if(flag2==0){
		cout<<"error: ���������ļ���"<<fpath<<"��δ��"<<endl;
		return;
	}
	strcpy(content,f[i].content);
	p=strtok(content,"+");
	while(p){
		strcpy(c[k],p);
		k++;//�ļ�����
		p=strtok(NULL,"+");
	}
	if(k!=0){
		cout<<"�ļ���"<<fpath<<"������Ϊ:"<<endl;
		for(int m=0;m<k;m++)
			cout<<c[m]<<endl;
	}
	else
		cout<<"�ļ�����Ϊ�գ�"<<endl;
}

/*���ļ���д��*/
void write(char fpath[],Active a[],int option){
	File f[500];
	int FN=0,UN=0,DN=0,flag=0,flag2=0,flag3=0,i=0,j=0,n=0;
	User user[20];
	Directory dir[200];
	char line[50];
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(j=0;j<500;j++)
		if(a[j].path[0]!=0)
			n++;//���ļ�����
	for(j=0;j<n;j++)
		if(strcmp(a[j].path,fpath)==0){
			flag2=1;
			break;
		}
	if(flag2==0){
		cout<<"error: ���������ļ���"<<fpath<<"��δ��"<<endl;
		return;
	}
	if(strcmp(f[i].limit,"r")==0){
		cout<<"error: ���������ļ���"<<fpath<<"��Ϊֻ���ļ�"<<endl;
		return;
	}
	cout<<"�Ѵ򿪡�"<<fpath<<"��,������:"<<endl;
	FN=0;
	UN=0;
	DN=0;
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	if(f[i].state==0){
		f[i].state=1;//���ļ���������
		WriteUser(user,UN);
		WriteDir(dir,DN);
		WriteFile(f,FN);
		flag3=1;
	}
	else{
		cout<<"error: ���ļ���������..."<<endl;
		return;
	}
	gets(line);
	if(option==0){
		memset(f[i].content,0,1000);
		strcpy(f[i].content,line);
		while(strcmp(line,"#")!=0){
			gets(line);
			if(strcmp(line,"#")!=0){
				strcat(f[i].content,"+");
				strcat(f[i].content,line);
			}
		}
	}
	else{
		strcat(f[i].content,"+");
		strcat(f[i].content,line);
		while(strcmp(line,"#")!=0){
			gets(line);
			if(strcmp(line,"#")!=0){
				strcat(f[i].content,"+");
				strcat(f[i].content,line);
			}
		}
	}
	f[i].state=0;
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*�ַ����滻*/
int replace(char *sSrc, char *sMatchStr, char *sReplaceStr)
{
	int  StringLen;
	char caNewString[256];
 
	char *FindPos = strstr(sSrc, sMatchStr);
	if( (!FindPos) || (!sMatchStr) )
		return -1;
 
	while( FindPos )
	{
		memset(caNewString, 0, sizeof(caNewString));
		StringLen = FindPos - sSrc;
		strncpy(caNewString, sSrc, StringLen);
		strcat(caNewString, sReplaceStr);
		strcat(caNewString, FindPos + strlen(sMatchStr));
		strcpy(sSrc, caNewString);
 
		FindPos = strstr(sSrc, sMatchStr);
	}
 
	return 0;
}

/*�ƶ��ļ�*/
void move(char spath[],char dpath[],char option1,char option2,int &flag){
	int UN=0,DN=0,FN=0,flag1=0,flag2=0,flag3=0,i=0,j=0,k=0,t=0,n=0;
	char dpath2[100],d[100],filename[20],filename2[20];
	char *p;
	char temp[20][20];
	User user[20];
	Directory dir[200];
	File f[500];
	time_t timep;
    time(&timep);
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,spath)==0){
			flag1=1; //���Դ�ļ��Ƿ����
			break;
		}
	}
	if(flag1==0){
		cout<<"error: ���������ļ���"<<spath<<"��������"<<endl;
		return;
	}
	strcpy(dpath2,dpath);
	p=strtok(dpath2,"/");
	while(p){
		strcpy(temp[k],p);
		k++;//·���㼶
		p=strtok(NULL,"/");
	}
	strcpy(d,"/");
	for(int m=0;m<k-1;m++){
		if(m!=0)
			strcat(d,"/");
		strcat(d,temp[m]);
	}
	strcpy(filename,temp[k-1]);
	p=strtok(filename,".");
	strcpy(filename2,d);
	strcat(filename2,"/");
	strcat(filename2,p);
	for(t=0;t<DN;t++){
		if(strcmp(dir[t].path,d)==0){
			flag2=1; //���Ŀ���ļ�����Ŀ¼�Ƿ����
			break;
		}
	}
	if(strcmp(spath,dpath)==0){
		cout<<"tips: �ļ���"<<temp[k-1]<<"������Ŀ¼��"<<d<<"���У������ƶ�"<<endl;
		return;
	}
	if(flag2==0){
		cout<<"error: ��������Ŀ¼��"<<d<<"��������"<<endl;
		return;
	}
	for(t=0;t<FN;t++){
		if(strstr(f[t].path,filename2)!=NULL){
			flag3=1;//���Ŀ���ļ�����Ŀ¼���Ƿ��������ļ�
			n++;
		}	
	}
	for(t=0;t<FN;t++){
		if(strcmp(f[t].path,dpath)==0){
			flag1=1;
			break;
		}
	}
	if(flag3==1){
		if(option2!='f'){
			char yesno;
			cout<<"Ŀ¼��"<<d<<"���к���ͬ���ļ����Ƿ�Ҫ���ǣ�(y/n)";
			cin>>yesno;
			flag=1;
			if(yesno!='y'&&yesno!='Y'){
				return;
			}
		}
		if(option1=='b'){
			char filename3[20];
			char num[5];
			strcpy(filename3,p);
			itoa(n,num,10);
			strcat(filename3,"(");
			strcat(filename3,num);
			strcat(filename3,")");
			strcat(filename3,".txt");
			memset(f[t].name,0,20);
			strcpy(f[t].name,filename3);
			replace(f[t].path,temp[k-1],filename3);//����
			memset(f[i].ctime,0,50);
			strcpy(f[i].ctime,f[t].ctime);
			memset(f[i].name,0,20);
			strcpy(f[i].name,temp[k-1]);
			memset(f[i].path,0,100);
			strcpy(f[i].path,dpath);
			memset(f[t].ctime,0,50);
			strftime(f[t].ctime, sizeof(f[t].ctime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
			cout<<"tips: ԭ��"<<dpath<<"���ı����ļ�Ϊ��"<<f[t].path<<"��";
			flag++;
		}
		else{
			memset(f[t].content,0,1000);
			strcpy(f[t].content,f[i].content);
			for(int m=i;m<FN;m++)
				f[m]=f[m+1];
			memset(f[FN-1].name,0,20);
			memset(f[FN-1].owner,0,20);
			memset(f[FN-1].path,0,100);
			memset(f[FN-1].ctime,0,50);
			memset(f[FN-1].limit,0,5);
			memset(f[FN-1].content,0,1000);
			f[FN-1].state=0;
			FN--;
		}
	}
	else{
		f[FN]=f[i];
		memset(f[FN].name,0,20);
		strcpy(f[FN].name,temp[k-1]);
		memset(f[FN].path,0,100);
		strcpy(f[FN].path,dpath);
		memset(f[i].ctime,0,50);
		strftime(f[FN].ctime, sizeof(f[FN].ctime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
		FN++;
		for(int m=i;m<FN;m++)
			f[m]=f[m+1];
		memset(f[FN-1].name,0,20);
		memset(f[FN-1].owner,0,20);
		memset(f[FN-1].path,0,100);
		memset(f[FN-1].ctime,0,50);
		memset(f[FN-1].limit,0,5);
		memset(f[FN-1].content,0,1000);
		f[FN-1].state=0;
		FN--;
	}
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*�����ļ�*/
void copy(char spath[],char dpath[],char option1,char option2,int &flag){
	int UN=0,DN=0,FN=0,flag1=0,flag2=0,flag3=0,i=0,j=0,k=0,t=0,n=0;
	char dpath2[100],d[100],filename[20],filename2[20];
	char *p;
	char temp[20][20];
	User user[20];
	Directory dir[200];
	File f[500];
	time_t timep;
    time(&timep);
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,spath)==0){
			flag1=1; //���Դ�ļ��Ƿ����
			break;
		}
	}
	if(flag1==0){
		cout<<"error: ���������ļ���"<<spath<<"��������"<<endl;
		return;
	}
	strcpy(dpath2,dpath);
	p=strtok(dpath2,"/");
	while(p){
		strcpy(temp[k],p);
		k++;//·���㼶
		p=strtok(NULL,"/");
	}
	strcpy(d,"/");
	for(int m=0;m<k-1;m++){
		if(m!=0)
			strcat(d,"/");
		strcat(d,temp[m]);
	}
	strcpy(filename,temp[k-1]);
	p=strtok(filename,".");
	strcpy(filename2,d);
	strcat(filename2,"/");
	strcat(filename2,p);
	for(t=0;t<DN;t++){
		if(strcmp(dir[t].path,d)==0){
			flag2=1; //���Ŀ���ļ�����Ŀ¼�Ƿ����
			break;
		}
	}
	if(flag2==0){
		cout<<"error: ��������Ŀ¼��"<<d<<"��������"<<endl;
		return;
	}
	for(t=0;t<FN;t++){
		if(strstr(f[t].path,filename2)!=NULL){
			flag3=1;//���Ŀ���ļ�����Ŀ¼���Ƿ��������ļ�
			n++;
		}	
	}
	for(t=0;t<FN;t++){
		if(strcmp(f[t].path,dpath)==0){
			flag1=1;
			break;
		}
	}
	if(flag3==1){
		if(option2!='f'){
			char yesno;
			cout<<"Ŀ¼��"<<d<<"���к���ͬ���ļ����Ƿ�Ҫ���ǣ�(y/n)";
			flag=1;
			cin>>yesno;
			if(yesno!='y'&&yesno!='Y'){
				return;
			}
		}
		if(option1=='b'){
			char filename3[20];
			char num[5];
			strcpy(filename3,p);
			itoa(n,num,10);
			strcat(filename3,"(");
			strcat(filename3,num);
			strcat(filename3,")");
			strcat(filename3,".txt");
			memset(f[t].name,0,20);
			strcpy(f[t].name,filename3);
			replace(f[t].path,temp[k-1],filename3);//����
			f[FN]=f[i];
			memset(f[FN].ctime,0,50);
			strcpy(f[FN].ctime,f[t].ctime);
			memset(f[t].ctime,0,50);
			strftime(f[t].ctime, sizeof(f[t].ctime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
			memset(f[FN].name,0,20);
			strcpy(f[FN].name,temp[k-1]);
			memset(f[FN].path,0,100);
			strcpy(f[FN].path,dpath);
			FN++;
			cout<<"tips: ԭ��"<<dpath<<"���ı����ļ�Ϊ��"<<f[t].path<<"��";
			flag++;
		}
		else{
			memset(f[t].content,0,1000);
			strcpy(f[t].content,f[i].content);
		}
	}
	else{
		f[FN]=f[i];
		memset(f[FN].name,0,20);
		strcpy(f[FN].name,temp[k-1]);
		memset(f[FN].path,0,100);
		strcpy(f[FN].path,dpath);
		memset(f[i].ctime,0,50);
		strftime(f[FN].ctime, sizeof(f[FN].ctime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
		FN++;
	}
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*�����ļ�*/
void find(char option1,char name[],char option2,char time[],char username[]){
	int FN=0,flag=0,n2=0,n3=0;
	File f[200],f2[200],f3[200];
	ReadFile(f,FN);
	if(option1=='n'){
		for(int i=0;i<FN;i++){
			if(strcmp(f[i].name,name)==0&&strstr(f[i].path,username)!=NULL){
				f2[n2]=f[i];
				n2++;
			}
		}
		if(option2=='t'){
			for(int i=0;i<n2;i++){
				if(strstr(f2[i].ctime,time)!=NULL){
					f3[n3]=f2[i];
					n3++;
				}
			}
		}
		else{
			for(int i=0;i<n2;i++){
				f3[n3]=f2[i];
				n3++;
			}
		}
	}
	else{
		for(int i=0;i<FN;i++){
			if(strstr(f[i].path,username)!=NULL){
				f2[n2]=f[i];
				n2++;
			}
		}
		if(option2=='t'){
			for(int i=0;i<n2;i++){
				if(strstr(f2[i].ctime,time)!=NULL){
					f3[n3]=f2[i];
					n3++;
				}
			}
		}
		else{
			for(int i=0;i<n2;i++){
				f3[n3]=f2[i];
				n3++;
			}
		}
	}
	if(n3!=0){
		printf("%-15s%-15s%-30s%-30s%-10s\n","�ļ���","������","�ļ�·��","����ʱ��","Ȩ��");
		for(int i=0;i<n3;i++){
			printf("%-15s%-15s%-30s%-30s",f3[i].name,f3[i].owner,f3[i].path,f3[i].ctime);
			if(strcmp(f3[i].limit,"r")==0)
				printf("%-10s\n","ֻ��");
			if(strcmp(f3[i].limit,"rw")==0)
				printf("%-10s\n","�ɶ���д");
		}
	}
	else
		cout<<"���޷����������ļ�"<<endl;
}

/*��ʾ�ļ�ǰn��*/
void head(char fpath[],Active a[],int num){
	File f[500];
	int FN=0,flag=0,flag2=0,i=0,j=0,n=0,k=0;
	char *p;
	char content[1000];
	char c[50][50];
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(j=0;j<500;j++)
		if(a[j].path[0]!=0)
			n++;//���ļ�����
	for(j=0;j<n;j++)
		if(strcmp(a[j].path,fpath)==0){
			flag2=1;
			break;
		}
	if(flag2==0){
		cout<<"error: ���������ļ���"<<fpath<<"��δ��"<<endl;
		return;
	}
	strcpy(content,f[i].content);
	p=strtok(content,"+");
	while(p){
		strcpy(c[k],p);
		k++;//�ļ�����
		p=strtok(NULL,"+");
	}
	if(num>k){
		cout<<"error: ѡ������ļ�����"<<k<<"��"<<endl;
		return;
	}
	cout<<"�ļ���"<<fpath<<"����ǰ"<<num<<"��Ϊ:"<<endl;
	for(int m=0;m<num;m++)
		cout<<c[m]<<endl;
}

/*��ʾ�ļ�ĩβn��*/
void tail(char fpath[],Active a[],int num){
	File f[500];
	int FN=0,flag=0,flag2=0,i=0,j=0,n=0,k=0;
	char *p;
	char content[1000];
	char c[50][50];
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,fpath)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: ���������ļ���"<<fpath<<"��������"<<endl;
		return;
	}
	for(j=0;j<500;j++)
		if(a[j].path[0]!=0)
			n++;//���ļ�����
	for(j=0;j<n;j++)
		if(strcmp(a[j].path,fpath)==0){
			flag2=1;
			break;
		}
	if(flag2==0){
		cout<<"error: ���������ļ���"<<fpath<<"��δ��"<<endl;
		return;
	}
	strcpy(content,f[i].content);
	p=strtok(content,"+");
	while(p){
		strcpy(c[k],p);
		k++;//�ļ�����
		p=strtok(NULL,"+");
	}
	if(num>k){
		cout<<"error: ѡ������ļ�����"<<k<<"��"<<endl;
		return;
	}
	cout<<"�ļ���"<<fpath<<"����ĩβ"<<num<<"��Ϊ:"<<endl;
	for(int m=k-num;m<k;m++)
		cout<<c[m]<<endl;
}

/*�Ӵ��̵����ļ�*/
void import(char filename[],char spath[],char dpath[],char owner[]){
	FILE *fp;
	User user[20];
	Directory dir[200];
	File f[500];
	time_t timep;
    time(&timep);
	int UN=0,DN=0,FN=0,i=0,k=0,flag=0;
	char content[50][50];
	char *p;
	char dpath2[100],dpath3[100];
	char temp[20][20];
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	fp=fopen(spath,"r");
	if(!fp){
		cout<<"error: �ļ���ʧ�ܣ�"<<endl;
		return;
	}
	strcpy(dpath2,dpath);
	p=strtok(dpath2,"/");
	while(p){
		strcpy(temp[k],p);
		k++;//�ļ�����
		p=strtok(NULL,"/");
	}
	for(int i=0;i<FN;i++){
		if(strcmp(f[i].path,dpath)==0){
			cout<<"tips: �ļ��ѵ���"<<endl;
			return;
		}
	}
	dpath3[0]='/';
	strcpy(dpath3+1,temp[0]);
	for(int i=1;i<k-1;i++){
		strcat(dpath3,"/");
		strcat(dpath3,temp[i]);
	}
	for(int i=0;i<DN;i++){
		if(strcmp(dir[i].path,dpath3)==0){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"error: �������󣬵����Ŀ��Ŀ¼�����ڣ�"<<endl;
		return;
	}
	strcpy(f[FN].name,filename);
	strcpy(f[FN].path,dpath);
	strcpy(f[FN].owner,owner);
	strcpy(f[FN].limit,"rw");
	strftime(f[FN].ctime, sizeof(f[FN].ctime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	while(!feof(fp)){
		fgets(content[i],100,fp);
		i++;
	}
	for(int j=0;j<i;j++){
		int length=0;
		length=strlen(content[j]);
		if(j!=i-1)
			content[j][length-1]='\0';
		if(j==0)
			strcpy(f[FN].content,content[j]);
		else
			strcat(f[FN].content,content[j]);
		if(j!=i-1)
			strcat(f[FN].content,"+");
	}
	if(i==0)
		strcpy(f[FN].content,"��");
	f[FN].state=0;
	FN++;
	fclose(fp);
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}

/*���ļ�����������*/
void Export(char filename[],char spath[],char dpath[],int flag){
	FILE *fp;
	char content[100];
	char c[50][50];
	char *p;
	File f[500];
	int FN=0,flag1=0,i=0,k=0;
	ReadFile(f,FN);
	for(i=0;i<FN;i++){
		if(strcmp(f[i].path,spath)==0){
			flag1=1;
			break;
		}
	}
	if(flag1==0){
		cout<<"error: ���������ļ���"<<spath<<"��������"<<endl;
		return;
	}
	if(flag==0)
		fp=fopen(dpath,"w");
	else
		fp=fopen(dpath,"a+");
	if(!fp){
		cout<<"error: �ļ���ʧ�ܣ�"<<endl;
		return;
	}
	strcpy(content,f[i].content);
	p=strtok(content,"+");
	while(p){
		strcpy(c[k],p);
		k++;//�ļ�����
		p=strtok(NULL,"+");
	}
	if(flag==1)
		fputc('\n',fp);
	for(int j=0;j<k;j++){
		fputs(c[j],fp);
		if(j!=k-1)
			fputc('\n',fp);
	}
	fclose(fp);
}

/*����Ŀ¼*/
void mkdir(char dpath2[],int l){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag=0,i=0,flag2=0;
	char *p;
	char d[20][20];//Ŀ¼��
	char dpath[100];
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	strcpy(dpath,dpath2);
	p=strtok(dpath2,"/");
	while(p){
		strcpy(d[i],p);
		i++;//·������
		p=strtok(NULL,"/");
	}
	if(l==1){
		if(flag==0){
			strcpy(dir[DN].name,d[0]);
			strcpy(dir[DN].path,dpath);
			dir[DN].level=l+1;
			//dir[DN].num=0;
			DN++;
			WriteUser(user,UN);
			WriteDir(dir,DN);
			WriteFile(f,FN);
		}
	}
	else if(l>=2){
		int j=1;
		char path[100];
		path[0]='/';
		strcpy(path+1,d[0]);
		while(j<=l){
			flag2=0;
			strcat(path,"/");
			strcat(path,d[j]);
			for(int k=0;k<DN;k++){
				if(strcmp(path,dir[k].path)==0){
					flag2=1;
					break;
				}
			}
			if(flag2==0){
				strcpy(dir[DN].name,d[0]);
				strcpy(dir[DN].path,path);
				dir[DN].level=j+1;
				//dir[DN].num=0;
				DN++;
				WriteUser(user,UN);
				WriteDir(dir,DN);
				WriteFile(f,FN);
			}
			j++;
		}
	}

}

/*ɾ��Ŀ¼*/
void rmdir(char dpath[],char option1,char option2,int &flag){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag1=0,i=0,flag2=0;
	char *p;
	char d[20][20];//Ŀ¼��
	char dpath2[100];
	ReadUser(user,UN);
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<DN;i++){
		if(strcmp(dir[i].path,dpath)==0){
			flag1=1;//flag���Ŀ¼�Ƿ����
			break;
		}
	}
	if(flag1==0){
		cout<<"error: ��������Ŀ¼��"<<dpath<<"��������"<<endl;
		return;
	}
	for(i=0;i<DN;i++){
		if(strstr(dir[i].path,dpath)!=NULL&&strcmp(dir[i].path,dpath)!=0&&option1!='r'){
			cout<<"error: ��������, Ŀ¼��"<<dpath<<"����Ϊ��"<<endl;
			return;
		}
	}
	if(option2!='f'){
		char choice;
		cout<<"�Ƿ�ȷ��ɾ��Ŀ¼��"<<dpath<<"����(y/n)";
		cin>>choice;
		if(choice!='y'&&choice!='Y'){
			return;
		}
		flag=1;
	}
	for(i=0;i<DN;i++){
		if(strstr(dir[i].path,dpath)!=NULL){
			for(int j=i;j<DN;j++)
				dir[j]=dir[j+1];
			memset(dir[DN-1].name,0,20);
			memset(dir[DN-1].path,0,100);
			dir[DN-1].level=0;
			//dir[DN-1].num=0;
			DN--;
			i--;
		}
	}
	WriteUser(user,UN);
	WriteDir(dir,DN);
	WriteFile(f,FN);
}
bool cmp(const char *elem1, const char *elem2)  
{  
	if (strcmp(elem1, elem2) < 0)  
		return true;  
    return false;  
} 

/*�鿴Ŀ¼*/
void dir(char dpath[],int flag){
	User user[20];
	Directory dir[200];
	File f[500];
	int DN=0,FN=0,flag1=0,i=0,flag2=0,n1=0,n2=0,k=0;
	char *p;
	char temp1[20][20],temp2[50][50],d[200][100],ff[500][100],t[100];
	char path[100];
	ReadDir(dir,DN);
	ReadFile(f,FN);
	for(i=0;i<DN;i++){
		if(strcmp(dir[i].path,dpath)==0){
			flag1=1;//flag���Ŀ¼�Ƿ����
			break;
		}
	}
	if(flag1==0){
		cout<<"error: ��������Ŀ¼��"<<dpath<<"��������"<<endl;
		return;
	}
	if(flag==0){
		/*��ʾ��ǰĿ¼�е���Ŀ¼*/
		for(int j=0;j<DN;j++){
			k=0;
			strcpy(path,dir[j].path);
			p=strtok(path,"/");
			while(p){
				strcpy(temp1[k],p);
				k++;//·������
				p=strtok(NULL,"/");
			}
			if(strstr(dir[j].path,dpath)!=NULL&&dir[j].level==dir[i].level+1){
				strcpy(d[n1],temp1[k-1]);
				n1++;
			}
		}
		for(int j=0;j<n1-1;j++)
			for(int m=0;m<n1-1-j;m++){
				if(strcmp(d[m],d[m+1])>0){
					strcpy(t,d[m]);
					strcpy(d[m],d[m+1]);
					strcpy(d[m+1],t);
				}
			}
		if(n1!=0)
			cout<<"��Ŀ¼��"<<endl;
		for(int j=0;j<n1;j++){
			cout<<d[j]<<endl;
		}
		/*��ʾ��ǰĿ¼�е��ļ�*/
		for(int j=0;j<FN;j++){
			k=0;
			strcpy(path,f[j].path);
			p=strtok(path,"/");
			while(p){
				strcpy(temp2[k],p);
				k++;//·������
				p=strtok(NULL,"/");
			}
			if(strstr(f[j].path,dpath)!=NULL&&k==dir[i].level+1){
				strcpy(ff[n2],temp2[k-1]);
				n2++;
			}
		}
		for(int j=0;j<n2-1;j++)
			for(int m=0;m<n2-1-j;m++){
				if(strcmp(ff[m],ff[m+1])>0){
					strcpy(t,ff[m]);
					strcpy(ff[m],ff[m+1]);
					strcpy(ff[m+1],t);
				}
			}
		if(n2!=0)
			cout<<"�ļ���"<<endl;
		for(int j=0;j<n2;j++){
			cout<<ff[j]<<endl;
		}
		if(n1==0&&n2==0)
			cout<<"��"<<endl;
	}
	else{
		/*��ʾ��ǰĿ¼�е�������Ŀ¼*/
		for(int j=0;j<DN;j++){
			if(strstr(dir[j].path,dpath)!=NULL&&strcmp(dir[j].path,dpath)!=0){
				strcpy(d[n1],dir[j].path+strlen(dpath)+1);
				n1++;
			}
		}
		for(int j=0;j<n1-1;j++)
			for(int m=0;m<n1-1-j;m++){
				if(strcmp(d[m],d[m+1])>0){
					strcpy(t,d[m]);
					strcpy(d[m],d[m+1]);
					strcpy(d[m+1],t);
				}
			}
		if(n1!=0)
			cout<<"��Ŀ¼��"<<endl;
		for(int j=0;j<n1;j++){
			cout<<d[j]<<endl;
		}
		/*��ʾ��ǰĿ¼�е������ļ�*/
		for(int j=0;j<FN;j++){
			if(strstr(f[j].path,dpath)!=NULL){
				strcpy(ff[n2],f[j].path+strlen(dpath)+1);
				n2++;
			}
		}
		for(int j=0;j<n2-1;j++)
			for(int m=0;m<n2-1-j;m++){
				if(strcmp(ff[m],ff[m+1])>0){
					strcpy(t,ff[m]);
					strcpy(ff[m],ff[m+1]);
					strcpy(ff[m+1],t);
				}
			}
		if(n2!=0)
			cout<<"�ļ���"<<endl;
		for(int j=0;j<n2;j++){
			cout<<ff[j]<<endl;
		}
		if(n1==0&&n2==0)
			cout<<"��"<<endl;
	}
}

/*�����û�*/
void useradd(char username[],char password[]){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag=1;
	ReadUser(user,UN);
	for(int i=0;i<UN;i++){
		if(strcmp(username,user[i].name)==0){
			cout<<"error: ��������,�û���"<<username<<"���Ѵ���"<<endl;
			flag=0;//���Ҫ���ӵ��û��Ƿ��Ѿ�����
			break;
		}
	}
	if(flag==1){
		ReadDir(dir,DN);
		ReadFile(f,FN);
		strcpy(user[UN].name,username);
		strcpy(user[UN].passwd,password);
		strcpy(dir[DN].name,username);//Ϊ�����û������û���Ŀ¼
		dir[DN].path[0]='/';
		strcpy(dir[DN].path+1,username);
		dir[DN].level=1;
		//dir[DN].num=0;
		UN++;
		DN++;
		WriteUser(user,UN);
		WriteDir(dir,DN);
		WriteFile(f,FN);
	}
}

/*ɾ���û�*/
void userdel(char username[]){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag=0;
	ReadUser(user,UN);
	for(int i=0;i<UN;i++){
		if(strcmp(username,user[i].name)==0){
			flag=1;//���Ҫɾ�����û��Ƿ����
			break;
		}
	}
	if(flag==1){
		ReadDir(dir,DN);
		ReadFile(f,FN);
		for(int i=0;i<UN;i++){
			if(strcmp(user[i].name,username)==0){
				for(int j=i;j<UN;j++)
					user[j]=user[j+1];
				memset(user[UN-1].name,0,20);
				memset(user[UN-1].passwd,0,7);
				UN--;
				i--;
				break;
			}
		}//ɾ���û�
		for(int i=0;i<DN;i++){
			if(strcmp(dir[i].name,username)==0){
				for(int j=i;j<DN;j++)
					dir[j]=dir[j+1];
				memset(dir[DN-1].name,0,20);
				memset(dir[DN-1].path,0,100);
				dir[DN-1].level=0;
				//dir[DN-1].num=0;
				DN--;
				i--;
			}
		}//ɾ���û�����Ŀ¼
		for(int i=0;i<FN;i++){
			if(strcmp(f[i].owner,username)==0){
				for(int j=i;j<FN;j++)
					f[j]=f[j+1];
				memset(f[FN-1].name,0,20);
				memset(f[FN-1].owner,0,20);
				memset(f[FN-1].path,0,1000);
				memset(f[FN-1].ctime,0,20);
				memset(f[FN-1].limit,0,5);
				memset(f[FN-1].content,0,1000);
				FN--;
				i--;
			}
		}//ɾ���û������ļ�
		WriteUser(user,UN);
		WriteDir(dir,DN);
		WriteFile(f,FN);
	}
	else
		cout<<"error: ��������, �û���"<<username<<"��������"<<endl;
}

/*�޸��û�����*/
void password(char username[]){
	User user[20];
	Directory dir[200];
	File f[500];
	int UN=0,DN=0,FN=0,flag=0,i=0,n=0;
	char pwd1[7],pwd2[7],pwd3[7];//pwd1���˻�ԭ����,pwd2���޸ĺ������,pwd3��ȷ������
	ReadUser(user,UN);
	for(i=0;i<UN;i++){
		if(strcmp(username,user[i].name)==0){
			flag=1;//���Ҫ�޸ĵ��û��Ƿ����
			break;
		}
	}
	if(flag==1){
		cout<<"ԭ����: ";
		for(int j=0;j<6;j++)
		{
			fflush(stdin);
			pwd1[j]=getch();
			if(pwd1[j]!=13)
				cout<<"*";
		}
		pwd1[6]='\0';
		if(strcmp(pwd1,user[i].passwd)!=0)
			cout<<endl<<"error: �������"<<endl;
		else{
			cout<<endl<<"������: ";
			for(int j=0;j<6;j++)
			{
				fflush(stdin);
				pwd2[j]=getch();
				if(pwd2[j]!=13)
					cout<<"*";
			}
			pwd2[6]='\0';
			cout<<endl<<"ȷ������: ";
			for(int j=0;j<6;j++)
			{
				fflush(stdin);
				pwd3[j]=getch();
				if(pwd3[j]!=13)
					cout<<"*";
			}
			pwd3[6]='\0';
			cout<<endl;
			if(strcmp(pwd2,pwd3)!=0)
				cout<<"error: �������벻һ��"<<endl;
			else{
				strcpy(user[i].passwd,pwd2);
				ReadDir(dir,DN);
				ReadFile(f,FN);
				WriteUser(user,UN);
				WriteDir(dir,DN);
				WriteFile(f,FN);
			}
		}
	}
	else
		cout<<"error: ��������, �û���"<<username<<"��������"<<endl;
}

/*�鿴�û��б�*/
void userlist(){
	User user[20];
	int FN=0;
	ReadUser(user,FN);
	cout<<"ϵͳ�û��б�Ϊ:"<<endl;
	for(int i=0;i<FN;i++)
		cout<<user[i].name<<endl;
}

int main(){
	char path[100],path2[100];//path2Ϊpath�ָ�ǰ�ı���
	char *p,*p2;
	char temp[20][20],temp2[20][20]; //temp��Ű�'/'�ָ��·��,temp2��Ű�' '�ָ������
	char name[20];//��ǰ��¼�û����û���
	char passwd[7];//��ǰ��¼�û�������
	int level=0,i=0;
	Active a[500];
	for(int i=0;i<500;i++){
		memset(a[i].path,0,100);
		a[i].n=0;
	}
	login(name,passwd);
	system("cls");
	path[0]='/';
	strcpy(path+1,name);//��ʼ·��Ϊ�û���Ŀ¼
	strcpy(path2,path);
	p=strtok(path,"/");
	while(p){
		strcpy(temp[level],p);
		level++;//·������
		p=strtok(NULL,"/");
	}
	while(1){
		char command[50];
		cout<<"[ "<<name<<" # "<<temp[level-1]<<" ] ";
		gets(command);
		p2=strtok(command," ");
		for(i=0;i<20;i++)
			memset(temp2[i],0,20);
		i=0;
		while(p2){
			strcpy(temp2[i],p2);
			i++;
			p2=strtok(NULL," ");
		}
		if(strcmp(temp2[0],"login")==0){
			memset(name,0,20);
			memset(passwd,0,7);
			login(name,passwd);
			path[0]='/';
			strcpy(path+1,name);
			strcpy(path2,path);
			level=0;
			p=strtok(path,"/");
			for(i=0;i<20;i++)
				memset(temp[i],0,20);
			while(p){
				strcpy(temp[level],p);
				level++;//·������
				p=strtok(NULL,"/");
			}
			system("cls");
		}
		else if(strcmp(temp2[0],"create")==0){
			char fpath[100];//����·��
			char filename[20];//�ļ���
			int flag=0,flag2=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ���δ����"<<endl;
				continue;
			}
			else if(strstr(temp2[1],".txt")==NULL){
				cout<<"error: ���������ļ���ʽ���Ϸ�"<<endl;
				continue;
			}
			if(temp2[2][0]==0||temp2[2][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�����Ŀ¼δ����"<<endl;
				continue;
			}
			if(temp2[3][0]!=0&&temp2[3][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//create����û��ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(filename,temp2[1]);
				strcpy(fpath,path2);
				if(temp2[2][0]!=0){
					if(temp2[2][0]!='/')
						strcat(fpath,"/");
					strcat(fpath,temp2[2]);
				}
			}
			create(filename,fpath,name);
		}
		else if(strcmp(temp2[0],"delete")==0){
			char fpath[100];//����·��
			int flag=0,j=0,n=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//delete����û��ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				del(fpath);
			}
			for(j=0;j<500;j++)
				if(a[j].path[0]!=0)
					n++;//���ļ�����
			for(j=0;j<n;j++){
				if(strcmp(a[j].path,fpath)==0)
					break;
			}
			for(int k=j;k<n;k++)
				a[k]=a[k+1];
			memset(a[n].path,0,100);
			a[n].n=0;
		}
		else if(strcmp(temp2[0],"open")==0){
			char fpath[100];//����·��
			int flag=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//open����û��ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				open(fpath,a);
			}	
		}
		else if(strcmp(temp2[0],"close")==0){
			char fpath[100];//����·��
			int flag=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//open����û��ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				close(fpath,a);
			}
		}
		else if(strcmp(temp2[0],"read")==0){
			char fpath[100];//����·��
			int flag=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//read������ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				read(fpath,a);
			}
		}
		else if(strcmp(temp2[0],"write")==0){
			char fpath[100];//����·��
			int flag=0,flag2=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='a'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
				if(temp2[i][0]=='-'&&temp2[i][1]=='a')
					flag2=1;
			}//write����ֻ��-aѡ���ʾ׷��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				write(fpath,a,flag2);
			}
		}
		else if(strcmp(temp2[0],"move")==0){
			char spath[100],dpath[100];//Դ�ļ�·��,Ŀ���ļ�·��
			char option1,option2;
			int flag=0,f=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Դ�ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[1],".txt")==NULL){
				cout<<"error: ��������Դ�ļ�·�������Ϸ�"<<endl;
				continue;
			}
			if(temp2[2][0]==0||temp2[2][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ���ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[2],".txt")==NULL){
				cout<<"error: ��������Ŀ���ļ�·�������Ϸ�"<<endl;
				continue;
			}
			if(temp2[3][0]!=0&&temp2[3][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			else{
				strcpy(spath,path2);
				if(temp2[1][0]!='/'){
					strcat(spath,"/");
					strcat(spath,temp2[1]);
				}
				else
					strcat(spath,temp2[1]);
				strcpy(dpath,path2);
				if(temp2[2][0]!='/'){
					strcat(dpath,"/");
					strcat(dpath,temp2[2]);
				}
				else
					strcat(dpath,temp2[2]);
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='b'&&temp2[i][1]!='f'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
				if(temp2[i][1]=='b')
					option1='b';
				if(temp2[i][1]=='f')
					option2='f';
			}//move�����ѡ��-b��ʾ����ͬ���ļ����ƶ�ǰ���ݣ�-f��ʾ����ͬ���ļ����ƶ�ʱǿ�Ƹ���
			if(flag==0)
				move(spath,dpath,option1,option2,f);
			if(f==1)
				getchar();
			if(f==2){
				getchar();
				getchar();
			}
		}
		else if(strcmp(temp2[0],"copy")==0){
			char spath[100],dpath[100];//Դ�ļ�·��,Ŀ���ļ�·��
			char option1,option2;
			int flag=0,f=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Դ�ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[1],".txt")==NULL){
				cout<<"error: ��������Դ�ļ�·�������Ϸ�"<<endl;
				continue;
			}
			if(temp2[2][0]==0||temp2[2][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ���ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[2],".txt")==NULL){
				cout<<"error: ��������Ŀ���ļ�·�������Ϸ�"<<endl;
				continue;
			}
			if(temp2[3][0]!=0&&temp2[3][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			else{
				strcpy(spath,path2);
				if(temp2[1][0]!='/'){
					strcat(spath,"/");
					strcat(spath,temp2[1]);
				}
				else
					strcat(spath,temp2[1]);
				strcpy(dpath,path2);
				if(temp2[2][0]!='/'){
					strcat(dpath,"/");
					strcat(dpath,temp2[2]);
				}
				else
					strcat(dpath,temp2[2]);
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='b'&&temp2[i][1]!='f'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
				if(temp2[i][1]=='b')
					option1='b';
				if(temp2[i][1]=='f')
					option2='f';
			}//copy�����ѡ��-b��ʾ����ͬ���ļ����滻ǰ���ݣ�-f��ʾ����ͬ���ļ���ǿ�Ƹ���
			if(flag==0)
				copy(spath,dpath,option1,option2,f);
			if(f==1)
				getchar();
			if(f==2){
				getchar();
				getchar();
			}
		}
		else if(strcmp(temp2[0],"find")==0){
			char option1='0',option2='0';
			char filename[20];
			char time[50];
			int flag=0,flag2=0,flag3=0;
			if(temp2[1][0]!=0&&temp2[1][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
					if(temp2[i][0]=='-'&&temp2[i][1]!='n'&&temp2[i][1]!='t'){
						cout<<"error: ѡ�����"<<endl;
						flag=1;
						break;
					}
					if(temp2[i][1]=='n'){
						if(temp2[i+1][0]==0||temp2[i+1][0]=='-'){
							cout<<"error: ȱ�ٲ������ļ���δ����"<<endl;
							flag2=1;
							break;
						}
						option1='n';
						strcpy(filename,temp2[i+1]);
					}
					if(temp2[i][1]=='t'){
						if(temp2[i+1][0]==0||temp2[i+1][0]=='-'){
							cout<<"error: ȱ�ٲ������ļ�����ʱ��δ����"<<endl;
							flag3=1;
							break;
						}
						option2='t';
						strcpy(time,temp2[i+1]);
					}
			}//find -nѡ���ʾ�����ļ������ң�-tѡ���ʾ�����ļ�����ʱ�����
			if(flag==1||flag2==1||flag3==1)
				continue;
			find(option1,filename,option2,time,name);
		}
		else if(strcmp(temp2[0],"head")==0){
			char fpath[100];//����·��
			char num[20];
			int flag=0,flag2=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]==0){
				cout<<"error: ȱ��ѡ��"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					strcpy(num,temp2[i]+1);
					for(int j=0;j<strlen(num);j++){
						if(isdigit(num[j])==0){
							cout<<"error: ѡ�����"<<endl;
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}//head������ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				head(fpath,a,atoi(num));
			}
		}
		else if(strcmp(temp2[0],"tail")==0){
			char fpath[100];//����·��
			char num[20];
			int flag=0,flag2=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]==0){
				cout<<"error: ȱ��ѡ��"<<endl;
				continue;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					strcpy(num,temp2[i]+1);
					for(int j=0;j<strlen(num);j++){
						if(isdigit(num[j])==0){
							cout<<"error: ѡ�����"<<endl;
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}//head������ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				tail(fpath,a,atoi(num));
			}
		}
		else if(strcmp(temp2[0],"chmod")==0){
			char fpath[100];//����·��
			int flag=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�·��δ����"<<endl;
				continue;
			}
			if(temp2[2][0]==0||temp2[2][0]=='-'){
				cout<<"error: ȱ�ٲ������ļ�Ȩ��δ����"<<endl;
				continue;
			}
			else if(strcmp(temp2[2],"r")!=0&&strcmp(temp2[2],"rw")!=0){
				cout<<"error: ��������δ������ļ�Ȩ��"<<endl;
				continue;
			}
			if(temp2[3][0]!=0&&temp2[3][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//chmod����û��ѡ��
			if(flag==1)
				continue;
			else{
				strcpy(fpath,path2);
				if(temp2[1][0]!='/')
					strcat(fpath,"/");
				strcat(fpath,temp2[1]);
				chmod(fpath,temp2[2]);
			}
		}
		else if(strcmp(temp2[0],"import")==0){
			char fpath[100],fpath2[100];
			char dpath[100];
			char d[20][20];
			int flag=0,flag2=0;
			char *p3;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Դ�ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[1],".txt")==NULL){
				cout<<"error: ��������Դ�ļ�·������"<<temp2[1]<<"�����Ϸ�"<<endl;
				continue;
			}
			if(temp2[2][0]==0||temp2[2][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ���ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[2],".txt")==NULL)
				flag2=1;
			if(temp2[3][0]!=0&&temp2[3][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//import����û��ѡ��
			int j=0;
			if(flag==1)
				continue;
			else{
				strcpy(fpath,temp2[1]);
				if(strcmp(temp2[2],".")==0)
					strcpy(dpath,path2);
				else{
					strcpy(dpath,path2);
					if(temp2[2][0]!='/')
						strcat(dpath,"/");
					strcat(dpath,temp2[2]);
				}
				if(flag2==1){
					strcpy(fpath2,fpath);
					p3=strtok(fpath2,"/");
					while(p3){
						strcpy(d[j],p3);
						j++;
						p3=strtok(NULL,"/");
					}
					strcat(dpath,"/");
					strcat(dpath,d[j-1]);
				}
				else{
					strcpy(fpath2,dpath);
					p3=strtok(fpath2,"/");
					while(p3){
						strcpy(d[j],p3);
						j++;
						p3=strtok(NULL,"/");
					}
				}
				import(d[j-1],fpath,dpath,name);
			}
		}
		else if(strcmp(temp2[0],"export")==0){
			char fpath[100],spath[100];//�����ļ�·��
			char dpath[100];
			char d[20][20];
			int flag=0,f=0,flag2=0;
			char *p3;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Դ�ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[1],".txt")==NULL){
				cout<<"error: ��������Դ�ļ�·������"<<temp2[1]<<"�����Ϸ�"<<endl;
				continue;
			}
			if(temp2[2][0]==0||temp2[2][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ���ļ�·��δ����"<<endl;
				continue;
			}
			if(strstr(temp2[2],".txt")==NULL){
				flag2=1;
			}
			if(temp2[3][0]!=0&&temp2[3][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='a'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//export����-aѡ���ʾ׷��
			if(flag==1)
				continue;
			else{
				if(temp2[3][0]=='-'&&temp2[3][1]=='a')
					f=1;
				int j=0;
				strcpy(spath,path2);
				if(temp2[1][0]!='/')
					strcpy(spath,"/");
				strcat(spath,temp2[1]);
				strcpy(dpath,temp2[2]);
				if(flag2==1){
					strcpy(fpath,spath);
					p3=strtok(fpath,"/");
					while(p3){
						strcpy(d[j],p3);
						j++;
						p3=strtok(NULL,"/");
					}
					if(dpath[strlen(dpath)-1]!='/')
						strcat(dpath,"/");
					strcat(dpath,d[j-1]);
				}
				else{
					strcpy(fpath,dpath);
					p3=strtok(fpath,"/");
					while(p3){
						strcpy(d[j],p3);
						j++;
						p3=strtok(NULL,"/");
					}
				}
				Export(d[j-1],spath,dpath,f);
			}
		}
		else if(strcmp(temp2[0],"mkdir")==0){
			char dpath[100];//���·��
			int flag=0,flag2;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ¼��δ����"<<endl;
				continue;
			}
			else{
				strcpy(dpath,temp2[1]);
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='p'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//mkdir�����ѡ��ֻ��-p,��ʾ�����༶Ŀ¼
			if(flag==0){
				char d[20][20];//dpath��Ŀ¼��
				char dpath2[100];//����·��
				char dpath3[100];
				char dpath4[100];//dpath�ڷָ�ǰ�ı���
				char *p3;
				Directory dir[200];
				int l=0,flag3=0,flag4=0,DN=0;
				ReadDir(dir,DN);
				for(i=0;i<20;i++)
					memset(d[i],0,20);
				i=0;
				strcpy(dpath4,dpath);
				p3=strtok(dpath,"/");
				while(p3){
					strcpy(d[i],p3);
					i++;
					p3=strtok(NULL,"/");
				}
				for(i=0;i<20;i++)
					if(d[i][0]!=0)
						l++;//���Ŀ¼�㼶
				strcpy(dpath2,path2);
				if(dpath[0]!='/')
					strcat(dpath2,"/");
				strcat(dpath2,dpath4);
				for(int j=0;j<200;j++){
					if(strcmp(dir[j].path,dpath2)==0){
						cout<<"error: ��������Ŀ¼��"<<dpath2<<"���Ѵ���"<<endl;
						flag3=1;
						break;
					}
				}
				if(flag3==1)
					continue;
				strcpy(dpath3,"/");
				strcat(dpath3,name);
				for(i=0;i<l-1;i++){
					flag4=0;
					strcat(dpath3,"/");
					strcat(dpath3,d[i]);
					for(int j=0;j<200;j++)
						if(strcmp(dir[j].path,dpath3)==0){
							flag4=1;
							break;
						}
					if(flag4==0)
						break;
				}
				if(strcmp(temp2[2],"-p")!=0&&flag4==0&&l>=2){
					cout<<"error: ��������Ŀ¼��"<<dpath3<<"��������"<<endl;
					continue;
				}
				mkdir(dpath2,l);
			}
		}
		else if(strcmp(temp2[0],"rmdir")==0){
			char dpath[100];//����·��
			char option1,option2;
			int flag=0,f=0;
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ¼��δ����"<<endl;
				continue;
			}
			else if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			else{
				strcpy(dpath,path2);
				if(temp2[1][0]!='/')
					strcat(dpath,"/");
				strcat(dpath,temp2[1]);
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='r'&&temp2[i][1]!='f'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
				if(temp2[i][1]=='r')
					option1='r';
				if(temp2[i][1]=='f')
					option2='f';
			}//rmdir�����ѡ��-r��ʾ�Ƿ�ݹ�ɾ��,-f��ʾ�Ƿ�ǿ��ɾ��
			if(flag==0)
				rmdir(dpath,option1,option2,f);
			if(f==1)
				getchar();
		}
		else if(strcmp(temp2[0],"cd")==0){
			char dpath[100],dpath2[100];
			char *p3;
			char d[20][20];
			Directory dir[200];
			int flag=0,DN=0,flag2=0,i=0,n=0;
			strcpy(dpath2,temp2[1]);
			p3=strtok(dpath2,"/");
			while(p3){
				strcpy(d[i],p3);
				i++;
				p3=strtok(NULL,"/");
			}
			for(int j=0;j<i;j++){
				if(strcmp(d[j],"..")==0)
					n++;
				if(strcmp(d[j],"..")!=0)
					break;
			}
			ReadDir(dir,DN);
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ�����Ŀ¼��δ����"<<endl;
				continue;
			}
			else if(strstr(temp2[1],".txt")!=NULL){
				cout<<"error: ��������Ŀ¼����"<<temp2[1]<<"�����Ϸ�"<<endl;
				continue;
			}
			else if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			else{
				if(n>level-1){
					cout<<"error: ��������Ŀ¼������"<<endl;
					continue;
				}
				else{
					for(int j=0;j<level-n;j++){
						if(j==0)
							strcpy(dpath,"/");
						else
							strcat(dpath,"/");
						strcat(dpath,temp[j]);
					}
					for(int j=n;j<i;j++){
						strcat(dpath,"/");
						strcat(dpath,d[j]);
					}
					if(strcmp(dpath,path2)==0){
						cout<<"tips: ��ǰ����·����Ϊ��"<<dpath<<"��"<<endl;
						continue;
					}
				
				}
			}
			for(i=0;i<DN;i++){
				if(strcmp(dir[i].path,dpath)==0){
					flag2=1;
					break;//���Ŀ¼�Ƿ����
				}
			}
			if(flag2==0){
				cout<<"error: ��������Ŀ¼��"<<dpath<<"��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//cd����û��ѡ��
			if(flag==0){
				strcpy(path,dpath);
				strcpy(path2,path);
				p=strtok(path,"/");
				level=0;
				while(p){
					strcpy(temp[level],p);
					level++;//·������
					p=strtok(NULL,"/");
				}
			}
		}
		else if(strcmp(temp2[0],"dir")==0){
			int flag=0,f=0,flag2=0;
			char dpath[100];
			if(temp2[1][0]!=0&&temp2[1][0]!='-'){
				flag2=1;
			}
			if(temp2[2][0]!=0&&temp2[2][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='a'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
				if(temp2[1][0]=='-'&&temp2[i][1]=='a')
					f=1;
			}//dir����-aѡ���ʾ��ʾ��Ŀ¼�����е���Ŀ¼���ļ�
			if(flag==0){
				if(flag2==1){
					strcpy(dpath,path2);
					if(temp2[1][0]!='/')
						strcat(dpath,"/");
					strcat(dpath,temp2[1]);
				}
				else
					strcpy(dpath,path2);
				dir(dpath,f);
			}
				
		}
		else if(strcmp(temp2[0],"pwd")==0){
			int flag=0;
			if(temp2[1][0]!=0&&temp2[1][0]!='-'){
				cout<<"error: ��������"<<endl;
				continue;
			}
			for(i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//pwd����û��ѡ��
			if(flag==1)
				continue;
			cout<<path2<<endl;
		}
		else if(strcmp(temp2[0],"useradd")==0){
			char username[20];
			char password[7];
			int flag=0,flag2=0;//flag���ѡ���Ƿ��д���flag2��ǲ����Ƿ��д���,flag3�����ӵ��û��Ƿ����
			if(strcmp(name,"admin")!=0){
				cout<<"error: �û���"<<name<<"������Ȩ��"<<endl; //ֻ��admin�ſ��������û�
				continue;
			}
			if(temp2[1][0]==0||temp2[1][0]=='-'){
				cout<<"error: ȱ�ٲ������û���δ����"<<endl;
				continue;
			}
			else
				strcpy(username,temp2[1]);
			for(int i=0;i<20;i++){
				if(temp2[i][0]=='-'&&temp2[i][1]!='p'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//useradd�����ѡ��ֻ��-p����ʾ�Ƿ����Ĭ������
			if(flag==0){
				if(strcmp(temp2[2],"-p")==0){
					if(strlen(temp2[3])==8&&temp2[3][0]=='"'&&temp2[3][7]=='"'){
						strncpy(password,temp2[3]+1,strlen(temp2[3])-2);
						password[6]='\0';
					}
					else{
						cout<<"error: ������ʽ����"<<endl; //û�����Ż����벻��6λ
						flag2=1;
					}
				}
				else{
					if(temp2[2][0]==0)
						strcpy(password,"000000");
					else{
						cout<<"error: ��������"<<endl; //û�м�-p���� ���ǲ���������
						flag2=1;
					}
				}
				if(flag2==0)
					useradd(username,password);
			}
			
		}
		else if(strcmp(temp2[0],"userdel")==0){
			char username[20];
			int flag=0;
			if(strcmp(name,"admin")!=0){
				cout<<"error: �û���"<<name<<"������Ȩ��"<<endl; //ֻ��admin�ſ���ɾ���û�
				continue;
			}
			if(temp2[1][0]==0){
				cout<<"error: ȱ�ٲ������û���δ����"<<endl;
				continue;
			}
			else
				strcpy(username,temp2[1]);
			for(int i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//userdelû��ѡ��
			if(flag==0){
				if(temp2[2][0]!=0){
					cout<<"error: ��������"<<endl;
					continue;
				}
				else
					userdel(username);
			}

		}
		else if(strcmp(temp2[0],"password")==0){
			char username[20];
			int flag=0;
			if(temp2[1][0]==0){
				cout<<"error: ȱ�ٲ������û���δ����"<<endl;
				continue;
			}
			else{
				if(strcmp(name,"admin")!=0&&strcmp(name,temp2[1])!=0){
					cout<<"error: �û���"<<name<<"������Ȩ��"<<endl; //��ͨ�û�ֻ���޸��Լ�������
					continue;
				}
				strcpy(username,temp2[1]);
			}
			for(int i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//passwdû��ѡ��
			if(flag==0){
				if(temp2[2][0]!=0){
					cout<<"error: ��������"<<endl;
					continue;
				}
				else
					password(username);
			}
				
		}
		else if(strcmp(temp2[0],"userlist")==0){
			int flag=0;
			if(strcmp(name,"admin")!=0){
				cout<<"error: �û���"<<name<<"������Ȩ��"<<endl; //ֻ��admin���ܲ鿴�û��б�
				continue;
			}
			for(int i=0;i<20;i++){
				if(temp2[i][0]=='-'){
					cout<<"error: ѡ�����"<<endl;
					flag=1;
					break;
				}
			}//userlistû��ѡ��
			if(flag==0){
				if(temp2[1][0]!=0){
					cout<<"error: ��������"<<endl;
					continue;
				}
				else
					userlist();
			}
		}
		else if(strcmp(temp2[0],"exit")==0){
			char yesno,choice;
			int n=0,n2=0;
			for(int j=0;j<500;j++){
				if(a[j].path[0]!=0)
					n++;//���ļ��ĸ���
			}
			if(temp2[1][0]!=0){
				cout<<"error: ��������"<<endl;
				continue;
			}
			cout<<"�Ƿ�ȷ���˳�ϵͳ��(y/n)";
			cin>>yesno;
			if(yesno=='y'||yesno=='Y'){
				if(n!=0){
					cout<<"��ǰϵͳ�����ڴ򿪵��ļ�:"<<endl;
					for(int j=0;j<n;j++)
						cout<<a[j].path<<endl;
					cout<<"�Ƿ�ǿ�ƹرգ�(y/n)";
					cin>>choice;
					getchar();
					if(choice=='y'||choice=='Y')
						for(int j=0;j<n-n2;j++){
							close(a[j].path,a);
							n2++;
							j--;
						}
					else
						continue;
				}
				cout<<"ϵͳ�����˳���"<<endl;
				getch();
				exit(0);
			}
			getchar();
		}
		else if(temp2[0][0]!=0)
			cout<<"error: δ���������"<<endl;
	}
	return 0;
}