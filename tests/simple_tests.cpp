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

    SECTION("Ignores Non Alphabetics")
    {
        CHECK(soundex.Encode("A#") == "A000");
    }

    SECTION("Replaces multiple consonants with digits")
    {
        CHECK(soundex.Encode("Acdl") == "A234");
    }

    SECTION("Limits length to four characters")
    {
        CHECK(soundex.Encode("Dcdlb").length() == 4);
    }

    SECTION("Ignores vowel like letters")
    {
        CHECK(soundex.Encode("Baeiouhycdl") == "B234");
    }

    SECTION("Combines duplicated encodings when all are duplicated")
    {
        // Note that 'b' and 'f' both encode to '1'
        // 'c' and 'g' both encode to '2'
        // and 'd' and 't' both encode to '3'
        CHECK(soundex.Encode("Abfcgdt") == "A123");
    }

    SECTION("Combines duplicated encodings")
    {
        CHECK(soundex.Encode("Abdtl") == "A134");
    }
}

// Test list
// Manage one letter words
// Fail when given multiple words as input
// Assert size is always 4
// Test 0 padding