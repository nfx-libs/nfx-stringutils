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
 * @file BM_StringValidation.cpp
 * @brief Benchmark string validation functions
 */

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cctype>
#include <string_view>
#include <vector>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
    //=====================================================================
    // String validation benchmarks
    //=====================================================================

    //----------------------------------------------
    // Test data
    //----------------------------------------------

    static const std::vector<std::string_view> test_strings = {
        "",
        "a",
        "Hello",
        "Hello World",
        "The quick brown fox jumps over the lazy dog",
        "   whitespace test   ",
        "12345",
        "abc123def",
        "UPPERCASE",
        "lowercase",
        "MixedCase",
        "https://example.com/path?query=value",
        "true",
        "false",
        "123456789",
        "-987654321",
        "3.14159",
        "not_a_number" };

    //----------------------------------------------
    // Empty string validation
    //----------------------------------------------

    static void BM_Std_empty( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : test_strings )
            {
                bool result = str.empty();
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    static void BM_NFX_isEmpty( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : test_strings )
            {
                bool result = nfx::string::isEmpty( str );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    //----------------------------------------------
    // Null or whitespace validation
    //----------------------------------------------

    static void BM_Manual_isNullOrWhiteSpace( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : test_strings )
            {
                bool result = str.empty() || std::all_of( str.begin(), str.end(),
                                                 []( char c ) { return std::isspace( static_cast<unsigned char>( c ) ); } );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    static void BM_NFX_isNullOrWhiteSpace( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : test_strings )
            {
                bool result = nfx::string::isNullOrWhiteSpace( str );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    //----------------------------------------------
    // All digits validation
    //----------------------------------------------

    static void BM_Manual_isAllDigits( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : test_strings )
            {
                bool result = !str.empty() && std::all_of( str.begin(), str.end(),
                                                  []( char c ) { return std::isdigit( static_cast<unsigned char>( c ) ); } );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }

    static void BM_NFX_isAllDigits( ::benchmark::State& state )
    {
        for ( auto _ : state )
        {
            for ( const auto& str : test_strings )
            {
                bool result = nfx::string::isAllDigits( str );
                ::benchmark::DoNotOptimize( result );
            }
        }
    }
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_Std_empty )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isEmpty )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_isNullOrWhiteSpace )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isNullOrWhiteSpace )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_isAllDigits )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isAllDigits )
    ->MinTime( 1.0 )
    ->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
