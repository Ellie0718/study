#include"stdio.h"
#include"conio.h"
#include"stdlib.h"
#include"string.h"
#define N 20
struct type
{
	float fuwu;
	float huowu;
	float gongcheng;
};
typedef struct company
{
	int no;
	char name[15];
	char manager[20];
	struct type sale;
	float total;
	float average;
}COM;
struct user
{
	char name[20];
	char password[6];
};
void input()
{
	void menu();
	COM com1[N];
	FILE *fp1;
	char yesno,yn,x,m;
	int i=0,j=0,y=0;
	if((fp1=fopen("my_dazuoye.txt","w"))==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	printf("欢迎来到信息录入页面!\n");
	printf("若不是第一次输入,请按#回到菜单");
	scanf("%c",&x);
	if(x=='#')
		menu();
	else
	{
		printf("是否为输入错误?(y/n)");
		fflush(stdin);
		scanf("%c",&yn);
		if(yn=='y'||yn=='Y')
			menu();
	}
	do
	{
		com1[i].no=i+1;
		printf("\n公司编号:%d\n",com1[i].no);
		fprintf(fp1,"%5d",com1[i].no);
		do
		{
			y=0;
			printf("公司名:");
			fflush(stdin);
			gets(com1[i].name);
			if(i!=0)
			{
				for(j=0;j<i;j++)
					if(strcmp(com1[i].name,com1[j].name)==0)
					{
						printf("\n该公司名已存在!请重输!\n");
						getch();
						y=1;
						break;
					}
			}
			else
				break;
		}while(y==1);
		fprintf(fp1,"%-15s",com1[i].name);
		printf("公司经理:");
		gets(com1[i].manager);
		fprintf(fp1,"%-20s",com1[i].manager);
		printf("服务类产品销售额:");
		do
		{
			fflush(stdin);
			scanf("%f",&com1[i].sale.fuwu);
			m=getchar();
			if(m=='\n')
				fprintf(fp1,"%15f",(com1[i].sale).fuwu);
			else
			{
				printf("您输入的包含字符!请重新输入!\n");
				printf("服务类产品销售额:");
			}
		}while(m!='\n');
		printf("货物类产品销售额:");
		do
		{
			fflush(stdin);
			scanf("%f",&com1[i].sale.huowu);
			m=getchar();
			if(m=='\n')
				fprintf(fp1,"%15f",(com1[i].sale).huowu);
			else
			{
				printf("您输入的包含字符!请重新输入!\n");
				printf("货物类产品销售额:");
			}
		}while(m!='\n');
		printf("工程类产品销售额:");
		do
		{
			fflush(stdin);
			scanf("%f",&com1[i].sale.gongcheng);
			m=getchar();
			if(m=='\n')
				fprintf(fp1,"%15f",(com1[i].sale).gongcheng);
			else
			{
				printf("您输入的包含字符!请重新输入!\n");
				printf("工程类产品销售额:");
			}
		}while(m!='\n');
		printf("\nContinue?(y/n)");
		fflush(stdin);
		scanf("%c",&yesno);
		if(yesno=='y'||yesno=='Y')
			fputc('\n',fp1);
		i++;
	}while((yesno=='y'||yesno=='Y')&&i<N);
	fclose(fp1);
	printf("\n录入信息成功!\n");
	getch();	
}
void display()
{
	COM com2[N];
	FILE *fp2;
	int i=0,x=0;
	if((fp2=fopen("my_dazuoye.txt","r"))==NULL)
	{
		printf("文件打开错误!请先录入信息!\n\n");
		x=1;
		getch();
	}
	if(x==0)
	{
		fscanf(fp2,"%5d",&com2[0].no);
		while(!feof(fp2))
		{
			fscanf(fp2,"%5d",&com2[i].no);
			fgets(com2[i].name,15,fp2);
			fgets(com2[i].manager,20,fp2);
			fscanf(fp2,"%15f",&(com2[i].sale).fuwu);
			fscanf(fp2,"%15f",&(com2[i].sale).huowu);
			fscanf(fp2,"%15f",&(com2[i].sale).gongcheng);
			printf("公司编号:%d\n",com2[i].no);
			printf("公司名:");
			puts(com2[i].name);
			printf("公司经理:");
			puts(com2[i].manager);
			printf("服务类产品销售额:%f\n",(com2[i].sale).fuwu);
			printf("货物类产品销售额:%f\n",(com2[i].sale).huowu);
			printf("工程类产品销售额:%f\n\n\n",(com2[i].sale).gongcheng);
			i++;
		}
		if(i==0)
		{
			printf("信息不存在!");
			getch();
		}
		fclose(fp2);
		if(i!=0)
			printf("显示信息成功!\n");
		getch();
	}
}
void seek()
{
	COM com3[N];
	FILE *fp3;
    char a[15];
	int i=0,n=0,x=0;
	if((fp3=fopen("my_dazuoye.txt","r"))==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}	
	printf("\n请输入要查找的公司的名称:");
	gets(a);
	n=strlen(a);
	for(i=n;i<14;i++)
		a[i]=' ';
	a[i]='\0';
	while((!feof(fp3)))
	{
		fscanf(fp3,"%d",&com3[i].no);
		fgets(com3[i].name,15,fp3);
		fgets(com3[i].manager,20,fp3);
		fscanf(fp3,"%15f",&(com3[i].sale).fuwu);
		fscanf(fp3,"%15f",&(com3[i].sale).huowu);
		fscanf(fp3,"%15f",&(com3[i].sale).gongcheng);
		if(strcmp(com3[i].name,a)==0)
		{
			n=i;
			x=1;
			break;
		}
	}
	if(x==1)
	{
	printf("\n公司编号:%d\n",com3[n].no);
	printf("公司名:");
	puts(com3[n].name);
	printf("公司经理:");
	puts(com3[n].manager);
	printf("服务类产品销售额:%f\n",com3[n].sale.fuwu);
	printf("货物类产品销售额:%f\n",com3[n].sale.huowu);
	printf("工程类产品销售额:%f\n",com3[n].sale.gongcheng);
	fclose(fp3);
	printf("查询信息成功!");
    getch();
	}
	else
		{
			printf("\n该公司不存在!!!");
			getch();
			fclose(fp3);
		}
}
void edit()
{
	void menu();
	COM com4[N];
	FILE *fp4;
	char yesno;
	char a[15],name[15],m1;
	int i,j,m,n=0,n1=0,n2=0,n3=0,x=0,y=0;
	fp4=fopen("my_dazuoye.txt","r");
	if(fp4==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	printf("\n请输入要修改的公司的名称:");
	gets(a);
	n1=strlen(a);
	for(i=n1;i<14;i++)
		a[i]=' ';
	a[i]='\0';
	i=0;
	while(!feof(fp4))
	{
		fscanf(fp4,"%5d",&com4[i].no);
		fgets(com4[i].name,15,fp4);
		fgets(com4[i].manager,20,fp4);
		fscanf(fp4,"%15f",&(com4[i].sale).fuwu);
		fscanf(fp4,"%15f",&(com4[i].sale).huowu);
		fscanf(fp4,"%15f",&(com4[i].sale).gongcheng);
		if(strcmp(com4[i].name,a)==0)
		{
			n=i;
			x=1;
		}
		i++;
	}
	n3=i;
	fclose(fp4);
	if(x==1)
	{
		printf("\n公司编号:%d\n",com4[n].no);
		printf("公司名:");
		puts(com4[n].name);
		printf("公司经理:");
		puts(com4[n].manager);
		printf("服务类产品销售额:%f\n",com4[n].sale.fuwu);
		printf("货物类产品销售额:%f\n",com4[n].sale.huowu);
		printf("工程类产品销售额:%f\n\n",com4[n].sale.gongcheng);
		printf("-------------------\n");
		printf("1.公司名\n");
		printf("2.公司经理\n");
		printf("3.服务类产品销售额\n");
		printf("4.货物类产品销售额\n");
		printf("5.工程类产品销售额\n");
		printf("-------------------\n");
		printf("请选择修改信息类型:");
		scanf("%d",&m);
		printf("请输入:");
		if(m==1)
		{
			do
			{
				y=0;
				fflush(stdin);
				gets(name);
				n2=strlen(name);
				for(i=n2;i<14;i++)
					name[i]=' ';
				name[i]='\0';
				for(j=0;j<n3;j++)
					if(strcmp(name,com4[j].name)==0)
					{
						printf("\n该公司名已存在!请重输!\n");
						printf("公司名:");
						y=1;
						break;
					}
			}while(y==1);
			strcpy(com4[n].name,name);
		}
		else if(m==2)
		{
			fflush(stdin);
			gets(com4[n].manager);
		}
		else if(m==3)
			do
			{
				fflush(stdin);
				scanf("%f",&com4[n].sale.fuwu);
				m1=getchar();
				if(m1=='\n')
					fprintf(fp4,"%15f",(com4[n].sale).fuwu);
				else
				{
					printf("您输入的包含字符!请重新输入!\n");
					printf("服务类产品销售额:");
				}
			}while(m1!='\n');
		else if(m==4)
			do
			{
				fflush(stdin);
				scanf("%f",&com4[n].sale.huowu);
				m1=getchar();
				if(m1=='\n')
					fprintf(fp4,"%15f",(com4[n].sale).huowu);
				else
				{
					printf("您输入的包含字符!请重新输入!\n");
					printf("货物类产品销售额:");
				}
			}while(m1!='\n');
		else if(m==5)
			do
			{
				fflush(stdin);
				scanf("%f",&com4[n].sale.gongcheng);
				m1=getchar();
				if(m1=='\n')
					fprintf(fp4,"%15f",(com4[n].sale).gongcheng);
				else
				{
					printf("您输入的包含字符!请重新输入!\n");
					printf("工程类产品销售额:");
				}
			}while(m1!='\n');
		else
		{
			printf("\n输入错误!!!");
			getch();
			menu();
		}
		printf("确定要修改吗?(y/n)");
		fflush(stdin);
		scanf("%c",&yesno);
		while(yesno=='y'||yesno=='Y')
		{
			fp4=fopen("my_dazuoye.txt","w");
			if(fp4==NULL)
			{
				printf("文件打开错误!");
				getch();
				exit(0);
			}
			for(j=0;j<n3;j++)
			{
				fprintf(fp4,"%5d",com4[j].no);
				fprintf(fp4,"%-15s",com4[j].name);
				fprintf(fp4,"%-20s",com4[j].manager);
				fprintf(fp4,"%15f",(com4[j].sale).fuwu);
				fprintf(fp4,"%15f",(com4[j].sale).huowu);
				fprintf(fp4,"%15f",(com4[j].sale).gongcheng);
				if(j<n3-1)
					fputc('\n',fp4);
			}
			fclose(fp4);
			printf("修改信息成功!");
			getch();
			break;
		}
	}
	else
	{
		printf("\n该公司不存在!!!");
		getch();
		fclose(fp4);
	}
}
void append()
{
	void menu();
	COM com5[N];
	FILE *fp5;
	char yesno,yn;
	int i=0,n=0,n2=0,y=0,j=0;
	char name[15],m;
	fp5=fopen("my_dazuoye.txt","a+");
	if(fp5==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	printf("确认要添加吗?(y/n)");
	fflush(stdin);
	scanf("%c",&yn);
	if(yn=='y'||yn=='Y')
	{
		while(!feof(fp5))
		{
			fscanf(fp5,"%5d",&com5[i].no);
			fgets(com5[i].name,15,fp5);
			fgets(com5[i].manager,20,fp5);
			fscanf(fp5,"%15f",&(com5[i].sale).fuwu);
			fscanf(fp5,"%15f",&(com5[i].sale).huowu);
			fscanf(fp5,"%15f",&(com5[i].sale).gongcheng);
			i++;
			n++;
		}
		if(fscanf(fp5,"%5d",&com5[0].name)!=0)
		{
			printf("现已录入%d个公司的信息!\n",n);
			if(n==20)
			{
				printf("录入已完成,不可再录入!\n");
				getch();
				printf("按任意键返回菜单");
				getch();
				menu();
			}
			do
			{
				com5[n].no=com5[n-1].no+1;
				printf("公司编号:%d\n",com5[n].no);
				fputc('\n',fp5);
				fprintf(fp5,"%5d",com5[n].no);
				do
				{
					y=0;
					printf("公司名:");
					fflush(stdin);
					gets(name);
					n2=strlen(name);
					for(i=n2;i<14;i++)
						name[i]=' ';
					name[i]='\0';
					for(j=0;j<n;j++)
						if(strcmp(name,com5[j].name)==0)
						{
							printf("\n该公司名已存在!请重输!\n\n");
							getch();
							y=1;
							break;
						}
				}while(y==1);
				strcpy(com5[n].name,name);
				fprintf(fp5,"%-15s",com5[n].name);
				printf("公司经理:");
				gets(com5[n].manager);
				fprintf(fp5,"%-20s",com5[n].manager);
				printf("服务类产品销售额:");
				do
				{
					fflush(stdin);
					scanf("%f",&com5[n].sale.fuwu);
					m=getchar();
					if(m=='\n')
						fprintf(fp5,"%15f",(com5[n].sale).fuwu);
					else
					{
						printf("您输入的包含字符!请重新输入!\n");
						printf("服务类产品销售额:");
					}
				}while(m!='\n');
				printf("货物类产品销售额:");
				do
				{
					fflush(stdin);
					scanf("%f",&com5[n].sale.huowu);
					m=getchar();
					if(m=='\n')
						fprintf(fp5,"%15f",(com5[n].sale).huowu);
					else
					{
						printf("您输入的包含字符!请重新输入!\n");
						printf("货物类产品销售额:");
					}
				}while(m!='\n');
				printf("工程类产品销售额:");
				do
				{
					fflush(stdin);
					scanf("%f",&com5[n].sale.gongcheng);
					m=getchar();
					if(m=='\n')
						fprintf(fp5,"%15f",(com5[n].sale).gongcheng);
					else
					{
						printf("您输入的包含字符!请重新输入!\n");
						printf("工程类产品销售额:");
					}
				}while(m!='\n');
				printf("Continue?(y/n)");
				fflush(stdin);
				scanf("%c",&yesno);
				if(yesno=='y'||yesno=='Y')
					fputc('\n',fp5);
			}while(yesno=='y'||yesno=='Y');
			fclose(fp5);
			printf("添加信息成功!");
			getch();
		}
		else
		{
			printf("信息不存在!请先完成录入信息!");
			getch();
		}
	}
}
void shanchu()
{
	COM com6[N];
	FILE *fp6;
	char yesno;
	char a[15];
	int i,j,n=0,n1=0,x=0;
	fp6=fopen("my_dazuoye.txt","r");
	if(fp6==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	printf("\n请输入要删除的公司的名称:");
	gets(a);
	n1=strlen(a);
	for(i=n1;i<14;i++)
		a[i]=' ';
	a[i]='\0';
	i=0;
	while(!feof(fp6))
	{
		fscanf(fp6,"%5d",&com6[i].no);
		fgets(com6[i].name,15,fp6);
		fgets(com6[i].manager,20,fp6);
		fscanf(fp6,"%15f",&(com6[i].sale).fuwu);
		fscanf(fp6,"%15f",&(com6[i].sale).huowu);
		fscanf(fp6,"%15f",&(com6[i].sale).gongcheng);
		if(strcmp(com6[i].name,a)==0)
		{
			n=i;
			x=1;
		}
		i++;
	}
	fclose(fp6);
	if(x==1)
	{
		printf("\n公司编号:%d\n",com6[n].no);
		printf("公司名:");
		puts(com6[n].name);
		printf("公司经理:");
		puts(com6[n].manager);
		printf("服务类产品销售额:%f\n",com6[n].sale.fuwu);
		printf("货物类产品销售额:%f\n",com6[n].sale.huowu);
		printf("工程类产品销售额:%f\n\n",com6[n].sale.gongcheng);
		printf("确认要删除吗?(y/n)");
		scanf("%c",&yesno);
		while(yesno=='y'||yesno=='Y')
		{
			for(j=n;j<i;j++)
				com6[j]=com6[j+1];
			break;
		}
		fp6=fopen("my_dazuoye.txt","w");
		if(fp6==NULL)
		{
			printf("文件打开错误!");
			getch();
			exit(0);
		}
		for(j=0;j<i-1;j++)
		{
			fprintf(fp6,"%5d",com6[j].no);
			fprintf(fp6,"%-15s",com6[j].name);
			fprintf(fp6,"%-20s",com6[j].manager);
			fprintf(fp6,"%15f",(com6[j].sale).fuwu);
			fprintf(fp6,"%15f",(com6[j].sale).huowu);
			fprintf(fp6,"%15f",(com6[j].sale).gongcheng);
			if(j<i-2)
				fputc('\n',fp6);
		}
		fclose(fp6);
		printf("删除信息成功!");
		getch();
	}
	else
	{
		printf("\n该公司不存在!!!");
		getch();
		fclose(fp6);
	}
}
void total()
{
    COM com[N];
	FILE *fp;
	char a[15];
	float total;
	int i,j,n=0,n1=0,x=0;
	fp=fopen("my_dazuoye.txt","r");
	if(fp==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	printf("\n请输入要查询的公司的名称:");
	gets(a);
	n1=strlen(a);
	for(i=n1;i<14;i++)
		a[i]=' ';
	a[i]='\0';
	i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%5d",&com[i].no);
		fgets(com[i].name,15,fp);
		fgets(com[i].manager,20,fp);
		fscanf(fp,"%15f",&(com[i].sale).fuwu);
		fscanf(fp,"%15f",&(com[i].sale).huowu);
		fscanf(fp,"%15f",&(com[i].sale).gongcheng);
		if(strcmp(com[i].name,a)==0)
		{
			n=i;
			x=1;
		}
		i++;
	}
	if(x==1)
	{
		total=com[n].sale.fuwu+com[n].sale.huowu+com[n].sale.gongcheng;
		printf("\n该公司三类产品(服务类、货物类、工程类)累计年销售总额为:%f",total);
		getch();
	}
	else
	{
		printf("\n该公司不存在!!!");
		getch();
	}
	fclose(fp);
}
void sort1()
{
	COM com[N];
	FILE *fp;
	char s[100];
	int i=0,j=0,n=0;
	float t;
	fp=fopen("my_dazuoye.txt","r");
	if(fp==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%5d",&com[i].no);
		fgets(com[i].name,15,fp);
		fgets(com[i].manager,20,fp);
		fscanf(fp,"%15f",&(com[i].sale).fuwu);
		fscanf(fp,"%15f",&(com[i].sale).huowu);
		fscanf(fp,"%15f",&(com[i].sale).gongcheng);
		com[i].total=com[i].sale.fuwu+com[i].sale.huowu+com[i].sale.gongcheng;
		i++;
		n++;
	}
	for(i=0;i<N-1;i++)
		for(j=0;j<N-i;j++)
			if(com[j].total<com[j+1].total)
			{
				t=com[j].total;
				strcpy(s,com[j].name);
				com[j].total=com[j+1].total;
				strcpy(com[j].name,com[j+1].name);
				com[j+1].total=t;
				strcpy(com[j+1].name,s);
			}
	printf("\n所有分公司的年销售总额由大到小排序为:\n\n");
	for(i=0;i<n;i++)
	{
		printf("第%d名\n",i+1);
		printf("======\n");
		printf("公司名:");
		puts(com[i].name);
		printf("年销售总额:");
		printf("%f\n\n",com[i].total);
	}
	fclose(fp);
	getch();
}
void ranking()
{
	COM com[N];
	FILE *fp;
	char yesno;
	char a[15],s[15];
	float t;
	int i,j,k,m,n=0,n1=0,x=0;
	fp=fopen("my_dazuoye.txt","r");
	if(fp==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	printf("\n请输入要查询的公司的名称:");
	gets(a);
	n1=strlen(a);
	for(i=n1;i<14;i++)
		a[i]=' ';
	a[i]='\0';
	i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%5d",&com[i].no);
		fgets(com[i].name,15,fp);
		fgets(com[i].manager,20,fp);
		fscanf(fp,"%15f",&(com[i].sale).fuwu);
		fscanf(fp,"%15f",&(com[i].sale).huowu);
		fscanf(fp,"%15f",&(com[i].sale).gongcheng);
		com[i].total=com[i].sale.fuwu+com[i].sale.huowu+com[i].sale.gongcheng;
		i++;
	}
	for(j=0;j<N-1;j++)
		for(k=0;k<N-i;k++)
			if(com[k].total<com[k+1].total)
			{
				t=com[k].total;
				strcpy(s,com[k].name);
				com[k].total=com[k+1].total;
				strcpy(com[k].name,com[k+1].name);
				com[k+1].total=t;
				strcpy(com[k+1].name,s);
			}
	for(j=0;j<N-1;j++)
		if(strcmp(com[j].name,a)==0)
		{
			n=j;
			x=1;
		}
	if(x==1)
	{
		printf("\n该公司在年度销售总额中的名次为:%d",n+1);
		getch();
	}
	else
	{
		printf("\n该公司不存在!!!");
		getch();
	}
	fclose(fp);
}
void average()
{
	COM com[N];
	FILE *fp;
	int i=0,n=0;
	float a=0,kind_average=0;
	char b[20],c[20],d[20],type_name[20];
	fp=fopen("my_dazuoye.txt","r");
	if(fp==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	while((!feof(fp))&&i<N)
	{
		fscanf(fp,"%5d",&com[i].no);
		fgets(com[i].name,15,fp);
		fgets(com[i].manager,20,fp);
		fscanf(fp,"%15f",&(com[i].sale).fuwu);
		fscanf(fp,"%15f",&(com[i].sale).huowu);
		fscanf(fp,"%15f",&(com[i].sale).gongcheng);
		i++;
		n++;
	}
	strcpy(b,"fuwu\0");
	strcpy(c,"huowu\0");
	strcpy(d,"gongcheng\0");
	printf("-------------------\n");
	printf("1.服务类(fuwu)\n");
	printf("2.货物类(huowu)\n");
	printf("3.工程类(gongcheng)\n");
	printf("-------------------\n");
	printf("请输入类别名称:");
	gets(type_name);
	if(strcmp(type_name,b)==0)
	{
		for(i=0;i<n;i++)
			a=a+com[i].sale.fuwu;
		kind_average=a/n;
		printf("\n所有分公司的服务类产品的平均销售额为:%f",kind_average);
		getch();
	}
	else if(strcmp(type_name,c)==0)
	{
		for(i=0;i<n;i++)
			a=a+com[i].sale.huowu;
		kind_average=a/n;
		printf("\n所有分公司的货物类产品的平均销售额为:%f",kind_average);
		getch();
	}
	else if(strcmp(type_name,d)==0)
	{
		for(i=0;i<n;i++)
			a=a+com[i].sale.gongcheng;
		kind_average=a/n;
		printf("\n所有分公司的工程类产品的平均销售额为%f",kind_average);
		getch();
	}
	else
	{
		printf("\n输入错误!!!");
		getch();
	}
	fclose(fp);
}
void sort2()
{
	COM com[N];
	FILE *fp;
	int i=0,j=0,n=0,k,m;
	char s[15];
	float t;
	fp=fopen("my_dazuoye.txt","r");
	if(fp==NULL)
	{
		printf("文件打开错误!");
		getch();
		exit(0);
	}
	while((!feof(fp))&&i<N)
	{
		fscanf(fp,"%5d",&com[i].no);
		fgets(com[i].name,15,fp);
		fgets(com[i].manager,20,fp);
		fscanf(fp,"%15f",&(com[i].sale).fuwu);
		fscanf(fp,"%15f",&(com[i].sale).huowu);
		fscanf(fp,"%15f",&(com[i].sale).gongcheng);
		i++;
		n++;
	}
	printf("-----------\n");
	printf("1.服务类\n");
	printf("2.货物类\n");
	printf("3.工程类\n");
	printf("-----------\n");
	printf("请选择类别:");
	scanf("%d",&k);
	if(k==1)
	{
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				if(com[j].sale.fuwu<com[j+1].sale.fuwu)
				{
					t=com[j].sale.fuwu;
					strcpy(s,com[j].name);
					com[j].sale.fuwu=com[j+1].sale.fuwu;
					strcpy(com[j].name,com[j+1].name);
					com[j+1].sale.fuwu=t;
					strcpy(com[j+1].name,s);
				}
		printf("\n所有分公司服务类产品年度销售额由大到小排序:\n\n");
		for(i=0;i<n;i++)
	   {
			printf("第%d名\n",i+1);
			printf("======\n");
			printf("公司名:");
			puts(com[i].name);
			printf("服务类产品年销售额:");
			printf("%f\n\n",com[i].sale.fuwu);
		}
		getch();
	}
	else if(k==2)
	{
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				if(com[j].sale.huowu<com[j+1].sale.huowu)
				{
					t=com[j].sale.huowu;
					strcpy(s,com[j].name);
					com[j].sale.huowu=com[j+1].sale.huowu;
					strcpy(com[j].name,com[j+1].name);
					com[j+1].sale.huowu=t;
					strcpy(com[j+1].name,s);
				}
		for(i=0;i<n;i++)
	   {
			printf("第%d名\n",i+1);
			printf("======\n");
			printf("公司名:");
			puts(com[i].name);
			printf("货物类产品年销售额:");
			printf("%f\n\n",com[i].sale.huowu);
	   }
		getch();
	}
	else if(k==3)
	{
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				if(com[j].sale.gongcheng<com[j+1].sale.gongcheng)
				{
					t=com[j].sale.gongcheng;
					strcpy(s,com[j].name);
					com[j].sale.gongcheng=com[j+1].sale.gongcheng;
					strcpy(com[j].name,com[j+1].name);
					com[j+1].sale.gongcheng=t;
					strcpy(com[j+1].name,s);
				}
		for(i=0;i<n;i++)
	   {
			printf("第%d名\n",i+1);
			printf("======\n");
			printf("公司名:");
			puts(com[i].name);
			printf("工程类产品年销售额:");
			printf("%f\n\n",com[i].sale.gongcheng);
	   }
		getch();
	}
	else
	{
		printf("\n输入错误!!!");
		getch();
	}
	fclose(fp);
}
void tuichu()
{
	char yesno;
	void menu();
	printf("\n您确定要退出吗?(y/n)");
	scanf("%c",&yesno);
	while(yesno=='n'||yesno=='N')
	{
		menu();
		fflush(stdin);
		scanf("%c",&yesno);
	}
	exit(0);
}
void menu()
{
	int choice,n=0;
	char m;
	do
	{
		system("cls");
		printf("==========欢迎使用销售业绩管理系统!==========\n");
		printf("录入信息------------------------------------1\n");
		printf("显示信息------------------------------------2\n");
		printf("查询信息------------------------------------3\n");
		printf("修改信息------------------------------------4\n");
		printf("添加信息------------------------------------5\n");
		printf("删除信息------------------------------------6\n");
		printf("求某个分公司三类产品累计年销售总额----------7\n");
		printf("求所有分公司的年销售总额并排序--------------8\n");
		printf("求某个分公司的年度销售总额的名次------------9\n");
		printf("求所有分公司的某类产品的平均销售额----------10\n");
		printf("对所有分公司的某类产品年度销售额排序--------11\n");
		printf("退出----------------------------------------0\n");
		printf("=============================================\n");
		printf("请输入您的选择(若首次进入，请先选择1):");
		fflush(stdin);
		n=scanf("%d",&choice);
		m=getchar();
		if(n==1&&m=='\n')
		{
			if(choice>=0&&choice<12)
				switch(choice)
				{
					case 1:input();break;
					case 2:display();break;
					case 3:seek();break;
					case 4:edit();break;
					case 5:append();break;
					case 6:shanchu();break;
					case 7:total();break;
					case 8:sort1();break;
					case 9:ranking();break;
					case 10:average();break;
					case 11:sort2();break;
					case 0:tuichu();break;
					default:printf("请重输！");getch();break;
				}
			else
			{
				printf("您输入的数不在范围内，请重新输入\n");
				getch();
			}
		}
		else
		{
			printf("您的输入包含字母等非法字符，请重新输入\n");
			getch();
		}
	}while(choice!=0);
}
void create()
{
	void denglu();
	FILE *fp;
	struct user a[10];
	char password1[7];
	int i,x=0;
	printf("\n\n======欢迎来到注册界面======\n\n");
	fp=fopen("users.txt","r");
	if(fp==NULL)
	{
		printf("暂无任何注册信息!\n");
		getch();
	}
	else
	{
		printf("账户已存在!请勿重复注册!");
		denglu();
	}
	fp=fopen("users.txt","w");
	printf("请输入用户名:");
	gets(a[0].name);
	printf("请输入六位密码:");
	for(i=0;i<6;i++)
	{
		fflush(stdin);
		a[0].password[i]=getch();
		printf("*");
	}
	a[0].password[6]='\0';
	printf("\n请再次输入六位密码:");
	for(i=0;i<6;i++)
	{
		fflush(stdin);
		password1[i]=getch();
		printf("*");
	}
	password1[6]='\0';
	if(strcmp(a[0].password,password1)==0)
	{
		fprintf(fp,"%-20s",a[0].name);
		fprintf(fp,"%-7s",a[0].password);
		fclose(fp);
		printf("\n注册成功!");
		getch();
	}
	else
	{
		printf("\n两次密码不一致!");
		getch();
		fclose(fp);
		remove("users.txt");
	}
}
void denglu()
{
	void menu();
	FILE *fp;
	struct user a[10];
	char password1[7],name[20];
	int i=0,n,x=0;
	printf("\n\n======欢迎来到登录界面======\n\n");
	fp=fopen("users.txt","r");
	if(fp==NULL)
	{
		printf("用户不存在，请先完成注册!\n");
		x=1;
		getch();
	}
	if(x==0)
	{
		printf("\n请输入用户名:");
		gets(name);
		n=strlen(name);
		for(i=n;i<19;i++)
			name[i]=' ';
		name[i]='\0';
		printf("请输入六位密码:");
		for(i=0;i<6;i++)
		{
			fflush(stdin);
			password1[i]=getch();
			printf("*");
		}
		password1[6]='\0';
		i=0;
		while(!feof(fp))
		{
			fgets(a[i].name,21,fp);
			a[i].name[19]='\0';
			fgets(a[i].password,7,fp);
			if((strcmp(a[i].name,name)==0)&&(strcmp(a[i].password,password1)==0))
			{
				fclose(fp);
				printf("\n登录成功!!!");
				getch();
				menu();
			}
			else
			{
				fclose(fp);
				printf("\n登录失败!!!\n");
				getch();
				break;
			}
			i++;
		}
	}
}
void main()
{
	int ch,n=0;
	char m;
	do
	{
		system("cls");
		printf("======用户注册登录界面======\n");
		printf("         1.注册账号\n");
		printf("         2.登录账号\n");
		printf("         0.退出\n");
		printf("============================\n");
		printf("请选择:");
		fflush(stdin);
		n=scanf("%d",&ch);
		m=getchar();
		if(n==1&&m=='\n')
		{
			if(ch>=0&&ch<4)
				switch(ch)
				{
				case 1:create();break;
				case 2:denglu();break;
				case 0:tuichu();break;
				}
			else
			{
				printf("您输入的数不在范围内，请重新输入\n");
				getch();
			}
		}
		else
		{
			printf("您的输入包含字母等非法字符，请重新输入\n");
			getch();
		}
	}while(ch!=0);
}