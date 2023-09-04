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
	cout << "����Ա����������������" << endl;
}

bool Administrator::login()
{
	string name, pw;
	cout << "�������˺ţ�";
	cin >> name;

	while (1)
	{
		if (username == name)
		{
			cout << "���������룺";
			cin >> pw;
			cout << endl;
			if (password == pw) return true;
			else cout << "�����������������" << endl;

		}
		else
		{
			cout << "���˺Ų����ڣ�" << endl;
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
		cout << "��ѡ�������" << endl;
		cout << "1.���Ҷ���\n2.�޸Ķ���\n3.ɾ������\n4.��Ʒ��Ϣ����\n5.��Ʒ��Ϣ�޸�\n";
		cout << "6.��Ʒ��Ϣɾ��\n7.��Ʒ��Ϣ����\n8.�������ͳ��\n9.�˵�չʾ\n10.ĳ������ͳ��\n";
		cout << "0.�˳�\n";
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
		cout << "������Ҫ���ҵĶ�����ţ�";
		cin >> x;
		cout << endl;
		x--;
		if (x >= 0 && x < orders.size())
		{
			cout << "����" << x + 1 << ":" << endl;
			cout << "��ţ�"  << time << setw(3) << setfill('0') << x + 1 << endl;
			for (int i = 0; i < orders[x].size(); i++)
				cout << orders[x][i].first.getNumber() << " " << orders[x][i].first.getName() << " " << fixed << setprecision(2)
				<< orders[x][i].first.getPrice() << "Ԫ " << fixed << setprecision(1) << orders[x][i].first.getDiscount()
				<< "   " << orders[x][i].second << "��" << endl;
			cout << "��Ʒ�ܼۣ�" << totalprice[x] << endl << endl;
			if (extraFee[x] == 15)
			{
				cout << "����\n" << "�����ѣ�" << extraFee[x] << endl;

			}
			else
			{
				cout << "��ʳ" << endl;
				cout << "���ţ�" << customerTableNumber[x] << endl;
				if (extraFee[x] == 0) cout << "������" << endl;
				else cout << "����\n" << "����ѣ�" << extraFee[x] << endl;
			}
			cout << "�ܷ��ã�" << totalprice[x] + extraFee[x] << endl << endl;
		}
		else cout << "�ö��������ڣ�" << endl << endl;
	}
	else cout << "�޶���" << endl << endl;
	
}

void Administrator::change_order()
{
	
	
	if (orders.size() > 0)
	{
		calculatePrice();
		int x;
		cout << "������Ҫ�޸ĵĶ�����ţ�";
		cin >> x;
		cout << endl;
		x--;
		if (x >= 0 && x < orders.size())
		{
			cout << "����" << x + 1 << ":" << endl;
			for (int i = 0; i < orders[x].size(); i++)
				cout << orders[x][i].first.getNumber() << " " << orders[x][i].first.getName() << " " << fixed << setprecision(2)
				<< orders[x][i].first.getPrice() << "Ԫ " << fixed << setprecision(1) << orders[x][i].first.getDiscount()
				<< "   " << orders[x][i].second << "��" << endl;
			cout << "�ܼۣ�" << totalprice[x] << endl << endl ;

			string n;
			string a;
			cout << "ѡ���Ʒ��ţ�";
			cin >> n;
			cout << endl;
			if (getDishQueue(x, n) != -1)
			{
				int t = getDishQueue(x, n);
				cout << "ѡ����������޸�:";
				cin >> a;
				cout << endl;
				change_orderDishAmount(x, t, a);
				cout << "���޸ģ�" << endl;
				st[x] = 0;
				totalprice[x] = 0;
			}
			else cout << "�ò�Ʒ�����ڣ�" << endl << endl;

		}
		else cout << "�ö��������ڣ�" << endl << endl;
	}
	else cout << "�޶���" << endl << endl;
}
void Administrator::delete_order()
{
	
	
	if (orders.size() > 0)
	{
		calculatePrice();
		int x;
		cout << "������Ҫɾ���Ķ�����ţ�";
		cin >> x;
		cout << endl;
		x--;
		if (x >= 0 && x < orders.size())
		{
			
			cout << "����" << x + 1 << ":" << endl;
			for (int i = 0; i < orders[x].size(); i++)
				cout << orders[x][i].first.getNumber() << " " << orders[x][i].first.getName() << " " << fixed << setprecision(2)
				<< orders[x][i].first.getPrice() << "Ԫ " << fixed << setprecision(1) << orders[x][i].first.getDiscount()
				<< "   " << orders[x][i].second << "��" << endl;
			cout << "�ܼۣ�" << totalprice[x] << endl << endl ;

			orders.erase(orders.begin() + x);
			st.erase(st.begin() + x);
			totalprice.erase(totalprice.begin() + x);
			cout << "��ɾ����" << endl << endl;
		}
		else cout << "�ö��������ڣ�" << endl << endl;
	}
	else cout << "�޶���" << endl << endl;
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
	cout << "������Ҫ��ӵĲ�Ʒ�ı�š����ơ��۸��ۿ�:" << endl;
	cout << "(���롮x���������)" << endl;
	cout << "**********************************************" << endl;
	while(1)
	{
		cin >> number;
		if (number == "x")
		{
			cout << "������˲�Ʒ����ӣ�" << endl;
			break;
		}
		else if (find_number(number) != -1)
		{
			cout << "�ñ���ѱ�������Ʒʹ��" << endl;
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
	cout << "������Ҫɾ���Ĳ�Ʒ��ţ�" ;
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
		cout << "��ɾ��" << endl;
	}
	else cout << "�ò�Ʒ��Ų����ڣ�" << endl;
}

void Administrator::sort_menu()
{
	sort(menu.begin(), menu.end());
}
void Administrator::change_menu()
{
	string num;
	cout << "��������Ҫ�޸ĵĲ�Ʒ�ı�ţ�" ;
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
		cout << "����1��2��3��4�ֱ��޸ı�š����ơ��۸��ۿ�:" << endl;
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			string x;
			cout << "�������޸ĺ�ı�ţ�" ;
			cin >> x;
			if (find_number(x) == -1)
			{
				menu[i].change_number(x);
				cout << "�޸����" << endl;
			}
			else cout << "�ñ���Ѵ��ڣ�" << endl;
			
			break;
		}
		case 2:
		{
			string x;
			cout << "�������޸ĺ�����ƣ�" ;
			cin >> x;
			cout << "�޸����" << endl;
			menu[i].change_name(x);
			break;
		}
		case 3:
		{
			string x;
			cout << "�������޸ĺ�ļ۸�";
			cin >> x;
			cout << "�޸����" << endl;
			menu[i].change_price(x);
			break;
		}
		case 4:
		{
			string x;
			cout << "�������޸ĺ���Żݣ�" ;
			cin >> x;
			cout << "�޸����" << endl;
			menu[i].change_discount(x);
			break;
		}
		default: cout << "ʧ�ܣ�" << endl;
			break;
		}
	}
	else cout << "�ò�Ʒ��Ų����ڣ�" << endl;
	sort_menu();
}

void Administrator::show_statistics()
{
	
	if (orders.size() > 0)
	{
		calculatePrice();
		for (int i = 0; i < orders.size(); i++)
		{
			cout << "����" << i + 1 << ":" << endl;
			cout << "��ţ�" << time << setw(3) << setfill('0') << i + 1 << endl;
			for (int j = 0; j < orders[i].size(); j++)
			{
				cout << orders[i][j].first.getNumber() << " " << orders[i][j].first.getName() << " " << fixed << setprecision(2)
					<< orders[i][j].first.getPrice() << "Ԫ " << fixed << setprecision(1) << orders[i][j].first.getDiscount()
					<< "   " << orders[i][j].second << "��" << endl;
				MenuSoldAmount[find_Number(orders[i][j].first.getNumber())].second += atoi(orders[i][j].second.c_str()); 
			}
				
			cout << "��Ʒ�ܼۣ�" << totalprice[i] << endl << endl;
			if (extraFee[i] == 15)
			{
				cout << "����\n"<<"�����ѣ�"<< extraFee[i] << endl;
				
			}
			else
			{
				cout << "��ʳ" << endl;
				cout << "���ţ�" << customerTableNumber[i] << endl;
				if (extraFee[i] == 0) cout << "������" << endl;
				else cout << "����\n" << "����ѣ�" << extraFee[i] << endl;
			}
			cout << "�ܷ��ã�" << totalprice[i] + extraFee[i] << endl << endl;
			
		}
		showDailystatistics();
		
	}
	else cout << "�޶���" << endl;
	
}

void Administrator::find_menu()
{
	cout << "������Ҫ���ҵĲ�Ʒ��ţ�" ;
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
		cout << "��ţ�" << menu[i].getNumber() << " ���ƣ�" << menu[i].getName() <<
			" �۸�" << menu[i].getPrice() << " �Żݣ�" << menu[i].getDiscount() << endl;
	}
	else cout << "�ò�Ʒ��Ų����ڣ�" << endl;

}

void Administrator::show_totalMenu()
{
	if (menu.size() > 0)
	{
		for (int i = 0; i < menu.size(); i++)
		{
			cout << menu[i].getNumber() << " " << menu[i].getName() << " " << fixed << setprecision(2)
				<< menu[i].getPrice() << "Ԫ " << fixed << setprecision(1) << menu[i].getDiscount() << "" << endl;
		}
	}
	else cout << "�˵�Ϊ��" << endl;
	
}
void Administrator::out_file_totalMenu(string file_name)
{
	ofstream fout(file_name, ios::app);
	for (int i = 0; i < menu.size(); i++)
	{
		fout << menu[i].getNumber() << " " << menu[i].getName() << " " << fixed << setprecision(2)
			<< menu[i].getPrice() << "Ԫ " << fixed << setprecision(1) << menu[i].getDiscount() << endl;
		
	}
	fout.close();

}

void Administrator::out_file_totalOrder(string file_name)
{
	ofstream fout(file_name, ios::app);
	for (int i = 0; i < orders.size(); i++)
	{
		fout << "����" << i + 1 << ":" << endl;
		fout << "��ţ�" << time << setw(3) << setfill('0') << i + 1 << endl;
		for (int j = 0; j < orders[i].size(); j++)
			fout << orders[i][j].first.getNumber() << " " << orders[i][j].first.getName() << " " << fixed << setprecision(2)
			<< orders[i][j].first.getPrice() << "Ԫ " << fixed << setprecision(1) << orders[i][j].first.getDiscount()
			<< "   " << orders[i][j].second << "��" << endl;
		fout << "��Ʒ�ܼۣ�" << totalprice[i] << endl << endl;
		if (extraFee[i] == 15)
		{
			fout << "����\n" << "�����ѣ�" << extraFee[i] << endl;

		}
		else
		{
			fout << "��ʳ" << endl;
			fout << "���ţ�" << customerTableNumber[i] << endl;
			if (extraFee[i] == 0) fout << "������" << endl;
			else fout << "����\n" << "����ѣ�" << extraFee[i] << endl;
		}
		fout << "�ܷ��ã�" << totalprice[i] + extraFee[i] << endl << endl;
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

	// ��ȡ��ǰʱ���ʱ���
	time_t currentTime = std::time(nullptr);

	// ��ʱ���ת��Ϊ����ʱ��
	tm* localTime = localtime(&currentTime);

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
				<< MenuSoldAmount[i].first.getPrice() << "Ԫ " << fixed << setprecision(1) << MenuSoldAmount[i].first.getDiscount() << " "
			    << MenuSoldAmount[i].second << "��" << "" << endl;;
		}
	}
	else cout << "�˵�Ϊ��,��Ч��" << endl;
}

void Administrator::statisOneDay()
{

	string time;
	cout << "������Ҫͳ�Ƶ�����: ";
	cin >> time;
	time += ".txt";
	std::ifstream file(time);  


	if (!file.is_open()) 
	{
		std::cout << "�޷����ļ���" << std::endl;
		return ;
	}

	int orderCount = 0;
	double totalCost = 0.0;  // ���ж����ܷ���
	double dineInCost = 0.0;  // ��ʳ�����ܷ���
	double takeoutCost = 0.0;  // ���������ܷ���
	std::string line;
	while (std::getline(file, line)) 
	{
		if (line.find("����") != std::string::npos)
		{
			orderCount++;
			size_t totalPricePos = line.find("�ܷ��ã�");
			if (totalPricePos != std::string::npos) 
			{
				double cost = std::stod(line.substr(totalPricePos + 4));
				totalCost += cost;
				if (line.find("��ʳ") != std::string::npos) 
				{
					dineInCost += cost;
				}
				if (line.find("����") != std::string::npos) 
				{
					takeoutCost += cost;
				}
			}
		}
	}

	file.close();
	cout << "�������:" << endl;
	std::cout << "�ӵ�������" << orderCount << std::endl;
	std::cout << "�����۶" << totalCost << std::endl;
	std::cout << "�������۶�ռ�ȣ�" << dineInCost / totalCost << std::endl;
	std::cout << "��ʳ���۶�ռ�ȣ�" << takeoutCost / totalCost << std::endl;

	return ;
	


}
