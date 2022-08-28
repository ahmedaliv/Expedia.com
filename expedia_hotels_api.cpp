#include "expedia_hotels_api.h"
#include "sstream"
using std::ostringstream;
using std::istringstream;
///////////////////////////////////
//hotelroom functions

	string HotelRoom::ToString() const {
		ostringstream oss;
		oss << "Hotel: " << hotel_name << " Room Type: " << room_type << "(" << available_rooms << ") Price per night: " << price_per_night << " From Date " << date_from << " to " << date_to << "";
		return oss.str();
	}

	const string& HotelRoom::GetDateFrom() const {
		return date_from;
	}

	void HotelRoom::SetDateFrom(const string& dateFrom) {
		date_from = dateFrom;
	}

	const string& HotelRoom::GetDateTo() const {
		return date_to;
	}

	void HotelRoom::SetDateTo(const string& dateTo) {
		date_to = dateTo;
	}

	double HotelRoom::GetPricePerNight() const {
		return price_per_night;
	}

	void HotelRoom::SetPricePerNight(double pricePerNight) {
		price_per_night = pricePerNight;
	}

	const string& HotelRoom::GetRoomType() const {
		return room_type;
	}

	void HotelRoom::SetRoomType(const string& roomType) {
		room_type = roomType;
	}

	int HotelRoom::GetAvailableRooms() const {
		return available_rooms;
	}

	void HotelRoom::SetAvailableRooms(int availableRooms) {
		available_rooms = availableRooms;
	}

	const string& HotelRoom::GetHotelName() const {
		return hotel_name;
	}

	void HotelRoom::SetHotelName(const string& hotelName) {
		hotel_name = hotelName;
	}


	int HotelRequest::GetTotalNights() const {
		// Some date computations
		return 3;
	}
	int HotelRequest::GetAdults() const {
		return adults;
	}

	void HotelRequest::SetAdults(int adults) {
		this->adults = adults;
	}

	int HotelRequest::GetChildren() const {
		return children;
	}

	void HotelRequest::SetChildren(int children) {
		this->children = children;
	}

	const string& HotelRequest::GetCity() const {
		return city;
	}

	void HotelRequest::SetCity(const string& city) {
		this->city = city;
	}

	const string& HotelRequest::GetCountry() const {
		return country;
	}

	void HotelRequest::SetCountry(const string& country) {
		this->country = country;
	}

	const string& HotelRequest::GetFromDate() const {
		return from_date;
	}

	void HotelRequest::SetFromDate(const string& fromDate) {
		from_date = fromDate;
	}

	int HotelRequest::GetRooms() const {
		return rooms;
	}

	void HotelRequest::SetRooms(int rooms) {
		this->rooms = rooms;
	}

	const string& HotelRequest::GetToDate() const {
		return to_date;
	}

	void HotelRequest::SetToDate(const string& toDate) {
		to_date = toDate;
	}



	HotelReservation::HotelReservation(const HotelRequest &request, const HotelRoom &room) :
			request(request), room(room) {
	}

	 HotelReservation* HotelReservation::Clone() const  {
		return new HotelReservation(*this);
	}

	 double HotelReservation::TotalCost() const  {
		return room.GetPricePerNight() * request.GetTotalNights();
	}

	 string HotelReservation::ToString() const  {
		ostringstream oss;
		oss << "Hotel reservation: " << room.GetHotelName() << ": " << request.GetCity() << " @ " << request.GetCountry() << "\n";
		oss << "\t" << request.GetFromDate() << " to " << request.GetToDate() << " : " << request.GetTotalNights() << "\n";
		oss << "\t" << "Adults: " << request.GetAdults() << " children " << request.GetChildren() << "\n";
		oss << "\tTotal Cost:" << TotalCost() << "\n";

		return oss.str();
	}

	const HotelRequest& HotelReservation::GetRequest() const {
		return request;
	}

	const HotelRoom& HotelReservation::GetRoom() const {
		return room;
	}


////////////
//HiltonHotelsManager

	 string  HiltonHotelsManager::GetName() const  {
		return "Hilton Hotel";
	}

	 vector<HotelRoom> HiltonHotelsManager::SearchHotelRooms() {
		vector<HiltonRoom> api_rooms = HiltonHotelAPI::SearchRooms(request.GetCountry(), request.GetCity(), request.GetFromDate(), request.GetToDate(), request.GetAdults(), request.GetChildren(), request.GetRooms());
		vector<HotelRoom> rooms;

		for (auto & api_room : api_rooms) {
			HotelRoom room;
			room.SetHotelName("Hilton Hotel");
			room.SetDateFrom(api_room.date_from);
			room.SetDateTo(api_room.date_to);
			room.SetPricePerNight(api_room.price_per_night);
			room.SetAvailableRooms(api_room.available);
			room.SetRoomType(api_room.room_type);

			rooms.push_back(room);
		}
		return rooms;
	}

	 bool HiltonHotelsManager::ReserveRoom(const HotelReservation &reservation) const {
		return true;
	}


//////////////
// Marioothotelsmanager functions



	 string MarriottHotelsManager::GetName() const  {
		return "Marriott Hotel";
	}

	 vector<HotelRoom> MarriottHotelsManager::SearchHotelRooms() {
		//string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children
		vector<MarriottFoundRoom> api_rooms = MarriottHotelAPI::FindRooms(request.GetFromDate(), request.GetToDate(), request.GetCountry(), request.GetCity(), request.GetRooms(), request.GetAdults(), request.GetChildren());
		vector<HotelRoom> rooms;

		for (auto & api_room : api_rooms) {
			HotelRoom room;
			room.SetHotelName("Marriott Hotel");
			room.SetDateFrom(api_room.date_from);
			room.SetDateTo(api_room.date_to);
			room.SetPricePerNight(api_room.price_per_night);
			room.SetAvailableRooms(api_room.available);
			room.SetRoomType(api_room.room_type);

			rooms.push_back(room);
		}
		return rooms;
	}
	 bool MarriottHotelsManager::ReserveRoom(const HotelReservation &reservation) const {
		return true;
	}

