#ifndef MENU_H
#define MENU_H
#include<iostream>
#include<vector>
using namespace std;
class Menu
{
public:
	Menu(string a, string b, string c, string d);
	~Menu();

	bool operator < (const Menu &) const;
	void out_file(string file_name);
	void cout_menu();
	string getNumber();
	string getName();
	string getPrice();
	string getDiscount();


	void change_number(string);
	void change_name(string);
	void change_price(string);
	void change_discount(string);

private:
	string number;
	string name;
	string price;
	string discount;
};
#endif

