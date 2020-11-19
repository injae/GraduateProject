#include "db/migrate.hpp"
#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <fmt/ranges.h>

using namespace ranges;

int main(int argc, char* argv[]) {
    fmt::print("database test data migrate\n");

    auto client_db = db::Connector("_PrivateSetX").setup();
    auto server_db = db::Connector("_PrivateSetY").setup();

    //client_db.drop_table();
    //server_db.drop_table();

    auto test_data = db::test_random_dataset_generator(149940);

    fmt::print("generate intersection");
    std::vector<db::PrivateSet> intersections;
    for(auto num = 0; num < 30; ++num) {
        auto id = std::to_string(num);
        for(auto i = 0; i < 30-id.size(); ++i) id += "F";
        intersections.emplace_back(db::PrivateSet{id, 10, 10.1});
    }

    auto client_set = test_data | views::slice(0,49970) | to_vector;
    client_set.insert(client_set.end(), intersections.begin(), intersections.end());
    auto server_set = test_data | views::slice(49970, 149940) | to_vector;
    server_set.insert(server_set.end(), intersections.begin(), intersections.end());

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(client_set.begin(), client_set.end(), g);
    std::shuffle(server_set.begin(), server_set.end(), g);

    db::migrate(client_db, client_set);
    db::migrate(server_db, server_set);

    fmt::print("intersections[{}]\n{}\n", intersections.size(), intersections);

    return 0;
}
// select * from 
// SELECT * INTO OUTFILE '/Users/nieel/dev/jogyu/dataset2_PrivateSetX.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '"' ESCAPED BY '\\' LINES TERMINATED BY '\n' FROM _PrivateSetX;
// SELECT * INTO OUTFILE '/Users/nieel/dev/jogyu/dataset2_PrivateSetY.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '"' ESCAPED BY '\\' LINES TERMINATED BY '\n' FROM _PrivateSetY;

// 20byte
// 교집합 눈에 보이는 값 sha1으로 해서 

// 클 5만
// 서 10만
// 교 30
