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
 * @file TESTS_StringNumericParsing.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
	//=====================================================================
	// String numeric parsing tests
	//=====================================================================

	TEST( StringNumericParsing, FromString_Bool_TrueValues )
	{
		bool result{ false };

		// Single character true values
		EXPECT_TRUE( fromString<bool>( "1", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "t", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "T", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "y", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "Y", result ) );
		EXPECT_TRUE( result );

		// Two character true values
		EXPECT_TRUE( fromString<bool>( "on", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "ON", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "On", result ) );
		EXPECT_TRUE( result );

		// Three character true values
		EXPECT_TRUE( fromString<bool>( "yes", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "YES", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "Yes", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "YeS", result ) );
		EXPECT_TRUE( result );

		// Four character true values
		EXPECT_TRUE( fromString<bool>( "true", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "TRUE", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "True", result ) );
		EXPECT_TRUE( result );

		EXPECT_TRUE( fromString<bool>( "TrUe", result ) );
		EXPECT_TRUE( result );
	}

	TEST( StringNumericParsing, FromString_Bool_FalseValues )
	{
		bool result{ true };

		// Single character false values
		EXPECT_TRUE( fromString<bool>( "0", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "f", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "F", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "n", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "N", result ) );
		EXPECT_FALSE( result );

		// Two character false values
		EXPECT_TRUE( fromString<bool>( "no", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "NO", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "No", result ) );
		EXPECT_FALSE( result );

		// Three character false values
		EXPECT_TRUE( fromString<bool>( "off", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "OFF", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "Off", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "OfF", result ) );
		EXPECT_FALSE( result );

		// Five character false values
		EXPECT_TRUE( fromString<bool>( "false", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "FALSE", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "False", result ) );
		EXPECT_FALSE( result );

		EXPECT_TRUE( fromString<bool>( "FaLsE", result ) );
		EXPECT_FALSE( result );
	}

	TEST( StringNumericParsing, FromString_Bool_InvalidValues )
	{
		bool result{ false };

		// Empty string
		EXPECT_FALSE( fromString<bool>( "", result ) );

		// Invalid single characters
		EXPECT_FALSE( fromString<bool>( "a", result ) );
		EXPECT_FALSE( fromString<bool>( "2", result ) );
		EXPECT_FALSE( fromString<bool>( "x", result ) );

		// Invalid multi-character strings
		EXPECT_FALSE( fromString<bool>( "maybe", result ) );
		EXPECT_FALSE( fromString<bool>( "truee", result ) );
		EXPECT_FALSE( fromString<bool>( "falsee", result ) );
		EXPECT_FALSE( fromString<bool>( "tr", result ) );
		EXPECT_FALSE( fromString<bool>( "fal", result ) );

		// Numbers other than 0/1
		EXPECT_FALSE( fromString<bool>( "2", result ) );
		EXPECT_FALSE( fromString<bool>( "-1", result ) );
		EXPECT_FALSE( fromString<bool>( "10", result ) );

		// Whitespace variations
		EXPECT_FALSE( fromString<bool>( " true", result ) );
		EXPECT_FALSE( fromString<bool>( "true ", result ) );
		EXPECT_FALSE( fromString<bool>( " true ", result ) );
	}

	TEST( StringNumericParsing, FromString_Int )
	{
		int result{ 0 };

		// Valid positive numbers
		EXPECT_TRUE( fromString<int>( "123", result ) );
		EXPECT_EQ( 123, result );

		EXPECT_TRUE( fromString<int>( "0", result ) );
		EXPECT_EQ( 0, result );

		EXPECT_TRUE( fromString<int>( "1", result ) );
		EXPECT_EQ( 1, result );

		// Valid negative numbers
		EXPECT_TRUE( fromString<int>( "-123", result ) );
		EXPECT_EQ( -123, result );

		EXPECT_TRUE( fromString<int>( "-1", result ) );
		EXPECT_EQ( -1, result );

		// Boundary values
		EXPECT_TRUE( fromString<int>( "2147483647", result ) );
		EXPECT_EQ( std::numeric_limits<int>::max(), result );

		EXPECT_TRUE( fromString<int>( "-2147483648", result ) );
		EXPECT_EQ( std::numeric_limits<int>::min(), result );

		// Invalid cases
		EXPECT_FALSE( fromString<int>( "", result ) );
		EXPECT_FALSE( fromString<int>( "abc", result ) );
		EXPECT_FALSE( fromString<int>( "123abc", result ) );
		EXPECT_FALSE( fromString<int>( "abc123", result ) );
		EXPECT_FALSE( fromString<int>( "12.34", result ) );
		EXPECT_FALSE( fromString<int>( " 123", result ) );
		EXPECT_FALSE( fromString<int>( "123 ", result ) );
		EXPECT_FALSE( fromString<int>( "+123", result ) );

		// Overflow cases
		EXPECT_FALSE( fromString<int>( "2147483648", result ) );  // max + 1
		EXPECT_FALSE( fromString<int>( "-2147483649", result ) ); // min - 1
		EXPECT_FALSE( fromString<int>( "999999999999999999999", result ) );
	}

	TEST( StringNumericParsing, FromString_UInt )
	{
		std::uint32_t result{ 0 };

		// Valid positive numbers
		EXPECT_TRUE( fromString<uint32_t>( "123", result ) );
		EXPECT_EQ( 123u, result );

		EXPECT_TRUE( fromString<uint32_t>( "0", result ) );
		EXPECT_EQ( 0u, result );

		EXPECT_TRUE( fromString<uint32_t>( "1", result ) );
		EXPECT_EQ( 1u, result );

		// Boundary values
		EXPECT_TRUE( fromString<uint32_t>( "4294967295", result ) );
		EXPECT_EQ( std::numeric_limits<std::uint32_t>::max(), result );

		// Invalid cases
		EXPECT_FALSE( fromString<uint32_t>( "", result ) );
		EXPECT_FALSE( fromString<uint32_t>( "-1", result ) );	// Negative not allowed
		EXPECT_FALSE( fromString<uint32_t>( "-123", result ) ); // Negative not allowed
		EXPECT_FALSE( fromString<uint32_t>( "abc", result ) );
		EXPECT_FALSE( fromString<uint32_t>( "123abc", result ) );
		EXPECT_FALSE( fromString<uint32_t>( "abc123", result ) );
		EXPECT_FALSE( fromString<uint32_t>( "12.34", result ) );
		EXPECT_FALSE( fromString<uint32_t>( " 123", result ) );
		EXPECT_FALSE( fromString<uint32_t>( "123 ", result ) );
		EXPECT_FALSE( fromString<uint32_t>( "+123", result ) );

		// Overflow cases
		EXPECT_FALSE( fromString<uint32_t>( "4294967296", result ) ); // max + 1
		EXPECT_FALSE( fromString<uint32_t>( "999999999999999999999", result ) );
	}

	TEST( StringNumericParsing, FromString_Long )
	{
		std::int64_t result{ 0 };

		// Valid positive numbers
		EXPECT_TRUE( fromString<int64_t>( "123", result ) );
		EXPECT_EQ( 123LL, result );

		EXPECT_TRUE( fromString<int64_t>( "0", result ) );
		EXPECT_EQ( 0LL, result );

		// Valid negative numbers
		EXPECT_TRUE( fromString<int64_t>( "-123", result ) );
		EXPECT_EQ( -123LL, result );

		// Large numbers
		EXPECT_TRUE( fromString<int64_t>( "9223372036854775807", result ) );
		EXPECT_EQ( std::numeric_limits<std::int64_t>::max(), result );

		EXPECT_TRUE( fromString<int64_t>( "-9223372036854775808", result ) );
		EXPECT_EQ( std::numeric_limits<std::int64_t>::min(), result );

		// Invalid cases
		EXPECT_FALSE( fromString<int64_t>( "", result ) );
		EXPECT_FALSE( fromString<int64_t>( "abc", result ) );
		EXPECT_FALSE( fromString<int64_t>( "123abc", result ) );
		EXPECT_FALSE( fromString<int64_t>( "12.34", result ) );
		EXPECT_FALSE( fromString<int64_t>( " 123", result ) );
		EXPECT_FALSE( fromString<int64_t>( "+123", result ) );
	}

	TEST( StringNumericParsing, FromString_Float )
	{
		float result{ 0.0f };

		// Valid integers
		EXPECT_TRUE( fromString<float>( "123", result ) );
		EXPECT_FLOAT_EQ( 123.0f, result );

		EXPECT_TRUE( fromString<float>( "0", result ) );
		EXPECT_FLOAT_EQ( 0.0f, result );

		EXPECT_TRUE( fromString<float>( "-123", result ) );
		EXPECT_FLOAT_EQ( -123.0f, result );

		// Valid decimals
		EXPECT_TRUE( fromString<float>( "123.456", result ) );
		EXPECT_FLOAT_EQ( 123.456f, result );

		EXPECT_TRUE( fromString<float>( "-123.456", result ) );
		EXPECT_FLOAT_EQ( -123.456f, result );

		EXPECT_TRUE( fromString<float>( "0.123", result ) );
		EXPECT_FLOAT_EQ( 0.123f, result );

		EXPECT_TRUE( fromString<float>( "3.14159", result ) );
		EXPECT_FLOAT_EQ( 3.14159f, result );

		// Scientific notation
		EXPECT_TRUE( fromString<float>( "1.23e2", result ) );
		EXPECT_FLOAT_EQ( 123.0f, result );

		EXPECT_TRUE( fromString<float>( "1.23e-2", result ) );
		EXPECT_FLOAT_EQ( 0.0123f, result );

		EXPECT_TRUE( fromString<float>( "1e10", result ) );
		EXPECT_FLOAT_EQ( 1e10f, result );

		// Edge cases - very small and large values
		EXPECT_TRUE( fromString<float>( "1.175494e-38", result ) ); // Near FLT_MIN
		EXPECT_FLOAT_EQ( 1.175494e-38f, result );

		EXPECT_TRUE( fromString<float>( "3.402823e+38", result ) ); // Near FLT_MAX
		EXPECT_FLOAT_EQ( 3.402823e+38f, result );

		// Special floating-point values (supported by std::from_chars)
		EXPECT_TRUE( fromString<float>( "nan", result ) );
		EXPECT_TRUE( std::isnan( result ) );

		EXPECT_TRUE( fromString<float>( "NaN", result ) );
		EXPECT_TRUE( std::isnan( result ) );

		EXPECT_TRUE( fromString<float>( "inf", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_GT( result, 0.0f ); // Positive infinity

		EXPECT_TRUE( fromString<float>( "-inf", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_LT( result, 0.0f ); // Negative infinity

		EXPECT_TRUE( fromString<float>( "infinity", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_GT( result, 0.0f );

		EXPECT_TRUE( fromString<float>( "-infinity", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_LT( result, 0.0f );

		// Invalid cases
		EXPECT_FALSE( fromString<float>( "", result ) );
		EXPECT_FALSE( fromString<float>( "abc", result ) );
		EXPECT_FALSE( fromString<float>( "123abc", result ) );
		EXPECT_FALSE( fromString<float>( " 123.456", result ) );
		EXPECT_FALSE( fromString<float>( "123.456 ", result ) );
		EXPECT_FALSE( fromString<float>( "+123.456", result ) );

		// Multiple decimal points
		EXPECT_FALSE( fromString<float>( "12.34.56", result ) );

		// Invalid scientific notation
		EXPECT_FALSE( fromString<float>( "1e", result ) );
		EXPECT_FALSE( fromString<float>( "e10", result ) );
	}

	TEST( StringNumericParsing, FromString_Double )
	{
		double result{ 0.0 };

		// Valid integers
		EXPECT_TRUE( fromString<double>( "123", result ) );
		EXPECT_DOUBLE_EQ( 123.0, result );

		EXPECT_TRUE( fromString<double>( "0", result ) );
		EXPECT_DOUBLE_EQ( 0.0, result );

		EXPECT_TRUE( fromString<double>( "-123", result ) );
		EXPECT_DOUBLE_EQ( -123.0, result );

		// Valid decimals
		EXPECT_TRUE( fromString<double>( "123.456", result ) );
		EXPECT_DOUBLE_EQ( 123.456, result );

		EXPECT_TRUE( fromString<double>( "-123.456", result ) );
		EXPECT_DOUBLE_EQ( -123.456, result );

		EXPECT_TRUE( fromString<double>( "0.123", result ) );
		EXPECT_DOUBLE_EQ( 0.123, result );

		// Scientific notation
		EXPECT_TRUE( fromString<double>( "1.23e2", result ) );
		EXPECT_DOUBLE_EQ( 123.0, result );

		EXPECT_TRUE( fromString<double>( "1.23e-2", result ) );
		EXPECT_DOUBLE_EQ( 0.0123, result );

		// Special floating-point values (supported by std::from_chars)
		EXPECT_TRUE( fromString<double>( "nan", result ) );
		EXPECT_TRUE( std::isnan( result ) );

		EXPECT_TRUE( fromString<double>( "NaN", result ) );
		EXPECT_TRUE( std::isnan( result ) );

		EXPECT_TRUE( fromString<double>( "inf", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_GT( result, 0.0 ); // Positive infinity

		EXPECT_TRUE( fromString<double>( "-inf", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_LT( result, 0.0 ); // Negative infinity

		EXPECT_TRUE( fromString<double>( "infinity", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_GT( result, 0.0 );

		EXPECT_TRUE( fromString<double>( "-infinity", result ) );
		EXPECT_TRUE( std::isinf( result ) );
		EXPECT_LT( result, 0.0 );

		// Invalid cases
		EXPECT_FALSE( fromString<double>( "", result ) );
		EXPECT_FALSE( fromString<double>( "abc", result ) );
		EXPECT_FALSE( fromString<double>( "123abc", result ) );
		EXPECT_FALSE( fromString<double>( " 123.456", result ) );
		EXPECT_FALSE( fromString<double>( "123.456 ", result ) );
		EXPECT_FALSE( fromString<double>( "+123.456", result ) );
	}
} // namespace nfx::string::test
