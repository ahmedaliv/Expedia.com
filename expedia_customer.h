#ifndef EXPEDIA_CUSTOMER_H_INCLUDED
#define EXPEDIA_CUSTOMER_H_INCLUDED



#include "expedia_payment_card.h"
#include "expedia_common_reservation.h"
#include "expedia_user.h"


class Customer: public User {
protected:
	vector<PaymentCard*> cards;	// * to allow polymophism
	ReservationsSet reservations;

public:
	Customer(const Customer&) = delete;
	void operator=(const Customer&) = delete;

	Customer() ;

	~Customer() ;
	void AddPaymentCard(const PaymentCard& card);

	void AddReservation(const Reservation& reservation) ;

	const vector<PaymentCard*>& GetCards() const ;

	const ReservationsSet& GetReservations() const ;
};
#endif // EXPEDIA_CUSTOMER_H_INCLUDED
