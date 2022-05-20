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
        return PadWithZeros(ToUppercase(Head(word)) + Tail(EncodeDigits(word)));
    }

private:
    auto EncodeDigits(const std::string& word) const -> std::string
    {
        auto digits = std::string{};
        // We need to check on the first digit's code, in order to avoid duplication
        const auto first_code = EncodeDigit(word.front());
        digits.push_back(first_code.value_or('*'));

        auto encoded_consonants = std::size_t{ 0 };
        for (const auto& letter : Tail(word))
        {
            if (IsConsonant(letter) && !ConsonantShouldBeIgnored(letter))
            {
                const auto to_encode = EncodeDigit(letter);
                if (!to_encode.has_value())
                    continue;
                const auto value = to_encode.value();
                if (digits.empty() || value != digits.back())
                {
                    digits.push_back(value);
                    ++encoded_consonants;
                }
            }
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

    auto IsConsonant(const char letter) const -> bool
    {
        if (!std::isalpha(letter))
            return false;
        // We do not consider 'y' to be a vowel here
        const auto vowels = std::vector<char>{ 'a', 'e', 'i', 'o', 'u' };
        return std::find(std::begin(vowels), std::end(vowels), tolower(letter)) == std::end(vowels);
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
