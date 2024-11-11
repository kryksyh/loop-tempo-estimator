/*  SPDX-License-Identifier: GPL-2.0-or-later */
/*!********************************************************************

  Audacity: A Digital Audio Editor

  MathApproxTest.cpp

  Matthieu Hodgkinson

**********************************************************************/
/*

 This file was copied from Audacity 3.5.1,
 https://github.com/audacity/audacity/releases/tag/Audacity-3.5.1.

 Modifications might have been made to remove dependencies on Audacity code and
 when renaming files. The algorithm remains the same.

EDIT: Commit "Simplify and improve algorithm by considering only 4/4" improves
quality of classifier and possibly time performance, too.

 */

#include "MathApprox.h"
#include <algorithm>
#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include <numeric>

TEST_CASE("FastLog2")
{
   constexpr auto size = 40;
   const auto input = [&] {
      std::vector<float> exponential(size);
      std::iota(exponential.begin(), exponential.end(), -20.f);
      std::vector<float> input(exponential.size());
      std::transform(
         exponential.begin(), exponential.end(), input.begin(),
         [](float x) { return std::exp(x); });
      return input;
   }();
   const auto expected = [&] {
      std::vector<float> expected(size);
      std::transform(input.begin(), input.end(), expected.begin(), [](float x) {
         return std::log2(x);
      });
      return expected;
   }();
   const auto actual = [&] {
      std::vector<float> actual(size);
      std::transform(input.begin(), input.end(), actual.begin(), FastLog2);
      return actual;
   }();
   const auto error = [&] {
      std::vector<float> error(size);
      std::transform(
         expected.begin(), expected.end(), actual.begin(), error.begin(),
         [](float e, float a) { return std::abs(e - a); });
      return error;
   }();
   const auto maxError = *std::max_element(error.begin(), error.end());
   REQUIRE(maxError < 1e-2);
}
