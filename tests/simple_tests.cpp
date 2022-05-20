#include "catch.hpp"

#include "../soundex.hpp"

TEST_CASE("Test Soundex Encoding", "[Soundex::encoding]")
{

    SECTION("Retains sole letter of one-letter word")
    {
        CHECK(Soundex::Encode("A") == "A000");
    }

    SECTION("Pads zeros until three digits")
    {
        CHECK(Soundex::Encode("I") == "I000");
    }

    SECTION("Replaces non-repeated consonants with appropriate digits")
    {
        CHECK(Soundex::Encode("Ab") == "A100");
        CHECK(Soundex::Encode("Ac") == "A200");
        CHECK(Soundex::Encode("Ad") == "A300");
        CHECK(Soundex::Encode("Af") == "A100");
        CHECK(Soundex::Encode("Fm") == "F500");
    }

    SECTION("Ignores repeated adjacent consonants codes")
    {
        CHECK(Soundex::Encode("Bf") == "B000");
        CHECK(Soundex::Encode("Dd") == "D000");
        CHECK(Soundex::Encode("Mm") == "M000");
    }

    SECTION("Replaces multiple consonants with digits")
    {
        CHECK(Soundex::Encode("Acdl") == "A234");
    }

    SECTION("Limits length to four characters")
    {
        CHECK(Soundex::Encode("Dcdlb").length() == 4);
    }

    SECTION("Ignores vowel like letters")
    {
        CHECK(Soundex::Encode("Baeiouhycdl") == "B234");
    }

    SECTION("Combines duplicated encodings when all are duplicated")
    {
        // Note that 'b' and 'f' both encode to '1'
        // 'c' and 'g' both encode to '2'
        // and 'd' and 't' both encode to '3'
        CHECK(Soundex::Encode("Abfcgdt") == "A123");
    }

    SECTION("Combines duplicated encodings")
    {
        CHECK(Soundex::Encode("Abdtl") == "A134");
    }

    SECTION("Makes first letter uppercase")
    {
        CHECK(Soundex::Encode("abcd").front() == 'A');
    }

    SECTION("Ignores vowel-like letters")
    {
        CHECK(Soundex::Encode("BaAeEiIoOuUhHyYcdl") == "B234");
    }

    SECTION("Ignores case when encoding consonants")
    {
        CHECK(Soundex::Encode("BCDL") == Soundex::Encode("Bcdl"));
    }

    SECTION("Combines duplicate codes when 2nd letter duplicates 1st")
    {
        CHECK(Soundex::Encode("Bbcd") == "B230");
    }

    SECTION("Does not combine duplicate encoding separated by vowels")
    {
        CHECK(Soundex::Encode("Jbob") == "J110");
    }

    SECTION("Should throw on input with non-alphabetic letters")
    {
        CHECK_THROWS(Soundex::Encode("Mr.Smith"));
        CHECK_THROWS(Soundex::Encode("123"));
        CHECK_THROWS(Soundex::Encode("Normalwordbutnumber4"));
        CHECK_THROWS(Soundex::Encode("Some sentence with spaces"));
        CHECK_THROWS(Soundex::Encode(":/',f"));
    }

    SECTION("Should throw on empty string")
    {
        CHECK_THROWS(Soundex::Encode(""));
    }
}

// Test list
// Manage one letter words
// Fail when given multiple words as input
// Assert size is always 4
// Test 0 padding