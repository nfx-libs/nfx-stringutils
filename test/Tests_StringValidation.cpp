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
 * @file Tests_StringValidation.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // String validation tests
    //=====================================================================

    TEST( StringValidation, HasExactLength )
    {
        // Basic functionality
        EXPECT_TRUE( hasExactLength( "hello", 5 ) );
        EXPECT_FALSE( hasExactLength( "hello", 4 ) );
        EXPECT_FALSE( hasExactLength( "hello", 6 ) );

        // Edge cases
        EXPECT_TRUE( hasExactLength( "", 0 ) );
        EXPECT_FALSE( hasExactLength( "", 1 ) );
        EXPECT_TRUE( hasExactLength( "a", 1 ) );

        // Long strings
        const std::string longStr( 1000, 'x' );
        EXPECT_TRUE( hasExactLength( longStr, 1000 ) );
        EXPECT_FALSE( hasExactLength( longStr, 999 ) );
        EXPECT_FALSE( hasExactLength( longStr, 1001 ) );
    }

    TEST( StringValidation, IsEmpty )
    {
        // Basic functionality
        EXPECT_TRUE( isEmpty( "" ) );
        EXPECT_FALSE( isEmpty( "a" ) );
        EXPECT_FALSE( isEmpty( "hello" ) );

        // String view from various sources
        std::string str = "test";
        EXPECT_FALSE( isEmpty( str ) );
        EXPECT_TRUE( isEmpty( std::string_view{} ) );

        // Whitespace is not empty
        EXPECT_FALSE( isEmpty( " " ) );
        EXPECT_FALSE( isEmpty( "\t" ) );
        EXPECT_FALSE( isEmpty( "\n" ) );
    }

    TEST( StringValidation, IsNullOrWhiteSpace )
    {
        EXPECT_TRUE( isNullOrWhiteSpace( "" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( std::string_view{} ) );

        // Single whitespace characters
        EXPECT_TRUE( isNullOrWhiteSpace( " " ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\t" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\n" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\r" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\f" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\v" ) );

        // Multiple whitespace characters
        EXPECT_TRUE( isNullOrWhiteSpace( "   " ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\t\t\t" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( "\n\r\n" ) );
        EXPECT_TRUE( isNullOrWhiteSpace( " \t\n\r\f\v " ) );

        // Non-whitespace strings
        EXPECT_FALSE( isNullOrWhiteSpace( "a" ) );
        EXPECT_FALSE( isNullOrWhiteSpace( "hello" ) );
        EXPECT_FALSE( isNullOrWhiteSpace( "hello world" ) );

        // Strings with mixed content (containing non-whitespace)
        EXPECT_FALSE( isNullOrWhiteSpace( " a " ) );
        EXPECT_FALSE( isNullOrWhiteSpace( "\ta\t" ) );
        EXPECT_FALSE( isNullOrWhiteSpace( "\n hello \n" ) );
        EXPECT_FALSE( isNullOrWhiteSpace( "   .   " ) );

        // String view from various sources
        std::string whitespaceStr = "   \t\n   ";
        std::string normalStr = "test";
        EXPECT_TRUE( isNullOrWhiteSpace( whitespaceStr ) );
        EXPECT_FALSE( isNullOrWhiteSpace( normalStr ) );
    }

    TEST( StringValidation, IsAllDigits )
    {
        // Valid digit strings
        EXPECT_TRUE( isAllDigits( "0" ) );
        EXPECT_TRUE( isAllDigits( "1" ) );
        EXPECT_TRUE( isAllDigits( "9" ) );
        EXPECT_TRUE( isAllDigits( "123" ) );
        EXPECT_TRUE( isAllDigits( "0123456789" ) );
        EXPECT_TRUE( isAllDigits( "999999999" ) );

        // Large digit string
        const std::string largeDigits( 1000, '5' );
        EXPECT_TRUE( isAllDigits( largeDigits ) );

        // Mixed digit string
        EXPECT_TRUE( isAllDigits( "1234567890" ) );

        // Invalid cases - empty string
        EXPECT_FALSE( isAllDigits( "" ) );
        EXPECT_FALSE( isAllDigits( std::string_view{} ) );

        // Invalid cases - contains non-digits
        EXPECT_FALSE( isAllDigits( "123a" ) );
        EXPECT_FALSE( isAllDigits( "a123" ) );
        EXPECT_FALSE( isAllDigits( "12a34" ) );
        EXPECT_FALSE( isAllDigits( "123 " ) );
        EXPECT_FALSE( isAllDigits( " 123" ) );
        EXPECT_FALSE( isAllDigits( "123.456" ) );
        EXPECT_FALSE( isAllDigits( "123-456" ) );
        EXPECT_FALSE( isAllDigits( "+123" ) );
        EXPECT_FALSE( isAllDigits( "-123" ) );

        // Invalid cases - only non-digits
        EXPECT_FALSE( isAllDigits( "abc" ) );
        EXPECT_FALSE( isAllDigits( "hello" ) );
        EXPECT_FALSE( isAllDigits( "!@#$" ) );
        EXPECT_FALSE( isAllDigits( "   " ) );
        EXPECT_FALSE( isAllDigits( "\t\n\r" ) );

        // Invalid cases - single non-digit characters
        EXPECT_FALSE( isAllDigits( "a" ) );
        EXPECT_FALSE( isAllDigits( "Z" ) );
        EXPECT_FALSE( isAllDigits( " " ) );
        EXPECT_FALSE( isAllDigits( "!" ) );
        EXPECT_FALSE( isAllDigits( "." ) );
        EXPECT_FALSE( isAllDigits( "-" ) );
        EXPECT_FALSE( isAllDigits( "+" ) );

        // Edge cases - ASCII characters around digits
        EXPECT_FALSE( isAllDigits( "/" ) ); // ASCII 47 (before '0')
        EXPECT_FALSE( isAllDigits( ":" ) ); // ASCII 58 (after '9')

        // Unicode digits should return false (ASCII-only)
        EXPECT_FALSE( isAllDigits( "１２３" ) ); // Full-width digits
        EXPECT_FALSE( isAllDigits( "۱۲۳" ) );    // Arabic-Indic digits

        // String view from various sources
        std::string digitStr = "98765";
        std::string mixedStr = "123abc";
        EXPECT_TRUE( isAllDigits( digitStr ) );
        EXPECT_FALSE( isAllDigits( mixedStr ) );

        // Performance test with very long digit string
        const std::string veryLargeDigits( 10000, '7' );
        EXPECT_TRUE( isAllDigits( veryLargeDigits ) );

        // Performance test with very long mixed string
        std::string veryLargeMixed( 9999, '8' );
        veryLargeMixed += "a"; // Add one non-digit at the end
        EXPECT_FALSE( isAllDigits( veryLargeMixed ) );
    }
} // namespace nfx::string::test
