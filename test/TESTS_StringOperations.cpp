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
 * @file TESTS_StringOperations.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
	//=====================================================================
	// String operations tests
	//=====================================================================

	TEST( StringOperations, EndsWith )
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

	TEST( StringOperations, EndsWith_CharOverload )
	{
		// Basic functionality with char
		EXPECT_TRUE( endsWith( "hello world", 'd' ) );
		EXPECT_TRUE( endsWith( "test", 't' ) );
		EXPECT_FALSE( endsWith( "hello world", 'h' ) );
		EXPECT_FALSE( endsWith( "hello world", 'D' ) ); // Case sensitive

		// Edge cases
		EXPECT_FALSE( endsWith( "", 'a' ) );  // Empty string
		EXPECT_TRUE( endsWith( "a", 'a' ) );  // Single character match
		EXPECT_FALSE( endsWith( "a", 'b' ) ); // Single character no match

		// Special characters
		EXPECT_TRUE( endsWith( "file.txt", 't' ) );
		EXPECT_TRUE( endsWith( "question?", '?' ) );
		EXPECT_TRUE( endsWith( "exclaim!", '!' ) );
	}

	TEST( StringOperations, EndsWith_CStringOverload )
	{
		// Basic functionality with const char*
		EXPECT_TRUE( endsWith( "hello world", "world" ) );
		EXPECT_TRUE( endsWith( "testing", "ing" ) );
		EXPECT_FALSE( endsWith( "hello world", "hello" ) );
		EXPECT_FALSE( endsWith( "hello world", "World" ) ); // Case sensitive

		// Edge cases
		EXPECT_TRUE( endsWith( "test", "" ) );	   // Empty suffix
		EXPECT_FALSE( endsWith( "", "test" ) );	   // Empty string
		EXPECT_TRUE( endsWith( "test", "test" ) ); // Exact match

		// Literals
		const char* suffix = "fix";
		EXPECT_TRUE( endsWith( "suffix", suffix ) );
		EXPECT_FALSE( endsWith( "pretend", suffix ) );
	}

	TEST( StringOperations, StartsWith )
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

	TEST( StringOperations, StartsWith_CharOverload )
	{
		// Basic functionality with char
		EXPECT_TRUE( startsWith( "hello world", 'h' ) );
		EXPECT_TRUE( startsWith( "test", 't' ) );
		EXPECT_FALSE( startsWith( "hello world", 'w' ) );
		EXPECT_FALSE( startsWith( "hello world", 'H' ) ); // Case sensitive

		// Edge cases
		EXPECT_FALSE( startsWith( "", 'a' ) );	// Empty string
		EXPECT_TRUE( startsWith( "a", 'a' ) );	// Single character match
		EXPECT_FALSE( startsWith( "a", 'b' ) ); // Single character no match

		// Special characters
		EXPECT_TRUE( startsWith( "@mention", '@' ) );
		EXPECT_TRUE( startsWith( "#hashtag", '#' ) );
		EXPECT_TRUE( startsWith( " space", ' ' ) );
	}

	TEST( StringOperations, StartsWith_CStringOverload )
	{
		// Basic functionality with const char*
		EXPECT_TRUE( startsWith( "hello world", "hello" ) );
		EXPECT_TRUE( startsWith( "testing", "test" ) );
		EXPECT_FALSE( startsWith( "hello world", "world" ) );
		EXPECT_FALSE( startsWith( "hello world", "Hello" ) ); // Case sensitive

		// Edge cases
		EXPECT_TRUE( startsWith( "test", "" ) );	 // Empty prefix
		EXPECT_FALSE( startsWith( "", "test" ) );	 // Empty string
		EXPECT_TRUE( startsWith( "test", "test" ) ); // Exact match

		// Literals
		const char* prefix = "pre";
		EXPECT_TRUE( startsWith( "prefix", prefix ) );
		EXPECT_FALSE( startsWith( "suffix", prefix ) );
	}

	TEST( StringOperations, Contains )
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

	TEST( StringOperations, Contains_CharOverload )
	{
		// Basic functionality with char
		EXPECT_TRUE( contains( "hello world", 'h' ) );
		EXPECT_TRUE( contains( "hello world", 'o' ) );
		EXPECT_TRUE( contains( "hello world", 'd' ) );
		EXPECT_TRUE( contains( "hello world", ' ' ) );
		EXPECT_FALSE( contains( "hello world", 'x' ) );
		EXPECT_FALSE( contains( "hello world", 'H' ) ); // Case sensitive

		// Edge cases
		EXPECT_FALSE( contains( "", 'a' ) );  // Empty string
		EXPECT_TRUE( contains( "a", 'a' ) );  // Single character match
		EXPECT_FALSE( contains( "a", 'b' ) ); // Single character no match

		// Special characters
		EXPECT_TRUE( contains( "user@example.com", '@' ) );
		EXPECT_TRUE( contains( "path/to/file", '/' ) );
		EXPECT_TRUE( contains( "key=value", '=' ) );

		// Multiple occurrences (finds first)
		EXPECT_TRUE( contains( "hello", 'l' ) );
		EXPECT_TRUE( contains( "aaa", 'a' ) );
	}

	TEST( StringOperations, Contains_CStringOverload )
	{
		// Basic functionality with const char*
		EXPECT_TRUE( contains( "hello world", "hello" ) );
		EXPECT_TRUE( contains( "hello world", "world" ) );
		EXPECT_TRUE( contains( "hello world", "o w" ) );
		EXPECT_FALSE( contains( "hello world", "Hello" ) ); // Case sensitive
		EXPECT_FALSE( contains( "hello world", "xyz" ) );

		// Edge cases
		EXPECT_TRUE( contains( "test", "" ) );	   // Empty substring
		EXPECT_FALSE( contains( "", "test" ) );	   // Empty string
		EXPECT_TRUE( contains( "test", "test" ) ); // Exact match

		// Literals
		const char* substring = "sub";
		EXPECT_TRUE( contains( "substring", substring ) );
		EXPECT_FALSE( contains( "string", substring ) );

		// Multiple occurrences
		EXPECT_TRUE( contains( "abcabcabc", "abc" ) );
		EXPECT_TRUE( contains( "hello hello", "llo" ) );
	}

	TEST( StringOperations, IStartsWith )
	{
		// Basic functionality (case-insensitive)
		EXPECT_TRUE( istartsWith( "hello world", "hello" ) );
		EXPECT_TRUE( istartsWith( "hello world", "HELLO" ) );
		EXPECT_TRUE( istartsWith( "hello world", "Hello" ) );
		EXPECT_TRUE( istartsWith( "HELLO WORLD", "hello" ) );
		EXPECT_TRUE( istartsWith( "Hello World", "hElLo" ) );
		EXPECT_FALSE( istartsWith( "hello world", "world" ) );

		// Edge cases
		EXPECT_TRUE( istartsWith( "test", "" ) );	 // Empty prefix
		EXPECT_TRUE( istartsWith( "test", "test" ) ); // Exact match
		EXPECT_TRUE( istartsWith( "TEST", "test" ) ); // Exact match different case
		EXPECT_FALSE( istartsWith( "", "test" ) );	 // Empty string, non-empty prefix
		EXPECT_TRUE( istartsWith( "", "" ) );		 // Both empty

		// Prefix longer than string
		EXPECT_FALSE( istartsWith( "hi", "hello" ) );

		// Single characters
		EXPECT_TRUE( istartsWith( "A", "a" ) );
		EXPECT_FALSE( istartsWith( "a", "b" ) );

		// Real-world use cases
		EXPECT_TRUE( istartsWith( "HTTPS://example.com", "http" ) );   // Protocol detection
		EXPECT_TRUE( istartsWith( "Document.PDF", "doc" ) );		   // Case-insensitive filename
		EXPECT_TRUE( istartsWith( "Content-Type: text/html", "CONTENT" ) ); // HTTP headers
	}

	TEST( StringOperations, IStartsWith_CharOverload )
	{
		// Basic functionality with char (case-insensitive)
		EXPECT_TRUE( istartsWith( "hello world", 'h' ) );
		EXPECT_TRUE( istartsWith( "hello world", 'H' ) );
		EXPECT_TRUE( istartsWith( "Hello World", 'h' ) );
		EXPECT_TRUE( istartsWith( "HELLO", 'h' ) );
		EXPECT_FALSE( istartsWith( "hello world", 'w' ) );

		// Edge cases
		EXPECT_FALSE( istartsWith( "", 'a' ) ); // Empty string
		EXPECT_TRUE( istartsWith( "a", 'A' ) ); // Single character match different case
		EXPECT_TRUE( istartsWith( "A", 'a' ) ); // Single character match different case
		EXPECT_FALSE( istartsWith( "a", 'b' ) ); // Single character no match

		// Special characters (case doesn't apply)
		EXPECT_TRUE( istartsWith( "@mention", '@' ) );
		EXPECT_TRUE( istartsWith( " space", ' ' ) );
	}

	TEST( StringOperations, IStartsWith_CStringOverload )
	{
		// Basic functionality with const char* (case-insensitive)
		EXPECT_TRUE( istartsWith( "hello world", "HELLO" ) );
		EXPECT_TRUE( istartsWith( "TESTING", "test" ) );
		EXPECT_FALSE( istartsWith( "hello world", "WORLD" ) );

		// Edge cases
		EXPECT_TRUE( istartsWith( "test", "" ) );	 // Empty prefix
		EXPECT_FALSE( istartsWith( "", "test" ) );	 // Empty string
		EXPECT_TRUE( istartsWith( "TEST", "test" ) ); // Exact match different case

		// Literals
		const char* prefix = "PRE";
		EXPECT_TRUE( istartsWith( "prefix", prefix ) );
		EXPECT_FALSE( istartsWith( "suffix", prefix ) );
	}

	TEST( StringOperations, IEndsWith )
	{
		// Basic functionality (case-insensitive)
		EXPECT_TRUE( iendsWith( "hello world", "world" ) );
		EXPECT_TRUE( iendsWith( "hello world", "WORLD" ) );
		EXPECT_TRUE( iendsWith( "hello world", "World" ) );
		EXPECT_TRUE( iendsWith( "HELLO WORLD", "world" ) );
		EXPECT_TRUE( iendsWith( "Hello World", "WoRlD" ) );
		EXPECT_FALSE( iendsWith( "hello world", "hello" ) );

		// Edge cases
		EXPECT_TRUE( iendsWith( "test", "" ) );	   // Empty suffix
		EXPECT_TRUE( iendsWith( "test", "test" ) ); // Exact match
		EXPECT_TRUE( iendsWith( "TEST", "test" ) ); // Exact match different case
		EXPECT_FALSE( iendsWith( "", "test" ) );   // Empty string, non-empty suffix
		EXPECT_TRUE( iendsWith( "", "" ) );		   // Both empty

		// Suffix longer than string
		EXPECT_FALSE( iendsWith( "hi", "hello" ) );

		// Single characters
		EXPECT_TRUE( iendsWith( "A", "a" ) );
		EXPECT_FALSE( iendsWith( "a", "b" ) );

		// Real-world use cases
		EXPECT_TRUE( iendsWith( "file.TXT", ".txt" ) );		   // File extension
		EXPECT_TRUE( iendsWith( "Document.PDF", ".pdf" ) );   // Case-insensitive extension
		EXPECT_TRUE( iendsWith( "image.JPG", ".jpg" ) );	   // Image extension
	}

	TEST( StringOperations, IEndsWith_CharOverload )
	{
		// Basic functionality with char (case-insensitive)
		EXPECT_TRUE( iendsWith( "hello world", 'd' ) );
		EXPECT_TRUE( iendsWith( "hello world", 'D' ) );
		EXPECT_TRUE( iendsWith( "Hello World", 'd' ) );
		EXPECT_TRUE( iendsWith( "WORLD", 'd' ) );
		EXPECT_FALSE( iendsWith( "hello world", 'h' ) );

		// Edge cases
		EXPECT_FALSE( iendsWith( "", 'a' ) ); // Empty string
		EXPECT_TRUE( iendsWith( "a", 'A' ) ); // Single character match different case
		EXPECT_TRUE( iendsWith( "A", 'a' ) ); // Single character match different case
		EXPECT_FALSE( iendsWith( "a", 'b' ) ); // Single character no match

		// Special characters
		EXPECT_TRUE( iendsWith( "file.txt", 't' ) );
		EXPECT_TRUE( iendsWith( "question?", '?' ) );
	}

	TEST( StringOperations, IEndsWith_CStringOverload )
	{
		// Basic functionality with const char* (case-insensitive)
		EXPECT_TRUE( iendsWith( "hello world", "WORLD" ) );
		EXPECT_TRUE( iendsWith( "TESTING", "ing" ) );
		EXPECT_FALSE( iendsWith( "hello world", "HELLO" ) );

		// Edge cases
		EXPECT_TRUE( iendsWith( "test", "" ) );	   // Empty suffix
		EXPECT_FALSE( iendsWith( "", "test" ) );   // Empty string
		EXPECT_TRUE( iendsWith( "TEST", "test" ) ); // Exact match different case

		// Literals
		const char* suffix = "FIX";
		EXPECT_TRUE( iendsWith( "suffix", suffix ) );
		EXPECT_FALSE( iendsWith( "pretend", suffix ) );
	}

	TEST( StringOperations, IContains )
	{
		// Basic functionality (case-insensitive)
		EXPECT_TRUE( icontains( "hello world", "HELLO" ) );
		EXPECT_TRUE( icontains( "hello world", "WORLD" ) );
		EXPECT_TRUE( icontains( "hello world", "O W" ) );
		EXPECT_TRUE( icontains( "HELLO WORLD", "hello" ) );
		EXPECT_TRUE( icontains( "Hello World", "LLo WoR" ) );
		EXPECT_FALSE( icontains( "hello world", "xyz" ) );

		// Edge cases
		EXPECT_TRUE( icontains( "test", "" ) );	   // Empty substring
		EXPECT_TRUE( icontains( "test", "TEST" ) ); // Exact match different case
		EXPECT_FALSE( icontains( "", "test" ) );   // Empty string, non-empty substring
		EXPECT_TRUE( icontains( "", "" ) );		   // Both empty

		// Substring longer than string
		EXPECT_FALSE( icontains( "hi", "hello" ) );

		// Multiple occurrences
		EXPECT_TRUE( icontains( "hello HELLO", "hello" ) );
		EXPECT_TRUE( icontains( "AbCaBcAbC", "abc" ) );

		// Real-world use cases
		EXPECT_TRUE( icontains( "Content-Type: application/json", "TYPE" ) ); // HTTP headers
		EXPECT_TRUE( icontains( "User-Agent: Mozilla", "agent" ) );
		EXPECT_TRUE( icontains( "Search for KEYWORD in text", "keyword" ) ); // Search functionality
	}

	TEST( StringOperations, IContains_CharOverload )
	{
		// Basic functionality with char (case-insensitive)
		EXPECT_TRUE( icontains( "hello world", 'H' ) );
		EXPECT_TRUE( icontains( "hello world", 'O' ) );
		EXPECT_TRUE( icontains( "hello world", 'D' ) );
		EXPECT_TRUE( icontains( "HELLO WORLD", 'h' ) );
		EXPECT_FALSE( icontains( "hello world", 'X' ) );

		// Edge cases
		EXPECT_FALSE( icontains( "", 'a' ) ); // Empty string
		EXPECT_TRUE( icontains( "a", 'A' ) ); // Single character match different case
		EXPECT_TRUE( icontains( "A", 'a' ) ); // Single character match different case
		EXPECT_FALSE( icontains( "a", 'b' ) ); // Single character no match

		// Special characters (case doesn't apply)
		EXPECT_TRUE( icontains( "user@example.com", '@' ) );
		EXPECT_TRUE( icontains( "path/to/file", '/' ) );

		// Multiple occurrences
		EXPECT_TRUE( icontains( "HeLLo", 'l' ) );
		EXPECT_TRUE( icontains( "HeLLo", 'L' ) );
	}

	TEST( StringOperations, IContains_CStringOverload )
	{
		// Basic functionality with const char* (case-insensitive)
		EXPECT_TRUE( icontains( "hello world", "HELLO" ) );
		EXPECT_TRUE( icontains( "hello world", "WORLD" ) );
		EXPECT_TRUE( icontains( "hello world", "O W" ) );
		EXPECT_FALSE( icontains( "hello world", "XYZ" ) );

		// Edge cases
		EXPECT_TRUE( icontains( "test", "" ) );	   // Empty substring
		EXPECT_FALSE( icontains( "", "test" ) );   // Empty string
		EXPECT_TRUE( icontains( "TEST", "test" ) ); // Exact match different case

		// Literals
		const char* substring = "SUB";
		EXPECT_TRUE( icontains( "substring", substring ) );
		EXPECT_FALSE( icontains( "string", substring ) );

		// Multiple occurrences
		EXPECT_TRUE( icontains( "AbCaBcAbC", "abc" ) );
		EXPECT_TRUE( icontains( "HELLO hello", "LLO" ) );
	}

	TEST( StringOperations, Equals )
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

	TEST( StringOperations, IEquals )
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

	TEST( StringOperations, Count_Substring )
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

	TEST( StringOperations, CountOverlapping_Substring )
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

	TEST( StringOperations, Count_Character )
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

	TEST( StringOperations, Replace )
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

	TEST( StringOperations, ReplaceAll )
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

	TEST( StringOperations, Join_Container )
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

	TEST( StringOperations, Join_Iterator )
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

	TEST( StringOperations, PadLeft )
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

	TEST( StringOperations, PadRight )
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

	TEST( StringOperations, Center )
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

	TEST( StringOperations, Repeat )
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

	TEST( StringOperations, Reverse )
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

	TEST( StringOperations, IndexOf )
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

	TEST( StringOperations, LastIndexOf )
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

	TEST( StringOperations, IndexOf_CharOverload )
	{
		constexpr auto npos = std::string_view::npos;

		// Basic search with char
		EXPECT_EQ( indexOf( "hello world", 'o' ), 4 );	// First 'o'
		EXPECT_EQ( indexOf( "hello world", 'h' ), 0 );	// At start
		EXPECT_EQ( indexOf( "hello world", 'd' ), 10 ); // At end

		// Not found
		EXPECT_EQ( indexOf( "hello world", 'x' ), npos );
		EXPECT_EQ( indexOf( "hello world", 'H' ), npos ); // Case sensitive

		// Empty string
		EXPECT_EQ( indexOf( "", 'a' ), npos );

		// Single character string
		EXPECT_EQ( indexOf( "a", 'a' ), 0 );
		EXPECT_EQ( indexOf( "a", 'b' ), npos );

		// Special characters
		EXPECT_EQ( indexOf( "user@example.com", '@' ), 4 );
		EXPECT_EQ( indexOf( "path/to/file", '/' ), 4 );
		EXPECT_EQ( indexOf( "key=value", '=' ), 3 );
		EXPECT_EQ( indexOf( "hello world", ' ' ), 5 );

		// Multiple occurrences (returns first)
		EXPECT_EQ( indexOf( "hello", 'l' ), 2 );
		EXPECT_EQ( indexOf( "aaa", 'a' ), 0 );
	}

	TEST( StringOperations, LastIndexOf_CharOverload )
	{
		constexpr auto npos = std::string_view::npos;

		// Basic search with char (returns last)
		EXPECT_EQ( lastIndexOf( "hello world", 'o' ), 7 );	// Last 'o'
		EXPECT_EQ( lastIndexOf( "hello world", 'h' ), 0 );	// Only one
		EXPECT_EQ( lastIndexOf( "hello world", 'd' ), 10 ); // At end

		// Not found
		EXPECT_EQ( lastIndexOf( "hello world", 'x' ), npos );
		EXPECT_EQ( lastIndexOf( "hello world", 'H' ), npos ); // Case sensitive

		// Empty string
		EXPECT_EQ( lastIndexOf( "", 'a' ), npos );

		// Single character string
		EXPECT_EQ( lastIndexOf( "a", 'a' ), 0 );
		EXPECT_EQ( lastIndexOf( "a", 'b' ), npos );

		// Special characters
		EXPECT_EQ( lastIndexOf( "file.backup.txt", '.' ), 11 );
		EXPECT_EQ( lastIndexOf( "/usr/local/bin", '/' ), 10 );
		EXPECT_EQ( lastIndexOf( "192.168.1.1", '.' ), 9 );

		// Multiple occurrences
		EXPECT_EQ( lastIndexOf( "hello", 'l' ), 3 );
		EXPECT_EQ( lastIndexOf( "aaa", 'a' ), 2 );
	}

	//----------------------------------------------
	// String trimming
	//----------------------------------------------

	//-----------------------------
	// Non-allocating
	//-----------------------------

	TEST( StringOperations, TrimStart )
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

	TEST( StringOperations, TrimEnd )
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

	TEST( StringOperations, Trim )
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

	TEST( StringOperations, ToLowerString )
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

	TEST( StringOperations, ToUpperString )
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

	TEST( StringOperations, ToLowerChar )
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

	TEST( StringOperations, ToUpperChar )
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
} // namespace nfx::string::test
