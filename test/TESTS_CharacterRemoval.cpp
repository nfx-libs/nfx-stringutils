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
 * @file TESTS_CharacterRemoval.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Character & String Removal
    //=====================================================================

    TEST( CharacterRemoval, RemoveAll_Character )
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

    TEST( CharacterRemoval, RemoveAll_Substring )
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

    TEST( CharacterRemoval, RemoveIf_Predicate )
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

    TEST( CharacterRemoval, RemoveWhitespace )
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

    TEST( CharacterRemoval, CollapseWhitespace )
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

    TEST( CharacterRemoval, EdgeCases )
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
} // namespace nfx::string::test
