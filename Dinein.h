#ifndef DINEIN_H
#define DINEIN_H

#include "Customer.h"
class Dinein : public Customer
{
public:
	Dinein();
	virtual ~Dinein();
	void setdata(double,double);
	virtual void select_dish(Administrator&) override;
	virtual void show_order() override;
	virtual vector<PMS> getCustomerOrder() override;
	double getTableNumber();
	double getRoomFee();
	bool findUsedNumber(double);
private:
	double tableNumber;
	double roomFee;
	double DTotalPrice;
	string dTime;
	static vector<double> usedTableNumber;
};

#endif

