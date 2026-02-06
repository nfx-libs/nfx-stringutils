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
 * @file TESTS_EscapeUnescape.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // JSON Escape/Unescape
    //=====================================================================

    TEST( EscapeUnescape, JSON_BasicEscaping )
    {
        // No escaping needed
        EXPECT_EQ( "hello world", jsonEscape( "hello world" ) );
        EXPECT_EQ( "abc123", jsonEscape( "abc123" ) );
        EXPECT_EQ( "", jsonEscape( "" ) );

        // Quote escaping
        EXPECT_EQ( "\\\"quoted\\\"", jsonEscape( "\"quoted\"" ) );
        EXPECT_EQ( "say \\\"hello\\\"", jsonEscape( "say \"hello\"" ) );

        // Backslash escaping
        EXPECT_EQ( "\\\\", jsonEscape( "\\" ) );
        EXPECT_EQ( "path\\\\to\\\\file", jsonEscape( "path\\to\\file" ) );

        // Forward slash escaping
        EXPECT_EQ( "path\\/to\\/file", jsonEscape( "path/to/file" ) );
    }

    TEST( EscapeUnescape, JSON_ControlCharacters )
    {
        // Standard escape sequences
        EXPECT_EQ( "\\b", jsonEscape( "\b" ) ); // backspace
        EXPECT_EQ( "\\f", jsonEscape( "\f" ) ); // form feed
        EXPECT_EQ( "\\n", jsonEscape( "\n" ) ); // newline
        EXPECT_EQ( "\\r", jsonEscape( "\r" ) ); // carriage return
        EXPECT_EQ( "\\t", jsonEscape( "\t" ) ); // tab

        // Multiple control characters
        EXPECT_EQ( "line1\\nline2", jsonEscape( "line1\nline2" ) );
        EXPECT_EQ( "col1\\tcol2", jsonEscape( "col1\tcol2" ) );
        EXPECT_EQ( "\\r\\n", jsonEscape( "\r\n" ) );

        // Other control characters (escaped as \uXXXX)
        EXPECT_EQ( "\\u0000", jsonEscape( std::string( 1, '\0' ) ) );
        EXPECT_EQ( "\\u0001", jsonEscape( "\x01" ) );
        EXPECT_EQ( "\\u001F", jsonEscape( "\x1F" ) );
    }

    TEST( EscapeUnescape, JSON_MixedContent )
    {
        // Mixed special characters
        EXPECT_EQ( "line1\\nline2\\tvalue", jsonEscape( "line1\nline2\tvalue" ) );
        EXPECT_EQ( "\\\"key\\\": \\\"value\\\"", jsonEscape( "\"key\": \"value\"" ) );
        EXPECT_EQ( "path\\\\file\\nend", jsonEscape( "path\\file\nend" ) );

        // Real JSON-like content
        EXPECT_EQ( "{\\\"name\\\": \\\"John\\\"}", jsonEscape( "{\"name\": \"John\"}" ) );
    }

    TEST( EscapeUnescape, JSON_BasicUnescaping )
    {
        // No unescaping needed
        EXPECT_EQ( "hello world", jsonUnescape( "hello world" ) );
        EXPECT_EQ( "abc123", jsonUnescape( "abc123" ) );
        EXPECT_EQ( "", jsonUnescape( "" ) );

        // Quote unescaping
        EXPECT_EQ( "\"quoted\"", jsonUnescape( "\\\"quoted\\\"" ) );
        EXPECT_EQ( "say \"hello\"", jsonUnescape( "say \\\"hello\\\"" ) );

        // Backslash unescaping
        EXPECT_EQ( "\\", jsonUnescape( "\\\\" ) );
        EXPECT_EQ( "path\\to\\file", jsonUnescape( "path\\\\to\\\\file" ) );

        // Forward slash unescaping
        EXPECT_EQ( "path/to/file", jsonUnescape( "path\\/to\\/file" ) );
    }

    TEST( EscapeUnescape, JSON_UnescapeControlCharacters )
    {
        // Standard escape sequences
        EXPECT_EQ( "\b", jsonUnescape( "\\b" ) );
        EXPECT_EQ( "\f", jsonUnescape( "\\f" ) );
        EXPECT_EQ( "\n", jsonUnescape( "\\n" ) );
        EXPECT_EQ( "\r", jsonUnescape( "\\r" ) );
        EXPECT_EQ( "\t", jsonUnescape( "\\t" ) );

        // Multiple control characters
        EXPECT_EQ( "line1\nline2", jsonUnescape( "line1\\nline2" ) );
        EXPECT_EQ( "col1\tcol2", jsonUnescape( "col1\\tcol2" ) );
        EXPECT_EQ( "\r\n", jsonUnescape( "\\r\\n" ) );
    }

    TEST( EscapeUnescape, JSON_UnicodeEscapes )
    {
        // ASCII characters via Unicode
        EXPECT_EQ( "A", jsonUnescape( "\\u0041" ) );
        EXPECT_EQ( "z", jsonUnescape( "\\u007A" ) );
        EXPECT_EQ( "0", jsonUnescape( "\\u0030" ) );

        // Control characters via Unicode
        EXPECT_EQ( std::string( 1, '\0' ), jsonUnescape( "\\u0000" ) );
        EXPECT_EQ( "\x01", jsonUnescape( "\\u0001" ) );
        EXPECT_EQ( "\x1F", jsonUnescape( "\\u001F" ) );

        // Latin-1 supplement (2-byte UTF-8)
        EXPECT_EQ( "é", jsonUnescape( "\\u00E9" ) ); // U+00E9
        EXPECT_EQ( "ñ", jsonUnescape( "\\u00F1" ) ); // U+00F1
        EXPECT_EQ( "ü", jsonUnescape( "\\u00FC" ) ); // U+00FC

        // BMP characters (3-byte UTF-8)
        EXPECT_EQ( "€", jsonUnescape( "\\u20AC" ) );  // U+20AC Euro sign
        EXPECT_EQ( "™", jsonUnescape( "\\u2122" ) );  // U+2122 Trademark
        EXPECT_EQ( "→", jsonUnescape( "\\u2192" ) );  // U+2192 Right arrow
        EXPECT_EQ( "中", jsonUnescape( "\\u4E2D" ) ); // U+4E2D Chinese character

        // Mixed
        EXPECT_EQ( "café", jsonUnescape( "caf\\u00E9" ) );
        EXPECT_EQ( "hello→world", jsonUnescape( "hello\\u2192world" ) );
    }

    TEST( EscapeUnescape, JSON_UnescapeMixedContent )
    {
        // Mixed special characters
        EXPECT_EQ( "line1\nline2\tvalue", jsonUnescape( "line1\\nline2\\tvalue" ) );
        EXPECT_EQ( "\"key\": \"value\"", jsonUnescape( "\\\"key\\\": \\\"value\\\"" ) );
        EXPECT_EQ( "path\\file\nend", jsonUnescape( "path\\\\file\\nend" ) );

        // Real JSON-like content
        EXPECT_EQ( "{\"name\": \"John\"}", jsonUnescape( "{\\\"name\\\": \\\"John\\\"}" ) );
    }

    TEST( EscapeUnescape, JSON_MalformedInput )
    {
        // Invalid: backslash at end
        EXPECT_EQ( "", jsonUnescape( "test\\" ) );

        // Invalid: unknown escape sequence
        EXPECT_EQ( "", jsonUnescape( "\\x" ) );
        EXPECT_EQ( "", jsonUnescape( "\\q" ) );

        // Invalid: incomplete Unicode escape
        EXPECT_EQ( "", jsonUnescape( "\\u" ) );
        EXPECT_EQ( "", jsonUnescape( "\\u0" ) );
        EXPECT_EQ( "", jsonUnescape( "\\u00" ) );
        EXPECT_EQ( "", jsonUnescape( "\\u000" ) );

        // Invalid: non-hex in Unicode escape
        EXPECT_EQ( "", jsonUnescape( "\\u00GG" ) );
        EXPECT_EQ( "", jsonUnescape( "\\uXXXX" ) );
        EXPECT_EQ( "", jsonUnescape( "\\u12ZZ" ) );
    }

    TEST( EscapeUnescape, JSON_RoundTripEscaping )
    {
        // Test that escape/unescape round-trips correctly
        std::vector<std::string> test_strings = {
            "hello world",
            "\"quoted\"",
            "path\\to\\file",
            "line1\nline2\ttab",
            "{\"key\": \"value\"}",
            "control: \b\f\n\r\t",
            std::string( 1, '\0' ) + "null char",
            "unicode: café ñoël 中文",
            "mixed \n\t\"test\"\\ end",
            "",
            "a",
            "special: !@#$%^&*()",
            "\x01\x02\x1F" // control chars
        };

        for ( const auto& original : test_strings )
        {
            std::string escaped = jsonEscape( original );
            std::string unescaped = jsonUnescape( escaped );
            EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
        }
    }

    TEST( EscapeUnescape, JSON_RealWorldExamples )
    {
        // JSON object
        std::string jsonObj = R"({"name":"John","age":30})";
        std::string escaped = jsonEscape( jsonObj );
        EXPECT_EQ( "{\\\"name\\\":\\\"John\\\",\\\"age\\\":30}", escaped );
        EXPECT_EQ( jsonObj, jsonUnescape( escaped ) );

        // Multiline text
        std::string multiline = "line1\nline2\nline3";
        escaped = jsonEscape( multiline );
        EXPECT_EQ( "line1\\nline2\\nline3", escaped );
        EXPECT_EQ( multiline, jsonUnescape( escaped ) );

        // Error message with quotes
        std::string error = "Error: \"file not found\"";
        escaped = jsonEscape( error );
        EXPECT_EQ( "Error: \\\"file not found\\\"", escaped );
        EXPECT_EQ( error, jsonUnescape( escaped ) );

        // Path with backslashes
        std::string path = "C:\\Users\\John\\Documents";
        escaped = jsonEscape( path );
        EXPECT_EQ( "C:\\\\Users\\\\John\\\\Documents", escaped );
        EXPECT_EQ( path, jsonUnescape( escaped ) );
    }

    TEST( EscapeUnescape, JSON_EdgeCases )
    {
        // All control characters
        for ( int i = 0; i < 32; ++i )
        {
            std::string test( 1, static_cast<char>( i ) );
            std::string escaped = jsonEscape( test );
            std::string unescaped = jsonUnescape( escaped );
            EXPECT_EQ( test, unescaped ) << "Failed for control char: " << i;
        }

        // All printable ASCII
        for ( int i = 32; i < 127; ++i )
        {
            std::string test( 1, static_cast<char>( i ) );
            std::string escaped = jsonEscape( test );
            std::string unescaped = jsonUnescape( escaped );
            EXPECT_EQ( test, unescaped ) << "Failed for ASCII: " << i;
        }

        // Long strings
        std::string long_text( 1000, 'a' );
        EXPECT_EQ( long_text, jsonUnescape( jsonEscape( long_text ) ) );

        std::string long_newlines( 1000, '\n' );
        std::string escaped_newlines = jsonEscape( long_newlines );
        EXPECT_EQ( long_newlines, jsonUnescape( escaped_newlines ) );
    }

    //=====================================================================
    // XML/HTML Escape/Unescape
    //=====================================================================

    TEST( EscapeUnescape, XML_BasicEscaping )
    {
        // No escaping needed
        EXPECT_EQ( "hello world", xmlEscape( "hello world" ) );
        EXPECT_EQ( "abc123", xmlEscape( "abc123" ) );
        EXPECT_EQ( "", xmlEscape( "" ) );

        // Ampersand escaping
        EXPECT_EQ( "AT&amp;T", xmlEscape( "AT&T" ) );
        EXPECT_EQ( "Tom &amp; Jerry", xmlEscape( "Tom & Jerry" ) );

        // Less-than escaping
        EXPECT_EQ( "a &lt; b", xmlEscape( "a < b" ) );
        EXPECT_EQ( "&lt;tag&gt;", xmlEscape( "<tag>" ) );

        // Greater-than escaping
        EXPECT_EQ( "a &gt; b", xmlEscape( "a > b" ) );

        // Quote escaping
        EXPECT_EQ( "&quot;quoted&quot;", xmlEscape( "\"quoted\"" ) );
        EXPECT_EQ( "say &quot;hello&quot;", xmlEscape( "say \"hello\"" ) );

        // Apostrophe escaping
        EXPECT_EQ( "it&apos;s", xmlEscape( "it's" ) );
        EXPECT_EQ( "&apos;single&apos;", xmlEscape( "'single'" ) );
    }

    TEST( EscapeUnescape, XML_MixedContent )
    {
        // Multiple special characters
        EXPECT_EQ( "&lt;tag attr=&quot;value&quot;&gt;", xmlEscape( "<tag attr=\"value\">" ) );
        EXPECT_EQ( "A &amp; B &lt; C &gt; D", xmlEscape( "A & B < C > D" ) );
        EXPECT_EQ( "&apos;It&apos;s &quot;fine&quot;&apos;", xmlEscape( "'It's \"fine\"'" ) );

        // Real XML-like content
        EXPECT_EQ( "&lt;p&gt;Hello &amp; goodbye&lt;/p&gt;", xmlEscape( "<p>Hello & goodbye</p>" ) );
    }

    TEST( EscapeUnescape, XML_RealWorldExamples )
    {
        // XML element
        std::string xml = "<name>John & Jane</name>";
        EXPECT_EQ( "&lt;name&gt;John &amp; Jane&lt;/name&gt;", xmlEscape( xml ) );

        // HTML with quotes
        std::string html = "<a href=\"page.html\">Link</a>";
        EXPECT_EQ( "&lt;a href=&quot;page.html&quot;&gt;Link&lt;/a&gt;", xmlEscape( html ) );

        // SQL-like content
        std::string sql = "SELECT * FROM table WHERE x > 5 AND y < 10";
        EXPECT_EQ( "SELECT * FROM table WHERE x &gt; 5 AND y &lt; 10", xmlEscape( sql ) );
    }

    TEST( EscapeUnescape, XML_BasicUnescaping )
    {
        // No unescaping needed
        EXPECT_EQ( "hello world", xmlUnescape( "hello world" ) );
        EXPECT_EQ( "abc123", xmlUnescape( "abc123" ) );
        EXPECT_EQ( "", xmlUnescape( "" ) );

        // Ampersand unescaping
        EXPECT_EQ( "AT&T", xmlUnescape( "AT&amp;T" ) );
        EXPECT_EQ( "Tom & Jerry", xmlUnescape( "Tom &amp; Jerry" ) );

        // Less-than unescaping
        EXPECT_EQ( "a < b", xmlUnescape( "a &lt; b" ) );
        EXPECT_EQ( "<tag>", xmlUnescape( "&lt;tag&gt;" ) );

        // Greater-than unescaping
        EXPECT_EQ( "a > b", xmlUnescape( "a &gt; b" ) );

        // Quote unescaping
        EXPECT_EQ( "\"quoted\"", xmlUnescape( "&quot;quoted&quot;" ) );
        EXPECT_EQ( "say \"hello\"", xmlUnescape( "say &quot;hello&quot;" ) );

        // Apostrophe unescaping
        EXPECT_EQ( "it's", xmlUnescape( "it&apos;s" ) );
        EXPECT_EQ( "'single'", xmlUnescape( "&apos;single&apos;" ) );
    }

    TEST( EscapeUnescape, XML_NumericEntities )
    {
        // Decimal numeric character references
        EXPECT_EQ( "A", xmlUnescape( "&#65;" ) );   // ASCII 'A'
        EXPECT_EQ( "0", xmlUnescape( "&#48;" ) );   // ASCII '0'
        EXPECT_EQ( " ", xmlUnescape( "&#32;" ) );   // Space
        EXPECT_EQ( "é", xmlUnescape( "&#233;" ) );  // Latin small letter e with acute
        EXPECT_EQ( "©", xmlUnescape( "&#169;" ) );  // Copyright sign
        EXPECT_EQ( "€", xmlUnescape( "&#8364;" ) ); // Euro sign

        // Hexadecimal numeric character references
        EXPECT_EQ( "A", xmlUnescape( "&#x41;" ) );    // ASCII 'A'
        EXPECT_EQ( "0", xmlUnescape( "&#x30;" ) );    // ASCII '0'
        EXPECT_EQ( " ", xmlUnescape( "&#x20;" ) );    // Space
        EXPECT_EQ( "é", xmlUnescape( "&#xE9;" ) );    // e-acute (lowercase hex)
        EXPECT_EQ( "é", xmlUnescape( "&#xE9;" ) );    // e-acute (uppercase hex)
        EXPECT_EQ( "©", xmlUnescape( "&#xA9;" ) );    // Copyright
        EXPECT_EQ( "€", xmlUnescape( "&#x20AC;" ) );  // Euro sign
        EXPECT_EQ( "中", xmlUnescape( "&#x4E2D;" ) ); // Chinese character

        // Mixed in text
        EXPECT_EQ( "Price: €10", xmlUnescape( "Price: &#8364;10" ) );
        EXPECT_EQ( "Copyright © 2025", xmlUnescape( "Copyright &#169; 2025" ) );
    }

    TEST( EscapeUnescape, XML_UnescapeMixedContent )
    {
        // Multiple entities
        EXPECT_EQ( "<tag attr=\"value\">", xmlUnescape( "&lt;tag attr=&quot;value&quot;&gt;" ) );
        EXPECT_EQ( "A & B < C > D", xmlUnescape( "A &amp; B &lt; C &gt; D" ) );
        EXPECT_EQ( "'It's \"fine\"'", xmlUnescape( "&apos;It&apos;s &quot;fine&quot;&apos;" ) );

        // Real XML-like content
        EXPECT_EQ( "<p>Hello & goodbye</p>", xmlUnescape( "&lt;p&gt;Hello &amp; goodbye&lt;/p&gt;" ) );

        // Mix of entities and numeric references
        EXPECT_EQ( "< & >", xmlUnescape( "&lt; &#38; &gt;" ) );
        EXPECT_EQ( "café", xmlUnescape( "caf&#233;" ) );
    }

    TEST( EscapeUnescape, XML_MalformedInput )
    {
        // Invalid: ampersand without semicolon
        EXPECT_EQ( "", xmlUnescape( "test & more" ) );
        EXPECT_EQ( "", xmlUnescape( "test &amp more" ) );

        // Invalid: unknown entity
        EXPECT_EQ( "", xmlUnescape( "&unknown;" ) );
        EXPECT_EQ( "", xmlUnescape( "&xyz;" ) );

        // Invalid: incomplete entity
        EXPECT_EQ( "", xmlUnescape( "&" ) );
        EXPECT_EQ( "", xmlUnescape( "&a" ) );

        // Invalid: malformed numeric entity
        EXPECT_EQ( "", xmlUnescape( "&#;" ) );
        EXPECT_EQ( "", xmlUnescape( "&#x;" ) );
        EXPECT_EQ( "", xmlUnescape( "&#xGG;" ) );
        EXPECT_EQ( "", xmlUnescape( "&#xyz;" ) );

        // Invalid: codepoint out of range
        EXPECT_EQ( "", xmlUnescape( "&#x110000;" ) ); // Beyond valid Unicode range
    }

    TEST( EscapeUnescape, XML_RoundTripEscaping )
    {
        // Test that escape/unescape round-trips correctly
        std::vector<std::string> test_strings = {
            "hello world",
            "<tag>",
            "AT&T",
            "a < b > c",
            "\"quoted\" and 'apostrophe'",
            "<p>Text & more</p>",
            "<a href=\"link.html\">Click</a>",
            "",
            "a",
            "Tom & Jerry's \"show\"",
            "x < y && y > z" };

        for ( const auto& original : test_strings )
        {
            std::string escaped = xmlEscape( original );
            std::string unescaped = xmlUnescape( escaped );
            EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
        }
    }

    TEST( EscapeUnescape, XML_RoundTripWithEntities )
    {
        // XML document fragment
        std::string xmlFrag = "<person name=\"John & Jane\">Data</person>";
        std::string escaped = xmlEscape( xmlFrag );
        EXPECT_EQ( "&lt;person name=&quot;John &amp; Jane&quot;&gt;Data&lt;/person&gt;", escaped );
        EXPECT_EQ( xmlFrag, xmlUnescape( escaped ) );

        // HTML attribute
        std::string html = "<img src=\"image.png\" alt=\"A > B\">";
        escaped = xmlEscape( html );
        EXPECT_EQ( "&lt;img src=&quot;image.png&quot; alt=&quot;A &gt; B&quot;&gt;", escaped );
        EXPECT_EQ( html, xmlUnescape( escaped ) );

        // Text with special chars
        std::string text = "R&D's result: x < 5 & y > 3";
        escaped = xmlEscape( text );
        EXPECT_EQ( "R&amp;D&apos;s result: x &lt; 5 &amp; y &gt; 3", escaped );
        EXPECT_EQ( text, xmlUnescape( escaped ) );
    }

    TEST( EscapeUnescape, XML_EdgeCases )
    {
        // All special characters
        EXPECT_EQ( "&amp;&lt;&gt;&quot;&apos;", xmlEscape( "&<>\"'" ) );
        EXPECT_EQ( "&<>\"'", xmlUnescape( "&amp;&lt;&gt;&quot;&apos;" ) );

        // Consecutive special chars
        EXPECT_EQ( "&amp;&amp;&amp;", xmlEscape( "&&&" ) );
        EXPECT_EQ( "&lt;&lt;&lt;", xmlEscape( "<<<" ) );

        // Long strings
        std::string long_text( 1000, 'a' );
        EXPECT_EQ( long_text, xmlUnescape( xmlEscape( long_text ) ) );

        std::string long_ampersands( 1000, '&' );
        std::string escaped_ampersands = xmlEscape( long_ampersands );
        EXPECT_EQ( long_ampersands, xmlUnescape( escaped_ampersands ) );

        // Unicode characters (should pass through unchanged)
        std::string unicode = "café ñoël €10 中文";
        EXPECT_EQ( unicode, xmlEscape( unicode ) );

        // Mix with numeric entities
        EXPECT_EQ( "café", xmlUnescape( "caf&#xE9;" ) );
        EXPECT_EQ( "€", xmlUnescape( "&#x20AC;" ) );
    }

    //=====================================================================
    // C/C++ Escape/Unescape
    //=====================================================================

    TEST( EscapeUnescape, Cpp_BasicEscaping )
    {
        // No escaping needed
        EXPECT_EQ( "hello world", cppEscape( "hello world" ) );
        EXPECT_EQ( "abc123", cppEscape( "abc123" ) );
        EXPECT_EQ( "", cppEscape( "" ) );

        // Newline
        EXPECT_EQ( "line1\\nline2", cppEscape( "line1\nline2" ) );

        // Tab
        EXPECT_EQ( "col1\\tcol2", cppEscape( "col1\tcol2" ) );

        // Carriage return
        EXPECT_EQ( "text\\rmore", cppEscape( "text\rmore" ) );

        // Backslash
        EXPECT_EQ( "path\\\\to\\\\file", cppEscape( "path\\to\\file" ) );

        // Double quote
        EXPECT_EQ( "say \\\"hello\\\"", cppEscape( "say \"hello\"" ) );

        // Single quote
        EXPECT_EQ( "it\\'s", cppEscape( "it's" ) );

        // Null character
        EXPECT_EQ( "null\\0char", cppEscape( std::string( "null\0char", 9 ) ) );
    }

    TEST( EscapeUnescape, Cpp_ControlCharacters )
    {
        // Standard escape sequences
        EXPECT_EQ( "\\b", cppEscape( "\b" ) ); // backspace
        EXPECT_EQ( "\\f", cppEscape( "\f" ) ); // form feed
        EXPECT_EQ( "\\v", cppEscape( "\v" ) ); // vertical tab
        EXPECT_EQ( "\\a", cppEscape( "\a" ) ); // alert (bell)

        // Other control characters (as \xHH)
        EXPECT_EQ( "\\x01", cppEscape( "\x01" ) );
        EXPECT_EQ( "\\x1f", cppEscape( "\x1F" ) );
        EXPECT_EQ( "\\x7f", cppEscape( "\x7F" ) ); // DEL character
    }

    TEST( EscapeUnescape, Cpp_MixedContent )
    {
        // Multiple escape sequences
        EXPECT_EQ( "line1\\nline2\\ttab", cppEscape( "line1\nline2\ttab" ) );
        EXPECT_EQ( "path\\\\file\\nend", cppEscape( "path\\file\nend" ) );
        EXPECT_EQ( "\\\"quoted\\\" text", cppEscape( "\"quoted\" text" ) );

        // Mix of printable and control chars
        EXPECT_EQ( "hello\\nworld\\t!", cppEscape( "hello\nworld\t!" ) );
    }

    TEST( EscapeUnescape, Cpp_BasicUnescaping )
    {
        // No unescaping needed
        EXPECT_EQ( "hello world", cppUnescape( "hello world" ) );
        EXPECT_EQ( "abc123", cppUnescape( "abc123" ) );
        EXPECT_EQ( "", cppUnescape( "" ) );

        // Newline
        EXPECT_EQ( "line1\nline2", cppUnescape( "line1\\nline2" ) );

        // Tab
        EXPECT_EQ( "col1\tcol2", cppUnescape( "col1\\tcol2" ) );

        // Carriage return
        EXPECT_EQ( "text\rmore", cppUnescape( "text\\rmore" ) );

        // Backslash
        EXPECT_EQ( "path\\to\\file", cppUnescape( "path\\\\to\\\\file" ) );

        // Double quote
        EXPECT_EQ( "say \"hello\"", cppUnescape( "say \\\"hello\\\"" ) );

        // Single quote
        EXPECT_EQ( "it's", cppUnescape( "it\\'s" ) );

        // Null character
        EXPECT_EQ( std::string( "null\0char", 9 ), cppUnescape( "null\\0char" ) );
    }

    TEST( EscapeUnescape, Cpp_UnescapeControlCharacters )
    {
        // Standard escape sequences
        EXPECT_EQ( "\b", cppUnescape( "\\b" ) );
        EXPECT_EQ( "\f", cppUnescape( "\\f" ) );
        EXPECT_EQ( "\v", cppUnescape( "\\v" ) );
        EXPECT_EQ( "\a", cppUnescape( "\\a" ) );

        // Multiple control characters
        EXPECT_EQ( "\n\t\r", cppUnescape( "\\n\\t\\r" ) );
    }

    TEST( EscapeUnescape, Cpp_HexadecimalEscapes )
    {
        // Hexadecimal escape sequences
        EXPECT_EQ( "\x01", cppUnescape( "\\x01" ) );
        EXPECT_EQ( "\x0F", cppUnescape( "\\x0f" ) );
        EXPECT_EQ( "\x0F", cppUnescape( "\\x0F" ) ); // uppercase
        EXPECT_EQ( "\x1F", cppUnescape( "\\x1f" ) );
        EXPECT_EQ( "\x7F", cppUnescape( "\\x7f" ) );
        EXPECT_EQ( "\xFF", cppUnescape( "\\xff" ) );

        // Mixed with text
        EXPECT_EQ( "A\x01Z", cppUnescape( "A\\x01Z" ) );
        EXPECT_EQ( "test\x1Fvalue", cppUnescape( "test\\x1fvalue" ) );
    }

    TEST( EscapeUnescape, Cpp_OctalEscapes )
    {
        // Octal escape sequences
        EXPECT_EQ( std::string( 1, '\0' ), cppUnescape( "\\0" ) );
        EXPECT_EQ( "\001", cppUnescape( "\\001" ) );
        EXPECT_EQ( "\007", cppUnescape( "\\007" ) );
        EXPECT_EQ( "\010", cppUnescape( "\\010" ) ); // backspace
        EXPECT_EQ( "\012", cppUnescape( "\\012" ) ); // newline
        EXPECT_EQ( "\177", cppUnescape( "\\177" ) ); // DEL

        // Octal with fewer than 3 digits
        EXPECT_EQ( "\1", cppUnescape( "\\1" ) );
        EXPECT_EQ( "\7", cppUnescape( "\\7" ) );
        EXPECT_EQ( "\10", cppUnescape( "\\10" ) );
        EXPECT_EQ( "\77", cppUnescape( "\\77" ) );

        // Mixed with text
        EXPECT_EQ( "A\001Z", cppUnescape( "A\\001Z" ) );
    }

    TEST( EscapeUnescape, Cpp_UnescapeMixedContent )
    {
        // Multiple escape sequences
        EXPECT_EQ( "line1\nline2\ttab", cppUnescape( "line1\\nline2\\ttab" ) );
        EXPECT_EQ( "path\\file\nend", cppUnescape( "path\\\\file\\nend" ) );
        EXPECT_EQ( "\"quoted\" text", cppUnescape( "\\\"quoted\\\" text" ) );

        // Mix of different escape types
        EXPECT_EQ( "A\nB\tC\\D", cppUnescape( "A\\nB\\tC\\\\D" ) );
        EXPECT_EQ( "hex:\x0Aoctal:\012", cppUnescape( "hex:\\x0Aoctal:\\012" ) );
    }

    TEST( EscapeUnescape, Cpp_MalformedInput )
    {
        // Invalid: backslash at end
        EXPECT_EQ( "", cppUnescape( "test\\" ) );

        // Invalid: unknown escape sequence
        EXPECT_EQ( "", cppUnescape( "\\q" ) );
        EXPECT_EQ( "", cppUnescape( "\\z" ) );

        // Invalid: incomplete hex escape
        EXPECT_EQ( "", cppUnescape( "\\x" ) );
        EXPECT_EQ( "", cppUnescape( "\\x0" ) );

        // Invalid: non-hex in hex escape
        EXPECT_EQ( "", cppUnescape( "\\xGG" ) );
        EXPECT_EQ( "", cppUnescape( "\\xZZ" ) );

        // Invalid: octal value out of range
        EXPECT_EQ( "", cppUnescape( "\\400" ) ); // 256 in octal
        EXPECT_EQ( "", cppUnescape( "\\777" ) ); // 511 in octal
    }

    TEST( EscapeUnescape, Cpp_RoundTripEscaping )
    {
        // Test that escape/unescape round-trips correctly
        std::vector<std::string> test_strings = {
            "hello world",
            "line1\nline2",
            "col1\tcol2",
            "path\\to\\file",
            "\"quoted\"",
            "it's fine",
            std::string( "null\0inside", 11 ),
            "all: \n\t\r\\\"\'\b\f\v\a",
            "\x01\x02\x1F\x7F",
            "",
            "a",
            "normal text 123" };

        for ( const auto& original : test_strings )
        {
            std::string escaped = cppEscape( original );
            std::string unescaped = cppUnescape( escaped );
            EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
        }
    }

    TEST( EscapeUnescape, Cpp_RealWorldExamples )
    {
        // Code generation
        std::string code = "std::string msg = \"Hello\\nWorld\";";
        std::string escaped = cppEscape( code );
        EXPECT_EQ( "std::string msg = \\\"Hello\\\\nWorld\\\";", escaped );
        EXPECT_EQ( code, cppUnescape( escaped ) );

        // File paths
        std::string path = "C:\\Users\\John\\Documents";
        escaped = cppEscape( path );
        EXPECT_EQ( "C:\\\\Users\\\\John\\\\Documents", escaped );
        EXPECT_EQ( path, cppUnescape( escaped ) );

        // Multi-line text
        std::string multiline = "Line 1\nLine 2\nLine 3";
        escaped = cppEscape( multiline );
        EXPECT_EQ( "Line 1\\nLine 2\\nLine 3", escaped );
        EXPECT_EQ( multiline, cppUnescape( escaped ) );

        // SQL query
        std::string sql = "SELECT * FROM users WHERE name = \"John\"";
        escaped = cppEscape( sql );
        EXPECT_EQ( "SELECT * FROM users WHERE name = \\\"John\\\"", escaped );
        EXPECT_EQ( sql, cppUnescape( escaped ) );
    }

    TEST( EscapeUnescape, EdgeCases )
    {
        // All printable ASCII
        for ( int i = 32; i < 127; ++i )
        {
            if ( i == '\\' || i == '"' || i == '\'' )
                continue; // These get escaped

            std::string test( 1, static_cast<char>( i ) );
            std::string escaped = cppEscape( test );
            std::string unescaped = cppUnescape( escaped );
            EXPECT_EQ( test, unescaped ) << "Failed for ASCII: " << i;
        }

        // All control characters
        for ( int i = 0; i < 32; ++i )
        {
            std::string test( 1, static_cast<char>( i ) );
            std::string escaped = cppEscape( test );
            std::string unescaped = cppUnescape( escaped );
            EXPECT_EQ( test, unescaped ) << "Failed for control char: " << i;
        }

        // DEL character
        std::string del( 1, '\x7F' );
        EXPECT_EQ( del, cppUnescape( cppEscape( del ) ) );

        // Long strings
        std::string long_text( 1000, 'a' );
        EXPECT_EQ( long_text, cppUnescape( cppEscape( long_text ) ) );

        std::string long_newlines( 1000, '\n' );
        std::string escaped_newlines = cppEscape( long_newlines );
        EXPECT_EQ( long_newlines, cppUnescape( escaped_newlines ) );
    }

    //=====================================================================
    // UTF-8 Utilities
    //=====================================================================

    TEST( UTF8, DecodeCodepoint_ASCII )
    {
        std::string_view str = "Hello";
        std::size_t i = 0;
        uint32_t codepoint = 0;

        // 'H'
        EXPECT_TRUE( decodeUtf8Codepoint( str, i, codepoint ) );
        EXPECT_EQ( 'H', codepoint );
        EXPECT_EQ( 1, i );

        // 'e'
        EXPECT_TRUE( decodeUtf8Codepoint( str, i, codepoint ) );
        EXPECT_EQ( 'e', codepoint );
        EXPECT_EQ( 2, i );
    }

    TEST( UTF8, DecodeCodepoint_TwoByte )
    {
        // Latin Small Letter E with Acute (é) - U+00E9
        std::string_view str = "café";
        std::size_t i = 3; // Position of é
        uint32_t codepoint = 0;

        EXPECT_TRUE( decodeUtf8Codepoint( str, i, codepoint ) );
        EXPECT_EQ( 0x00E9, codepoint );
        EXPECT_EQ( 5, i ); // Moved 2 bytes forward
    }

    TEST( UTF8, DecodeCodepoint_ThreeByte )
    {
        // Euro Sign (€) - U+20AC
        std::string_view str = "100€";
        std::size_t i = 3;
        uint32_t codepoint = 0;

        EXPECT_TRUE( decodeUtf8Codepoint( str, i, codepoint ) );
        EXPECT_EQ( 0x20AC, codepoint );
        EXPECT_EQ( 6, i );
    }

    TEST( UTF8, DecodeCodepoint_FourByte )
    {
        // Emoji (😀) - U+1F600
        std::string_view str = "😀";
        std::size_t i = 0;
        uint32_t codepoint = 0;

        EXPECT_TRUE( decodeUtf8Codepoint( str, i, codepoint ) );
        EXPECT_EQ( 0x1F600, codepoint );
        EXPECT_EQ( 4, i );
    }

    TEST( UTF8, DecodeCodepoint_InvalidSequences )
    {
        std::size_t i = 0;
        uint32_t codepoint = 0;

        // Truncated sequence
        std::string_view truncated = "\xC3"; // Missing second byte
        i = 0;
        EXPECT_FALSE( decodeUtf8Codepoint( truncated, i, codepoint ) );

        // Invalid continuation byte
        std::string_view invalid = "\xC3\x00";
        i = 0;
        EXPECT_FALSE( decodeUtf8Codepoint( invalid, i, codepoint ) );

        // Overlong encoding (U+0000 encoded as 2 bytes)
        std::string_view overlong = "\xC0\x80";
        i = 0;
        EXPECT_FALSE( decodeUtf8Codepoint( overlong, i, codepoint ) );

        // Surrogate pair (U+D800)
        std::string_view surrogate = "\xED\xA0\x80";
        i = 0;
        EXPECT_FALSE( decodeUtf8Codepoint( surrogate, i, codepoint ) );

        // Out of range (> U+10FFFF)
        std::string_view outofrange = "\xF4\x90\x80\x80";
        i = 0;
        EXPECT_FALSE( decodeUtf8Codepoint( outofrange, i, codepoint ) );
    }

    TEST( UTF8, EncodeCodepoint_ASCII )
    {
        std::string result;
        encodeUtf8Codepoint( result, 'A' );
        EXPECT_EQ( "A", result );

        result.clear();
        encodeUtf8Codepoint( result, 0x00 );
        EXPECT_EQ( std::string( 1, '\0' ), result );
    }

    TEST( UTF8, EncodeCodepoint_TwoByte )
    {
        std::string result;
        encodeUtf8Codepoint( result, 0x00E9 ); // é
        EXPECT_EQ( "é", result );

        result.clear();
        encodeUtf8Codepoint( result, 0x00A9 ); // ©
        EXPECT_EQ( "©", result );
    }

    TEST( UTF8, EncodeCodepoint_ThreeByte )
    {
        std::string result;
        encodeUtf8Codepoint( result, 0x20AC ); // €
        EXPECT_EQ( "€", result );

        result.clear();
        encodeUtf8Codepoint( result, 0x4E2D ); // 中
        EXPECT_EQ( "中", result );
    }

    TEST( UTF8, EncodeCodepoint_FourByte )
    {
        std::string result;
        encodeUtf8Codepoint( result, 0x1F600 ); // 😀
        EXPECT_EQ( "😀", result );

        result.clear();
        encodeUtf8Codepoint( result, 0x1F4A9 ); // 💩
        EXPECT_EQ( "💩", result );
    }

    TEST( UTF8, RoundTrip )
    {
        // Test various codepoints
        std::vector<uint32_t> codepoints = {
            0x0041,  // A
            0x00E9,  // é
            0x20AC,  // €
            0x1F600, // 😀
            0x10000, // First supplementary character
            0x10FFFF // Last valid Unicode codepoint
        };

        for ( uint32_t original : codepoints )
        {
            std::string encoded;
            encodeUtf8Codepoint( encoded, original );

            std::size_t i = 0;
            uint32_t decoded = 0;
            EXPECT_TRUE( decodeUtf8Codepoint( encoded, i, decoded ) );
            EXPECT_EQ( original, decoded );
            EXPECT_EQ( encoded.size(), i ); // Should have consumed entire string
        }
    }

    TEST( EscapeUnescape, JSON_UnicodeEscaping )
    {
        // Test escapeNonAscii = false (default)
        EXPECT_EQ( "café", jsonEscape( "café", false ) );
        EXPECT_EQ( "€100", jsonEscape( "€100", false ) );
        EXPECT_EQ( "😀", jsonEscape( "😀", false ) );

        // Test escapeNonAscii = true
        EXPECT_EQ( "caf\\u00e9", jsonEscape( "café", true ) );
        EXPECT_EQ( "\\u20ac100", jsonEscape( "€100", true ) );

        // Emoji requires surrogate pair
        EXPECT_EQ( "\\ud83d\\ude00", jsonEscape( "😀", true ) );

        // Mixed content
        EXPECT_EQ( "Hello \\u4e2d\\u56fd", jsonEscape( "Hello 中国", true ) );
    }

    TEST( EscapeUnescape, JSON_UnicodeSurrogatePairs )
    {
        // Test unescaping surrogate pairs
        EXPECT_EQ( "😀", jsonUnescape( "\\ud83d\\ude00" ) );
        EXPECT_EQ( "💩", jsonUnescape( "\\ud83d\\udca9" ) );

        // Test invalid surrogates
        EXPECT_EQ( "", jsonUnescape( "\\ud83d" ) );        // High surrogate alone
        EXPECT_EQ( "", jsonUnescape( "\\ud83d\\u0041" ) ); // High + non-surrogate
        EXPECT_EQ( "", jsonUnescape( "\\ude00" ) );        // Low surrogate alone
    }

    TEST( EscapeUnescape, JSON_UnicodeRoundTrip )
    {
        // Test various Unicode strings
        std::vector<std::string> testStrings = {
            "café",
            "€100",
            "Hello 世界",
            "😀🎉🚀",
            "Привет",
            "مرحبا",
            "こんにちは" };

        for ( const auto& original : testStrings )
        {
            // Round-trip with escapeNonAscii = true
            std::string escaped = jsonEscape( original, true );
            std::string unescaped = jsonUnescape( escaped );
            EXPECT_EQ( original, unescaped ) << "Failed for: " << original;

            // Round-trip with escapeNonAscii = false
            escaped = jsonEscape( original, false );
            unescaped = jsonUnescape( escaped );
            EXPECT_EQ( original, unescaped ) << "Failed for: " << original;
        }
    }
} // namespace nfx::string::test
