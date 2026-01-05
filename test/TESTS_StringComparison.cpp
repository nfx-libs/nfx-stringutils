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
 * @file TESTS_StringComparison.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // String comparison tests
    //=====================================================================

    TEST( StringComparison, CompareIgnoreCase_Basic )
    {
        EXPECT_EQ( 0, compareIgnoreCase( "hello", "HELLO" ) );
        EXPECT_EQ( 0, compareIgnoreCase( "World", "wOrLd" ) );
        EXPECT_EQ( 0, compareIgnoreCase( "ABC123", "abc123" ) );
        EXPECT_LT( compareIgnoreCase( "apple", "BANANA" ), 0 );
        EXPECT_GT( compareIgnoreCase( "zebra", "APPLE" ), 0 );
    }

    TEST( StringComparison, CompareIgnoreCase_LengthDifference )
    {
        // Length only matters when prefixes match
        EXPECT_LT( compareIgnoreCase( "test", "TESTING" ), 0 ); // "test" is prefix of "testing"
        EXPECT_GT( compareIgnoreCase( "testing", "TEST" ), 0 ); // "testing" is longer
        EXPECT_EQ( 0, compareIgnoreCase( "", "" ) );
        EXPECT_GT( compareIgnoreCase( "a", "" ), 0 );
        EXPECT_LT( compareIgnoreCase( "", "A" ), 0 );
    }

    TEST( StringComparison, CompareIgnoreCase_SpecialCharacters )
    {
        EXPECT_EQ( 0, compareIgnoreCase( "Test-123", "test-123" ) );
        EXPECT_LT( compareIgnoreCase( "file_1.txt", "FILE_2.TXT" ), 0 );
        EXPECT_GT( compareIgnoreCase( "CONFIG.INI", "config.dat" ), 0 );
    }

    TEST( StringComparison, CompareIgnoreCase_Sorting )
    {
        // Verify sorting behavior
        EXPECT_LT( compareIgnoreCase( "apple", "BANANA" ), 0 );
        EXPECT_LT( compareIgnoreCase( "Banana", "CHERRY" ), 0 );
        EXPECT_GT( compareIgnoreCase( "zebra", "APPLE" ), 0 );
    }

    TEST( StringComparison, NaturalCompare_BasicNumericSorting )
    {
        EXPECT_LT( naturalCompare( "file2.txt", "file10.txt" ), 0 );
        EXPECT_GT( naturalCompare( "file10.txt", "file2.txt" ), 0 );
        EXPECT_LT( naturalCompare( "v1.0", "v2.0" ), 0 );
        EXPECT_LT( naturalCompare( "v1.9", "v1.10" ), 0 );
        EXPECT_EQ( 0, naturalCompare( "file123", "file123" ) );
    }

    TEST( StringComparison, NaturalCompare_MultipleNumbers )
    {
        EXPECT_LT( naturalCompare( "page1section2", "page1section10" ), 0 );
        EXPECT_LT( naturalCompare( "v2.3.4", "v2.3.10" ), 0 );
        EXPECT_LT( naturalCompare( "1.2.3", "1.2.10" ), 0 );
        EXPECT_GT( naturalCompare( "10.5.1", "2.99.99" ), 0 );
    }

    TEST( StringComparison, NaturalCompare_MixedContent )
    {
        EXPECT_LT( naturalCompare( "test", "test1" ), 0 );
        EXPECT_LT( naturalCompare( "abc", "abc123" ), 0 );
        EXPECT_GT( naturalCompare( "xyz9", "xyz" ), 0 );
        EXPECT_LT( naturalCompare( "file", "file0" ), 0 );
    }

    TEST( StringComparison, NaturalCompare_EdgeCases )
    {
        EXPECT_EQ( 0, naturalCompare( "", "" ) );
        EXPECT_GT( naturalCompare( "a", "" ), 0 );
        EXPECT_LT( naturalCompare( "", "a" ), 0 );
        EXPECT_LT( naturalCompare( "0", "00" ), 0 );
        EXPECT_LT( naturalCompare( "1", "10" ), 0 );
    }

    TEST( StringComparison, NaturalCompare_RealWorldFilenames )
    {
        // Simulate file sorting
        EXPECT_LT( naturalCompare( "chapter1.doc", "chapter2.doc" ), 0 );
        EXPECT_LT( naturalCompare( "chapter2.doc", "chapter10.doc" ), 0 );
        EXPECT_LT( naturalCompare( "image1.png", "image10.png" ), 0 );
        EXPECT_LT( naturalCompare( "version1.2.3", "version1.2.10" ), 0 );
    }

    TEST( StringComparison, CommonPrefix_BasicMatching )
    {
        EXPECT_EQ( "hello ", commonPrefix( "hello world", "hello there" ) ); // Include space
        EXPECT_EQ( "test", commonPrefix( "testing", "tester" ) );
        EXPECT_EQ( "", commonPrefix( "abc", "xyz" ) );
        EXPECT_EQ( "same", commonPrefix( "same", "same" ) );
    }

    TEST( StringComparison, CommonPrefix_PartialMatches )
    {
        EXPECT_EQ( "/usr/local/", commonPrefix( "/usr/local/bin", "/usr/local/lib" ) ); // Include trailing /
        EXPECT_EQ( "file_", commonPrefix( "file_1.txt", "file_2.txt" ) );
        EXPECT_EQ( "prefix", commonPrefix( "prefix123", "prefix456" ) );
    }

    TEST( StringComparison, CommonPrefix_EdgeCases )
    {
        EXPECT_EQ( "", commonPrefix( "", "" ) );
        EXPECT_EQ( "", commonPrefix( "abc", "" ) );
        EXPECT_EQ( "", commonPrefix( "", "xyz" ) );
        EXPECT_EQ( "a", commonPrefix( "a", "abc" ) );
        EXPECT_EQ( "abc", commonPrefix( "abc", "abc" ) );
    }

    TEST( StringComparison, CommonPrefix_CaseSensitive )
    {
        EXPECT_EQ( "", commonPrefix( "Hello", "hello" ) );
        EXPECT_EQ( "Test", commonPrefix( "Testing", "Tester" ) );
    }

    TEST( StringComparison, CommonSuffix_BasicMatching )
    {
        EXPECT_EQ( ".txt", commonSuffix( "file1.txt", "file2.txt" ) );
        EXPECT_EQ( "ing", commonSuffix( "testing", "running" ) );
        EXPECT_EQ( "", commonSuffix( "abc", "xyz" ) );
        EXPECT_EQ( "same", commonSuffix( "same", "same" ) );
    }

    TEST( StringComparison, CommonSuffix_PartialMatches )
    {
        EXPECT_EQ( "/data", commonSuffix( "/usr/local/data", "/home/user/data" ) );
        EXPECT_EQ( "_test.cpp", commonSuffix( "unit_test.cpp", "integration_test.cpp" ) );
        EXPECT_EQ( "123", commonSuffix( "abc123", "xyz123" ) );
    }

    TEST( StringComparison, CommonSuffix_EdgeCases )
    {
        EXPECT_EQ( "", commonSuffix( "", "" ) );
        EXPECT_EQ( "", commonSuffix( "abc", "" ) );
        EXPECT_EQ( "", commonSuffix( "", "xyz" ) );
        EXPECT_EQ( "c", commonSuffix( "abc", "c" ) );
        EXPECT_EQ( "abc", commonSuffix( "abc", "abc" ) );
    }

    TEST( StringComparison, CommonSuffix_CaseSensitive )
    {
        EXPECT_EQ( "ello", commonSuffix( "Hello", "hello" ) );       // Case matters: 'H' != 'h', but "ello" matches
        EXPECT_EQ( "esting", commonSuffix( "Testing", "testing" ) ); // 'T' != 't', but "esting" matches
    }
} // namespace nfx::string::test
