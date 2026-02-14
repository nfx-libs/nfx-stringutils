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
 * @file Tests_PredicateOperations.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Predicate-Based Operations
    //=====================================================================

    TEST( PredicateOperations, TrimStartIf )
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

    TEST( PredicateOperations, TrimEndIf )
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

    TEST( PredicateOperations, TrimIf )
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

    TEST( PredicateOperations, CountIf )
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

    TEST( PredicateOperations, FindIf )
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

    TEST( PredicateOperations, FindIfNot )
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

    TEST( PredicateOperations, ReplaceIf )
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

    TEST( PredicateOperations, ComplexPredicates )
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
        std::string_view text = "  123abc456  ";
        auto trimmed = trimIf( text, isWhitespace );
        auto digit_count = countIf( trimmed, isDigit );
        auto first_alpha = findIf( trimmed, isAlpha );
        auto replaced = replaceIf( trimmed, isDigit, '#' );

        EXPECT_EQ( "123abc456", trimmed );
        EXPECT_EQ( 6, digit_count );
        EXPECT_EQ( 3, first_alpha );
        EXPECT_EQ( "###abc###", replaced );
    }

    TEST( PredicateOperations, EdgeCasesAndRobustness )
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

    //----------------------------------------------
    // Round-trip conversion tests
    //----------------------------------------------

    TEST( PredicateOperations, RoundTripConversion )
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

    TEST( PredicateOperations, EdgeCases )
    {
        // Edge ASCII boundaries for case conversion
        std::string edgeCases = "@[`{";               // Characters around A-Z and a-z ranges
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
} // namespace nfx::string::test
