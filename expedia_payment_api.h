#ifndef EXPEDIA_PAYMENT_API_H_INCLUDED
#define EXPEDIA_PAYMENT_API_H_INCLUDED
#include <iostream>
#include "json.hpp"
using std::string;


using namespace json;

class PayPalCreditCard {
public:
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
};

class PayPalOnlinePaymentAPI {
public:
	void SetCardInfo(const PayPalCreditCard* const card) {
	}
	bool MakePayment(double money) {
		return true;
	}
};

class StripeUserInfo {
public:
	string name;
	string address;
};

class StripeCardInfo {
public:
	string id;
	string expiry_date;
};

class StripePaymentAPI {
public:
	bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money) {
		return true;
	}
};

class SquarePaymentAPI {
public:
	bool static WithDrawMoney(string JsonQuery) {
		//cout << JsonQuery << "\n";
		json::JSON obj = JSON::Load(JsonQuery);
		return true;
	}
};

////////////////////////////////
// now we have to make a general api for us that handles this
// then we process each one and deal with it

class IPayment {
public:
	virtual void SetUserInfo(string name, string address) = 0;
	virtual void SetCardInfo(string id, string expiry_date, int ccv) = 0;
	virtual bool MakePayment(double money) = 0;
	virtual ~IPayment() {
	}
};

// then with each credit card , we inherit from this general api
// so our site have a vector of pointers to this parent
// but it also can handle each call with the right process ( POWER OF POLYMORPHISM)

class PayPalPayment : public IPayment {
private:
   PayPalOnlinePaymentAPI paypal;
	PayPalCreditCard card;
public:
    virtual void SetUserInfo(string name, string address) ;

	virtual void SetCardInfo(string id, string expiry_date, int ccv);
	virtual bool MakePayment(double money) ;

};
class StripePayment: public IPayment {
private:
	StripeCardInfo card;
	StripeUserInfo user;
public:
	virtual void SetUserInfo(string name, string address) ;
	virtual void SetCardInfo(string id, string expiry_date, int ccv) ;
	virtual bool MakePayment(double money) ;
};

class SquarePayment: public IPayment {
private:
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;

public:
	virtual void SetUserInfo(string name_, string address_);
	virtual void SetCardInfo(string id_, string expiry_date_, int ccv_) ;
	virtual bool MakePayment(double money) ;
};

// we handle all by factory design pattern

class PaymentFactory {
public:
	static IPayment* GetPaymentHelper() {
		if (true)
			return new SquarePayment();
		else if (true)
			return new PayPalPayment();
		else
			return new StripePayment();
	}
};




#endif // EXPEDIA_PAYMENT_API_H_INCLUDED
