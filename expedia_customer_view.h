#ifndef EXPEDIA_CUSTOMER_VIEW_H_INCLUDED
#define EXPEDIA_CUSTOMER_VIEW_H_INCLUDED


#include "expedia_customer_mgr.h"

class CustomerView {
private:
	CustomerManager &customer_manager;
	const Customer& customer;
	ItineraryReservation current_itinerary;

	void ReadFlightRequest(FlightRequest &request) const;

	void ReadHotelRequest(HotelRequest &request) const;
	int ChooseRoom(const vector<HotelRoom> &rooms) const;
	int ChooseFlight(const vector<Flight> &flights) const ;

	void AddFlight() ;

	void AddHotel() ;

	void PayItinerary() ;

public:
	CustomerView(CustomerManager &customer_manager);
	void Display() ;

	void ViewProfile() const ;

	void MakeItinerary() ;
	void ListItineraries() const;
};

#endif // EXPEDIA_CUSTOMER_VIEW_H_INCLUDED
