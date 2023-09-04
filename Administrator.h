#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include<iostream>
#include<vector>
#include"Menu.h"
typedef pair<Menu, string>PMS;
typedef pair<Menu, int> PMI;
using namespace std;
class Administrator
{
public:
	Administrator(string, string);
	~Administrator();
	bool login();
	void operation();

	void add_order(vector<PMS>,double,double);
	void calculatePrice();
	void find_order();
	void change_order();
	void delete_order();

	

	int getDishQueue(int,string);
	void change_orderDishAmount(int,int,string);
	void showDailystatistics();
	void statisOneDay();
	void sort_menu();
	void add_menu();
	void change_menu();
	void delete_menu();
	void find_menu();
	int find_number(string);
	int find_Number(string);//和小写的不一样
	Menu getMenu(string);
	string getLocalTime();
	void show_statistics();
	void out_file_totalMenu(string);
	void out_file_totalOrder(string);
	void show_totalMenu();
private:
	string username;
	string password;
	string time;
	vector<Menu>menu;
	vector<vector<PMS>>orders;
	vector<double> totalprice;
	vector<int> st;
	vector<double> extraFee;
	vector<double> customerTableNumber;
	vector<PMI> MenuSoldAmount;
	
};
#endif
