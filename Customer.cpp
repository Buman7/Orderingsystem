#include<iostream>
#include"Customer.h"
#include"Menu.h"
#include"Administrator.h"
#include<stdlib.h>
#include<algorithm>
#include<iomanip>
#include <ctime>
#include <sstream>
using namespace std;

int Customer::orderNumber = 0;
Customer::Customer()
{
	totalPrice = 0;
}
Customer::~Customer()
{
	cout << "�˿�����������������" << endl;
}
void Customer::select_dish(Administrator& A)
{
	
	cout << "��������Ҫѡ��Ĳ�Ʒ��ż�����(���롮x���˳�)" << endl;
	while (1)
	{
		string number, amount;
		cin >> number;
		if (number == "x") break;
		int x = A.find_number(number);
		if (x != -1)
		{
			cin >> amount;
			PMS p = { A.getMenu(number),amount };
			customer_dish.push_back(p);
		}
		else cout << "�ò�Ʒ�����ڣ�" << endl;

	}
	sort(customer_dish.begin(), customer_dish.end());
	for (int i = 0; i < customer_dish.size(); i++)
	{
		string p = customer_dish[i].first.getPrice();
		string a = customer_dish[i].second;
		string d = customer_dish[i].first.getDiscount();
		double price = atof(p.c_str());
		double discount = atof(d.c_str());
		price *= discount;
		int amount = atoi(a.c_str());
		totalPrice += price * amount;
	}


}
void Customer::show_order()
{
	for (int i = 0; i < customer_dish.size(); i++)
	{
		cout << customer_dish[i].first.getNumber() << " " << customer_dish[i].first.getName() << " " << fixed << setprecision(2)
			<< customer_dish[i].first.getPrice() << "Ԫ " << fixed << setprecision(1) << customer_dish[i].first.getDiscount() 
			<< "��   "<< customer_dish[i].second <<"��" << endl;
	}
	cout << "��Ʒ�ܼۣ�" << totalPrice << endl;
}
vector<PMS> Customer::getCustomerOrder()
{
	return customer_dish;
}

double Customer::getTotalPrice()
{
	return totalPrice;
}

string Customer::getLocalTime()
{

	// ��ȡ��ǰʱ���ʱ���
	time_t currentTime = std::time(nullptr);

	// ��ʱ���ת��Ϊ����ʱ��
	tm* localTime = std::localtime(&currentTime);

	// ��ȡ�ꡢ�¡�����Ϣ
	int year = localTime->tm_year + 1900;   // tm_year��ʾ��1900�꿪ʼ������
	int month = localTime->tm_mon + 1;      // tm_mon��ʾ��0��ʼ������
	int day = localTime->tm_mday;           // tm_mday��ʾһ�����еĵڼ���

	// ʹ��ostringstream���������ַ���
	ostringstream oss;
	oss << year;

	// ����·ݻ������Ǹ�λ������ǰ�油��
	if (month < 10)
		oss << "0";
	oss << month;

	if (day < 10)
		oss << "0";
	oss << day;

	// ��ostringstream�����л�ȡ�����ַ���
	string dateString = oss.str();

	// �����ǰ�����ַ���
	//cout << "��ǰ���ڣ�" << dateString << std::endl;

	return dateString;
	
}