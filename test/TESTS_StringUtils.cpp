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
 * @file TESTS_StringUtils.cpp
 * @brief Comprehensive tests for StringUtils high-performance string library
 * @details Tests covering validation, parsing, string operations, character classification,
 *          trimming, case conversion, edge cases, and performance validation for both
 *          zero-allocation (string_view) and allocating (std::string) functions
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
	//=====================================================================
	// String utils tests
	//=====================================================================

	//----------------------------------------------
	// String validation
	//----------------------------------------------

	TEST( StringUtilsValidation, HasExactLength )
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

	TEST( StringUtilsValidation, IsEmpty )
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

	TEST( StringUtilsValidation, IsNullOrWhiteSpace )
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

	TEST( StringUtilsValidation, IsAllDigits )
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
		EXPECT_FALSE( isAllDigits( "۱۲۳" ) );	 // Arabic-Indic digits

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

	//----------------------------------------------
	// Character classification
	//----------------------------------------------

	TEST( StringUtilsCharacterClassification, IsWhitespace )
	{
		// Whitespace characters
		EXPECT_TRUE( isWhitespace( ' ' ) );
		EXPECT_TRUE( isWhitespace( '\t' ) );
		EXPECT_TRUE( isWhitespace( '\n' ) );
		EXPECT_TRUE( isWhitespace( '\r' ) );
		EXPECT_TRUE( isWhitespace( '\f' ) );
		EXPECT_TRUE( isWhitespace( '\v' ) );

		// Non-whitespace characters
		EXPECT_FALSE( isWhitespace( 'a' ) );
		EXPECT_FALSE( isWhitespace( 'Z' ) );
		EXPECT_FALSE( isWhitespace( '0' ) );
		EXPECT_FALSE( isWhitespace( '9' ) );
		EXPECT_FALSE( isWhitespace( '!' ) );
		EXPECT_FALSE( isWhitespace( '@' ) );
		EXPECT_FALSE( isWhitespace( '\0' ) );
	}

	TEST( StringUtilsCharacterClassification, IsDigit )
	{
		// Digits
		EXPECT_TRUE( isDigit( '0' ) );
		EXPECT_TRUE( isDigit( '1' ) );
		EXPECT_TRUE( isDigit( '5' ) );
		EXPECT_TRUE( isDigit( '9' ) );

		// Non-digits
		EXPECT_FALSE( isDigit( 'a' ) );
		EXPECT_FALSE( isDigit( 'Z' ) );
		EXPECT_FALSE( isDigit( ' ' ) );
		EXPECT_FALSE( isDigit( '!' ) );
		EXPECT_FALSE( isDigit( '\t' ) );
		EXPECT_FALSE( isDigit( '\0' ) );
	}

	TEST( StringUtilsCharacterClassification, IsAlpha )
	{
		// Lowercase letters
		EXPECT_TRUE( isAlpha( 'a' ) );
		EXPECT_TRUE( isAlpha( 'm' ) );
		EXPECT_TRUE( isAlpha( 'z' ) );

		// Uppercase letters
		EXPECT_TRUE( isAlpha( 'A' ) );
		EXPECT_TRUE( isAlpha( 'M' ) );
		EXPECT_TRUE( isAlpha( 'Z' ) );

		// Non-alphabetic
		EXPECT_FALSE( isAlpha( '0' ) );
		EXPECT_FALSE( isAlpha( '9' ) );
		EXPECT_FALSE( isAlpha( ' ' ) );
		EXPECT_FALSE( isAlpha( '!' ) );
		EXPECT_FALSE( isAlpha( '\t' ) );
		EXPECT_FALSE( isAlpha( '\0' ) );
	}

	TEST( StringUtilsCharacterClassification, IsAlphaNumeric )
	{
		// Letters
		EXPECT_TRUE( isAlphaNumeric( 'a' ) );
		EXPECT_TRUE( isAlphaNumeric( 'Z' ) );
		EXPECT_TRUE( isAlphaNumeric( 'm' ) );

		// Digits
		EXPECT_TRUE( isAlphaNumeric( '0' ) );
		EXPECT_TRUE( isAlphaNumeric( '5' ) );
		EXPECT_TRUE( isAlphaNumeric( '9' ) );

		// Non-alphanumeric
		EXPECT_FALSE( isAlphaNumeric( ' ' ) );
		EXPECT_FALSE( isAlphaNumeric( '!' ) );
		EXPECT_FALSE( isAlphaNumeric( '@' ) );
		EXPECT_FALSE( isAlphaNumeric( '\t' ) );
		EXPECT_FALSE( isAlphaNumeric( '\0' ) );
	}

	//----------------------------------------------
	// Network and URI validation
	//----------------------------------------------

	//-----------------------------
	// URI character classification
	//-----------------------------

	TEST( StringUtilsCharacterClassification, isURIReserved_char )
	{
		// RFC 3986 Section 2.2 - Reserved Characters
		// gen-delims: : / ? # [ ] @
		EXPECT_TRUE( isURIReserved( ':' ) );
		EXPECT_TRUE( isURIReserved( '/' ) );
		EXPECT_TRUE( isURIReserved( '?' ) );
		EXPECT_TRUE( isURIReserved( '#' ) );
		EXPECT_TRUE( isURIReserved( '[' ) );
		EXPECT_TRUE( isURIReserved( ']' ) );
		EXPECT_TRUE( isURIReserved( '@' ) );

		// sub-delims: ! $ & ' ( ) * + , ; =
		EXPECT_TRUE( isURIReserved( '!' ) );
		EXPECT_TRUE( isURIReserved( '$' ) );
		EXPECT_TRUE( isURIReserved( '&' ) );
		EXPECT_TRUE( isURIReserved( '\'' ) );
		EXPECT_TRUE( isURIReserved( '(' ) );
		EXPECT_TRUE( isURIReserved( ')' ) );
		EXPECT_TRUE( isURIReserved( '*' ) );
		EXPECT_TRUE( isURIReserved( '+' ) );
		EXPECT_TRUE( isURIReserved( ',' ) );
		EXPECT_TRUE( isURIReserved( ';' ) );
		EXPECT_TRUE( isURIReserved( '=' ) );

		// Non-reserved characters
		EXPECT_FALSE( isURIReserved( 'a' ) );
		EXPECT_FALSE( isURIReserved( 'Z' ) );
		EXPECT_FALSE( isURIReserved( '0' ) );
		EXPECT_FALSE( isURIReserved( '9' ) );
		EXPECT_FALSE( isURIReserved( '-' ) );
		EXPECT_FALSE( isURIReserved( '.' ) );
		EXPECT_FALSE( isURIReserved( '_' ) );
		EXPECT_FALSE( isURIReserved( '~' ) );
		EXPECT_FALSE( isURIReserved( ' ' ) );
		EXPECT_FALSE( isURIReserved( '\t' ) );
		EXPECT_FALSE( isURIReserved( '\n' ) );
		EXPECT_FALSE( isURIReserved( '\0' ) );

		// Edge ASCII characters
		EXPECT_FALSE( isURIReserved( '"' ) );  // ASCII 34
		EXPECT_FALSE( isURIReserved( '%' ) );  // ASCII 37
		EXPECT_FALSE( isURIReserved( '<' ) );  // ASCII 60
		EXPECT_FALSE( isURIReserved( '>' ) );  // ASCII 62
		EXPECT_FALSE( isURIReserved( '\\' ) ); // ASCII 92
		EXPECT_FALSE( isURIReserved( '^' ) );  // ASCII 94
		EXPECT_FALSE( isURIReserved( '`' ) );  // ASCII 96
		EXPECT_FALSE( isURIReserved( '|' ) );  // ASCII 124
	}

	TEST( StringUtilsCharacterClassification, isURIReserved_string )
	{
		// Valid reserved character strings
		EXPECT_TRUE( isURIReserved( ":" ) );
		EXPECT_TRUE( isURIReserved( "/" ) );
		EXPECT_TRUE( isURIReserved( "?" ) );
		EXPECT_TRUE( isURIReserved( "#" ) );
		EXPECT_TRUE( isURIReserved( "[]" ) );
		EXPECT_TRUE( isURIReserved( "@" ) );
		EXPECT_TRUE( isURIReserved( "!$&'()*+,;=" ) );
		EXPECT_TRUE( isURIReserved( ":/?#[]@" ) );
		EXPECT_TRUE( isURIReserved( "!$&'()*+,;=" ) );
		EXPECT_TRUE( isURIReserved( ":/?#[]@!$&'()*+,;=" ) ); // All reserved characters

		// Mixed strings with reserved and unreserved characters
		EXPECT_FALSE( isURIReserved( ":a" ) );
		EXPECT_FALSE( isURIReserved( "a:" ) );
		EXPECT_FALSE( isURIReserved( ":a:" ) );
		EXPECT_FALSE( isURIReserved( ":a?" ) );				// Contains unreserved char 'a'
		EXPECT_FALSE( isURIReserved( "test:" ) );			// Text + reserved
		EXPECT_FALSE( isURIReserved( ":test" ) );			// Reserved + text
		EXPECT_FALSE( isURIReserved( "test:123" ) );		// Text + reserved + digits
		EXPECT_FALSE( isURIReserved( "a/b" ) );				// Unreserved + reserved + unreserved
		EXPECT_FALSE( isURIReserved( "hello@world.com" ) ); // Mixed realistic scenario
		EXPECT_FALSE( isURIReserved( "user:pass" ) );		// Common auth format
		EXPECT_FALSE( isURIReserved( "file.txt" ) );		// Filename with unreserved chars
		EXPECT_FALSE( isURIReserved( "test" ) );
		EXPECT_FALSE( isURIReserved( "123" ) );
		EXPECT_FALSE( isURIReserved( "abc123" ) );

		// Invalid cases - empty string
		EXPECT_FALSE( isURIReserved( "" ) );
		EXPECT_FALSE( isURIReserved( std::string_view{} ) );

		// Strings with only unreserved characters
		EXPECT_FALSE( isURIReserved( "abcdefghijklmnopqrstuvwxyz" ) );
		EXPECT_FALSE( isURIReserved( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );
		EXPECT_FALSE( isURIReserved( "0123456789" ) );
		EXPECT_FALSE( isURIReserved( "-._~" ) );
		EXPECT_FALSE( isURIReserved( "abc123-._~XYZ" ) );

		// Strings with whitespace and control characters
		EXPECT_FALSE( isURIReserved( " " ) );
		EXPECT_FALSE( isURIReserved( "\t\n\r" ) );
		EXPECT_FALSE( isURIReserved( ": " ) ); // Contains space

		// Large string tests
		const std::string largeReserved( 1000, ':' );
		EXPECT_TRUE( isURIReserved( largeReserved ) );

		const std::string largeMixed = std::string( 999, ':' ) + "a";
		EXPECT_FALSE( isURIReserved( largeMixed ) );
	}

	TEST( StringUtilsCharacterClassification, isURIUnreserved_char )
	{
		// RFC 3986 Section 2.3 - Unreserved Characters
		// ALPHA (uppercase)
		EXPECT_TRUE( isURIUnreserved( 'A' ) );
		EXPECT_TRUE( isURIUnreserved( 'M' ) );
		EXPECT_TRUE( isURIUnreserved( 'Z' ) );

		// ALPHA (lowercase)
		EXPECT_TRUE( isURIUnreserved( 'a' ) );
		EXPECT_TRUE( isURIUnreserved( 'm' ) );
		EXPECT_TRUE( isURIUnreserved( 'z' ) );

		// DIGIT
		EXPECT_TRUE( isURIUnreserved( '0' ) );
		EXPECT_TRUE( isURIUnreserved( '5' ) );
		EXPECT_TRUE( isURIUnreserved( '9' ) );

		// Special unreserved characters: - . _ ~
		EXPECT_TRUE( isURIUnreserved( '-' ) );
		EXPECT_TRUE( isURIUnreserved( '.' ) );
		EXPECT_TRUE( isURIUnreserved( '_' ) );
		EXPECT_TRUE( isURIUnreserved( '~' ) );

		// Reserved characters should return false
		EXPECT_FALSE( isURIUnreserved( ':' ) );
		EXPECT_FALSE( isURIUnreserved( '/' ) );
		EXPECT_FALSE( isURIUnreserved( '?' ) );
		EXPECT_FALSE( isURIUnreserved( '#' ) );
		EXPECT_FALSE( isURIUnreserved( '[' ) );
		EXPECT_FALSE( isURIUnreserved( ']' ) );
		EXPECT_FALSE( isURIUnreserved( '@' ) );
		EXPECT_FALSE( isURIUnreserved( '!' ) );
		EXPECT_FALSE( isURIUnreserved( '$' ) );
		EXPECT_FALSE( isURIUnreserved( '&' ) );
		EXPECT_FALSE( isURIUnreserved( '\'' ) );
		EXPECT_FALSE( isURIUnreserved( '(' ) );
		EXPECT_FALSE( isURIUnreserved( ')' ) );
		EXPECT_FALSE( isURIUnreserved( '*' ) );
		EXPECT_FALSE( isURIUnreserved( '+' ) );
		EXPECT_FALSE( isURIUnreserved( ',' ) );
		EXPECT_FALSE( isURIUnreserved( ';' ) );
		EXPECT_FALSE( isURIUnreserved( '=' ) );

		// Other characters should return false
		EXPECT_FALSE( isURIUnreserved( ' ' ) );
		EXPECT_FALSE( isURIUnreserved( '\t' ) );
		EXPECT_FALSE( isURIUnreserved( '\n' ) );
		EXPECT_FALSE( isURIUnreserved( '\r' ) );
		EXPECT_FALSE( isURIUnreserved( '\0' ) );
		EXPECT_FALSE( isURIUnreserved( '"' ) );
		EXPECT_FALSE( isURIUnreserved( '%' ) );
		EXPECT_FALSE( isURIUnreserved( '<' ) );
		EXPECT_FALSE( isURIUnreserved( '>' ) );
		EXPECT_FALSE( isURIUnreserved( '\\' ) );
		EXPECT_FALSE( isURIUnreserved( '^' ) );
		EXPECT_FALSE( isURIUnreserved( '`' ) );
		EXPECT_FALSE( isURIUnreserved( '|' ) );

		// Edge ASCII boundaries
		EXPECT_FALSE( isURIUnreserved( '@' ) ); // ASCII 64 (before 'A')
		EXPECT_FALSE( isURIUnreserved( '[' ) ); // ASCII 91 (after 'Z')
		EXPECT_FALSE( isURIUnreserved( '`' ) ); // ASCII 96 (before 'a')
		EXPECT_FALSE( isURIUnreserved( '{' ) ); // ASCII 123 (after 'z')
		EXPECT_FALSE( isURIUnreserved( '/' ) ); // ASCII 47 (before '0')
		EXPECT_FALSE( isURIUnreserved( ':' ) ); // ASCII 58 (after '9')
	}

	TEST( StringUtilsCharacterClassification, isURIUnreserved_string )
	{
		// Valid unreserved character strings
		EXPECT_TRUE( isURIUnreserved( "a" ) );
		EXPECT_TRUE( isURIUnreserved( "Z" ) );
		EXPECT_TRUE( isURIUnreserved( "0" ) );
		EXPECT_TRUE( isURIUnreserved( "9" ) );
		EXPECT_TRUE( isURIUnreserved( "-" ) );
		EXPECT_TRUE( isURIUnreserved( "." ) );
		EXPECT_TRUE( isURIUnreserved( "_" ) );
		EXPECT_TRUE( isURIUnreserved( "~" ) );

		// Multiple unreserved characters
		EXPECT_TRUE( isURIUnreserved( "abc" ) );
		EXPECT_TRUE( isURIUnreserved( "XYZ" ) );
		EXPECT_TRUE( isURIUnreserved( "123" ) );
		EXPECT_TRUE( isURIUnreserved( "-._~" ) );
		EXPECT_TRUE( isURIUnreserved( "abcdefghijklmnopqrstuvwxyz" ) );
		EXPECT_TRUE( isURIUnreserved( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );
		EXPECT_TRUE( isURIUnreserved( "0123456789" ) );
		EXPECT_TRUE( isURIUnreserved( "abc123XYZ-._~" ) ); // All unreserved types

		// Valid URL-like strings with only unreserved characters
		EXPECT_TRUE( isURIUnreserved( "example" ) );
		EXPECT_TRUE( isURIUnreserved( "test123" ) );
		EXPECT_TRUE( isURIUnreserved( "my-file.txt" ) );
		EXPECT_TRUE( isURIUnreserved( "user_name" ) );
		EXPECT_TRUE( isURIUnreserved( "version~1" ) );

		// Mixed strings with reserved characters
		EXPECT_FALSE( isURIUnreserved( "a:" ) );
		EXPECT_FALSE( isURIUnreserved( ":a" ) );
		EXPECT_FALSE( isURIUnreserved( "a:b" ) );
		EXPECT_FALSE( isURIUnreserved( "test/" ) );
		EXPECT_FALSE( isURIUnreserved( "file?name" ) );
		EXPECT_FALSE( isURIUnreserved( "user@domain" ) );
		EXPECT_FALSE( isURIUnreserved( "path[0]" ) );
		EXPECT_FALSE( isURIUnreserved( "hello:world" ) );  // Text + reserved + text
		EXPECT_FALSE( isURIUnreserved( "test.txt?" ) );	   // Unreserved + reserved
		EXPECT_FALSE( isURIUnreserved( "!important" ) );   // Reserved + unreserved
		EXPECT_FALSE( isURIUnreserved( "data&more" ) );	   // Mixed realistic scenario
		EXPECT_FALSE( isURIUnreserved( "key=value" ) );	   // Common query format
		EXPECT_FALSE( isURIUnreserved( "path/to/file" ) ); // Path with slashes

		// Invalid cases - empty string
		EXPECT_FALSE( isURIUnreserved( "" ) );
		EXPECT_FALSE( isURIUnreserved( std::string_view{} ) );

		// Strings with whitespace and control characters
		EXPECT_FALSE( isURIUnreserved( " " ) );
		EXPECT_FALSE( isURIUnreserved( "\t" ) );
		EXPECT_FALSE( isURIUnreserved( "\n" ) );
		EXPECT_FALSE( isURIUnreserved( "a " ) );  // Contains space
		EXPECT_FALSE( isURIUnreserved( " a" ) );  // Contains space
		EXPECT_FALSE( isURIUnreserved( "a b" ) ); // Contains space

		// Strings with other non-unreserved characters
		EXPECT_FALSE( isURIUnreserved( "\"" ) );
		EXPECT_FALSE( isURIUnreserved( "%" ) );
		EXPECT_FALSE( isURIUnreserved( "<>" ) );
		EXPECT_FALSE( isURIUnreserved( "\\" ) );
		EXPECT_FALSE( isURIUnreserved( "^" ) );
		EXPECT_FALSE( isURIUnreserved( "`" ) );
		EXPECT_FALSE( isURIUnreserved( "|" ) );

		// Large string tests
		const std::string largeUnreserved( 1000, 'a' );
		EXPECT_TRUE( isURIUnreserved( largeUnreserved ) );

		const std::string largeMixed = std::string( 999, 'a' ) + ":";
		EXPECT_FALSE( isURIUnreserved( largeMixed ) );

		// Performance test with mixed unreserved types
		const std::string mixedUnreserved = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~";
		EXPECT_TRUE( isURIUnreserved( mixedUnreserved ) );

		// String view from various sources
		std::string unreservedStr = "test123";
		std::string mixedStr = "test:123";
		EXPECT_TRUE( isURIUnreserved( unreservedStr ) );
		EXPECT_FALSE( isURIUnreserved( mixedStr ) );
	}

	//-----------------------------
	// IP address validation
	//-----------------------------

	TEST( StringUtilsNetworkValidation, IsIPv4Address )
	{
		// Valid IPv4 addresses
		EXPECT_TRUE( isIPv4Address( "0.0.0.0" ) );
		EXPECT_TRUE( isIPv4Address( "127.0.0.1" ) );
		EXPECT_TRUE( isIPv4Address( "192.168.1.1" ) );
		EXPECT_TRUE( isIPv4Address( "255.255.255.255" ) );
		EXPECT_TRUE( isIPv4Address( "10.0.0.1" ) );
		EXPECT_TRUE( isIPv4Address( "172.16.0.1" ) );
		EXPECT_TRUE( isIPv4Address( "8.8.8.8" ) );
		EXPECT_TRUE( isIPv4Address( "1.2.3.4" ) );

		// Invalid IPv4 addresses - wrong format
		EXPECT_FALSE( isIPv4Address( "" ) );
		EXPECT_FALSE( isIPv4Address( "192.168.1" ) );	  // Missing octet
		EXPECT_FALSE( isIPv4Address( "192.168.1.1.1" ) ); // Too many octets
		EXPECT_FALSE( isIPv4Address( "192.168..1" ) );	  // Empty octet
		EXPECT_FALSE( isIPv4Address( ".192.168.1.1" ) );  // Starts with dot
		EXPECT_FALSE( isIPv4Address( "192.168.1.1." ) );  // Ends with dot
		EXPECT_FALSE( isIPv4Address( "192.168.1.1.." ) ); // Double dot at end

		// Invalid IPv4 addresses - out of range
		EXPECT_FALSE( isIPv4Address( "256.1.1.1" ) );		// > 255
		EXPECT_FALSE( isIPv4Address( "1.256.1.1" ) );		// > 255
		EXPECT_FALSE( isIPv4Address( "1.1.256.1" ) );		// > 255
		EXPECT_FALSE( isIPv4Address( "1.1.1.256" ) );		// > 255
		EXPECT_FALSE( isIPv4Address( "999.999.999.999" ) ); // Way out of range
		EXPECT_FALSE( isIPv4Address( "300.300.300.300" ) );

		// Invalid IPv4 addresses - non-numeric
		EXPECT_FALSE( isIPv4Address( "abc.def.ghi.jkl" ) );
		EXPECT_FALSE( isIPv4Address( "192.168.1.a" ) );
		EXPECT_FALSE( isIPv4Address( "192.168.1.1a" ) );
		EXPECT_FALSE( isIPv4Address( "192.168.1.1 " ) ); // Trailing space
		EXPECT_FALSE( isIPv4Address( " 192.168.1.1" ) ); // Leading space
		EXPECT_FALSE( isIPv4Address( "192.168. 1.1" ) ); // Space in middle

		// Invalid IPv4 addresses - special characters
		EXPECT_FALSE( isIPv4Address( "192.168.1.1:80" ) ); // Port included
		EXPECT_FALSE( isIPv4Address( "192.168.1.1/24" ) ); // CIDR notation
		EXPECT_FALSE( isIPv4Address( "192-168-1-1" ) );	   // Hyphens instead of dots

		// Edge cases
		EXPECT_FALSE( isIPv4Address( "..." ) );
		EXPECT_FALSE( isIPv4Address( "1.2.3.4.5.6.7.8" ) ); // Too long
		EXPECT_FALSE( isIPv4Address( "01.02.03.04" ) );		// Leading zeros (technically invalid in strict parsing)
	}

	TEST( StringUtilsNetworkValidation, IsIPv6Address )
	{
		// Valid IPv6 addresses - full notation
		EXPECT_TRUE( isIPv6Address( "2001:0db8:0000:0000:0000:0000:0000:0001" ) );
		EXPECT_TRUE( isIPv6Address( "2001:db8:0:0:0:0:0:1" ) );
		EXPECT_TRUE( isIPv6Address( "2001:0db8:85a3:0000:0000:8a2e:0370:7334" ) );

		// Valid IPv6 addresses - compressed notation
		EXPECT_TRUE( isIPv6Address( "::" ) );		   // All zeros
		EXPECT_TRUE( isIPv6Address( "::1" ) );		   // Loopback
		EXPECT_TRUE( isIPv6Address( "2001:db8::1" ) ); // Compressed middle
		EXPECT_TRUE( isIPv6Address( "2001:db8:85a3::8a2e:370:7334" ) );
		EXPECT_TRUE( isIPv6Address( "::ffff:192.0.2.1" ) ); // IPv4-mapped
		EXPECT_TRUE( isIPv6Address( "fe80::1" ) );			// Link-local

		// Valid IPv6 addresses - with zone ID
		EXPECT_TRUE( isIPv6Address( "fe80::1%eth0" ) );
		EXPECT_TRUE( isIPv6Address( "fe80::1%lo0" ) );

		// Invalid IPv6 addresses - wrong format
		EXPECT_FALSE( isIPv6Address( "" ) );
		EXPECT_FALSE( isIPv6Address( ":" ) );
		EXPECT_FALSE( isIPv6Address( ":::" ) );								   // Too many colons
		EXPECT_FALSE( isIPv6Address( "2001:db8::1::2" ) );					   // Multiple :: compressions
		EXPECT_FALSE( isIPv6Address( "gggg::1" ) );							   // Invalid hex
		EXPECT_FALSE( isIPv6Address( "2001:db8:85a3::8a2e:370:7334:extra" ) ); // Too many groups

		// Invalid IPv6 addresses - too many digits per group
		EXPECT_FALSE( isIPv6Address( "20011:db8::1" ) );	// 5 hex digits
		EXPECT_FALSE( isIPv6Address( "2001:db88888::1" ) ); // Too many digits

		// Invalid IPv6 addresses - invalid characters
		EXPECT_FALSE( isIPv6Address( "2001:db8::1 " ) );   // Trailing space
		EXPECT_FALSE( isIPv6Address( " 2001:db8::1" ) );   // Leading space
		EXPECT_FALSE( isIPv6Address( "2001:db8::g" ) );	   // Invalid hex char
		EXPECT_FALSE( isIPv6Address( "2001:db8::1/64" ) ); // CIDR notation
		EXPECT_FALSE( isIPv6Address( "[2001:db8::1]" ) );  // Brackets
	}

	//-----------------------------
	// Host validation
	//-----------------------------

	TEST( StringUtilsNetworkValidation, IsValidHostname )
	{
		// Valid hostnames
		EXPECT_TRUE( isValidHostname( "localhost" ) );
		EXPECT_TRUE( isValidHostname( "example.com" ) );
		EXPECT_TRUE( isValidHostname( "www.example.com" ) );
		EXPECT_TRUE( isValidHostname( "sub.domain.example.com" ) );
		EXPECT_TRUE( isValidHostname( "my-server" ) );
		EXPECT_TRUE( isValidHostname( "server-01" ) );
		EXPECT_TRUE( isValidHostname( "192-168-1-1" ) );  // Numeric but valid hostname format
		EXPECT_TRUE( isValidHostname( "a" ) );			  // Single character
		EXPECT_TRUE( isValidHostname( "a.b" ) );		  // Minimum domain
		EXPECT_TRUE( isValidHostname( "test123" ) );	  // Alphanumeric
		EXPECT_TRUE( isValidHostname( "test-123-abc" ) ); // With hyphens

		// Valid hostnames - max lengths
		const std::string label63( 63, 'a' ); // Max label length
		EXPECT_TRUE( isValidHostname( label63 ) );
		EXPECT_TRUE( isValidHostname( label63 + ".com" ) );

		const std::string hostname253 = label63 + "." + label63 + "." + label63 + ".com"; // Close to max
		EXPECT_TRUE( isValidHostname( hostname253 ) );

		// Invalid hostnames - empty
		EXPECT_FALSE( isValidHostname( "" ) );

		// Invalid hostnames - too long
		const std::string label64( 64, 'a' ); // Exceeds max label length
		EXPECT_FALSE( isValidHostname( label64 ) );
		const std::string hostname254( 254, 'a' ); // Exceeds max total length
		EXPECT_FALSE( isValidHostname( hostname254 ) );

		// Invalid hostnames - starts with hyphen
		EXPECT_FALSE( isValidHostname( "-server" ) );
		EXPECT_FALSE( isValidHostname( "server.-test" ) );

		// Invalid hostnames - ends with hyphen
		EXPECT_FALSE( isValidHostname( "server-" ) );
		EXPECT_FALSE( isValidHostname( "server.test-" ) );

		// Invalid hostnames - consecutive dots
		EXPECT_FALSE( isValidHostname( "example..com" ) );
		EXPECT_FALSE( isValidHostname( "..example" ) );

		// Invalid hostnames - starts/ends with dot
		EXPECT_FALSE( isValidHostname( ".example.com" ) );
		EXPECT_FALSE( isValidHostname( "example.com." ) );

		// Invalid hostnames - invalid characters
		EXPECT_FALSE( isValidHostname( "example_com" ) );  // Underscore
		EXPECT_FALSE( isValidHostname( "example.com!" ) ); // Special char
		EXPECT_FALSE( isValidHostname( "example com" ) );  // Space
		EXPECT_FALSE( isValidHostname( "example@com" ) );  // @ symbol
		EXPECT_FALSE( isValidHostname( "example:8080" ) ); // Colon
		EXPECT_FALSE( isValidHostname( "example/path" ) ); // Slash
	}

	TEST( StringUtilsNetworkValidation, IsDomainName )
	{
		// Valid domain names
		EXPECT_TRUE( isDomainName( "example.com" ) );
		EXPECT_TRUE( isDomainName( "www.example.com" ) );
		EXPECT_TRUE( isDomainName( "sub.domain.example.com" ) );
		EXPECT_TRUE( isDomainName( "a.b" ) ); // Minimum
		EXPECT_TRUE( isDomainName( "test-site.co.uk" ) );
		EXPECT_TRUE( isDomainName( "my-server.local" ) );

		// Invalid domain names - no dot
		EXPECT_FALSE( isDomainName( "localhost" ) ); // Valid hostname but not domain
		EXPECT_FALSE( isDomainName( "server" ) );
		EXPECT_FALSE( isDomainName( "test123" ) );

		// Invalid domain names - empty
		EXPECT_FALSE( isDomainName( "" ) );

		// Invalid domain names - invalid hostname format
		EXPECT_FALSE( isDomainName( ".com" ) );			 // Starts with dot
		EXPECT_FALSE( isDomainName( "example.com." ) );	 // Ends with dot
		EXPECT_FALSE( isDomainName( "example..com" ) );	 // Consecutive dots
		EXPECT_FALSE( isDomainName( "-test.com" ) );	 // Starts with hyphen
		EXPECT_FALSE( isDomainName( "test-.com" ) );	 // Label ends with hyphen
		EXPECT_FALSE( isDomainName( "test_site.com" ) ); // Underscore
		EXPECT_FALSE( isDomainName( "test site.com" ) ); // Space
	}

	//-----------------------------
	// Port validation
	//-----------------------------

	TEST( StringUtilsNetworkValidation, IsValidPort_String )
	{
		// Valid port strings
		EXPECT_TRUE( isValidPort( "0" ) );
		EXPECT_TRUE( isValidPort( "1" ) );
		EXPECT_TRUE( isValidPort( "80" ) );
		EXPECT_TRUE( isValidPort( "443" ) );
		EXPECT_TRUE( isValidPort( "8080" ) );
		EXPECT_TRUE( isValidPort( "3000" ) );
		EXPECT_TRUE( isValidPort( "65535" ) ); // Max port

		// Valid port strings - well-known ports
		EXPECT_TRUE( isValidPort( "21" ) );	  // FTP
		EXPECT_TRUE( isValidPort( "22" ) );	  // SSH
		EXPECT_TRUE( isValidPort( "25" ) );	  // SMTP
		EXPECT_TRUE( isValidPort( "53" ) );	  // DNS
		EXPECT_TRUE( isValidPort( "3306" ) ); // MySQL
		EXPECT_TRUE( isValidPort( "5432" ) ); // PostgreSQL

		// Invalid port strings - empty
		EXPECT_FALSE( isValidPort( "" ) );

		// Invalid port strings - out of range
		EXPECT_FALSE( isValidPort( "65536" ) ); // Max + 1
		EXPECT_FALSE( isValidPort( "99999" ) );
		EXPECT_FALSE( isValidPort( "100000" ) );
		EXPECT_FALSE( isValidPort( "999999" ) );

		// Invalid port strings - non-numeric
		EXPECT_FALSE( isValidPort( "abc" ) );
		EXPECT_FALSE( isValidPort( "80a" ) );
		EXPECT_FALSE( isValidPort( "a80" ) );
		EXPECT_FALSE( isValidPort( "8o8o" ) ); // Letter 'o' instead of zero

		// Invalid port strings - with whitespace
		EXPECT_FALSE( isValidPort( " 80" ) );
		EXPECT_FALSE( isValidPort( "80 " ) );
		EXPECT_FALSE( isValidPort( " 80 " ) );

		// Invalid port strings - with special characters
		EXPECT_FALSE( isValidPort( "-80" ) );	// Negative sign
		EXPECT_FALSE( isValidPort( "+80" ) );	// Plus sign
		EXPECT_FALSE( isValidPort( "80.0" ) );	// Decimal
		EXPECT_FALSE( isValidPort( "80:80" ) ); // Colon
	}

	//-----------------------------
	// Endpoint parsing
	//-----------------------------

	TEST( StringUtilsNetworkValidation, TryParseEndpoint_IPv4 )
	{
		std::string_view host{};
		uint16_t port{ 0 };

		// Valid IPv4 endpoints
		EXPECT_TRUE( tryParseEndpoint( "192.168.1.1:80", host, port ) );
		EXPECT_EQ( "192.168.1.1", host );
		EXPECT_EQ( 80, port );

		EXPECT_TRUE( tryParseEndpoint( "127.0.0.1:8080", host, port ) );
		EXPECT_EQ( "127.0.0.1", host );
		EXPECT_EQ( 8080, port );

		EXPECT_TRUE( tryParseEndpoint( "10.0.0.1:443", host, port ) );
		EXPECT_EQ( "10.0.0.1", host );
		EXPECT_EQ( 443, port );

		EXPECT_TRUE( tryParseEndpoint( "8.8.8.8:53", host, port ) );
		EXPECT_EQ( "8.8.8.8", host );
		EXPECT_EQ( 53, port );

		// Invalid IPv4 endpoints - no port
		EXPECT_FALSE( tryParseEndpoint( "192.168.1.1", host, port ) );

		// Invalid IPv4 endpoints - invalid port
		EXPECT_FALSE( tryParseEndpoint( "192.168.1.1:abc", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "192.168.1.1:70000", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "192.168.1.1:", host, port ) );

		// Invalid IPv4 endpoints - invalid IP
		EXPECT_FALSE( tryParseEndpoint( "256.1.1.1:80", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "192.168.1:80", host, port ) );
	}

	TEST( StringUtilsNetworkValidation, TryParseEndpoint_IPv6 )
	{
		std::string_view host{};
		uint16_t port{ 0 };

		// Valid IPv6 endpoints - with brackets
		EXPECT_TRUE( tryParseEndpoint( "[::1]:80", host, port ) );
		EXPECT_EQ( "::1", host );
		EXPECT_EQ( 80, port );

		EXPECT_TRUE( tryParseEndpoint( "[2001:db8::1]:443", host, port ) );
		EXPECT_EQ( "2001:db8::1", host );
		EXPECT_EQ( 443, port );

		EXPECT_TRUE( tryParseEndpoint( "[fe80::1]:8080", host, port ) );
		EXPECT_EQ( "fe80::1", host );
		EXPECT_EQ( 8080, port );

		// Valid IPv6 endpoints - with zone ID
		EXPECT_TRUE( tryParseEndpoint( "[fe80::1%eth0]:80", host, port ) );
		EXPECT_EQ( "fe80::1%eth0", host );
		EXPECT_EQ( 80, port );

		// Invalid IPv6 endpoints - missing brackets
		EXPECT_FALSE( tryParseEndpoint( "::1:80", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "2001:db8::1:443", host, port ) );

		// Invalid IPv6 endpoints - no port
		EXPECT_FALSE( tryParseEndpoint( "[::1]", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "[2001:db8::1]", host, port ) );

		// Invalid IPv6 endpoints - invalid format
		EXPECT_FALSE( tryParseEndpoint( "[::1", host, port ) );		 // Missing closing bracket
		EXPECT_FALSE( tryParseEndpoint( "::1]", host, port ) );		 // Missing opening bracket
		EXPECT_FALSE( tryParseEndpoint( "[::1]:abc", host, port ) ); // Invalid port
	}

	TEST( StringUtilsNetworkValidation, TryParseEndpoint_Hostname )
	{
		std::string_view host{};
		uint16_t port{ 0 };

		// Valid hostname endpoints
		EXPECT_TRUE( tryParseEndpoint( "localhost:80", host, port ) );
		EXPECT_EQ( "localhost", host );
		EXPECT_EQ( 80, port );

		EXPECT_TRUE( tryParseEndpoint( "example.com:443", host, port ) );
		EXPECT_EQ( "example.com", host );
		EXPECT_EQ( 443, port );

		EXPECT_TRUE( tryParseEndpoint( "www.example.com:8080", host, port ) );
		EXPECT_EQ( "www.example.com", host );
		EXPECT_EQ( 8080, port );

		EXPECT_TRUE( tryParseEndpoint( "my-server:3000", host, port ) );
		EXPECT_EQ( "my-server", host );
		EXPECT_EQ( 3000, port );

		// Invalid hostname endpoints - no port
		EXPECT_FALSE( tryParseEndpoint( "localhost", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "example.com", host, port ) );

		// Invalid hostname endpoints - invalid port
		EXPECT_FALSE( tryParseEndpoint( "localhost:abc", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "example.com:70000", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "example.com:", host, port ) );

		// Invalid hostname endpoints - invalid hostname
		EXPECT_FALSE( tryParseEndpoint( "-invalid:80", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "invalid-:80", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "inva lid:80", host, port ) );
	}

	TEST( StringUtilsNetworkValidation, TryParseEndpoint_EdgeCases )
	{
		std::string_view host{};
		uint16_t port{ 0 };

		// Empty string
		EXPECT_FALSE( tryParseEndpoint( "", host, port ) );

		// No colon separator
		EXPECT_FALSE( tryParseEndpoint( "localhost", host, port ) );
		EXPECT_FALSE( tryParseEndpoint( "192.168.1.1", host, port ) );

		// Empty host
		EXPECT_FALSE( tryParseEndpoint( ":80", host, port ) );

		// Empty port
		EXPECT_FALSE( tryParseEndpoint( "localhost:", host, port ) );

		// Multiple colons (ambiguous for non-IPv6)
		EXPECT_FALSE( tryParseEndpoint( "host:80:443", host, port ) );

		// Port boundaries
		EXPECT_TRUE( tryParseEndpoint( "localhost:0", host, port ) );
		EXPECT_EQ( 0, port );

		EXPECT_TRUE( tryParseEndpoint( "localhost:65535", host, port ) );
		EXPECT_EQ( 65535, port );

		EXPECT_FALSE( tryParseEndpoint( "localhost:65536", host, port ) );
	}

	//----------------------------------------------
	// Operations
	//----------------------------------------------

	TEST( StringUtilsOperations, EndsWith )
	{
		// Basic functionality
		EXPECT_TRUE( endsWith( "hello world", "world" ) );
		EXPECT_TRUE( endsWith( "hello world", "d" ) );
		EXPECT_FALSE( endsWith( "hello world", "hello" ) );
		EXPECT_FALSE( endsWith( "hello world", "World" ) ); // Case sensitive

		// Edge cases
		EXPECT_TRUE( endsWith( "test", "" ) );	   // Empty suffix
		EXPECT_TRUE( endsWith( "test", "test" ) ); // Exact match
		EXPECT_FALSE( endsWith( "", "test" ) );	   // Empty string, non-empty suffix
		EXPECT_TRUE( endsWith( "", "" ) );		   // Both empty

		// Suffix longer than string
		EXPECT_FALSE( endsWith( "hi", "hello" ) );

		// Single characters
		EXPECT_TRUE( endsWith( "a", "a" ) );
		EXPECT_FALSE( endsWith( "a", "b" ) );
	}

	TEST( StringUtilsOperations, StartsWith )
	{
		// Basic functionality
		EXPECT_TRUE( startsWith( "hello world", "hello" ) );
		EXPECT_TRUE( startsWith( "hello world", "h" ) );
		EXPECT_FALSE( startsWith( "hello world", "world" ) );
		EXPECT_FALSE( startsWith( "hello world", "Hello" ) ); // Case sensitive

		// Edge cases
		EXPECT_TRUE( startsWith( "test", "" ) );	 // Empty prefix
		EXPECT_TRUE( startsWith( "test", "test" ) ); // Exact match
		EXPECT_FALSE( startsWith( "", "test" ) );	 // Empty string, non-empty prefix
		EXPECT_TRUE( startsWith( "", "" ) );		 // Both empty

		// Prefix longer than string
		EXPECT_FALSE( startsWith( "hi", "hello" ) );

		// Single characters
		EXPECT_TRUE( startsWith( "a", "a" ) );
		EXPECT_FALSE( startsWith( "a", "b" ) );
	}

	TEST( StringUtilsOperations, Contains )
	{
		// Basic functionality
		EXPECT_TRUE( contains( "hello world", "hello" ) );
		EXPECT_TRUE( contains( "hello world", "world" ) );
		EXPECT_TRUE( contains( "hello world", "o w" ) );
		EXPECT_TRUE( contains( "hello world", "l" ) );
		EXPECT_FALSE( contains( "hello world", "Hello" ) ); // Case sensitive
		EXPECT_FALSE( contains( "hello world", "xyz" ) );

		// Edge cases
		EXPECT_TRUE( contains( "test", "" ) );	   // Empty substring
		EXPECT_TRUE( contains( "test", "test" ) ); // Exact match
		EXPECT_FALSE( contains( "", "test" ) );	   // Empty string, non-empty substring
		EXPECT_TRUE( contains( "", "" ) );		   // Both empty

		// Substring longer than string
		EXPECT_FALSE( contains( "hi", "hello" ) );

		// Multiple occurrences
		EXPECT_TRUE( contains( "hello hello", "hello" ) );
		EXPECT_TRUE( contains( "abcabcabc", "abc" ) );
	}

	TEST( StringUtilsOperations, Equals )
	{
		// Basic functionality
		EXPECT_TRUE( equals( "hello", "hello" ) );
		EXPECT_FALSE( equals( "hello", "world" ) );
		EXPECT_FALSE( equals( "hello", "Hello" ) ); // Case sensitive

		// Edge cases
		EXPECT_TRUE( equals( "", "" ) );	  // Both empty
		EXPECT_FALSE( equals( "", "test" ) ); // One empty
		EXPECT_FALSE( equals( "test", "" ) ); // One empty

		// Different lengths
		EXPECT_FALSE( equals( "hello", "hello world" ) );
		EXPECT_FALSE( equals( "hello world", "hello" ) );

		// Single characters
		EXPECT_TRUE( equals( "a", "a" ) );
		EXPECT_FALSE( equals( "a", "b" ) );
	}

	TEST( StringUtilsOperations, IEquals )
	{
		// Basic functionality
		EXPECT_TRUE( iequals( "hello", "hello" ) );
		EXPECT_TRUE( iequals( "hello", "HELLO" ) );
		EXPECT_TRUE( iequals( "hello", "Hello" ) );
		EXPECT_TRUE( iequals( "HELLO", "hello" ) );
		EXPECT_TRUE( iequals( "HeLLo", "hEllO" ) );
		EXPECT_FALSE( iequals( "hello", "world" ) );

		// Edge cases
		EXPECT_TRUE( iequals( "", "" ) );	   // Both empty
		EXPECT_FALSE( iequals( "", "test" ) ); // One empty
		EXPECT_FALSE( iequals( "test", "" ) ); // One empty

		// Different lengths
		EXPECT_FALSE( iequals( "hello", "hello world" ) );
		EXPECT_FALSE( iequals( "hello world", "hello" ) );

		// Mixed case with numbers and special chars
		EXPECT_TRUE( iequals( "Test123!", "TEST123!" ) );
		EXPECT_TRUE( iequals( "Test123!", "test123!" ) );
		EXPECT_FALSE( iequals( "Test123!", "Test124!" ) );

		// ASCII-only case conversion
		EXPECT_TRUE( iequals( "ASCII", "ascii" ) );
		EXPECT_TRUE( iequals( "Test", "TEST" ) );
	}

	TEST( StringUtilsOperations, Count_Substring )
	{
		// Basic counting
		EXPECT_EQ( count( "banana", "na" ), 2 );
		EXPECT_EQ( count( "hello world", "l" ), 3 );
		EXPECT_EQ( count( "abcabcabc", "abc" ), 3 );

		// No matches
		EXPECT_EQ( count( "hello", "xyz" ), 0 );
		EXPECT_EQ( count( "test", "testing" ), 0 );

		// Edge cases
		EXPECT_EQ( count( "", "test" ), 0 ); // Empty string
		EXPECT_EQ( count( "test", "" ), 0 ); // Empty substring
		EXPECT_EQ( count( "", "" ), 0 );	 // Both empty

		// Single character matches
		EXPECT_EQ( count( "aaa", "a" ), 3 );
		EXPECT_EQ( count( "test", "t" ), 2 );

		// Overlapping not counted
		EXPECT_EQ( count( "aaaa", "aa" ), 2 );	 // Non-overlapping: "aa" + "aa"
		EXPECT_EQ( count( "ababa", "aba" ), 1 ); // "aba" found once, then skips to position after match

		// Full string match
		EXPECT_EQ( count( "hello", "hello" ), 1 );

		// Longer substring than string
		EXPECT_EQ( count( "hi", "hello" ), 0 );
	}

	TEST( StringUtilsOperations, CountOverlapping_Substring )
	{
		// Basic overlapping patterns
		EXPECT_EQ( countOverlapping( "aaaa", "aa" ), 3 );	 // Positions 0, 1, 2
		EXPECT_EQ( countOverlapping( "ababa", "aba" ), 2 );	 // Positions 0, 2
		EXPECT_EQ( countOverlapping( "banana", "ana" ), 2 ); // Positions 1, 3

		// Compare with non-overlapping
		EXPECT_EQ( count( "aaaa", "aa" ), 2 );			  // Non-overlapping
		EXPECT_EQ( countOverlapping( "aaaa", "aa" ), 3 ); // Overlapping

		// No matches
		EXPECT_EQ( countOverlapping( "hello", "xyz" ), 0 );
		EXPECT_EQ( countOverlapping( "test", "testing" ), 0 );

		// Edge cases
		EXPECT_EQ( countOverlapping( "", "test" ), 0 ); // Empty string
		EXPECT_EQ( countOverlapping( "test", "" ), 0 ); // Empty substring
		EXPECT_EQ( countOverlapping( "", "" ), 0 );		// Both empty

		// Single occurrence (same as non-overlapping)
		EXPECT_EQ( countOverlapping( "hello world", "world" ), 1 );
		EXPECT_EQ( countOverlapping( "abc", "abc" ), 1 );

		// Multiple non-overlapping occurrences (same result as count)
		EXPECT_EQ( countOverlapping( "a b a b a", "a" ), 3 );

		// Longer substring than string
		EXPECT_EQ( countOverlapping( "hi", "hello" ), 0 );

		// DNA sequence example (real-world use case)
		EXPECT_EQ( countOverlapping( "ATGATGATG", "ATG" ), 3 ); // Overlapping start codons

		// Repeated pattern
		EXPECT_EQ( countOverlapping( "aaaaaa", "aaa" ), 4 ); // Positions 0, 1, 2, 3
	}

	TEST( StringUtilsOperations, Count_Character )
	{
		// Basic counting
		EXPECT_EQ( count( "banana", 'a' ), 3 );
		EXPECT_EQ( count( "hello world", 'l' ), 3 );
		EXPECT_EQ( count( "test", 't' ), 2 );

		// No matches
		EXPECT_EQ( count( "hello", 'x' ), 0 );
		EXPECT_EQ( count( "abc", 'z' ), 0 );

		// Edge cases
		EXPECT_EQ( count( "", 'a' ), 0 );  // Empty string
		EXPECT_EQ( count( "a", 'a' ), 1 ); // Single character

		// All same character
		EXPECT_EQ( count( "aaaa", 'a' ), 4 );

		// Special characters
		EXPECT_EQ( count( "a,b,c,d", ',' ), 3 );
		EXPECT_EQ( count( "one two three", ' ' ), 2 );
	}

	TEST( StringUtilsOperations, Replace )
	{
		// Basic replacement
		EXPECT_EQ( replace( "hello world", "world", "C++" ), "hello C++" );
		EXPECT_EQ( replace( "test test", "test", "demo" ), "demo test" ); // Only first

		// No match
		EXPECT_EQ( replace( "hello", "xyz", "abc" ), "hello" );

		// Edge cases
		EXPECT_EQ( replace( "", "old", "new" ), "" );	   // Empty string
		EXPECT_EQ( replace( "test", "", "new" ), "test" ); // Empty old string
		EXPECT_EQ( replace( "hello", "hello", "" ), "" );  // Replace with empty

		// Same length replacement
		EXPECT_EQ( replace( "abc", "b", "x" ), "axc" );

		// Longer replacement
		EXPECT_EQ( replace( "hi", "i", "ello" ), "hello" );

		// Shorter replacement
		EXPECT_EQ( replace( "hello", "ello", "i" ), "hi" );

		// Beginning of string
		EXPECT_EQ( replace( "prefix-test", "prefix", "new" ), "new-test" );

		// End of string
		EXPECT_EQ( replace( "test-suffix", "suffix", "new" ), "test-new" );

		// Full string replacement
		EXPECT_EQ( replace( "old", "old", "new" ), "new" );
	}

	TEST( StringUtilsOperations, ReplaceAll )
	{
		// Basic replacement
		EXPECT_EQ( replaceAll( "hello world world", "world", "C++" ), "hello C++ C++" );
		EXPECT_EQ( replaceAll( "test test test", "test", "demo" ), "demo demo demo" );

		// No match
		EXPECT_EQ( replaceAll( "hello", "xyz", "abc" ), "hello" );

		// Edge cases
		EXPECT_EQ( replaceAll( "", "old", "new" ), "" );	  // Empty string
		EXPECT_EQ( replaceAll( "test", "", "new" ), "test" ); // Empty old string

		// Single occurrence (same as replace)
		EXPECT_EQ( replaceAll( "hello world", "world", "C++" ), "hello C++" );

		// Multiple non-adjacent occurrences
		EXPECT_EQ( replaceAll( "a b a b a", "a", "x" ), "x b x b x" );

		// Adjacent occurrences
		EXPECT_EQ( replaceAll( "aaa", "a", "b" ), "bbb" );

		// Longer replacement
		EXPECT_EQ( replaceAll( "a-b-c", "-", " and " ), "a and b and c" );

		// Shorter replacement
		EXPECT_EQ( replaceAll( "one and two and three", " and ", "+" ), "one+two+three" );

		// Replace with empty (removal)
		EXPECT_EQ( replaceAll( "a,b,c", ",", "" ), "abc" );

		// Complex pattern
		EXPECT_EQ( replaceAll( "the the the", "the", "a" ), "a a a" );
	}

	TEST( StringUtilsOperations, Join_Container )
	{
		// Basic join with vector
		std::vector<std::string> words{ "hello", "world", "test" };
		EXPECT_EQ( join( words, " " ), "hello world test" );
		EXPECT_EQ( join( words, ", " ), "hello, world, test" );
		EXPECT_EQ( join( words, "" ), "helloworldtest" );

		// Single element
		std::vector<std::string> single{ "alone" };
		EXPECT_EQ( join( single, ", " ), "alone" );

		// Empty container
		std::vector<std::string> empty;
		EXPECT_EQ( join( empty, ", " ), "" );

		// String views
		std::vector<std::string_view> views{ "a", "b", "c" };
		EXPECT_EQ( join( views, "-" ), "a-b-c" );

		// Different delimiter types
		std::vector<std::string> items{ "1", "2", "3" };
		EXPECT_EQ( join( items, "," ), "1,2,3" );
		EXPECT_EQ( join( items, " | " ), "1 | 2 | 3" );

		// CSV-style
		std::vector<std::string> csv{ "John", "Doe", "30", "Engineer" };
		EXPECT_EQ( join( csv, "," ), "John,Doe,30,Engineer" );
	}

	TEST( StringUtilsOperations, Join_Iterator )
	{
		std::vector<std::string> words{ "one", "two", "three", "four" };

		// Full range
		EXPECT_EQ( join( words.begin(), words.end(), " " ), "one two three four" );

		// Partial range
		EXPECT_EQ( join( words.begin(), words.begin() + 2, "-" ), "one-two" );
		EXPECT_EQ( join( words.begin() + 1, words.end(), ", " ), "two, three, four" );

		// Single element
		EXPECT_EQ( join( words.begin(), words.begin() + 1, ", " ), "one" );

		// Empty range
		EXPECT_EQ( join( words.begin(), words.begin(), ", " ), "" );
		EXPECT_EQ( join( words.end(), words.end(), ", " ), "" );
	}

	TEST( StringUtilsOperations, PadLeft )
	{
		// Basic padding
		EXPECT_EQ( padLeft( "42", 5, '0' ), "00042" );
		EXPECT_EQ( padLeft( "test", 10, ' ' ), "      test" );
		EXPECT_EQ( padLeft( "x", 5, '*' ), "****x" );

		// Default fill character (space)
		EXPECT_EQ( padLeft( "hi", 5 ), "   hi" );

		// Already at width
		EXPECT_EQ( padLeft( "hello", 5, ' ' ), "hello" );

		// Already wider than width
		EXPECT_EQ( padLeft( "hello world", 5, ' ' ), "hello world" );

		// Empty string
		EXPECT_EQ( padLeft( "", 5, '*' ), "*****" );

		// Zero width
		EXPECT_EQ( padLeft( "test", 0, ' ' ), "test" );

		// Real-world use cases
		EXPECT_EQ( padLeft( "1", 3, '0' ), "001" );						 // Zero-padding numbers
		EXPECT_EQ( padLeft( "Name", 20, ' ' ), "                Name" ); // Right-align in column
	}

	TEST( StringUtilsOperations, PadRight )
	{
		// Basic padding
		EXPECT_EQ( padRight( "42", 5, '0' ), "42000" );
		EXPECT_EQ( padRight( "test", 10, ' ' ), "test      " );
		EXPECT_EQ( padRight( "x", 5, '*' ), "x****" );

		// Default fill character (space)
		EXPECT_EQ( padRight( "hi", 5 ), "hi   " );

		// Already at width
		EXPECT_EQ( padRight( "hello", 5, ' ' ), "hello" );

		// Already wider than width
		EXPECT_EQ( padRight( "hello world", 5, ' ' ), "hello world" );

		// Empty string
		EXPECT_EQ( padRight( "", 5, '*' ), "*****" );

		// Zero width
		EXPECT_EQ( padRight( "test", 0, ' ' ), "test" );

		// Real-world use cases
		EXPECT_EQ( padRight( "Name", 20, ' ' ), "Name                " ); // Left-align in column
		EXPECT_EQ( padRight( "OK", 10, '.' ), "OK........" );			  // Menu items
	}

	TEST( StringUtilsOperations, Center )
	{
		// Basic centering
		EXPECT_EQ( center( "Hi", 6, '*' ), "**Hi**" );
		EXPECT_EQ( center( "test", 10, ' ' ), "   test   " );
		EXPECT_EQ( center( "x", 5, '-' ), "--x--" );

		// Default fill character (space)
		EXPECT_EQ( center( "hello", 11 ), "   hello   " );

		// Odd padding (extra char goes right)
		EXPECT_EQ( center( "Hi", 5, '*' ), "*Hi**" );		// 3 total padding: 1 left, 2 right
		EXPECT_EQ( center( "test", 9, ' ' ), "  test   " ); // 5 total padding: 2 left, 3 right

		// Already at width
		EXPECT_EQ( center( "hello", 5, ' ' ), "hello" );

		// Already wider than width
		EXPECT_EQ( center( "hello world", 5, ' ' ), "hello world" );

		// Empty string
		EXPECT_EQ( center( "", 5, '*' ), "*****" );

		// Zero width
		EXPECT_EQ( center( "test", 0, ' ' ), "test" );

		// Real-world use cases
		EXPECT_EQ( center( "TITLE", 20, '=' ), "=======TITLE========" ); // Headers
		EXPECT_EQ( center( "Menu", 10, ' ' ), "   Menu   " );			 // Centered text
	}

	TEST( StringUtilsOperations, Repeat )
	{
		// Basic repetition
		EXPECT_EQ( repeat( "*", 5 ), "*****" );
		EXPECT_EQ( repeat( "ab", 3 ), "ababab" );
		EXPECT_EQ( repeat( "test", 2 ), "testtest" );

		// Single repetition
		EXPECT_EQ( repeat( "hello", 1 ), "hello" );

		// Zero repetitions
		EXPECT_EQ( repeat( "test", 0 ), "" );

		// Empty string
		EXPECT_EQ( repeat( "", 5 ), "" );

		// Long strings
		EXPECT_EQ( repeat( "abc", 4 ), "abcabcabcabc" );

		// Real-world use cases
		EXPECT_EQ( repeat( "-", 40 ), "----------------------------------------" ); // Separators
		EXPECT_EQ( repeat( " ", 4 ), "    " );										// Indentation
		EXPECT_EQ( repeat( "=", 10 ), "==========" );								// Headers
		EXPECT_EQ( repeat( "Na", 8 ) + " Batman!", "NaNaNaNaNaNaNaNa Batman!" );	// :)
	}

	TEST( StringUtilsOperations, Reverse )
	{
		// Basic reverse
		EXPECT_EQ( reverse( "hello" ), "olleh" );
		EXPECT_EQ( reverse( "world" ), "dlrow" );
		EXPECT_EQ( reverse( "abc" ), "cba" );

		// Single character
		EXPECT_EQ( reverse( "x" ), "x" );

		// Empty string
		EXPECT_EQ( reverse( "" ), "" );

		// Palindrome check (reverse equals original)
		EXPECT_EQ( reverse( "radar" ), "radar" );
		EXPECT_EQ( reverse( "noon" ), "noon" );
		EXPECT_NE( reverse( "hello" ), "hello" );

		// Numbers and special characters
		EXPECT_EQ( reverse( "12345" ), "54321" );
		EXPECT_EQ( reverse( "a!b@c#" ), "#c@b!a" );

		// Real-world use cases
		EXPECT_EQ( reverse( "desserts" ), "stressed" );	   // Palindrome pairs
		EXPECT_EQ( reverse( reverse( "test" ) ), "test" ); // Double reverse = identity
		std::string dna = "ATCG";
		EXPECT_EQ( reverse( dna ), "GCTA" ); // DNA complement prep
	}

	TEST( StringUtilsOperations, IndexOf )
	{
		constexpr auto npos = std::string_view::npos;

		// Basic search
		EXPECT_EQ( indexOf( "hello world", "world" ), 6 );
		EXPECT_EQ( indexOf( "hello world", "hello" ), 0 );
		EXPECT_EQ( indexOf( "hello world", "o" ), 4 ); // First 'o'

		// Not found
		EXPECT_EQ( indexOf( "hello world", "xyz" ), npos );
		EXPECT_EQ( indexOf( "hello", "hello world" ), npos ); // Substr longer than str

		// Empty cases
		EXPECT_EQ( indexOf( "hello", "" ), 0 );	  // Empty substr found at position 0
		EXPECT_EQ( indexOf( "", "" ), 0 );		  // Both empty
		EXPECT_EQ( indexOf( "", "test" ), npos ); // Empty str, non-empty substr

		// Case sensitivity
		EXPECT_EQ( indexOf( "Hello World", "world" ), npos ); // Case mismatch
		EXPECT_EQ( indexOf( "Hello World", "World" ), 6 );	  // Case match

		// Multiple occurrences (returns first)
		EXPECT_EQ( indexOf( "hello hello", "hello" ), 0 );
		EXPECT_EQ( indexOf( "abcabc", "abc" ), 0 );

		// Real-world use cases
		EXPECT_EQ( indexOf( "https://example.com/path", "://" ), 5 );	   // URL parsing
		EXPECT_EQ( indexOf( "user@example.com", "@" ), 4 );				   // Email parsing
		EXPECT_EQ( indexOf( "Content-Type: application/json", ":" ), 12 ); // HTTP header parsing
		EXPECT_EQ( indexOf( "file.txt", "." ), 4 );						   // Extension search
	}

	TEST( StringUtilsOperations, LastIndexOf )
	{
		constexpr auto npos = std::string_view::npos;

		// Basic search (returns last occurrence)
		EXPECT_EQ( lastIndexOf( "hello hello", "hello" ), 6 );
		EXPECT_EQ( lastIndexOf( "abcabc", "abc" ), 3 );
		EXPECT_EQ( lastIndexOf( "hello world", "o" ), 7 ); // Last 'o'

		// Single occurrence
		EXPECT_EQ( lastIndexOf( "hello world", "world" ), 6 );
		EXPECT_EQ( lastIndexOf( "hello world", "hello" ), 0 );

		// Not found
		EXPECT_EQ( lastIndexOf( "hello world", "xyz" ), npos );
		EXPECT_EQ( lastIndexOf( "hello", "hello world" ), npos );

		// Empty cases
		EXPECT_EQ( lastIndexOf( "hello", "" ), 5 );	  // Empty substr found at end (str.size())
		EXPECT_EQ( lastIndexOf( "", "" ), 0 );		  // Both empty
		EXPECT_EQ( lastIndexOf( "", "test" ), npos ); // Empty str, non-empty substr

		// Case sensitivity
		EXPECT_EQ( lastIndexOf( "Hello World", "world" ), npos );
		EXPECT_EQ( lastIndexOf( "Hello World", "World" ), 6 );

		// Real-world use cases
		EXPECT_EQ( lastIndexOf( "file.backup.txt", "." ), 11 );		  // File extension (last dot)
		EXPECT_EQ( lastIndexOf( "/usr/local/bin", "/" ), 10 );		  // Path basename (last slash)
		EXPECT_EQ( lastIndexOf( "user@mail.example.com", "." ), 17 ); // Domain TLD (last dot)
		EXPECT_EQ( lastIndexOf( "path/to/file.txt", "/" ), 7 );		  // Directory separator
		EXPECT_EQ( lastIndexOf( "192.168.1.1", "." ), 9 );			  // IP last octet
	}

	//----------------------------------------------
	// String trimming
	//----------------------------------------------

	//----------------------------
	// Non-allocating
	//----------------------------

	TEST( StringUtilsStringTrimming, TrimStart )
	{
		// No leading whitespace
		EXPECT_EQ( trimStart( "hello" ), "hello" );
		EXPECT_EQ( trimStart( "hello world" ), "hello world" );

		// Leading whitespace
		EXPECT_EQ( trimStart( " hello" ), "hello" );
		EXPECT_EQ( trimStart( "\thello" ), "hello" );
		EXPECT_EQ( trimStart( "\n\r hello" ), "hello" );
		EXPECT_EQ( trimStart( "   hello world   " ), "hello world   " );

		// Only whitespace
		EXPECT_EQ( trimStart( "   " ), "" );
		EXPECT_EQ( trimStart( "\t\n\r" ), "" );

		// Empty string
		EXPECT_EQ( trimStart( "" ), "" );

		// Mixed whitespace types
		EXPECT_EQ( trimStart( " \t\n\r\f\v hello" ), "hello" );
	}

	TEST( StringUtilsStringTrimming, TrimEnd )
	{
		// No trailing whitespace
		EXPECT_EQ( trimEnd( "hello" ), "hello" );
		EXPECT_EQ( trimEnd( "hello world" ), "hello world" );

		// Trailing whitespace
		EXPECT_EQ( trimEnd( "hello " ), "hello" );
		EXPECT_EQ( trimEnd( "hello\t" ), "hello" );
		EXPECT_EQ( trimEnd( "hello \n\r" ), "hello" );
		EXPECT_EQ( trimEnd( "   hello world   " ), "   hello world" );

		// Only whitespace
		EXPECT_EQ( trimEnd( "   " ), "" );
		EXPECT_EQ( trimEnd( "\t\n\r" ), "" );

		// Empty string
		EXPECT_EQ( trimEnd( "" ), "" );

		// Mixed whitespace types
		EXPECT_EQ( trimEnd( "hello \t\n\r\f\v " ), "hello" );
	}

	TEST( StringUtilsStringTrimming, Trim )
	{
		// No whitespace
		EXPECT_EQ( trim( "hello" ), "hello" );
		EXPECT_EQ( trim( "hello world" ), "hello world" );

		// Leading and trailing whitespace
		EXPECT_EQ( trim( " hello " ), "hello" );
		EXPECT_EQ( trim( "\thello\t" ), "hello" );
		EXPECT_EQ( trim( "\n\r hello world \n\r" ), "hello world" );
		EXPECT_EQ( trim( "   hello world   " ), "hello world" );

		// Only leading whitespace
		EXPECT_EQ( trim( " hello" ), "hello" );

		// Only trailing whitespace
		EXPECT_EQ( trim( "hello " ), "hello" );

		// Only whitespace
		EXPECT_EQ( trim( "   " ), "" );
		EXPECT_EQ( trim( "\t\n\r\f\v" ), "" );

		// Empty string
		EXPECT_EQ( trim( "" ), "" );

		// Internal whitespace preserved
		EXPECT_EQ( trim( "  hello  world  " ), "hello  world" );
	}

	//----------------------------------------------
	// String case conversion
	//----------------------------------------------

	TEST( StringUtilsCaseConversion, ToLowerString )
	{
		// Basic ASCII conversion
		EXPECT_EQ( "hello world", toLower( "HELLO WORLD" ) );
		EXPECT_EQ( "hello world", toLower( "Hello World" ) );
		EXPECT_EQ( "hello world", toLower( "HeLLo WoRLd" ) );

		// Already lowercase
		EXPECT_EQ( "hello world", toLower( "hello world" ) );

		// Mixed case with numbers and symbols
		EXPECT_EQ( "test123!@#", toLower( "TEST123!@#" ) );
		EXPECT_EQ( "test123!@#", toLower( "Test123!@#" ) );

		// Empty string
		EXPECT_EQ( "", toLower( "" ) );

		// Single characters
		EXPECT_EQ( "a", toLower( "A" ) );
		EXPECT_EQ( "z", toLower( "Z" ) );
		EXPECT_EQ( "1", toLower( "1" ) );
		EXPECT_EQ( "!", toLower( "!" ) );

		// All uppercase alphabet
		EXPECT_EQ( "abcdefghijklmnopqrstuvwxyz", toLower( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );

		// Unicode characters should remain unchanged (ASCII-only conversion)
		EXPECT_EQ( "café", toLower( "café" ) ); // Already has lowercase é
		EXPECT_EQ( "cafÉ", toLower( "CAFÉ" ) ); // Only ASCII 'C', 'A', 'F' converted, É unchanged

		// Large string test
		const std::string largeUpper( 1000, 'X' );
		const std::string largeLower( 1000, 'x' );
		EXPECT_EQ( largeLower, toLower( largeUpper ) );
	}

	TEST( StringUtilsCaseConversion, ToUpperString )
	{
		// Basic ASCII conversion
		EXPECT_EQ( "HELLO WORLD", toUpper( "hello world" ) );
		EXPECT_EQ( "HELLO WORLD", toUpper( "Hello World" ) );
		EXPECT_EQ( "HELLO WORLD", toUpper( "HeLLo WoRLd" ) );

		// Already uppercase
		EXPECT_EQ( "HELLO WORLD", toUpper( "HELLO WORLD" ) );

		// Mixed case with numbers and symbols
		EXPECT_EQ( "TEST123!@#", toUpper( "test123!@#" ) );
		EXPECT_EQ( "TEST123!@#", toUpper( "Test123!@#" ) );

		// Empty string
		EXPECT_EQ( "", toUpper( "" ) );

		// Single characters
		EXPECT_EQ( "A", toUpper( "a" ) );
		EXPECT_EQ( "Z", toUpper( "z" ) );
		EXPECT_EQ( "1", toUpper( "1" ) );
		EXPECT_EQ( "!", toUpper( "!" ) );

		// All lowercase alphabet
		EXPECT_EQ( "ABCDEFGHIJKLMNOPQRSTUVWXYZ", toUpper( "abcdefghijklmnopqrstuvwxyz" ) );

		// Unicode characters should remain unchanged (ASCII-only conversion)
		EXPECT_EQ( "CAFÉ", toUpper( "CAFÉ" ) ); // Already has uppercase É
		EXPECT_EQ( "CAFé", toUpper( "café" ) ); // Only ASCII 'c', 'a', 'f' converted, é unchanged

		// Large string test
		const std::string largeLower( 1000, 'x' );
		const std::string largeUpper( 1000, 'X' );
		EXPECT_EQ( largeUpper, toUpper( largeLower ) );
	}

	//----------------------------------------------
	// Character case conversion
	//----------------------------------------------

	TEST( StringUtilsCaseConversion, ToLowerChar )
	{
		// ASCII uppercase to lowercase
		EXPECT_EQ( 'a', toLower( 'A' ) );
		EXPECT_EQ( 'z', toLower( 'Z' ) );
		EXPECT_EQ( 'm', toLower( 'M' ) );

		// Already lowercase - no change
		EXPECT_EQ( 'a', toLower( 'a' ) );
		EXPECT_EQ( 'z', toLower( 'z' ) );
		EXPECT_EQ( 'm', toLower( 'm' ) );

		// Non-alphabetic characters - no change
		EXPECT_EQ( '0', toLower( '0' ) );
		EXPECT_EQ( '9', toLower( '9' ) );
		EXPECT_EQ( ' ', toLower( ' ' ) );
		EXPECT_EQ( '!', toLower( '!' ) );
		EXPECT_EQ( '@', toLower( '@' ) );

		// Edge ASCII values
		EXPECT_EQ( '@', toLower( '@' ) ); // ASCII 64 (before 'A')
		EXPECT_EQ( '[', toLower( '[' ) ); // ASCII 91 (after 'Z')
		EXPECT_EQ( '`', toLower( '`' ) ); // ASCII 96 (before 'a')
		EXPECT_EQ( '{', toLower( '{' ) ); // ASCII 123 (after 'z')
	}

	TEST( StringUtilsCaseConversion, ToUpperChar )
	{
		// ASCII lowercase to uppercase
		EXPECT_EQ( 'A', toUpper( 'a' ) );
		EXPECT_EQ( 'Z', toUpper( 'z' ) );
		EXPECT_EQ( 'M', toUpper( 'm' ) );

		// Already uppercase - no change
		EXPECT_EQ( 'A', toUpper( 'A' ) );
		EXPECT_EQ( 'Z', toUpper( 'Z' ) );
		EXPECT_EQ( 'M', toUpper( 'M' ) );

		// Non-alphabetic characters - no change
		EXPECT_EQ( '0', toUpper( '0' ) );
		EXPECT_EQ( '9', toUpper( '9' ) );
		EXPECT_EQ( ' ', toUpper( ' ' ) );
		EXPECT_EQ( '!', toUpper( '!' ) );
		EXPECT_EQ( '@', toUpper( '@' ) );

		// Edge ASCII values
		EXPECT_EQ( '@', toUpper( '@' ) ); // ASCII 64 (before 'A')
		EXPECT_EQ( '[', toUpper( '[' ) ); // ASCII 91 (after 'Z')
		EXPECT_EQ( '`', toUpper( '`' ) ); // ASCII 96 (before 'a')
		EXPECT_EQ( '{', toUpper( '{' ) ); // ASCII 123 (after 'z')
	}

	//----------------------------------------------
	// String parsing
	//----------------------------------------------

	//----------------------------
	// Bool
	//----------------------------

	TEST( StringUtilsBoolParsing, FromString_Bool_TrueValues )
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

	TEST( StringUtilsBoolParsing, FromString_Bool_FalseValues )
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

	TEST( StringUtilsBoolParsing, FromString_Bool_InvalidValues )
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

	//----------------------------------------------
	// Numeric
	//----------------------------------------------

	TEST( StringUtilsNumericParsing, FromString_Int )
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

	TEST( StringUtilsNumericParsing, FromString_UInt )
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

	TEST( StringUtilsNumericParsing, FromString_Long )
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

	TEST( StringUtilsNumericParsing, FromString_Float )
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

	TEST( StringUtilsNumericParsing, FromString_Double )
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

	//----------------------------------------------
	// PerformanceAndEdgeCase
	//----------------------------------------------

	TEST( StringUtilsPerformanceAndEdgeCase, Unicode )
	{
		// Basic Unicode string handling (UTF-8 encoded)
		const std::string utf8_string = "café";
		const std::string utf8_upper = "CAFÉ";
		const std::string ascii_cafe = "cafe";

		// Test basic string operations with Unicode
		EXPECT_TRUE( equals( utf8_string, "café" ) );
		EXPECT_FALSE( equals( utf8_string, utf8_upper ) ); // Case sensitive
		EXPECT_FALSE( equals( utf8_string, ascii_cafe ) ); // é ≠ e

		// String length tests with Unicode (UTF-8 byte count vs character count)
		EXPECT_TRUE( hasExactLength( utf8_string, 5 ) );  // "café" = 5 bytes in UTF-8
		EXPECT_FALSE( hasExactLength( utf8_string, 4 ) ); // Not 4 characters visually

		// StartsWith/EndsWith with Unicode
		EXPECT_TRUE( startsWith( utf8_string, "ca" ) );
		EXPECT_TRUE( endsWith( utf8_string, "é" ) );  // Single Unicode character
		EXPECT_FALSE( endsWith( utf8_string, "e" ) ); // ASCII 'e' ≠ Unicode 'é'

		// Contains with Unicode
		EXPECT_TRUE( contains( utf8_string, "af" ) );
		EXPECT_TRUE( contains( utf8_string, "é" ) );
		EXPECT_FALSE( contains( utf8_string, "e" ) ); // ASCII 'e' not in "café"

		// Case-insensitive comparison limitations with Unicode
		// Note: std::tolower only works correctly for ASCII characters
		EXPECT_FALSE( iequals( utf8_string, utf8_upper ) ); // Expected failure for non-ASCII
		EXPECT_TRUE( iequals( "ASCII", "ascii" ) );			// Works for ASCII only

		// Test with various Unicode characters
		const std::string emoji = "Hello 🌍 World";
		const std::string chinese = "你好世界";
		const std::string russian = "Привет мир";
		const std::string arabic = "مرحبا بالعالم";

		// Basic operations should work with any UTF-8 encoded string
		EXPECT_FALSE( isEmpty( emoji ) );
		EXPECT_FALSE( isEmpty( chinese ) );
		EXPECT_FALSE( isEmpty( russian ) );
		EXPECT_FALSE( isEmpty( arabic ) );

		EXPECT_TRUE( startsWith( emoji, "Hello" ) );
		EXPECT_TRUE( endsWith( emoji, "World" ) );
		EXPECT_TRUE( contains( emoji, "🌍" ) );
		EXPECT_TRUE( equals( chinese, chinese ) );

		// Mixed ASCII and Unicode
		const std::string mixed = "ASCII混合テキストMIXED";
		EXPECT_TRUE( startsWith( mixed, "ASCII" ) );
		EXPECT_TRUE( endsWith( mixed, "MIXED" ) );
		EXPECT_TRUE( contains( mixed, "混合" ) );
		EXPECT_TRUE( contains( mixed, "テキスト" ) );

		// Unicode normalization considerations (different byte representations)
		// Note: This library treats strings as byte sequences, not normalized Unicode
		const std::string composed = "é";	// Single composed character U+00E9
		const std::string decomposed = "é"; // e + combining acute accent U+0065 + U+0301
		// These might be visually identical but have different byte representations
		// The library correctly treats them as different byte sequences

		// Boolean parsing with Unicode characters should fail gracefully
		bool boolResult{ false };
		EXPECT_FALSE( fromString<bool>( "真", boolResult ) );	// Chinese "true"
		EXPECT_FALSE( fromString<bool>( "はい", boolResult ) ); // Japanese "yes"
		EXPECT_FALSE( fromString<bool>( "да", boolResult ) );	// Russian "yes"
		EXPECT_FALSE( fromString<bool>( "نعم", boolResult ) );	// Arabic "yes"

		// Numeric parsing with Unicode should also fail gracefully
		int intResult{ 0 };
		EXPECT_FALSE( fromString<int>( "１２３", intResult ) ); // Full-width numbers
		EXPECT_FALSE( fromString<int>( "۱۲۳", intResult ) );	// Arabic-Indic digits

		// Performance test with Unicode strings
		const std::string rocket_emoji{ "🚀" };				   // Single rocket emoji
		const std::size_t rocket_bytes{ rocket_emoji.size() }; // Should be 4 bytes for 🚀

		// Create string with multiple emojis using string concatenation
		std::string longUnicode;
		for ( int i{ 0 }; i < 100; ++i )
		{
			longUnicode += rocket_emoji;
		}

		EXPECT_FALSE( isEmpty( longUnicode ) );
		EXPECT_TRUE( hasExactLength( longUnicode, 100 * rocket_bytes ) ); // 100 × bytes per emoji
		EXPECT_TRUE( contains( longUnicode, rocket_emoji ) );

		// Test with Latin-1 accented characters (safer for MSVC)
		std::string accented;
		for ( int i{ 0 }; i < 50; ++i )
		{
			accented += "é"; // Each é is 2 bytes in UTF-8
		}
		EXPECT_TRUE( hasExactLength( accented, 100 ) ); // 50 × 2 bytes per é
		EXPECT_TRUE( contains( accented, "é" ) );

		// Test basic Unicode awareness without complex character construction
		const std::string simple_unicode = "Héllo Wörld";
		EXPECT_TRUE( contains( simple_unicode, "é" ) );
		EXPECT_TRUE( contains( simple_unicode, "ö" ) );
		EXPECT_FALSE( contains( simple_unicode, "e" ) ); // 'e' ≠ 'é'
	}

	TEST( StringUtilsPerformanceAndEdgeCase, LargeStrings )
	{
		// Test with large strings to ensure no performance issues
		const std::string largeStr( 10000, 'x' );
		const std::string largeSuffix( 1000, 'x' );
		const std::string largePrefix( 1000, 'x' );

		EXPECT_TRUE( endsWith( largeStr, largeSuffix ) );
		EXPECT_TRUE( startsWith( largeStr, largePrefix ) );
		EXPECT_TRUE( contains( largeStr, largeSuffix ) );
		EXPECT_TRUE( equals( largeStr, largeStr ) );
		EXPECT_TRUE( iequals( largeStr, largeStr ) );
		EXPECT_TRUE( hasExactLength( largeStr, 10000 ) );
		EXPECT_FALSE( isEmpty( largeStr ) );
	}

	TEST( StringUtilsPerformanceAndEdgeCase, SpecialCharacters )
	{
		// Test with special characters
		const std::string special = "!@#$%^&*()_+-=[]{}|;':\",./<>?";

		EXPECT_TRUE( startsWith( special, "!@#" ) );
		EXPECT_TRUE( endsWith( special, "<>?" ) );
		EXPECT_TRUE( contains( special, "[]{}|" ) );
		EXPECT_TRUE( equals( special, special ) );
		EXPECT_TRUE( iequals( special, special ) );

		// Unicode characters (basic test)
		EXPECT_TRUE( equals( "café", "café" ) );
		EXPECT_FALSE( equals( "café", "cafe" ) );
	}

	TEST( StringUtilsPerformanceAndEdgeCase, NullTerminatedStrings )
	{
		// Test with null-terminated strings to ensure string_view handles them correctly
		const char* cstr = "hello world";

		EXPECT_TRUE( startsWith( cstr, "hello" ) );
		EXPECT_TRUE( endsWith( cstr, "world" ) );
		EXPECT_TRUE( contains( cstr, "o w" ) );
		EXPECT_TRUE( hasExactLength( cstr, 11 ) );

		bool result;
		EXPECT_TRUE( fromString<bool>( "true", result ) );
		EXPECT_TRUE( result );

		int intResult;
		EXPECT_TRUE( fromString<int>( "123", intResult ) );
		EXPECT_EQ( 123, intResult );
	}

	//----------------------------------------------
	// Round-trip conversion tests
	//----------------------------------------------

	TEST( StringUtilsCaseConversion, RoundTripConversion )
	{
		// Test that toLower(toUpper(x)) == toLower(x) and vice versa for ASCII
		const std::string original = "Hello World 123!";
		const std::string lower = toLower( original );
		const std::string upper = toUpper( original );

		// Round-trip conversions
		EXPECT_EQ( lower, toLower( toUpper( lower ) ) );
		EXPECT_EQ( upper, toUpper( toLower( upper ) ) );

		// ASCII alphabet round-trip
		const std::string ascii = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
		EXPECT_EQ( toLower( ascii ), toLower( toUpper( toLower( ascii ) ) ) );
		EXPECT_EQ( toUpper( ascii ), toUpper( toLower( toUpper( ascii ) ) ) );
	}

	TEST( StringUtilsCaseConversion, EdgeCases )
	{
		// Edge ASCII boundaries for case conversion
		std::string edgeCases = "@[`{";				  // Characters around A-Z and a-z ranges
		EXPECT_EQ( edgeCases, toLower( edgeCases ) ); // Should remain unchanged
		EXPECT_EQ( edgeCases, toUpper( edgeCases ) ); // Should remain unchanged

		// Null character (should handle gracefully)
		EXPECT_EQ( '\0', toLower( '\0' ) );
		EXPECT_EQ( '\0', toUpper( '\0' ) );

		// Whitespace characters
		EXPECT_EQ( ' ', toLower( ' ' ) );
		EXPECT_EQ( '\t', toLower( '\t' ) );
		EXPECT_EQ( '\n', toLower( '\n' ) );
		EXPECT_EQ( '\r', toLower( '\r' ) );

		EXPECT_EQ( ' ', toUpper( ' ' ) );
		EXPECT_EQ( '\t', toUpper( '\t' ) );
		EXPECT_EQ( '\n', toUpper( '\n' ) );
		EXPECT_EQ( '\r', toUpper( '\r' ) );
	}

	//----------------------------------------------
	// Substring Extraction
	//----------------------------------------------

	TEST( StringUtilsSubstringExtraction, SubstringBefore )
	{
		// Basic functionality
		EXPECT_EQ( "hello", substringBefore( "hello.world.txt", "." ) );
		EXPECT_EQ( "hello", substringBefore( "hello.world", "." ) );
		EXPECT_EQ( "", substringBefore( ".world", "." ) );

		// Delimiter not found
		EXPECT_EQ( "hello", substringBefore( "hello", "." ) );
		EXPECT_EQ( "helloworld", substringBefore( "helloworld", "." ) );

		// Empty delimiter
		EXPECT_EQ( "hello.world", substringBefore( "hello.world", "" ) );

		// Empty string
		EXPECT_EQ( "", substringBefore( "", "." ) );

		// Multi-character delimiter
		EXPECT_EQ( "hello", substringBefore( "hello::world", "::" ) );
		EXPECT_EQ( "file", substringBefore( "file.tar.gz", ".tar" ) );

		// Delimiter at start
		EXPECT_EQ( "", substringBefore( "::world", "::" ) );

		// Multiple occurrences (first match)
		EXPECT_EQ( "one", substringBefore( "one.two.three", "." ) );
	}

	TEST( StringUtilsSubstringExtraction, SubstringAfter )
	{
		// Basic functionality
		EXPECT_EQ( "world.txt", substringAfter( "hello.world.txt", "." ) );
		EXPECT_EQ( "world", substringAfter( "hello.world", "." ) );
		EXPECT_EQ( "world", substringAfter( ".world", "." ) );

		// Delimiter not found
		EXPECT_EQ( "", substringAfter( "hello", "." ) );
		EXPECT_EQ( "", substringAfter( "helloworld", "." ) );

		// Empty delimiter
		EXPECT_EQ( "", substringAfter( "hello.world", "" ) );

		// Empty string
		EXPECT_EQ( "", substringAfter( "", "." ) );

		// Multi-character delimiter
		EXPECT_EQ( "world", substringAfter( "hello::world", "::" ) );
		EXPECT_EQ( ".gz", substringAfter( "file.tar.gz", "tar" ) );

		// Delimiter at end
		EXPECT_EQ( "", substringAfter( "hello::", "::" ) );

		// Multiple occurrences (first match)
		EXPECT_EQ( "two.three", substringAfter( "one.two.three", "." ) );
	}

	TEST( StringUtilsSubstringExtraction, SubstringBeforeLast )
	{
		// Basic functionality
		EXPECT_EQ( "hello.world", substringBeforeLast( "hello.world.txt", "." ) );
		EXPECT_EQ( "hello", substringBeforeLast( "hello.world", "." ) );
		EXPECT_EQ( "", substringBeforeLast( ".world", "." ) );

		// Delimiter not found
		EXPECT_EQ( "hello", substringBeforeLast( "hello", "." ) );
		EXPECT_EQ( "helloworld", substringBeforeLast( "helloworld", "." ) );

		// Empty delimiter
		EXPECT_EQ( "hello.world", substringBeforeLast( "hello.world", "" ) );

		// Empty string
		EXPECT_EQ( "", substringBeforeLast( "", "." ) );

		// Multi-character delimiter
		EXPECT_EQ( "hello::world", substringBeforeLast( "hello::world::test", "::" ) );
		EXPECT_EQ( "file.tar", substringBeforeLast( "file.tar.gz", "." ) );

		// Multiple occurrences (last match)
		EXPECT_EQ( "one.two", substringBeforeLast( "one.two.three", "." ) );

		// Path examples
		EXPECT_EQ( "/path/to", substringBeforeLast( "/path/to/file.txt", "/" ) );
	}

	TEST( StringUtilsSubstringExtraction, SubstringAfterLast )
	{
		// Basic functionality
		EXPECT_EQ( "txt", substringAfterLast( "hello.world.txt", "." ) );
		EXPECT_EQ( "world", substringAfterLast( "hello.world", "." ) );
		EXPECT_EQ( "world", substringAfterLast( ".world", "." ) );

		// Delimiter not found
		EXPECT_EQ( "", substringAfterLast( "hello", "." ) );
		EXPECT_EQ( "", substringAfterLast( "helloworld", "." ) );

		// Empty delimiter
		EXPECT_EQ( "", substringAfterLast( "hello.world", "" ) );

		// Empty string
		EXPECT_EQ( "", substringAfterLast( "", "." ) );

		// Multi-character delimiter
		EXPECT_EQ( "test", substringAfterLast( "hello::world::test", "::" ) );
		EXPECT_EQ( "gz", substringAfterLast( "file.tar.gz", "." ) );

		// Delimiter at end
		EXPECT_EQ( "", substringAfterLast( "hello::", "::" ) );

		// Multiple occurrences (last match)
		EXPECT_EQ( "three", substringAfterLast( "one.two.three", "." ) );

		// File extension extraction
		EXPECT_EQ( "cpp", substringAfterLast( "main.cpp", "." ) );
		EXPECT_EQ( "gz", substringAfterLast( "archive.tar.gz", "." ) );
	}

	TEST( StringUtilsSubstringExtraction, ExtractBetween )
	{
		// Basic functionality
		EXPECT_EQ( "world", extractBetween( "Hello [world] test", "[", "]" ) );
		EXPECT_EQ( "content", extractBetween( "Start<content>End", "<", ">" ) );
		EXPECT_EQ( "text", extractBetween( "{{text}}", "{{", "}}" ) );

		// Start delimiter not found
		EXPECT_EQ( "", extractBetween( "Hello world test", "[", "]" ) );

		// End delimiter not found
		EXPECT_EQ( "", extractBetween( "Hello [world test", "[", "]" ) );

		// Empty delimiters
		EXPECT_EQ( "", extractBetween( "Hello world", "", "]" ) );
		EXPECT_EQ( "", extractBetween( "Hello world", "[", "" ) );
		EXPECT_EQ( "", extractBetween( "Hello world", "", "" ) );

		// Empty string
		EXPECT_EQ( "", extractBetween( "", "[", "]" ) );

		// Empty content between delimiters
		EXPECT_EQ( "", extractBetween( "Hello []", "[", "]" ) );
		EXPECT_EQ( "", extractBetween( "<>", "<", ">" ) );

		// Multiple occurrences (first match)
		EXPECT_EQ( "first", extractBetween( "[first] and [second]", "[", "]" ) );

		// Nested delimiters (extracts to first end)
		EXPECT_EQ( "outer [inner", extractBetween( "[outer [inner]]", "[", "]" ) );

		// Real-world examples
		EXPECT_EQ( "tag", extractBetween( "<tag>content</tag>", "<", ">" ) );
		EXPECT_EQ( "value", extractBetween( "key=\"value\"", "\"", "\"" ) );
		EXPECT_EQ( "192.168.1.1", extractBetween( "[192.168.1.1]:8080", "[", "]" ) );
	}

	TEST( StringUtilsSubstringExtraction, RemovePrefix )
	{
		// Basic functionality
		EXPECT_EQ( "World", removePrefix( "HelloWorld", "Hello" ) );
		EXPECT_EQ( "world.txt", removePrefix( "file.world.txt", "file." ) );

		// Prefix not present
		EXPECT_EQ( "HelloWorld", removePrefix( "HelloWorld", "Goodbye" ) );
		EXPECT_EQ( "test", removePrefix( "test", "prefix" ) );

		// Empty prefix
		EXPECT_EQ( "HelloWorld", removePrefix( "HelloWorld", "" ) );

		// Empty string
		EXPECT_EQ( "", removePrefix( "", "Hello" ) );
		EXPECT_EQ( "", removePrefix( "", "" ) );

		// Prefix equals entire string
		EXPECT_EQ( "", removePrefix( "Hello", "Hello" ) );

		// Prefix longer than string
		EXPECT_EQ( "Hi", removePrefix( "Hi", "Hello" ) );

		// Case sensitive
		EXPECT_EQ( "helloWorld", removePrefix( "helloWorld", "Hello" ) );
		EXPECT_EQ( "World", removePrefix( "HelloWorld", "Hello" ) );

		// Real-world examples
		EXPECT_EQ( "example.com", removePrefix( "www.example.com", "www." ) );
		EXPECT_EQ( "/path/to/file", removePrefix( "/root/path/to/file", "/root" ) );
		EXPECT_EQ( "String", removePrefix( "std::String", "std::" ) );
	}

	TEST( StringUtilsSubstringExtraction, RemoveSuffix )
	{
		// Basic functionality
		EXPECT_EQ( "Hello", removeSuffix( "HelloWorld", "World" ) );
		EXPECT_EQ( "file.world", removeSuffix( "file.world.txt", ".txt" ) );

		// Suffix not present
		EXPECT_EQ( "HelloWorld", removeSuffix( "HelloWorld", "Goodbye" ) );
		EXPECT_EQ( "test", removeSuffix( "test", "suffix" ) );

		// Empty suffix
		EXPECT_EQ( "HelloWorld", removeSuffix( "HelloWorld", "" ) );

		// Empty string
		EXPECT_EQ( "", removeSuffix( "", "World" ) );
		EXPECT_EQ( "", removeSuffix( "", "" ) );

		// Suffix equals entire string
		EXPECT_EQ( "", removeSuffix( "Hello", "Hello" ) );

		// Suffix longer than string
		EXPECT_EQ( "Hi", removeSuffix( "Hi", "World" ) );

		// Case sensitive
		EXPECT_EQ( "Helloworld", removeSuffix( "Helloworld", "World" ) );
		EXPECT_EQ( "Hello", removeSuffix( "HelloWorld", "World" ) );

		// Real-world examples
		EXPECT_EQ( "document", removeSuffix( "document.pdf", ".pdf" ) );
		EXPECT_EQ( "archive.tar", removeSuffix( "archive.tar.gz", ".gz" ) );
		EXPECT_EQ( "/path/to/dir", removeSuffix( "/path/to/dir/", "/" ) );
		EXPECT_EQ( "test", removeSuffix( "test.cpp", ".cpp" ) );
	}

	TEST( StringUtilsSubstringExtraction, EdgeCases )
	{
		// Combining operations
		std::string_view path = "/root/path/to/file.txt";
		std::string_view filename = substringAfterLast( path, "/" );
		EXPECT_EQ( "file.txt", filename );
		std::string_view name = substringBeforeLast( filename, "." );
		EXPECT_EQ( "file", name );
		std::string_view ext = substringAfterLast( filename, "." );
		EXPECT_EQ( "txt", ext );

		// URL parsing example
		std::string_view url = "https://example.com/path/to/resource";
		std::string_view protocol = substringBefore( url, "://" );
		EXPECT_EQ( "https", protocol );
		std::string_view rest = substringAfter( url, "://" );
		EXPECT_EQ( "example.com/path/to/resource", rest );
		std::string_view domain = substringBefore( rest, "/" );
		EXPECT_EQ( "example.com", domain );

		// Email parsing
		std::string_view email = "user@example.com";
		std::string_view username = substringBefore( email, "@" );
		EXPECT_EQ( "user", username );
		std::string_view domain2 = substringAfter( email, "@" );
		EXPECT_EQ( "example.com", domain2 );

		// Prefix/suffix removal chain
		std::string_view str = "[[wrapped]]";
		std::string_view step1 = removePrefix( str, "[[" );
		EXPECT_EQ( "wrapped]]", step1 );
		std::string_view step2 = removeSuffix( step1, "]]" );
		EXPECT_EQ( "wrapped", step2 );
	}

	//----------------------------------------------
	// Character & String Removal
	//----------------------------------------------

	TEST( StringUtilsCharacterRemoval, RemoveAll_Character )
	{
		// Basic functionality
		EXPECT_EQ( "heo word", removeAll( "hello world", 'l' ) );
		EXPECT_EQ( "bnn", removeAll( "banana", 'a' ) );
		EXPECT_EQ( "heoword", removeAll( "helloworld", 'l' ) );

		// Character not present
		EXPECT_EQ( "hello", removeAll( "hello", 'x' ) );
		EXPECT_EQ( "world", removeAll( "world", 'z' ) );

		// All characters match
		EXPECT_EQ( "", removeAll( "aaa", 'a' ) );
		EXPECT_EQ( "", removeAll( "zzz", 'z' ) );

		// Empty string
		EXPECT_EQ( "", removeAll( "", 'a' ) );

		// Single character
		EXPECT_EQ( "", removeAll( "a", 'a' ) );
		EXPECT_EQ( "b", removeAll( "b", 'a' ) );

		// Whitespace removal
		EXPECT_EQ( "helloworld", removeAll( "hello world", ' ' ) );
		EXPECT_EQ( "helloworld", removeAll( "hello\t\tworld", '\t' ) );

		// Case sensitive
		EXPECT_EQ( "HeLLo", removeAll( "HeLLo", 'l' ) );
		EXPECT_EQ( "Heo", removeAll( "HeLLo", 'L' ) );

		// Special characters
		EXPECT_EQ( "helloworld", removeAll( "hello-world", '-' ) );
		EXPECT_EQ( "hello world", removeAll( "hello, world", ',' ) );
	}

	TEST( StringUtilsCharacterRemoval, RemoveAll_Substring )
	{
		// Basic functionality
		EXPECT_EQ( "heo word", removeAll( "hello world", "l" ) );
		EXPECT_EQ( " world", removeAll( "hello world", "hello" ) );
		EXPECT_EQ( "hello ", removeAll( "hello world", "world" ) );

		// Multi-character substring
		EXPECT_EQ( "file.gz", removeAll( "file.tar.gz", ".tar" ) );
		EXPECT_EQ( "helloworld", removeAll( "hello::world", "::" ) );
		EXPECT_EQ( "onetwothree", removeAll( "one::two::three", "::" ) );

		// Substring not present
		EXPECT_EQ( "hello", removeAll( "hello", "xyz" ) );
		EXPECT_EQ( "world", removeAll( "world", "foo" ) );

		// Empty substring
		EXPECT_EQ( "hello world", removeAll( "hello world", "" ) );

		// Empty string
		EXPECT_EQ( "", removeAll( "", "hello" ) );

		// Substring equals entire string
		EXPECT_EQ( "", removeAll( "hello", "hello" ) );

		// Substring longer than string
		EXPECT_EQ( "hi", removeAll( "hi", "hello" ) );

		// Multiple occurrences
		EXPECT_EQ( "123", removeAll( "a1a2a3", "a" ) );
		EXPECT_EQ( "filetxt", removeAll( "file...txt", "." ) );

		// Case sensitive
		EXPECT_EQ( "helloWorld", removeAll( "helloWorld", "world" ) );
		EXPECT_EQ( "hello", removeAll( "helloWorld", "World" ) );

		// Adjacent occurrences
		EXPECT_EQ( "text", removeAll( "te||xt", "||" ) );
		EXPECT_EQ( "text", removeAll( "||||text", "||" ) );

		// Real-world examples
		EXPECT_EQ( "HelloWorld", removeAll( "Hello World", " " ) );
		EXPECT_EQ( "pathtofile", removeAll( "//path//to//file", "//" ) );
	}

	TEST( StringUtilsCharacterRemoval, RemoveIf_Predicate )
	{
		// Remove digits
		EXPECT_EQ( "hello", removeIf( "hello123", isDigit ) );
		EXPECT_EQ( "test", removeIf( "t3e5s7t", isDigit ) );
		EXPECT_EQ( "", removeIf( "12345", isDigit ) );

		// Remove whitespace using predicate
		auto is_ws = []( char c ) { return isWhitespace( c ); };
		EXPECT_EQ( "helloworld", removeIf( "hello world", is_ws ) );
		EXPECT_EQ( "helloworld", removeIf( "hello\t\n\rworld", is_ws ) );

		// Remove vowels
		auto is_vowel = []( char c ) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; };
		EXPECT_EQ( "hll", removeIf( "hello", is_vowel ) );
		EXPECT_EQ( "wrld", removeIf( "world", is_vowel ) );

		// Remove non-alphanumeric
		auto is_non_alnum = []( char c ) { return !isAlphaNumeric( c ); };
		EXPECT_EQ( "hello123world", removeIf( "hello-123_world!", is_non_alnum ) );

		// Empty string
		EXPECT_EQ( "", removeIf( "", isDigit ) );

		// No matches
		EXPECT_EQ( "hello", removeIf( "hello", isDigit ) );
		EXPECT_EQ( "abc", removeIf( "abc", isDigit ) );

		// All match
		EXPECT_EQ( "", removeIf( "12345", isDigit ) );
		EXPECT_EQ( "", removeIf( "   ", is_ws ) );

		// Lambda with capture
		char target = 'x';
		auto is_target = [target]( char c ) { return c == target; };
		EXPECT_EQ( "hello", removeIf( "hexllo", is_target ) );
	}

	TEST( StringUtilsCharacterRemoval, RemoveWhitespace )
	{
		// Basic functionality
		EXPECT_EQ( "helloworld", removeWhitespace( "hello world" ) );
		EXPECT_EQ( "helloworld", removeWhitespace( "hello  world" ) );
		EXPECT_EQ( "helloworld", removeWhitespace( "  hello  world  " ) );

		// Various whitespace types
		EXPECT_EQ( "helloworld", removeWhitespace( "hello\tworld" ) );
		EXPECT_EQ( "helloworld", removeWhitespace( "hello\nworld" ) );
		EXPECT_EQ( "helloworld", removeWhitespace( "hello\rworld" ) );
		EXPECT_EQ( "helloworld", removeWhitespace( "hello\r\nworld" ) );
		EXPECT_EQ( "helloworld", removeWhitespace( "hello \t\n\r world" ) );

		// Empty string
		EXPECT_EQ( "", removeWhitespace( "" ) );

		// Only whitespace
		EXPECT_EQ( "", removeWhitespace( "   " ) );
		EXPECT_EQ( "", removeWhitespace( " \t\n\r " ) );

		// No whitespace
		EXPECT_EQ( "helloworld", removeWhitespace( "helloworld" ) );

		// Leading/trailing whitespace
		EXPECT_EQ( "hello", removeWhitespace( "  hello  " ) );
		EXPECT_EQ( "hello", removeWhitespace( "\t\nhello\r\n" ) );

		// Real-world examples
		EXPECT_EQ( "Hello,World!", removeWhitespace( "Hello, World!" ) );
		EXPECT_EQ( "192.168.1.1", removeWhitespace( "192.168.1.1" ) );
		EXPECT_EQ( "key=value", removeWhitespace( "key = value" ) );
	}

	TEST( StringUtilsCharacterRemoval, CollapseWhitespace )
	{
		// Basic functionality
		EXPECT_EQ( "hello world", collapseWhitespace( "hello  world" ) );
		EXPECT_EQ( "hello world", collapseWhitespace( "hello   world" ) );
		EXPECT_EQ( "hello world", collapseWhitespace( "  hello  world  " ) );

		// Various whitespace types
		EXPECT_EQ( "hello world", collapseWhitespace( "hello\tworld" ) );
		EXPECT_EQ( "hello world", collapseWhitespace( "hello\nworld" ) );
		EXPECT_EQ( "hello world", collapseWhitespace( "hello\r\nworld" ) );
		EXPECT_EQ( "hello world", collapseWhitespace( "hello \t\n\r world" ) );

		// Multiple words
		EXPECT_EQ( "one two three", collapseWhitespace( "one  two   three" ) );
		EXPECT_EQ( "one two three", collapseWhitespace( "  one   two   three  " ) );

		// Empty string
		EXPECT_EQ( "", collapseWhitespace( "" ) );

		// Only whitespace
		EXPECT_EQ( "", collapseWhitespace( "   " ) );
		EXPECT_EQ( "", collapseWhitespace( " \t\n\r " ) );

		// No whitespace
		EXPECT_EQ( "helloworld", collapseWhitespace( "helloworld" ) );

		// Single space already
		EXPECT_EQ( "hello world", collapseWhitespace( "hello world" ) );

		// Leading/trailing only
		EXPECT_EQ( "hello", collapseWhitespace( "  hello  " ) );
		EXPECT_EQ( "hello", collapseWhitespace( "\t\nhello\r\n" ) );

		// Real-world examples - normalizing text
		EXPECT_EQ( "This is a test", collapseWhitespace( "This   is\ta\ntest" ) );
		EXPECT_EQ( "Hello World", collapseWhitespace( "  Hello     World  " ) );
		EXPECT_EQ( "one two three", collapseWhitespace( "one\n\ntwo\t\tthree" ) );

		// Consecutive newlines and tabs
		EXPECT_EQ( "line1 line2 line3", collapseWhitespace( "line1\n\n\nline2\t\t\tline3" ) );
	}

	TEST( StringUtilsCharacterRemoval, EdgeCases )
	{
		// Combining operations
		std::string text = "  hello   world  123  ";
		std::string step1 = collapseWhitespace( text );
		EXPECT_EQ( "hello world 123", step1 );
		std::string step2 = removeIf( step1, isDigit );
		EXPECT_EQ( "hello world ", step2 );
		std::string_view step3 = trim( step2 );
		EXPECT_EQ( "hello world", step3 );

		// Chain character removal
		std::string input = "a1b2c3";
		std::string removed_digits = removeIf( input, isDigit );
		EXPECT_EQ( "abc", removed_digits );
		std::string removed_a = removeAll( removed_digits, 'a' );
		EXPECT_EQ( "bc", removed_a );

		// Empty results
		EXPECT_EQ( "", removeAll( "aaaa", 'a' ) );
		EXPECT_EQ( "", removeWhitespace( "   \t\n\r   " ) );
		EXPECT_EQ( "", collapseWhitespace( "   \t\n\r   " ) );

		// Single character strings
		EXPECT_EQ( "a", removeAll( "a", 'b' ) );
		EXPECT_EQ( "", removeAll( "a", 'a' ) );
		EXPECT_EQ( "a", removeWhitespace( "a" ) );
		EXPECT_EQ( "", removeWhitespace( " " ) );
	}

	//==========================================================================
	// Predicate-Based Operations
	//==========================================================================

	TEST( StringUtilsPredicateOperations, TrimStartIf )
	{
		// Trim digits from start
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( "abc", trimStartIf( "123abc", is_digit ) );
		EXPECT_EQ( "abc456", trimStartIf( "123abc456", is_digit ) );
		EXPECT_EQ( "abc", trimStartIf( "abc", is_digit ) );

		// Trim spaces (custom predicate)
		auto is_space = []( char c ) { return c == ' '; };
		EXPECT_EQ( "hello", trimStartIf( "   hello", is_space ) );
		EXPECT_EQ( "hello   ", trimStartIf( "   hello   ", is_space ) );

		// Trim vowels
		auto is_vowel = []( char c ) {
			return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
		};
		EXPECT_EQ( "xyz", trimStartIf( "aeiouxyz", is_vowel ) );

		// Edge cases
		EXPECT_EQ( "", trimStartIf( "", is_digit ) );
		EXPECT_EQ( "", trimStartIf( "12345", is_digit ) );
		EXPECT_EQ( "abc", trimStartIf( "abc", is_digit ) );

		// Using library predicates
		EXPECT_EQ( "hello123", trimStartIf( "   hello123", isWhitespace ) );
		EXPECT_EQ( "abc", trimStartIf( "123abc", isDigit ) );
	}

	TEST( StringUtilsPredicateOperations, TrimEndIf )
	{
		// Trim digits from end
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( "abc", trimEndIf( "abc123", is_digit ) );
		EXPECT_EQ( "123abc", trimEndIf( "123abc456", is_digit ) );
		EXPECT_EQ( "abc", trimEndIf( "abc", is_digit ) );

		// Trim spaces
		auto is_space = []( char c ) { return c == ' '; };
		EXPECT_EQ( "hello", trimEndIf( "hello   ", is_space ) );
		EXPECT_EQ( "   hello", trimEndIf( "   hello   ", is_space ) );

		// Trim punctuation
		auto is_punct = []( char c ) { return c == '.' || c == '!' || c == '?'; };
		EXPECT_EQ( "Hello", trimEndIf( "Hello...", is_punct ) );
		EXPECT_EQ( "End", trimEndIf( "End!?!", is_punct ) );

		// Edge cases
		EXPECT_EQ( "", trimEndIf( "", is_digit ) );
		EXPECT_EQ( "", trimEndIf( "12345", is_digit ) );
		EXPECT_EQ( "abc", trimEndIf( "abc", is_digit ) );

		// Using library predicates
		EXPECT_EQ( "hello123", trimEndIf( "hello123   ", isWhitespace ) );
		EXPECT_EQ( "abc", trimEndIf( "abc123", isDigit ) );
	}

	TEST( StringUtilsPredicateOperations, TrimIf )
	{
		// Trim digits from both ends
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( "abc", trimIf( "123abc456", is_digit ) );
		EXPECT_EQ( "abc", trimIf( "abc", is_digit ) );
		EXPECT_EQ( "", trimIf( "12345", is_digit ) );

		// Trim spaces
		auto is_space = []( char c ) { return c == ' '; };
		EXPECT_EQ( "hello", trimIf( "   hello   ", is_space ) );
		EXPECT_EQ( "hello world", trimIf( "  hello world  ", is_space ) );

		// Trim special characters
		auto is_special = []( char c ) { return c == '*' || c == '#' || c == '@'; };
		EXPECT_EQ( "text", trimIf( "**##text@@**", is_special ) );

		// Edge cases
		EXPECT_EQ( "", trimIf( "", is_digit ) );
		EXPECT_EQ( "", trimIf( "***", is_special ) );
		EXPECT_EQ( "abc", trimIf( "abc", is_digit ) );

		// Using library predicates
		EXPECT_EQ( "hello", trimIf( "   hello   ", isWhitespace ) );
		EXPECT_EQ( "abc", trimIf( "123abc456", isDigit ) );
		EXPECT_EQ( "123", trimIf( "abc123xyz", isAlpha ) );
	}

	TEST( StringUtilsPredicateOperations, CountIf )
	{
		// Count digits
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( 3, countIf( "abc123", is_digit ) );
		EXPECT_EQ( 5, countIf( "12345", is_digit ) );
		EXPECT_EQ( 0, countIf( "abcdef", is_digit ) );

		// Count vowels
		auto is_vowel = []( char c ) {
			char lower = ( c >= 'A' && c <= 'Z' ) ? c + 32 : c;
			return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
		};
		EXPECT_EQ( 2, countIf( "hello", is_vowel ) ); // e, o
		EXPECT_EQ( 5, countIf( "aeiou", is_vowel ) );
		EXPECT_EQ( 0, countIf( "xyz", is_vowel ) );

		// Count spaces
		auto is_space = []( char c ) { return c == ' '; };
		EXPECT_EQ( 2, countIf( "hello world test", is_space ) );
		EXPECT_EQ( 0, countIf( "hello", is_space ) );

		// Count uppercase
		auto is_upper = []( char c ) { return c >= 'A' && c <= 'Z'; };
		EXPECT_EQ( 2, countIf( "Hello World", is_upper ) ); // H, W
		EXPECT_EQ( 0, countIf( "hello", is_upper ) );

		// Edge cases
		EXPECT_EQ( 0, countIf( "", is_digit ) );
		EXPECT_EQ( 3, countIf( "123", is_digit ) );

		// Using library predicates
		EXPECT_EQ( 3, countIf( "abc123", isDigit ) );
		EXPECT_EQ( 3, countIf( "abc123", isAlpha ) );
		EXPECT_EQ( 6, countIf( "abc123", isAlphaNumeric ) );
		EXPECT_EQ( 4, countIf( "  \t\n", isWhitespace ) );
	}

	TEST( StringUtilsPredicateOperations, FindIf )
	{
		// Find first digit
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( 3, findIf( "abc123", is_digit ) );
		EXPECT_EQ( 0, findIf( "123abc", is_digit ) );
		EXPECT_EQ( std::string_view::npos, findIf( "abcdef", is_digit ) );

		// Find first vowel
		auto is_vowel = []( char c ) {
			char lower = ( c >= 'A' && c <= 'Z' ) ? c + 32 : c;
			return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
		};
		EXPECT_EQ( 1, findIf( "hello", is_vowel ) );
		EXPECT_EQ( 0, findIf( "apple", is_vowel ) );
		EXPECT_EQ( std::string_view::npos, findIf( "xyz", is_vowel ) );

		// Find first uppercase
		auto is_upper = []( char c ) { return c >= 'A' && c <= 'Z'; };
		EXPECT_EQ( 0, findIf( "Hello", is_upper ) );
		EXPECT_EQ( 6, findIf( "hello World", is_upper ) );
		EXPECT_EQ( std::string_view::npos, findIf( "hello", is_upper ) );

		// Edge cases
		EXPECT_EQ( std::string_view::npos, findIf( "", is_digit ) );
		EXPECT_EQ( 0, findIf( "1", is_digit ) );

		// Using library predicates
		EXPECT_EQ( 3, findIf( "abc123", isDigit ) );
		EXPECT_EQ( 0, findIf( "abc123", isAlpha ) );
		EXPECT_EQ( 0, findIf( "   hello", isWhitespace ) );
	}

	TEST( StringUtilsPredicateOperations, FindIfNot )
	{
		// Find first non-digit
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( 3, findIfNot( "123abc", is_digit ) );
		EXPECT_EQ( 0, findIfNot( "abc123", is_digit ) );
		EXPECT_EQ( std::string_view::npos, findIfNot( "12345", is_digit ) );

		// Find first non-space
		auto is_space = []( char c ) { return c == ' '; };
		EXPECT_EQ( 3, findIfNot( "   hello", is_space ) );
		EXPECT_EQ( 0, findIfNot( "hello", is_space ) );
		EXPECT_EQ( std::string_view::npos, findIfNot( "     ", is_space ) );

		// Find first non-vowel
		auto is_vowel = []( char c ) {
			char lower = ( c >= 'A' && c <= 'Z' ) ? c + 32 : c;
			return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
		};
		EXPECT_EQ( 0, findIfNot( "hello", is_vowel ) );
		EXPECT_EQ( 2, findIfNot( "aexyz", is_vowel ) );
		EXPECT_EQ( std::string_view::npos, findIfNot( "aeiou", is_vowel ) );

		// Edge cases
		EXPECT_EQ( std::string_view::npos, findIfNot( "", is_digit ) );
		EXPECT_EQ( std::string_view::npos, findIfNot( "1", is_digit ) );
		EXPECT_EQ( 0, findIfNot( "a", is_digit ) );

		// Using library predicates
		EXPECT_EQ( 0, findIfNot( "abc123", isDigit ) );
		EXPECT_EQ( 3, findIfNot( "123abc", isDigit ) );
		EXPECT_EQ( 3, findIfNot( "   hello", isWhitespace ) );
	}

	TEST( StringUtilsPredicateOperations, ReplaceIf )
	{
		// Replace digits with 'X'
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		EXPECT_EQ( "abcXXX", replaceIf( "abc123", is_digit, 'X' ) );
		EXPECT_EQ( "XXXXX", replaceIf( "12345", is_digit, 'X' ) );
		EXPECT_EQ( "abcdef", replaceIf( "abcdef", is_digit, 'X' ) );

		// Replace vowels with '*'
		auto is_vowel = []( char c ) {
			char lower = ( c >= 'A' && c <= 'Z' ) ? c + 32 : c;
			return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
		};
		EXPECT_EQ( "h*ll*", replaceIf( "hello", is_vowel, '*' ) );
		EXPECT_EQ( "*****", replaceIf( "aeiou", is_vowel, '*' ) );
		EXPECT_EQ( "xyz", replaceIf( "xyz", is_vowel, '*' ) );

		// Replace spaces with underscores
		auto is_space = []( char c ) { return c == ' '; };
		EXPECT_EQ( "hello_world", replaceIf( "hello world", is_space, '_' ) );
		EXPECT_EQ( "___", replaceIf( "   ", is_space, '_' ) );

		// Replace uppercase with lowercase 'x'
		auto is_upper = []( char c ) { return c >= 'A' && c <= 'Z'; };
		EXPECT_EQ( "xello xorld", replaceIf( "Hello World", is_upper, 'x' ) );

		// Edge cases
		EXPECT_EQ( "", replaceIf( "", is_digit, 'X' ) );
		EXPECT_EQ( "X", replaceIf( "1", is_digit, 'X' ) );
		EXPECT_EQ( "abc", replaceIf( "abc", is_digit, 'X' ) );

		// Using library predicates
		EXPECT_EQ( "abcXXX", replaceIf( "abc123", isDigit, 'X' ) );
		EXPECT_EQ( "___hello", replaceIf( "   hello", isWhitespace, '_' ) );
		EXPECT_EQ( "XXX123", replaceIf( "abc123", isAlpha, 'X' ) );
	}

	TEST( StringUtilsPredicateOperations, ComplexPredicates )
	{
		// Complex predicate: alphanumeric
		auto is_alnum = []( char c ) { return ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ); };

		EXPECT_EQ( "abc123", trimIf( "!!!abc123??", []( char c ) { return !( ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ); } ) );
		EXPECT_EQ( 6, countIf( "abc123!!!", is_alnum ) );
		EXPECT_EQ( "abc123___", replaceIf( "abc123!!!", []( char c ) { return c == '!'; }, '_' ) );

		// Predicate with capture
		char target = 'o';
		auto is_target = [target]( char c ) { return c == target; };
		EXPECT_EQ( 2, countIf( "hello world", is_target ) );
		EXPECT_EQ( 4, findIf( "hello world", is_target ) );

		// Multiple operations chained
		std::string text = "  123abc456  ";
		auto trimmed = trimIf( text, isWhitespace );
		auto digit_count = countIf( trimmed, isDigit );
		auto first_alpha = findIf( trimmed, isAlpha );
		auto replaced = replaceIf( trimmed, isDigit, '#' );

		EXPECT_EQ( "123abc456", trimmed );
		EXPECT_EQ( 6, digit_count );
		EXPECT_EQ( 3, first_alpha );
		EXPECT_EQ( "###abc###", replaced );
	}

	TEST( StringUtilsPredicateOperations, EdgeCasesAndRobustness )
	{
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		auto always_true = []( char ) { return true; };
		auto always_false = []( char ) { return false; };

		// Empty string
		EXPECT_EQ( "", trimIf( "", always_true ) );
		EXPECT_EQ( 0, countIf( "", always_true ) );
		EXPECT_EQ( std::string_view::npos, findIf( "", always_true ) );
		EXPECT_EQ( std::string_view::npos, findIfNot( "", always_false ) );
		EXPECT_EQ( "", replaceIf( "", always_true, 'X' ) );

		// Always true predicate (matches everything)
		EXPECT_EQ( "", trimIf( "test", always_true ) );
		EXPECT_EQ( 4, countIf( "test", always_true ) );
		EXPECT_EQ( 0, findIf( "test", always_true ) );
		EXPECT_EQ( std::string_view::npos, findIfNot( "test", always_true ) );
		EXPECT_EQ( "XXXX", replaceIf( "test", always_true, 'X' ) );

		// Always false predicate (matches nothing)
		EXPECT_EQ( "test", trimIf( "test", always_false ) );
		EXPECT_EQ( 0, countIf( "test", always_false ) );
		EXPECT_EQ( std::string_view::npos, findIf( "test", always_false ) );
		EXPECT_EQ( 0, findIfNot( "test", always_false ) );
		EXPECT_EQ( "test", replaceIf( "test", always_false, 'X' ) );

		// Single character strings
		EXPECT_EQ( "", trimIf( "1", is_digit ) );
		EXPECT_EQ( "a", trimIf( "a", is_digit ) );
		EXPECT_EQ( 1, countIf( "1", is_digit ) );
		EXPECT_EQ( 0, countIf( "a", is_digit ) );
	}

	//==========================================================================
	// URL Encoding/Decoding
	//==========================================================================

	TEST( StringUtilsURLEncoding, BasicEncoding )
	{
		// Unreserved characters should not be encoded
		EXPECT_EQ( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~",
			urlEncode( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~" ) );

		// Spaces
		EXPECT_EQ( "hello%20world", urlEncode( "hello world" ) );
		EXPECT_EQ( "%20%20%20", urlEncode( "   " ) );

		// Common special characters
		EXPECT_EQ( "hello%2Cworld", urlEncode( "hello,world" ) );
		EXPECT_EQ( "test%3Dvalue", urlEncode( "test=value" ) );
		EXPECT_EQ( "path%2Fto%2Ffile", urlEncode( "path/to/file" ) );
		EXPECT_EQ( "query%3Fname%26value", urlEncode( "query?name&value" ) );

		// Empty string
		EXPECT_EQ( "", urlEncode( "" ) );

		// Single characters
		EXPECT_EQ( "a", urlEncode( "a" ) );
		EXPECT_EQ( "%20", urlEncode( " " ) );
		EXPECT_EQ( "%2F", urlEncode( "/" ) );
	}

	TEST( StringUtilsURLEncoding, ReservedCharacters )
	{
		// Gen-delims (RFC 3986): : / ? # [ ] @
		EXPECT_EQ( "%3A", urlEncode( ":" ) );
		EXPECT_EQ( "%2F", urlEncode( "/" ) );
		EXPECT_EQ( "%3F", urlEncode( "?" ) );
		EXPECT_EQ( "%23", urlEncode( "#" ) );
		EXPECT_EQ( "%5B", urlEncode( "[" ) );
		EXPECT_EQ( "%5D", urlEncode( "]" ) );
		EXPECT_EQ( "%40", urlEncode( "@" ) );

		// Sub-delims (RFC 3986): ! $ & ' ( ) * + , ; =
		EXPECT_EQ( "%21", urlEncode( "!" ) );
		EXPECT_EQ( "%24", urlEncode( "$" ) );
		EXPECT_EQ( "%26", urlEncode( "&" ) );
		EXPECT_EQ( "%27", urlEncode( "'" ) );
		EXPECT_EQ( "%28", urlEncode( "(" ) );
		EXPECT_EQ( "%29", urlEncode( ")" ) );
		EXPECT_EQ( "%2A", urlEncode( "*" ) );
		EXPECT_EQ( "%2B", urlEncode( "+" ) );
		EXPECT_EQ( "%2C", urlEncode( "," ) );
		EXPECT_EQ( "%3B", urlEncode( ";" ) );
		EXPECT_EQ( "%3D", urlEncode( "=" ) );
	}

	TEST( StringUtilsURLEncoding, SpecialAndUnicodeCharacters )
	{
		// Control characters
		EXPECT_EQ( "%00", urlEncode( std::string( 1, '\0' ) ) );
		EXPECT_EQ( "%09", urlEncode( "\t" ) );
		EXPECT_EQ( "%0A", urlEncode( "\n" ) );
		EXPECT_EQ( "%0D", urlEncode( "\r" ) );

		// High-bit characters (would be UTF-8 encoded in real URLs)
		EXPECT_EQ( "%C3%A9", urlEncode( "é" ) );	// UTF-8: C3 A9
		EXPECT_EQ( "%E2%9C%93", urlEncode( "✓" ) ); // UTF-8: E2 9C 93

		// Special symbols
		EXPECT_EQ( "%25", urlEncode( "%" ) );
		EXPECT_EQ( "%22", urlEncode( "\"" ) );
		EXPECT_EQ( "%3C", urlEncode( "<" ) );
		EXPECT_EQ( "%3E", urlEncode( ">" ) );
		EXPECT_EQ( "%5C", urlEncode( "\\" ) );
		EXPECT_EQ( "%7C", urlEncode( "|" ) );
		EXPECT_EQ( "%7B", urlEncode( "{" ) );
		EXPECT_EQ( "%7D", urlEncode( "}" ) );
	}

	TEST( StringUtilsURLEncoding, RealWorldExamples )
	{
		// Email addresses
		EXPECT_EQ( "user%40example.com", urlEncode( "user@example.com" ) );
		EXPECT_EQ( "test.user%2Bfilter%40mail.com", urlEncode( "test.user+filter@mail.com" ) );

		// URLs
		EXPECT_EQ( "https%3A%2F%2Fexample.com%2Fpath%3Fquery%3Dvalue",
			urlEncode( "https://example.com/path?query=value" ) );

		// Filenames
		EXPECT_EQ( "my%20document%20%281%29.pdf", urlEncode( "my document (1).pdf" ) );

		// Search queries
		EXPECT_EQ( "C%2B%2B%20programming", urlEncode( "C++ programming" ) );
		EXPECT_EQ( "how%20to%20%22escape%22%20strings%3F", urlEncode( "how to \"escape\" strings?" ) );

		// Form data
		EXPECT_EQ( "name%3DJohn%26age%3D30", urlEncode( "name=John&age=30" ) );
	}

	TEST( StringUtilsURLDecoding, BasicDecoding )
	{
		// Unreserved characters
		EXPECT_EQ( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~",
			urlDecode( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~" ) );

		// Spaces
		EXPECT_EQ( "hello world", urlDecode( "hello%20world" ) );
		EXPECT_EQ( "   ", urlDecode( "%20%20%20" ) );

		// Common special characters
		EXPECT_EQ( "hello,world", urlDecode( "hello%2Cworld" ) );
		EXPECT_EQ( "test=value", urlDecode( "test%3Dvalue" ) );
		EXPECT_EQ( "path/to/file", urlDecode( "path%2Fto%2Ffile" ) );
		EXPECT_EQ( "query?name&value", urlDecode( "query%3Fname%26value" ) );

		// Empty string
		EXPECT_EQ( "", urlDecode( "" ) );

		// Mixed encoded and non-encoded
		EXPECT_EQ( "hello world test", urlDecode( "hello%20world%20test" ) );
		EXPECT_EQ( "test value", urlDecode( "test%20value" ) );
	}

	TEST( StringUtilsURLDecoding, CaseInsensitiveHex )
	{
		// Uppercase hex
		EXPECT_EQ( "hello world", urlDecode( "hello%20world" ) );

		// Lowercase hex
		EXPECT_EQ( "hello world", urlDecode( "hello%20world" ) );

		// Mixed case hex
		EXPECT_EQ( "test:value", urlDecode( "test%3avalue" ) );
		EXPECT_EQ( "test:value", urlDecode( "test%3Avalue" ) );
		EXPECT_EQ( "café", urlDecode( "caf%c3%a9" ) );
		EXPECT_EQ( "café", urlDecode( "caf%C3%A9" ) );
	}

	TEST( StringUtilsURLDecoding, SpecialCharacters )
	{
		// Reserved characters
		EXPECT_EQ( ":", urlDecode( "%3A" ) );
		EXPECT_EQ( "/", urlDecode( "%2F" ) );
		EXPECT_EQ( "?", urlDecode( "%3F" ) );
		EXPECT_EQ( "#", urlDecode( "%23" ) );
		EXPECT_EQ( "@", urlDecode( "%40" ) );
		EXPECT_EQ( "&", urlDecode( "%26" ) );
		EXPECT_EQ( "=", urlDecode( "%3D" ) );

		// Control characters
		EXPECT_EQ( std::string( 1, '\0' ), urlDecode( "%00" ) );
		EXPECT_EQ( "\t", urlDecode( "%09" ) );
		EXPECT_EQ( "\n", urlDecode( "%0A" ) );
		EXPECT_EQ( "\r", urlDecode( "%0D" ) );

		// UTF-8 encoded characters
		EXPECT_EQ( "é", urlDecode( "%C3%A9" ) );
		EXPECT_EQ( "✓", urlDecode( "%E2%9C%93" ) );

		// Special symbols
		EXPECT_EQ( "%", urlDecode( "%25" ) );
		EXPECT_EQ( "\"", urlDecode( "%22" ) );
		EXPECT_EQ( "<", urlDecode( "%3C" ) );
		EXPECT_EQ( ">", urlDecode( "%3E" ) );
	}

	TEST( StringUtilsURLDecoding, RealWorldExamples )
	{
		// Email addresses
		EXPECT_EQ( "user@example.com", urlDecode( "user%40example.com" ) );
		EXPECT_EQ( "test.user+filter@mail.com", urlDecode( "test.user%2Bfilter%40mail.com" ) );

		// URLs
		EXPECT_EQ( "https://example.com/path?query=value",
			urlDecode( "https%3A%2F%2Fexample.com%2Fpath%3Fquery%3Dvalue" ) );

		// Filenames
		EXPECT_EQ( "my document (1).pdf", urlDecode( "my%20document%20%281%29.pdf" ) );

		// Search queries
		EXPECT_EQ( "C++ programming", urlDecode( "C%2B%2B%20programming" ) );
		EXPECT_EQ( "how to \"escape\" strings?", urlDecode( "how%20to%20%22escape%22%20strings%3F" ) );
	}

	TEST( StringUtilsURLDecoding, MalformedInput )
	{
		// Invalid: % at end
		EXPECT_EQ( "", urlDecode( "test%" ) );

		// Invalid: % with only one hex digit
		EXPECT_EQ( "", urlDecode( "test%2" ) );

		// Invalid: % with non-hex characters
		EXPECT_EQ( "", urlDecode( "test%GG" ) );
		EXPECT_EQ( "", urlDecode( "test%ZZ" ) );
		EXPECT_EQ( "", urlDecode( "test%2X" ) );
		EXPECT_EQ( "", urlDecode( "test%X2" ) );

		// Invalid: % in middle with bad hex
		EXPECT_EQ( "", urlDecode( "hello%2Xworld" ) );

		// Invalid: incomplete encoding
		EXPECT_EQ( "", urlDecode( "test%0" ) );
	}

	TEST( StringUtilsURLEncoding, RoundTripEncoding )
	{
		// Test that encode/decode round-trips correctly
		std::vector<std::string> test_strings = {
			"hello world",
			"test@example.com",
			"C++ programming",
			"path/to/file.txt",
			"query?name=value&id=123",
			"special !@#$%^&*()_+-=[]{}|;:',.<>?/",
			"unicode: café ñoël 日本語",
			"mixed ABCabc123-._~!@#",
			"",
			" ",
			"a",
			"https://example.com:8080/path?query=value#fragment" };

		for ( const auto& original : test_strings )
		{
			std::string encoded = urlEncode( original );
			std::string decoded = urlDecode( encoded );
			EXPECT_EQ( original, decoded ) << "Failed for: " << original;
		}
	}

	TEST( StringUtilsURLEncoding, EdgeCases )
	{
		// All percent signs
		EXPECT_EQ( "%25%25%25", urlEncode( "%%%" ) );
		EXPECT_EQ( "%%%", urlDecode( "%25%25%25" ) );

		// Long strings
		std::string long_unreserved( 1000, 'a' );
		EXPECT_EQ( long_unreserved, urlEncode( long_unreserved ) );
		EXPECT_EQ( long_unreserved, urlDecode( long_unreserved ) );

		std::string long_encoded( 1000, ' ' );
		std::string expected_encoded( 3000, '\0' );
		for ( std::size_t i = 0; i < 1000; ++i )
		{
			expected_encoded[i * 3] = '%';
			expected_encoded[i * 3 + 1] = '2';
			expected_encoded[i * 3 + 2] = '0';
		}
		EXPECT_EQ( expected_encoded, urlEncode( long_encoded ) );

		// All bytes
		for ( int i = 0; i < 256; ++i )
		{
			std::string test( 1, static_cast<char>( i ) );
			std::string encoded = urlEncode( test );
			std::string decoded = urlDecode( encoded );
			EXPECT_EQ( test, decoded ) << "Failed for byte: " << i;
		}
	}

	//==========================================================================
	// JSON Escape/Unescape
	//==========================================================================

	TEST( StringUtilsJSONEscape, BasicEscaping )
	{
		// No escaping needed
		EXPECT_EQ( "hello world", jsonEscape( "hello world" ) );
		EXPECT_EQ( "abc123", jsonEscape( "abc123" ) );
		EXPECT_EQ( "", jsonEscape( "" ) );

		// Quote escaping
		EXPECT_EQ( "\\\"quoted\\\"", jsonEscape( "\"quoted\"" ) );
		EXPECT_EQ( "say \\\"hello\\\"", jsonEscape( "say \"hello\"" ) );

		// Backslash escaping
		EXPECT_EQ( "\\\\", jsonEscape( "\\" ) );
		EXPECT_EQ( "path\\\\to\\\\file", jsonEscape( "path\\to\\file" ) );

		// Forward slash escaping
		EXPECT_EQ( "path\\/to\\/file", jsonEscape( "path/to/file" ) );
	}

	TEST( StringUtilsJSONEscape, ControlCharacters )
	{
		// Standard escape sequences
		EXPECT_EQ( "\\b", jsonEscape( "\b" ) ); // backspace
		EXPECT_EQ( "\\f", jsonEscape( "\f" ) ); // form feed
		EXPECT_EQ( "\\n", jsonEscape( "\n" ) ); // newline
		EXPECT_EQ( "\\r", jsonEscape( "\r" ) ); // carriage return
		EXPECT_EQ( "\\t", jsonEscape( "\t" ) ); // tab

		// Multiple control characters
		EXPECT_EQ( "line1\\nline2", jsonEscape( "line1\nline2" ) );
		EXPECT_EQ( "col1\\tcol2", jsonEscape( "col1\tcol2" ) );
		EXPECT_EQ( "\\r\\n", jsonEscape( "\r\n" ) );

		// Other control characters (escaped as \uXXXX)
		EXPECT_EQ( "\\u0000", jsonEscape( std::string( 1, '\0' ) ) );
		EXPECT_EQ( "\\u0001", jsonEscape( "\x01" ) );
		EXPECT_EQ( "\\u001F", jsonEscape( "\x1F" ) );
	}

	TEST( StringUtilsJSONEscape, MixedContent )
	{
		// Mixed special characters
		EXPECT_EQ( "line1\\nline2\\tvalue", jsonEscape( "line1\nline2\tvalue" ) );
		EXPECT_EQ( "\\\"key\\\": \\\"value\\\"", jsonEscape( "\"key\": \"value\"" ) );
		EXPECT_EQ( "path\\\\file\\nend", jsonEscape( "path\\file\nend" ) );

		// Real JSON-like content
		EXPECT_EQ( "{\\\"name\\\": \\\"John\\\"}", jsonEscape( "{\"name\": \"John\"}" ) );
	}

	TEST( StringUtilsJSONUnescape, BasicUnescaping )
	{
		// No unescaping needed
		EXPECT_EQ( "hello world", jsonUnescape( "hello world" ) );
		EXPECT_EQ( "abc123", jsonUnescape( "abc123" ) );
		EXPECT_EQ( "", jsonUnescape( "" ) );

		// Quote unescaping
		EXPECT_EQ( "\"quoted\"", jsonUnescape( "\\\"quoted\\\"" ) );
		EXPECT_EQ( "say \"hello\"", jsonUnescape( "say \\\"hello\\\"" ) );

		// Backslash unescaping
		EXPECT_EQ( "\\", jsonUnescape( "\\\\" ) );
		EXPECT_EQ( "path\\to\\file", jsonUnescape( "path\\\\to\\\\file" ) );

		// Forward slash unescaping
		EXPECT_EQ( "path/to/file", jsonUnescape( "path\\/to\\/file" ) );
	}

	TEST( StringUtilsJSONUnescape, ControlCharacters )
	{
		// Standard escape sequences
		EXPECT_EQ( "\b", jsonUnescape( "\\b" ) );
		EXPECT_EQ( "\f", jsonUnescape( "\\f" ) );
		EXPECT_EQ( "\n", jsonUnescape( "\\n" ) );
		EXPECT_EQ( "\r", jsonUnescape( "\\r" ) );
		EXPECT_EQ( "\t", jsonUnescape( "\\t" ) );

		// Multiple control characters
		EXPECT_EQ( "line1\nline2", jsonUnescape( "line1\\nline2" ) );
		EXPECT_EQ( "col1\tcol2", jsonUnescape( "col1\\tcol2" ) );
		EXPECT_EQ( "\r\n", jsonUnescape( "\\r\\n" ) );
	}

	TEST( StringUtilsJSONUnescape, UnicodeEscapes )
	{
		// ASCII characters via Unicode
		EXPECT_EQ( "A", jsonUnescape( "\\u0041" ) );
		EXPECT_EQ( "z", jsonUnescape( "\\u007A" ) );
		EXPECT_EQ( "0", jsonUnescape( "\\u0030" ) );

		// Control characters via Unicode
		EXPECT_EQ( std::string( 1, '\0' ), jsonUnescape( "\\u0000" ) );
		EXPECT_EQ( "\x01", jsonUnescape( "\\u0001" ) );
		EXPECT_EQ( "\x1F", jsonUnescape( "\\u001F" ) );

		// Latin-1 supplement (2-byte UTF-8)
		EXPECT_EQ( "é", jsonUnescape( "\\u00E9" ) ); // U+00E9
		EXPECT_EQ( "ñ", jsonUnescape( "\\u00F1" ) ); // U+00F1
		EXPECT_EQ( "ü", jsonUnescape( "\\u00FC" ) ); // U+00FC

		// BMP characters (3-byte UTF-8)
		EXPECT_EQ( "€", jsonUnescape( "\\u20AC" ) );  // U+20AC Euro sign
		EXPECT_EQ( "™", jsonUnescape( "\\u2122" ) );  // U+2122 Trademark
		EXPECT_EQ( "→", jsonUnescape( "\\u2192" ) );  // U+2192 Right arrow
		EXPECT_EQ( "中", jsonUnescape( "\\u4E2D" ) ); // U+4E2D Chinese character

		// Mixed
		EXPECT_EQ( "café", jsonUnescape( "caf\\u00E9" ) );
		EXPECT_EQ( "hello→world", jsonUnescape( "hello\\u2192world" ) );
	}

	TEST( StringUtilsJSONUnescape, MixedContent )
	{
		// Mixed special characters
		EXPECT_EQ( "line1\nline2\tvalue", jsonUnescape( "line1\\nline2\\tvalue" ) );
		EXPECT_EQ( "\"key\": \"value\"", jsonUnescape( "\\\"key\\\": \\\"value\\\"" ) );
		EXPECT_EQ( "path\\file\nend", jsonUnescape( "path\\\\file\\nend" ) );

		// Real JSON-like content
		EXPECT_EQ( "{\"name\": \"John\"}", jsonUnescape( "{\\\"name\\\": \\\"John\\\"}" ) );
	}

	TEST( StringUtilsJSONUnescape, MalformedInput )
	{
		// Invalid: backslash at end
		EXPECT_EQ( "", jsonUnescape( "test\\" ) );

		// Invalid: unknown escape sequence
		EXPECT_EQ( "", jsonUnescape( "\\x" ) );
		EXPECT_EQ( "", jsonUnescape( "\\q" ) );

		// Invalid: incomplete Unicode escape
		EXPECT_EQ( "", jsonUnescape( "\\u" ) );
		EXPECT_EQ( "", jsonUnescape( "\\u0" ) );
		EXPECT_EQ( "", jsonUnescape( "\\u00" ) );
		EXPECT_EQ( "", jsonUnescape( "\\u000" ) );

		// Invalid: non-hex in Unicode escape
		EXPECT_EQ( "", jsonUnescape( "\\u00GG" ) );
		EXPECT_EQ( "", jsonUnescape( "\\uXXXX" ) );
		EXPECT_EQ( "", jsonUnescape( "\\u12ZZ" ) );
	}

	TEST( StringUtilsJSONEscape, RoundTripEscaping )
	{
		// Test that escape/unescape round-trips correctly
		std::vector<std::string> test_strings = {
			"hello world",
			"\"quoted\"",
			"path\\to\\file",
			"line1\nline2\ttab",
			"{\"key\": \"value\"}",
			"control: \b\f\n\r\t",
			std::string( 1, '\0' ) + "null char",
			"unicode: café ñoël 中文",
			"mixed \n\t\"test\"\\ end",
			"",
			"a",
			"special: !@#$%^&*()",
			"\x01\x02\x1F" // control chars
		};

		for ( const auto& original : test_strings )
		{
			std::string escaped = jsonEscape( original );
			std::string unescaped = jsonUnescape( escaped );
			EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
		}
	}

	TEST( StringUtilsJSONEscape, RealWorldExamples )
	{
		// JSON object
		std::string jsonObj = R"({"name":"John","age":30})";
		std::string escaped = jsonEscape( jsonObj );
		EXPECT_EQ( "{\\\"name\\\":\\\"John\\\",\\\"age\\\":30}", escaped );
		EXPECT_EQ( jsonObj, jsonUnescape( escaped ) );

		// Multiline text
		std::string multiline = "line1\nline2\nline3";
		escaped = jsonEscape( multiline );
		EXPECT_EQ( "line1\\nline2\\nline3", escaped );
		EXPECT_EQ( multiline, jsonUnescape( escaped ) );

		// Error message with quotes
		std::string error = "Error: \"file not found\"";
		escaped = jsonEscape( error );
		EXPECT_EQ( "Error: \\\"file not found\\\"", escaped );
		EXPECT_EQ( error, jsonUnescape( escaped ) );

		// Path with backslashes
		std::string path = "C:\\Users\\John\\Documents";
		escaped = jsonEscape( path );
		EXPECT_EQ( "C:\\\\Users\\\\John\\\\Documents", escaped );
		EXPECT_EQ( path, jsonUnescape( escaped ) );
	}

	TEST( StringUtilsJSONEscape, EdgeCases )
	{
		// All control characters
		for ( int i = 0; i < 32; ++i )
		{
			std::string test( 1, static_cast<char>( i ) );
			std::string escaped = jsonEscape( test );
			std::string unescaped = jsonUnescape( escaped );
			EXPECT_EQ( test, unescaped ) << "Failed for control char: " << i;
		}

		// All printable ASCII
		for ( int i = 32; i < 127; ++i )
		{
			std::string test( 1, static_cast<char>( i ) );
			std::string escaped = jsonEscape( test );
			std::string unescaped = jsonUnescape( escaped );
			EXPECT_EQ( test, unescaped ) << "Failed for ASCII: " << i;
		}

		// Long strings
		std::string long_text( 1000, 'a' );
		EXPECT_EQ( long_text, jsonUnescape( jsonEscape( long_text ) ) );

		std::string long_newlines( 1000, '\n' );
		std::string escaped_newlines = jsonEscape( long_newlines );
		EXPECT_EQ( long_newlines, jsonUnescape( escaped_newlines ) );
	}

	//==========================================================================
	// XML/HTML Escape/Unescape
	//==========================================================================

	TEST( StringUtilsXMLEscape, BasicEscaping )
	{
		// No escaping needed
		EXPECT_EQ( "hello world", xmlEscape( "hello world" ) );
		EXPECT_EQ( "abc123", xmlEscape( "abc123" ) );
		EXPECT_EQ( "", xmlEscape( "" ) );

		// Ampersand escaping
		EXPECT_EQ( "AT&amp;T", xmlEscape( "AT&T" ) );
		EXPECT_EQ( "Tom &amp; Jerry", xmlEscape( "Tom & Jerry" ) );

		// Less-than escaping
		EXPECT_EQ( "a &lt; b", xmlEscape( "a < b" ) );
		EXPECT_EQ( "&lt;tag&gt;", xmlEscape( "<tag>" ) );

		// Greater-than escaping
		EXPECT_EQ( "a &gt; b", xmlEscape( "a > b" ) );

		// Quote escaping
		EXPECT_EQ( "&quot;quoted&quot;", xmlEscape( "\"quoted\"" ) );
		EXPECT_EQ( "say &quot;hello&quot;", xmlEscape( "say \"hello\"" ) );

		// Apostrophe escaping
		EXPECT_EQ( "it&apos;s", xmlEscape( "it's" ) );
		EXPECT_EQ( "&apos;single&apos;", xmlEscape( "'single'" ) );
	}

	TEST( StringUtilsXMLEscape, MixedContent )
	{
		// Multiple special characters
		EXPECT_EQ( "&lt;tag attr=&quot;value&quot;&gt;", xmlEscape( "<tag attr=\"value\">" ) );
		EXPECT_EQ( "A &amp; B &lt; C &gt; D", xmlEscape( "A & B < C > D" ) );
		EXPECT_EQ( "&apos;It&apos;s &quot;fine&quot;&apos;", xmlEscape( "'It's \"fine\"'" ) );

		// Real XML-like content
		EXPECT_EQ( "&lt;p&gt;Hello &amp; goodbye&lt;/p&gt;", xmlEscape( "<p>Hello & goodbye</p>" ) );
	}

	TEST( StringUtilsXMLEscape, RealWorldExamples )
	{
		// XML element
		std::string xml = "<name>John & Jane</name>";
		EXPECT_EQ( "&lt;name&gt;John &amp; Jane&lt;/name&gt;", xmlEscape( xml ) );

		// HTML with quotes
		std::string html = "<a href=\"page.html\">Link</a>";
		EXPECT_EQ( "&lt;a href=&quot;page.html&quot;&gt;Link&lt;/a&gt;", xmlEscape( html ) );

		// SQL-like content
		std::string sql = "SELECT * FROM table WHERE x > 5 AND y < 10";
		EXPECT_EQ( "SELECT * FROM table WHERE x &gt; 5 AND y &lt; 10", xmlEscape( sql ) );
	}

	TEST( StringUtilsXMLUnescape, BasicUnescaping )
	{
		// No unescaping needed
		EXPECT_EQ( "hello world", xmlUnescape( "hello world" ) );
		EXPECT_EQ( "abc123", xmlUnescape( "abc123" ) );
		EXPECT_EQ( "", xmlUnescape( "" ) );

		// Ampersand unescaping
		EXPECT_EQ( "AT&T", xmlUnescape( "AT&amp;T" ) );
		EXPECT_EQ( "Tom & Jerry", xmlUnescape( "Tom &amp; Jerry" ) );

		// Less-than unescaping
		EXPECT_EQ( "a < b", xmlUnescape( "a &lt; b" ) );
		EXPECT_EQ( "<tag>", xmlUnescape( "&lt;tag&gt;" ) );

		// Greater-than unescaping
		EXPECT_EQ( "a > b", xmlUnescape( "a &gt; b" ) );

		// Quote unescaping
		EXPECT_EQ( "\"quoted\"", xmlUnescape( "&quot;quoted&quot;" ) );
		EXPECT_EQ( "say \"hello\"", xmlUnescape( "say &quot;hello&quot;" ) );

		// Apostrophe unescaping
		EXPECT_EQ( "it's", xmlUnescape( "it&apos;s" ) );
		EXPECT_EQ( "'single'", xmlUnescape( "&apos;single&apos;" ) );
	}

	TEST( StringUtilsXMLUnescape, NumericEntities )
	{
		// Decimal numeric character references
		EXPECT_EQ( "A", xmlUnescape( "&#65;" ) );	// ASCII 'A'
		EXPECT_EQ( "0", xmlUnescape( "&#48;" ) );	// ASCII '0'
		EXPECT_EQ( " ", xmlUnescape( "&#32;" ) );	// Space
		EXPECT_EQ( "é", xmlUnescape( "&#233;" ) );	// Latin small letter e with acute
		EXPECT_EQ( "©", xmlUnescape( "&#169;" ) );	// Copyright sign
		EXPECT_EQ( "€", xmlUnescape( "&#8364;" ) ); // Euro sign

		// Hexadecimal numeric character references
		EXPECT_EQ( "A", xmlUnescape( "&#x41;" ) );	  // ASCII 'A'
		EXPECT_EQ( "0", xmlUnescape( "&#x30;" ) );	  // ASCII '0'
		EXPECT_EQ( " ", xmlUnescape( "&#x20;" ) );	  // Space
		EXPECT_EQ( "é", xmlUnescape( "&#xE9;" ) );	  // e-acute (lowercase hex)
		EXPECT_EQ( "é", xmlUnescape( "&#xE9;" ) );	  // e-acute (uppercase hex)
		EXPECT_EQ( "©", xmlUnescape( "&#xA9;" ) );	  // Copyright
		EXPECT_EQ( "€", xmlUnescape( "&#x20AC;" ) );  // Euro sign
		EXPECT_EQ( "中", xmlUnescape( "&#x4E2D;" ) ); // Chinese character

		// Mixed in text
		EXPECT_EQ( "Price: €10", xmlUnescape( "Price: &#8364;10" ) );
		EXPECT_EQ( "Copyright © 2025", xmlUnescape( "Copyright &#169; 2025" ) );
	}

	TEST( StringUtilsXMLUnescape, MixedContent )
	{
		// Multiple entities
		EXPECT_EQ( "<tag attr=\"value\">", xmlUnescape( "&lt;tag attr=&quot;value&quot;&gt;" ) );
		EXPECT_EQ( "A & B < C > D", xmlUnescape( "A &amp; B &lt; C &gt; D" ) );
		EXPECT_EQ( "'It's \"fine\"'", xmlUnescape( "&apos;It&apos;s &quot;fine&quot;&apos;" ) );

		// Real XML-like content
		EXPECT_EQ( "<p>Hello & goodbye</p>", xmlUnescape( "&lt;p&gt;Hello &amp; goodbye&lt;/p&gt;" ) );

		// Mix of entities and numeric references
		EXPECT_EQ( "< & >", xmlUnescape( "&lt; &#38; &gt;" ) );
		EXPECT_EQ( "café", xmlUnescape( "caf&#233;" ) );
	}

	TEST( StringUtilsXMLUnescape, MalformedInput )
	{
		// Invalid: ampersand without semicolon
		EXPECT_EQ( "", xmlUnescape( "test & more" ) );
		EXPECT_EQ( "", xmlUnescape( "test &amp more" ) );

		// Invalid: unknown entity
		EXPECT_EQ( "", xmlUnescape( "&unknown;" ) );
		EXPECT_EQ( "", xmlUnescape( "&xyz;" ) );

		// Invalid: incomplete entity
		EXPECT_EQ( "", xmlUnescape( "&" ) );
		EXPECT_EQ( "", xmlUnescape( "&a" ) );

		// Invalid: malformed numeric entity
		EXPECT_EQ( "", xmlUnescape( "&#;" ) );
		EXPECT_EQ( "", xmlUnescape( "&#x;" ) );
		EXPECT_EQ( "", xmlUnescape( "&#xGG;" ) );
		EXPECT_EQ( "", xmlUnescape( "&#xyz;" ) );

		// Invalid: codepoint out of range
		EXPECT_EQ( "", xmlUnescape( "&#x110000;" ) ); // Beyond valid Unicode range
	}

	TEST( StringUtilsXMLEscape, RoundTripEscaping )
	{
		// Test that escape/unescape round-trips correctly
		std::vector<std::string> test_strings = {
			"hello world",
			"<tag>",
			"AT&T",
			"a < b > c",
			"\"quoted\" and 'apostrophe'",
			"<p>Text & more</p>",
			"<a href=\"link.html\">Click</a>",
			"",
			"a",
			"Tom & Jerry's \"show\"",
			"x < y && y > z" };

		for ( const auto& original : test_strings )
		{
			std::string escaped = xmlEscape( original );
			std::string unescaped = xmlUnescape( escaped );
			EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
		}
	}

	TEST( StringUtilsXMLEscape, RoundTripWithEntities )
	{
		// XML document fragment
		std::string xmlFrag = "<person name=\"John & Jane\">Data</person>";
		std::string escaped = xmlEscape( xmlFrag );
		EXPECT_EQ( "&lt;person name=&quot;John &amp; Jane&quot;&gt;Data&lt;/person&gt;", escaped );
		EXPECT_EQ( xmlFrag, xmlUnescape( escaped ) );

		// HTML attribute
		std::string html = "<img src=\"image.png\" alt=\"A > B\">";
		escaped = xmlEscape( html );
		EXPECT_EQ( "&lt;img src=&quot;image.png&quot; alt=&quot;A &gt; B&quot;&gt;", escaped );
		EXPECT_EQ( html, xmlUnescape( escaped ) );

		// Text with special chars
		std::string text = "R&D's result: x < 5 & y > 3";
		escaped = xmlEscape( text );
		EXPECT_EQ( "R&amp;D&apos;s result: x &lt; 5 &amp; y &gt; 3", escaped );
		EXPECT_EQ( text, xmlUnescape( escaped ) );
	}

	TEST( StringUtilsXMLEscape, EdgeCases )
	{
		// All special characters
		EXPECT_EQ( "&amp;&lt;&gt;&quot;&apos;", xmlEscape( "&<>\"'" ) );
		EXPECT_EQ( "&<>\"'", xmlUnescape( "&amp;&lt;&gt;&quot;&apos;" ) );

		// Consecutive special chars
		EXPECT_EQ( "&amp;&amp;&amp;", xmlEscape( "&&&" ) );
		EXPECT_EQ( "&lt;&lt;&lt;", xmlEscape( "<<<" ) );

		// Long strings
		std::string long_text( 1000, 'a' );
		EXPECT_EQ( long_text, xmlUnescape( xmlEscape( long_text ) ) );

		std::string long_ampersands( 1000, '&' );
		std::string escaped_ampersands = xmlEscape( long_ampersands );
		EXPECT_EQ( long_ampersands, xmlUnescape( escaped_ampersands ) );

		// Unicode characters (should pass through unchanged)
		std::string unicode = "café ñoël €10 中文";
		EXPECT_EQ( unicode, xmlEscape( unicode ) );

		// Mix with numeric entities
		EXPECT_EQ( "café", xmlUnescape( "caf&#xE9;" ) );
		EXPECT_EQ( "€", xmlUnescape( "&#x20AC;" ) );
	}

	//==========================================================================
	// C/C++ Escape/Unescape
	//==========================================================================

	TEST( StringUtilsCppEscape, BasicEscaping )
	{
		// No escaping needed
		EXPECT_EQ( "hello world", cppEscape( "hello world" ) );
		EXPECT_EQ( "abc123", cppEscape( "abc123" ) );
		EXPECT_EQ( "", cppEscape( "" ) );

		// Newline
		EXPECT_EQ( "line1\\nline2", cppEscape( "line1\nline2" ) );

		// Tab
		EXPECT_EQ( "col1\\tcol2", cppEscape( "col1\tcol2" ) );

		// Carriage return
		EXPECT_EQ( "text\\rmore", cppEscape( "text\rmore" ) );

		// Backslash
		EXPECT_EQ( "path\\\\to\\\\file", cppEscape( "path\\to\\file" ) );

		// Double quote
		EXPECT_EQ( "say \\\"hello\\\"", cppEscape( "say \"hello\"" ) );

		// Single quote
		EXPECT_EQ( "it\\'s", cppEscape( "it's" ) );

		// Null character
		EXPECT_EQ( "null\\0char", cppEscape( std::string( "null\0char", 9 ) ) );
	}

	TEST( StringUtilsCppEscape, ControlCharacters )
	{
		// Standard escape sequences
		EXPECT_EQ( "\\b", cppEscape( "\b" ) ); // backspace
		EXPECT_EQ( "\\f", cppEscape( "\f" ) ); // form feed
		EXPECT_EQ( "\\v", cppEscape( "\v" ) ); // vertical tab
		EXPECT_EQ( "\\a", cppEscape( "\a" ) ); // alert (bell)

		// Other control characters (as \xHH)
		EXPECT_EQ( "\\x01", cppEscape( "\x01" ) );
		EXPECT_EQ( "\\x1f", cppEscape( "\x1F" ) );
		EXPECT_EQ( "\\x7f", cppEscape( "\x7F" ) ); // DEL character
	}

	TEST( StringUtilsCppEscape, MixedContent )
	{
		// Multiple escape sequences
		EXPECT_EQ( "line1\\nline2\\ttab", cppEscape( "line1\nline2\ttab" ) );
		EXPECT_EQ( "path\\\\file\\nend", cppEscape( "path\\file\nend" ) );
		EXPECT_EQ( "\\\"quoted\\\" text", cppEscape( "\"quoted\" text" ) );

		// Mix of printable and control chars
		EXPECT_EQ( "hello\\nworld\\t!", cppEscape( "hello\nworld\t!" ) );
	}

	TEST( StringUtilsCppUnescape, BasicUnescaping )
	{
		// No unescaping needed
		EXPECT_EQ( "hello world", cppUnescape( "hello world" ) );
		EXPECT_EQ( "abc123", cppUnescape( "abc123" ) );
		EXPECT_EQ( "", cppUnescape( "" ) );

		// Newline
		EXPECT_EQ( "line1\nline2", cppUnescape( "line1\\nline2" ) );

		// Tab
		EXPECT_EQ( "col1\tcol2", cppUnescape( "col1\\tcol2" ) );

		// Carriage return
		EXPECT_EQ( "text\rmore", cppUnescape( "text\\rmore" ) );

		// Backslash
		EXPECT_EQ( "path\\to\\file", cppUnescape( "path\\\\to\\\\file" ) );

		// Double quote
		EXPECT_EQ( "say \"hello\"", cppUnescape( "say \\\"hello\\\"" ) );

		// Single quote
		EXPECT_EQ( "it's", cppUnescape( "it\\'s" ) );

		// Null character
		EXPECT_EQ( std::string( "null\0char", 9 ), cppUnescape( "null\\0char" ) );
	}

	TEST( StringUtilsCppUnescape, ControlCharacters )
	{
		// Standard escape sequences
		EXPECT_EQ( "\b", cppUnescape( "\\b" ) );
		EXPECT_EQ( "\f", cppUnescape( "\\f" ) );
		EXPECT_EQ( "\v", cppUnescape( "\\v" ) );
		EXPECT_EQ( "\a", cppUnescape( "\\a" ) );

		// Multiple control characters
		EXPECT_EQ( "\n\t\r", cppUnescape( "\\n\\t\\r" ) );
	}

	TEST( StringUtilsCppUnescape, HexadecimalEscapes )
	{
		// Hexadecimal escape sequences
		EXPECT_EQ( "\x01", cppUnescape( "\\x01" ) );
		EXPECT_EQ( "\x0F", cppUnescape( "\\x0f" ) );
		EXPECT_EQ( "\x0F", cppUnescape( "\\x0F" ) ); // uppercase
		EXPECT_EQ( "\x1F", cppUnescape( "\\x1f" ) );
		EXPECT_EQ( "\x7F", cppUnescape( "\\x7f" ) );
		EXPECT_EQ( "\xFF", cppUnescape( "\\xff" ) );

		// Mixed with text
		EXPECT_EQ( "A\x01Z", cppUnescape( "A\\x01Z" ) );
		EXPECT_EQ( "test\x1Fvalue", cppUnescape( "test\\x1fvalue" ) );
	}

	TEST( StringUtilsCppUnescape, OctalEscapes )
	{
		// Octal escape sequences
		EXPECT_EQ( std::string( 1, '\0' ), cppUnescape( "\\0" ) );
		EXPECT_EQ( "\001", cppUnescape( "\\001" ) );
		EXPECT_EQ( "\007", cppUnescape( "\\007" ) );
		EXPECT_EQ( "\010", cppUnescape( "\\010" ) ); // backspace
		EXPECT_EQ( "\012", cppUnescape( "\\012" ) ); // newline
		EXPECT_EQ( "\177", cppUnescape( "\\177" ) ); // DEL

		// Octal with fewer than 3 digits
		EXPECT_EQ( "\1", cppUnescape( "\\1" ) );
		EXPECT_EQ( "\7", cppUnescape( "\\7" ) );
		EXPECT_EQ( "\10", cppUnescape( "\\10" ) );
		EXPECT_EQ( "\77", cppUnescape( "\\77" ) );

		// Mixed with text
		EXPECT_EQ( "A\001Z", cppUnescape( "A\\001Z" ) );
	}

	TEST( StringUtilsCppUnescape, MixedContent )
	{
		// Multiple escape sequences
		EXPECT_EQ( "line1\nline2\ttab", cppUnescape( "line1\\nline2\\ttab" ) );
		EXPECT_EQ( "path\\file\nend", cppUnescape( "path\\\\file\\nend" ) );
		EXPECT_EQ( "\"quoted\" text", cppUnescape( "\\\"quoted\\\" text" ) );

		// Mix of different escape types
		EXPECT_EQ( "A\nB\tC\\D", cppUnescape( "A\\nB\\tC\\\\D" ) );
		EXPECT_EQ( "hex:\x0Aoctal:\012", cppUnescape( "hex:\\x0Aoctal:\\012" ) );
	}

	TEST( StringUtilsCppUnescape, MalformedInput )
	{
		// Invalid: backslash at end
		EXPECT_EQ( "", cppUnescape( "test\\" ) );

		// Invalid: unknown escape sequence
		EXPECT_EQ( "", cppUnescape( "\\q" ) );
		EXPECT_EQ( "", cppUnescape( "\\z" ) );

		// Invalid: incomplete hex escape
		EXPECT_EQ( "", cppUnescape( "\\x" ) );
		EXPECT_EQ( "", cppUnescape( "\\x0" ) );

		// Invalid: non-hex in hex escape
		EXPECT_EQ( "", cppUnescape( "\\xGG" ) );
		EXPECT_EQ( "", cppUnescape( "\\xZZ" ) );

		// Invalid: octal value out of range
		EXPECT_EQ( "", cppUnescape( "\\400" ) ); // 256 in octal
		EXPECT_EQ( "", cppUnescape( "\\777" ) ); // 511 in octal
	}

	TEST( StringUtilsCppEscape, RoundTripEscaping )
	{
		// Test that escape/unescape round-trips correctly
		std::vector<std::string> test_strings = {
			"hello world",
			"line1\nline2",
			"col1\tcol2",
			"path\\to\\file",
			"\"quoted\"",
			"it's fine",
			std::string( "null\0inside", 11 ),
			"all: \n\t\r\\\"\'\b\f\v\a",
			"\x01\x02\x1F\x7F",
			"",
			"a",
			"normal text 123" };

		for ( const auto& original : test_strings )
		{
			std::string escaped = cppEscape( original );
			std::string unescaped = cppUnescape( escaped );
			EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
		}
	}

	TEST( StringUtilsCppEscape, RealWorldExamples )
	{
		// Code generation
		std::string code = "std::string msg = \"Hello\\nWorld\";";
		std::string escaped = cppEscape( code );
		EXPECT_EQ( "std::string msg = \\\"Hello\\\\nWorld\\\";", escaped );
		EXPECT_EQ( code, cppUnescape( escaped ) );

		// File paths
		std::string path = "C:\\Users\\John\\Documents";
		escaped = cppEscape( path );
		EXPECT_EQ( "C:\\\\Users\\\\John\\\\Documents", escaped );
		EXPECT_EQ( path, cppUnescape( escaped ) );

		// Multi-line text
		std::string multiline = "Line 1\nLine 2\nLine 3";
		escaped = cppEscape( multiline );
		EXPECT_EQ( "Line 1\\nLine 2\\nLine 3", escaped );
		EXPECT_EQ( multiline, cppUnescape( escaped ) );

		// SQL query
		std::string sql = "SELECT * FROM users WHERE name = \"John\"";
		escaped = cppEscape( sql );
		EXPECT_EQ( "SELECT * FROM users WHERE name = \\\"John\\\"", escaped );
		EXPECT_EQ( sql, cppUnescape( escaped ) );
	}

	TEST( StringUtilsCppEscape, EdgeCases )
	{
		// All printable ASCII
		for ( int i = 32; i < 127; ++i )
		{
			if ( i == '\\' || i == '"' || i == '\'' )
				continue; // These get escaped

			std::string test( 1, static_cast<char>( i ) );
			std::string escaped = cppEscape( test );
			std::string unescaped = cppUnescape( escaped );
			EXPECT_EQ( test, unescaped ) << "Failed for ASCII: " << i;
		}

		// All control characters
		for ( int i = 0; i < 32; ++i )
		{
			std::string test( 1, static_cast<char>( i ) );
			std::string escaped = cppEscape( test );
			std::string unescaped = cppUnescape( escaped );
			EXPECT_EQ( test, unescaped ) << "Failed for control char: " << i;
		}

		// DEL character
		std::string del( 1, '\x7F' );
		EXPECT_EQ( del, cppUnescape( cppEscape( del ) ) );

		// Long strings
		std::string long_text( 1000, 'a' );
		EXPECT_EQ( long_text, cppUnescape( cppEscape( long_text ) ) );

		std::string long_newlines( 1000, '\n' );
		std::string escaped_newlines = cppEscape( long_newlines );
		EXPECT_EQ( long_newlines, cppUnescape( escaped_newlines ) );
	}

	//=========================================================
	// String formatting utilities tests
	//=========================================================

	//-----------------------------
	// truncate tests
	//-----------------------------

	TEST( StringUtilsTruncate, BasicTruncation )
	{
		EXPECT_EQ( "Hello", truncate( "Hello World", 5 ) );
		EXPECT_EQ( "Hello W", truncate( "Hello World", 7 ) );
		EXPECT_EQ( "", truncate( "Hello", 0 ) );
	}

	TEST( StringUtilsTruncate, WithEllipsis )
	{
		EXPECT_EQ( "Hel...", truncate( "Hello World", 6, "..." ) );
		EXPECT_EQ( "Hello W...", truncate( "Hello World", 10, "..." ) );
		EXPECT_EQ( "H>>", truncate( "Hello", 3, ">>" ) );
		EXPECT_EQ( "Hello", truncate( "Hello", 10, "..." ) ); // Shorter than maxLength
	}

	TEST( StringUtilsTruncate, ShortStrings )
	{
		EXPECT_EQ( "Hi", truncate( "Hi", 10 ) );
		EXPECT_EQ( "Hi", truncate( "Hi", 10, "..." ) );
		EXPECT_EQ( "Hello", truncate( "Hello", 5 ) );
	}

	TEST( StringUtilsTruncate, EmptyStrings )
	{
		EXPECT_EQ( "", truncate( "", 10 ) );
		EXPECT_EQ( "", truncate( "", 10, "..." ) );
		EXPECT_EQ( "", truncate( "", 0 ) );
	}

	TEST( StringUtilsTruncate, ExactLength )
	{
		EXPECT_EQ( "Hello", truncate( "Hello", 5 ) );
		EXPECT_EQ( "Hello", truncate( "Hello", 5, "..." ) );
	}

	TEST( StringUtilsTruncate, EllipsisLongerThanMaxLength )
	{
		EXPECT_EQ( "H...", truncate( "Hello World", 4, "..." ) ); // Ellipsis equals maxLength, include 1 char + partial ellipsis
		EXPECT_EQ( "H>>", truncate( "Hello", 3, ">>" ) );
		EXPECT_EQ( "Hell", truncate( "Hello", 4, "......" ) ); // Ellipsis much longer than maxLength, just truncate
	}

	//-----------------------------
	// wordWrap tests
	//-----------------------------

	TEST( StringUtilsWordWrap, BasicWrapping )
	{
		EXPECT_EQ( "Hello\nWorld", wordWrap( "Hello World", 8 ) );
		EXPECT_EQ( "This is\na test", wordWrap( "This is a test", 9 ) ); // "This is" = 7 chars, fits within 9
		EXPECT_EQ( "One Two\nThree", wordWrap( "One Two Three", 8 ) );
	}

	TEST( StringUtilsWordWrap, LongWords )
	{
		// Long words get broken at width
		EXPECT_EQ( "Supercalif\nragilistic\nexpialidoc\nious is\nlong", wordWrap( "Supercalifragilisticexpialidocious is long", 10 ) );
		EXPECT_EQ( "A\nvery\nlong\nword", wordWrap( "A very long word", 5 ) );
	}

	TEST( StringUtilsWordWrap, MultipleLines )
	{
		EXPECT_EQ( "Line\none\nLine\ntwo", wordWrap( "Line one\nLine two", 6 ) );
		EXPECT_EQ( "First\nSecond\nThird", wordWrap( "First\nSecond\nThird", 10 ) );
	}

	TEST( StringUtilsWordWrap, EmptyLines )
	{
		EXPECT_EQ( "\n\n", wordWrap( "\n\n", 10 ) );
		EXPECT_EQ( "Text\n\nMore", wordWrap( "Text\n\nMore", 10 ) );
	}

	TEST( StringUtilsWordWrap, Punctuation )
	{
		EXPECT_EQ( "Hello,\nWorld!", wordWrap( "Hello, World!", 8 ) );
		EXPECT_EQ( "Test;\nanother\ntest.", wordWrap( "Test; another test.", 9 ) );
	}

	TEST( StringUtilsWordWrap, EdgeCases )
	{
		EXPECT_EQ( "", wordWrap( "", 10 ) );
		EXPECT_EQ( "Hello", wordWrap( "Hello", 0 ) );				// Width 0
		EXPECT_EQ( "Hello World", wordWrap( "Hello World", 100 ) ); // Width larger than string
	}

	//-----------------------------
	// indent tests
	//-----------------------------

	TEST( StringUtilsIndent, SingleLine )
	{
		EXPECT_EQ( "  Hello", indent( "Hello", 2 ) );
		EXPECT_EQ( "    World", indent( "World", 4 ) );
		EXPECT_EQ( " Text", indent( "Text", 1 ) );
	}

	TEST( StringUtilsIndent, MultiLine )
	{
		EXPECT_EQ( "  Line1\n  Line2", indent( "Line1\nLine2", 2 ) );
		EXPECT_EQ( "    First\n    Second\n    Third", indent( "First\nSecond\nThird", 4 ) );
	}

	TEST( StringUtilsIndent, EmptyLines )
	{
		EXPECT_EQ( "  \n  ", indent( "\n", 2 ) );
		EXPECT_EQ( "  Text\n  \n  More", indent( "Text\n\nMore", 2 ) );
	}

	TEST( StringUtilsIndent, MixedContent )
	{
		EXPECT_EQ( "  if (true) {\n      code();\n  }", indent( "if (true) {\n    code();\n}", 2 ) );
	}

	TEST( StringUtilsIndent, ZeroSpaces )
	{
		EXPECT_EQ( "Hello", indent( "Hello", 0 ) );
		EXPECT_EQ( "Line1\nLine2", indent( "Line1\nLine2", 0 ) );
	}

	TEST( StringUtilsIndent, EmptyString )
	{
		EXPECT_EQ( "", indent( "", 4 ) );
	}

	//-----------------------------
	// dedent tests
	//-----------------------------

	TEST( StringUtilsDedent, CommonWhitespace )
	{
		EXPECT_EQ( "Line1\nLine2", dedent( "  Line1\n  Line2" ) );
		EXPECT_EQ( "Line1\n  Line2", dedent( "    Line1\n      Line2" ) );
		EXPECT_EQ( "First\nSecond", dedent( "   First\n   Second" ) );
	}

	TEST( StringUtilsDedent, MixedIndentation )
	{
		EXPECT_EQ( "Line1\n  Line2\nLine3", dedent( "  Line1\n    Line2\n  Line3" ) );
		EXPECT_EQ( "Code\n    More", dedent( "    Code\n        More" ) );
	}

	TEST( StringUtilsDedent, EmptyLines )
	{
		EXPECT_EQ( "Text\n\nMore", dedent( "  Text\n\n  More" ) );
		EXPECT_EQ( "\n\n", dedent( "\n\n" ) );
	}

	TEST( StringUtilsDedent, NoLeadingWhitespace )
	{
		EXPECT_EQ( "Hello\nWorld", dedent( "Hello\nWorld" ) );
		EXPECT_EQ( "Text", dedent( "Text" ) );
	}

	TEST( StringUtilsDedent, TabsAndSpaces )
	{
		EXPECT_EQ( "Line1\nLine2", dedent( "\tLine1\n\tLine2" ) );
		EXPECT_EQ( "A\n  B", dedent( "  A\n    B" ) );
	}

	TEST( StringUtilsDedent, EdgeCases )
	{
		EXPECT_EQ( "", dedent( "" ) );
		EXPECT_EQ( "   ", dedent( "   " ) ); // Only whitespace
		EXPECT_EQ( "Text", dedent( "Text" ) );
	}

	//-----------------------------
	// Advanced comparison tests
	//-----------------------------

	TEST( StringUtilsCompareIgnoreCase, BasicComparison )
	{
		EXPECT_EQ( 0, compareIgnoreCase( "hello", "HELLO" ) );
		EXPECT_EQ( 0, compareIgnoreCase( "World", "wOrLd" ) );
		EXPECT_EQ( 0, compareIgnoreCase( "ABC123", "abc123" ) );
		EXPECT_LT( compareIgnoreCase( "apple", "BANANA" ), 0 );
		EXPECT_GT( compareIgnoreCase( "zebra", "APPLE" ), 0 );
	}

	TEST( StringUtilsCompareIgnoreCase, LengthDifference )
	{
		// Length only matters when prefixes match
		EXPECT_LT( compareIgnoreCase( "test", "TESTING" ), 0 ); // "test" is prefix of "testing"
		EXPECT_GT( compareIgnoreCase( "testing", "TEST" ), 0 ); // "testing" is longer
		EXPECT_EQ( 0, compareIgnoreCase( "", "" ) );
		EXPECT_GT( compareIgnoreCase( "a", "" ), 0 );
		EXPECT_LT( compareIgnoreCase( "", "A" ), 0 );
	}

	TEST( StringUtilsCompareIgnoreCase, SpecialCharacters )
	{
		EXPECT_EQ( 0, compareIgnoreCase( "Test-123", "test-123" ) );
		EXPECT_LT( compareIgnoreCase( "file_1.txt", "FILE_2.TXT" ), 0 );
		EXPECT_GT( compareIgnoreCase( "CONFIG.INI", "config.dat" ), 0 );
	}

	TEST( StringUtilsCompareIgnoreCase, Sorting )
	{
		// Verify sorting behavior
		EXPECT_LT( compareIgnoreCase( "apple", "BANANA" ), 0 );
		EXPECT_LT( compareIgnoreCase( "Banana", "CHERRY" ), 0 );
		EXPECT_GT( compareIgnoreCase( "zebra", "APPLE" ), 0 );
	}

	TEST( StringUtilsNaturalCompare, BasicNumericSorting )
	{
		EXPECT_LT( naturalCompare( "file2.txt", "file10.txt" ), 0 );
		EXPECT_GT( naturalCompare( "file10.txt", "file2.txt" ), 0 );
		EXPECT_LT( naturalCompare( "v1.0", "v2.0" ), 0 );
		EXPECT_LT( naturalCompare( "v1.9", "v1.10" ), 0 );
		EXPECT_EQ( 0, naturalCompare( "file123", "file123" ) );
	}

	TEST( StringUtilsNaturalCompare, MultipleNumbers )
	{
		EXPECT_LT( naturalCompare( "page1section2", "page1section10" ), 0 );
		EXPECT_LT( naturalCompare( "v2.3.4", "v2.3.10" ), 0 );
		EXPECT_LT( naturalCompare( "1.2.3", "1.2.10" ), 0 );
		EXPECT_GT( naturalCompare( "10.5.1", "2.99.99" ), 0 );
	}

	TEST( StringUtilsNaturalCompare, MixedContent )
	{
		EXPECT_LT( naturalCompare( "test", "test1" ), 0 );
		EXPECT_LT( naturalCompare( "abc", "abc123" ), 0 );
		EXPECT_GT( naturalCompare( "xyz9", "xyz" ), 0 );
		EXPECT_LT( naturalCompare( "file", "file0" ), 0 );
	}

	TEST( StringUtilsNaturalCompare, EdgeCases )
	{
		EXPECT_EQ( 0, naturalCompare( "", "" ) );
		EXPECT_GT( naturalCompare( "a", "" ), 0 );
		EXPECT_LT( naturalCompare( "", "a" ), 0 );
		EXPECT_LT( naturalCompare( "0", "00" ), 0 );
		EXPECT_LT( naturalCompare( "1", "10" ), 0 );
	}

	TEST( StringUtilsNaturalCompare, RealWorldFilenames )
	{
		// Simulate file sorting
		EXPECT_LT( naturalCompare( "chapter1.doc", "chapter2.doc" ), 0 );
		EXPECT_LT( naturalCompare( "chapter2.doc", "chapter10.doc" ), 0 );
		EXPECT_LT( naturalCompare( "image1.png", "image10.png" ), 0 );
		EXPECT_LT( naturalCompare( "version1.2.3", "version1.2.10" ), 0 );
	}

	TEST( StringUtilsCommonPrefix, BasicMatching )
	{
		EXPECT_EQ( "hello ", commonPrefix( "hello world", "hello there" ) ); // Include space
		EXPECT_EQ( "test", commonPrefix( "testing", "tester" ) );
		EXPECT_EQ( "", commonPrefix( "abc", "xyz" ) );
		EXPECT_EQ( "same", commonPrefix( "same", "same" ) );
	}

	TEST( StringUtilsCommonPrefix, PartialMatches )
	{
		EXPECT_EQ( "/usr/local/", commonPrefix( "/usr/local/bin", "/usr/local/lib" ) ); // Include trailing /
		EXPECT_EQ( "file_", commonPrefix( "file_1.txt", "file_2.txt" ) );
		EXPECT_EQ( "prefix", commonPrefix( "prefix123", "prefix456" ) );
	}

	TEST( StringUtilsCommonPrefix, EdgeCases )
	{
		EXPECT_EQ( "", commonPrefix( "", "" ) );
		EXPECT_EQ( "", commonPrefix( "abc", "" ) );
		EXPECT_EQ( "", commonPrefix( "", "xyz" ) );
		EXPECT_EQ( "a", commonPrefix( "a", "abc" ) );
		EXPECT_EQ( "abc", commonPrefix( "abc", "abc" ) );
	}

	TEST( StringUtilsCommonPrefix, CaseSensitive )
	{
		EXPECT_EQ( "", commonPrefix( "Hello", "hello" ) );
		EXPECT_EQ( "Test", commonPrefix( "Testing", "Tester" ) );
	}

	TEST( StringUtilsCommonSuffix, BasicMatching )
	{
		EXPECT_EQ( ".txt", commonSuffix( "file1.txt", "file2.txt" ) );
		EXPECT_EQ( "ing", commonSuffix( "testing", "running" ) );
		EXPECT_EQ( "", commonSuffix( "abc", "xyz" ) );
		EXPECT_EQ( "same", commonSuffix( "same", "same" ) );
	}

	TEST( StringUtilsCommonSuffix, PartialMatches )
	{
		EXPECT_EQ( "/data", commonSuffix( "/usr/local/data", "/home/user/data" ) );
		EXPECT_EQ( "_test.cpp", commonSuffix( "unit_test.cpp", "integration_test.cpp" ) );
		EXPECT_EQ( "123", commonSuffix( "abc123", "xyz123" ) );
	}

	TEST( StringUtilsCommonSuffix, EdgeCases )
	{
		EXPECT_EQ( "", commonSuffix( "", "" ) );
		EXPECT_EQ( "", commonSuffix( "abc", "" ) );
		EXPECT_EQ( "", commonSuffix( "", "xyz" ) );
		EXPECT_EQ( "c", commonSuffix( "abc", "c" ) );
		EXPECT_EQ( "abc", commonSuffix( "abc", "abc" ) );
	}

	TEST( StringUtilsCommonSuffix, CaseSensitive )
	{
		EXPECT_EQ( "ello", commonSuffix( "Hello", "hello" ) );		 // Case matters: 'H' != 'h', but "ello" matches
		EXPECT_EQ( "esting", commonSuffix( "Testing", "testing" ) ); // 'T' != 't', but "esting" matches
	}

	//----------------------------------------------
	// Date validation (RFC 3339)
	//----------------------------------------------

	TEST( StringUtilsIsDate, ValidDates )
	{
		EXPECT_TRUE( isDate( "2025-11-29" ) );
		EXPECT_TRUE( isDate( "2000-01-01" ) );
		EXPECT_TRUE( isDate( "1999-12-31" ) );
		EXPECT_TRUE( isDate( "2024-02-29" ) ); // Leap year (basic check, not validating leap year logic)
		EXPECT_TRUE( isDate( "2023-02-28" ) );
		EXPECT_TRUE( isDate( "0001-01-01" ) );
		EXPECT_TRUE( isDate( "9999-12-31" ) );
	}

	TEST( StringUtilsIsDate, InvalidDates )
	{
		EXPECT_FALSE( isDate( "" ) );
		EXPECT_FALSE( isDate( "2025-13-01" ) );	 // Invalid month
		EXPECT_FALSE( isDate( "2025-00-01" ) );	 // Invalid month
		EXPECT_FALSE( isDate( "2025-01-32" ) );	 // Invalid day
		EXPECT_FALSE( isDate( "2025-01-00" ) );	 // Invalid day
		EXPECT_FALSE( isDate( "2025-04-31" ) );	 // April has 30 days
		EXPECT_FALSE( isDate( "2025-06-31" ) );	 // June has 30 days
		EXPECT_FALSE( isDate( "25-11-29" ) );	 // Wrong year format
		EXPECT_FALSE( isDate( "2025/11/29" ) );	 // Wrong separator
		EXPECT_FALSE( isDate( "2025-1-29" ) );	 // Missing leading zero
		EXPECT_FALSE( isDate( "2025-11-9" ) );	 // Missing leading zero
		EXPECT_FALSE( isDate( "20251129" ) );	 // No separators
		EXPECT_FALSE( isDate( "2025-11-29T" ) ); // Extra character
	}

	//----------------------------------------------
	// Time validation (RFC 3339)
	//----------------------------------------------

	TEST( StringUtilsIsTime, ValidTimes )
	{
		EXPECT_TRUE( isTime( "14:30:00Z" ) );
		EXPECT_TRUE( isTime( "00:00:00Z" ) );
		EXPECT_TRUE( isTime( "23:59:59Z" ) );
		EXPECT_TRUE( isTime( "12:00:00z" ) ); // Lowercase z
		EXPECT_TRUE( isTime( "14:30:00+00:00" ) );
		EXPECT_TRUE( isTime( "14:30:00-05:00" ) );
		EXPECT_TRUE( isTime( "14:30:00+12:00" ) );
		EXPECT_TRUE( isTime( "14:30:00.123Z" ) );		// Fractional seconds
		EXPECT_TRUE( isTime( "14:30:00.123456789Z" ) ); // Many fractional digits
		EXPECT_TRUE( isTime( "23:59:60Z" ) );			// Leap second (standard case)
		EXPECT_TRUE( isTime( "00:00:60Z" ) );			// Leap second (boundary test)
		EXPECT_TRUE( isTime( "12:30:60+00:00" ) );		// Leap second with offset
		EXPECT_TRUE( isTime( "23:59:60.999Z" ) );		// Leap second with fractional
	}

	TEST( StringUtilsIsTime, InvalidTimes )
	{
		EXPECT_FALSE( isTime( "" ) );
		EXPECT_FALSE( isTime( "24:00:00Z" ) );		// Invalid hour
		EXPECT_FALSE( isTime( "14:60:00Z" ) );		// Invalid minute
		EXPECT_FALSE( isTime( "14:30:61Z" ) );		// Invalid second (61 > 60)
		EXPECT_FALSE( isTime( "14:30:62Z" ) );		// Invalid second (62 > 60)
		EXPECT_FALSE( isTime( "14:30:99Z" ) );		// Invalid second (way over)
		EXPECT_FALSE( isTime( "14:30:00" ) );		// Missing timezone
		EXPECT_FALSE( isTime( "14:30:00+" ) );		// Incomplete timezone
		EXPECT_FALSE( isTime( "14:30:00+25:00" ) ); // Invalid tz hour
		EXPECT_FALSE( isTime( "14:30:00+00:60" ) ); // Invalid tz minute
		EXPECT_FALSE( isTime( "14:30Z" ) );			// Missing seconds
		EXPECT_FALSE( isTime( "14:30:00.Z" ) );		// Empty fractional
		EXPECT_FALSE( isTime( "1:30:00Z" ) );		// Missing leading zero
	}

	//----------------------------------------------
	// DateTime validation (RFC 3339)
	//----------------------------------------------

	TEST( StringUtilsIsDateTime, ValidDateTimes )
	{
		EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00Z" ) );
		EXPECT_TRUE( isDateTime( "2025-11-29t14:30:00z" ) ); // Lowercase
		EXPECT_TRUE( isDateTime( "2000-01-01T00:00:00Z" ) );
		EXPECT_TRUE( isDateTime( "2025-12-31T23:59:59Z" ) );
		EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00+05:30" ) );
		EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00-08:00" ) );
		EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00.123Z" ) );
		EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00.123456+00:00" ) );
	}

	TEST( StringUtilsIsDateTime, InvalidDateTimes )
	{
		EXPECT_FALSE( isDateTime( "" ) );
		EXPECT_FALSE( isDateTime( "2025-11-29" ) );			  // Date only
		EXPECT_FALSE( isDateTime( "14:30:00Z" ) );			  // Time only
		EXPECT_FALSE( isDateTime( "2025-11-29 14:30:00Z" ) ); // Space instead of T
		EXPECT_FALSE( isDateTime( "2025-13-29T14:30:00Z" ) ); // Invalid month
		EXPECT_FALSE( isDateTime( "2025-11-29T25:30:00Z" ) ); // Invalid hour
		EXPECT_FALSE( isDateTime( "2025-11-29T14:30:00" ) );  // Missing timezone
		EXPECT_FALSE( isDateTime( "2025/11/29T14:30:00Z" ) ); // Wrong date separator
	}

	//----------------------------------------------
	// Duration validation (ISO 8601)
	//----------------------------------------------

	TEST( StringUtilsIsDuration, ValidDurations )
	{
		EXPECT_TRUE( isDuration( "P1Y" ) );
		EXPECT_TRUE( isDuration( "P1M" ) );
		EXPECT_TRUE( isDuration( "P1D" ) );
		EXPECT_TRUE( isDuration( "PT1H" ) );
		EXPECT_TRUE( isDuration( "PT1M" ) );
		EXPECT_TRUE( isDuration( "PT1S" ) );
		EXPECT_TRUE( isDuration( "P1Y2M3D" ) );
		EXPECT_TRUE( isDuration( "PT1H2M3S" ) );
		EXPECT_TRUE( isDuration( "P1Y2M3DT4H5M6S" ) );
		EXPECT_TRUE( isDuration( "P1W" ) ); // Week format
		EXPECT_TRUE( isDuration( "P52W" ) );
		EXPECT_TRUE( isDuration( "PT0.5S" ) ); // Fractional seconds
		EXPECT_TRUE( isDuration( "PT1.123S" ) );
	}

	TEST( StringUtilsIsDuration, InvalidDurations )
	{
		EXPECT_FALSE( isDuration( "" ) );
		EXPECT_FALSE( isDuration( "P" ) );		  // P alone
		EXPECT_FALSE( isDuration( "1Y" ) );		  // Missing P
		EXPECT_FALSE( isDuration( "PT" ) );		  // T without time
		EXPECT_FALSE( isDuration( "P1H" ) );	  // H without T
		EXPECT_FALSE( isDuration( "P1Y2M3DT" ) ); // T without time parts
		EXPECT_FALSE( isDuration( "P1WT1H" ) );	  // Week with other parts
		EXPECT_FALSE( isDuration( "P.5S" ) );	  // Decimal without integer
	}

	//----------------------------------------------
	// Email validation (RFC 5321)
	//----------------------------------------------

	TEST( StringUtilsIsEmail, ValidEmails )
	{
		EXPECT_TRUE( isEmail( "user@example.com" ) );
		EXPECT_TRUE( isEmail( "user.name@example.com" ) );
		EXPECT_TRUE( isEmail( "user+tag@example.com" ) );
		EXPECT_TRUE( isEmail( "user@sub.example.com" ) );
		EXPECT_TRUE( isEmail( "user@example.co.uk" ) );
		EXPECT_TRUE( isEmail( "a@b.co" ) );
		EXPECT_TRUE( isEmail( "user123@example123.com" ) );
		EXPECT_TRUE( isEmail( "user_name@example.com" ) );
		EXPECT_TRUE( isEmail( "user-name@example.com" ) );
		EXPECT_TRUE( isEmail( "user!def@example.com" ) ); // Special chars allowed in local
	}

	TEST( StringUtilsIsEmail, InvalidEmails )
	{
		EXPECT_FALSE( isEmail( "" ) );
		EXPECT_FALSE( isEmail( "user" ) );							   // No @
		EXPECT_FALSE( isEmail( "@example.com" ) );					   // No local part
		EXPECT_FALSE( isEmail( "user@" ) );							   // No domain
		EXPECT_FALSE( isEmail( "user@.com" ) );						   // Domain starts with dot
		EXPECT_FALSE( isEmail( "user@example" ) );					   // No TLD (single label)
		EXPECT_FALSE( isEmail( ".user@example.com" ) );				   // Local starts with dot
		EXPECT_FALSE( isEmail( "user.@example.com" ) );				   // Local ends with dot
		EXPECT_FALSE( isEmail( "user..name@example.com" ) );		   // Consecutive dots
		EXPECT_FALSE( isEmail( "user name@example.com" ) );			   // Space in local
		EXPECT_FALSE( isEmail( std::string( 255, 'a' ) + "@b.com" ) ); // Too long
	}

	//----------------------------------------------
	// UUID validation (RFC 4122)
	//----------------------------------------------

	TEST( StringUtilsIsUUID, ValidUUIDs )
	{
		EXPECT_TRUE( isUUID( "550e8400-e29b-41d4-a716-446655440000" ) );
		EXPECT_TRUE( isUUID( "00000000-0000-0000-0000-000000000000" ) );
		EXPECT_TRUE( isUUID( "ffffffff-ffff-ffff-ffff-ffffffffffff" ) );
		EXPECT_TRUE( isUUID( "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF" ) ); // Uppercase
		EXPECT_TRUE( isUUID( "123e4567-e89b-12d3-a456-426614174000" ) );
		EXPECT_TRUE( isUUID( "a1b2c3d4-e5f6-7890-abcd-ef1234567890" ) );
	}

	TEST( StringUtilsIsUUID, InvalidUUIDs )
	{
		EXPECT_FALSE( isUUID( "" ) );
		EXPECT_FALSE( isUUID( "550e8400-e29b-41d4-a716-44665544000" ) );   // Too short
		EXPECT_FALSE( isUUID( "550e8400-e29b-41d4-a716-4466554400000" ) ); // Too long
		EXPECT_FALSE( isUUID( "550e8400e29b41d4a716446655440000" ) );	   // No hyphens
		EXPECT_FALSE( isUUID( "550e8400-e29b-41d4-a716446655440000" ) );   // Missing hyphen
		EXPECT_FALSE( isUUID( "550g8400-e29b-41d4-a716-446655440000" ) );  // Invalid hex 'g'
		EXPECT_FALSE( isUUID( "550e8400-e29b-41d4-a716-44665544000z" ) );  // Invalid char 'z'
		EXPECT_FALSE( isUUID( "550e8400_e29b_41d4_a716_446655440000" ) );  // Underscores
	}

	//----------------------------------------------
	// URI validation (RFC 3986)
	//----------------------------------------------

	TEST( StringUtilsIsURI, ValidURIs )
	{
		EXPECT_TRUE( isURI( "http://example.com" ) );
		EXPECT_TRUE( isURI( "https://example.com/path" ) );
		EXPECT_TRUE( isURI( "ftp://ftp.example.com/file.txt" ) );
		EXPECT_TRUE( isURI( "mailto:user@example.com" ) );
		EXPECT_TRUE( isURI( "file:///path/to/file" ) );
		EXPECT_TRUE( isURI( "custom-scheme://host/path" ) );
		EXPECT_TRUE( isURI( "scheme+sub://host" ) );
		EXPECT_TRUE( isURI( "scheme.sub://host" ) );
		EXPECT_TRUE( isURI( "urn:isbn:0451450523" ) );
		EXPECT_TRUE( isURI( "tel:+1-816-555-1212" ) );
	}

	TEST( StringUtilsIsURI, InvalidURIs )
	{
		EXPECT_FALSE( isURI( "" ) );
		EXPECT_FALSE( isURI( "example.com" ) );			// No scheme
		EXPECT_FALSE( isURI( "://example.com" ) );		// Empty scheme
		EXPECT_FALSE( isURI( "1http://example.com" ) ); // Scheme starts with digit
		EXPECT_FALSE( isURI( "-http://example.com" ) ); // Scheme starts with hyphen
		EXPECT_FALSE( isURI( "http ://example.com" ) ); // Space in URI
		EXPECT_FALSE( isURI( "http://example .com" ) ); // Space in URI
	}

	//----------------------------------------------
	// URI Reference validation (RFC 3986)
	//----------------------------------------------

	TEST( StringUtilsIsURIReference, ValidURIReferences )
	{
		// Absolute URIs
		EXPECT_TRUE( isURIReference( "http://example.com" ) );
		EXPECT_TRUE( isURIReference( "https://example.com/path" ) );

		// Relative references
		EXPECT_TRUE( isURIReference( "/path/to/resource" ) );
		EXPECT_TRUE( isURIReference( "relative/path" ) );
		EXPECT_TRUE( isURIReference( "../parent/path" ) );
		EXPECT_TRUE( isURIReference( "./current/path" ) );
		EXPECT_TRUE( isURIReference( "?query=value" ) );
		EXPECT_TRUE( isURIReference( "#fragment" ) );
		EXPECT_TRUE( isURIReference( "" ) ); // Empty is valid
	}

	TEST( StringUtilsIsURIReference, InvalidURIReferences )
	{
		EXPECT_FALSE( isURIReference( "path with spaces" ) );
		EXPECT_FALSE( isURIReference( "http://example .com" ) );
		EXPECT_FALSE( isURIReference( "/path\twith\ttabs" ) );
	}

	//----------------------------------------------
	// JSON Pointer validation (RFC 6901)
	//----------------------------------------------

	TEST( StringUtilsIsJSONPointer, ValidPointers )
	{
		EXPECT_TRUE( isJSONPointer( "" ) );	 // Root document
		EXPECT_TRUE( isJSONPointer( "/" ) ); // Empty key
		EXPECT_TRUE( isJSONPointer( "/foo" ) );
		EXPECT_TRUE( isJSONPointer( "/foo/bar" ) );
		EXPECT_TRUE( isJSONPointer( "/foo/0" ) ); // Array index
		EXPECT_TRUE( isJSONPointer( "/a~1b" ) );  // Escaped /
		EXPECT_TRUE( isJSONPointer( "/c%d" ) );	  // % is allowed
		EXPECT_TRUE( isJSONPointer( "/e^f" ) );	  // ^ is allowed
		EXPECT_TRUE( isJSONPointer( "/m~0n" ) );  // Escaped ~
		EXPECT_TRUE( isJSONPointer( "/foo/bar/baz/0/qux" ) );
	}

	TEST( StringUtilsIsJSONPointer, InvalidPointers )
	{
		EXPECT_FALSE( isJSONPointer( "foo" ) );		// Missing leading /
		EXPECT_FALSE( isJSONPointer( "foo/bar" ) ); // Missing leading /
		EXPECT_FALSE( isJSONPointer( "/foo~" ) );	// ~ at end
		EXPECT_FALSE( isJSONPointer( "/foo~2" ) );	// Invalid escape ~2
		EXPECT_FALSE( isJSONPointer( "/foo~a" ) );	// Invalid escape ~a
	}

	//----------------------------------------------
	// Relative JSON Pointer validation
	//----------------------------------------------

	TEST( StringUtilsIsRelativeJSONPointer, ValidPointers )
	{
		// Bare integers are valid per RFC 6901
		EXPECT_TRUE( isRelativeJSONPointer( "0" ) );   // Just zero (valid!)
		EXPECT_TRUE( isRelativeJSONPointer( "1" ) );   // Just integer (valid!)
		EXPECT_TRUE( isRelativeJSONPointer( "42" ) );  // Just integer (valid!)
		EXPECT_TRUE( isRelativeJSONPointer( "100" ) ); // Multi-digit integer (valid!)

		// Integer with # or path
		EXPECT_TRUE( isRelativeJSONPointer( "0#" ) );		 // Current + name
		EXPECT_TRUE( isRelativeJSONPointer( "1#" ) );		 // Parent + name
		EXPECT_TRUE( isRelativeJSONPointer( "0/foo" ) );	 // Current + path
		EXPECT_TRUE( isRelativeJSONPointer( "1/foo/bar" ) ); // Parent + path
		EXPECT_TRUE( isRelativeJSONPointer( "2/0" ) );		 // Grandparent + index
		EXPECT_TRUE( isRelativeJSONPointer( "0/" ) );		 // Empty token
		EXPECT_TRUE( isRelativeJSONPointer( "10/foo" ) );	 // Multi-digit
		EXPECT_TRUE( isRelativeJSONPointer( "0/a~0b" ) );	 // With escape
	}

	TEST( StringUtilsIsRelativeJSONPointer, InvalidPointers )
	{
		EXPECT_FALSE( isRelativeJSONPointer( "" ) );	   // Empty
		EXPECT_FALSE( isRelativeJSONPointer( "#" ) );	   // Missing number
		EXPECT_FALSE( isRelativeJSONPointer( "/foo" ) );   // Absolute pointer
		EXPECT_FALSE( isRelativeJSONPointer( "01/foo" ) ); // Leading zero (with path)
		EXPECT_FALSE( isRelativeJSONPointer( "01" ) );	   // Leading zero (bare)
		EXPECT_FALSE( isRelativeJSONPointer( "01#" ) );	   // Leading zero (with #)
		EXPECT_FALSE( isRelativeJSONPointer( "-1/foo" ) ); // Negative
		EXPECT_FALSE( isRelativeJSONPointer( "-1" ) );	   // Negative bare
		EXPECT_FALSE( isRelativeJSONPointer( "a/foo" ) );  // Non-digit start
		EXPECT_FALSE( isRelativeJSONPointer( "0#foo" ) );  // # not at end
		EXPECT_FALSE( isRelativeJSONPointer( "1#2" ) );	   // # in middle
	}

	//----------------------------------------------
	// Constexpr validation tests
	//----------------------------------------------

	TEST( StringUtilsConstexpr, DateTimeValidation )
	{
		constexpr bool validDate = isDate( "2025-11-29" );
		constexpr bool invalidDate = isDate( "invalid" );
		constexpr bool validTime = isTime( "14:30:00Z" );
		constexpr bool validDateTime = isDateTime( "2025-11-29T14:30:00Z" );
		constexpr bool validDuration = isDuration( "P1Y2M3D" );

		EXPECT_TRUE( validDate );
		EXPECT_FALSE( invalidDate );
		EXPECT_TRUE( validTime );
		EXPECT_TRUE( validDateTime );
		EXPECT_TRUE( validDuration );
	}

	TEST( StringUtilsConstexpr, FormatValidation )
	{
		constexpr bool validUUID = isUUID( "550e8400-e29b-41d4-a716-446655440000" );
		constexpr bool validURI = isURI( "https://example.com" );
		constexpr bool validURIRef = isURIReference( "/path" );
		constexpr bool validJSONPtr = isJSONPointer( "/foo/bar" );
		constexpr bool validRelPtr = isRelativeJSONPointer( "1/foo" );

		EXPECT_TRUE( validUUID );
		EXPECT_TRUE( validURI );
		EXPECT_TRUE( validURIRef );
		EXPECT_TRUE( validJSONPtr );
		EXPECT_TRUE( validRelPtr );
	}
} // namespace nfx::string::test
