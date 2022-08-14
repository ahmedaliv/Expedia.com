#include  "expedia_customer_mgr.h"


	CustomerManager::CustomerManager(User *user, ExpediaBackend &expedia_manager) :
			customer(dynamic_cast<Customer*>(user)), expedia_manager(expedia_manager) {

		if (customer == nullptr) {
			cout << "Error: User is null pointer as input\n";
			assert(customer != nullptr);
		}

	}

	vector<Flight> CustomerManager::FindFlights(const FlightRequest &request) const {
		return expedia_manager.FindFlights(request);
	}

	vector<HotelRoom> CustomerManager::FindHotels(const HotelRequest &request) const {
		return expedia_manager.FindHotels(request);
	}

	vector<string> CustomerManager::GetPaymentChoices() const {
		vector<string> cards_info;

		for (PaymentCard* card : customer->GetCards())
			cards_info.push_back(card->ToString());
		return cards_info;
	}

	bool CustomerManager::MakeReservation(const Reservation& reservation, PaymentCard &payment_card) {


		bool is_paid = expedia_manager.ChargeCost(reservation.TotalCost(), payment_card);

		if (is_paid) {
			cout << "Money withdraw successfully\n";

			bool is_confirmed = expedia_manager.ConfirmReservation(reservation);

			if (is_confirmed) {
				cout << "Reservation confirmed\n";
				customer->AddReservation(reservation);
				return true;
			} else {
				cout << "Failed to confirm some of your reservation items\n";
				cout << "Canceling payment and whatever reserved\n";
				bool is_uncharged = expedia_manager.UnchargeCost(reservation.TotalCost(), payment_card);

				if (!is_uncharged)
					cout << "Problems in returning back your money. Call us on 911\n";
			}
		} else
			cout << "Failed to withdtaw Money for the reservation\n";

		return false;
	}

	vector<string> CustomerManager::GetItineraries() const {
		const ReservationsSet& set = customer->GetReservations();
		vector<string> itineraries;

		for (const Reservation* reservation : set.GetReservations())
			itineraries.push_back(reservation->ToString());

		return itineraries;
	}

	const Customer* CustomerManager::GetCustomer() const {
		return customer;
	}

