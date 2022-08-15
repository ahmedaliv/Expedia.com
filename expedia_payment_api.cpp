#include "expedia_payment_api.h"
#include "sstream"
using std::ostringstream;
using std::istringstream;

//PayPalPayment Function

void PayPalPayment::SetUserInfo(string name, string address) {
		card.name = name;
		card.address = address;
	}
 void PayPalPayment::SetCardInfo(string id, string expiry_date, int ccv) {
		card.id = id;
		card.expiry_date = expiry_date;
		card.ccv = ccv;
	}
 bool PayPalPayment::MakePayment(double money) {
		paypal.SetCardInfo(&card);
		return paypal.MakePayment(money);
	}



// StripePayment Functions

 void StripePayment::SetUserInfo(string name, string address) {
		user.name = name;
		user.address = address;
	}
	 void StripePayment::SetCardInfo(string id, string expiry_date, int ccv) {
		card.id = id;
		card.expiry_date = expiry_date;
	}
	 bool StripePayment::MakePayment(double money) {
		return StripePaymentAPI::WithDrawMoney(user, card, money);
	}



// SquarePayment Functions

 void SquarePayment::SetUserInfo(string name_, string address_) {
		name = name_;
		address = address_;
	}
	 void SquarePayment::SetCardInfo(string id_, string expiry_date_, int ccv_) {
		id = id_;
		expiry_date = expiry_date_;
		ccv = ccv_;
	}
	 bool SquarePayment::MakePayment(double money) {
		// This now similar to Adapter pattern. We change format of interface to match another interface
		json::JSON obj;
		obj["user_info"] = json::Array(name, address);
		obj["card_info"]["ID"] = id;
		obj["card_info"]["DATE"] = expiry_date;
		obj["card_info"]["CCV"] = ccv;
		obj["money"] = money;

		ostringstream oss;
		oss << obj;
		string json_query = oss.str();

		return SquarePaymentAPI::WithDrawMoney(json_query);
	}

