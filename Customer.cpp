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
	cout << "顾客类析构函数被调用" << endl;
}
void Customer::select_dish(Administrator& A)
{
	
	cout << "请输入您要选择的菜品编号及份数(输入‘x’退出)" << endl;
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
		else cout << "该菜品不存在！" << endl;

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
			<< customer_dish[i].first.getPrice() << "元 " << fixed << setprecision(1) << customer_dish[i].first.getDiscount() 
			<< "折   "<< customer_dish[i].second <<"份" << endl;
	}
	cout << "菜品总价：" << totalPrice << endl;
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

	// 获取当前时间的时间戳
	time_t currentTime = std::time(nullptr);

	// 将时间戳转换为本地时间
	tm* localTime = std::localtime(&currentTime);

	// 提取年、月、日信息
	int year = localTime->tm_year + 1900;   // tm_year表示从1900年开始的年数
	int month = localTime->tm_mon + 1;      // tm_mon表示从0开始的月数
	int day = localTime->tm_mday;           // tm_mday表示一个月中的第几天

	// 使用ostringstream构建日期字符串
	ostringstream oss;
	oss << year;

	// 如果月份或日期是个位数，在前面补零
	if (month < 10)
		oss << "0";
	oss << month;

	if (day < 10)
		oss << "0";
	oss << day;

	// 从ostringstream对象中获取日期字符串
	string dateString = oss.str();

	// 输出当前日期字符串
	//cout << "当前日期：" << dateString << std::endl;

	return dateString;
	
}