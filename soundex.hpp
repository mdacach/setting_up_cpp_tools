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
        return PadWithZeros(Head(word) + EncodeDigits(Tail(word)));
    }

private:
    auto Head(const std::string& word) const -> std::string { return word.substr(0, 1); }

    auto Tail(const std::string& word) const -> std::string { return word.substr(1); }

    auto EncodeDigits(const std::string& word) const -> std::string
    {
        auto digits = std::string{};
        auto encoded_consonants = std::size_t{ 0 };
        for (const auto& letter : word)
        {
            if (IsConsonant(letter) && !ConsonantShouldBeIgnored(letter))
            {
                const auto to_encode = EncodeDigit(letter).front();
                if (digits.empty() || to_encode != digits.back())
                {
                    digits.push_back(to_encode);
                    ++encoded_consonants;
                }
            }
            if (encoded_consonants + 1 == FIXED_SIZE) // We already have the first letter "as is"
                break;
        }
        return digits;
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
        const auto ignored_consonants = std::vector<char>{ 'w', 'h', 'y' };
        return std::find(std::begin(ignored_consonants), std::end(ignored_consonants), letter) !=
               std::end(ignored_consonants);
    }

    auto EncodeDigit(const char letter) const -> std::string
    {
        // clang-format off
        const static std::unordered_map<char, std::string> encodings
        {
            { 'b', "1" }, { 'f', "1" }, { 'p', "1" }, { 'v', "1" },
            { 'c', "2" }, { 'g', "2" }, { 'j', "2" }, { 'k', "2" }, { 'q', "2" },
                               { 's', "2" }, { 'x', "2" }, { 'z', "2"},
            { 'd', "3" }, { 't', "3" },
            { 'l', "4" },
            { 'm', "5" }, { 'n', "5" },
            { 'r', "6" },
        };
        // clang-format on

        const auto& item = encodings.find(letter);
        return item == std::end(encodings) ? "" : item->second;
    }

    auto PadWithZeros(const std::string& word) const -> std::string
    {
        const auto zeros_needed = FIXED_SIZE - word.length();
        return std::string{ word } + std::string(zeros_needed, '0');
    }
};
