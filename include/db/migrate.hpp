#pragma once

#ifndef __DB_MIGRATE_HPP__
#define __DB_MIGRATE_HPP__

#include <array>
#include <db/connector.hpp>
#include <range/v3/all.hpp>
#include <fmt/format.h>

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
            fmt::print("=");
            db.con()->insert(insert_nation_query(it, db.table_name()));
        });
        fmt::print("\n{} migrated size:{} dataset\n",db.table_name(), dataset.size());
    }
}

#endif

