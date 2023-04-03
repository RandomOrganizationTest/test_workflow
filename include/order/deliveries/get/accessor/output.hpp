#ifndef _ORDER_DELIVERIES_GET_ACCESSOR_OUTPUT_HPP_
#define _ORDER_DELIVERIES_GET_ACCESSOR_OUTPUT_HPP_

#include "api/obspher/order/deliveries/get/outputs.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <chrono>

namespace order::deliveries::get::accessor::output
{
    inline void group_uuid(api::obspher::order::deliveries::get::outputs & outputs, std::string value)
    {
        outputs.success.group = std::move(value);
    }
    inline constexpr std::back_insert_iterator<
        std::vector<std::string>
    > deliveries_back_inserter(api::obspher::order::deliveries::get::outputs & outputs)
    {
        return std::back_inserter(outputs.success.deliveries);
    }
    inline void reserve_deliveries(api::obspher::order::deliveries::get::outputs & outputs, std::size_t size)
    {
        outputs.success.deliveries.reserve(size);
    }
    inline void delivery(std::string & output, std::string value)
    {
        output = std::move(value);
    }
}

#endif