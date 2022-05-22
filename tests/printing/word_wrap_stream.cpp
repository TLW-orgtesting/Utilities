#include <catch2/catch.hpp>
#include <sstream>
#include <utilities/printing/word_wrap_stream.hpp>
using namespace utilities::printing;
#include <iostream>
TEST_CASE("WordWrapStream") {
    std::stringstream ss;
    std::stringstream corr;
    WordWrapStream p(&ss);
    SECTION("Short sentence") {
        const auto sen = "This is a short sentence under 80 characters long";
        p << sen;
        corr << sen;
        REQUIRE(ss.str() == corr.str());
    }
    SECTION("Long sentence") {
        const std::string p1 =
          "This is a long sentence that exceeds 80 characters in length because"
          " I am not";
        const auto p2 = "being even remotely terse while writing it out on the "
                        "computer screen.";
        p << p1 + " " + p2;
        corr << p1 << std::endl << p2;
        REQUIRE(ss.str() == corr.str());
    }
    SECTION("80+ character word") {
        const std::string p1 = "This sentence has a long string in it";
        const std::string p2(85, 'x');
        p << p1 + " " + p2;
        corr << p1 << std::endl << p2;
        REQUIRE(ss.str() == corr.str());
    }
    SECTION("Sentence with endline") {
        const std::string p1 = "This sentence has a linebreak in it.\n";
        const auto p2        = "This sentence should appear on the next line.";
        p << p1 + p2;
        corr << p1 << p2;
        REQUIRE(ss.str() == corr.str());
    }
    SECTION("Leading spaces") {
        const std::string p1 = "  This sentence has leading spaces.";
        p << p1;
        REQUIRE(ss.str() == p1);
    }
    SECTION("std::endl") {
        const std::string p1 = "Hello world";
        p << p1 << std::endl << p1;
        corr << p1 << std::endl << p1;
        REQUIRE(ss.str() == corr.str());
    }
    SECTION("Multiple lines leading spaces") {
        const std::string p1 = "  This sentence has leading spaces";
        p << p1 << std::endl << p1;
        corr << p1 << std::endl << p1;
        REQUIRE(ss.str() == corr.str());
    }
}
