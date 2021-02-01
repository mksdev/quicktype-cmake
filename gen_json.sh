input_path="./schema/$1.schema"
output_path="./schema/include/gen/$1.h"
namespace=$1

./quicktype_gen.sh $input_path $output_path $namespace
