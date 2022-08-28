#include "expedia_flights_api.h"
#include "sstream"
using std::ostringstream;
using std::istringstream;
// Flight Functions
string Flight::ToString() const {
		ostringstream oss;
		oss << "Airline: " << airline_name << " Cost: " << total_cost << " Departure Date " << date_time_from << " Arrival date " << date_time_to;
		return oss.str();
	}

	const string& Flight::GetDateTimeFrom() const {
		return date_time_from;
	}

	void Flight::SetDateTimeFrom(const string& dateTimeFrom) {
		date_time_from = dateTimeFrom;
	}

	const string& Flight::GetDateTimeTo() const {
		return date_time_to;
	}

	void Flight::SetDateTimeTo(const string& dateTimeTo) {
		date_time_to = dateTimeTo;
	}

	double Flight::GetTotalCost() const {
		return total_cost;
	}

	void Flight::SetTotalCost(double totalCost) {
		total_cost = totalCost;
	}

	const string& Flight::GetAirlineName() const {
		return airline_name;
	}

	void Flight::SetAirlineName(const string& airlineName) {
		airline_name = airlineName;
	}

// Flight Request   functions

string FlightRequest::GetDatePartFrom() const {
		return datetime_from;	// extract date only
	}

	string FlightRequest::GetDatePartTo() const {
		return datetime_to;	// extract date only
	}

	int FlightRequest::GetAdults() const {
		return adults;
	}

	void FlightRequest::SetAdults(int adults) {
		this->adults = adults;
	}

	int FlightRequest::GetChildren() const {
		return childern;
	}

	void FlightRequest::SetChildren(int childern) {
		this->childern = childern;
	}

	const string& FlightRequest::GetDatetimeFrom() const {
		return datetime_from;
	}

	void FlightRequest::SetDatetimeFrom(const string& datetimeFrom) {
		datetime_from = datetimeFrom;
	}

	const string& FlightRequest::GetDatetimeTo() const {
		return datetime_to;
	}

	void FlightRequest::SetDatetimeTo(const string& datetimeTo) {
		datetime_to = datetimeTo;
	}

	const string& FlightRequest::GetFrom() const {
		return from;
	}

	void FlightRequest::SetFrom(const string& from) {
		this->from = from;
	}

	int FlightRequest::GetInfants() const {
		return infants;
	}

	void FlightRequest::SetInfants(int infants) {
		this->infants = infants;
	}

	const string& FlightRequest::GetTo() const {
		return to;
	}

	void FlightRequest::SetTo(const string& to) {
		this->to = to;
	}


// Flight Reservation Functions

FlightReservation::FlightReservation(const FlightRequest &request, const Flight &flight) :
			request(request), flight(flight) {
	}

	 FlightReservation* FlightReservation::Clone() const  {
		return new FlightReservation(*this);
	}

	 double FlightReservation::TotalCost() const  {
		return flight.GetTotalCost();
	}

	 string FlightReservation::ToString() const  {
		ostringstream oss;
		oss << "Airline reservation with reservation: " << flight.GetAirlineName() << ": From " << request.GetFrom() << " on " << request.GetDatetimeFrom() << "\n";
		oss << "\tTo " << request.GetTo() << " on " << request.GetDatetimeTo() << "\n";
		oss << "\t" << "Adults: " << request.GetAdults() << " children: " << request.GetChildren() << " infants: " << request.GetInfants() << "\n";
		oss << "\tTotal Cost:" << TotalCost() << "\n";

		return oss.str();
	}

	const Flight& FlightReservation::GetFlight() const {
		return flight;
	}

	const FlightRequest& FlightReservation::GetRequest() const {
		return request;
	}


///////////////////////


//AirCanadaFlightsManager functions

 string AirCanadaFlightsManager::GetName() const  {
		return "AirCanada Airlines";
	}

	 vector<Flight> AirCanadaFlightsManager::SearchFlights() const  {
		vector<AirCanadaFlight> flights_aircanada = AirCanadaOnlineAPI::GetFlights(request.GetFrom(), request.GetDatePartFrom(), request.GetTo(), request.GetDatePartTo(), request.GetAdults(), request.GetChildren());
		vector<Flight> flights;

		// convert
		for (auto & flight_aircanada : flights_aircanada) {
			Flight flight;
			flight.SetAirlineName(GetName());
			flight.SetDateTimeFrom(flight_aircanada.date_time_from);
			flight.SetDateTimeTo(flight_aircanada.date_time_to);
			flight.SetTotalCost(flight_aircanada.price);

			flights.push_back(flight);
		}
		return flights;
	}

	 bool AirCanadaFlightsManager::ReserveFlight(const FlightReservation &reservation) const {
		// Just dummy. We should map from reservation to the agency api
		return AirCanadaOnlineAPI::ReserveFlight(AirCanadaFlight(), AirCanadaCustomerInfo());
	}



///////////////
// TurkishFlightsManager

    string TurkishFlightsManager::GetName() const  {
		return "Turksih Airlines";
	}

	 vector<Flight> TurkishFlightsManager::SearchFlights() const  {
		TurkishAirlinesOnlineAPI api;

		api.SetFromToInfo(request.GetDatetimeFrom(), request.GetFrom(), request.GetDatetimeTo(), request.GetTo());
		api.SetPassengersInfo(request.GetInfants(), request.GetChildren(), request.GetAdults());

		vector<TurkishFlight> flights_turkey = api.GetAvailableFlights();
		vector<Flight> flights;

		// convert
		for (auto & flight_turkey : flights_turkey) {
			Flight flight;
			flight.SetAirlineName("Turksih Airlines");
			flight.SetDateTimeFrom(flight_turkey.datetime_from);
			flight.SetDateTimeTo(flight_turkey.datetime_to);
			flight.SetTotalCost(flight_turkey.cost);

			flights.push_back(flight);
		}
		return flights;
	}
	 bool TurkishFlightsManager::ReserveFlight(const FlightReservation &reservation) const {
		// Just dummy. We should map from reservation to the agency api
		return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo(), TurkishFlight());
	}
