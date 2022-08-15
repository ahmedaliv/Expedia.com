#include "expedia_payment_card.h"
#include "sstream"
using std::ostringstream;
using std::istringstream;


const string& PaymentCard::GetCardNumber() const {
		return card_number;
	}

	void PaymentCard::SetCardNumber(const string& cardNumber) {
		card_number = cardNumber;
	}

	const string& PaymentCard::GetExpiryDate() const {
		return expiry_date;
	}

	void PaymentCard::SetExpiryDate(const string& expiryDate) {
		expiry_date = expiryDate;
	}

	const string& PaymentCard::GetOwnerName() const {
		return owner_name;
	}

	void PaymentCard::SetOwnerName(const string& ownerName) {
		owner_name = ownerName;
	}

	int PaymentCard::GetSecurityCode() const {
		return security_code;
	}

	void PaymentCard::SetSecurityCode(int securityCode) {
		security_code = securityCode;
	}

	string PaymentCard::ToString() const {
		ostringstream oss;
		oss << "Owner: " << owner_name << " Card number: " << card_number << " Expiry date: " << expiry_date;
		// security_code shouldn't be displayed! for security reasons.
		return oss.str();
	}


	 PaymentCard::~PaymentCard() {
	}



////////////////////////////////////

// DebitCard

const string& DebitCard::GetBillingAddress() const {
		return billing_address;
	}

	void DebitCard::SetBillingAddress(const string& billingAddress) {
		billing_address = billingAddress;
	}

	 PaymentCard* DebitCard::Clone() const  {
		return new DebitCard(*this);
	}

	 string DebitCard::ToString() const {
		ostringstream oss;
		oss << "[Debit Card]: " << PaymentCard::ToString() << " Billing Address: " << billing_address;
		return oss.str();
	}


/////////////////////////
// Credit Card


 string CreditCard::ToString() const  {
		ostringstream oss;
		oss << "[Credit Card]: " << PaymentCard::ToString();
		return oss.str();
	}
	 PaymentCard* CreditCard::Clone() const  {
		return new CreditCard(*this);
	}
