#include "db/migrate.hpp"
#include <fmt/format.h>


int main(int argc, char* argv[]) {
    fmt::print("database test data migrate\n");

    auto client_db = db::Connector("_PrivateSetX").setup();
    auto server_db = db::Connector("_PrivateSetY").setup();
   
    //client_db.drop_table();
    //server_db.drop_table();
    auto test_data = db::random_dataset_generator(100000);
    db::migrate(server_db, test_data);
    db::migrate(client_db, test_data);

    return 0;
}
