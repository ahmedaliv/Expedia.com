#ifndef EXPEDIA_CUSTOMER_MGR_H_INCLUDED
#define EXPEDIA_CUSTOMER_MGR_H_INCLUDED


#include "expedia_backend.h"
#include "expedia_payment_card.h"
#include "expedia_common_reservation.h"
#include "expedia_customer.h"
class CustomerManager {
private:
	Customer *customer;
	ExpediaBackend &expedia_manager;

public:
	CustomerManager(User *user, ExpediaBackend &expedia_manager) ;

	vector<Flight> FindFlights(const FlightRequest &request) const ;

	vector<HotelRoom> FindHotels(const HotelRequest &request) const ;

	vector<string> GetPaymentChoices() const ;
	bool MakeReservation(const Reservation& reservation, PaymentCard &payment_card) ;

	vector<string> GetItineraries() const;

	const Customer* GetCustomer() const;
};


#endif // EXPEDIA_CUSTOMER_MGR_H_INCLUDED
