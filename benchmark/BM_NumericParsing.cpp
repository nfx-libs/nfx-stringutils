/*
 * MIT License
 *
 * Copyright (c) 2025 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file BM_NumericParsing.cpp
 * @brief Benchmark numeric parsing functions
 */

#include <benchmark/benchmark.h>

#include <charconv>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
    //=====================================================================
    // Numeric parsing benchmarks
    //=====================================================================

    //----------------------------------------------
    // Test data
    //----------------------------------------------

    static const std::vector<std::string_view> int_test_strings = {
        "0",
        "42",
        "-123",
        "999999",
        "-987654321",
        "2147483647",
        "-2147483648" };

    static const std::vector<std::string_view> double_test_strings = {
        "0.0",
        "3.14159",
        "-2.71828",
        "123.456",
        "-999.999",
        "1.23e10",
        "-4.56e-7" };

    //----------------------------------------------
    // Integer parsing
    //----------------------------------------------

    static void BM_Std_stoi( ::benchmark::State& state )
    {
        static const std::vector<std::string> int_test_strings_str = {
            "0", "42", "-123", "999999", "-987654321", "2147483647", "-2147483648" };

        for ( auto _ : state )
        {
            for ( const auto& str : int_test_strings_str )
            {
                try
                {
                    int result = std::stoi( str );
                    ::benchmark::DoNotOptimize( result );
                }
                catch ( ... )
                {
                }
            }
        }
    }

    static void BM_Std_from_chars_int( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : int_test_strings )
            {
                int result{ 0 };
                std::from_chars( str.data(), str.data() + str.size(), result );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    static void BM_NFX_fromString_int( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : int_test_strings )
            {
                auto result = nfx::string::fromString<int>( str );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    //----------------------------------------------
    // Double parsing
    //----------------------------------------------

    static void BM_Std_stod( ::benchmark::State& state )
    {
        static const std::vector<std::string> double_test_strings_str = {
            "0.0", "3.14159", "-2.71828", "123.456", "-999.999", "1.23e10", "-4.56e-7" };

        for ( auto _ : state )
        {
            for ( const auto& str : double_test_strings_str )
            {
                try
                {
                    double result = std::stod( str );
                    ::benchmark::DoNotOptimize( result );
                }
                catch ( ... )
                {
                }
            }
        }
    }

    static void BM_Std_from_chars_double( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : double_test_strings )
            {
                double result{ 0.0 };
                std::from_chars( str.data(), str.data() + str.size(), result );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    static void BM_NFX_fromString_double( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : double_test_strings )
            {
                auto result = nfx::string::fromString<double>( str );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_Std_stoi )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_from_chars_int )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_fromString_int )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_stod )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_from_chars_double )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_fromString_double )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
