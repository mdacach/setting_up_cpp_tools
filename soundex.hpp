//
// Created by matheus on 17/05/22 following
// Modern C++ programming with test-driven development
// by Jeff Langr.
//
#pragma once

#include <string>
#include <unordered_map>

#include "helpers.hpp"

class Soundex
{
    static const std::size_t FIXED_SIZE{ 4 };

public:
    static auto Encode(const std::string& word) -> std::string
    {
        if (!SanitizeInput(word))
            throw std::runtime_error("Input is not allowed. When input: " + word);
        const auto encoding = [&word]
        {
            auto first_letter = Helpers::ToUppercase(Helpers::Head(word));
            auto tail_encoding = Helpers::Tail(EncodeDigits(word));
            return first_letter + tail_encoding;
        }();
        return Helpers::PadWithZeros(encoding, FIXED_SIZE);
    }

private:
    // Returns true if input is OK, false otherwise.
    static auto SanitizeInput(const std::string& word) -> bool
    {
        if (std::size(word) == 0)
            return false;
        return std::all_of(std::cbegin(word), std::cend(word),
                           [](char c)
                           {
                               // We need the cast here because:
                               // https://en.cppreference.com/w/cpp/string/byte/isalpha See notes
                               return std::isalpha(static_cast<unsigned char>(c));
                           });
    }

    static auto EncodeDigits(const std::string& word) -> std::string
    {
        auto digits = std::string{};
        // We need to check on the first digit's code, in order to avoid duplication
        const auto first_code = EncodeDigit(word.front());
        digits.push_back(first_code.value_or('*'));

        auto last_letter = char{ '*' };
        auto encoded_consonants = std::size_t{ 0 };
        for (const auto& letter : Helpers::Tail(word))
        {
            if (Helpers::IsConsonant(letter) && !Helpers::ConsonantShouldBeIgnored(letter))
            {
                const auto to_encode = EncodeDigit(letter);
                if (!to_encode.has_value())
                {
                    last_letter = letter;
                    continue;
                }
                const auto value = to_encode.value();
                const auto same_of_last_digit = value == digits.back();
                const auto last_letter_vowel = Helpers::IsVowel(last_letter);
                if (digits.empty() || (!same_of_last_digit || last_letter_vowel))
                {
                    digits.push_back(value);
                    ++encoded_consonants;
                }
            }
            last_letter = letter;
            if (encoded_consonants + 1 == FIXED_SIZE) // We already have the first letter "as is"
                break;
        }
        return digits;
    }

    static auto EncodeDigit(char letter) -> std::optional<char>
    {
        // clang-format off
        const static std::unordered_map<char, char> encodings
            {
                { 'b', '1' }, { 'f', '1' }, { 'p', '1' }, { 'v', '1' },
                { 'c', '2' }, { 'g', '2' }, { 'j', '2' }, { 'k', '2' }, { 'q', '2' },
                { 's', '2' }, { 'x', '2' }, { 'z', '2'},
                { 'd', '3' }, { 't', '3' },
                { 'l', '4' },
                { 'm', '5' }, { 'n', '5' },
                { 'r', '6' },
            };
        // clang-format on

        letter = static_cast<char>(tolower(letter));
        const auto& item = encodings.find(letter);
        if (item == std::end(encodings))
            return std::nullopt;
        return item->second;
    }
};
