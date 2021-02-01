//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     City data = nlohmann::json::parse(jsonString);

#pragma once

#include <json.hpp>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}
#endif

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

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    struct GroupedProperties {
        std::string city;
        std::shared_ptr<std::string> state;
        std::string street_address;
    };

    struct City {
        GroupedProperties addr1;
        GroupedProperties addr2;
    };
}
}

namespace nlohmann {
    void from_json(const json & j, gen::city::GroupedProperties & x);
    void to_json(json & j, const gen::city::GroupedProperties & x);

    void from_json(const json & j, gen::city::City & x);
    void to_json(json & j, const gen::city::City & x);

    inline void from_json(const json & j, gen::city::GroupedProperties& x) {
        x.city = j.at("city").get<std::string>();
        x.state = gen::city::get_optional<std::string>(j, "state");
        x.street_address = j.at("street_address").get<std::string>();
    }

    inline void to_json(json & j, const gen::city::GroupedProperties & x) {
        j = json::object();
        j["city"] = x.city;
        j["state"] = x.state;
        j["street_address"] = x.street_address;
    }

    inline void from_json(const json & j, gen::city::City& x) {
        x.addr1 = j.at("addr1").get<gen::city::GroupedProperties>();
        x.addr2 = j.at("addr2").get<gen::city::GroupedProperties>();
    }

    inline void to_json(json & j, const gen::city::City & x) {
        j = json::object();
        j["addr1"] = x.addr1;
        j["addr2"] = x.addr2;
    }
}
