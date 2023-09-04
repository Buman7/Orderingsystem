#include<iostream>
#include"Menu.h"
#include<iomanip>
#include<fstream>
using namespace std;

Menu::Menu(string a, string b, string c, string d)
{
	number = a;
	name = b;
	price = c;
	discount = d;
}
Menu::~Menu()
{
	//cout << "菜品" << getNumber() << ":"<<getName() << "类的析构函数被调用" << endl;
}

bool Menu::operator < (const Menu& M) const
{
	return number < M.number;
}
void Menu::out_file(string file_name)
{
	ofstream fout(file_name, ios::app);
	fout << number << " " << name << " " << fixed << setprecision(2) << price
		<< "元 " << fixed << setprecision(1) << discount << "折" << endl;
	fout.close();
}

void Menu::cout_menu()
{
	cout << setw(10) << number << setw(20) << name
		<< setw(10) << fixed << setprecision(2) << price << "元" << setw(10) << fixed
		<< setprecision(1) << discount << "折" << endl;
}

string Menu::getNumber()
{
	return number;
}
string Menu::getName()
{
	return name;
}
string Menu::getPrice()
{
	return price;
}
string Menu::getDiscount()
{
	return discount;
}

void Menu::change_number(string number)
{
	this->number = number;
}

void Menu::change_name(string name)
{
	this->name = name;
}
void Menu::change_price(string price)
{
	this->price = price;
}
void Menu::change_discount(string discount)
{
	this->discount = discount;
}
