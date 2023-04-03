#include "order/deliveries/get/handler.hpp"

#include "order/deliveries/get/accessor/database.hpp"
#include "database/model/credentials.hpp"

#include "api/obspher/order/deliveries/get/errors.hpp"

order::deliveries::get::endpoint::endpoint(
    cppserver::configuration const& c,
    std::vector<std::shared_ptr<cppserver::virtual_endpoint>> const& e
) :
    cppserver::endpoint<endpoint, cppserver::middleware::authorization_bearer<detail::granter>>{c, e},
    _mysql_context{
        accessor::database::mysql_uri(c),
        accessor::database::mysql_port(c),
        "order::deliveries::get",
        std::string{credentials::mysql_user()},
        std::string{credentials::mysql_pwd()}
    },
    _deliveries_retreiver{_mysql_context}
{}

order::deliveries::get::endpoint::outputs_t order::deliveries::get::endpoint::process(auto && , order::deliveries::get::endpoint::inputs_t const& inputs) const // cppcheck-suppress  unusedFunction
{
    auto outputs = _deliveries_retreiver.template retreive<outputs_t, api::obspher::order::deliveries::get::order_not_found>(inputs.uuid);
    return outputs;
}