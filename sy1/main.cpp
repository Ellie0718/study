#include<iostream>
#include<cstdlib>
#include<ctime>
#include <iomanip>
#include<stdio.h>
#define OK 1
#define ERROR 0
using namespace std;
struct PCB{
    int No;//进程名（数字）
    int status;//进程状态（0--等待 1--就绪）
    int priority;//优先级（1-10）
    int time;//所需执行时间（ms）
};
typedef struct QNode{
    PCB data;
    struct QNode *next;//队列指针
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
    Q.rear->next=p;//将新结点插到队尾
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
        Q.rear=Q.front;//删除最后一个元素时，需要同时改变front和rear
    delete p;
    return OK;
}
void PrintQueue(LinkQueue Q,int t[]){
	printf("进程名\t优先级\t执行时间\n");
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
    cout<<"-----当前正在运行的进程信息-----"<<endl;
    cout<<"进程名：进程"<<pcb.No<<endl;
    cout<<"优先级："<<pcb.priority<<endl;
    cout<<"总执行时间："<<pcb.time<<endl;
}
/*先进先出调度算法*/
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
		cout<<"----------初始就绪队列----------"<<endl;
		PrintQueue(Ready,t);
	}
	else
		cout<<"无PCB处于就绪态！"<<endl;
	if(Wait.front!=Wait.rear){
		cout<<endl<<"----------初始等待队列----------"<<endl;
		PrintQueue(Wait,t);
	}
	else
		cout<<"无PCB处于阻塞态！"<<endl;
	cout<<"================================"<<endl<<endl;
    while(n>0){
        PCB pcb1,pcb2;
        int r=rand()%2;//是否唤醒
        int r2=0;//是否阻塞
        int duration=rand()%5+1;//时间片大小（1-5随机数)
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
		cout<<endl<<"------------就绪队列------------"<<endl;
		if(Ready.front!=Ready.rear)
			PrintQueue(Ready,t);
		else
			cout<<"无PCB处于就绪态！"<<endl;
		cout<<endl<<"------------等待队列------------"<<endl;
		if(Wait.front!=Wait.rear)
			PrintQueue(Wait,t);
		else
			cout<<"无PCB处于阻塞态！"<<endl;
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
		cout<<"----------初始就绪队列----------"<<endl;
		printf("进程名\t优先级\t总执行时间\n");
		for(int i=0;i<ReadyNum;i++)
			printf("%d\t%d\t%d\n",Ready[i].No,Ready[i].priority,Ready[i].time);
	}
	else
		cout<<"无PCB处于就绪态！"<<endl;
	if(WaitNum!=0){
		cout<<endl<<"----------初始等待队列----------"<<endl;
		printf("进程名\t优先级\t总执行时间\n");
		for(int i=0;i<WaitNum;i++)
			printf("%d\t%d\t%d\n",Wait[i].No,Wait[i].priority,Wait[i].time);
	}
		else
			cout<<"无PCB处于阻塞态！"<<endl;
	cout<<"================================"<<endl<<endl;
}
/*基于优先数的调度算法*/
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
        int r=rand()%2;//是否唤醒
		int r2=0;//是否阻塞
        int duration=rand()%5+1;//时间片大小（1-5随机数)
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
		cout<<endl<<"------------就绪队列------------"<<endl;
		if(ReadyNum!=0){
			printf("进程名\t优先级\t执行时间\n");
			for(int i=0;i<ReadyNum;i++)
				printf("%d\t%d\t%d\n",Ready[i].No,Ready[i].priority,t[Ready[i].No-1]);
		}
		else
			cout<<"无PCB处于就绪态！"<<endl;
		cout<<endl<<"------------等待队列------------"<<endl;
		if(WaitNum!=0){
			printf("进程名\t优先级\t执行时间\n");
			for(int i=0;i<WaitNum;i++)
				printf("%d\t%d\t%d\n",Wait[i].No,Wait[i].priority,t[Wait[i].No-1]);
		}
		else
			cout<<"无PCB处于阻塞态！"<<endl;
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
/*最短执行时间的调度算法*/
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
        int r=rand()%2;//是否唤醒
		int r2=0;//是否阻塞
        int duration=rand()%5+1;//时间片大小（1-5随机数)
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
		cout<<endl<<"------------就绪队列------------"<<endl;
		if(ReadyNum!=0){
			printf("进程名\t优先级\t执行时间\n");
			for(int i=0;i<ReadyNum;i++)
				printf("%d\t%d\t%d\n",Ready[i].No,Ready[i].priority,t[Ready[i].No-1]);
		}
		else
			cout<<"无PCB处于就绪态！"<<endl;
		cout<<endl<<"------------等待队列------------"<<endl;
		if(WaitNum!=0){
			printf("进程名\t优先级\t执行时间\n");
			for(int i=0;i<WaitNum;i++)
				printf("%d\t%d\t%d\n",Wait[i].No,Wait[i].priority,t[Wait[i].No-1]);
		}
		else
			cout<<"无PCB处于阻塞态！"<<endl;
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
			pcb[i].No=i+1;//设置进程名
			pcb[i].status=rand()%2;//设置进程状态（0/1随机数）
			pcb[i].priority=rand()%10+1;//设置进程优先级（1-10随机数）
			pcb[i].time=rand()%20+1;//设置进程所需总时间(1-20随机数)
		}
        cout<<"1. 先进先出调度算法" <<endl;
        cout<<"2. 基于优先数的调度算法"<<endl;
        cout<<"3. 最短执行时间调度算法"<<endl;
        cout<<"请选择需要使用的调度算法(1 or 2 or 3):";
        cin>>choice;
        switch(choice){
            case 1:FIFO(pcb);break;
            case 2:OnPriority(pcb);break;
            case 3:ShortestTime(pcb);break;
            default:cout<<"输入错误！"<<endl;break;
        }
        cout<<"您还要继续输入吗?(y/n)";
        cin>>yesno;
    }
    return 0;
}
