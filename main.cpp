#include <iostream>

#include <gen/city.h>

int main() {
    std::string js = "{\n"
                        "\t\"addr1\": {\n"
                        "\t   \"street_address\": \"1600 Pennsylvania Avenue NW\",\n"
                        "\t   \"city\": \"Washington\",\n"
                        "\t   \"state\": \"DC\"\n"
                        "\t},\n"
                        "\t\"addr2\": {\n"
                        "\t   \"street_address\": \"1600 Pennsylvania Avenue NW\",\n"
                        "\t   \"city\": \"Praha\",\n"
                        "\t   \"state\": \"DC\"\n"
                        "\t}\n"
                        "}";

    gen::city::City city = nlohmann::json::parse(js);

    return 0;
}
