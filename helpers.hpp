//
// Created by matheus on 17/05/22 following
// Modern C++ programming with test-driven development
// by Jeff Langr.
//
#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace Helpers
{
    static auto Head(const std::string& word) -> std::string
    {
        return word.substr(0, 1);
    }

    static auto Tail(const std::string& word) -> std::string
    {
        return word.substr(1);
    }

    static auto ToUppercase(const std::string& word) -> std::string
    {
        return std::string(1, static_cast<char>(std::toupper(static_cast<unsigned char>(word.front()))));
    }

    static auto IsConsonant(char letter) -> bool
    {
        // We do not consider 'y' to be a vowel here
        letter = static_cast<char>(std::tolower(letter));
        const auto vowels = std::vector<char>{ 'a', 'e', 'i', 'o', 'u' };
        return std::find(std::begin(vowels), std::end(vowels), tolower(letter)) == std::end(vowels);
    }

    static auto IsVowel(char letter) -> bool
    {
        // Given it is alphabetic, it must be consonant or vowel
        return !IsConsonant(letter);
    }

    static auto ConsonantShouldBeIgnored(const char letter) -> bool
    {
        const auto ignored_consonants = std::vector<char>{ 'w', 'h', 'y', 'W', 'H', 'Y' };
        return std::find(std::begin(ignored_consonants), std::end(ignored_consonants), letter) !=
               std::end(ignored_consonants);
    }

    static auto PadWithZeros(const std::string& word, std::size_t desired_size) -> std::string
    {
        const auto zeros_needed = desired_size - word.length();
        return std::string{ word } + std::string(zeros_needed, '0');
    }
} // namespace Helpers
