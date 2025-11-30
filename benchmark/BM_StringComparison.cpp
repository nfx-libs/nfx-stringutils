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
 * @file BM_StringComparison.cpp
 * @brief Benchmark string comparison functions
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
	// String comparison benchmarks
	//=====================================================================

	//----------------------------------------------
	// Test data
	//----------------------------------------------

	static const std::vector<std::pair<std::string_view, std::string_view>> comparison_test_pairs = {
		{ "apple", "APPLE" },
		{ "apple", "BANANA" },
		{ "zebra", "APPLE" },
		{ "Hello", "hello" },
		{ "test", "TEST" },
		{ "ABC", "abc" } };

	static const std::vector<std::pair<std::string_view, std::string_view>> natural_test_pairs = {
		{ "file2.txt", "file10.txt" },
		{ "v1.9", "v1.10" },
		{ "chapter2", "chapter10" },
		{ "test1", "test2" },
		{ "abc123", "abc456" } };

	static const std::vector<std::pair<std::string_view, std::string_view>> prefix_test_pairs = {
		{ "/usr/local/bin", "/usr/local/lib" },
		{ "testing", "tester" },
		{ "file_1.txt", "file_2.txt" },
		{ "Hello", "World" },
		{ "abcdefgh", "abcxyz" } };

	static const std::vector<std::pair<std::string_view, std::string_view>> suffix_test_pairs = {
		{ "file1.txt", "file2.txt" },
		{ "testing", "running" },
		{ "unit_test.cpp", "integration_test.cpp" },
		{ "Hello", "World" },
		{ "abcxyz", "defxyz" } };

	//----------------------------------------------
	// Case-insensitive comparison
	//----------------------------------------------

	static void BM_Manual_equalsIgnoreCase( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : comparison_test_pairs )
			{
				bool result = false;
				if ( lhs.size() == rhs.size() )
				{
					result = std::equal( lhs.begin(), lhs.end(), rhs.begin(),
						[]( char a, char b ) {
							return std::tolower( static_cast<unsigned char>( a ) ) ==
								   std::tolower( static_cast<unsigned char>( b ) );
						} );
				}
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_equalsIgnoreCase( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : comparison_test_pairs )
			{
				bool result = ( nfx::string::compareIgnoreCase( lhs, rhs ) == 0 );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Manual_compareIgnoreCase( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : comparison_test_pairs )
			{
				int result = 0;
				auto it1 = lhs.begin();
				auto it2 = rhs.begin();
				while ( it1 != lhs.end() && it2 != rhs.end() )
				{
					char c1 = static_cast<char>( std::tolower( static_cast<unsigned char>( *it1 ) ) );
					char c2 = static_cast<char>( std::tolower( static_cast<unsigned char>( *it2 ) ) );
					if ( c1 != c2 )
					{
						result = ( c1 < c2 ) ? -1 : 1;
						break;
					}
					++it1;
					++it2;
				}
				if ( result == 0 )
				{
					if ( it1 != lhs.end() )
						result = 1;
					else if ( it2 != rhs.end() )
						result = -1;
				}
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_compareIgnoreCase( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : comparison_test_pairs )
			{
				auto result = nfx::string::compareIgnoreCase( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Natural comparison
	//----------------------------------------------

	static void BM_Std_compare( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : natural_test_pairs )
			{
				auto result = lhs.compare( rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_naturalCompare( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : natural_test_pairs )
			{
				auto result = nfx::string::naturalCompare( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Common prefix operations
	//----------------------------------------------

	static void BM_Manual_commonPrefix( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : prefix_test_pairs )
			{
				// Manual common prefix
				size_t minLen = std::min( lhs.size(), rhs.size() );
				size_t i = 0;
				while ( i < minLen && lhs[i] == rhs[i] )
				{
					++i;
				}
				auto result = lhs.substr( 0, i );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_commonPrefix( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : prefix_test_pairs )
			{
				auto result = nfx::string::commonPrefix( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Common suffix operations
	//----------------------------------------------

	static void BM_Manual_commonSuffix( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : suffix_test_pairs )
			{
				// Manual common suffix
				size_t minLen = std::min( lhs.size(), rhs.size() );
				size_t i = 0;
				while ( i < minLen && lhs[lhs.size() - 1 - i] == rhs[rhs.size() - 1 - i] )
				{
					++i;
				}
				auto result = ( i > 0 ) ? lhs.substr( lhs.size() - i ) : std::string_view{};
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_commonSuffix( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : suffix_test_pairs )
			{
				auto result = nfx::string::commonSuffix( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_Manual_equalsIgnoreCase )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_equalsIgnoreCase )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_compareIgnoreCase )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_compareIgnoreCase )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_compare )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_naturalCompare )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_commonPrefix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_commonPrefix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_commonSuffix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_commonSuffix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
