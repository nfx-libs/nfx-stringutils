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
 * @file TESTS_EdgeCases.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Edge cases tests
    //=====================================================================

    TEST( EdgeCases, Unicode )
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
        EXPECT_TRUE( iequals( "ASCII", "ascii" ) );         // Works for ASCII only

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
        const std::string composed = "é";   // Single composed character U+00E9
        const std::string decomposed = "é"; // e + combining acute accent U+0065 + U+0301
        // These might be visually identical but have different byte representations
        // The library correctly treats them as different byte sequences

        // Boolean parsing with Unicode characters should fail gracefully
        bool boolResult{ false };
        EXPECT_FALSE( fromString<bool>( "真", boolResult ) );   // Chinese "true"
        EXPECT_FALSE( fromString<bool>( "はい", boolResult ) ); // Japanese "yes"
        EXPECT_FALSE( fromString<bool>( "да", boolResult ) );   // Russian "yes"
        EXPECT_FALSE( fromString<bool>( "نعم", boolResult ) );  // Arabic "yes"

        // Numeric parsing with Unicode should also fail gracefully
        int intResult{ 0 };
        EXPECT_FALSE( fromString<int>( "１２３", intResult ) ); // Full-width numbers
        EXPECT_FALSE( fromString<int>( "۱۲۳", intResult ) );    // Arabic-Indic digits

        // Performance test with Unicode strings
        const std::string rocket_emoji{ "🚀" };                // Single rocket emoji
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

    TEST( EdgeCases, LargeStrings )
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

    TEST( EdgeCases, SpecialCharacters )
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

    TEST( EdgeCases, NullTerminatedStrings )
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
} // namespace nfx::string::test
