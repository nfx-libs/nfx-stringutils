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
 * @file Tests_FormatValidation.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Format validation tests
    //=====================================================================

    //----------------------------------------------
    // Date validation (RFC 3339)
    //----------------------------------------------

    TEST( FormatValidation, ValidDates )
    {
        EXPECT_TRUE( isDate( "2025-11-29" ) );
        EXPECT_TRUE( isDate( "2000-01-01" ) );
        EXPECT_TRUE( isDate( "1999-12-31" ) );
        EXPECT_TRUE( isDate( "2024-02-29" ) ); // Leap year (basic check, not validating leap year logic)
        EXPECT_TRUE( isDate( "2023-02-28" ) );
        EXPECT_TRUE( isDate( "0001-01-01" ) );
        EXPECT_TRUE( isDate( "9999-12-31" ) );
    }

    TEST( FormatValidation, InvalidDates )
    {
        EXPECT_FALSE( isDate( "" ) );
        EXPECT_FALSE( isDate( "2025-13-01" ) );  // Invalid month
        EXPECT_FALSE( isDate( "2025-00-01" ) );  // Invalid month
        EXPECT_FALSE( isDate( "2025-01-32" ) );  // Invalid day
        EXPECT_FALSE( isDate( "2025-01-00" ) );  // Invalid day
        EXPECT_FALSE( isDate( "2025-04-31" ) );  // April has 30 days
        EXPECT_FALSE( isDate( "2025-06-31" ) );  // June has 30 days
        EXPECT_FALSE( isDate( "25-11-29" ) );    // Wrong year format
        EXPECT_FALSE( isDate( "2025/11/29" ) );  // Wrong separator
        EXPECT_FALSE( isDate( "2025-1-29" ) );   // Missing leading zero
        EXPECT_FALSE( isDate( "2025-11-9" ) );   // Missing leading zero
        EXPECT_FALSE( isDate( "20251129" ) );    // No separators
        EXPECT_FALSE( isDate( "2025-11-29T" ) ); // Extra character
    }

    //----------------------------------------------
    // DateTime validation (RFC 3339)
    //----------------------------------------------

    TEST( FormatValidation, ValidDateTimes )
    {
        EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00Z" ) );
        EXPECT_TRUE( isDateTime( "2025-11-29t14:30:00z" ) ); // Lowercase
        EXPECT_TRUE( isDateTime( "2000-01-01T00:00:00Z" ) );
        EXPECT_TRUE( isDateTime( "2025-12-31T23:59:59Z" ) );
        EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00+05:30" ) );
        EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00-08:00" ) );
        EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00.123Z" ) );
        EXPECT_TRUE( isDateTime( "2025-11-29T14:30:00.123456+00:00" ) );
    }

    TEST( FormatValidation, InvalidDateTimes )
    {
        EXPECT_FALSE( isDateTime( "" ) );
        EXPECT_FALSE( isDateTime( "2025-11-29" ) );           // Date only
        EXPECT_FALSE( isDateTime( "14:30:00Z" ) );            // Time only
        EXPECT_FALSE( isDateTime( "2025-11-29 14:30:00Z" ) ); // Space instead of T
        EXPECT_FALSE( isDateTime( "2025-13-29T14:30:00Z" ) ); // Invalid month
        EXPECT_FALSE( isDateTime( "2025-11-29T25:30:00Z" ) ); // Invalid hour
        EXPECT_FALSE( isDateTime( "2025-11-29T14:30:00" ) );  // Missing timezone
        EXPECT_FALSE( isDateTime( "2025/11/29T14:30:00Z" ) ); // Wrong date separator
    }

    //----------------------------------------------
    // Constexpr validation tests
    //----------------------------------------------

    TEST( FormatValidation, DateTimeValidation )
    {
        constexpr bool validDate = isDate( "2025-11-29" );
        constexpr bool invalidDate = isDate( "invalid" );
        constexpr bool validTime = isTime( "14:30:00Z" );
        constexpr bool validDateTime = isDateTime( "2025-11-29T14:30:00Z" );
        constexpr bool validDuration = isDuration( "P1Y2M3D" );

        EXPECT_TRUE( validDate );
        EXPECT_FALSE( invalidDate );
        EXPECT_TRUE( validTime );
        EXPECT_TRUE( validDateTime );
        EXPECT_TRUE( validDuration );
    }

    TEST( FormatValidation, FormatValidation )
    {
        constexpr bool validUUID = isUuid( "550e8400-e29b-41d4-a716-446655440000" );
        constexpr bool validURI = isUri( "https://example.com" );
        constexpr bool validURIRef = isUriReference( "/path" );
        constexpr bool validJSONPtr = isJsonPointer( "/foo/bar" );
        constexpr bool validRelPtr = isRelativeJsonPointer( "1/foo" );

        EXPECT_TRUE( validUUID );
        EXPECT_TRUE( validURI );
        EXPECT_TRUE( validURIRef );
        EXPECT_TRUE( validJSONPtr );
        EXPECT_TRUE( validRelPtr );
    }

    //----------------------------------------------
    // Time validation (RFC 3339)
    //----------------------------------------------

    TEST( FormatValidation, ValidTimes )
    {
        EXPECT_TRUE( isTime( "14:30:00Z" ) );
        EXPECT_TRUE( isTime( "00:00:00Z" ) );
        EXPECT_TRUE( isTime( "23:59:59Z" ) );
        EXPECT_TRUE( isTime( "12:00:00z" ) ); // Lowercase z
        EXPECT_TRUE( isTime( "14:30:00+00:00" ) );
        EXPECT_TRUE( isTime( "14:30:00-05:00" ) );
        EXPECT_TRUE( isTime( "14:30:00+12:00" ) );
        EXPECT_TRUE( isTime( "14:30:00.123Z" ) );       // Fractional seconds
        EXPECT_TRUE( isTime( "14:30:00.123456789Z" ) ); // Many fractional digits
        EXPECT_TRUE( isTime( "23:59:60Z" ) );           // Leap second (standard case)
        EXPECT_TRUE( isTime( "00:00:60Z" ) );           // Leap second (boundary test)
        EXPECT_TRUE( isTime( "12:30:60+00:00" ) );      // Leap second with offset
        EXPECT_TRUE( isTime( "23:59:60.999Z" ) );       // Leap second with fractional
    }

    TEST( FormatValidation, InvalidTimes )
    {
        EXPECT_FALSE( isTime( "" ) );
        EXPECT_FALSE( isTime( "24:00:00Z" ) );      // Invalid hour
        EXPECT_FALSE( isTime( "14:60:00Z" ) );      // Invalid minute
        EXPECT_FALSE( isTime( "14:30:61Z" ) );      // Invalid second (61 > 60)
        EXPECT_FALSE( isTime( "14:30:62Z" ) );      // Invalid second (62 > 60)
        EXPECT_FALSE( isTime( "14:30:99Z" ) );      // Invalid second (way over)
        EXPECT_FALSE( isTime( "14:30:00" ) );       // Missing timezone
        EXPECT_FALSE( isTime( "14:30:00+" ) );      // Incomplete timezone
        EXPECT_FALSE( isTime( "14:30:00+25:00" ) ); // Invalid tz hour
        EXPECT_FALSE( isTime( "14:30:00+00:60" ) ); // Invalid tz minute
        EXPECT_FALSE( isTime( "14:30Z" ) );         // Missing seconds
        EXPECT_FALSE( isTime( "14:30:00.Z" ) );     // Empty fractional
        EXPECT_FALSE( isTime( "1:30:00Z" ) );       // Missing leading zero
    }

    //----------------------------------------------
    // Duration validation (ISO 8601)
    //----------------------------------------------

    TEST( FormatValidation, ValidDurations )
    {
        EXPECT_TRUE( isDuration( "P1Y" ) );
        EXPECT_TRUE( isDuration( "P1M" ) );
        EXPECT_TRUE( isDuration( "P1D" ) );
        EXPECT_TRUE( isDuration( "PT1H" ) );
        EXPECT_TRUE( isDuration( "PT1M" ) );
        EXPECT_TRUE( isDuration( "PT1S" ) );
        EXPECT_TRUE( isDuration( "P1Y2M3D" ) );
        EXPECT_TRUE( isDuration( "PT1H2M3S" ) );
        EXPECT_TRUE( isDuration( "P1Y2M3DT4H5M6S" ) );
        EXPECT_TRUE( isDuration( "P1W" ) ); // Week format
        EXPECT_TRUE( isDuration( "P52W" ) );
        EXPECT_TRUE( isDuration( "PT0.5S" ) ); // Fractional seconds
        EXPECT_TRUE( isDuration( "PT1.123S" ) );
    }

    TEST( FormatValidation, InvalidDurations )
    {
        EXPECT_FALSE( isDuration( "" ) );
        EXPECT_FALSE( isDuration( "P" ) );        // P alone
        EXPECT_FALSE( isDuration( "1Y" ) );       // Missing P
        EXPECT_FALSE( isDuration( "PT" ) );       // T without time
        EXPECT_FALSE( isDuration( "P1H" ) );      // H without T
        EXPECT_FALSE( isDuration( "P1Y2M3DT" ) ); // T without time parts
        EXPECT_FALSE( isDuration( "P1WT1H" ) );   // Week with other parts
        EXPECT_FALSE( isDuration( "P.5S" ) );     // Decimal without integer
    }

    //----------------------------------------------
    // Email validation (RFC 5321)
    //----------------------------------------------

    TEST( FormatValidation, ValidEmails )
    {
        EXPECT_TRUE( isEmail( "user@example.com" ) );
        EXPECT_TRUE( isEmail( "user.name@example.com" ) );
        EXPECT_TRUE( isEmail( "user+tag@example.com" ) );
        EXPECT_TRUE( isEmail( "user@sub.example.com" ) );
        EXPECT_TRUE( isEmail( "user@example.co.uk" ) );
        EXPECT_TRUE( isEmail( "a@b.co" ) );
        EXPECT_TRUE( isEmail( "user123@example123.com" ) );
        EXPECT_TRUE( isEmail( "user_name@example.com" ) );
        EXPECT_TRUE( isEmail( "user-name@example.com" ) );
        EXPECT_TRUE( isEmail( "user!def@example.com" ) ); // Special chars allowed in local
    }

    TEST( FormatValidation, InvalidEmails )
    {
        EXPECT_FALSE( isEmail( "" ) );
        EXPECT_FALSE( isEmail( "user" ) );                             // No @
        EXPECT_FALSE( isEmail( "@example.com" ) );                     // No local part
        EXPECT_FALSE( isEmail( "user@" ) );                            // No domain
        EXPECT_FALSE( isEmail( "user@.com" ) );                        // Domain starts with dot
        EXPECT_FALSE( isEmail( "user@example" ) );                     // No TLD (single label)
        EXPECT_FALSE( isEmail( ".user@example.com" ) );                // Local starts with dot
        EXPECT_FALSE( isEmail( "user.@example.com" ) );                // Local ends with dot
        EXPECT_FALSE( isEmail( "user..name@example.com" ) );           // Consecutive dots
        EXPECT_FALSE( isEmail( "user name@example.com" ) );            // Space in local
        EXPECT_FALSE( isEmail( std::string( 255, 'a' ) + "@b.com" ) ); // Too long
    }

    TEST( FormatValidation, ValidIdnEmails )
    {
        // Valid ASCII emails (should still work)
        EXPECT_TRUE( isIdnEmail( "user@example.com" ) );
        EXPECT_TRUE( isIdnEmail( "user.name@example.com" ) );
        EXPECT_TRUE( isIdnEmail( "user+tag@sub.example.com" ) );
        EXPECT_TRUE( isIdnEmail( "test123@test.co.uk" ) );

        // Valid Punycode domain emails
        EXPECT_TRUE( isIdnEmail( "user@xn--e1afmkfd.ru" ) );           // user@пример.ru
        EXPECT_TRUE( isIdnEmail( "test@xn--n3h.com" ) );               // test@☃.com
        EXPECT_TRUE( isIdnEmail( "info@xn--80akhbyknj4f.xn--p1ai" ) ); // info@испытание.рф
        EXPECT_TRUE( isIdnEmail( "admin@example.xn--fiqs8s" ) );       // admin@example.中国

        // Valid Unicode domain emails
        EXPECT_TRUE( isIdnEmail( "user@münchen.de" ) ); // German
        EXPECT_TRUE( isIdnEmail( "admin@zürich.ch" ) ); // Swiss
        EXPECT_TRUE( isIdnEmail( "info@россия.рф" ) );  // Russian
        EXPECT_TRUE( isIdnEmail( "test@中国.cn" ) );    // Chinese
        EXPECT_TRUE( isIdnEmail( "user@日本.jp" ) );    // Japanese
        EXPECT_TRUE( isIdnEmail( "contact@مصر.eg" ) );  // Arabic
        EXPECT_TRUE( isIdnEmail( "hello@ελλάδα.gr" ) ); // Greek
        EXPECT_TRUE( isIdnEmail( "info@españa.es" ) );  // Spanish
        EXPECT_TRUE( isIdnEmail( "contact@café.fr" ) ); // French
        EXPECT_TRUE( isIdnEmail( "test@naïve.com" ) );  // Diaeresis

        // Valid Unicode local-part emails (EAI/SMTPUTF8)
        EXPECT_TRUE( isIdnEmail( "用户@example.com" ) );       // Chinese user
        EXPECT_TRUE( isIdnEmail( "José@example.com" ) );       // Spanish name
        EXPECT_TRUE( isIdnEmail( "françois@café.fr" ) );       // French name and domain
        EXPECT_TRUE( isIdnEmail( "müller@münchen.de" ) );      // German name and domain
        EXPECT_TRUE( isIdnEmail( "пользователь@россия.рф" ) ); // Russian name and domain
        EXPECT_TRUE( isIdnEmail( "用户@中国.cn" ) );           // Chinese name and domain

        // Mixed Unicode and ASCII
        EXPECT_TRUE( isIdnEmail( "user@test.münchen.de" ) );
        EXPECT_TRUE( isIdnEmail( "josé.garcía@example.com" ) );
    }

    TEST( FormatValidation, InvalidIdnEmails )
    {
        // Invalid - basic validation
        EXPECT_FALSE( isIdnEmail( "" ) );
        EXPECT_FALSE( isIdnEmail( "user" ) );         // No @
        EXPECT_FALSE( isIdnEmail( "@example.com" ) ); // No local part
        EXPECT_FALSE( isIdnEmail( "user@" ) );        // No domain
        EXPECT_FALSE( isIdnEmail( "user@example" ) ); // No TLD (single label)

        // Invalid - dot handling
        EXPECT_FALSE( isIdnEmail( ".user@example.com" ) );      // Local starts with dot
        EXPECT_FALSE( isIdnEmail( "user.@example.com" ) );      // Local ends with dot
        EXPECT_FALSE( isIdnEmail( "user..name@example.com" ) ); // Consecutive dots
        EXPECT_FALSE( isIdnEmail( "user@.münchen.de" ) );       // Domain starts with dot

        // Invalid - length constraints
        EXPECT_FALSE( isIdnEmail( std::string( 255, 'a' ) + "@example.com" ) ); // Too long total
        EXPECT_FALSE( isIdnEmail( std::string( 65, 'a' ) + "@example.com" ) );  // Local-part too long

        // Invalid - malformed Punycode
        EXPECT_FALSE( isIdnEmail( "user@xn--.com" ) );     // Empty Punycode
        EXPECT_FALSE( isIdnEmail( "user@xn--!abc.com" ) ); // Invalid char in Punycode
    }

    //----------------------------------------------
    // UUID validation (RFC 4122)
    //----------------------------------------------

    TEST( FormatValidation, ValidUUIDs )
    {
        EXPECT_TRUE( isUuid( "550e8400-e29b-41d4-a716-446655440000" ) );
        EXPECT_TRUE( isUuid( "00000000-0000-0000-0000-000000000000" ) );
        EXPECT_TRUE( isUuid( "ffffffff-ffff-ffff-ffff-ffffffffffff" ) );
        EXPECT_TRUE( isUuid( "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF" ) ); // Uppercase
        EXPECT_TRUE( isUuid( "123e4567-e89b-12d3-a456-426614174000" ) );
        EXPECT_TRUE( isUuid( "a1b2c3d4-e5f6-7890-abcd-ef1234567890" ) );
    }

    TEST( FormatValidation, InvalidUUIDs )
    {
        EXPECT_FALSE( isUuid( "" ) );
        EXPECT_FALSE( isUuid( "550e8400-e29b-41d4-a716-44665544000" ) );   // Too short
        EXPECT_FALSE( isUuid( "550e8400-e29b-41d4-a716-4466554400000" ) ); // Too long
        EXPECT_FALSE( isUuid( "550e8400e29b41d4a716446655440000" ) );      // No hyphens
        EXPECT_FALSE( isUuid( "550e8400-e29b-41d4-a716446655440000" ) );   // Missing hyphen
        EXPECT_FALSE( isUuid( "550g8400-e29b-41d4-a716-446655440000" ) );  // Invalid hex 'g'
        EXPECT_FALSE( isUuid( "550e8400-e29b-41d4-a716-44665544000z" ) );  // Invalid char 'z'
        EXPECT_FALSE( isUuid( "550e8400_e29b_41d4_a716_446655440000" ) );  // Underscores
    }

    //----------------------------------------------
    // URI validation (RFC 3986)
    //----------------------------------------------

    TEST( FormatValidation, ValidURIs )
    {
        EXPECT_TRUE( isUri( "http://example.com" ) );
        EXPECT_TRUE( isUri( "https://example.com/path" ) );
        EXPECT_TRUE( isUri( "ftp://ftp.example.com/file.txt" ) );
        EXPECT_TRUE( isUri( "mailto:user@example.com" ) );
        EXPECT_TRUE( isUri( "file:///path/to/file" ) );
        EXPECT_TRUE( isUri( "custom-scheme://host/path" ) );
        EXPECT_TRUE( isUri( "scheme+sub://host" ) );
        EXPECT_TRUE( isUri( "scheme.sub://host" ) );
        EXPECT_TRUE( isUri( "urn:isbn:0451450523" ) );
        EXPECT_TRUE( isUri( "tel:+1-816-555-1212" ) );
    }

    TEST( FormatValidation, InvalidURIs )
    {
        EXPECT_FALSE( isUri( "" ) );
        EXPECT_FALSE( isUri( "example.com" ) );         // No scheme
        EXPECT_FALSE( isUri( "://example.com" ) );      // Empty scheme
        EXPECT_FALSE( isUri( "1http://example.com" ) ); // Scheme starts with digit
        EXPECT_FALSE( isUri( "-http://example.com" ) ); // Scheme starts with hyphen
        EXPECT_FALSE( isUri( "http ://example.com" ) ); // Space in URI
        EXPECT_FALSE( isUri( "http://example .com" ) ); // Space in URI
    }

    //----------------------------------------------
    // URI Reference validation (RFC 3986)
    //----------------------------------------------

    TEST( FormatValidation, ValidURIReferences )
    {
        // Absolute URIs
        EXPECT_TRUE( isUriReference( "http://example.com" ) );
        EXPECT_TRUE( isUriReference( "https://example.com/path" ) );

        // Relative references
        EXPECT_TRUE( isUriReference( "/path/to/resource" ) );
        EXPECT_TRUE( isUriReference( "relative/path" ) );
        EXPECT_TRUE( isUriReference( "../parent/path" ) );
        EXPECT_TRUE( isUriReference( "./current/path" ) );
        EXPECT_TRUE( isUriReference( "?query=value" ) );
        EXPECT_TRUE( isUriReference( "#fragment" ) );
        EXPECT_TRUE( isUriReference( "" ) ); // Empty is valid
    }

    TEST( FormatValidation, InvalidURIReferences )
    {
        EXPECT_FALSE( isUriReference( "path with spaces" ) );
        EXPECT_FALSE( isUriReference( "http://example .com" ) );
        EXPECT_FALSE( isUriReference( "/path\twith\ttabs" ) );
    }

    //----------------------------------------------
    // IRI validation (RFC 3987)
    //----------------------------------------------

    TEST( FormatValidation, ValidIRIs )
    {
        // ASCII IRIs (same as URIs)
        EXPECT_TRUE( isIri( "http://example.com" ) );
        EXPECT_TRUE( isIri( "https://example.com/path" ) );
        EXPECT_TRUE( isIri( "ftp://ftp.example.com/file.txt" ) );
        EXPECT_TRUE( isIri( "mailto:user@example.com" ) );
        EXPECT_TRUE( isIri( "file:///path/to/file" ) );

        // IRIs with Unicode characters
        EXPECT_TRUE( isIri( "https://example.com/路径" ) );
        EXPECT_TRUE( isIri( "https://münchen.de/über" ) );
        EXPECT_TRUE( isIri( "http://例え.jp/テスト" ) );
        EXPECT_TRUE( isIri( "https://test.com/путь" ) );
        EXPECT_TRUE( isIri( "ftp://server.com/文件" ) );

        // Custom schemes with Unicode
        EXPECT_TRUE( isIri( "custom-scheme://host/路径" ) );
        EXPECT_TRUE( isIri( "scheme+sub://münchen.de" ) );
        EXPECT_TRUE( isIri( "scheme.sub://host/中文" ) );
    }

    TEST( FormatValidation, InvalidIRIs )
    {
        EXPECT_FALSE( isIri( "" ) );                     // Empty
        EXPECT_FALSE( isIri( "example.com" ) );          // No scheme
        EXPECT_FALSE( isIri( "://example.com" ) );       // Empty scheme
        EXPECT_FALSE( isIri( "1http://example.com" ) );  // Scheme starts with digit
        EXPECT_FALSE( isIri( "-http://example.com" ) );  // Scheme starts with hyphen
        EXPECT_FALSE( isIri( "http://example.com\n" ) ); // Control character
        EXPECT_FALSE( isIri( "http://example.com\r" ) ); // Control character
    }

    //----------------------------------------------
    // IRI Reference validation (RFC 3987)
    //----------------------------------------------

    TEST( FormatValidation, ValidIRIReferences )
    {
        // Absolute IRIs
        EXPECT_TRUE( isIriReference( "http://example.com" ) );
        EXPECT_TRUE( isIriReference( "https://example.com/path" ) );
        EXPECT_TRUE( isIriReference( "https://例え.jp/テスト" ) );

        // Relative references with ASCII
        EXPECT_TRUE( isIriReference( "/path/to/resource" ) );
        EXPECT_TRUE( isIriReference( "relative/path" ) );
        EXPECT_TRUE( isIriReference( "../parent/path" ) );
        EXPECT_TRUE( isIriReference( "./current/path" ) );
        EXPECT_TRUE( isIriReference( "?query=value" ) );
        EXPECT_TRUE( isIriReference( "#fragment" ) );
        EXPECT_TRUE( isIriReference( "" ) ); // Empty is valid

        // Relative references with Unicode
        EXPECT_TRUE( isIriReference( "/路径/到/资源" ) );
        EXPECT_TRUE( isIriReference( "相对/路径" ) );
        EXPECT_TRUE( isIriReference( "../родитель/путь" ) );
        EXPECT_TRUE( isIriReference( "?запрос=значение" ) );
        EXPECT_TRUE( isIriReference( "#фрагмент" ) );
        EXPECT_TRUE( isIriReference( "über/uns" ) );
        EXPECT_TRUE( isIriReference( "ファイル.txt" ) );
    }

    TEST( FormatValidation, InvalidIRIReferences )
    {
        EXPECT_FALSE( isIriReference( "/path\nwith\nnewlines" ) ); // Control characters
        EXPECT_FALSE( isIriReference( "/path\rwith\rcarriage" ) ); // Control characters
        constexpr char nullIri[] = "path\0with\0nulls";
        EXPECT_FALSE( isIriReference( std::string_view( nullIri, sizeof( nullIri ) - 1 ) ) ); // Null characters
        EXPECT_FALSE( isIriReference( "http://example.com\n" ) );                             // Newline in IRI
    }

    //----------------------------------------------
    // JSON Pointer validation (RFC 6901)
    //----------------------------------------------

    TEST( FormatValidation, JsonPointer_Valid )
    {
        EXPECT_TRUE( isJsonPointer( "" ) );  // Root document
        EXPECT_TRUE( isJsonPointer( "/" ) ); // Empty key
        EXPECT_TRUE( isJsonPointer( "/foo" ) );
        EXPECT_TRUE( isJsonPointer( "/foo/bar" ) );
        EXPECT_TRUE( isJsonPointer( "/foo/0" ) ); // Array index
        EXPECT_TRUE( isJsonPointer( "/a~1b" ) );  // Escaped /
        EXPECT_TRUE( isJsonPointer( "/c%d" ) );   // % is allowed
        EXPECT_TRUE( isJsonPointer( "/e^f" ) );   // ^ is allowed
        EXPECT_TRUE( isJsonPointer( "/m~0n" ) );  // Escaped ~
        EXPECT_TRUE( isJsonPointer( "/foo/bar/baz/0/qux" ) );
    }

    TEST( FormatValidation, JsonPointer_Invalid )
    {
        EXPECT_FALSE( isJsonPointer( "foo" ) );     // Missing leading /
        EXPECT_FALSE( isJsonPointer( "foo/bar" ) ); // Missing leading /
        EXPECT_FALSE( isJsonPointer( "/foo~" ) );   // ~ at end
        EXPECT_FALSE( isJsonPointer( "/foo~2" ) );  // Invalid escape ~2
        EXPECT_FALSE( isJsonPointer( "/foo~a" ) );  // Invalid escape ~a
    }

    //----------------------------------------------
    // Relative JSON Pointer validation
    //----------------------------------------------

    TEST( FormatValidation, RelativeJsonPointer_Valid )
    {
        // Bare integers are valid per RFC 6901
        EXPECT_TRUE( isRelativeJsonPointer( "0" ) );   // Just zero (valid!)
        EXPECT_TRUE( isRelativeJsonPointer( "1" ) );   // Just integer (valid!)
        EXPECT_TRUE( isRelativeJsonPointer( "42" ) );  // Just integer (valid!)
        EXPECT_TRUE( isRelativeJsonPointer( "100" ) ); // Multi-digit integer (valid!)

        // Integer with # or path
        EXPECT_TRUE( isRelativeJsonPointer( "0#" ) );        // Current + name
        EXPECT_TRUE( isRelativeJsonPointer( "1#" ) );        // Parent + name
        EXPECT_TRUE( isRelativeJsonPointer( "0/foo" ) );     // Current + path
        EXPECT_TRUE( isRelativeJsonPointer( "1/foo/bar" ) ); // Parent + path
        EXPECT_TRUE( isRelativeJsonPointer( "2/0" ) );       // Grandparent + index
        EXPECT_TRUE( isRelativeJsonPointer( "0/" ) );        // Empty token
        EXPECT_TRUE( isRelativeJsonPointer( "10/foo" ) );    // Multi-digit
        EXPECT_TRUE( isRelativeJsonPointer( "0/a~0b" ) );    // With escape
    }

    TEST( FormatValidation, RelativeJsonPointer_Invalid )
    {
        EXPECT_FALSE( isRelativeJsonPointer( "" ) );       // Empty
        EXPECT_FALSE( isRelativeJsonPointer( "#" ) );      // Missing number
        EXPECT_FALSE( isRelativeJsonPointer( "/foo" ) );   // Absolute pointer
        EXPECT_FALSE( isRelativeJsonPointer( "01/foo" ) ); // Leading zero (with path)
        EXPECT_FALSE( isRelativeJsonPointer( "01" ) );     // Leading zero (bare)
        EXPECT_FALSE( isRelativeJsonPointer( "01#" ) );    // Leading zero (with #)
        EXPECT_FALSE( isRelativeJsonPointer( "-1/foo" ) ); // Negative
        EXPECT_FALSE( isRelativeJsonPointer( "-1" ) );     // Negative bare
        EXPECT_FALSE( isRelativeJsonPointer( "a/foo" ) );  // Non-digit start
        EXPECT_FALSE( isRelativeJsonPointer( "0#foo" ) );  // # not at end
        EXPECT_FALSE( isRelativeJsonPointer( "1#2" ) );    // # in middle
    }
} // namespace nfx::string::test
