#ifndef _ORDER_DELIVERIES_GET_DATABASE_DELIVERIES_HPP_
#define _ORDER_DELIVERIES_GET_DATABASE_DELIVERIES_HPP_

#include "database/mysql.hpp"
#include "sql/model/obspher.hpp"
#include <string>

namespace order::deliveries::get::database
{
    struct deliveries final
    {
    private:
        using query_t = ::database::mysql::query<
            std::pair<sql::model::obspher::delivery_group, sql::model::obspher::delivery_group::id>,
            std::pair<sql::model::obspher::delivery_group, sql::model::obspher::delivery_group::uuid>
        >;

    public:
        explicit deliveries(::database::mysql::context const& context) :
            _delivery_order_routed_order{::database::mysql::table::create<sql::model::obspher::delivery_order_routed_order>(context)},
            _delivery_order_accepted_order{::database::mysql::table::create<sql::model::obspher::delivery_order_accepted_order>(context)},
            _delivery_order_done_order{::database::mysql::table::create<sql::model::obspher::delivery_order_done_order>(context)},
            _delivery_order_pending_order{::database::mysql::table::create<sql::model::obspher::delivery_order_pending_order>(context)},
            _delivery_order_rejected_order_by_company{::database::mysql::table::create<sql::model::obspher::delivery_order_rejected_order_by_company>(context)},
            _delivery_delivery{::database::mysql::table::create<sql::model::obspher::delivery_delivery>(context)}
        {}

        template<class Output, class NotFound>
        Output retreive(std::string const& order_uuid) const
        {
            {
                auto results = query_t{}
                    .from<sql::model::obspher::delivery_order_routed_order>(_delivery_order_routed_order)
                    .inner_join<
                        sql::model::obspher::delivery_group,
                        std::pair<sql::model::obspher::delivery_group, sql::model::obspher::delivery_group::id>,
                        std::pair<sql::model::obspher::delivery_order_routed_order, sql::model::obspher::delivery_order_routed_order::delivery_group_id>
                    >()
                    .where(
                        ::database::mysql::clause<std::pair<sql::model::obspher::delivery_order_routed_order, sql::model::obspher::delivery_order_routed_order::uuid>>{}.equal(order_uuid)
                    )
                .all();
                if(!results.empty())
                {
                    return build_output<Output>(results.front());
                }
            }
            {
                auto results = query_t{}
                    .from<sql::model::obspher::delivery_order_accepted_order>(_delivery_order_accepted_order)
                    .inner_join<
                        sql::model::obspher::delivery_group,
                        std::pair<sql::model::obspher::delivery_group, sql::model::obspher::delivery_group::id>,
                        std::pair<sql::model::obspher::delivery_order_accepted_order, sql::model::obspher::delivery_order_accepted_order::delivery_group_id>
                    >()
                    .where(
                        ::database::mysql::clause<std::pair<sql::model::obspher::delivery_order_accepted_order, sql::model::obspher::delivery_order_accepted_order::uuid>>{}.equal(order_uuid)
                    )
                .all();
                if(!results.empty())
                {
                    return build_output<Output>(results.front());
                }
            }
            {
                auto results = query_t{}
                    .from<sql::model::obspher::delivery_order_pending_order>(_delivery_order_pending_order)
                    .inner_join<
                        sql::model::obspher::delivery_group,
                        std::pair<sql::model::obspher::delivery_group, sql::model::obspher::delivery_group::id>,
                        std::pair<sql::model::obspher::delivery_order_pending_order, sql::model::obspher::delivery_order_pending_order::delivery_group_id>
                    >()
                    .where(
                        ::database::mysql::clause<std::pair<sql::model::obspher::delivery_order_pending_order, sql::model::obspher::delivery_order_pending_order::uuid>>{}.equal(order_uuid)
                    )
                .all();
                if(!results.empty())
                {
                    return build_output<Output>(results.front());
                }
            }
            {
                auto results = query_t{}
                    .from<sql::model::obspher::delivery_order_rejected_order_by_company>(_delivery_order_rejected_order_by_company)
                    .inner_join<
                        sql::model::obspher::delivery_group,
                        std::pair<sql::model::obspher::delivery_group, sql::model::obspher::delivery_group::id>,
                        std::pair<sql::model::obspher::delivery_order_rejected_order_by_company, sql::model::obspher::delivery_order_rejected_order_by_company::delivery_group_id>
                    >()
                    .where(
                        ::database::mysql::clause<std::pair<sql::model::obspher::delivery_order_rejected_order_by_company, sql::model::obspher::delivery_order_rejected_order_by_company::uuid>>{}.equal(order_uuid)
                    )
                .all();
                if(!results.empty())
                {
                    return build_output<Output>(results.front());
                }
            }
            throw NotFound{"order with UUID " + order_uuid + " not found"};
        }

    private:
        ::database::mysql::table _delivery_order_routed_order;
        ::database::mysql::table _delivery_order_accepted_order;
        ::database::mysql::table _delivery_order_done_order;
        ::database::mysql::table _delivery_order_pending_order;
        ::database::mysql::table _delivery_order_rejected_order_by_company;
        ::database::mysql::table _delivery_delivery;

        template<class Output>
        Output build_output(query_t::return_t const& result) const
        {
            Output output{};
            accessor::output::group_uuid(output, std::move(std::get<1>(result).value()));
            auto results = ::database::mysql::query<
                std::pair<sql::model::obspher::delivery_delivery, sql::model::obspher::delivery_delivery::uuid>
            >{}
                .from<sql::model::obspher::delivery_delivery>(_delivery_delivery)
                .inner_join<
                    sql::model::obspher::delivery_delivery_in_group,
                    std::pair<sql::model::obspher::delivery_delivery_in_group, sql::model::obspher::delivery_delivery_in_group::delivery_id>,
                    std::pair<sql::model::obspher::delivery_delivery, sql::model::obspher::delivery_delivery::id>
                >()
                .where(
                    ::database::mysql::clause<std::pair<sql::model::obspher::delivery_delivery_in_group, sql::model::obspher::delivery_delivery_in_group::group_id>>{}.equal(std::get<0>(result).value())
                )
            .all();
            accessor::output::reserve_deliveries(output, results.size());
            std::transform(
                results.cbegin(),
                results.cend(),
                accessor::output::deliveries_back_inserter(output),
                [](auto const& result){
                    typename std::invoke_result_t<decltype(&accessor::output::deliveries_back_inserter), Output&>::container_type::value_type value{};
                    accessor::output::delivery(value, std::move(std::get<0>(result).value()));
                    return std::get<0>(result).value();
                }
            );
            return output;
        }
    };
}

#endif