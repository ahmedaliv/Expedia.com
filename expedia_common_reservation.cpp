#include "expedia_common_reservation.h"
#include <sstream>
using std::ostringstream;
using std::istringstream;

ItineraryReservation::ItineraryReservation(const ItineraryReservation& another_reservation) {	// copy constructor
		for (const Reservation* reservation : another_reservation.GetReservations())
			AddReservation(*reservation);
	}

void ItineraryReservation::AddReservation(const Reservation& reservation) {
		reservations.push_back(reservation.Clone());
	}

double ItineraryReservation::TotalCost() const {
		double cost = 0;

		for (const Reservation* reservation : reservations)
			cost += reservation->TotalCost();

		return cost;
	}
	ItineraryReservation::~ItineraryReservation() {
		Clear();
	}

const vector<Reservation*>& ItineraryReservation::GetReservations() const {
		return reservations;
	}


	void ItineraryReservation::Clear() {
		for (const Reservation* reservation : reservations)
			delete reservation;
		reservations.clear();
	}

	 string ItineraryReservation::ToString() const  {
		ostringstream oss;

		oss <<"**********************************************\n";
		oss << "Itinerary of " << reservations.size() << " sub-reservations\n";

		for (const Reservation* reservation : reservations)
			oss << reservation->ToString() << "\n";

		oss << "Total Itinerary cost: " << TotalCost() << "\n";
		oss <<"**********************************************\n";
		return oss.str();
	}

	 Reservation* ItineraryReservation::Clone() const {
		return new ItineraryReservation(*this);
	}
