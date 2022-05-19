#include "catch.hpp"

#include "../soundex.hpp"

TEST_CASE("Test Soundex Encoding", "[soundex_encoding]")
{
    const auto soundex = Soundex{};

    SECTION("Retains sole letter of one-letter word")
    {
        CHECK(soundex.Encode("A") == "A000");
    }

    SECTION("Pads zeros until three digits")
    {
        CHECK(soundex.Encode("I") == "I000");
    }

    SECTION("Replaces consonants with appropriate digits")
    {
        CHECK(soundex.Encode("Ab") == "A100");
        CHECK(soundex.Encode("Ac") == "A200");
        CHECK(soundex.Encode("Ad") == "A300");
        CHECK(soundex.Encode("Af") == "A100");
        CHECK(soundex.Encode("Bf") == "B100");
        CHECK(soundex.Encode("Dd") == "D300");
        CHECK(soundex.Encode("Fm") == "F500");
        CHECK(soundex.Encode("Mm") == "M500");
    }
}

// Test list
// Manage one letter words
// Fail when given multiple words as input
// Assert size is always 4
// Test 0 padding