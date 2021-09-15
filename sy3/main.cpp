#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<stdio.h>
#include<algorithm>
#define OK 1
#define ERROR 0
using namespace std;
struct used_table{
 int address;       //已分分区起始地址
 int length;        //已分分区长度，单位为KB
 int flag;            //已分配表区登记栏标志，用0表示空栏目，
};          //已分配区表
struct free_table{
 int address;       //空闲区起始地址
 int length;        //空闲区长度，单位为KB
 int flag;            //空闲区表登记栏目用0表示空栏目，1表示未分配
};          //空闲区表
struct JCB{
    int No;//作业号
    int MemorySize;//内存大小，不超过L
    int Flag;//0表示没有分配到内存，1表示已分配到内存，2表示作业已经结束，内存已回收
};
bool compare(free_table f1,free_table f2){
	return f1.length>f2.length;
}
bool compare2(free_table f1,free_table f2){
	return f1.address<f2.address;
}
void PrintUT(used_table UT[]){
	cout<<endl<<"-----------已分配表-----------"<<endl;
	printf("起始地址   长度(KB)   标志\n");
	for(int j=0;j<10;j++){
		if(UT[j].address!=-1)
			printf("%-12d%",UT[j].address);
		else
			printf("%-12s","空");
		if(UT[j].length!=-1)
			printf("%-10d",UT[j].length);
		else
			printf("%-10s","空");
		if(UT[j].flag==0)
			cout<<"空"<<endl;
		else
			cout<<"作业"<<UT[j].flag<<endl;
	}
}
void PrintFT(free_table FT[],int M){
	cout<<endl<<"------------空闲表------------"<<endl;
	printf("起始地址   长度(KB)   标志\n");
	for(int j=0;j<M;j++){
		printf("%-12d%-10d",FT[j].address,FT[j].length);
		if(FT[j].flag==0)
			cout<<"空"<<endl;
		else
			cout<<"未分配"<<endl;
	}
}
int main()
{
    int N=0,x=0,M=10,choice=0,flag=0,X=0,locate=0;//N为已分配空间的作业数，M为空闲区的个数，X为分配的轮数
    free_table FT[11];
    used_table UT[10];
    JCB jcb[10];
    srand((unsigned)time(NULL));
    /*初始化空闲区表*/
    for(int i=0;i<10;i++){
        FT[i].flag=1;
		if(i<9)
			FT[i].length=pow(double(2),i+1);
		else
			FT[i].length=2;
        if(i==0)
            FT[i].address=0;
        else
            FT[i].address=FT[i-1].address+FT[i-1].length;
    }
    /*初始化已分配区表*/
	for(int i=0;i<10;i++){
		UT[i].address=-1;
		UT[i].flag=0;
		UT[i].length=-1;
	}
    /*建立作业队列（10个）*/
    for(int i=0;i<10;i++){
        jcb[i].No=i+1;
        jcb[i].MemorySize=rand()%1024+1;//每个作业内存需求不超过1M
        jcb[i].Flag=0;
    }
	while(flag==0){
		cout<<"1.首次适应法"<<endl;
		cout<<"2.循环首次适应法"<<endl;
		cout<<"3.最坏适应法"<<endl;
		cout<<"请选择一种内存分配算法：";
		cin>>choice;
		if(choice==1||choice==2||choice==3)
			flag=1;
		else{
			cout<<"输入错误：请重新输入！"<<endl;
			cin.get();
			cin.get();
			system("cls");
		}
	}
    while(N<10){
		int i=0,f=0,k=0,y=0;
		X++;
		for(i=0;i<10;i++){
			if(jcb[i].Flag==0){
				if(choice==1){//最先适应算法分配内存空间
					for(int m=0;m<M;m++){
						if(FT[m].length>=jcb[i].MemorySize){
							for(int j=0;j<10;j++){
								if(UT[j].flag==0){
									UT[j].address=FT[m].address;
									UT[j].length=jcb[i].MemorySize;
									UT[j].flag=jcb[i].No;//标志位改为已分配内存空间的作业号
									if(FT[m].length>jcb[i].MemorySize){
										FT[m].address+=jcb[i].MemorySize;
										FT[m].length-=jcb[i].MemorySize;
									}
									else{
										FT[m].length=0;
										FT[m].flag=0;//空闲区标志位设为“空”
										for(k=m;k<M;k++)
											FT[m]=FT[m+1];
										M--;
									}
									jcb[i].Flag=1;//已为作业分配内存空间
									N++;
									break;
								}
							}
							PrintUT(UT);
							PrintFT(FT,M);
							if(jcb[i].Flag==1)
								break;
						}
					}
				}
				else if(choice==2){//循环首次适应算法分配内存空间
					int num=0;
					for(int m=locate;num<M;m++,num++){
						if(m==M)
							m=0;
						if(FT[m].length>=jcb[i].MemorySize){
							locate=m;
							for(int j=0;j<10;j++){
								if(UT[j].flag==0){
									UT[j].address=FT[m].address;
									UT[j].length=jcb[i].MemorySize;
									UT[j].flag=jcb[i].No;//标志位改为已分配内存空间的作业号
									if(FT[m].length>jcb[i].MemorySize){
										FT[m].address+=jcb[i].MemorySize;
										FT[m].length-=jcb[i].MemorySize;
									}
									else{
										FT[m].length=0;
										FT[m].flag=0;//空闲区标志位设为“空”
										for(k=m;k<M;k++)
											FT[m]=FT[m+1];
										M--;
										locate--;
									}
									PrintUT(UT);
									PrintFT(FT,M);
									jcb[i].Flag=1;//已为作业分配内存空间
									N++;
									break;
								}
							}
							if(jcb[i].Flag==1)
								break;
						}
					}
				}
				else {//最坏适应算法分配内存空间
					sort(FT,FT+M,compare);
					for(int m=0;m<M;m++){
						if(FT[m].length>=jcb[i].MemorySize){
							for(int j=0;j<10;j++){
								if(UT[j].flag==0){
									UT[j].address=FT[m].address;
									UT[j].length=jcb[i].MemorySize;
									UT[j].flag=jcb[i].No;//标志位改为已分配内存空间的作业号
									if(FT[m].length>jcb[i].MemorySize){
										FT[m].address+=jcb[i].MemorySize;
										FT[m].length-=jcb[i].MemorySize;
									}
									else{
										FT[m].length=0;
										FT[m].flag=0;//空闲区标志位设为“空”
										for(k=m;k<M;k++)
											FT[m]=FT[m+1];
										M--;
									}
									PrintUT(UT);
									PrintFT(FT,M);
									jcb[i].Flag=1;//已为作业分配内存空间
									N++;
									break;
								}
							}
							if(jcb[i].Flag==1)
								break;
						}
					}
					sort(FT,FT+M,compare);
				}
				if(jcb[i].Flag==0){//没有足够空间分配
					cout<<endl<<"作业"<<jcb[i].No<<"等待"<<endl;
					cout<<"长度："<<jcb[i].MemorySize<<"KB"<<endl;
					y=1;
				}
			}
		}
		if(X==1){
			k=0;
			while(k<M-1){
				for(int u=0;u<M;u++)
					if(FT[k].address+FT[k].length==FT[u].address){
						FT[k].length+=FT[u].length;
						for(int p=u;p<M;p++)
							FT[p]=FT[p+1];
						M--;
						if(FT[locate].address>FT[u].address)
							locate--;
						u=0;
					}//有下邻空闲区
				k++;
			}
			locate++;
		}
		for(int j=0;j<10;j++){//查找已分配表
			if(UT[j].flag!=0){
				x=rand()%2;//产生一个随机数（0或1），如果为1，则把分配到的内存进行回收
				if(x==1){
					for(k=0;k<10;k++)
						if(jcb[k].No==UT[j].flag){
							jcb[k].Flag=2;
							break;
						}
					cout<<endl<<"-----------回收空间-----------"<<endl;
					printf("作业       起始地址   长度(KB)\n");
					printf("%-11d%-11d%-10d\n",UT[j].flag,UT[j].address,UT[j].length);
					sort(FT,FT+M,compare2);
					for(k=0;k<M;k++){
						if(UT[j].address<FT[k].address+FT[k].length){
							if(FT[k].address<FT[locate].address)
								locate++;
							for(int p=M;p>=k;p--)
								FT[p]=FT[p-1];
							FT[k].address=UT[j].address;
							FT[k].length=UT[j].length;
							FT[k].flag=1;
							M++;
							break;
						}
					}
					int u;
					for(u=0;u<M;u++)
						if(FT[u].address+FT[u].length==FT[k].address){
							FT[u].length+=FT[k].length;
							if(FT[locate].address>FT[k].address)
								locate--;
							for(int p=k;p<M;p++)
								FT[p]=FT[p+1];
							f=1;
							M--;
							break;
						}//有上邻空闲区
					if(f==1)
						k--;
					for(u=0;u<M;u++)
						if(FT[k].address+FT[k].length==FT[u].address){
							if(FT[locate].address>FT[u].address)
								locate--;
							FT[k].length+=FT[u].length;
							for(int p=u;p<M;p++)
								FT[p]=FT[p+1];
							M--;
							break;
						}//有下邻空闲区
					sort(FT,FT+M,compare);
					cout<<endl<<"--------空闲表(回收后)--------"<<endl;
					printf("起始地址   长度(KB)   标志\n");
					for(int j=0;j<M;j++){
						printf("%-12d%-10d",FT[j].address,FT[j].length);
						if(FT[j].flag==0)
							cout<<"空"<<endl;
						else
							cout<<"未分配"<<endl;
					}
					UT[j].flag=0;//已分配表标志位设置为空
					UT[j].address=-1;
					UT[j].length=-1;
				}
			}
		}
	}
	 return 0;
}

