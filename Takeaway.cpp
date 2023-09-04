#include"Takeaway.h"
#include<iomanip>


Takeaway::Takeaway()
	:Customer(),taFee(15),taTime("空"), taPosition("空"), taPhoneNumber("空"), TTotalPrice(0)
{
	orderNumber++;
}

Takeaway::~Takeaway()
{
	cout << "外卖类析构函数被调用！" << endl;
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

	cout << "请输入送餐时间、送餐地点、手机号： " << endl;
	cin >> time >> position >> phonenumber;
	setdata(time, position, phonenumber);
	TTotalPrice = taFee + Customer::getTotalPrice();
	cout << endl;
}

void Takeaway::show_order()
{
	
	cout << "编号：" << endl << Customer::getLocalTime() << setw(3) << setfill('0') << orderNumber << endl;
	cout << "所点菜单：" << endl;
	Customer::show_order();
	cout << "送餐时间： "<< taTime << endl;
	cout << "送餐地点： " << taPosition << endl;
	cout << "联系电话： " << taPhoneNumber << endl;
	cout << "外卖服务费： " << taFee << endl;
	cout << "总价：" << TTotalPrice << endl;
}

vector<PMS> Takeaway::getCustomerOrder()
{
	return Customer::getCustomerOrder();
}