#include "ParkingFactory.hpp"

#include "BarriersManager.hpp"
#include "ClientsManager.hpp"
#include "PaymentManager.hpp"
#include "ParkingPlacesManager.hpp"
#include "SessionsManager.hpp"
#include "StaffManager.hpp"

namespace ParkingEngine
{

std::unique_ptr<Parking> ParkingFacory::createParking(size_t barriersCount,
                                                      size_t placesCount,
                                                      double priceBaseСoefficient,
                                                      double disabledPersonDiscountCoef,
                                                      size_t floorDiscount)
{
    auto paymentManager = std::make_unique<PaymentManager>(priceBaseСoefficient, disabledPersonDiscountCoef, floorDiscount);
    auto placesManager = std::make_unique<ParkingPlacesManager>(placesCount);
    auto clientsManager = std::make_unique<ClientsManager>();
    auto staffManager = std::make_unique<StaffManager>();
    auto barriersManager = std::make_unique<BarriersManager>(barriersCount);
    auto sessionsManager = std::make_unique<SessionsManager>();
    
    return std::make_unique<Parking>(std::move(paymentManager),
                                     std::move(placesManager),
                                     std::move(clientsManager),
                                     std::move(staffManager),
                                     std::move(barriersManager),
                                     std::move(sessionsManager));
}

}
