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
 * @file TESTS_UrlEncoding.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
	//=====================================================================
	// URL Encoding/Decoding
	//=====================================================================

	TEST( UrlEncoding, BasicEncoding )
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

	TEST( UrlEncoding, ReservedCharacters )
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

	TEST( UrlEncoding, SpecialAndUnicodeCharacters )
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

	TEST( UrlEncoding, UrlEncode_RealWorldExamples )
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

	TEST( UrlEncoding, BasicDecoding )
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

	TEST( UrlEncoding, CaseInsensitiveHex )
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

	TEST( UrlEncoding, SpecialCharacters )
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

	TEST( UrlEncoding, UrlDecode_RealWorldExamples )
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

	TEST( UrlEncoding, MalformedInput )
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

	TEST( UrlEncoding, RoundTripEncoding )
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

	TEST( UrlEncoding, EdgeCases )
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
} // namespace nfx::string::test
