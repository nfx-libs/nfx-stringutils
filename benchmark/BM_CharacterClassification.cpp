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
 * @file BM_CharacterClassification.cpp
 * @brief Benchmark character classification functions
 */

#include <benchmark/benchmark.h>

#include <cctype>
#include <vector>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
	//=====================================================================
	// Character classification benchmarks
	//=====================================================================

	//----------------------------------------------
	// Test data
	//----------------------------------------------

	static const std::vector<char> test_chars = {
		'a', 'Z', '5', ' ', '\t', '\n', '!', '@', '#', '_', '-', '.', '~' };

	//----------------------------------------------
	// Whitespace classification
	//----------------------------------------------

	static void BM_Std_isspace( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = static_cast<bool>( std::isspace( static_cast<unsigned char>( c ) ) );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isWhitespace( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = nfx::string::isWhitespace( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Digit classification
	//----------------------------------------------

	static void BM_Std_isdigit( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = static_cast<bool>( std::isdigit( static_cast<unsigned char>( c ) ) );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isDigit( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = nfx::string::isDigit( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Alpha classification
	//----------------------------------------------

	static void BM_Std_isalpha( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = static_cast<bool>( std::isalpha( static_cast<unsigned char>( c ) ) );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isAlpha( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = nfx::string::isAlpha( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_Std_isspace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isWhitespace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_isdigit )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isDigit )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_isalpha )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isAlpha )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
