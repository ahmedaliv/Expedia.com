#ifndef EXPEDIA_COMMON_RESERVATION_H_INCLUDED
#define EXPEDIA_COMMON_RESERVATION_H_INCLUDED

#include <vector>
#include <iostream>
using std::vector;
using std::string;

class Reservation {
public:
	virtual Reservation* Clone() const = 0;

	virtual double TotalCost() const = 0;

	virtual string ToString() const = 0;

	virtual ~Reservation() {
	}
};


// then we make an itinerary (contains a group of reservations)
// so this helped us  that we won't be making a class for each group of reservations like flight and hotel or flight and car and so on
// and as it have the same probs and functions like a single reservation so  we inheirt from it

class ItineraryReservation: public Reservation  {
protected:
	vector<Reservation*> reservations;	// As has pointers, we need copy constructor

public:
	ItineraryReservation() {
	}

	ItineraryReservation(const ItineraryReservation& another_reservation);

	void AddReservation(const Reservation& reservation);

	virtual double TotalCost() const ;


	~ItineraryReservation();

	const vector<Reservation*>& GetReservations() const ;

	void Clear();
	virtual string ToString() const override ;

	virtual Reservation* Clone() const override ;

};



class ReservationsSet: public ItineraryReservation {
public:
	// We need another class that act like set of different reservations (not Itinerary)
	// This has same functionalities as ItineraryReservation
	// It is much better to have its own class, even empty class
	// Then code is more semantic + we can do future changes easily

	using ItineraryReservation::ItineraryReservation;	// use its copy constructor

	virtual Reservation* Clone() const {
		return new ReservationsSet(*this);
	}
};



#endif // EXPEDIA_COMMON_RESERVATION_H_INCLUDED
