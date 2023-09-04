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
	//cout << "��Ʒ" << getNumber() << ":"<<getName() << "�����������������" << endl;
}

bool Menu::operator < (const Menu& M) const
{
	return number < M.number;
}
void Menu::out_file(string file_name)
{
	ofstream fout(file_name, ios::app);
	fout << number << " " << name << " " << fixed << setprecision(2) << price
		<< "Ԫ " << fixed << setprecision(1) << discount << "��" << endl;
	fout.close();
}

void Menu::cout_menu()
{
	cout << setw(10) << number << setw(20) << name
		<< setw(10) << fixed << setprecision(2) << price << "Ԫ" << setw(10) << fixed
		<< setprecision(1) << discount << "��" << endl;
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
