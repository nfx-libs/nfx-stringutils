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
 * @file BM_Splitter.cpp
 * @brief Benchmark Splitter string splitting performance vs manual approaches
 */

#include <benchmark/benchmark.h>

#include <string_view>
#include <vector>

#include <nfx/string/Splitter.h>

namespace nfx::string::benchmark
{
	//=====================================================================
	// Splitter benchmark suite
	//=====================================================================

	//----------------------------------------------
	// Test data
	//----------------------------------------------

	static const std::string csvData = "John,Doe,30,Engineer,NewYork,75000,Active,2023-01-15";
	static const std::string pathData = "VE/400a/400/C101.31/S206/H346.11112/meta";
	static const std::string configData = "server=localhost;port=8080;database=mydb;timeout=30;ssl=true;debug=false";

	//----------------------------------------------
	// Manual vs Splitter with CSV data
	//----------------------------------------------

	class ManualSplitter
	{
	public:
		static void split( std::string_view input, char delimiter, std::vector<std::string_view>& output )
		{
			output.clear();

			size_t start = 0;
			size_t pos = 0;

			while ( ( pos = input.find( delimiter, start ) ) != std::string_view::npos )
			{
				output.emplace_back( input.substr( start, pos - start ) );
				start = pos + 1;
			}

			if ( start <= input.length() )
			{
				output.emplace_back( input.substr( start ) );
			}
		}
	};

	//----------------------------
	// Manual with CSV data
	//----------------------------

	static void BM_Manual_CSV( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			ManualSplitter::split( csvData, ',', segments );
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------
	// Splitter with CSV data
	//----------------------------

	static void BM_Splitter_CSV( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			segments.clear();
			for ( const auto segment : nfx::string::Splitter{ csvData, ',' } )
			{
				segments.emplace_back( segment );
			}
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------
	// SplitView with CSV data
	//----------------------------

	static void BM_SplitView_CSV( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			segments.clear();
			for ( const auto segment : nfx::string::splitView( csvData, ',' ) )
			{
				segments.emplace_back( segment );
			}
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------------------------
	// Manual vs Splitter with path data
	//----------------------------------------------

	//----------------------------
	// Manual with path data
	//----------------------------

	static void BM_Manual_Path( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			ManualSplitter::split( pathData, '/', segments );
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------
	// Splitter with path data
	//----------------------------

	static void BM_Splitter_Path( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			segments.clear();
			for ( const auto segment : nfx::string::Splitter{ pathData, '/' } )
			{
				segments.emplace_back( segment );
			}
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------
	// SplitView with path data
	//----------------------------

	static void BM_SplitView_Path( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			segments.clear();
			for ( const auto segment : nfx::string::splitView( pathData, '/' ) )
			{
				segments.emplace_back( segment );
			}
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------------------------
	// Manual vs Splitter with config data
	//----------------------------------------------

	//----------------------------
	// Manual with config data
	//----------------------------

	static void BM_Manual_Config( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			ManualSplitter::split( configData, ';', segments );
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------
	// Splitter with config data
	//----------------------------

	static void BM_Splitter_Config( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			segments.clear();
			for ( const auto segment : nfx::string::Splitter{ configData, ';' } )
			{
				segments.emplace_back( segment );
			}
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------
	// SplitView with config data
	//----------------------------

	static void BM_SplitView_Config( ::benchmark::State& state )
	{
		std::vector<std::string_view> segments;

		for ( auto _ : state )
		{
			segments.clear();
			for ( const auto segment : nfx::string::splitView( configData, ';' ) )
			{
				segments.emplace_back( segment );
			}
			::benchmark::DoNotOptimize( segments );
		}
	}

	//----------------------------------------------
	// Zero-allocation
	//----------------------------------------------

	static void BM_Splitter_ZeroAlloc( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			size_t count = 0;
			for ( const auto segment : nfx::string::Splitter{ csvData, ',' } )
			{
				count += segment.length();
			}
			::benchmark::DoNotOptimize( count );
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmarks registration
//=====================================================================

//----------------------------------------------
// Manual vs Splitter with CSV data
//----------------------------------------------

//----------------------------
// Manual with CSV data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_CSV )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Splitter with CSV data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Splitter_CSV )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// SplitView with CSV data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_SplitView_CSV )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Path benchmarks with improved accuracy
//----------------------------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_Path )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Splitter with path data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Splitter_Path )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// SplitView with path data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_SplitView_Path )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Config benchmarks with improved accuracy
//----------------------------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_Config )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Splitter with config data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Splitter_Config )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// SplitView with config data
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_SplitView_Config )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Zero-allocation with enhanced precision
//----------------------------------------------

BENCHMARK( nfx::string::benchmark::BM_Splitter_ZeroAlloc )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
