#include<iostream>
#include<cstdlib>
#include<ctime>
#include <iomanip>
#include<stdio.h>
#define OK 1
#define ERROR 0
using namespace std;
struct PCB{
    int No;//�����������֣�
    int status;//����״̬��0--�ȴ� 1--������
    int priority;//���ȼ���1-10��
    int time;//����ִ��ʱ�䣨ms��
};
typedef struct QNode{
    PCB data;
    struct QNode *next;//����ָ��
}QNode,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
int InitQueue(LinkQueue &Q){
    Q.front=Q.rear=new QNode;
    Q.front->next=NULL;
    return OK;
}
int EnQueue(LinkQueue &Q,PCB e){
    QueuePtr p=new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;//���½��嵽��β
    Q.rear=p;
    return OK;
}
int DeQueue(LinkQueue &Q,PCB &e){
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
void PrintQueue(LinkQueue Q,int t[]){
	printf("������\t���ȼ�\tִ��ʱ��\n");
	QueuePtr p=Q.front->next;
	while(p){
		printf("%d\t%d\t%d\n",p->data.No,p->data.priority,t[p->data.No-1]);
		if(p->next)
			p=p->next;
		else
			break;
	}
}
void PrintPCB(PCB pcb){
    cout<<"-----��ǰ�������еĽ�����Ϣ-----"<<endl;
    cout<<"������������"<<pcb.No<<endl;
    cout<<"���ȼ���"<<pcb.priority<<endl;
    cout<<"��ִ��ʱ�䣺"<<pcb.time<<endl;
}
/*�Ƚ��ȳ������㷨*/
void FIFO(PCB pcb[]){
    int n=10,t[10];
	LinkQueue Wait,Ready;
    InitQueue(Wait);
    InitQueue(Ready);
    srand((unsigned)time(NULL));
    for(int i=0;i<10;i++){
        if(pcb[i].status==1)
            EnQueue(Ready,pcb[i]);
        else
            EnQueue(Wait,pcb[i]);
    }
	for(int i=0;i<10;i++)
		t[i]=pcb[i].time;
	cout<<"================================"<<endl;
	if(Ready.front!=Ready.rear){
		cout<<"----------��ʼ��������----------"<<endl;
		PrintQueue(Ready,t);
	}
	else
		cout<<"��PCB���ھ���̬��"<<endl;
	if(Wait.front!=Wait.rear){
		cout<<endl<<"----------��ʼ�ȴ�����----------"<<endl;
		PrintQueue(Wait,t);
	}
	else
		cout<<"��PCB��������̬��"<<endl;
	cout<<"================================"<<endl<<endl;
    while(n>0){
        PCB pcb1,pcb2;
        int r=rand()%2;//�Ƿ���
        int r2=0;//�Ƿ�����
        int duration=rand()%5+1;//ʱ��Ƭ��С��1-5�����)
		cout<<"================================"<<endl;
        if(Ready.front!=Ready.rear){
            DeQueue(Ready,pcb1);
            PrintPCB(pcb1);
			if(duration>=t[pcb1.No-1])
                n--;
            else{
                t[pcb1.No-1]-=duration;
                r2=rand()%2;
                if(r2==0)
                    EnQueue(Ready,pcb1);
				else{
					EnQueue(Wait,pcb1);
					pcb1.status=0;
				}
            }
        }
		if(r==1&&Wait.front!=Wait.rear){
			DeQueue(Wait,pcb2);
			pcb2.status=1;
			EnQueue(Ready,pcb2);
		}
		cout<<endl<<"------------��������------------"<<endl;
		if(Ready.front!=Ready.rear)
			PrintQueue(Ready,t);
		else
			cout<<"��PCB���ھ���̬��"<<endl;
		cout<<endl<<"------------�ȴ�����------------"<<endl;
		if(Wait.front!=Wait.rear)
			PrintQueue(Wait,t);
		else
			cout<<"��PCB��������̬��"<<endl;
		cout<<"================================"<<endl<<endl;
    }
}
void Insert(PCB pcb[],PCB p,int &length){
	pcb[length]=p;
	length++;
}
void Delete(PCB pcb[],PCB &p,int &length){
	int max=pcb[0].priority,location=0;
	for(int i=1;i<length;i++)
		if(pcb[i].priority>max){
			max=pcb[i].priority;
			location=i;
		}
	p=pcb[location];
	for(int i=location;i<length;i++)
		pcb[i]=pcb[i+1];
	length--;
}
void PrintOrigin(PCB Ready[],PCB Wait[],int ReadyNum,int WaitNum){
	cout<<"================================"<<endl;
	if(ReadyNum!=0){
		cout<<"----------��ʼ��������----------"<<endl;
		printf("������\t���ȼ�\t��ִ��ʱ��\n");
		for(int i=0;i<ReadyNum;i++)
			printf("%d\t%d\t%d\n",Ready[i].No,Ready[i].priority,Ready[i].time);
	}
	else
		cout<<"��PCB���ھ���̬��"<<endl;
	if(WaitNum!=0){
		cout<<endl<<"----------��ʼ�ȴ�����----------"<<endl;
		printf("������\t���ȼ�\t��ִ��ʱ��\n");
		for(int i=0;i<WaitNum;i++)
			printf("%d\t%d\t%d\n",Wait[i].No,Wait[i].priority,Wait[i].time);
	}
		else
			cout<<"��PCB��������̬��"<<endl;
	cout<<"================================"<<endl<<endl;
}
/*�����������ĵ����㷨*/
void OnPriority(PCB pcb[]){
    int n=10,ReadyNum=0,WaitNum=0;
	int t[10];
	PCB Ready[10],Wait[10];
    srand((unsigned)time(NULL));
	for(int i=0;i<10;i++){
		if(pcb[i].status==1){
			Ready[ReadyNum]=pcb[i];
			ReadyNum++;
		}
		else{
			Wait[WaitNum]=pcb[i];
			WaitNum++;
		}
    }
	PrintOrigin(Ready,Wait,ReadyNum,WaitNum);
	for(int i=0;i<10;i++)
		t[i]=pcb[i].time;
    while(n>0){
        PCB pcb1,pcb2;
        int r=rand()%2;//�Ƿ���
		int r2=0;//�Ƿ�����
        int duration=rand()%5+1;//ʱ��Ƭ��С��1-5�����)
		cout<<"================================"<<endl;
        if(ReadyNum!=0){
			Delete(Ready,pcb1,ReadyNum);
            PrintPCB(pcb1);
            if(duration>=t[pcb1.No-1])
                n--;
            else{
                t[pcb1.No-1]-=duration;
                r2=rand()%2;
                if(r2==0)
                    Insert(Ready,pcb1,ReadyNum);
				else{
					Insert(Wait,pcb1,WaitNum);
					pcb1.status=0;
				}
            }
        }
		if(r==1&&WaitNum!=0){
			pcb2=Wait[0];
			for(int i=0;i<WaitNum;i++)
				Wait[i]=Wait[i+1];
			WaitNum--;
			pcb2.status=1;
			Insert(Ready,pcb2,ReadyNum);
		}
		cout<<endl<<"------------��������------------"<<endl;
		if(ReadyNum!=0){
			printf("������\t���ȼ�\tִ��ʱ��\n");
			for(int i=0;i<ReadyNum;i++)
				printf("%d\t%d\t%d\n",Ready[i].No,Ready[i].priority,t[Ready[i].No-1]);
		}
		else
			cout<<"��PCB���ھ���̬��"<<endl;
		cout<<endl<<"------------�ȴ�����------------"<<endl;
		if(WaitNum!=0){
			printf("������\t���ȼ�\tִ��ʱ��\n");
			for(int i=0;i<WaitNum;i++)
				printf("%d\t%d\t%d\n",Wait[i].No,Wait[i].priority,t[Wait[i].No-1]);
		}
		else
			cout<<"��PCB��������̬��"<<endl;
		cout<<"================================"<<endl<<endl;
    }

}
void Insert2(PCB pcb[],PCB p,int &length){
	pcb[length]=p;
	length++;
}

void Delete2(PCB pcb[],PCB &p,int &length,int t[]){
	int min=pcb[0].time,location=0;
	for(int i=1;i<length;i++)
		if(t[pcb[i].No-1]<min){
			min=t[pcb[i].No-1];
			location=i;
		}
	p=pcb[location];
	for(int i=location;i<length;i++)
		pcb[i]=pcb[i+1];
	length--;
}
/*���ִ��ʱ��ĵ����㷨*/
void ShortestTime(PCB pcb[]){
    int n=10,ReadyNum=0,WaitNum=0;
	int t[10];
	PCB Ready[10],Wait[10];
    srand((unsigned)time(NULL));
	for(int i=0;i<10;i++){
		if(pcb[i].status==1){
			Ready[ReadyNum]=pcb[i];
			ReadyNum++;
		}
		else{
			Wait[WaitNum]=pcb[i];
			WaitNum++;
		}
    }
	PrintOrigin(Ready,Wait,ReadyNum,WaitNum);
	for(int i=0;i<10;i++)
		t[i]=pcb[i].time;
    while(n>0){
        PCB pcb1,pcb2;
        int r=rand()%2;//�Ƿ���
		int r2=0;//�Ƿ�����
        int duration=rand()%5+1;//ʱ��Ƭ��С��1-5�����)
		cout<<"================================"<<endl;
        if(ReadyNum!=0){
			Delete2(Ready,pcb1,ReadyNum,t);
            PrintPCB(pcb1);
            if(duration>=t[pcb1.No-1])
                n--;
            else{
                t[pcb1.No-1]-=duration;
                r2=rand()%2;
                if(r2==0)
                    Insert2(Ready,pcb1,ReadyNum);
				else{
					Insert2(Wait,pcb1,WaitNum);
					pcb1.status=0;
				}
            }
        }
		if(r==1&&WaitNum!=0){
			pcb2=Wait[0];
			for(int i=0;i<WaitNum;i++)
				Wait[i]=Wait[i+1];
			WaitNum--;
			pcb2.status=1;
			Insert2(Ready,pcb2,ReadyNum);
		}
		cout<<endl<<"------------��������------------"<<endl;
		if(ReadyNum!=0){
			printf("������\t���ȼ�\tִ��ʱ��\n");
			for(int i=0;i<ReadyNum;i++)
				printf("%d\t%d\t%d\n",Ready[i].No,Ready[i].priority,t[Ready[i].No-1]);
		}
		else
			cout<<"��PCB���ھ���̬��"<<endl;
		cout<<endl<<"------------�ȴ�����------------"<<endl;
		if(WaitNum!=0){
			printf("������\t���ȼ�\tִ��ʱ��\n");
			for(int i=0;i<WaitNum;i++)
				printf("%d\t%d\t%d\n",Wait[i].No,Wait[i].priority,t[Wait[i].No-1]);
		}
		else
			cout<<"��PCB��������̬��"<<endl;
		cout<<"================================"<<endl<<endl;
    }
}
int main()
{
    int choice;
    char yesno='Y';
    while(yesno=='Y'||yesno=='y'){
        PCB pcb[10];
		srand((unsigned)time(NULL));
		for(int i=0;i<10;i++){
			pcb[i].No=i+1;//���ý�����
			pcb[i].status=rand()%2;//���ý���״̬��0/1�������
			pcb[i].priority=rand()%10+1;//���ý������ȼ���1-10�������
			pcb[i].time=rand()%20+1;//���ý���������ʱ��(1-20�����)
		}
        cout<<"1. �Ƚ��ȳ������㷨" <<endl;
        cout<<"2. �����������ĵ����㷨"<<endl;
        cout<<"3. ���ִ��ʱ������㷨"<<endl;
        cout<<"��ѡ����Ҫʹ�õĵ����㷨(1 or 2 or 3):";
        cin>>choice;
        switch(choice){
            case 1:FIFO(pcb);break;
            case 2:OnPriority(pcb);break;
            case 3:ShortestTime(pcb);break;
            default:cout<<"�������"<<endl;break;
        }
        cout<<"����Ҫ����������?(y/n)";
        cin>>yesno;
    }
    return 0;
}
