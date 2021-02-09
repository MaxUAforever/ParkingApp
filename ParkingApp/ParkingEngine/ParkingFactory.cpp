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
    auto timeManager = std::make_unique<TimeManager>();
    auto staffManager = std::make_unique<StaffManager>();
    auto placesManager = std::make_unique<ParkingPlacesManager>(placesCount);
    auto barriersManager = std::make_unique<BarriersManager>(barriersCount);
    auto sessionsManager = std::make_unique<SessionsManager>();
    
    // TODO: trouble with managers
    auto clientsManager = std::make_unique<ClientsManager>(*timeManager);
    auto paymentManager = std::make_unique<PaymentManager>(*timeManager, *placesManager, priceBaseСoefficient, disabledPersonDiscountCoef, floorDiscount);
    
    return std::make_unique<Parking>(std::move(timeManager),
                                     std::move(paymentManager),
                                     std::move(placesManager),
                                     std::move(clientsManager),
                                     std::move(staffManager),
                                     std::move(barriersManager));
}

} // namespace ParkingEngine
