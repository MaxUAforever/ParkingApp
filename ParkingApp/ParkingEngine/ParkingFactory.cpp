#include "ParkingFactory.hpp"

#include "BarriersManager.hpp"
#include "ClientsManager.hpp"
#include "PaymentManager.hpp"
#include "ParkingPlacesManager.hpp"
#include "TimeManager.hpp"
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
    auto vehiclesManager = std::make_unique<VehiclesManager>();
    auto placesManager = std::make_unique<ParkingPlacesManager>(placesCount);
    auto barriersManager = std::make_unique<BarriersManager>(barriersCount);
    
    const VehicleDiscounts vehicleDiscounts = {{VehicleType::Motorbyke, 0.5}, {VehicleType::Truck, 2}};
    
    auto clientsManager = std::make_unique<ClientsManager>(*timeManager);
    auto paymentManager = std::make_unique<PaymentManager>(*timeManager, *placesManager, *staffManager, vehicleDiscounts, priceBaseСoefficient, disabledPersonDiscountCoef, floorDiscount);
    
    return std::make_unique<Parking>(std::move(timeManager),
                                     std::move(paymentManager),
                                     std::move(placesManager),
                                     std::move(clientsManager),
                                     std::move(staffManager),
                                     std::move(barriersManager),
                                     std::move(vehiclesManager));
}

} // namespace ParkingEngine
