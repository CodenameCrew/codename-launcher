find ./src \( -name '*.c' -o -name '*.cpp' -o -name '*.m' -o -name '*.mm' -o -name '*.h' -o -name '*.hpp' \) | grep -v './src/rapidjson/' | xargs clang-format -i
