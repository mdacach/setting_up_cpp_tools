#include "catch.hpp"
#include <string_view>

using namespace std::string_literals;
class Soundex
{
public:
    auto Encode(std::string_view word) const -> std::string { return PadWithZeros(word); }

private:
    auto PadWithZeros(std::string_view word) const -> std::string { return std::string{ word } + "000"; }
};

TEST_CASE("Test Soundex Encoding", "[soundex_encoding]")
{
    const auto soundex = Soundex{};

    SECTION("Retains sole letter of one-letter word")
    {
        const auto encoded = soundex.Encode("A");

        CHECK(encoded == "A000");
    }

    SECTION("Pads zeros until three digits")
    {
        const auto encoded = soundex.Encode("I");

        CHECK(encoded == "I000");
    }
}

// Test list
// Manage one letter words
// Fail when given multiple words as input
// Assert size is always 4
// Test 0 padding