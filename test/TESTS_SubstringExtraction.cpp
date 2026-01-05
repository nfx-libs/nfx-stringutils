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
 * @file TESTS_SubstringExtraction.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
	//=====================================================================
	// Substring extraction tests
	//=====================================================================

	TEST( SubstringExtraction, SubstringBefore )
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

	TEST( SubstringExtraction, SubstringAfter )
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

	TEST( SubstringExtraction, SubstringBeforeLast )
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

	TEST( SubstringExtraction, SubstringAfterLast )
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

	TEST( SubstringExtraction, ExtractBetween )
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

	TEST( SubstringExtraction, RemovePrefix )
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

	TEST( SubstringExtraction, RemoveSuffix )
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

	TEST( SubstringExtraction, EdgeCases )
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

	TEST( SubstringExtraction, SubstringBefore_CharOverload )
	{
		// Basic functionality
		EXPECT_EQ( "hello", substringBefore( "hello.world", '.' ) );
		EXPECT_EQ( "path", substringBefore( "path/to/file", '/' ) );
		EXPECT_EQ( "user", substringBefore( "user@example.com", '@' ) );

		// Character not found (returns entire string)
		EXPECT_EQ( "hello world", substringBefore( "hello world", '.' ) );
		EXPECT_EQ( "test", substringBefore( "test", '@' ) );

		// Empty string
		EXPECT_EQ( "", substringBefore( "", '.' ) );

		// Character at start
		EXPECT_EQ( "", substringBefore( ".hidden", '.' ) );

		// Character at end
		EXPECT_EQ( "test", substringBefore( "test.", '.' ) );

		// Multiple occurrences (returns before first)
		EXPECT_EQ( "hello", substringBefore( "hello.world.txt", '.' ) );
		EXPECT_EQ( "", substringBefore( "/usr/local", '/' ) );

		// Special characters
		EXPECT_EQ( "key", substringBefore( "key=value", '=' ) );
		EXPECT_EQ( "hello", substringBefore( "hello world", ' ' ) );
	}

	TEST( SubstringExtraction, SubstringAfter_CharOverload )
	{
		// Basic functionality
		EXPECT_EQ( "world", substringAfter( "hello.world", '.' ) );
		EXPECT_EQ( "to/file", substringAfter( "path/to/file", '/' ) );
		EXPECT_EQ( "example.com", substringAfter( "user@example.com", '@' ) );

		// Character not found (returns empty)
		EXPECT_EQ( "", substringAfter( "hello world", '.' ) );
		EXPECT_EQ( "", substringAfter( "test", '@' ) );

		// Empty string
		EXPECT_EQ( "", substringAfter( "", '.' ) );

		// Character at start
		EXPECT_EQ( "hidden", substringAfter( ".hidden", '.' ) );

		// Character at end
		EXPECT_EQ( "", substringAfter( "test.", '.' ) );

		// Multiple occurrences (returns after first)
		EXPECT_EQ( "world.txt", substringAfter( "hello.world.txt", '.' ) );
		EXPECT_EQ( "usr/local", substringAfter( "/usr/local", '/' ) );

		// Special characters
		EXPECT_EQ( "value", substringAfter( "key=value", '=' ) );
		EXPECT_EQ( "world", substringAfter( "hello world", ' ' ) );
	}

	TEST( SubstringExtraction, SubstringBeforeLast_CharOverload )
	{
		// Basic functionality
		EXPECT_EQ( "hello.world", substringBeforeLast( "hello.world.txt", '.' ) );
		EXPECT_EQ( "path/to", substringBeforeLast( "path/to/file", '/' ) );
		EXPECT_EQ( "192.168.1", substringBeforeLast( "192.168.1.1", '.' ) );

		// Character not found (returns entire string)
		EXPECT_EQ( "hello world", substringBeforeLast( "hello world", '.' ) );
		EXPECT_EQ( "test", substringBeforeLast( "test", '@' ) );

		// Empty string
		EXPECT_EQ( "", substringBeforeLast( "", '.' ) );

		// Character at start (only occurrence)
		EXPECT_EQ( "", substringBeforeLast( ".hidden", '.' ) );

		// Character at end
		EXPECT_EQ( "test", substringBeforeLast( "test.", '.' ) );

		// Single occurrence
		EXPECT_EQ( "hello", substringBeforeLast( "hello.world", '.' ) );

		// Multiple occurrences (returns before last)
		EXPECT_EQ( "file.backup", substringBeforeLast( "file.backup.txt", '.' ) );
		EXPECT_EQ( "/usr/local", substringBeforeLast( "/usr/local/bin", '/' ) );
	}

	TEST( SubstringExtraction, SubstringAfterLast_CharOverload )
	{
		// Basic functionality
		EXPECT_EQ( "txt", substringAfterLast( "hello.world.txt", '.' ) );
		EXPECT_EQ( "file", substringAfterLast( "path/to/file", '/' ) );
		EXPECT_EQ( "1", substringAfterLast( "192.168.1.1", '.' ) );

		// Character not found (returns empty)
		EXPECT_EQ( "", substringAfterLast( "hello world", '.' ) );
		EXPECT_EQ( "", substringAfterLast( "test", '@' ) );

		// Empty string
		EXPECT_EQ( "", substringAfterLast( "", '.' ) );

		// Character at start (only occurrence)
		EXPECT_EQ( "hidden", substringAfterLast( ".hidden", '.' ) );

		// Character at end
		EXPECT_EQ( "", substringAfterLast( "test.", '.' ) );

		// Single occurrence
		EXPECT_EQ( "world", substringAfterLast( "hello.world", '.' ) );

		// Multiple occurrences (returns after last)
		EXPECT_EQ( "txt", substringAfterLast( "file.backup.txt", '.' ) );
		EXPECT_EQ( "bin", substringAfterLast( "/usr/local/bin", '/' ) );
		EXPECT_EQ( "com", substringAfterLast( "user@mail.example.com", '.' ) );
	}
} // namespace nfx::string::test
