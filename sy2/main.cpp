#include <iostream>
#include <cstring>
#define buffersize 3
#define OK 1
#define ERROR 0
using namespace std;
struct PCB{
    int type; //进程类型标号 0--生产者进程 1--消费者进程
    int no;//进程系统号
    int status;//进程状态 0--阻塞 1--就绪
    char product;//进程产品
	int reason;//阻塞原因 0--没有阻塞 1--因为没有筐而被阻塞 2--因为没有产品而被阻塞 3--因为仓库里有人而被阻塞
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
void PrintQueue(LinkQueue Q){
    cout<<"进程名"<<endl;
	QueuePtr p=Q.front->next;
	while(p){
		cout<<"进程"<<p->data.no<<endl;
		if(p->next)
			p=p->next;
		else
			break;
	}
}
void P(int &signal,PCB &pcb,LinkQueue &Wait,int reason){
    signal--;
    if(signal<0){
        pcb.status=0;//阻塞
		pcb.reason=reason;//设置阻塞原因
        EnQueue(Wait,pcb);
    }
}
void V(int &signal,PCB &pcb,LinkQueue &Wait,LinkQueue &Ready){
    signal++;
    if(signal<=0){
        PCB pcb;
        DeQueue(Wait,pcb);
        pcb.status=1;//就绪
        EnQueue(Ready,pcb);
    }
}
void PrintPCB(PCB pcb){
    cout<<endl<<"-----当前正在运行的进程信息-----"<<endl;
    cout<<"进程名：进程"<<pcb.no<<endl;
    cout<<"进程类型：";
    if(pcb.type==0)
        cout<<"生产者进程"<<endl<<"放入产品："<<pcb.product<<endl;
    else
        cout<<"消费者进程"<<endl<<"取出产品："<<pcb.product<<endl;
}
int main()
{
    char buffer[buffersize];//系统缓冲区大小为3
    LinkQueue Ready,ProducerWait,ConsumerWait,Over;
    char yesno='y';
    int n=0,No=1,type=0,flag=0,Mutex=1,Empty=buffersize,Full=0;
    InitQueue(Ready);
    InitQueue(ProducerWait);
    InitQueue(ConsumerWait);
    InitQueue(Over);
    memset(buffer,'0',buffersize);
    while(yesno=='y'||yesno=='Y'){
        cout<<"请输入要产生的进程数：";
        cin>>n;
        /*产生进程，初始化就绪队列*/
        while(n>0){
            PCB pcb;
            cout<<"请输入要产生的进程类别（0为生产者进程,1为消费者进程）:";
            cin>>type;
            if(type==0){
                pcb.type=0;
                pcb.no=No;
                pcb.status=1;
				pcb.reason=0;
                while(flag==0){
                    cout<<"请输入生产的产品（A | B | C）：";
                    cin>>pcb.product;
                    if(pcb.product!='A'&&pcb.product!='B'&&pcb.product!='C'){
                        cout<<"产品输入错误，请重新输入！"<<endl;
                    }
                    else
                        flag=1;
                }
                EnQueue(Ready,pcb);
                n--;
                No++;
            }
            else if(type==1){
                pcb.type=1;
                pcb.no=No;
                pcb.status=1;
				pcb.reason=0;
                EnQueue(Ready,pcb);
                n--;
                No++;
            }
            else
                cout<<"进程类别输入错误,请重新输入！"<<endl;
            flag=0;
        }
        /*进程调度*/
        while(Ready.front!=Ready.rear){
            PCB pcb;
            DeQueue(Ready,pcb);
            if(pcb.type==0){
				if(pcb.reason==0){
					 P(Empty,pcb,ProducerWait,1);//检查是否有筐
					 if(pcb.status==0)
						 continue;
				}
				if(pcb.reason!=3){
					P(Mutex,pcb,ProducerWait,3);//检查仓库里是否有人
					if(pcb.status==0)
						continue;
				}
                for(int i=0;i<buffersize;i++)
                    if(buffer[i]=='0'){
                        buffer[i]=pcb.product;
                        break;
                    }//放产品
                V(Mutex,pcb,ConsumerWait,Ready);//出仓库
                V(Full,pcb,ConsumerWait,Ready);//产品+1
            }//生产者进程
            else{
				if(pcb.reason==0){
					P(Full,pcb,ConsumerWait,2);//检查是否有产品
					if(pcb.status==0)
						continue;
				}
				if(pcb.reason!=3){
					P(Mutex,pcb,ConsumerWait,3);//检查仓库里是否有人
					if(pcb.status==0)
						continue;
				}
                for(int i=0;i<buffersize;i++)
                    if(buffer[i]!='0'){
                        pcb.product=buffer[i];
						buffer[i]='0';
                        break;
                    }//取产品
                V(Mutex,pcb,ProducerWait,Ready);//出仓库
                V(Empty,pcb,ProducerWait,Ready);//筐+1
            }//消费者进程
            if(pcb.status==1){
                PrintPCB(pcb);
                EnQueue(Over,pcb);
            }
        }
        cout<<endl<<"---------生产者等待队列---------"<<endl;
        if(ProducerWait.front!=ProducerWait.rear)
            PrintQueue(ProducerWait);
        else
            cout<<"空！"<<endl;
        cout<<endl<<"---------消费者等待队列---------"<<endl;
        if(ConsumerWait.front!=ConsumerWait.rear)
            PrintQueue(ConsumerWait);
        else
            cout<<"空！"<<endl;
        cout<<"是否继续产生进程?(y/n)"<<endl;
        cin>>yesno;
    }
    return 0;
}
