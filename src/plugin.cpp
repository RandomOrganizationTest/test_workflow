#include "order/deliveries/get/handler.hpp"

#include "cppserver/endpoint_creation.hpp"

extern "C" std::shared_ptr<cppserver::virtual_endpoint> create(
    cppserver::configuration const& configuration,
    std::vector<std::shared_ptr<cppserver::virtual_endpoint>> const& endpoints
)
{
    return order::deliveries::get::endpoint::create(configuration, endpoints);
}
