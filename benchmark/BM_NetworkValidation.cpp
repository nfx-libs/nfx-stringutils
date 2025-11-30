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
 * @file BM_NetworkValidation.cpp
 * @brief Benchmark network validation functions
 */

#include <benchmark/benchmark.h>

#include <string>
#include <string_view>
#include <vector>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
	//=====================================================================
	// Network validation benchmarks
	//=====================================================================

	//----------------------------------------------
	// Test data
	//----------------------------------------------

	static const std::vector<char> uri_test_chars = {
		'a', 'Z', '0', '9', '-', '.', '_', '~', // Unreserved
		':', '/', '?', '#', '[', ']', '@',		// Gen-delims
		'!', '$', '&', '\'', '(', ')', '*',		// Sub-delims part 1
		'+', ',', ';', '=',						// Sub-delims part 2
		'%', ' '								// Other
	};

	//----------------------------------------------
	// URI reserved character classification
	//----------------------------------------------

	static void BM_Manual_isUriReserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : uri_test_chars )
			{
				bool result = ( c == ':' || c == '/' || c == '?' || c == '#' || c == '[' || c == ']' ||
								c == '@' || c == '!' || c == '$' || c == '&' || c == '\'' || c == '(' ||
								c == ')' || c == '*' || c == '+' || c == ',' || c == ';' || c == '=' );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isUriReserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : uri_test_chars )
			{
				bool result = nfx::string::isUriReserved( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// URI unreserved character classification
	//----------------------------------------------

	static void BM_Manual_isUriUnreserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : uri_test_chars )
			{
				bool result = ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ||
								( c >= '0' && c <= '9' ) || c == '-' || c == '.' || c == '_' || c == '~' );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isUriUnreserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : uri_test_chars )
			{
				bool result = nfx::string::isUriUnreserved( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmark registration
//=====================================================================

BENCHMARK( nfx::string::benchmark::BM_Manual_isUriReserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isUriReserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Manual_isUriUnreserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isUriUnreserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
