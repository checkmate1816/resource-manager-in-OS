#include<iostream>
#include<string>
using namespace std;
class PCB
{
public:
	string PID;
	int Priority;
	int Status;//0������1������2����
	PCB *Parent=NULL;
	PCB *Childrenhead=NULL;//�ӽڵ����
	PCB *Childrenrear = NULL;//�ӽڵ����
	PCB *lastbrother = NULL;//��ͬһ�����µ��ֵ�ָ��
	PCB *nextbrother = NULL;//��ͬһ�����µ��ֵ�ָ��
	PCB *last=NULL;//PCB����������
	PCB *next=NULL;//PCB����������
	int idealresource[4] = { 0 };//���������Դ����
	int yetresource[4] = { 0 };//ʵ�ʷ�����Դ����
	string blockname = { "\n"};//������ĳ����Դ����
	void init(string s, int y)
	{
		PID = s;
		Priority = y;
		Status = 0;
	}

};
class RCB {
public:
	string RID;//��Դ��ID
	int total = 0;//����Դ����
	int Status;//������Դ������
	PCB *head=NULL;
	PCB  *rear=NULL;
	RCB(string name, int num)
	{
		RID = name;
		total = num;
		Status = num;
	}
};
PCB *systemreadyhead = NULL;
PCB *systemreadyrear = NULL;
PCB *userreadyhead = NULL;
PCB *userreadyrear = NULL;
PCB *initreadyhead = NULL;
PCB *initreadyrear = NULL;
PCB *running = NULL;
RCB R1("R1", 1), R2("R2", 2), R3("R3", 3), R4("R4", 4);
void insertready(PCB *pcb)//�����������
{
	switch (pcb->Priority)
	{
	case 0: {
		pcb->Status = 0;
		pcb->last = initreadyrear;
		pcb->next = NULL;
		if (initreadyrear != NULL)
			initreadyrear->next = pcb;
		else
			initreadyhead = pcb;
		initreadyrear = pcb;
		break;
	}
	case 1: {
		pcb->Status = 0;
		pcb->last = userreadyrear;
		pcb->next = NULL;
		if (userreadyrear != NULL)
			userreadyrear->next = pcb;
		else
			userreadyhead = pcb;
		userreadyrear = pcb;
		break;

	}
	case 2: {
		pcb->Status = 0;
		pcb->last = systemreadyrear;
		pcb->next = NULL;
		if (systemreadyrear != NULL)
			systemreadyrear->next = pcb;
		else
			systemreadyhead = pcb;
		systemreadyrear = pcb;
		break;
	}
	default:
		cout << "error" << endl;
	}
}
void insertrunning(PCB *pcb)//�����̸�Ϊ����̬
{
	running = pcb;
	running->last = NULL;
	running->Status = 2;
	switch (pcb->Priority)
	{
	case 0:
	{
		if (initreadyhead != initreadyrear)
		{
			initreadyhead = pcb->next;
			initreadyhead->last = NULL;
			running->next = NULL;
		}
		else
		{
			initreadyhead = NULL;
			initreadyrear = NULL;
		}
		break;
	}
	case 1:
	{
		if (userreadyhead != userreadyrear)
		{
			userreadyhead = pcb->next;
			userreadyhead->last = NULL;
			running->next = NULL;
		}
		else
		{
			userreadyhead = NULL;
			userreadyrear = NULL;
		}
		break;
	}
	case 2:
	{
		if (systemreadyhead != systemreadyrear)
		{
			systemreadyhead = pcb->next;
			systemreadyhead->last = NULL;
			running->next = NULL;
		}
		else
		{
			systemreadyhead = NULL;
			systemreadyrear = NULL;
		}
		break;
	}
	}
}
void Scheduler()
{
	PCB *highpcb;
	if (systemreadyhead != NULL)//�ҳ����ȼ���ߵĽ���
		highpcb = systemreadyhead;
	else if (userreadyhead != NULL)
		highpcb = userreadyhead;
	else
		highpcb = NULL;
	if (highpcb == NULL)
		return;
	if(running == NULL)
		insertrunning(highpcb);
	else if ((highpcb->Priority > running->Priority)&&running->Status==2)//ϵͳ�½�����ռ
	{
		insertready(running);
		insertrunning(highpcb);
	}
	else if (running->Status == 0)//ʱ���ж�
	{
		insertready(running);
		insertrunning(highpcb);
	}
	else if(running->Status == 1)//��������
		insertrunning(highpcb);
}
void timeout()//�ж�
{
	PCB * temp = running;
	running->Status = 0;
	Scheduler();
	if (running != temp)
		cout << "process" << "  " << running->PID << " " << "is running" << ",process  " << temp->PID << " " << "is ready" << endl;
	else//������û���л�ʱ
	{
		running->Status = 2;
		cout << "process  " << temp->PID << "  is running" << endl;
	}
}

PCB* search(PCB *pcb, string pid)//���ø��ӹ�ϵ��init���̲��ҽ���
{
	PCB *temp = NULL;
	temp = pcb;
	if (temp == NULL)
		return NULL;
	if (temp->PID.compare(pid) == 0)
		return temp;
	if (search(temp->nextbrother, pid) == NULL)
	{
		return search(temp->Childrenhead, pid);
	}
	else
		return search(temp->nextbrother, pid);
}
RCB* getRCB(string name)//ͨ��rid�ҵ���Դ��
{
	if (name.compare("R1")==0)
		return &R1;
	if (name.compare("R2")==0)
		return &R2;
	if (name.compare("R3")==0)
		return &R3;
	if (name.compare("R4")==0)
		return &R4;
}
RCB* getRCB(int n)//ͨ�������ҵ���Դ��
{
	if (n==0)
		return &R1;
	if (n==1)
		return &R2;
	if (n==2)
		return &R3;
	if (n==3)
		return &R4;
}
int ridtransmit(string rid)
{
	if (rid.compare("R1")==0)
		return 0;
	else if (rid.compare("R2")==0)
		return 1;
	else if (rid.compare("R3")==0)
		return 2;
	else if (rid.compare("R4")==0)
		return 3;
}
void insertblock(PCB *pcb, RCB *rcb)//����������Ϊ����
{
	pcb->blockname = rcb->RID;
	if (rcb->head == NULL)//����������
	{
		rcb->head = pcb;
		rcb->rear = pcb;
	}
	else//�����Ѿ�������
	{
		pcb->last = rcb->rear;
		rcb->rear->next = pcb;
		rcb->rear = pcb;
	}
}
void Request(string name, int n)//��������Դ
{
	RCB *r = getRCB(name);
	int temp = ridtransmit(name);
	*(running->idealresource + temp) += n;
	if (r->Status >= n)
	{
		r->Status = r->Status - n;
		*(running->yetresource + temp) += n;
		cout << "process"<<"  " << running->PID <<"  " << "requests  " << n <<"  "<< r->RID << endl;
	}
	else
	{
		if (n > r->total)//����������������
		{
			printf("��Դ��Ŀ����\n");
			return;
		}
		else if (r->Status < n)//������������ǰ����
		{
			running->Status = 1;
			insertblock(running, r);
		}
		Scheduler();
		cout << "process  " << running->PID << "  is running  " << "process  " << r->rear->PID << "  is blocked" << endl;
	}
}
void removeblock(RCB *r)
{
	PCB *pcb = r->head;
	r->head->last = NULL;
	r->head = r->head->next;
	cout << "wake up   process" << "  " << pcb->PID << endl;
	insertready(pcb);
}
void Release(string rid, int n)
{
	RCB *r = getRCB(rid);
	int temp = ridtransmit(rid);
	if (*(running->yetresource + temp) >= n)
	{
		*(running->yetresource + temp) -= n;
		r->Status += n;
		cout << "process  " << running->PID << "   release   " << n << "  " << r->RID << endl;
	}
	else
	{
		cout << "��ӵ����Դ��������" << endl;
		return;
	}
	while (r->head != NULL && *(r->head->idealresource + temp) <= r->Status)
	{
		r->Status -= *(r->head->idealresource + temp);
		*(r->head->yetresource + temp) += *(r->head->idealresource + temp);
		removeblock(r);
	}
	Scheduler();
}
void killresource(PCB *p)//ɱ�������ͷ���Դ
{
	int *a = p->yetresource;
	RCB *r = NULL;
	for (int i = 0; i < 4; i++)
	{
		if (*a != 0)
		{
			r = getRCB(i);
			r->Status += *a;
			if (i != 3)
				cout << "release  " << r->RID <<" ";
			else
				cout << "release  " << r->RID << endl;
			while (r->head != NULL && *(r->head->idealresource + i) <= r->Status)
			{
				r->Status -= *(r->head->idealresource + i + 1);
				*(r->head->yetresource + i) += *(r->head->idealresource + i);
				removeblock(r);
			}
		}
		a++;
	}
}
void linkchange(PCB *pcb)//����������
{
	pcb->last->next = pcb->next;
	pcb->next->last = pcb->last;
	return;
}
PCB *no = NULL;
void killtree(PCB *p)
{
	if (p->Childrenhead!= NULL)
		killtree(p->Childrenhead);
	if (p->Parent != no)
	{
		if (p->nextbrother != NULL)
			killtree(p->nextbrother);
	}
	if (p->Status == 2)//������������
	{
		killresource(p);
		delete p;
		running = NULL;
	}
	else if (p->Status == 0)//�����ھ�������
	{
		if (p->last != NULL)//p��Ϊ��ͷ�ڵ�
		{
			if (p->next != NULL)//pҲ��Ϊ��β�ڵ�
			{
				killresource(p);
				linkchange(p);//�������Ӿ���״̬��
				delete p;
			}
			else//pΪ��β�ڵ�
			{
				switch (p->Priority)
				{
				case 0:
				{
					killresource(p);
					if (p->last != NULL)
					{
						p->last->next = NULL;
						initreadyrear = p->last;
					}
					else
					{
						initreadyhead = NULL;
						initreadyrear = NULL;
					}
					delete p;
					break;
				}
				case 1:
				{
					killresource(p);
					if (p->last != NULL)
					{
						p->last->next = NULL;
						userreadyrear = p->last;
					}
					else
					{
						userreadyhead = NULL;
						userreadyrear = NULL;
					}
					delete p;
					break;
				}
				case 2:
				{
					killresource(p);
					if (p->last != NULL)
					{
						p->last->next = NULL;
						systemreadyrear = p->last;
					}
					else
					{
						systemreadyhead = NULL;
						systemreadyrear = NULL;
					}
					delete p;
					break;
				}
				}
			}
		}
		else//pΪ��ͷ�ڵ�
		{
			switch (p->Priority)
			{
			case 0:
			{
				killresource(p);
				if (p->next != NULL)
				{
					p->next->last = NULL;
					initreadyhead = p->next;
				}
				else
				{
					initreadyhead = NULL;
					initreadyrear = NULL;
				}
				delete p;
				break;
			}
			case 1:
			{
				killresource(p);
				if (p->next != NULL)
				{
					p->next->last = NULL;
					userreadyhead = p->next;
				}
				else
				{
					userreadyhead = NULL;
					userreadyrear = NULL;
				}
				delete p;
				break;
			}
			case 2:
			{
				killresource(p);
				if (p->next != NULL)
				{
					p->next->last = NULL;
					systemreadyhead = p->next;
				}
				else
				{
					systemreadyhead = NULL;
					systemreadyrear = NULL;
				}
				delete p;
				break;
			}
			}
		}
	}
	else//��������
	{
		if (p->last != NULL && p->next != NULL)//���̲�����������ͷ����β
		{
			linkchange(p);
			killresource(p);
			delete p;
		}
		else if (p->last == NULL)//����������ͷ��
		{
			RCB *r = getRCB(p->blockname);
			if (p->next != NULL)
			{
				r->head->last = NULL;
				r->head = p->next;
			}
			else
			{
				r->head = NULL;
				r->rear = NULL;
			}
			killresource(p);
			delete p;
		}
		else//����������β��
		{
			RCB *r = getRCB(p->blockname);
			if (p->last != NULL)
			{
				r->rear->next = NULL;
				r->rear = p->last;
			}
			else
			{
				r->head = NULL;
				r->rear = NULL;
			}
			killresource(p);
			delete p;
		}
	}
	return;//������һ��
}
void Init()//��ʼ������
{
	PCB *pcb = new PCB;
	pcb->init("init", 0);
	insertrunning(pcb);
	Scheduler();
	cout << "process" <<"  "<< running->PID <<"  "<< "is running" << endl;
}
void create(string name, int priority)//��������
{
	PCB *pcb = new PCB;
	pcb->init(name, priority);
	if (running == NULL)//���޵�ǰ���н���
	{
		pcb->Parent = initreadyhead;
		pcb->lastbrother = initreadyhead->Childrenrear;
		initreadyhead->Childrenrear->nextbrother = pcb;
		initreadyhead->Childrenrear = pcb;
	}
	else if (running->Childrenhead == NULL)//���������нڵ����ӽڵ�ʱ
	{
		pcb->Parent = running;
		running->Childrenhead = pcb;
		running->Childrenrear = pcb;
	}
	else//��ǰ���н������ӽڵ�ʱ
	{
		pcb->Parent = running;
		pcb->lastbrother = running->Childrenrear;
		running->Childrenrear->nextbrother = pcb;
		running->Childrenrear = pcb;
	}
	insertready(pcb);
	Scheduler();
	cout << "process" <<"   "<< running->PID <<"   "<< "is running" << endl;
}
void Destroy(string pid)//���ٽ���
{
	PCB *p;
	p = search(initreadyhead, pid);
	if (p != NULL)
	{
		no = p->Parent;
		if (p->lastbrother != NULL)
		{
			if (p->nextbrother != NULL)//��ɾ���ڵ��ڶ����м�
			{
				p->lastbrother->nextbrother = p->nextbrother;
				p->nextbrother->lastbrother = p->lastbrother;
				killtree(p);
			}
			else//��ɾ���ڵ��ڶ���β��
			{
				no->Childrenrear = p->lastbrother;
				p->lastbrother->nextbrother = NULL;
				killtree(p);
			}
		}
		else
		{
			if (p->nextbrother != NULL)//��ɾ���ڵ��ڶ���ͷ��
			{
				no->Childrenhead = p->nextbrother;
				p->nextbrother->lastbrother = NULL;
				killtree(p);
			}
			else//������ֻ�б�ɾ���ڵ�
			{
				no->Childrenhead = NULL;
				no->Childrenrear = NULL;
				killtree(p);
			}
		}
	}
	Scheduler();
}
void Printpcb(string pid)
{
	PCB *p;
	p = search(initreadyhead, pid);
	if (p != NULL)
	{
		cout << "PID:" << p->PID << "  " << "Priority:" << p->Priority << "  " << "Status:" << p->Status<<"  " << "R1:"<<p->yetresource[0]<<"  "<<"R2:"<<p->yetresource[1]<<"  "<<"R3:"<<p->yetresource[2]<<"  "<<"R4:"<<p->yetresource[3]<<endl;
	}
	else
		cout << "pcb not found" << endl;
}
