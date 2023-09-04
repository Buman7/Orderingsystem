#include"Takeaway.h"
#include<iomanip>


Takeaway::Takeaway()
	:Customer(),taFee(15),taTime("��"), taPosition("��"), taPhoneNumber("��"), TTotalPrice(0)
{
	orderNumber++;
}

Takeaway::~Takeaway()
{
	cout << "�������������������ã�" << endl;
}

void Takeaway::setdata(string time, string position, string phonenumber)
{
	taTime = time;
	taPosition = position;
	taPhoneNumber = phonenumber;
}
void Takeaway::select_dish(Administrator& A)
{
	string time, position, phonenumber;
	Customer::select_dish(A);

	cout << "�������Ͳ�ʱ�䡢�Ͳ͵ص㡢�ֻ��ţ� " << endl;
	cin >> time >> position >> phonenumber;
	setdata(time, position, phonenumber);
	TTotalPrice = taFee + Customer::getTotalPrice();
	cout << endl;
}

void Takeaway::show_order()
{
	
	cout << "��ţ�" << endl << Customer::getLocalTime() << setw(3) << setfill('0') << orderNumber << endl;
	cout << "����˵���" << endl;
	Customer::show_order();
	cout << "�Ͳ�ʱ�䣺 "<< taTime << endl;
	cout << "�Ͳ͵ص㣺 " << taPosition << endl;
	cout << "��ϵ�绰�� " << taPhoneNumber << endl;
	cout << "��������ѣ� " << taFee << endl;
	cout << "�ܼۣ�" << TTotalPrice << endl;
}

vector<PMS> Takeaway::getCustomerOrder()
{
	return Customer::getCustomerOrder();
}