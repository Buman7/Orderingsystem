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
	cout << "界面类析构函数被调用" << endl;
}
void Interface::welcome()
{
	
	while (1)
	{
		Customer *C;
		int flag = 0;
		cout << "***************************************" << endl;
		cout << "*         " << "请选择序号确定身份：  " << "      " << "*" << endl;
		cout << "*             " << "1.管理员" << "                " << "*" << endl;
		cout << "*             " << "2.顾客" << "                  " << "*" << endl;
		cout << "*             " << "3.退出" << "                  " << "*" << endl;
		cout << "***************************************" << endl;
		int op;
		cin >> op;
		switch (op)
		{
		case 1: 
		{
			if (A.login())
			{
				cout << "管理员您好" << endl;
				A.operation();
			}
			break;
		}

		case 2:
		{
			int op;
			cout << "顾客您好,以下为菜单" << endl;
			A.show_totalMenu();
			cout << "********************" << endl;
			cout << "请选择消费方式：" << endl;
			cout << "1.堂食" << endl;
			cout << "2.外卖" << endl;
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
			else cout << "失败！" << endl;
			break;
		}

		default:
		{
			flag = 1;
			cout << "失败！" << endl;
			break;
		}
		}
		if (flag) break;
	}
	
}
