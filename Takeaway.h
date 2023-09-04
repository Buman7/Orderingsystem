#ifndef TAKEAWAY_H
#define TAKEAWAY_H
#include"Customer.h"
class Takeaway : public Customer
{
public:
	Takeaway();
	virtual ~Takeaway();
	void setdata(string, string, string);
	virtual void select_dish(Administrator&) override;
	virtual void show_order() override;
	virtual vector<PMS> getCustomerOrder() override;
private:
	double taFee;
	string taTime;
	string taPosition;
	string taPhoneNumber;
	double TTotalPrice;

};
#endif
