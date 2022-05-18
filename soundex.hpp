//
// Created by matheus on 17/05/22 following
// Modern C++ programming with test-driven development
// by Jeff Langr.
//
#pragma once

#include <string>
#include <string_view>

using namespace std::string_literals;
class Soundex
{
public:
    auto Encode(std::string_view word) const -> std::string { return PadWithZeros(word); }

private:
    auto PadWithZeros(std::string_view word) const -> std::string { return std::string{ word } + "000"; }
};
