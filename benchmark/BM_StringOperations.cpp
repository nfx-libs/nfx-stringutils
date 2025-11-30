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
 * @file BM_StringOperations.cpp
 * @brief Benchmark string operations
 */

#include <benchmark/benchmark.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
	//=====================================================================
	// String operations benchmarks
	//=====================================================================

	//----------------------------------------------
	// Test data
	//----------------------------------------------

	static const std::string test_string = "The quick brown fox jumps over the lazy dog";
	static const std::vector<std::string> test_strings = {
		"apple",
		"banana",
		"cherry",
		"date",
		"elderberry" };

	//----------------------------------------------
	// StartsWith operations
	//----------------------------------------------

	static void BM_Std_starts_with( ::benchmark::State& state )
	{
		const std::string prefix = "The quick";
		for ( auto _ : state )
		{
			bool result = test_string.starts_with( prefix );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_startsWith( ::benchmark::State& state )
	{
		const std::string_view prefix = "The quick";
		for ( auto _ : state )
		{
			bool result = nfx::string::startsWith( test_string, prefix );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// EndsWith operations
	//----------------------------------------------

	static void BM_Std_ends_with( ::benchmark::State& state )
	{
		const std::string suffix = "lazy dog";
		for ( auto _ : state )
		{
			bool result = test_string.ends_with( suffix );
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_endsWith( ::benchmark::State& state )
	{
		const std::string_view suffix = "lazy dog";
		for ( auto _ : state )
		{
			bool result = nfx::string::endsWith( test_string, suffix );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// Contains operations
	//----------------------------------------------

	static void BM_Std_find_contains( ::benchmark::State& state )
	{
		const std::string search = "brown";
		for ( auto _ : state )
		{
			bool result = test_string.find( search ) != std::string::npos;
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_contains( ::benchmark::State& state )
	{
		const std::string_view search = "brown";
		for ( auto _ : state )
		{
			bool result = nfx::string::contains( test_string, search );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// Count operations
	//----------------------------------------------

	static void BM_Manual_count( ::benchmark::State& state )
	{
		const char target = 'o';
		for ( auto _ : state )
		{
			size_t count = std::count( test_string.begin(), test_string.end(), target );
			::benchmark::DoNotOptimize( count );
		}
	}

	static void BM_NFX_count( ::benchmark::State& state )
	{
		const char target = 'o';
		for ( auto _ : state )
		{
			size_t count = nfx::string::count( test_string, target );
			::benchmark::DoNotOptimize( count );
		}
	}

	static void BM_Manual_countSubstring( ::benchmark::State& state )
	{
		const std::string_view search = "the";
		for ( auto _ : state )
		{
			size_t count = 0;
			size_t pos = 0;
			while ( ( pos = test_string.find( search, pos ) ) != std::string::npos )
			{
				++count;
				pos += search.length();
			}
			::benchmark::DoNotOptimize( count );
		}
	}

	static void BM_NFX_countSubstring( ::benchmark::State& state )
	{
		const std::string_view search = "the";
		for ( auto _ : state )
		{
			size_t count = nfx::string::count( test_string, search );
			::benchmark::DoNotOptimize( count );
		}
	}

	//----------------------------------------------
	// Replace operations
	//----------------------------------------------

	static void BM_Manual_replaceAll( ::benchmark::State& state )
	{
		const std::string from = "o";
		const std::string to = "0";
		for ( auto _ : state )
		{
			std::string result = test_string;
			size_t pos = 0;
			while ( ( pos = result.find( from, pos ) ) != std::string::npos )
			{
				result.replace( pos, from.length(), to );
				pos += to.length();
			}
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_replaceAll( ::benchmark::State& state )
	{
		const std::string_view from = "o";
		const std::string_view to = "0";
		for ( auto _ : state )
		{
			auto result = nfx::string::replaceAll( test_string, from, to );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// Join operations
	//----------------------------------------------

	static void BM_Manual_join( ::benchmark::State& state )
	{
		const std::string delimiter = ", ";
		for ( auto _ : state )
		{
			std::string result;
			for ( size_t i = 0; i < test_strings.size(); ++i )
			{
				if ( i > 0 )
					result += delimiter;
				result += test_strings[i];
			}
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_join( ::benchmark::State& state )
	{
		const std::string_view delimiter = ", ";
		for ( auto _ : state )
		{
			auto result = nfx::string::join( test_strings, delimiter );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// IndexOf operations
	//----------------------------------------------

	static void BM_Std_find( ::benchmark::State& state )
	{
		const std::string search = "brown";
		for ( auto _ : state )
		{
			size_t pos = test_string.find( search );
			::benchmark::DoNotOptimize( pos );
		}
	}

	static void BM_NFX_indexOf( ::benchmark::State& state )
	{
		const std::string_view search = "brown";
		for ( auto _ : state )
		{
			auto pos = nfx::string::indexOf( test_string, search );
			::benchmark::DoNotOptimize( pos );
		}
	}

	//----------------------------------------------
	// LastIndexOf operations
	//----------------------------------------------

	static void BM_Std_rfind( ::benchmark::State& state )
	{
		const std::string search = "the";
		for ( auto _ : state )
		{
			size_t pos = test_string.rfind( search );
			::benchmark::DoNotOptimize( pos );
		}
	}

	static void BM_NFX_lastIndexOf( ::benchmark::State& state )
	{
		const std::string_view search = "the";
		for ( auto _ : state )
		{
			auto pos = nfx::string::lastIndexOf( test_string, search );
			::benchmark::DoNotOptimize( pos );
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_Std_starts_with )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_startsWith )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_ends_with )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_endsWith )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_find_contains )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_contains )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_count )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_count )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_countSubstring )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_countSubstring )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_replaceAll )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_replaceAll )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_join )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_join )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_find )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_indexOf )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_rfind )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_lastIndexOf )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
