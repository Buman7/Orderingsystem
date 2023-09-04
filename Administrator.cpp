#include<iostream>
#include"Administrator.h"
#include"Menu.h"
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include <ctime>
#include <sstream>
#include<stdlib.h>
using namespace std;


Administrator::Administrator(string name, string pw)
	: username(name), password(pw)
{
	time = getLocalTime();
}
Administrator::~Administrator()
{
	cout << "管理员类析构函数被调用" << endl;
}

bool Administrator::login()
{
	string name, pw;
	cout << "请输入账号：";
	cin >> name;

	while (1)
	{
		if (username == name)
		{
			cout << "请输入密码：";
			cin >> pw;
			cout << endl;
			if (password == pw) return true;
			else cout << "密码错误！请重新输入" << endl;

		}
		else
		{
			cout << "该账号不存在！" << endl;
			return false;
		}
	}
}

void Administrator::operation()
{
	
	string timetxt = time + ".txt";
	while (1)
	{
		int op;
		int flag = 1;
		cout << "******************" << endl;
		cout << "请选择操作：" << endl;
		cout << "1.查找订单\n2.修改订单\n3.删除订单\n4.菜品信息增加\n5.菜品信息修改\n";
		cout << "6.菜品信息删除\n7.菜品信息查找\n8.销售情况统计\n9.菜单展示\n10.某日销售统计\n";
		cout << "0.退出\n";
		cout << "******************" << endl;
		
		cin >> op;
		switch (op)
		{
		case 1: find_order();
			break;
		case 2: change_order();
			break;
		case 3: delete_order();
			break;
		case 4: add_menu();
			break;
		case 5: change_menu();
			break;
		case 6: delete_menu();
			break;
		case 7: find_menu();
			break;
		case 8: show_statistics();
			break;
		case 9: show_totalMenu();
			break;
		case 10: statisOneDay();
			break;
		case 0:flag = 0;
			break;
		default:
			break;
		}
		if (!flag) break;
	}
	
	out_file_totalMenu("menu.txt");
	out_file_totalOrder(timetxt);
}

void Administrator::add_order(vector<PMS> v,double ctn,double ef)
{
	orders.push_back(v);
	extraFee.push_back(ef); 
	customerTableNumber.push_back(ctn);
	st.push_back(0);
	totalprice.push_back(0);
}

void Administrator::calculatePrice()
{
	for (int i = 0; i < orders.size(); i++)
	{
		for (int j = 0; j < orders[i].size(); j++)
		{
			string p = orders[i][j].first.getPrice();
			string a = orders[i][j].second;
			string d = orders[i][j].first.getDiscount();
			double price = atof(p.c_str());
			double discount = atof(d.c_str());
			price *= discount;
			int amount = atoi(a.c_str());
			if(!st[i]) totalprice[i] += price * amount;
		}
		st[i] = 1;
	}
}
void Administrator::find_order()
{
	
	if (orders.size() > 0)
	{
		calculatePrice();
		int x;
		cout << "请输入要查找的订单编号：";
		cin >> x;
		cout << endl;
		x--;
		if (x >= 0 && x < orders.size())
		{
			cout << "订单" << x + 1 << ":" << endl;
			cout << "编号："  << time << setw(3) << setfill('0') << x + 1 << endl;
			for (int i = 0; i < orders[x].size(); i++)
				cout << orders[x][i].first.getNumber() << " " << orders[x][i].first.getName() << " " << fixed << setprecision(2)
				<< orders[x][i].first.getPrice() << "元 " << fixed << setprecision(1) << orders[x][i].first.getDiscount()
				<< "   " << orders[x][i].second << "份" << endl;
			cout << "菜品总价：" << totalprice[x] << endl << endl;
			if (extraFee[x] == 15)
			{
				cout << "外卖\n" << "外卖费：" << extraFee[x] << endl;

			}
			else
			{
				cout << "堂食" << endl;
				cout << "桌号：" << customerTableNumber[x] << endl;
				if (extraFee[x] == 0) cout << "不包厢" << endl;
				else cout << "包厢\n" << "包厢费：" << extraFee[x] << endl;
			}
			cout << "总费用：" << totalprice[x] + extraFee[x] << endl << endl;
		}
		else cout << "该订单不存在！" << endl << endl;
	}
	else cout << "无订单" << endl << endl;
	
}

void Administrator::change_order()
{
	
	
	if (orders.size() > 0)
	{
		calculatePrice();
		int x;
		cout << "请输入要修改的订单编号：";
		cin >> x;
		cout << endl;
		x--;
		if (x >= 0 && x < orders.size())
		{
			cout << "订单" << x + 1 << ":" << endl;
			for (int i = 0; i < orders[x].size(); i++)
				cout << orders[x][i].first.getNumber() << " " << orders[x][i].first.getName() << " " << fixed << setprecision(2)
				<< orders[x][i].first.getPrice() << "元 " << fixed << setprecision(1) << orders[x][i].first.getDiscount()
				<< "   " << orders[x][i].second << "份" << endl;
			cout << "总价：" << totalprice[x] << endl << endl ;

			string n;
			string a;
			cout << "选择菜品编号：";
			cin >> n;
			cout << endl;
			if (getDishQueue(x, n) != -1)
			{
				int t = getDishQueue(x, n);
				cout << "选择份数进行修改:";
				cin >> a;
				cout << endl;
				change_orderDishAmount(x, t, a);
				cout << "已修改！" << endl;
				st[x] = 0;
				totalprice[x] = 0;
			}
			else cout << "该菜品不存在！" << endl << endl;

		}
		else cout << "该订单不存在！" << endl << endl;
	}
	else cout << "无订单" << endl << endl;
}
void Administrator::delete_order()
{
	
	
	if (orders.size() > 0)
	{
		calculatePrice();
		int x;
		cout << "请输入要删除的订单编号：";
		cin >> x;
		cout << endl;
		x--;
		if (x >= 0 && x < orders.size())
		{
			
			cout << "订单" << x + 1 << ":" << endl;
			for (int i = 0; i < orders[x].size(); i++)
				cout << orders[x][i].first.getNumber() << " " << orders[x][i].first.getName() << " " << fixed << setprecision(2)
				<< orders[x][i].first.getPrice() << "元 " << fixed << setprecision(1) << orders[x][i].first.getDiscount()
				<< "   " << orders[x][i].second << "份" << endl;
			cout << "总价：" << totalprice[x] << endl << endl ;

			orders.erase(orders.begin() + x);
			st.erase(st.begin() + x);
			totalprice.erase(totalprice.begin() + x);
			cout << "已删除！" << endl << endl;
		}
		else cout << "该订单不存在！" << endl << endl;
	}
	else cout << "无订单" << endl << endl;
}

int Administrator::getDishQueue(int x,string n)
{
	for (int i = 0; i < orders[x].size(); i++)
		if (n == orders[x][i].first.getNumber()) return i;
	return -1;
}
void Administrator::change_orderDishAmount(int x,int t,string a)
{
	orders[x][t].second = a;
}
void Administrator::add_menu()
{
	string number, name, price, discount;
	cout << "**********************************************" << endl;
	cout << "请输入要添加的菜品的编号、名称、价格、折扣:" << endl;
	cout << "(输入‘x’结束添加)" << endl;
	cout << "**********************************************" << endl;
	while(1)
	{
		cin >> number;
		if (number == "x")
		{
			cout << "你结束了菜品的添加！" << endl;
			break;
		}
		else if (find_number(number) != -1)
		{
			cout << "该编号已被其他菜品使用" << endl;
		}
		else
		{
			cin >> name >> price >> discount;
			Menu m(number, name, price, discount);
			menu.push_back(m);
			MenuSoldAmount.push_back({m,0});
		}
		
	}
		sort_menu();
	
}
void Administrator::delete_menu()
{
	string num;
	cout << "请输入要删除的菜品编号：" ;
	cin >> num;
	cout << endl;
	int i = 0,flag = 0;
	for ( i = 0; i < menu.size(); i++)
	{
		if (num == menu[i].getNumber())
		{
			flag = 1;
			break;
		}
	}
	sort_menu();
	if (flag)
	{
		menu.erase(menu.begin() + i);
		cout << "已删除" << endl;
	}
	else cout << "该菜品编号不存在！" << endl;
}

void Administrator::sort_menu()
{
	sort(menu.begin(), menu.end());
}
void Administrator::change_menu()
{
	string num;
	cout << "请输入需要修改的菜品的编号：" ;
	cin >> num;
	cout << endl;
	int i = 0, flag = 0;
	for (i = 0; i < menu.size(); i++)
	{
		if (num == menu[i].getNumber())
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		cout << "输入1、2、3、4分别修改编号、名称、价格、折扣:" << endl;
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			string x;
			cout << "请输入修改后的编号：" ;
			cin >> x;
			if (find_number(x) == -1)
			{
				menu[i].change_number(x);
				cout << "修改完成" << endl;
			}
			else cout << "该编号已存在！" << endl;
			
			break;
		}
		case 2:
		{
			string x;
			cout << "请输入修改后的名称：" ;
			cin >> x;
			cout << "修改完成" << endl;
			menu[i].change_name(x);
			break;
		}
		case 3:
		{
			string x;
			cout << "请输入修改后的价格：";
			cin >> x;
			cout << "修改完成" << endl;
			menu[i].change_price(x);
			break;
		}
		case 4:
		{
			string x;
			cout << "请输入修改后的优惠：" ;
			cin >> x;
			cout << "修改完成" << endl;
			menu[i].change_discount(x);
			break;
		}
		default: cout << "失败！" << endl;
			break;
		}
	}
	else cout << "该菜品编号不存在！" << endl;
	sort_menu();
}

void Administrator::show_statistics()
{
	
	if (orders.size() > 0)
	{
		calculatePrice();
		for (int i = 0; i < orders.size(); i++)
		{
			cout << "订单" << i + 1 << ":" << endl;
			cout << "编号：" << time << setw(3) << setfill('0') << i + 1 << endl;
			for (int j = 0; j < orders[i].size(); j++)
			{
				cout << orders[i][j].first.getNumber() << " " << orders[i][j].first.getName() << " " << fixed << setprecision(2)
					<< orders[i][j].first.getPrice() << "元 " << fixed << setprecision(1) << orders[i][j].first.getDiscount()
					<< "   " << orders[i][j].second << "份" << endl;
				MenuSoldAmount[find_Number(orders[i][j].first.getNumber())].second += atoi(orders[i][j].second.c_str()); 
			}
				
			cout << "菜品总价：" << totalprice[i] << endl << endl;
			if (extraFee[i] == 15)
			{
				cout << "外卖\n"<<"外卖费："<< extraFee[i] << endl;
				
			}
			else
			{
				cout << "堂食" << endl;
				cout << "桌号：" << customerTableNumber[i] << endl;
				if (extraFee[i] == 0) cout << "不包厢" << endl;
				else cout << "包厢\n" << "包厢费：" << extraFee[i] << endl;
			}
			cout << "总费用：" << totalprice[i] + extraFee[i] << endl << endl;
			
		}
		showDailystatistics();
		
	}
	else cout << "无订单" << endl;
	
}

void Administrator::find_menu()
{
	cout << "请输入要查找的菜品编号：" ;
	string num;
	cin >> num;
	cout << endl;
	int i = 0, flag = 0;
	for (i = 0; i < menu.size(); i++)
	{
		if (num == menu[i].getNumber())
		{
			flag = 1;
			break;
		}
	}

	if (flag)
	{
		cout << "编号：" << menu[i].getNumber() << " 名称：" << menu[i].getName() <<
			" 价格：" << menu[i].getPrice() << " 优惠：" << menu[i].getDiscount() << endl;
	}
	else cout << "该菜品编号不存在！" << endl;

}

void Administrator::show_totalMenu()
{
	if (menu.size() > 0)
	{
		for (int i = 0; i < menu.size(); i++)
		{
			cout << menu[i].getNumber() << " " << menu[i].getName() << " " << fixed << setprecision(2)
				<< menu[i].getPrice() << "元 " << fixed << setprecision(1) << menu[i].getDiscount() << "" << endl;
		}
	}
	else cout << "菜单为空" << endl;
	
}
void Administrator::out_file_totalMenu(string file_name)
{
	ofstream fout(file_name, ios::app);
	for (int i = 0; i < menu.size(); i++)
	{
		fout << menu[i].getNumber() << " " << menu[i].getName() << " " << fixed << setprecision(2)
			<< menu[i].getPrice() << "元 " << fixed << setprecision(1) << menu[i].getDiscount() << endl;
		
	}
	fout.close();

}

void Administrator::out_file_totalOrder(string file_name)
{
	ofstream fout(file_name, ios::app);
	for (int i = 0; i < orders.size(); i++)
	{
		fout << "订单" << i + 1 << ":" << endl;
		fout << "编号：" << time << setw(3) << setfill('0') << i + 1 << endl;
		for (int j = 0; j < orders[i].size(); j++)
			fout << orders[i][j].first.getNumber() << " " << orders[i][j].first.getName() << " " << fixed << setprecision(2)
			<< orders[i][j].first.getPrice() << "元 " << fixed << setprecision(1) << orders[i][j].first.getDiscount()
			<< "   " << orders[i][j].second << "份" << endl;
		fout << "菜品总价：" << totalprice[i] << endl << endl;
		if (extraFee[i] == 15)
		{
			fout << "外卖\n" << "外卖费：" << extraFee[i] << endl;

		}
		else
		{
			fout << "堂食" << endl;
			fout << "桌号：" << customerTableNumber[i] << endl;
			if (extraFee[i] == 0) fout << "不包厢" << endl;
			else fout << "包厢\n" << "包厢费：" << extraFee[i] << endl;
		}
		fout << "总费用：" << totalprice[i] + extraFee[i] << endl << endl;
	}
	fout.close();
}

int Administrator::find_number(string num)
{
	for (int i = 0; i < menu.size(); i++)
		if (num == menu[i].getNumber()) return i;
			
	return -1;
}

int Administrator::find_Number(string num)
{
	for (int i = 0; i < MenuSoldAmount.size(); i++)
		if (num == MenuSoldAmount[i].first.getNumber()) return i;

	return -1;
}

Menu Administrator::getMenu(string number)
{
	for (int i = 0; i < menu.size(); i++)
	{
		if (number == menu[i].getNumber()) return menu[i];
	}
}

string Administrator::getLocalTime()
{

	// 获取当前时间的时间戳
	time_t currentTime = std::time(nullptr);

	// 将时间戳转换为本地时间
	tm* localTime = localtime(&currentTime);

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

bool cmp(PMI& a, PMI& b)
{
	return a.second > b.second;
}
void Administrator::showDailystatistics()
{
	sort(MenuSoldAmount.begin(), MenuSoldAmount.end(), cmp);
	if (MenuSoldAmount.size() > 0)
	{
		for (int i = 0; i < MenuSoldAmount.size(); i++)
		{
			cout << MenuSoldAmount[i].first.getNumber() << " " << MenuSoldAmount[i].first.getName() << " " << fixed << setprecision(2)
				<< MenuSoldAmount[i].first.getPrice() << "元 " << fixed << setprecision(1) << MenuSoldAmount[i].first.getDiscount() << " "
			    << MenuSoldAmount[i].second << "份" << "" << endl;;
		}
	}
	else cout << "菜单为空,无效！" << endl;
}

void Administrator::statisOneDay()
{

	string time;
	cout << "请输入要统计的日期: ";
	cin >> time;
	time += ".txt";
	std::ifstream file(time);  


	if (!file.is_open()) 
	{
		std::cout << "无法打开文件。" << std::endl;
		return ;
	}

	int orderCount = 0;
	double totalCost = 0.0;  // 所有订单总费用
	double dineInCost = 0.0;  // 堂食订单总费用
	double takeoutCost = 0.0;  // 外卖订单总费用
	std::string line;
	while (std::getline(file, line)) 
	{
		if (line.find("订单") != std::string::npos)
		{
			orderCount++;
			size_t totalPricePos = line.find("总费用：");
			if (totalPricePos != std::string::npos) 
			{
				double cost = std::stod(line.substr(totalPricePos + 4));
				totalCost += cost;
				if (line.find("堂食") != std::string::npos) 
				{
					dineInCost += cost;
				}
				if (line.find("外卖") != std::string::npos) 
				{
					takeoutCost += cost;
				}
			}
		}
	}

	file.close();
	cout << "销售情况:" << endl;
	std::cout << "接单总数：" << orderCount << std::endl;
	std::cout << "总销售额：" << totalCost << std::endl;
	std::cout << "外卖销售额占比：" << dineInCost / totalCost << std::endl;
	std::cout << "堂食销售额占比：" << takeoutCost / totalCost << std::endl;

	return ;
	


}
