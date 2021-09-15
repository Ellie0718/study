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
 int address;       //�ѷַ�����ʼ��ַ
 int length;        //�ѷַ������ȣ���λΪKB
 int flag;            //�ѷ�������Ǽ�����־����0��ʾ����Ŀ��
};          //�ѷ�������
struct free_table{
 int address;       //��������ʼ��ַ
 int length;        //���������ȣ���λΪKB
 int flag;            //��������Ǽ���Ŀ��0��ʾ����Ŀ��1��ʾδ����
};          //��������
struct JCB{
    int No;//��ҵ��
    int MemorySize;//�ڴ��С��������L
    int Flag;//0��ʾû�з��䵽�ڴ棬1��ʾ�ѷ��䵽�ڴ棬2��ʾ��ҵ�Ѿ��������ڴ��ѻ���
};
bool compare(free_table f1,free_table f2){
	return f1.length>f2.length;
}
bool compare2(free_table f1,free_table f2){
	return f1.address<f2.address;
}
void PrintUT(used_table UT[]){
	cout<<endl<<"-----------�ѷ����-----------"<<endl;
	printf("��ʼ��ַ   ����(KB)   ��־\n");
	for(int j=0;j<10;j++){
		if(UT[j].address!=-1)
			printf("%-12d%",UT[j].address);
		else
			printf("%-12s","��");
		if(UT[j].length!=-1)
			printf("%-10d",UT[j].length);
		else
			printf("%-10s","��");
		if(UT[j].flag==0)
			cout<<"��"<<endl;
		else
			cout<<"��ҵ"<<UT[j].flag<<endl;
	}
}
void PrintFT(free_table FT[],int M){
	cout<<endl<<"------------���б�------------"<<endl;
	printf("��ʼ��ַ   ����(KB)   ��־\n");
	for(int j=0;j<M;j++){
		printf("%-12d%-10d",FT[j].address,FT[j].length);
		if(FT[j].flag==0)
			cout<<"��"<<endl;
		else
			cout<<"δ����"<<endl;
	}
}
int main()
{
    int N=0,x=0,M=10,choice=0,flag=0,X=0,locate=0;//NΪ�ѷ���ռ����ҵ����MΪ�������ĸ�����XΪ���������
    free_table FT[11];
    used_table UT[10];
    JCB jcb[10];
    srand((unsigned)time(NULL));
    /*��ʼ����������*/
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
    /*��ʼ���ѷ�������*/
	for(int i=0;i<10;i++){
		UT[i].address=-1;
		UT[i].flag=0;
		UT[i].length=-1;
	}
    /*������ҵ���У�10����*/
    for(int i=0;i<10;i++){
        jcb[i].No=i+1;
        jcb[i].MemorySize=rand()%1024+1;//ÿ����ҵ�ڴ����󲻳���1M
        jcb[i].Flag=0;
    }
	while(flag==0){
		cout<<"1.�״���Ӧ��"<<endl;
		cout<<"2.ѭ���״���Ӧ��"<<endl;
		cout<<"3.���Ӧ��"<<endl;
		cout<<"��ѡ��һ���ڴ�����㷨��";
		cin>>choice;
		if(choice==1||choice==2||choice==3)
			flag=1;
		else{
			cout<<"����������������룡"<<endl;
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
				if(choice==1){//������Ӧ�㷨�����ڴ�ռ�
					for(int m=0;m<M;m++){
						if(FT[m].length>=jcb[i].MemorySize){
							for(int j=0;j<10;j++){
								if(UT[j].flag==0){
									UT[j].address=FT[m].address;
									UT[j].length=jcb[i].MemorySize;
									UT[j].flag=jcb[i].No;//��־λ��Ϊ�ѷ����ڴ�ռ����ҵ��
									if(FT[m].length>jcb[i].MemorySize){
										FT[m].address+=jcb[i].MemorySize;
										FT[m].length-=jcb[i].MemorySize;
									}
									else{
										FT[m].length=0;
										FT[m].flag=0;//��������־λ��Ϊ���ա�
										for(k=m;k<M;k++)
											FT[m]=FT[m+1];
										M--;
									}
									jcb[i].Flag=1;//��Ϊ��ҵ�����ڴ�ռ�
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
				else if(choice==2){//ѭ���״���Ӧ�㷨�����ڴ�ռ�
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
									UT[j].flag=jcb[i].No;//��־λ��Ϊ�ѷ����ڴ�ռ����ҵ��
									if(FT[m].length>jcb[i].MemorySize){
										FT[m].address+=jcb[i].MemorySize;
										FT[m].length-=jcb[i].MemorySize;
									}
									else{
										FT[m].length=0;
										FT[m].flag=0;//��������־λ��Ϊ���ա�
										for(k=m;k<M;k++)
											FT[m]=FT[m+1];
										M--;
										locate--;
									}
									PrintUT(UT);
									PrintFT(FT,M);
									jcb[i].Flag=1;//��Ϊ��ҵ�����ڴ�ռ�
									N++;
									break;
								}
							}
							if(jcb[i].Flag==1)
								break;
						}
					}
				}
				else {//���Ӧ�㷨�����ڴ�ռ�
					sort(FT,FT+M,compare);
					for(int m=0;m<M;m++){
						if(FT[m].length>=jcb[i].MemorySize){
							for(int j=0;j<10;j++){
								if(UT[j].flag==0){
									UT[j].address=FT[m].address;
									UT[j].length=jcb[i].MemorySize;
									UT[j].flag=jcb[i].No;//��־λ��Ϊ�ѷ����ڴ�ռ����ҵ��
									if(FT[m].length>jcb[i].MemorySize){
										FT[m].address+=jcb[i].MemorySize;
										FT[m].length-=jcb[i].MemorySize;
									}
									else{
										FT[m].length=0;
										FT[m].flag=0;//��������־λ��Ϊ���ա�
										for(k=m;k<M;k++)
											FT[m]=FT[m+1];
										M--;
									}
									PrintUT(UT);
									PrintFT(FT,M);
									jcb[i].Flag=1;//��Ϊ��ҵ�����ڴ�ռ�
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
				if(jcb[i].Flag==0){//û���㹻�ռ����
					cout<<endl<<"��ҵ"<<jcb[i].No<<"�ȴ�"<<endl;
					cout<<"���ȣ�"<<jcb[i].MemorySize<<"KB"<<endl;
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
					}//�����ڿ�����
				k++;
			}
			locate++;
		}
		for(int j=0;j<10;j++){//�����ѷ����
			if(UT[j].flag!=0){
				x=rand()%2;//����һ���������0��1�������Ϊ1����ѷ��䵽���ڴ���л���
				if(x==1){
					for(k=0;k<10;k++)
						if(jcb[k].No==UT[j].flag){
							jcb[k].Flag=2;
							break;
						}
					cout<<endl<<"-----------���տռ�-----------"<<endl;
					printf("��ҵ       ��ʼ��ַ   ����(KB)\n");
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
						}//�����ڿ�����
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
						}//�����ڿ�����
					sort(FT,FT+M,compare);
					cout<<endl<<"--------���б�(���պ�)--------"<<endl;
					printf("��ʼ��ַ   ����(KB)   ��־\n");
					for(int j=0;j<M;j++){
						printf("%-12d%-10d",FT[j].address,FT[j].length);
						if(FT[j].flag==0)
							cout<<"��"<<endl;
						else
							cout<<"δ����"<<endl;
					}
					UT[j].flag=0;//�ѷ�����־λ����Ϊ��
					UT[j].address=-1;
					UT[j].length=-1;
				}
			}
		}
	}
	 return 0;
}

