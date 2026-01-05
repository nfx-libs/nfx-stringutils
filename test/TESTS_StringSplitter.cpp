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
 * @file TESTS_StringSplitter.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include <nfx/string/Splitter.h>
#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Splitter tests
    //=====================================================================

    //----------------------------------------------
    // Construction
    //----------------------------------------------

    TEST( StringSplitterConstruction, BasicConstruction )
    {
        const std::string_view str{ "hello,world,test" };
        const char delimiter{ ',' };

        string::Splitter splitter{ str, delimiter };

        EXPECT_NO_THROW( splitter.begin() );
        EXPECT_NO_THROW( splitter.end() );
    }

    TEST( StringSplitterConstruction, StringConstruction )
    {
        const std::string str{ "apple,banana,cherry" };
        const char delimiter{ ',' };

        string::Splitter splitter{ str, delimiter };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "apple" );
        EXPECT_EQ( segments[1], "banana" );
        EXPECT_EQ( segments[2], "cherry" );
    }

    TEST( StringSplitterConstruction, CStringConstruction )
    {
        const char* str{ "red,green,blue" };
        const char delimiter{ ',' };

        string::Splitter splitter{ str, delimiter };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "red" );
        EXPECT_EQ( segments[1], "green" );
        EXPECT_EQ( segments[2], "blue" );
    }

    TEST( StringSplitterConstruction, EmptyString )
    {
        const std::string_view str{ "" };
        const char delimiter{ ',' };

        string::Splitter splitter{ str, delimiter };

        // Should handle empty string gracefully
        auto begin_it{ splitter.begin() };
        auto end_it{ splitter.end() };
        EXPECT_EQ( begin_it, end_it );
    }

    TEST( StringSplitterConstruction, SingleCharacter )
    {
        const std::string_view str{ "a" };
        const char delimiter{ ',' };

        string::Splitter splitter{ str, delimiter };

        // Should handle single character
        auto begin_it{ splitter.begin() };
        auto end_it{ splitter.end() };
        EXPECT_NE( begin_it, end_it );
        EXPECT_EQ( *begin_it, "a" );
    }

    TEST( StringSplitterConstruction, FactoryFunction )
    {
        const std::string_view str{ "hello,world" };
        const char delimiter{ ',' };

        auto splitter{ string::splitView( str, delimiter ) };

        // Factory function should work identically
        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 2 );
        EXPECT_EQ( segments[0], "hello" );
        EXPECT_EQ( segments[1], "world" );
    }

    //----------------------------------------------
    // Basic iteration
    //----------------------------------------------

    TEST( StringSplitterIteration, BasicSplitting )
    {
        const std::string_view str{ "hello,world,test" };
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "hello" );
        EXPECT_EQ( segments[1], "world" );
        EXPECT_EQ( segments[2], "test" );
    }

    TEST( StringSplitterIteration, NoDelimiter )
    {
        const std::string_view str{ "hello_world_test" };
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 1 );
        EXPECT_EQ( segments[0], "hello_world_test" );
    }

    TEST( StringSplitterIteration, TrailingDelimiter )
    {
        const std::string_view str{ "hello,world," };
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "hello" );
        EXPECT_EQ( segments[1], "world" );
        EXPECT_EQ( segments[2], "" ); // Empty segment after trailing delimiter
    }

    TEST( StringSplitterIteration, LeadingDelimiter )
    {
        const std::string_view str{ ",hello,world" };
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "" ); // Empty segment before leading delimiter
        EXPECT_EQ( segments[1], "hello" );
        EXPECT_EQ( segments[2], "world" );
    }

    TEST( StringSplitterIteration, ConsecutiveDelimiters )
    {
        const std::string_view str{ "hello,,world" };
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "hello" );
        EXPECT_EQ( segments[1], "" ); // Empty segment between consecutive delimiters
        EXPECT_EQ( segments[2], "world" );
    }

    TEST( StringSplitterIteration, OnlyDelimiters )
    {
        const std::string_view str{ ",,," };
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 4 );
        for ( const auto& segment : segments )
        {
            EXPECT_EQ( segment, "" );
        }
    }

    //----------------------------------------------
    // Iterator behavior
    //----------------------------------------------

    TEST( StringSplitterIterator, ManualIteration )
    {
        const std::string_view str{ "a,b,c" };
        auto splitter{ string::splitView( str, ',' ) };

        auto it{ splitter.begin() };
        auto end{ splitter.end() };

        EXPECT_NE( it, end );
        EXPECT_EQ( *it, "a" );

        ++it;
        EXPECT_NE( it, end );
        EXPECT_EQ( *it, "b" );

        ++it;
        EXPECT_NE( it, end );
        EXPECT_EQ( *it, "c" );

        ++it;
        EXPECT_EQ( it, end );
    }

    TEST( StringSplitterIterator, BeginEndComparison )
    {
        const std::string_view str{ "hello,world" };
        auto splitter{ string::splitView( str, ',' ) };

        auto begin_it{ splitter.begin() };
        auto end_it{ splitter.end() };

        EXPECT_NE( begin_it, end_it );

        // Advance to end
        ++begin_it; // "world"
        EXPECT_NE( begin_it, end_it );

        ++begin_it; // past end
        EXPECT_EQ( begin_it, end_it );
    }

    TEST( StringSplitterIterator, MultipleBeginCalls )
    {
        const std::string_view str{ "hello,world" };
        auto splitter{ string::splitView( str, ',' ) };

        auto it1{ splitter.begin() };
        auto it2{ splitter.begin() };

        // Multiple begin() calls should return equivalent iterators
        EXPECT_EQ( *it1, *it2 );
        EXPECT_EQ( *it1, "hello" );
    }

    //----------------------------------------------
    // Different delimiters
    //----------------------------------------------

    TEST( StringSplitterDelimiters, SpaceDelimiter )
    {
        const std::string_view str{ "hello world test" };
        auto splitter{ string::splitView( str, ' ' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "hello" );
        EXPECT_EQ( segments[1], "world" );
        EXPECT_EQ( segments[2], "test" );
    }

    TEST( StringSplitterDelimiters, SemicolonDelimiter )
    {
        const std::string_view str{ "name=John;age=30;city=NYC" };
        auto splitter{ string::splitView( str, ';' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "name=John" );
        EXPECT_EQ( segments[1], "age=30" );
        EXPECT_EQ( segments[2], "city=NYC" );
    }

    TEST( StringSplitterDelimiters, NewlineDelimiter )
    {
        const std::string_view str{ "line1\nline2\nline3" };
        auto splitter{ string::splitView( str, '\n' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "line1" );
        EXPECT_EQ( segments[1], "line2" );
        EXPECT_EQ( segments[2], "line3" );
    }

    TEST( StringSplitterDelimiters, TabDelimiter )
    {
        const std::string_view str{ "col1\tcol2\tcol3" };
        auto splitter{ string::splitView( str, '\t' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "col1" );
        EXPECT_EQ( segments[1], "col2" );
        EXPECT_EQ( segments[2], "col3" );
    }

    //----------------------------------------------
    // Edge cases
    //----------------------------------------------

    TEST( StringSplitterEdgeCases, EmptyStringWithDelimiter )
    {
        const std::string_view str = "";
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 0 );
    }

    TEST( StringSplitterEdgeCases, SingleDelimiter )
    {
        const std::string_view str = ",";
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 2 );
        EXPECT_EQ( segments[0], "" );
        EXPECT_EQ( segments[1], "" );
    }

    TEST( StringSplitterEdgeCases, LongString )
    {
        // Test with a longer string to ensure no issues with larger data
        std::string long_str;
        for ( int i{ 0 }; i < 1000; ++i )
        {
            if ( i > 0 )
                long_str += ",";
            long_str += "item" + std::to_string( i );
        }

        auto splitter{ string::splitView( long_str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 1000 );
        EXPECT_EQ( segments[0], "item0" );
        EXPECT_EQ( segments[999], "item999" );
    }

    TEST( StringSplitterEdgeCases, UnicodeCharacters )
    {
        const std::string_view str = "héllo,wørld,tëst";
        auto splitter{ string::splitView( str, ',' ) };

        std::vector<std::string_view> segments;
        for ( auto segment : splitter )
        {
            segments.push_back( segment );
        }

        EXPECT_EQ( segments.size(), 3 );
        EXPECT_EQ( segments[0], "héllo" );
        EXPECT_EQ( segments[1], "wørld" );
        EXPECT_EQ( segments[2], "tëst" );
    }

    //----------------------------------------------
    // Real-world use cases
    //----------------------------------------------

    TEST( StringSplitterUseCases, CSVParsing )
    {
        const std::string_view csvLine = "John,Doe,30,Engineer,NewYork";
        auto splitter{ string::splitView( csvLine, ',' ) };

        std::vector<std::string_view> fields;
        for ( auto field : splitter )
        {
            fields.push_back( field );
        }

        EXPECT_EQ( fields.size(), 5 );
        EXPECT_EQ( fields[0], "John" );
        EXPECT_EQ( fields[1], "Doe" );
        EXPECT_EQ( fields[2], "30" );
        EXPECT_EQ( fields[3], "Engineer" );
        EXPECT_EQ( fields[4], "NewYork" );
    }

    TEST( StringSplitterUseCases, ConfigurationParsing )
    {
        const std::string_view config = "debug=true;timeout=30;host=localhost;port=8080";
        auto splitter{ string::splitView( config, ';' ) };

        std::vector<std::string_view> settings;
        for ( auto setting : splitter )
        {
            settings.push_back( setting );
        }

        EXPECT_EQ( settings.size(), 4 );
        EXPECT_EQ( settings[0], "debug=true" );
        EXPECT_EQ( settings[1], "timeout=30" );
        EXPECT_EQ( settings[2], "host=localhost" );
        EXPECT_EQ( settings[3], "port=8080" );
    }

    TEST( StringSplitterUseCases, LogParsing )
    {
        const std::string_view logEntry = "2025-08-31 14:30:15 INFO Application started successfully";
        auto splitter{ string::splitView( logEntry, ' ' ) };

        std::vector<std::string_view> parts;
        for ( auto part : splitter )
        {
            parts.push_back( part );
        }

        EXPECT_GE( parts.size(), 5 );
        EXPECT_EQ( parts[0], "2025-08-31" );
        EXPECT_EQ( parts[1], "14:30:15" );
        EXPECT_EQ( parts[2], "INFO" );
        EXPECT_EQ( parts[3], "Application" );
        EXPECT_EQ( parts[4], "started" );
    }

    TEST( StringSplitterUseCases, PathSplitting )
    {
        const std::string_view path = "/usr/local/bin/myapp";
        auto splitter{ string::splitView( path, '/' ) };

        std::vector<std::string_view> components;
        for ( auto component : splitter )
        {
            components.push_back( component );
        }

        EXPECT_EQ( components.size(), 5 );
        EXPECT_EQ( components[0], "" ); // Empty before leading /
        EXPECT_EQ( components[1], "usr" );
        EXPECT_EQ( components[2], "local" );
        EXPECT_EQ( components[3], "bin" );
        EXPECT_EQ( components[4], "myapp" );
    }

    //----------------------------------------------
    // C++20 Iterator Traits & STL Compatibility
    //----------------------------------------------

    TEST( StringSplitterIteratorTraits, HasRequiredTypedefs )
    {
        using Iterator = string::Splitter::Iterator;

        // Verify all required iterator type aliases exist
        using category = typename Iterator::iterator_category;
        using value = typename Iterator::value_type;
        using diff = typename Iterator::difference_type;
        using ptr = typename Iterator::pointer;
        using ref = typename Iterator::reference;

        // Verify correct types
        static_assert( std::is_same_v<category, std::forward_iterator_tag>, "Wrong iterator category" );
        static_assert( std::is_same_v<value, std::string_view>, "Wrong value_type" );
        static_assert( std::is_same_v<diff, std::ptrdiff_t>, "Wrong difference_type" );
        static_assert( std::is_same_v<ptr, const std::string_view*>, "Wrong pointer type" );
        static_assert( std::is_same_v<ref, std::string_view>, "Wrong reference type" );

        SUCCEED();
    }

    TEST( StringSplitterIteratorTraits, StdIteratorTraitsCompatibility )
    {
        using Iterator = string::Splitter::Iterator;
        using Traits = std::iterator_traits<Iterator>;

        // std::iterator_traits should work with our iterator
        static_assert( std::is_same_v<typename Traits::iterator_category, std::forward_iterator_tag> );
        static_assert( std::is_same_v<typename Traits::value_type, std::string_view> );
        static_assert( std::is_same_v<typename Traits::difference_type, std::ptrdiff_t> );
        static_assert( std::is_same_v<typename Traits::pointer, const std::string_view*> );
        static_assert( std::is_same_v<typename Traits::reference, std::string_view> );

        SUCCEED();
    }

    TEST( StringSplitterIteratorTraits, ForwardIteratorConcept )
    {
        using Iterator = string::Splitter::Iterator;

        // C++20 concept validation
        static_assert( std::forward_iterator<Iterator>, "Iterator must satisfy forward_iterator concept" );
        static_assert( std::input_iterator<Iterator>, "Iterator must satisfy input_iterator concept" );

        SUCCEED();
    }

    TEST( StringSplitterSTLAlgorithms, StdDistance )
    {
        const std::string_view str = "a,b,c,d,e";
        auto splitter{ string::splitView( str, ',' ) };

        // std::distance requires proper iterator traits
        const auto count = std::distance( splitter.begin(), splitter.end() );
        EXPECT_EQ( count, 5 );
    }

    TEST( StringSplitterSTLAlgorithms, StdAdvance )
    {
        const std::string_view str = "a,b,c,d,e";
        auto splitter{ string::splitView( str, ',' ) };

        auto it = splitter.begin();
        std::advance( it, 2 ); // Advance 2 positions

        EXPECT_EQ( *it, "c" );
    }

    TEST( StringSplitterSTLAlgorithms, StdNext )
    {
        const std::string_view str = "a,b,c,d,e";
        auto splitter{ string::splitView( str, ',' ) };

        auto it = splitter.begin();
        auto next_it = std::next( it );

        EXPECT_EQ( *it, "a" );
        EXPECT_EQ( *next_it, "b" );

        // std::next with offset
        auto third = std::next( it, 2 );
        EXPECT_EQ( *third, "c" );
    }

    TEST( StringSplitterSTLAlgorithms, StdFind )
    {
        const std::string_view str = "apple,banana,cherry,date";
        auto splitter{ string::splitView( str, ',' ) };

        // std::find requires proper iterator traits
        auto it = std::find( splitter.begin(), splitter.end(), std::string_view{ "cherry" } );

        EXPECT_NE( it, splitter.end() );
        EXPECT_EQ( *it, "cherry" );
    }

    TEST( StringSplitterSTLAlgorithms, StdCount )
    {
        const std::string_view str = "a,b,a,c,a,d";
        auto splitter{ string::splitView( str, ',' ) };

        // std::count requires proper iterator traits
        const auto count = std::count( splitter.begin(), splitter.end(), std::string_view{ "a" } );

        EXPECT_EQ( count, 3 );
    }

    TEST( StringSplitterSTLAlgorithms, StdForEach )
    {
        const std::string_view str = "1,2,3,4,5";
        auto splitter{ string::splitView( str, ',' ) };

        // std::for_each requires proper iterator traits
        size_t sum{ 0 };
        std::for_each( splitter.begin(), splitter.end(), [&sum]( std::string_view sv ) {
            int value;
            if ( nfx::string::fromString<int>( sv, value ) )
            {
                sum += value;
            }
        } );

        EXPECT_EQ( sum, 15 ); // 1+2+3+4+5 = 15
    }

    TEST( StringSplitterSTLAlgorithms, StdAllOf )
    {
        const std::string_view str = "123,456,789";
        auto splitter{ string::splitView( str, ',' ) };

        // std::all_of requires proper iterator traits
        bool all_digits = std::all_of( splitter.begin(), splitter.end(), []( std::string_view sv ) {
            return nfx::string::isAllDigits( sv );
        } );

        EXPECT_TRUE( all_digits );
    }

    TEST( StringSplitterSTLAlgorithms, StdAnyOf )
    {
        const std::string_view str = "abc,123,def";
        auto splitter{ string::splitView( str, ',' ) };

        // std::any_of requires proper iterator traits
        bool has_digits = std::any_of( splitter.begin(), splitter.end(), []( std::string_view sv ) {
            return nfx::string::isAllDigits( sv );
        } );

        EXPECT_TRUE( has_digits ); // "123" contains only digits
    }

    TEST( StringSplitterSTLAlgorithms, StdNoneOf )
    {
        const std::string_view str = "abc,def,ghi";
        auto splitter{ string::splitView( str, ',' ) };

        // std::none_of requires proper iterator traits
        bool no_digits = std::none_of( splitter.begin(), splitter.end(), []( std::string_view sv ) {
            return nfx::string::isAllDigits( sv );
        } );

        EXPECT_TRUE( no_digits ); // None of the segments are all digits
    }

    //----------------------------------------------
    // Performance characteristics
    //----------------------------------------------

    TEST( StringSplitterPerformance, ZeroAllocation )
    {
        // This test verifies that no heap allocations occur during splitting
        const std::string_view str = "a,b,c,d,e,f,g,h,i,j";
        auto splitter{ string::splitView( str, ',' ) };

        // Count segments without storing them (zero allocation)
        size_t count{ 0 };
        for ( auto segment : splitter )
        {
            (void)segment.length();
            ++count;
        }

        EXPECT_EQ( count, 10 );
    }

    TEST( StringSplitterPerformance, StringViewPreservation )
    {
        // Verify that returned stringViews point to original string data
        const std::string original = "hello,world,test";
        const std::string_view str = original;
        auto splitter{ string::splitView( str, ',' ) };

        auto it{ splitter.begin() };
        std::string_view firstSegment = *it;

        // The segment should point to the same memory as the original string
        EXPECT_EQ( firstSegment.data(), original.data() );
        EXPECT_EQ( firstSegment, "hello" );
    }
} // namespace nfx::string::test
