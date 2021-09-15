#include <iostream>
#include <cstring>
#define buffersize 3
#define OK 1
#define ERROR 0
using namespace std;
struct PCB{
    int type; //�������ͱ�� 0--�����߽��� 1--�����߽���
    int no;//����ϵͳ��
    int status;//����״̬ 0--���� 1--����
    char product;//���̲�Ʒ
	int reason;//����ԭ�� 0--û������ 1--��Ϊû�п�������� 2--��Ϊû�в�Ʒ�������� 3--��Ϊ�ֿ������˶�������
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
void PrintQueue(LinkQueue Q){
    cout<<"������"<<endl;
	QueuePtr p=Q.front->next;
	while(p){
		cout<<"����"<<p->data.no<<endl;
		if(p->next)
			p=p->next;
		else
			break;
	}
}
void P(int &signal,PCB &pcb,LinkQueue &Wait,int reason){
    signal--;
    if(signal<0){
        pcb.status=0;//����
		pcb.reason=reason;//��������ԭ��
        EnQueue(Wait,pcb);
    }
}
void V(int &signal,PCB &pcb,LinkQueue &Wait,LinkQueue &Ready){
    signal++;
    if(signal<=0){
        PCB pcb;
        DeQueue(Wait,pcb);
        pcb.status=1;//����
        EnQueue(Ready,pcb);
    }
}
void PrintPCB(PCB pcb){
    cout<<endl<<"-----��ǰ�������еĽ�����Ϣ-----"<<endl;
    cout<<"������������"<<pcb.no<<endl;
    cout<<"�������ͣ�";
    if(pcb.type==0)
        cout<<"�����߽���"<<endl<<"�����Ʒ��"<<pcb.product<<endl;
    else
        cout<<"�����߽���"<<endl<<"ȡ����Ʒ��"<<pcb.product<<endl;
}
int main()
{
    char buffer[buffersize];//ϵͳ��������СΪ3
    LinkQueue Ready,ProducerWait,ConsumerWait,Over;
    char yesno='y';
    int n=0,No=1,type=0,flag=0,Mutex=1,Empty=buffersize,Full=0;
    InitQueue(Ready);
    InitQueue(ProducerWait);
    InitQueue(ConsumerWait);
    InitQueue(Over);
    memset(buffer,'0',buffersize);
    while(yesno=='y'||yesno=='Y'){
        cout<<"������Ҫ�����Ľ�������";
        cin>>n;
        /*�������̣���ʼ����������*/
        while(n>0){
            PCB pcb;
            cout<<"������Ҫ�����Ľ������0Ϊ�����߽���,1Ϊ�����߽��̣�:";
            cin>>type;
            if(type==0){
                pcb.type=0;
                pcb.no=No;
                pcb.status=1;
				pcb.reason=0;
                while(flag==0){
                    cout<<"�����������Ĳ�Ʒ��A | B | C����";
                    cin>>pcb.product;
                    if(pcb.product!='A'&&pcb.product!='B'&&pcb.product!='C'){
                        cout<<"��Ʒ����������������룡"<<endl;
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
                cout<<"��������������,���������룡"<<endl;
            flag=0;
        }
        /*���̵���*/
        while(Ready.front!=Ready.rear){
            PCB pcb;
            DeQueue(Ready,pcb);
            if(pcb.type==0){
				if(pcb.reason==0){
					 P(Empty,pcb,ProducerWait,1);//����Ƿ��п�
					 if(pcb.status==0)
						 continue;
				}
				if(pcb.reason!=3){
					P(Mutex,pcb,ProducerWait,3);//���ֿ����Ƿ�����
					if(pcb.status==0)
						continue;
				}
                for(int i=0;i<buffersize;i++)
                    if(buffer[i]=='0'){
                        buffer[i]=pcb.product;
                        break;
                    }//�Ų�Ʒ
                V(Mutex,pcb,ConsumerWait,Ready);//���ֿ�
                V(Full,pcb,ConsumerWait,Ready);//��Ʒ+1
            }//�����߽���
            else{
				if(pcb.reason==0){
					P(Full,pcb,ConsumerWait,2);//����Ƿ��в�Ʒ
					if(pcb.status==0)
						continue;
				}
				if(pcb.reason!=3){
					P(Mutex,pcb,ConsumerWait,3);//���ֿ����Ƿ�����
					if(pcb.status==0)
						continue;
				}
                for(int i=0;i<buffersize;i++)
                    if(buffer[i]!='0'){
                        pcb.product=buffer[i];
						buffer[i]='0';
                        break;
                    }//ȡ��Ʒ
                V(Mutex,pcb,ProducerWait,Ready);//���ֿ�
                V(Empty,pcb,ProducerWait,Ready);//��+1
            }//�����߽���
            if(pcb.status==1){
                PrintPCB(pcb);
                EnQueue(Over,pcb);
            }
        }
        cout<<endl<<"---------�����ߵȴ�����---------"<<endl;
        if(ProducerWait.front!=ProducerWait.rear)
            PrintQueue(ProducerWait);
        else
            cout<<"�գ�"<<endl;
        cout<<endl<<"---------�����ߵȴ�����---------"<<endl;
        if(ConsumerWait.front!=ConsumerWait.rear)
            PrintQueue(ConsumerWait);
        else
            cout<<"�գ�"<<endl;
        cout<<"�Ƿ������������?(y/n)"<<endl;
        cin>>yesno;
    }
    return 0;
}
