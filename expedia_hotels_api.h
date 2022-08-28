#ifndef EXPEDIA_HOTELS_API_H_INCLUDED
#define EXPEDIA_HOTELS_API_H_INCLUDED
#include "expedia_common_reservation.h"

#include <iostream>
#include <vector>
using std::vector;
using std::string;

class HiltonRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class HiltonHotelAPI {
public:
	static vector<HiltonRoom> SearchRooms(string country, string city, string from_date, string to_date, int adults, int children, int needed_rooms) {
		vector<HiltonRoom> rooms;

		rooms.push_back( { "Interior View", 6, 200.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "City View", 3, 300.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Deluxe View", 8, 500.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

class MarriottFoundRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class MarriottHotelAPI {
public:
	static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children) {
		vector<MarriottFoundRoom> rooms;

		rooms.push_back( { "City View", 8, 320.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Interior View", 8, 220.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Private View", 5, 600.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

///////////////////////////////////

class HotelRoom {
private:
	string hotel_name;
	string room_type;
	int available_rooms = 0;
	double price_per_night = 0;
	string date_from;
	string date_to;

public:
	string ToString() const ;

	const string& GetDateFrom() const ;

	void SetDateFrom(const string& dateFrom);

	const string& GetDateTo() const;

	void SetDateTo(const string& dateTo) ;

	double GetPricePerNight() const;

	void SetPricePerNight(double pricePerNight);

	const string& GetRoomType() const ;

	void SetRoomType(const string& roomType) ;

	int GetAvailableRooms() const;

	void SetAvailableRooms(int availableRooms = 0);

	const string& GetHotelName() const ;

	void SetHotelName(const string& hotelName);
};

class HotelRequest {
private:
	string from_date;
	string to_date;
	string country;
	string city;
	int rooms;
	int adults;
	int children;

public:
	int GetTotalNights() const;
	int GetAdults() const ;

	void SetAdults(int adults);

	int GetChildren() const ;
	void SetChildren(int children) ;

	const string& GetCity() const ;

	void SetCity(const string& city);
	const string& GetCountry() const ;

	void SetCountry(const string& country);

	const string& GetFromDate() const ;

	void SetFromDate(const string& fromDate) ;

	int GetRooms() const ;

	void SetRooms(int rooms) ;

	const string& GetToDate() const;

	void SetToDate(const string& toDate);
};

class HotelReservation: public Reservation {
private:
	HotelRequest request;
	HotelRoom room;

public:
	HotelReservation(const HotelRequest &request, const HotelRoom &room) ;

	virtual HotelReservation* Clone() const override ;

	virtual double TotalCost() const override;

	virtual string ToString() const override;

	const HotelRequest& GetRequest() const ;

	const HotelRoom& GetRoom() const;
};

class IHotelsManager {
protected:
	HotelRequest request;
public:
	virtual string GetName() const = 0;

	virtual void SetHotelRequest(const HotelRequest &request_) {
		request = request_;
	}
	virtual vector<HotelRoom> SearchHotelRooms() = 0;

	virtual bool ReserveRoom(const HotelReservation &reservation) const = 0;

	virtual ~IHotelsManager() {
	}
};

class HiltonHotelsManager: public IHotelsManager {
private:

public:
	virtual string GetName() const override ;

	virtual vector<HotelRoom> SearchHotelRooms() ;
	virtual bool ReserveRoom(const HotelReservation &reservation) const override;
};

class MarriottHotelsManager: public IHotelsManager {
private:

public:
	virtual string GetName() const override ;

	virtual vector<HotelRoom> SearchHotelRooms() ;
	virtual bool ReserveRoom(const HotelReservation &reservation) const override;
};

class HotelsFactory {
public:
	static vector<IHotelsManager*> GetManagers() {
		vector<IHotelsManager*> managers;

		managers.push_back(new HiltonHotelsManager());
		managers.push_back(new MarriottHotelsManager());

		return managers;
	}

	static IHotelsManager* GetManager(string name) {
		for (IHotelsManager* mgr : HotelsFactory::GetManagers()) {
			if (mgr->GetName() == name)
				return mgr;
		}
		return nullptr;
	}
};
#endif // EXPEDIA_HOTELS_API_H_INCLUDED
