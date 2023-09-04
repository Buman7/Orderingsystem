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
	cout << "堂食类析构函数被调用！" << endl;
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
		else cout << "包厢号和包厢费必须合法！\n";
	}
	
}

void Dinein::select_dish(Administrator&A)
{
	double x,op;
	Customer::select_dish(A);
	while (1)
	{
		cout << "请选择桌号： ";
		cin >> x;
		if (!findUsedNumber(x))
		{
			usedTableNumber.push_back(x);
			cout << "是否包厢：  1.是  2.否" << endl;
			cin >> op;
			if (op == 1) setdata(x, 20);
			else setdata(x, 0);
			DTotalPrice = roomFee + Customer::getTotalPrice();
			break;
		}
		else cout << "该桌号无法使用！" << endl;
	}
}

void Dinein::show_order()
{
	cout << "编号：" << endl << dTime << setw(3) << setfill('0') << orderNumber << endl;
	Customer::show_order();
	cout << "餐桌号： " << tableNumber << endl;
	cout << "是否有包厢费： ";
	if (roomFee > 0) cout << "是" << endl;
	else cout << "否" << endl;
	cout << "包厢费： " << roomFee << endl;
	cout << "总价：" << DTotalPrice << endl;
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
		cout << "桌号必须合法！" << endl;
		return true;
	}
	
	
}