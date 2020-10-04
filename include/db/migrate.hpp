#pragma once

#ifndef __DB_MIGRATE_HPP__
#define __DB_MIGRATE_HPP__

#include <array>
#include <db/connector.hpp>
#include <range/v3/all.hpp>
#include <fmt/format.h>
#include <random>
#include <tuple>
#include <utility>

namespace db {
    const std::vector<PrivateSet> TEST_DATASET = {
            {"1", 20, 20.1},
            {"2", 18, 10.1},
            {"3", 18, 20.1},
            {"4", 30, 200 },
            {"5", 24, 210 },
    };

    /// if you don't want default dataset change dataset argument
    inline void migrate(Connector& db, const std::vector<PrivateSet>& dataset = TEST_DATASET) {
        using namespace ranges;
        for_each(dataset, [&](auto it){
            db.con()->insert(insert_nation_query(it, db.table_name()));
        });
        fmt::print("\n{} migrated size:{} dataset\n",db.table_name(), dataset.size());
    }

    // return almost 10% infector of size
    std::vector<PrivateSet> random_dataset_generator(int size) {
        using namespace ranges;
        std::vector<PrivateSet> data_set;
        auto values = views::iota(0,size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<u_int32_t> frequency(0, 30);
        std::normal_distribution<float> amounts(8.3,5.0);
        data_set = values
            | views::transform([&](auto it) {
                return PrivateSet{std::to_string(it), frequency(gen), amounts(gen)};}) | to_vector;

        auto infectors = distance(data_set
                                  | views::filter([](auto it) {
                                      return it.frequency >= 20 and it.amount >= 10.3  && it.amount <= 209;}));
        fmt::print("person : infector == {} : {} ({}%)\n", data_set.size(), infectors, ((double)infectors/data_set.size())*100.);

        return data_set;
    }


}

#endif

