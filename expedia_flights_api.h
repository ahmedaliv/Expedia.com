#ifndef EXPEDIA_FLIGHTS_API_H_INCLUDED
#define EXPEDIA_FLIGHTS_API_H_INCLUDED

#include "expedia_common_reservation.h"
#include <iostream>

class AirCanadaCustomerInfo {

};

class AirCanadaFlight {
public:
	double price;
	string date_time_from;
	string date_time_to;
};

class AirCanadaOnlineAPI {
public:
	static vector<AirCanadaFlight> GetFlights(string from, string from_date, string to, string to_date, int adults, int childern) {
		vector<AirCanadaFlight> flights;

		flights.push_back( { 200, "25-01-2022", "10-02-2022" });
		flights.push_back( { 250, "29-01-2022", "10-02-2022" });
		return flights;
	}
	static bool ReserveFlight(const AirCanadaFlight& flight, const AirCanadaCustomerInfo &info) {
		return true;
	}
};

class TurkishFlight {
public:
	double cost;
	string datetime_from;
	string datetime_to;
};

class TurkishCustomerInfo {

};

class TurkishAirlinesOnlineAPI {
public:
	void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) {
	}
	void SetPassengersInfo(int infants, int childern, int adults) {
	}
	vector<TurkishFlight> GetAvailableFlights() const {
		vector<TurkishFlight> flights;

		flights.push_back( { 300, "10-01-2022", "10-02-2022" });
		flights.push_back( { 320, "12-01-2022", "10-02-2022" });
		return flights;
	}

	static bool ReserveFlight(const TurkishCustomerInfo &info, const TurkishFlight& flight) {
		return false;
	}
};

////////////////////////////////

class Flight {
private:
	string airline_name;
	double total_cost = 0;
	string date_time_from;
	string date_time_to;

public:
	string ToString() const ;

	const string& GetDateTimeFrom() const ;

	void SetDateTimeFrom(const string& dateTimeFrom);

	const string& GetDateTimeTo() const ;

	void SetDateTimeTo(const string& dateTimeTo) ;

	double GetTotalCost() const ;

	void SetTotalCost(double totalCost) ;
	const string& GetAirlineName() const ;

	void SetAirlineName(const string& airlineName);
};

class FlightRequest {
private:
	string datetime_from;
	string from;
	string datetime_to;
	string to;
	int infants;
	int childern;
	int adults;

public:
	string GetDatePartFrom() const;

	string GetDatePartTo() const ;

	int GetAdults() const ;

	void SetAdults(int adults) ;

	int GetChildren() const ;

	void SetChildren(int childern) ;

	const string& GetDatetimeFrom() const ;

	void SetDatetimeFrom(const string& datetimeFrom) ;

	const string& GetDatetimeTo() const ;

	void SetDatetimeTo(const string& datetimeTo) ;

	const string& GetFrom() const;

	void SetFrom(const string& from);

	int GetInfants() const ;
	void SetInfants(int infants) ;

	const string& GetTo() const ;

	void SetTo(const string& to) ;
};

class FlightReservation: public Reservation {
private:
	FlightRequest request;
	Flight flight;

public:
	FlightReservation(const FlightRequest &request, const Flight &flight);

	virtual FlightReservation* Clone() const override ;

	virtual double TotalCost() const override ;

	virtual string ToString() const override ;
	const Flight& GetFlight() const ;

	const FlightRequest& GetRequest() const ;
};

class IFlightsManager {
protected:
	FlightRequest request;
public:
	virtual void SetFlightRequest(const FlightRequest &request_) {
		request = request_;
	}
	virtual vector<Flight> SearchFlights() const = 0;

	virtual bool ReserveFlight(const FlightReservation &reservation) const = 0;

	virtual string GetName() const = 0;

	virtual ~IFlightsManager() {
	}
};

class AirCanadaFlightsManager: public IFlightsManager {
public:
	virtual string GetName() const override ;

	virtual vector<Flight> SearchFlights() const override ;

	virtual bool ReserveFlight(const FlightReservation &reservation) const;
};

class TurkishFlightsManager: public IFlightsManager {
private:
public:
	virtual string GetName() const override ;

	virtual vector<Flight> SearchFlights() const override ;
	virtual bool ReserveFlight(const FlightReservation &reservation) const ;
};

/*
 * This class reduce the dependency of clients on specific managers. This is the only place that is coupled with the different types
 */
class FlightsFactory {
	// We can design this factory in more efficient way: e.g. using map + singleton
public:
	static vector<IFlightsManager*> GetManagers() {
		vector<IFlightsManager*> flights_managers;

		flights_managers.push_back(new TurkishFlightsManager());
		flights_managers.push_back(new AirCanadaFlightsManager());

		return flights_managers;
	}

	static IFlightsManager* GetManager(string name) {
		for (IFlightsManager* mgr : FlightsFactory::GetManagers()) {
			if (mgr->GetName() == name)
				return mgr;
		}
		return nullptr;
	}
};



#endif // EXPEDIA_FLIGHTS_API_H_INCLUDED
