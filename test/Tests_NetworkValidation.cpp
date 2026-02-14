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
 * @file Tests_NetworkValidation.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Network and URI validation tests
    //=====================================================================

    //----------------------------------------------
    // URI character classification
    //----------------------------------------------

    TEST( UriCharacterClassification, isURIReserved_char )
    {
        // RFC 3986 Section 2.2 - Reserved Characters
        // gen-delims: : / ? # [ ] @
        EXPECT_TRUE( isUriReserved( ':' ) );
        EXPECT_TRUE( isUriReserved( '/' ) );
        EXPECT_TRUE( isUriReserved( '?' ) );
        EXPECT_TRUE( isUriReserved( '#' ) );
        EXPECT_TRUE( isUriReserved( '[' ) );
        EXPECT_TRUE( isUriReserved( ']' ) );
        EXPECT_TRUE( isUriReserved( '@' ) );

        // sub-delims: ! $ & ' ( ) * + , ; =
        EXPECT_TRUE( isUriReserved( '!' ) );
        EXPECT_TRUE( isUriReserved( '$' ) );
        EXPECT_TRUE( isUriReserved( '&' ) );
        EXPECT_TRUE( isUriReserved( '\'' ) );
        EXPECT_TRUE( isUriReserved( '(' ) );
        EXPECT_TRUE( isUriReserved( ')' ) );
        EXPECT_TRUE( isUriReserved( '*' ) );
        EXPECT_TRUE( isUriReserved( '+' ) );
        EXPECT_TRUE( isUriReserved( ',' ) );
        EXPECT_TRUE( isUriReserved( ';' ) );
        EXPECT_TRUE( isUriReserved( '=' ) );

        // Non-reserved characters
        EXPECT_FALSE( isUriReserved( 'a' ) );
        EXPECT_FALSE( isUriReserved( 'Z' ) );
        EXPECT_FALSE( isUriReserved( '0' ) );
        EXPECT_FALSE( isUriReserved( '9' ) );
        EXPECT_FALSE( isUriReserved( '-' ) );
        EXPECT_FALSE( isUriReserved( '.' ) );
        EXPECT_FALSE( isUriReserved( '_' ) );
        EXPECT_FALSE( isUriReserved( '~' ) );
        EXPECT_FALSE( isUriReserved( ' ' ) );
        EXPECT_FALSE( isUriReserved( '\t' ) );
        EXPECT_FALSE( isUriReserved( '\n' ) );
        EXPECT_FALSE( isUriReserved( '\0' ) );

        // Edge ASCII characters
        EXPECT_FALSE( isUriReserved( '"' ) );  // ASCII 34
        EXPECT_FALSE( isUriReserved( '%' ) );  // ASCII 37
        EXPECT_FALSE( isUriReserved( '<' ) );  // ASCII 60
        EXPECT_FALSE( isUriReserved( '>' ) );  // ASCII 62
        EXPECT_FALSE( isUriReserved( '\\' ) ); // ASCII 92
        EXPECT_FALSE( isUriReserved( '^' ) );  // ASCII 94
        EXPECT_FALSE( isUriReserved( '`' ) );  // ASCII 96
        EXPECT_FALSE( isUriReserved( '|' ) );  // ASCII 124
    }

    TEST( UriCharacterClassification, isURIReserved_string )
    {
        // Valid reserved character strings
        EXPECT_TRUE( isUriReserved( ":" ) );
        EXPECT_TRUE( isUriReserved( "/" ) );
        EXPECT_TRUE( isUriReserved( "?" ) );
        EXPECT_TRUE( isUriReserved( "#" ) );
        EXPECT_TRUE( isUriReserved( "[]" ) );
        EXPECT_TRUE( isUriReserved( "@" ) );
        EXPECT_TRUE( isUriReserved( "!$&'()*+,;=" ) );
        EXPECT_TRUE( isUriReserved( ":/?#[]@" ) );
        EXPECT_TRUE( isUriReserved( "!$&'()*+,;=" ) );
        EXPECT_TRUE( isUriReserved( ":/?#[]@!$&'()*+,;=" ) ); // All reserved characters

        // Mixed strings with reserved and unreserved characters
        EXPECT_FALSE( isUriReserved( ":a" ) );
        EXPECT_FALSE( isUriReserved( "a:" ) );
        EXPECT_FALSE( isUriReserved( ":a:" ) );
        EXPECT_FALSE( isUriReserved( ":a?" ) );             // Contains unreserved char 'a'
        EXPECT_FALSE( isUriReserved( "test:" ) );           // Text + reserved
        EXPECT_FALSE( isUriReserved( ":test" ) );           // Reserved + text
        EXPECT_FALSE( isUriReserved( "test:123" ) );        // Text + reserved + digits
        EXPECT_FALSE( isUriReserved( "a/b" ) );             // Unreserved + reserved + unreserved
        EXPECT_FALSE( isUriReserved( "hello@world.com" ) ); // Mixed realistic scenario
        EXPECT_FALSE( isUriReserved( "user:pass" ) );       // Common auth format
        EXPECT_FALSE( isUriReserved( "file.txt" ) );        // Filename with unreserved chars
        EXPECT_FALSE( isUriReserved( "test" ) );
        EXPECT_FALSE( isUriReserved( "123" ) );
        EXPECT_FALSE( isUriReserved( "abc123" ) );

        // Invalid cases - empty string
        EXPECT_FALSE( isUriReserved( "" ) );
        EXPECT_FALSE( isUriReserved( std::string_view{} ) );

        // Strings with only unreserved characters
        EXPECT_FALSE( isUriReserved( "abcdefghijklmnopqrstuvwxyz" ) );
        EXPECT_FALSE( isUriReserved( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );
        EXPECT_FALSE( isUriReserved( "0123456789" ) );
        EXPECT_FALSE( isUriReserved( "-._~" ) );
        EXPECT_FALSE( isUriReserved( "abc123-._~XYZ" ) );

        // Strings with whitespace and control characters
        EXPECT_FALSE( isUriReserved( " " ) );
        EXPECT_FALSE( isUriReserved( "\t\n\r" ) );
        EXPECT_FALSE( isUriReserved( ": " ) ); // Contains space

        // Large string tests
        const std::string largeReserved( 1000, ':' );
        EXPECT_TRUE( isUriReserved( largeReserved ) );

        const std::string largeMixed = std::string( 999, ':' ) + "a";
        EXPECT_FALSE( isUriReserved( largeMixed ) );
    }

    TEST( UriCharacterClassification, isURIUnreserved_char )
    {
        // RFC 3986 Section 2.3 - Unreserved Characters
        // ALPHA (uppercase)
        EXPECT_TRUE( isUriUnreserved( 'A' ) );
        EXPECT_TRUE( isUriUnreserved( 'M' ) );
        EXPECT_TRUE( isUriUnreserved( 'Z' ) );

        // ALPHA (lowercase)
        EXPECT_TRUE( isUriUnreserved( 'a' ) );
        EXPECT_TRUE( isUriUnreserved( 'm' ) );
        EXPECT_TRUE( isUriUnreserved( 'z' ) );

        // DIGIT
        EXPECT_TRUE( isUriUnreserved( '0' ) );
        EXPECT_TRUE( isUriUnreserved( '5' ) );
        EXPECT_TRUE( isUriUnreserved( '9' ) );

        // Special unreserved characters: - . _ ~
        EXPECT_TRUE( isUriUnreserved( '-' ) );
        EXPECT_TRUE( isUriUnreserved( '.' ) );
        EXPECT_TRUE( isUriUnreserved( '_' ) );
        EXPECT_TRUE( isUriUnreserved( '~' ) );

        // Reserved characters should return false
        EXPECT_FALSE( isUriUnreserved( ':' ) );
        EXPECT_FALSE( isUriUnreserved( '/' ) );
        EXPECT_FALSE( isUriUnreserved( '?' ) );
        EXPECT_FALSE( isUriUnreserved( '#' ) );
        EXPECT_FALSE( isUriUnreserved( '[' ) );
        EXPECT_FALSE( isUriUnreserved( ']' ) );
        EXPECT_FALSE( isUriUnreserved( '@' ) );
        EXPECT_FALSE( isUriUnreserved( '!' ) );
        EXPECT_FALSE( isUriUnreserved( '$' ) );
        EXPECT_FALSE( isUriUnreserved( '&' ) );
        EXPECT_FALSE( isUriUnreserved( '\'' ) );
        EXPECT_FALSE( isUriUnreserved( '(' ) );
        EXPECT_FALSE( isUriUnreserved( ')' ) );
        EXPECT_FALSE( isUriUnreserved( '*' ) );
        EXPECT_FALSE( isUriUnreserved( '+' ) );
        EXPECT_FALSE( isUriUnreserved( ',' ) );
        EXPECT_FALSE( isUriUnreserved( ';' ) );
        EXPECT_FALSE( isUriUnreserved( '=' ) );

        // Other characters should return false
        EXPECT_FALSE( isUriUnreserved( ' ' ) );
        EXPECT_FALSE( isUriUnreserved( '\t' ) );
        EXPECT_FALSE( isUriUnreserved( '\n' ) );
        EXPECT_FALSE( isUriUnreserved( '\r' ) );
        EXPECT_FALSE( isUriUnreserved( '\0' ) );
        EXPECT_FALSE( isUriUnreserved( '"' ) );
        EXPECT_FALSE( isUriUnreserved( '%' ) );
        EXPECT_FALSE( isUriUnreserved( '<' ) );
        EXPECT_FALSE( isUriUnreserved( '>' ) );
        EXPECT_FALSE( isUriUnreserved( '\\' ) );
        EXPECT_FALSE( isUriUnreserved( '^' ) );
        EXPECT_FALSE( isUriUnreserved( '`' ) );
        EXPECT_FALSE( isUriUnreserved( '|' ) );

        // Edge ASCII boundaries
        EXPECT_FALSE( isUriUnreserved( '@' ) ); // ASCII 64 (before 'A')
        EXPECT_FALSE( isUriUnreserved( '[' ) ); // ASCII 91 (after 'Z')
        EXPECT_FALSE( isUriUnreserved( '`' ) ); // ASCII 96 (before 'a')
        EXPECT_FALSE( isUriUnreserved( '{' ) ); // ASCII 123 (after 'z')
        EXPECT_FALSE( isUriUnreserved( '/' ) ); // ASCII 47 (before '0')
        EXPECT_FALSE( isUriUnreserved( ':' ) ); // ASCII 58 (after '9')
    }

    TEST( UriCharacterClassification, isURIUnreserved_string )
    {
        // Valid unreserved character strings
        EXPECT_TRUE( isUriUnreserved( "a" ) );
        EXPECT_TRUE( isUriUnreserved( "Z" ) );
        EXPECT_TRUE( isUriUnreserved( "0" ) );
        EXPECT_TRUE( isUriUnreserved( "9" ) );
        EXPECT_TRUE( isUriUnreserved( "-" ) );
        EXPECT_TRUE( isUriUnreserved( "." ) );
        EXPECT_TRUE( isUriUnreserved( "_" ) );
        EXPECT_TRUE( isUriUnreserved( "~" ) );

        // Multiple unreserved characters
        EXPECT_TRUE( isUriUnreserved( "abc" ) );
        EXPECT_TRUE( isUriUnreserved( "XYZ" ) );
        EXPECT_TRUE( isUriUnreserved( "123" ) );
        EXPECT_TRUE( isUriUnreserved( "-._~" ) );
        EXPECT_TRUE( isUriUnreserved( "abcdefghijklmnopqrstuvwxyz" ) );
        EXPECT_TRUE( isUriUnreserved( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );
        EXPECT_TRUE( isUriUnreserved( "0123456789" ) );
        EXPECT_TRUE( isUriUnreserved( "abc123XYZ-._~" ) ); // All unreserved types

        // Valid URL-like strings with only unreserved characters
        EXPECT_TRUE( isUriUnreserved( "example" ) );
        EXPECT_TRUE( isUriUnreserved( "test123" ) );
        EXPECT_TRUE( isUriUnreserved( "my-file.txt" ) );
        EXPECT_TRUE( isUriUnreserved( "user_name" ) );
        EXPECT_TRUE( isUriUnreserved( "version~1" ) );

        // Mixed strings with reserved characters
        EXPECT_FALSE( isUriUnreserved( "a:" ) );
        EXPECT_FALSE( isUriUnreserved( ":a" ) );
        EXPECT_FALSE( isUriUnreserved( "a:b" ) );
        EXPECT_FALSE( isUriUnreserved( "test/" ) );
        EXPECT_FALSE( isUriUnreserved( "file?name" ) );
        EXPECT_FALSE( isUriUnreserved( "user@domain" ) );
        EXPECT_FALSE( isUriUnreserved( "path[0]" ) );
        EXPECT_FALSE( isUriUnreserved( "hello:world" ) );  // Text + reserved + text
        EXPECT_FALSE( isUriUnreserved( "test.txt?" ) );    // Unreserved + reserved
        EXPECT_FALSE( isUriUnreserved( "!important" ) );   // Reserved + unreserved
        EXPECT_FALSE( isUriUnreserved( "data&more" ) );    // Mixed realistic scenario
        EXPECT_FALSE( isUriUnreserved( "key=value" ) );    // Common query format
        EXPECT_FALSE( isUriUnreserved( "path/to/file" ) ); // Path with slashes

        // Invalid cases - empty string
        EXPECT_FALSE( isUriUnreserved( "" ) );
        EXPECT_FALSE( isUriUnreserved( std::string_view{} ) );

        // Strings with whitespace and control characters
        EXPECT_FALSE( isUriUnreserved( " " ) );
        EXPECT_FALSE( isUriUnreserved( "\t" ) );
        EXPECT_FALSE( isUriUnreserved( "\n" ) );
        EXPECT_FALSE( isUriUnreserved( "a " ) );  // Contains space
        EXPECT_FALSE( isUriUnreserved( " a" ) );  // Contains space
        EXPECT_FALSE( isUriUnreserved( "a b" ) ); // Contains space

        // Strings with other non-unreserved characters
        EXPECT_FALSE( isUriUnreserved( "\"" ) );
        EXPECT_FALSE( isUriUnreserved( "%" ) );
        EXPECT_FALSE( isUriUnreserved( "<>" ) );
        EXPECT_FALSE( isUriUnreserved( "\\" ) );
        EXPECT_FALSE( isUriUnreserved( "^" ) );
        EXPECT_FALSE( isUriUnreserved( "`" ) );
        EXPECT_FALSE( isUriUnreserved( "|" ) );

        // Large string tests
        const std::string largeUnreserved( 1000, 'a' );
        EXPECT_TRUE( isUriUnreserved( largeUnreserved ) );

        const std::string largeMixed = std::string( 999, 'a' ) + ":";
        EXPECT_FALSE( isUriUnreserved( largeMixed ) );

        // Performance test with mixed unreserved types
        const std::string mixedUnreserved = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~";
        EXPECT_TRUE( isUriUnreserved( mixedUnreserved ) );

        // String view from various sources
        std::string unreservedStr = "test123";
        std::string mixedStr = "test:123";
        EXPECT_TRUE( isUriUnreserved( unreservedStr ) );
        EXPECT_FALSE( isUriUnreserved( mixedStr ) );
    }

    //----------------------------------------------
    // URI Template validation (RFC 6570)
    //----------------------------------------------

    TEST( NetworkValidation, ValidTemplates )
    {
        // Level 1: Simple variable expansion
        EXPECT_TRUE( isUriTemplate( "/users/{id}" ) );
        EXPECT_TRUE( isUriTemplate( "/{username}" ) );
        EXPECT_TRUE( isUriTemplate( "/search/{term}/results" ) );

        // Level 2: Reserved character expansion
        EXPECT_TRUE( isUriTemplate( "/path{+path}" ) );
        EXPECT_TRUE( isUriTemplate( "/x{#fragment}" ) );

        // Level 3: Multiple variables
        EXPECT_TRUE( isUriTemplate( "/search{?q,page,limit}" ) );
        EXPECT_TRUE( isUriTemplate( "/map{?x,y,z}" ) );
        EXPECT_TRUE( isUriTemplate( "/path{;x,y}" ) );
        EXPECT_TRUE( isUriTemplate( "/list{.ext}" ) );
        EXPECT_TRUE( isUriTemplate( "/user/{id}/profile" ) );

        // Level 4: Value modifiers
        EXPECT_TRUE( isUriTemplate( "/search{?query*}" ) ); // Explode modifier
        EXPECT_TRUE( isUriTemplate( "/items{?fields*}" ) );
        EXPECT_TRUE( isUriTemplate( "/data{?list*,value}" ) );

        // Complex templates
        EXPECT_TRUE( isUriTemplate( "https://api.example.com/v1/users/{userId}/posts{?sort,limit}" ) );
        EXPECT_TRUE( isUriTemplate( "/api/{version}/{resource}{/id}{?filter*}" ) );
        EXPECT_TRUE( isUriTemplate( "{scheme}://{host}{/path*}{?query*}{#fragment}" ) );

        // Edge cases
        EXPECT_TRUE( isUriTemplate( "" ) );             // Empty template
        EXPECT_TRUE( isUriTemplate( "/static/path" ) ); // No variables
        EXPECT_TRUE( isUriTemplate( "/{a}/{b}/{c}" ) ); // Multiple simple variables
    }

    TEST( NetworkValidation, InvalidTemplates )
    {
        // Malformed expressions
        EXPECT_FALSE( isUriTemplate( "/path/{" ) );      // Unclosed brace
        EXPECT_FALSE( isUriTemplate( "/path/}" ) );      // Unmatched closing brace
        EXPECT_FALSE( isUriTemplate( "/path/{id" ) );    // Missing closing brace
        EXPECT_FALSE( isUriTemplate( "/path/id}" ) );    // Missing opening brace
        EXPECT_FALSE( isUriTemplate( "/path/{}" ) );     // Empty expression
        EXPECT_FALSE( isUriTemplate( "/path/{{id}}" ) ); // Double braces

        // Invalid variable names
        EXPECT_FALSE( isUriTemplate( "/path/{ id }" ) ); // Spaces in variable name
        EXPECT_FALSE( isUriTemplate( "/path/{id!}" ) );  // Invalid character
        EXPECT_FALSE( isUriTemplate( "/path/{id@}" ) );  // Invalid character

        // Invalid operators
        EXPECT_FALSE( isUriTemplate( "/path/{$id}" ) ); // Invalid operator
        EXPECT_FALSE( isUriTemplate( "/path/{%id}" ) ); // Invalid operator
        EXPECT_FALSE( isUriTemplate( "/path/{^id}" ) ); // Invalid operator

        // Control characters
        EXPECT_FALSE( isUriTemplate( "/path\n/{id}" ) ); // Newline
        EXPECT_FALSE( isUriTemplate( "/path\r/{id}" ) ); // Carriage return
        constexpr char nullTemplate[] = "/path\0/{id}";
        EXPECT_FALSE( isUriTemplate( std::string_view( nullTemplate, sizeof( nullTemplate ) - 1 ) ) ); // Null character
    }

    //----------------------------------------------
    // IP address validation
    //----------------------------------------------

    TEST( NetworkValidation, IsIPv4Address )
    {
        // Valid IPv4 addresses
        EXPECT_TRUE( isIpv4Address( "0.0.0.0" ) );
        EXPECT_TRUE( isIpv4Address( "127.0.0.1" ) );
        EXPECT_TRUE( isIpv4Address( "192.168.1.1" ) );
        EXPECT_TRUE( isIpv4Address( "255.255.255.255" ) );
        EXPECT_TRUE( isIpv4Address( "10.0.0.1" ) );
        EXPECT_TRUE( isIpv4Address( "172.16.0.1" ) );
        EXPECT_TRUE( isIpv4Address( "8.8.8.8" ) );
        EXPECT_TRUE( isIpv4Address( "1.2.3.4" ) );

        // Invalid IPv4 addresses - wrong format
        EXPECT_FALSE( isIpv4Address( "" ) );
        EXPECT_FALSE( isIpv4Address( "192.168.1" ) );     // Missing octet
        EXPECT_FALSE( isIpv4Address( "192.168.1.1.1" ) ); // Too many octets
        EXPECT_FALSE( isIpv4Address( "192.168..1" ) );    // Empty octet
        EXPECT_FALSE( isIpv4Address( ".192.168.1.1" ) );  // Starts with dot
        EXPECT_FALSE( isIpv4Address( "192.168.1.1." ) );  // Ends with dot
        EXPECT_FALSE( isIpv4Address( "192.168.1.1.." ) ); // Double dot at end

        // Invalid IPv4 addresses - out of range
        EXPECT_FALSE( isIpv4Address( "256.1.1.1" ) );       // > 255
        EXPECT_FALSE( isIpv4Address( "1.256.1.1" ) );       // > 255
        EXPECT_FALSE( isIpv4Address( "1.1.256.1" ) );       // > 255
        EXPECT_FALSE( isIpv4Address( "1.1.1.256" ) );       // > 255
        EXPECT_FALSE( isIpv4Address( "999.999.999.999" ) ); // Way out of range
        EXPECT_FALSE( isIpv4Address( "300.300.300.300" ) );

        // Invalid IPv4 addresses - non-numeric
        EXPECT_FALSE( isIpv4Address( "abc.def.ghi.jkl" ) );
        EXPECT_FALSE( isIpv4Address( "192.168.1.a" ) );
        EXPECT_FALSE( isIpv4Address( "192.168.1.1a" ) );
        EXPECT_FALSE( isIpv4Address( "192.168.1.1 " ) ); // Trailing space
        EXPECT_FALSE( isIpv4Address( " 192.168.1.1" ) ); // Leading space
        EXPECT_FALSE( isIpv4Address( "192.168. 1.1" ) ); // Space in middle

        // Invalid IPv4 addresses - special characters
        EXPECT_FALSE( isIpv4Address( "192.168.1.1:80" ) ); // Port included
        EXPECT_FALSE( isIpv4Address( "192.168.1.1/24" ) ); // CIDR notation
        EXPECT_FALSE( isIpv4Address( "192-168-1-1" ) );    // Hyphens instead of dots

        // Edge cases
        EXPECT_FALSE( isIpv4Address( "..." ) );
        EXPECT_FALSE( isIpv4Address( "1.2.3.4.5.6.7.8" ) ); // Too long
        EXPECT_FALSE( isIpv4Address( "01.02.03.04" ) );     // Leading zeros (technically invalid in strict parsing)
    }

    TEST( NetworkValidation, IsIPv6Address )
    {
        // Valid IPv6 addresses - full notation
        EXPECT_TRUE( isIpv6Address( "2001:0db8:0000:0000:0000:0000:0000:0001" ) );
        EXPECT_TRUE( isIpv6Address( "2001:db8:0:0:0:0:0:1" ) );
        EXPECT_TRUE( isIpv6Address( "2001:0db8:85a3:0000:0000:8a2e:0370:7334" ) );

        // Valid IPv6 addresses - compressed notation
        EXPECT_TRUE( isIpv6Address( "::" ) );          // All zeros
        EXPECT_TRUE( isIpv6Address( "::1" ) );         // Loopback
        EXPECT_TRUE( isIpv6Address( "2001:db8::1" ) ); // Compressed middle
        EXPECT_TRUE( isIpv6Address( "2001:db8:85a3::8a2e:370:7334" ) );
        EXPECT_TRUE( isIpv6Address( "::ffff:192.0.2.1" ) ); // IPv4-mapped
        EXPECT_TRUE( isIpv6Address( "fe80::1" ) );          // Link-local

        // Valid IPv6 addresses - with zone ID
        EXPECT_TRUE( isIpv6Address( "fe80::1%eth0" ) );
        EXPECT_TRUE( isIpv6Address( "fe80::1%lo0" ) );

        // Invalid IPv6 addresses - wrong format
        EXPECT_FALSE( isIpv6Address( "" ) );
        EXPECT_FALSE( isIpv6Address( ":" ) );
        EXPECT_FALSE( isIpv6Address( ":::" ) );                                // Too many colons
        EXPECT_FALSE( isIpv6Address( "2001:db8::1::2" ) );                     // Multiple :: compressions
        EXPECT_FALSE( isIpv6Address( "gggg::1" ) );                            // Invalid hex
        EXPECT_FALSE( isIpv6Address( "2001:db8:85a3::8a2e:370:7334:extra" ) ); // Too many groups

        // Invalid IPv6 addresses - too many digits per group
        EXPECT_FALSE( isIpv6Address( "20011:db8::1" ) );    // 5 hex digits
        EXPECT_FALSE( isIpv6Address( "2001:db88888::1" ) ); // Too many digits

        // Invalid IPv6 addresses - invalid characters
        EXPECT_FALSE( isIpv6Address( "2001:db8::1 " ) );   // Trailing space
        EXPECT_FALSE( isIpv6Address( " 2001:db8::1" ) );   // Leading space
        EXPECT_FALSE( isIpv6Address( "2001:db8::g" ) );    // Invalid hex char
        EXPECT_FALSE( isIpv6Address( "2001:db8::1/64" ) ); // CIDR notation
        EXPECT_FALSE( isIpv6Address( "[2001:db8::1]" ) );  // Brackets
    }

    //----------------------------------------------
    // Host validation
    //----------------------------------------------

    TEST( NetworkValidation, IsValidHostname )
    {
        // Valid hostnames
        EXPECT_TRUE( isHostname( "localhost" ) );
        EXPECT_TRUE( isHostname( "example.com" ) );
        EXPECT_TRUE( isHostname( "www.example.com" ) );
        EXPECT_TRUE( isHostname( "sub.domain.example.com" ) );
        EXPECT_TRUE( isHostname( "my-server" ) );
        EXPECT_TRUE( isHostname( "server-01" ) );
        EXPECT_TRUE( isHostname( "192-168-1-1" ) );  // Numeric but valid hostname format
        EXPECT_TRUE( isHostname( "a" ) );            // Single character
        EXPECT_TRUE( isHostname( "a.b" ) );          // Minimum domain
        EXPECT_TRUE( isHostname( "test123" ) );      // Alphanumeric
        EXPECT_TRUE( isHostname( "test-123-abc" ) ); // With hyphens

        // Valid hostnames - max lengths
        const std::string label63( 63, 'a' ); // Max label length
        EXPECT_TRUE( isHostname( label63 ) );
        EXPECT_TRUE( isHostname( label63 + ".com" ) );

        const std::string hostname253 = label63 + "." + label63 + "." + label63 + ".com"; // Close to max
        EXPECT_TRUE( isHostname( hostname253 ) );

        // Invalid hostnames - empty
        EXPECT_FALSE( isHostname( "" ) );

        // Invalid hostnames - too long
        const std::string label64( 64, 'a' ); // Exceeds max label length
        EXPECT_FALSE( isHostname( label64 ) );
        const std::string hostname254( 254, 'a' ); // Exceeds max total length
        EXPECT_FALSE( isHostname( hostname254 ) );

        // Invalid hostnames - starts with hyphen
        EXPECT_FALSE( isHostname( "-server" ) );
        EXPECT_FALSE( isHostname( "server.-test" ) );

        // Invalid hostnames - ends with hyphen
        EXPECT_FALSE( isHostname( "server-" ) );
        EXPECT_FALSE( isHostname( "server.test-" ) );

        // Invalid hostnames - consecutive dots
        EXPECT_FALSE( isHostname( "example..com" ) );
        EXPECT_FALSE( isHostname( "..example" ) );

        // Invalid hostnames - starts/ends with dot
        EXPECT_FALSE( isHostname( ".example.com" ) );
        EXPECT_FALSE( isHostname( "example.com." ) );

        // Invalid hostnames - invalid characters
        EXPECT_FALSE( isHostname( "example_com" ) );  // Underscore
        EXPECT_FALSE( isHostname( "example.com!" ) ); // Special char
        EXPECT_FALSE( isHostname( "example com" ) );  // Space
        EXPECT_FALSE( isHostname( "example@com" ) );  // @ symbol
        EXPECT_FALSE( isHostname( "example:8080" ) ); // Colon
        EXPECT_FALSE( isHostname( "example/path" ) ); // Slash
    }

    TEST( NetworkValidation, IsValidIdnHostname )
    {
        // Valid ASCII hostnames (should still work)
        EXPECT_TRUE( isIdnHostname( "localhost" ) );
        EXPECT_TRUE( isIdnHostname( "example.com" ) );
        EXPECT_TRUE( isIdnHostname( "www.example.com" ) );
        EXPECT_TRUE( isIdnHostname( "my-server-01" ) );

        // Valid Punycode hostnames (xn-- prefix)
        EXPECT_TRUE( isIdnHostname( "xn--e1afmkfd.ru" ) );           // пример.ru
        EXPECT_TRUE( isIdnHostname( "xn--n3h.com" ) );               // ☃.com (snowman)
        EXPECT_TRUE( isIdnHostname( "xn--80akhbyknj4f.xn--p1ai" ) ); // испытание.рф
        EXPECT_TRUE( isIdnHostname( "example.xn--fiqs8s" ) );        // example.中国

        // Valid Unicode hostnames (direct Unicode, not Punycode)
        EXPECT_TRUE( isIdnHostname( "münchen.de" ) ); // German umlaut
        EXPECT_TRUE( isIdnHostname( "zürich.ch" ) );  // Swiss city
        EXPECT_TRUE( isIdnHostname( "россия.рф" ) );  // Russia in Cyrillic
        EXPECT_TRUE( isIdnHostname( "中国.cn" ) );    // China in Chinese
        EXPECT_TRUE( isIdnHostname( "日本.jp" ) );    // Japan in Japanese
        EXPECT_TRUE( isIdnHostname( "مصر.eg" ) );     // Egypt in Arabic
        EXPECT_TRUE( isIdnHostname( "ελλάδα.gr" ) );  // Greece in Greek
        EXPECT_TRUE( isIdnHostname( "españa.es" ) );  // Spain with ñ
        EXPECT_TRUE( isIdnHostname( "café.fr" ) );    // French café
        EXPECT_TRUE( isIdnHostname( "naïve.com" ) );  // Diaeresis

        // Mixed ASCII and Unicode
        EXPECT_TRUE( isIdnHostname( "www.münchen.de" ) );
        EXPECT_TRUE( isIdnHostname( "test.中国.com" ) );

        // Valid hostnames - length constraints
        const std::string label63( 63, 'a' );
        EXPECT_TRUE( isIdnHostname( label63 ) );
        EXPECT_TRUE( isIdnHostname( label63 + ".com" ) );

        // Invalid hostnames - empty
        EXPECT_FALSE( isIdnHostname( "" ) );

        // Invalid hostnames - too long
        const std::string label64( 64, 'a' );
        EXPECT_FALSE( isIdnHostname( label64 ) );
        const std::string hostname254( 254, 'a' );
        EXPECT_FALSE( isIdnHostname( hostname254 ) );

        // Invalid hostnames - starts/ends with hyphen
        EXPECT_FALSE( isIdnHostname( "-server" ) );
        EXPECT_FALSE( isIdnHostname( "server-" ) );
        EXPECT_FALSE( isIdnHostname( "test.-example" ) );
        EXPECT_FALSE( isIdnHostname( "test.example-" ) );

        // Invalid hostnames - starts/ends with dot
        EXPECT_FALSE( isIdnHostname( ".example.com" ) );
        EXPECT_FALSE( isIdnHostname( "example.com." ) );

        // Invalid hostnames - consecutive dots
        EXPECT_FALSE( isIdnHostname( "example..com" ) );

        // Invalid Punycode (malformed)
        EXPECT_FALSE( isIdnHostname( "xn--" ) );            // Just prefix
        EXPECT_FALSE( isIdnHostname( "xn--.com" ) );        // Empty after prefix
        EXPECT_FALSE( isIdnHostname( "xn--abc!def.com" ) ); // Invalid char in Punycode
    }

    TEST( NetworkValidation, IsDomainName )
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
        EXPECT_FALSE( isDomainName( ".com" ) );          // Starts with dot
        EXPECT_FALSE( isDomainName( "example.com." ) );  // Ends with dot
        EXPECT_FALSE( isDomainName( "example..com" ) );  // Consecutive dots
        EXPECT_FALSE( isDomainName( "-test.com" ) );     // Starts with hyphen
        EXPECT_FALSE( isDomainName( "test-.com" ) );     // Label ends with hyphen
        EXPECT_FALSE( isDomainName( "test_site.com" ) ); // Underscore
        EXPECT_FALSE( isDomainName( "test site.com" ) ); // Space
    }

    //----------------------------------------------
    // Port validation
    //----------------------------------------------

    TEST( NetworkValidation, IsValidPort_String )
    {
        // Valid port strings
        EXPECT_TRUE( isPortNumber( "0" ) );
        EXPECT_TRUE( isPortNumber( "1" ) );
        EXPECT_TRUE( isPortNumber( "80" ) );
        EXPECT_TRUE( isPortNumber( "443" ) );
        EXPECT_TRUE( isPortNumber( "8080" ) );
        EXPECT_TRUE( isPortNumber( "3000" ) );
        EXPECT_TRUE( isPortNumber( "65535" ) ); // Max port

        // Valid port strings - well-known ports
        EXPECT_TRUE( isPortNumber( "21" ) );   // FTP
        EXPECT_TRUE( isPortNumber( "22" ) );   // SSH
        EXPECT_TRUE( isPortNumber( "25" ) );   // SMTP
        EXPECT_TRUE( isPortNumber( "53" ) );   // DNS
        EXPECT_TRUE( isPortNumber( "3306" ) ); // MySQL
        EXPECT_TRUE( isPortNumber( "5432" ) ); // PostgreSQL

        // Invalid port strings - empty
        EXPECT_FALSE( isPortNumber( "" ) );

        // Invalid port strings - out of range
        EXPECT_FALSE( isPortNumber( "65536" ) ); // Max + 1
        EXPECT_FALSE( isPortNumber( "99999" ) );
        EXPECT_FALSE( isPortNumber( "100000" ) );
        EXPECT_FALSE( isPortNumber( "999999" ) );

        // Invalid port strings - non-numeric
        EXPECT_FALSE( isPortNumber( "abc" ) );
        EXPECT_FALSE( isPortNumber( "80a" ) );
        EXPECT_FALSE( isPortNumber( "a80" ) );
        EXPECT_FALSE( isPortNumber( "8o8o" ) ); // Letter 'o' instead of zero

        // Invalid port strings - with whitespace
        EXPECT_FALSE( isPortNumber( " 80" ) );
        EXPECT_FALSE( isPortNumber( "80 " ) );
        EXPECT_FALSE( isPortNumber( " 80 " ) );

        // Invalid port strings - with special characters
        EXPECT_FALSE( isPortNumber( "-80" ) );   // Negative sign
        EXPECT_FALSE( isPortNumber( "+80" ) );   // Plus sign
        EXPECT_FALSE( isPortNumber( "80.0" ) );  // Decimal
        EXPECT_FALSE( isPortNumber( "80:80" ) ); // Colon
    }

    //----------------------------------------------
    // Endpoint parsing
    //----------------------------------------------

    TEST( NetworkValidation, TryParseEndpoint_IPv4 )
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

    TEST( NetworkValidation, TryParseEndpoint_IPv6 )
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
        EXPECT_FALSE( tryParseEndpoint( "[::1", host, port ) );      // Missing closing bracket
        EXPECT_FALSE( tryParseEndpoint( "::1]", host, port ) );      // Missing opening bracket
        EXPECT_FALSE( tryParseEndpoint( "[::1]:abc", host, port ) ); // Invalid port
    }

    TEST( NetworkValidation, TryParseEndpoint_Hostname )
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

    TEST( NetworkValidation, TryParseEndpoint_EdgeCases )
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
} // namespace nfx::string::test
