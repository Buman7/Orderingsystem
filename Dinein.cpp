#include "Dinein.h"
#include<iomanip>
vector<double>Dinein::usedTableNumber;
Dinein::Dinein()
	:Customer(),tableNumber(0),roomFee(0),DTotalPrice(0)
{
	dTime = Customer::getLocalTime();
	orderNumber++;
}

Dinein::~Dinein()
{
	cout << "��ʳ���������������ã�" << endl;
}

void Dinein::setdata(double n, double f)
{
	while (1)
	{
		if (n >= 1 && f >= 0)
		{
			tableNumber = n;
			roomFee = f;
			break;
		}
		else cout << "����źͰ���ѱ���Ϸ���\n";
	}
	
}

void Dinein::select_dish(Administrator&A)
{
	double x,op;
	Customer::select_dish(A);
	while (1)
	{
		cout << "��ѡ�����ţ� ";
		cin >> x;
		if (!findUsedNumber(x))
		{
			usedTableNumber.push_back(x);
			cout << "�Ƿ���᣺  1.��  2.��" << endl;
			cin >> op;
			if (op == 1) setdata(x, 20);
			else setdata(x, 0);
			DTotalPrice = roomFee + Customer::getTotalPrice();
			break;
		}
		else cout << "�������޷�ʹ�ã�" << endl;
	}
}

void Dinein::show_order()
{
	cout << "��ţ�" << endl << dTime << setw(3) << setfill('0') << orderNumber << endl;
	Customer::show_order();
	cout << "�����ţ� " << tableNumber << endl;
	cout << "�Ƿ��а���ѣ� ";
	if (roomFee > 0) cout << "��" << endl;
	else cout << "��" << endl;
	cout << "����ѣ� " << roomFee << endl;
	cout << "�ܼۣ�" << DTotalPrice << endl;
}

vector<PMS> Dinein::getCustomerOrder()
{
	return Customer::getCustomerOrder();
}

double Dinein::getTableNumber()
{
	return tableNumber;
}

double Dinein::getRoomFee()
{
	return roomFee;
}

bool Dinein::findUsedNumber(double x)
{
	if (x > 0)
	{
		if (usedTableNumber.size() > 0)
		{
			for (int i = 0; i < usedTableNumber.size(); i++)
				if (x == usedTableNumber[i]) return true;
			return false;
		}
		else return false;
	}
	else
	{
		cout << "���ű���Ϸ���" << endl;
		return true;
	}
	
	
}