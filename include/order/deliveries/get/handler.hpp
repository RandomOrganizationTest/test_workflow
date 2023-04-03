#ifndef _ORDER_DELIVERIES_GET_HANDLER_HPP_
#define _ORDER_DELIVERIES_GET_HANDLER_HPP_

#include "order/deliveries/get/accessor/output.hpp"
#include "order/deliveries/get/database/deliveries.hpp"

#include "database/mysql.hpp"

#include "api/obspher/server.hpp"

#include "api/obspher/order/deliveries/get/inputs.hpp"
#include "api/obspher/order/deliveries/get/outputs.hpp"
#include "api/obspher/order/deliveries/get/route.hpp"
#include "api/obspher/order/deliveries/get/method.hpp"
#include "api/obspher/order/deliveries/get/reader.hpp"
#include "api/obspher/order/deliveries/get/writer.hpp"

#include "service_security/model/user.hpp"
#include "service_security/access/granter.hpp"

#include "cppserver/middleware/authorization_bearer.hpp"
#include "cppserver/endpoint.hpp"

namespace order::deliveries::get
{
    namespace detail
    {
        struct granter final
        {
        public:
            static inline bool has_access(service_security::model::user const& user)
            {
                return service_security::access::granter::is_operator(
                    user,
                    service_security::model::operator_role::target::deliveries,
                    service_security::model::operator_role::action::read,
                    service_security::model::operator_role::scope::full
                );
            }
        };
    }

    struct endpoint final : public cppserver::endpoint<endpoint, cppserver::middleware::authorization_bearer<detail::granter>>
    {
    public:
        using server_t = api::obspher::server;

        using inputs_t = api::obspher::order::deliveries::get::inputs;
        using outputs_t = api::obspher::order::deliveries::get::outputs;

        using route_t = api::obspher::order::deliveries::get::route;
        using method_t = api::obspher::order::deliveries::get::method;

        using reader_t = api::obspher::order::deliveries::get::reader;
        template<class ContentType>
        using writer_t = api::obspher::order::deliveries::get::writer<ContentType>;

        endpoint(
            cppserver::configuration const& c,
            std::vector<std::shared_ptr<virtual_endpoint>> const& e
        );

        outputs_t process(auto &&, inputs_t const& inputs) const;

    private:
        ::database::mysql::context _mysql_context;
        database::deliveries _deliveries_retreiver;
    };
}

#endif