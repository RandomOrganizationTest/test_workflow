#ifndef _ORDER_DELIVERIES_GET_ACCESSOR_DATABASE_HPP_
#define _ORDER_DELIVERIES_GET_ACCESSOR_DATABASE_HPP_

#include "cppserver/configuration.hpp"
#include "cppserver/casters.hpp"
#include <string>

namespace order::deliveries::get::accessor
{
    struct database final
    {
    public:
        inline static std::string mysql_uri(cppserver::configuration const& conf)
        {
            return conf.get_value<std::string, 3>({"databases", "mysql", "uri"});
        }
        inline static unsigned short mysql_port(cppserver::configuration const& conf)
        {
            return conf.get_value<unsigned short, 3>({"databases", "mysql", "port"});
        }
    };
}

#endif