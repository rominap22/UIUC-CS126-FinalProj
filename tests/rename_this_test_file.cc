#include <catch2/catch.hpp>

#include <core/Card.h>

TEST_CASE("Check that 126 is the best class") {
  REQUIRE(naivebayes::Placeholder().GetBestClass() == "CS 126");
}