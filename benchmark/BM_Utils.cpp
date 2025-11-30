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
 * @file BM_StringUtilities.cpp
 * @brief Benchmark nfx::string::Utils performance vs standard library implementations
 */

#include <benchmark/benchmark.h>

#include <algorithm>
#include <charconv>
#include <cctype>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include <nfx/string/Utils.h>

namespace nfx::string::benchmark
{
	//=====================================================================
	// StringUtilities benchmark suite
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

	static const std::vector<char> test_chars = {
		'a', 'Z', '5', ' ', '\t', '\n', '!', '@', '#', '_', '-', '.', '~' };

	//----------------------------------------------
	// Character classification
	//----------------------------------------------

	//----------------------------
	// Spaces
	//----------------------------

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

	//----------------------------
	// Digit
	//----------------------------

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

	//----------------------------
	// Alpha
	//----------------------------

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

	//----------------------------------------------
	// String validation
	//----------------------------------------------

	//----------------------------
	// Empty
	//----------------------------

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

	//----------------------------
	// Null or whitespace
	//----------------------------

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

	//----------------------------
	// All digits
	//----------------------------

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

	//----------------------------------------------
	// String operations
	//----------------------------------------------

	//----------------------------
	// Starts with
	//----------------------------

	static void BM_Std_starts_with( ::benchmark::State& state )
	{
		const std::string_view prefix = "Hello";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				bool result = str.starts_with( prefix );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_startsWith( ::benchmark::State& state )
	{
		const std::string_view prefix = "Hello";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				bool result = nfx::string::startsWith( str, prefix );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Ends with
	//----------------------------

	static void BM_Std_ends_with( ::benchmark::State& state )
	{
		const std::string_view suffix = "dog";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				bool result = str.ends_with( suffix );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_endsWith( ::benchmark::State& state )
	{
		const std::string_view suffix = "dog";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				bool result = nfx::string::endsWith( str, suffix );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Contains
	//----------------------------

	static void BM_Std_contains( ::benchmark::State& state )
	{
		const std::string_view substr = "fox";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				bool result = str.find( substr ) != std::string_view::npos;
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_contains( ::benchmark::State& state )
	{
		const std::string_view substr = "fox";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				bool result = nfx::string::contains( str, substr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Counting operations
	//----------------------------------------------

	static void BM_Manual_count_substr( ::benchmark::State& state )
	{
		const std::string_view substr = "l";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				std::size_t count = 0;
				std::size_t pos = 0;
				while ( ( pos = str.find( substr, pos ) ) != std::string_view::npos )
				{
					++count;
					pos += substr.length();
				}
				::benchmark::DoNotOptimize( count );
			}
		}
	}

	static void BM_NFX_count_substr( ::benchmark::State& state )
	{
		const std::string_view substr = "l";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::count( str, substr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Manual_count_char( ::benchmark::State& state )
	{
		const char ch = 'l';
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				std::size_t count = 0;
				for ( char c : str )
				{
					if ( c == ch )
						++count;
				}
				::benchmark::DoNotOptimize( count );
			}
		}
	}

	static void BM_NFX_count_char( ::benchmark::State& state )
	{
		const char ch = 'l';
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::count( str, ch );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// String replacement
	//----------------------------------------------

	static void BM_Manual_replace( ::benchmark::State& state )
	{
		const std::string_view oldStr = "o";
		const std::string_view newStr = "0";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				std::string result( str );
				auto pos = result.find( oldStr );
				if ( pos != std::string::npos )
				{
					result.replace( pos, oldStr.length(), newStr );
				}
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_replace( ::benchmark::State& state )
	{
		const std::string_view oldStr = "o";
		const std::string_view newStr = "0";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::replace( str, oldStr, newStr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Manual_replaceAll( ::benchmark::State& state )
	{
		const std::string_view oldStr = "o";
		const std::string_view newStr = "0";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				std::string result( str );
				std::size_t pos = 0;
				while ( ( pos = result.find( oldStr, pos ) ) != std::string::npos )
				{
					result.replace( pos, oldStr.length(), newStr );
					pos += newStr.length();
				}
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_replaceAll( ::benchmark::State& state )
	{
		const std::string_view oldStr = "o";
		const std::string_view newStr = "0";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::replaceAll( str, oldStr, newStr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// String joining
	//----------------------------------------------

	static void BM_Manual_join( ::benchmark::State& state )
	{
		const std::vector<std::string_view> parts = { "one", "two", "three", "four", "five" };
		const std::string_view delimiter = ", ";
		for ( auto _ : state )
		{
			std::string result;
			for ( std::size_t i = 0; i < parts.size(); ++i )
			{
				if ( i > 0 )
					result += delimiter;
				result += parts[i];
			}
			::benchmark::DoNotOptimize( result );
		}
	}

	static void BM_NFX_join( ::benchmark::State& state )
	{
		const std::vector<std::string_view> parts = { "one", "two", "three", "four", "five" };
		const std::string_view delimiter = ", ";
		for ( auto _ : state )
		{
			auto result = nfx::string::join( parts, delimiter );
			::benchmark::DoNotOptimize( result );
		}
	}

	//----------------------------------------------
	// Search operations
	//----------------------------------------------

	static void BM_Std_find( ::benchmark::State& state )
	{
		const std::string_view substr = "fox";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = str.find( substr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_indexOf( ::benchmark::State& state )
	{
		const std::string_view substr = "fox";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::indexOf( str, substr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Std_rfind( ::benchmark::State& state )
	{
		const std::string_view substr = "o";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = str.rfind( substr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_lastIndexOf( ::benchmark::State& state )
	{
		const std::string_view substr = "o";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::lastIndexOf( str, substr );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Substring extraction
	//----------------------------------------------

	static void BM_Manual_substringBefore( ::benchmark::State& state )
	{
		const std::string_view delimiter = ".";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto pos = str.find( delimiter );
				auto result = ( pos != std::string_view::npos ) ? str.substr( 0, pos ) : str;
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_substringBefore( ::benchmark::State& state )
	{
		const std::string_view delimiter = ".";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::substringBefore( str, delimiter );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Manual_substringAfter( ::benchmark::State& state )
	{
		const std::string_view delimiter = ".";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto pos = str.find( delimiter );
				auto result = ( pos != std::string_view::npos ) ? str.substr( pos + delimiter.length() ) : std::string_view{};
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_substringAfter( ::benchmark::State& state )
	{
		const std::string_view delimiter = ".";
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::substringAfter( str, delimiter );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// String trimming
	//----------------------------------------------

	static void BM_Manual_trim( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto start = str.find_first_not_of( " \t\n\r\f\v" );
				if ( start == std::string_view::npos )
				{
					auto result = std::string_view{};
					::benchmark::DoNotOptimize( result );
					continue;
				}
				auto end = str.find_last_not_of( " \t\n\r\f\v" );
				auto result = str.substr( start, end - start + 1 );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_trim( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::trim( str );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Case conversion
	//----------------------------------------------

	//----------------------------
	// To lower
	//----------------------------

	static void BM_Std_tolower( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				char result = static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Std_transform_tolower( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				std::string result{ str };
				std::transform( result.begin(), result.end(), result.begin(),
					[]( unsigned char c ) { return static_cast<char>( std::tolower( c ) ); } );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_toLower_char( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				char result = nfx::string::toLower( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_toLower_string( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::toLower( str );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// To upper
	//----------------------------

	static void BM_Std_toupper( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				char result = static_cast<char>( std::toupper( static_cast<unsigned char>( c ) ) );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_Std_transform_toupper( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				std::string result{ str };
				std::transform( result.begin(), result.end(), result.begin(),
					[]( unsigned char c ) { return static_cast<char>( std::toupper( c ) ); } );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_toUpper_char( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				char result = nfx::string::toUpper( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_toUpper_string( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( const auto& str : test_strings )
			{
				auto result = nfx::string::toUpper( str );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Parsing
	//----------------------------------------------

	//----------------------------
	// Int
	//----------------------------

	static void BM_Std_from_chars_int( ::benchmark::State& state )
	{
		const std::vector<std::string_view> int_strings = { "123", "-456", "0", "999999", "not_a_number" };
		for ( auto _ : state )
		{
			for ( const auto& str : int_strings )
			{
				int result;
				auto [ptr, ec] = std::from_chars( str.data(), str.data() + str.size(), result );
				bool success = ( ec == std::errc{} );
				::benchmark::DoNotOptimize( success );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_ParseInt( ::benchmark::State& state )
	{
		const std::vector<std::string_view> int_strings = { "123", "-456", "0", "999999", "not_a_number" };
		for ( auto _ : state )
		{
			for ( const auto& str : int_strings )
			{
				int result;
				bool success = nfx::string::fromString<int>( str, result );
				::benchmark::DoNotOptimize( success );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Double
	//----------------------------

	static void BM_Std_from_chars_double( ::benchmark::State& state )
	{
		const std::vector<std::string_view> double_strings = { "3.14", "-2.718", "0.0", "1e6", "not_a_number" };
		for ( auto _ : state )
		{
			for ( const auto& str : double_strings )
			{
				double result;
				auto [ptr, ec] = std::from_chars( str.data(), str.data() + str.size(), result );
				bool success = ( ec == std::errc{} );
				::benchmark::DoNotOptimize( success );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_ParseDouble( ::benchmark::State& state )
	{
		const std::vector<std::string_view> double_strings = { "3.14", "-2.718", "0.0", "1e6", "not_a_number" };
		for ( auto _ : state )
		{
			for ( const auto& str : double_strings )
			{
				double result;
				bool success = nfx::string::fromString<double>( str, result );
				::benchmark::DoNotOptimize( success );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// URI character classification
	//----------------------------------------------

	//----------------------------
	// Reserved
	//----------------------------

	static void BM_Manual_isUriReserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = ( c == ':' || c == '/' || c == '?' || c == '#' || c == '[' ||
								c == ']' || c == '@' || c == '!' || c == '$' || c == '&' ||
								c == '\'' || c == '(' || c == ')' || c == '*' || c == '+' ||
								c == ',' || c == ';' || c == '=' );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isUriReserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = nfx::string::isUriReserved( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Unreserved
	//----------------------------

	static void BM_Manual_isUriUnreserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) ||
								( c >= '0' && c <= '9' ) || c == '-' || c == '.' ||
								c == '_' || c == '~' );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_isUriUnreserved( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			for ( char c : test_chars )
			{
				bool result = nfx::string::isUriUnreserved( c );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------------------------
	// Advanced comparison operations
	//----------------------------------------------

	//----------------------------
	// Case-insensitive comparison
	//----------------------------

	static void BM_Manual_compareIgnoreCase( ::benchmark::State& state )
	{
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "apple", "APPLE" },
			{ "apple", "BANANA" },
			{ "zebra", "APPLE" },
			{ "Hello", "hello" },
			{ "test", "TEST" },
			{ "ABC", "abc" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
			{
				// Manual case-insensitive comparison using std::lexicographical_compare
				auto result = std::lexicographical_compare(
					lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
					[]( char a, char b ) {
						return std::tolower( static_cast<unsigned char>( a ) ) <
							   std::tolower( static_cast<unsigned char>( b ) );
					} );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_compareIgnoreCase( ::benchmark::State& state )
	{
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "apple", "APPLE" },
			{ "apple", "BANANA" },
			{ "zebra", "APPLE" },
			{ "Hello", "hello" },
			{ "test", "TEST" },
			{ "ABC", "abc" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
			{
				auto result = nfx::string::compareIgnoreCase( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Natural sorting comparison
	//----------------------------

	static void BM_Std_compare( ::benchmark::State& state )
	{
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "file2.txt", "file10.txt" },
			{ "v1.9", "v1.10" },
			{ "chapter2", "chapter10" },
			{ "test1", "test2" },
			{ "abc123", "abc456" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
			{
				auto result = lhs.compare( rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	static void BM_NFX_naturalCompare( ::benchmark::State& state )
	{
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "file2.txt", "file10.txt" },
			{ "v1.9", "v1.10" },
			{ "chapter2", "chapter10" },
			{ "test1", "test2" },
			{ "abc123", "abc456" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
			{
				auto result = nfx::string::naturalCompare( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Common prefix
	//----------------------------

	static void BM_Manual_commonPrefix( ::benchmark::State& state )
	{
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "/usr/local/bin", "/usr/local/lib" },
			{ "testing", "tester" },
			{ "file_1.txt", "file_2.txt" },
			{ "Hello", "World" },
			{ "abcdefgh", "abcxyz" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
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
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "/usr/local/bin", "/usr/local/lib" },
			{ "testing", "tester" },
			{ "file_1.txt", "file_2.txt" },
			{ "Hello", "World" },
			{ "abcdefgh", "abcxyz" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
			{
				auto result = nfx::string::commonPrefix( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}

	//----------------------------
	// Common suffix
	//----------------------------

	static void BM_Manual_commonSuffix( ::benchmark::State& state )
	{
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "file1.txt", "file2.txt" },
			{ "testing", "running" },
			{ "unit_test.cpp", "integration_test.cpp" },
			{ "Hello", "World" },
			{ "abcxyz", "defxyz" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
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
		const std::vector<std::pair<std::string_view, std::string_view>> test_pairs = {
			{ "file1.txt", "file2.txt" },
			{ "testing", "running" },
			{ "unit_test.cpp", "integration_test.cpp" },
			{ "Hello", "World" },
			{ "abcxyz", "defxyz" } };

		for ( auto _ : state )
		{
			for ( const auto& [lhs, rhs] : test_pairs )
			{
				auto result = nfx::string::commonSuffix( lhs, rhs );
				::benchmark::DoNotOptimize( result );
			}
		}
	}
} // namespace nfx::string::benchmark

//=====================================================================
// Benchmarks registration
//=====================================================================

//----------------------------------------------
// Character Classification
//----------------------------------------------

//----------------------------
// Spaces
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_isspace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isWhitespace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Digit
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_isdigit )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isDigit )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Alpha
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_isalpha )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isAlpha )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// String Validation
//----------------------------------------------

//----------------------------
// Empty
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_empty )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isEmpty )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Null or whitespace
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_isNullOrWhiteSpace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isNullOrWhiteSpace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// All digits
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_isAllDigits )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isAllDigits )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// String Operations
//----------------------------------------------

//----------------------------
// Starts with
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_starts_with )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_startsWith )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Ends with
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_ends_with )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_endsWith )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Contains
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_contains )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_contains )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Counting Operations
//----------------------------------------------

//----------------------------
// Count substring
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_count_substr )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_count_substr )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Count character
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_count_char )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_count_char )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// String Replacement
//----------------------------------------------

//----------------------------
// Replace first
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_replace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_replace )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Replace all
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_replaceAll )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_replaceAll )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// String Joining
//----------------------------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_join )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_join )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Search Operations
//----------------------------------------------

//----------------------------
// Index of (first)
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_find )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_indexOf )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Last index of
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_rfind )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_lastIndexOf )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Substring Extraction
//----------------------------------------------

//----------------------------
// Substring before
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_substringBefore )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_substringBefore )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Substring after
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_substringAfter )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_substringAfter )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// String Trimming
//----------------------------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_trim )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_trim )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Case Conversion
//----------------------------------------------

//----------------------------
// To lower
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_tolower )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_transform_tolower )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_toLower_char )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_toLower_string )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// To upper
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_toupper )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_Std_transform_toupper )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_toUpper_char )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_toUpper_string )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Parsing
//----------------------------------------------

//----------------------------
// Int
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_from_chars_int )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_ParseInt )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Double
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_from_chars_double )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_ParseDouble )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// URI Character Classification
//----------------------------------------------

//----------------------------
// Reserved
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_isUriReserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isUriReserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Unreserved
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_isUriUnreserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_isUriUnreserved )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------------------------
// Advanced Comparison Operations
//----------------------------------------------

//----------------------------
// Case-insensitive comparison
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_compareIgnoreCase )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_compareIgnoreCase )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Natural sorting comparison
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Std_compare )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_naturalCompare )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Common prefix
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_commonPrefix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_commonPrefix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

//----------------------------
// Common suffix
//----------------------------

BENCHMARK( nfx::string::benchmark::BM_Manual_commonSuffix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK( nfx::string::benchmark::BM_NFX_commonSuffix )
	->MinTime( 1.0 )
	->Unit( benchmark::kNanosecond );

BENCHMARK_MAIN();
