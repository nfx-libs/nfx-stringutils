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
 * @file Tests_StringComparison.cpp
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

    TEST( StringComparison, NaturalSort_BasicNumericOrdering )
    {
        // Basic numeric comparisons
        EXPECT_TRUE( naturalSort( "file1.txt", "file2.txt" ) );
        EXPECT_TRUE( naturalSort( "file2.txt", "file10.txt" ) );
        EXPECT_FALSE( naturalSort( "file10.txt", "file2.txt" ) );
        EXPECT_TRUE( naturalSort( "v1.0", "v2.0" ) );
        EXPECT_TRUE( naturalSort( "v1.9", "v1.10" ) );
        EXPECT_FALSE( naturalSort( "file123", "file123" ) ); // Equal strings
    }

    TEST( StringComparison, NaturalSort_LeadingZeros )
    {
        // Leading zeros should be ignored in numeric parts
        EXPECT_TRUE( naturalSort( "file001.txt", "file002.txt" ) );
        EXPECT_TRUE( naturalSort( "file01.txt", "file2.txt" ) );
        EXPECT_FALSE( naturalSort( "file002.txt", "file001.txt" ) );
        EXPECT_TRUE( naturalSort( "00001", "2" ) );
    }

    TEST( StringComparison, NaturalSort_MultipleNumbers )
    {
        EXPECT_TRUE( naturalSort( "page1section2", "page1section10" ) );
        EXPECT_TRUE( naturalSort( "v2.3.4", "v2.3.10" ) );
        EXPECT_TRUE( naturalSort( "1.2.3", "1.2.10" ) );
        EXPECT_FALSE( naturalSort( "10.5.1", "2.99.99" ) );
    }

    TEST( StringComparison, NaturalSort_CaseInsensitiveText )
    {
        // naturalSort is now case-SENSITIVE (uses naturalCompare)
        EXPECT_TRUE( naturalSort( "File1.txt", "file1.txt" ) ); // 'F' < 'f' in ASCII
        EXPECT_TRUE( naturalSort( "APPLE", "banana" ) );        // 'A' < 'b'
        EXPECT_TRUE( naturalSort( "Test", "test2" ) );          // 'T' < 't'
        EXPECT_TRUE( naturalSort( "ZEBRA", "apple" ) );         // 'Z' < 'a' in ASCII
    }

    TEST( StringComparison, NaturalSort_MixedContent )
    {
        EXPECT_TRUE( naturalSort( "test", "test1" ) );
        EXPECT_TRUE( naturalSort( "abc", "abc123" ) );
        EXPECT_FALSE( naturalSort( "xyz9", "xyz" ) );
        EXPECT_TRUE( naturalSort( "file", "file0" ) );
    }

    TEST( StringComparison, NaturalSort_EdgeCases )
    {
        EXPECT_FALSE( naturalSort( "", "" ) );   // Equal empty strings
        EXPECT_FALSE( naturalSort( "a", "" ) );  // Non-empty > empty
        EXPECT_TRUE( naturalSort( "", "a" ) );   // Empty < non-empty
        EXPECT_TRUE( naturalSort( "0", "00" ) ); // Shorter wins when numbers equal
        EXPECT_TRUE( naturalSort( "1", "10" ) );
        EXPECT_FALSE( naturalSort( "abc", "abc" ) );
    }

    TEST( StringComparison, NaturalSort_RealWorldFilenames )
    {
        // Simulate file sorting
        EXPECT_TRUE( naturalSort( "chapter1.doc", "chapter2.doc" ) );
        EXPECT_TRUE( naturalSort( "chapter2.doc", "chapter10.doc" ) );
        EXPECT_TRUE( naturalSort( "image1.png", "image10.png" ) );
        EXPECT_TRUE( naturalSort( "version1.2.3", "version1.2.10" ) );

        // Real-world mixed case scenarios
        EXPECT_TRUE( naturalSort( "Document1.pdf", "document2.pdf" ) );
        EXPECT_TRUE( naturalSort( "Photo_001.jpg", "Photo_002.jpg" ) );
    }

    TEST( StringComparison, NaturalSort_PrefixOrdering )
    {
        // Shorter string should come before longer when it's a prefix
        EXPECT_TRUE( naturalSort( "test", "test1" ) );
        EXPECT_TRUE( naturalSort( "file", "file.txt" ) );
        EXPECT_FALSE( naturalSort( "testing", "test" ) );
        EXPECT_TRUE( naturalSort( "v1", "v1.0" ) );
    }

    TEST( StringComparison, INaturalCompare_BasicNumericOrdering )
    {
        // Basic case-insensitive numeric comparisons
        EXPECT_LT( inaturalCompare( "File1.txt", "file2.txt" ), 0 );
        EXPECT_LT( inaturalCompare( "FILE2.txt", "file10.txt" ), 0 );
        EXPECT_GT( inaturalCompare( "file10.txt", "FILE2.txt" ), 0 );
        EXPECT_LT( inaturalCompare( "V1.0", "v2.0" ), 0 );
        EXPECT_LT( inaturalCompare( "v1.9", "V1.10" ), 0 );
        EXPECT_EQ( 0, inaturalCompare( "File123", "file123" ) ); // Equal when case-insensitive
    }

    TEST( StringComparison, INaturalCompare_LeadingZeros )
    {
        // Leading zeros should be ignored
        EXPECT_LT( inaturalCompare( "File001.txt", "file002.txt" ), 0 );
        EXPECT_LT( inaturalCompare( "FILE01.txt", "file2.txt" ), 0 );
        EXPECT_GT( inaturalCompare( "file002.txt", "FILE001.txt" ), 0 );
        EXPECT_LT( inaturalCompare( "00001", "2" ), 0 );
    }

    TEST( StringComparison, INaturalCompare_CaseInsensitive )
    {
        // Non-numeric parts should be case-insensitive
        EXPECT_EQ( 0, inaturalCompare( "Test", "test" ) );
        EXPECT_EQ( 0, inaturalCompare( "HELLO", "hello" ) );
        EXPECT_LT( inaturalCompare( "Apple", "BANANA" ), 0 );
        EXPECT_GT( inaturalCompare( "ZEBRA", "apple" ), 0 );
    }

    TEST( StringComparison, INaturalCompare_MultipleNumbers )
    {
        EXPECT_LT( inaturalCompare( "Page1Section2", "page1section10" ), 0 );
        EXPECT_LT( inaturalCompare( "V2.3.4", "v2.3.10" ), 0 );
        EXPECT_LT( inaturalCompare( "1.2.3", "1.2.10" ), 0 );
        EXPECT_GT( inaturalCompare( "10.5.1", "2.99.99" ), 0 );
    }

    TEST( StringComparison, INaturalSort_BasicOrdering )
    {
        // Basic case-insensitive natural sort
        EXPECT_TRUE( inaturalSort( "File1.txt", "file2.txt" ) );
        EXPECT_TRUE( inaturalSort( "FILE2.txt", "file10.txt" ) );
        EXPECT_FALSE( inaturalSort( "file10.txt", "FILE2.txt" ) );
        EXPECT_FALSE( inaturalSort( "Test", "test" ) ); // Equal strings
    }

    TEST( StringComparison, INaturalSort_RealWorldFilenames )
    {
        // Case-insensitive file sorting
        EXPECT_TRUE( inaturalSort( "Document1.pdf", "DOCUMENT2.pdf" ) );
        EXPECT_TRUE( inaturalSort( "CHAPTER2.doc", "chapter10.doc" ) );
        EXPECT_TRUE( inaturalSort( "Image1.PNG", "image10.png" ) );
        EXPECT_TRUE( inaturalSort( "Version1.2.3", "VERSION1.2.10" ) );
    }

    TEST( StringComparison, INaturalSort_MixedContent )
    {
        EXPECT_TRUE( inaturalSort( "TEST", "test1" ) );
        EXPECT_TRUE( inaturalSort( "abc", "ABC123" ) );
        EXPECT_FALSE( inaturalSort( "XYZ9", "xyz" ) );
        EXPECT_TRUE( inaturalSort( "File", "FILE0" ) );
    }
} // namespace nfx::string::test
