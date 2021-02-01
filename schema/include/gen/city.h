//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     City data = nlohmann::json::parse(jsonString);

#pragma once

#include <json.hpp>

#include <optional>
#include <stdexcept>
#include <regex>

namespace gen {
namespace city {
    using nlohmann::json;

    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }

    class GroupedProperties {
        public:
        GroupedProperties() = default;
        virtual ~GroupedProperties() = default;

        private:
        std::string city;
        std::string state;
        std::string street_address;

        public:
        const std::string & get_city() const { return city; }
        std::string & get_mutable_city() { return city; }
        void set_city(const std::string & value) { this->city = value; }

        const std::string & get_state() const { return state; }
        std::string & get_mutable_state() { return state; }
        void set_state(const std::string & value) { this->state = value; }

        const std::string & get_street_address() const { return street_address; }
        std::string & get_mutable_street_address() { return street_address; }
        void set_street_address(const std::string & value) { this->street_address = value; }
    };

    class City {
        public:
        City() = default;
        virtual ~City() = default;

        private:
        GroupedProperties addr1;
        GroupedProperties addr2;

        public:
        const GroupedProperties & get_addr1() const { return addr1; }
        GroupedProperties & get_mutable_addr1() { return addr1; }
        void set_addr1(const GroupedProperties & value) { this->addr1 = value; }

        const GroupedProperties & get_addr2() const { return addr2; }
        GroupedProperties & get_mutable_addr2() { return addr2; }
        void set_addr2(const GroupedProperties & value) { this->addr2 = value; }
    };
}
}

namespace nlohmann {
    void from_json(const json & j, gen::city::GroupedProperties & x);
    void to_json(json & j, const gen::city::GroupedProperties & x);

    void from_json(const json & j, gen::city::City & x);
    void to_json(json & j, const gen::city::City & x);

    inline void from_json(const json & j, gen::city::GroupedProperties& x) {
        x.set_city(j.at("city").get<std::string>());
        x.set_state(j.at("state").get<std::string>());
        x.set_street_address(j.at("street_address").get<std::string>());
    }

    inline void to_json(json & j, const gen::city::GroupedProperties & x) {
        j = json::object();
        j["city"] = x.get_city();
        j["state"] = x.get_state();
        j["street_address"] = x.get_street_address();
    }

    inline void from_json(const json & j, gen::city::City& x) {
        x.set_addr1(j.at("addr1").get<gen::city::GroupedProperties>());
        x.set_addr2(j.at("addr2").get<gen::city::GroupedProperties>());
    }

    inline void to_json(json & j, const gen::city::City & x) {
        j = json::object();
        j["addr1"] = x.get_addr1();
        j["addr2"] = x.get_addr2();
    }
}
