#include <db/connector.hpp>
#include <fmt/format.h>
#include <string>

namespace db {
    using namespace fmt::literals;
    const std::string search_infector_query(const std::string& table) {
        return "select Value from {} where Frequency >= 20 and Amount between 10.3 and 209"_format(table);
    }

    const std::string search_visitor_query(const std::string& table) {
        return "select Value from {}"_format(table);
    }

    const std::string insert_nation_query(const PrivateSet& data, const std::string& table) {
        return "insert into {} VALUES ({}, {}, {})"_format(table, data.value, data.frequency, data.amount);
    }

    std::vector<PrivateSet> query_to_vec(mariadb::result_set_ref result) {
        std::vector<PrivateSet> list;
        fmt::print("size:{}\n",result->row_count());
        while(result->next()) {
            auto value = result->get_string("Value");
            auto frequency = result->get_unsigned32("Frequency");
            auto amount = result->get_decimal("Amount").float32();
            list.emplace_back(PrivateSet{value, frequency, amount});
        }
        return list;
    }

    Connector::Connector(const std::string& table_name) {
        using namespace mariadb;
        table_name_ = table_name;
        // host id password
        acc_ = account::create(env::host, env::user, env::password, "", env::port);
        con_ = connection::create(acc_);
    }

    Connector& Connector::setup() {
        con_->connect();
        if(not con_->connected()) {
            fmt::print("start mariadb server\n");
            system("mysql.server start");
            con_->connect();
            if(not con_->connected()) { fmt::print(stderr,"can't connect to mariadb server\n"); exit(1); }
        }
        con_->query("create database if not exists {}"_format(env::database));
        con_->set_schema(env::database);
        fmt::print("{}: connected\n", con_->schema());
        con_->query("create table if not exists {}(Value VARCHAR(30) NOT NULL,"
                    "Frequency INT NOT NULL, Amount DECIMAL(8,2))"_format(table_name_));
        return *this;
    }

    std::vector<std::string> Connector::visitor() {
        std::vector<std::string> list;
        auto result = con()->query(db::search_visitor_query(table_name_));
        while(result->next()) {
            auto value = result->get_string("Value");
            list.emplace_back(value);
        }
        return list;
    }

    std::vector<std::string> Connector::infectors() {
        std::vector<std::string> list;
        auto result = con()->query(db::search_infector_query(table_name_));
        while(result->next()) {
            auto value = result->get_string("Value");
            list.emplace_back(value);
        }
        return list;
    }
    
    void Connector::drop_table() {
        con_->query("drop table {}"_format(table_name_));
    }

}
