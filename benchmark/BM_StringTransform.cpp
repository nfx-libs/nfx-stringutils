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
 * @file BM_StringTransform.cpp
 * @brief Benchmark string transformation functions
 */

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
	//=====================================================================
	// String transformation benchmarks
	//=====================================================================

	//----------------------------------------------
	// Test data
	//----------------------------------------------

	static const std::string test_string = "The quick brown fox jumps over the lazy dog";
	static const std::string whitespace_string = "   whitespace test   ";

	//----------------------------------------------
	// Trim operations
	//----------------------------------------------

	static void BM_NFX_trim( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			auto result = nfx::string::trim( whitespace_string );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_trimStart( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			auto result = nfx::string::trimStart( whitespace_string );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_trimEnd( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			auto result = nfx::string::trimEnd( whitespace_string );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// Case conversion operations
	//----------------------------------------------

	static void BM_Manual_toLower( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			std::string result = test_string;
			std::transform( result.begin(), result.end(), result.begin(),
				[]( char c ) { return static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) ); } );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_toLower( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			auto result = nfx::string::toLower( test_string );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_Manual_toUpper( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			std::string result = test_string;
			std::transform( result.begin(), result.end(), result.begin(),
				[]( char c ) { return static_cast<char>( std::toupper( static_cast<unsigned char>( c ) ) ); } );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_toUpper( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			auto result = nfx::string::toUpper( test_string );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// Substring extraction operations
	//----------------------------------------------

	static void BM_NFX_substringBefore( ::benchmark::State& state )
	{
		const std::string_view delimiter = "brown";
		for ( auto _ : state )
		{
			auto result = nfx::string::substringBefore( test_string, delimiter );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_substringAfter( ::benchmark::State& state )
	{
		const std::string_view delimiter = "brown";
		for ( auto _ : state )
		{
			auto result = nfx::string::substringAfter( test_string, delimiter );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_substringBeforeLast( ::benchmark::State& state )
	{
		const std::string_view delimiter = "o";
		for ( auto _ : state )
		{
			auto result = nfx::string::substringBeforeLast( test_string, delimiter );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_substringAfterLast( ::benchmark::State& state )
	{
		const std::string_view delimiter = "o";
		for ( auto _ : state )
		{
			auto result = nfx::string::substringAfterLast( test_string, delimiter );
			::benchmark::DoNotOptimize( result );
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_NFX_trim )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_trimStart )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_trimEnd )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_toLower )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_toLower )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_toUpper )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_toUpper )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_substringBefore )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_substringAfter )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_substringBeforeLast )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_substringAfterLast )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
