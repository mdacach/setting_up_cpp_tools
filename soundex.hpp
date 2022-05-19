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
    auto Encode(const std::string& word) const -> std::string { return PadWithZeros(Head(word) + EncodeDigits(word)); }

private:
    auto Head(const std::string& word) const -> std::string { return word.substr(0, 1); }

    auto EncodeDigits(const std::string& word) const -> std::string
    {
        if (word.length() >= 2)
            return EncodeDigit(word.at(1));
        return "";
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
