#include "catch.hpp"
#include <string_view>

class Soundex
{
public:
    auto Encode(std::string_view word) const -> std::string { return std::string{ word }; }
};

TEST_CASE("Retains sole letter of one-letter word", "[soundex_encoding]")
{
    auto soundex = Soundex{};

    auto encoded = soundex.Encode("A");

    CHECK(encoded == "A");
}

// Test list
// Manage one letter words
// Fail when given multiple words as input
// Assert size is always 4
// Test 0 padding