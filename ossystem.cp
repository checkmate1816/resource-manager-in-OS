#include<iostream>
#include "definition.h"
#include<string>
#include<stdlib.h>
using namespace std;
void listready()
{
	PCB *temp;
	cout << "2:"<<endl;
	temp = systemreadyhead;
	while (temp != NULL)
	{
		if (temp != systemreadyrear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
	cout << "1:"<<endl;
	temp = userreadyhead;
	while (temp != NULL)
	{
		if (temp != userreadyrear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
	cout << "0:"<<endl;
	temp = initreadyhead;
	while (temp != NULL)
	{
		if (temp != initreadyrear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
}
void listres()
{
	RCB *temp;
	temp = &R1;
	cout << "R1:" << temp->Status<<endl;
	temp = &R2;
	cout << "R2:" << temp->Status << endl;
	temp = &R3;
	cout << "R3:" << temp->Status << endl;
	temp = &R4;
	cout << "R4:" << temp->Status << endl;
}
void listblock()
{
	PCB *temp;
	cout << "R1:"<<endl;
	temp = R1.head;
	while (temp != NULL)
	{
		if (temp != R1.rear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
	cout << "R2:"<<endl;
	temp = R2.head;
	while (temp != NULL)
	{
		if (temp != R2.rear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
	cout << "R3:" << endl;
	temp = R3.head;
	while (temp != NULL)
	{
		if (temp != R3.rear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
	cout << "R4:" << endl;
	temp = R4.head;
	while (temp != NULL)
	{
		if (temp != R4.rear)
			cout << temp->PID<<" ";
		else
			cout << temp->PID << endl;
		temp = temp->next;
	}
}
int main()
{
	string command = { '\0' };
	string target = { '\0' };
	int n = 0;
	cout << "ÇëÊäÈëÃüÁî" << endl;
	while (1)
	{
		cin >> command;
		if (command.compare("init") == 0)
			Init();
		else if (command.compare("cr") == 0)
		{
			cin >> target;
			cin >> n;
			create(target, n);
		}
		else if (command.compare("de") == 0)
		{
			cin >> target;
			Destroy(target);
		}
		else if (command.compare("req") == 0)
		{
			cin >> target;
			cin >> n;
			Request(target, n);
		}
		else if (command.compare("rel") == 0)
		{
			cin >> target;
			cin >> n;
			Release(target, n);
		}
		else if (command.compare("to") == 0)
			timeout();
		else if (command.compare("listready") == 0)
			listready();
		else if (command.compare("listblock") == 0)
			listblock();
		else if (command.compare("listres") == 0)
			listres();
		else if (command.compare("pr") == 0)
		{
			cin >> target;
			Printpcb(target);
		}
	}
	system("pasuse");
	return 0;
}



