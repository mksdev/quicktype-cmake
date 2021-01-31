quicktype --no-boost --lang c++ --namespace gen::$3 -s schema "$1" -o "$2"

search='#include "json.hpp"'
replace='#include <json.hpp>'

# Note the double quotes
sed -i "" "s/${search}/${replace}/g" "$2"
