#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<iostream>
#include"Menu.h"
#include<vector>
#include"Administrator.h"

typedef pair<Menu, string>PMS;
using namespace std;

class Customer
{
public:
	Customer();
	virtual ~Customer();
	virtual void select_dish(Administrator&);
	virtual void show_order();
	virtual vector<PMS> getCustomerOrder();
	string getLocalTime();
	double getTotalPrice();
	static int orderNumber;
private:
	double totalPrice;
	vector<PMS> customer_dish;

};
#endif
