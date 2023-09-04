#include<iostream>
#include"Interface.h"
#include"Customer.h"
#include"Administrator.h"
#include"Dinein.h"
#include"Takeaway.h"
using namespace std;

Administrator A("eee", "123456");

void virtualViaPointor(Customer* customerPtr)
{

	customerPtr->select_dish(A);
	customerPtr->show_order();
	
}

void virtualViaReference(Customer& customerRef)
{
	customerRef.select_dish(A);
	customerRef.show_order();
}
Interface::Interface()
{}
Interface::~Interface()
{
	cout << "��������������������" << endl;
}
void Interface::welcome()
{
	
	while (1)
	{
		Customer *C;
		int flag = 0;
		cout << "***************************************" << endl;
		cout << "*         " << "��ѡ�����ȷ����ݣ�  " << "      " << "*" << endl;
		cout << "*             " << "1.����Ա" << "                " << "*" << endl;
		cout << "*             " << "2.�˿�" << "                  " << "*" << endl;
		cout << "*             " << "3.�˳�" << "                  " << "*" << endl;
		cout << "***************************************" << endl;
		int op;
		cin >> op;
		switch (op)
		{
		case 1: 
		{
			if (A.login())
			{
				cout << "����Ա����" << endl;
				A.operation();
			}
			break;
		}

		case 2:
		{
			int op;
			cout << "�˿�����,����Ϊ�˵�" << endl;
			A.show_totalMenu();
			cout << "********************" << endl;
			cout << "��ѡ�����ѷ�ʽ��" << endl;
			cout << "1.��ʳ" << endl;
			cout << "2.����" << endl;
			cin >> op;
			if (op == 1)
			{
				Dinein d;
				C = &d;
				virtualViaPointor(C);
				A.add_order(d.getCustomerOrder(),d.getTableNumber(),d.getRoomFee());
			}
			else if (op == 2)
			{
				Takeaway t;
				C = &t;
				virtualViaPointor(C);
				A.add_order(t.getCustomerOrder(), 0, 15);
			}
			else cout << "ʧ�ܣ�" << endl;
			break;
		}

		default:
		{
			flag = 1;
			cout << "ʧ�ܣ�" << endl;
			break;
		}
		}
		if (flag) break;
	}
	
}
