#ifndef EXPEDIA_PAYMENT_CARD_H_INCLUDED
#define EXPEDIA_PAYMENT_CARD_H_INCLUDED
#include <iostream>
using std::string;
class PaymentCard {
protected:
	string owner_name;
	string card_number;
	string expiry_date;
	int security_code;	// e.g. ccv
	// string type;		// e.g. Visa or MasterCard
public:
	const string& GetCardNumber() const ;
	void SetCardNumber(const string& cardNumber) ;

	const string& GetExpiryDate() const;

	void SetExpiryDate(const string& expiryDate) ;

	const string& GetOwnerName() const ;

	void SetOwnerName(const string& ownerName);

	int GetSecurityCode() const ;

	void SetSecurityCode(int securityCode);

	virtual string ToString() const ;

    virtual PaymentCard* Clone() const = 0;

	virtual ~PaymentCard() ;
};

class DebitCard: public PaymentCard {
protected:
	string billing_address;

public:
	const string& GetBillingAddress() const ;

	void SetBillingAddress(const string& billingAddress);

	virtual PaymentCard* Clone() const override ;

	virtual string ToString() const ;
};

class CreditCard: public PaymentCard {
protected:
	// Say we don't keep billing address
	// Although no attributes, but better have separate class to differentiate them if needed
public:
	virtual string ToString() const override;
	virtual PaymentCard* Clone() const override ;
};


#endif // EXPEDIA_PAYMENT_CARD_H_INCLUDED
