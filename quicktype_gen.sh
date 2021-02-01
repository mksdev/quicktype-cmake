quicktype --no-boost --lang c++ --namespace gen::$3 -s schema "$1" -o "$2"

# fix local include to global include path
search='#include "json.hpp"'
replace='#include <json.hpp>'

sed -i "" "s/${search}/${replace}/g" "$2"
