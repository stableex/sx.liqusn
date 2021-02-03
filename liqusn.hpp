#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

namespace liqusn {

    using namespace eosio;

    const extended_symbol USN{ symbol{"USN", 4}, "danchortoken"_n };

    const name id = "usnliq"_n;
    const name code = "danchorsmart"_n;
    const std::string description = "USN Liquidator";
    const extended_symbol currency = USN;
    const std::string memo = "bid:";
    const int64_t min_amount = 5'000000000;


    /**
     * parameters table
     */
    struct [[eosio::table]] auctions_row {
        uint64_t    aid;
        name        user;
        uint64_t    price;
        asset       pledge;
        asset       issue;
        asset       remain_pledge;
        asset       remain_issue;
        time_point_sec  create_time;

        uint64_t primary_key() const { return aid; }
    };
    typedef eosio::multi_index< "auctions"_n, auctions_row > auctions;


    std::pair<asset, std::string> get_liquidation_amount() {

        auctions auctionstbl( code, code.value );
        for(const auto& row: auctionstbl) {
            if(row.remain_issue.amount >= min_amount) return { row.remain_issue, std::to_string(row.aid)};
        }

        return {asset{0, USN.get_symbol()}, ""};
    }

}