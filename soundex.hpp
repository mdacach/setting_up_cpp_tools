//
// Created by matheus on 17/05/22 following
// Modern C++ programming with test-driven development
// by Jeff Langr.
//
#pragma once

#include <string>
#include <unordered_map>

class Soundex
{
    static const std::size_t FIXED_SIZE{ 4 };

public:
    auto Encode(const std::string& word) const -> std::string
    {
        if (!SanitizeInput(word))
            throw std::runtime_error("Input is not allowed. When input: " + word);
        return PadWithZeros(ToUppercase(Head(word)) + Tail(EncodeDigits(word)));
    }

private:
    // Returns true if input is OK, false otherwise.
    auto SanitizeInput(const std::string& word) const -> bool
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
    auto EncodeDigits(const std::string& word) const -> std::string
    {
        auto digits = std::string{};
        // We need to check on the first digit's code, in order to avoid duplication
        const auto first_code = EncodeDigit(word.front());
        digits.push_back(first_code.value_or('*'));

        auto last_letter = char{ '*' };
        auto encoded_consonants = std::size_t{ 0 };
        for (const auto& letter : Tail(word))
        {
            if (IsConsonant(letter) && !ConsonantShouldBeIgnored(letter))
            {
                const auto to_encode = EncodeDigit(letter);
                if (!to_encode.has_value())
                {
                    last_letter = letter;
                    continue;
                }
                const auto value = to_encode.value();
                const auto same_of_last_digit = value == digits.back();
                const auto last_letter_vowel = IsVowel(last_letter);
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

    auto EncodeDigit(char letter) const -> std::optional<char>
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

    auto Head(const std::string& word) const -> std::string { return word.substr(0, 1); }

    auto Tail(const std::string& word) const -> std::string { return word.substr(1); }

    auto ToUppercase(const std::string& word) const -> std::string
    {
        return std::string(1, static_cast<char>(std::toupper(static_cast<unsigned char>(word.front()))));
    }

    auto IsConsonant(char letter) const -> bool
    {
        if (!std::isalpha(letter))
            return false;
        // We do not consider 'y' to be a vowel here
        letter = static_cast<char>(std::tolower(letter));
        const auto vowels = std::vector<char>{ 'a', 'e', 'i', 'o', 'u' };
        return std::find(std::begin(vowels), std::end(vowels), tolower(letter)) == std::end(vowels);
    }

    auto IsVowel(char letter) const -> bool
    {
        if (!std::isalpha(letter))
            return false;
        if (std::isdigit(letter))
            return false;
        // Given it is alphabetic, it must be consonant or vowel
        return !IsConsonant(letter);
    }

    auto ConsonantShouldBeIgnored(const char letter) const -> bool
    {
        const auto ignored_consonants = std::vector<char>{ 'w', 'h', 'y', 'W', 'H', 'Y' };
        return std::find(std::begin(ignored_consonants), std::end(ignored_consonants), letter) !=
               std::end(ignored_consonants);
    }

    auto PadWithZeros(const std::string& word) const -> std::string
    {
        const auto zeros_needed = FIXED_SIZE - word.length();
        return std::string{ word } + std::string(zeros_needed, '0');
    }
};
