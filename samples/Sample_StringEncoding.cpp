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
 * @file Sample_StringEncoding.cpp
 * @brief Demonstrates encoding and escaping operations for various formats
 * @details This sample shows URL encoding/decoding, JSON escaping/unescaping,
 *          XML/HTML escaping/unescaping, and C/C++ escape sequences
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <nfx/string/Utils.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - Encoding & Escaping ===\n\n";

    //=====================================================================
    // 1. URL encoding and decoding
    //=====================================================================
    {
        std::cout << "1. URL encoding and decoding\n";
        std::cout << "-------------------------------\n";

        // Basic URL encoding
        std::cout << "Basic encoding:\n";
        std::string searchQuery{ "C++ programming" };
        std::string encoded1{ urlEncode( searchQuery ) };
        std::cout << "  Original: \"" << searchQuery << "\"\n";
        std::cout << "  Encoded:  \"" << encoded1 << "\"\n";
        std::cout << "  Decoded:  \"" << urlDecode( encoded1 ) << "\"\n";

        // Email addresses
        std::cout << "\n"
                  << "Email encoding:\n";
        std::string email{ "user.name+filter@example.com" };
        std::string encodedEmail{ urlEncode( email ) };
        std::cout << "  Original: " << email << "\n";
        std::cout << "  Encoded:  " << encodedEmail << "\n";
        std::cout << "  Decoded:  " << urlDecode( encodedEmail ) << "\n";

        // Query strings
        std::cout << "\n"
                  << "Query string construction:\n";
        std::string param1{ "Hello World" };
        std::string param2{ "test@value" };
        std::string param3{ "C++ & Java" };
        std::string queryString{ "?q=" + urlEncode( param1 ) + "&email=" + urlEncode( param2 ) + "&lang=" + urlEncode( param3 ) };
        std::cout << "  Parameters:\n";
        std::cout << "    q     = \"" << param1 << "\"\n";
        std::cout << "    email = \"" << param2 << "\"\n";
        std::cout << "    lang  = \"" << param3 << "\"\n";
        std::cout << "  Query string: " << queryString << "\n";

        // URL components
        std::cout << "\n"
                  << "URL component encoding:\n";
        std::vector<std::pair<std::string, std::string>> urlParts = {
            { "Path", "/api/v1/users/search" },
            { "Query param", "name=John Doe" },
            { "Fragment", "#section-1.2" },
            { "Special chars", "!@#$%^&*()" } };

        for ( const auto& [label, value] : urlParts )
        {
            std::cout << "  " << label << ":\n";
            std::cout << "    Original: " << value << "\n";
            std::cout << "    Encoded:  " << urlEncode( value ) << "\n";
        }

        // Real-world example: Building a search URL
        std::cout << "\n"
                  << "Building a search URL:\n";
        std::string baseUrl{ "https://api.example.com/search" };
        std::string searchTerm{ "how to \"escape\" special characters?" };
        std::string category{ "C++ & C#" };
        std::string fullUrl{ baseUrl + "?q=" + urlEncode( searchTerm ) + "&category=" + urlEncode( category ) + "&limit=10" };
        std::cout << "  Search term: " << searchTerm << "\n";
        std::cout << "  Category:    " << category << "\n";
        std::cout << "  Full URL:\n    " << fullUrl << "\n";

        // Decoding example
        std::cout << "\n"
                  << "Decoding URL components:\n";
        std::string encodedUrl{ "https%3A%2F%2Fexample.com%2Fpath%3Fquery%3Dvalue" };
        std::string decodedUrl{ urlDecode( encodedUrl ) };
        std::cout << "  Encoded: " << encodedUrl << "\n";
        std::cout << "  Decoded: " << decodedUrl << "\n";

        // Special characters demonstration
        std::cout << "\n"
                  << "Special characters handling:\n";
        std::vector<std::string> specialCases = {
            "hello world",       // space
            "test@example.com",  // @
            "50% discount",      // %
            "C++ & Java",        // &
            "path/to/file",      // /
            "query?name=value",  // ?
            "fragment#section",  // #
            "price: $19.99",     // $
            "code: x = y + z;",  // = ; +
            "unicode: café ñoël" // UTF-8
        };

        for ( const auto& test : specialCases )
        {
            std::string encoded{ urlEncode( test ) };
            std::string decoded{ urlDecode( encoded ) };
            std::cout << "  \"" << test << "\" -> \"" << encoded << "\" -> \"" << decoded << "\"\n";
        }

        // Error handling
        std::cout << "\n"
                  << "Decoding error handling:\n";
        std::vector<std::string> invalidInputs = {
            "test%",     // incomplete
            "test%2",    // only one hex digit
            "test%GG",   // invalid hex
            "test%2Xval" // invalid hex in middle
        };

        for ( const auto& invalid : invalidInputs )
        {
            std::string result{ urlDecode( invalid ) };
            std::cout << "  \"" << invalid << "\" -> " << ( result.empty() ? "ERROR (empty)" : result ) << "\n";
        }

        std::cout << "\n";
    }

    //=====================================================================
    // 2. JSON escaping and unescaping
    //=====================================================================
    {
        std::cout << "2. JSON escaping and unescaping\n";
        std::cout << "---------------------------------\n";

        // Basic JSON escaping
        std::cout << "Basic JSON Escaping:\n";
        {
            std::string text = "Hello \"World\"";
            std::cout << "  Original: " << text << "\n";
            std::cout << "  Escaped:  " << jsonEscape( text ) << "\n\n";
        }

        // Building a JSON object
        std::cout << "Building JSON Object:\n";
        {
            std::string name = "John \"The Rock\" Doe";
            std::string path = "C:\\Users\\John\\Documents";
            std::string notes = "Line 1\nLine 2\tTabbed";

            std::cout << "  Name:  " << name << "\n";
            std::cout << "  Path:  " << path << "\n";
            std::cout << "  Notes: " << notes << "\n\n";

            std::string json = "{\n";
            json += "  \"name\": \"" + jsonEscape( name ) + "\",\n";
            json += "  \"path\": \"" + jsonEscape( path ) + "\",\n";
            json += "  \"notes\": \"" + jsonEscape( notes ) + "\"\n";
            json += "}";

            std::cout << "  JSON:\n"
                      << json << "\n\n";
        }

        // Control characters
        std::cout << "Control Characters:\n";
        {
            std::string controls[] = {
                std::string( "tab: " ) + "\t" + "end",
                std::string( "newline: " ) + "\n" + "end",
                std::string( "return: " ) + "\r" + "end",
                std::string( "backspace: " ) + "\b" + "end",
                std::string( "formfeed: " ) + "\f" + "end",
                std::string( "null: " ) + std::string( 1, '\0' ) + "end" };

            for ( const auto& ctrl : controls )
            {
                std::cout << "  Escaped: \"" << jsonEscape( ctrl ) << "\"\n";
            }
            std::cout << "\n";
        }

        // Unicode escaping
        std::cout << "Unicode Characters:\n";
        {
            std::string unicodes[] = {
                "café",
                "ñoël",
                "Price: €10",
                "Arrow →",
                "Chinese: 中文" };

            for ( const auto& unicode : unicodes )
            {
                std::string escaped = jsonEscape( unicode );
                std::cout << "  " << unicode << " -> " << escaped << "\n";
            }
            std::cout << "\n";
        }

        // JSON unescaping
        std::cout << "JSON Unescaping:\n";
        {
            std::vector<std::string> escapedStrings = {
                "Hello \\\"World\\\"",
                "Path: C:\\\\Users\\\\John",
                "Line1\\nLine2\\tTab",
                "Unicode: caf\\u00E9",
                "Euro: \\u20AC",
                "Chinese: \\u4E2D\\u6587" };

            for ( const auto& escaped : escapedStrings )
            {
                std::cout << "  \"" << escaped << "\" -> \"" << jsonUnescape( escaped ) << "\"\n";
            }
            std::cout << "\n";
        }

        // Real-world API response
        std::cout << "Real-World: Error Message in JSON:\n";
        {
            std::string errorCode = "FILE_NOT_FOUND";
            std::string errorMessage = "File \"data.txt\" not found in C:\\Users\\John\\Documents";
            std::string stackTrace = "at main.cpp:42\nat utils.cpp:107";

            std::string jsonError = "{\n";
            jsonError += "  \"error\": {\n";
            jsonError += "    \"code\": \"" + jsonEscape( errorCode ) + "\",\n";
            jsonError += "    \"message\": \"" + jsonEscape( errorMessage ) + "\",\n";
            jsonError += "    \"stackTrace\": \"" + jsonEscape( stackTrace ) + "\"\n";
            jsonError += "  }\n";
            jsonError += "}";

            std::cout << jsonError << "\n\n";
        }

        // Round-trip encoding
        std::cout << "Round-Trip Encoding:\n";
        {
            std::vector<std::string> testCases = {
                "Simple text",
                "Text with \"quotes\" and \\backslashes\\",
                "Multi\nLine\nText",
                "Special: \t\r\n\b\f",
                "Unicode: café ñoël €10" };

            for ( const auto& original : testCases )
            {
                std::string escaped = jsonEscape( original );
                std::string unescaped = jsonUnescape( escaped );
                std::cout << "  Original: " << original << "\n";
                std::cout << "  Escaped:  " << escaped << "\n";
                std::cout << "  Back:     " << unescaped << "\n";
                std::cout << "  Match:    " << ( original == unescaped ? "YES" : "NO" ) << "\n\n";
            }
        }

        // Malformed input handling
        std::cout << "Malformed Input Handling:\n";
        {
            std::vector<std::string> malformedInputs = {
                "test\\",      // backslash at end
                "test\\x",     // invalid escape
                "test\\u123",  // incomplete Unicode
                "test\\uXXXX", // invalid hex in Unicode
                "test\\q"      // unknown escape
            };

            for ( const auto& malformed : malformedInputs )
            {
                std::string result{ jsonUnescape( malformed ) };
                std::cout << "  \"" << malformed << "\" -> " << ( result.empty() ? "ERROR (empty)" : result ) << "\n";
            }

            std::cout << "\n";
        }
    }

    //=====================================================================
    // 3. XML/HTML escaping and unescaping
    //=====================================================================
    {
        std::cout << "3. XML/HTML escaping and unescaping\n";
        std::cout << "--------------------------------------\n";

        // Basic XML escaping
        std::cout << "Basic XML/HTML Escaping:\n";
        {
            std::string text = "<tag>";
            std::cout << "  Original: " << text << "\n";
            std::cout << "  Escaped:  " << xmlEscape( text ) << "\n\n";
        }

        // Building XML content
        std::cout << "Building XML Element:\n";
        {
            std::string name = "John & Jane";
            std::string company = "AT&T";
            std::string note = "x < 5 && y > 10";

            std::cout << "  Name:    " << name << "\n";
            std::cout << "  Company: " << company << "\n";
            std::cout << "  Note:    " << note << "\n\n";

            std::string xml = "<person>\n";
            xml += "  <name>" + xmlEscape( name ) + "</name>\n";
            xml += "  <company>" + xmlEscape( company ) + "</company>\n";
            xml += "  <note>" + xmlEscape( note ) + "</note>\n";
            xml += "</person>";

            std::cout << "  XML:\n"
                      << xml
                      << "\n\n";
        }

        // HTML attributes
        std::cout << "Building HTML with Attributes:\n";
        {
            std::string url = "page.html?x=1&y=2";
            std::string title = "Tom & Jerry's \"Show\"";
            std::string alt = "A > B";

            std::cout << "  URL:   " << url << "\n";
            std::cout << "  Title: " << title << "\n";
            std::cout << "  Alt:   " << alt << "\n\n";

            std::string html = "<a href=\"" + xmlEscape( url ) + "\" ";
            html += "title=\"" + xmlEscape( title ) + "\">";
            html += "Link</a>\n";
            html += "<img src=\"image.png\" alt=\"" + xmlEscape( alt ) + "\">";

            std::cout << "  HTML:\n  " << html << "\n\n";
        }

        // Special characters
        std::cout << "Five Predefined XML Entities:\n";
        {
            std::vector<std::pair<std::string, std::string>> entities = {
                { "&", "&amp;" },
                { "<", "&lt;" },
                { ">", "&gt;" },
                { "\"", "&quot;" },
                { "'", "&apos;" } };

            for ( const auto& [ch, entity] : entities )
            {
                std::cout << "  '" << ch << "' -> " << xmlEscape( ch ) << "\n";
            }
            std::cout << "\n";
        }

        // XML unescaping
        std::cout << "XML/HTML Unescaping:\n";
        {
            std::vector<std::string> escapedStrings = {
                "&lt;tag&gt;",
                "Tom &amp; Jerry",
                "&quot;quoted&quot;",
                "It&apos;s fine",
                "A &lt; B &amp; C &gt; D" };

            for ( const auto& escaped : escapedStrings )
            {
                std::cout << "  " << escaped << " -> " << xmlUnescape( escaped ) << "\n";
            }
            std::cout << "\n";
        }

        // Numeric character references
        std::cout << "Numeric Character References:\n";
        {
            std::vector<std::string> numericRefs = {
                "&#65;",    // A (decimal)
                "&#x41;",   // A (hex)
                "&#233;",   // e-acute (decimal)
                "&#xE9;",   // e-acute (hex)
                "&#169;",   // copyright (decimal)
                "&#x20AC;", // euro (hex)
                "&#x4E2D;"  // Chinese character (hex)
            };

            for ( const auto& ref : numericRefs )
            {
                std::cout << "  " << ref << " -> " << xmlUnescape( ref ) << "\n";
            }
            std::cout << "\n";
        }

        // Real-world XML document
        std::cout << "Real-World: XML Document Fragment:\n";
        {
            std::string productName = "Widget & Gadget";
            std::string description = "A < B \"comparison\" tool";
            std::string manufacturer = "R&D Corp's Factory";

            std::string xml = "<product>\n";
            xml += "  <name>" + xmlEscape( productName ) + "</name>\n";
            xml += "  <description>" + xmlEscape( description ) + "</description>\n";
            xml += "  <manufacturer>" + xmlEscape( manufacturer ) + "</manufacturer>\n";
            xml += "</product>";

            std::cout << xml << "\n\n";
        }

        // Round-trip encoding
        std::cout << "Round-Trip Encoding:\n";
        {
            std::vector<std::string> testCases = {
                "Simple text",
                "<tag>content</tag>",
                "Tom & Jerry",
                "a < b && c > d",
                "\"quoted\" and 'apostrophe'",
                "<p>Text & more</p>" };

            for ( const auto& original : testCases )
            {
                std::string escaped = xmlEscape( original );
                std::string unescaped = xmlUnescape( escaped );
                std::cout << "  Original: " << original << "\n";
                std::cout << "  Escaped:  " << escaped << "\n";
                std::cout << "  Back:     " << unescaped << "\n";
                std::cout << "  Match:    " << ( original == unescaped ? "YES" : "NO" ) << "\n\n";
            }
        }

        // Malformed input handling
        std::cout << "Malformed Input Handling:\n";
        {
            std::vector<std::string> malformedInputs = {
                "test & more",    // & without semicolon
                "test &unknown;", // unknown entity
                "test &#;",       // empty numeric entity
                "test &#x;",      // empty hex entity
                "test &#xGG;"     // invalid hex digits
            };

            for ( const auto& malformed : malformedInputs )
            {
                std::string result{ xmlUnescape( malformed ) };
                std::cout << "  \"" << malformed << "\" -> " << ( result.empty() ? "ERROR (empty)" : result ) << "\n";
            }

            std::cout << "\n";
        }
    }

    //=====================================================================
    // 4. C/C++ escape sequences
    //=====================================================================
    {
        std::cout << "4. C/C++ escape sequences\n";
        std::cout << "---------------------------\n";

        // Basic escaping
        std::cout << "Basic C++ Escaping:\n";
        {
            std::string text = "Hello\nWorld";
            std::cout << "  Original (2 lines):\n"
                      << text << "\n";
            std::cout << "  Escaped: " << cppEscape( text ) << "\n\n";
        }

        // Common escape sequences
        std::cout << "Common Escape Sequences:\n";
        {
            std::vector<std::pair<std::string, std::string>> escapes = {
                { "newline", "\n" },
                { "tab", "\t" },
                { "carriage-return", "\r" },
                { "backslash", "\\" },
                { "double-quote", "\"" },
                { "single-quote", "'" } };

            for ( const auto& [name, ch] : escapes )
            {
                std::cout << "  " << name << ": " << cppEscape( ch ) << "\n";
            }
            std::cout << "\n";
        }

        // Building C++ string literals
        std::cout << "Building C++ String Literal:\n";
        {
            std::string userInput = "Line 1\nLine 2\tTabbed\nPath: C:\\Users\\John";
            std::cout << "  User input:\n"
                      << userInput << "\n\n";

            std::string literal = "std::string text = \"" + cppEscape( userInput ) + "\";";
            std::cout << "  C++ code:\n  " << literal << "\n\n";
        }

        // Control characters
        std::cout << "Control Characters:\n";
        {
            std::vector<std::pair<std::string, std::string>> controls = {
                { "backspace", std::string( 1, '\b' ) },
                { "form-feed", std::string( 1, '\f' ) },
                { "vertical-tab", std::string( 1, '\v' ) },
                { "alert (bell)", std::string( 1, '\a' ) },
                { "null", std::string( 1, '\0' ) } };

            for ( const auto& [name, ch] : controls )
            {
                std::cout << "  " << name << ": " << cppEscape( ch ) << "\n";
            }
            std::cout << "\n";
        }

        // Hexadecimal escapes
        std::cout << "Hexadecimal Escape Sequences:\n";
        {
            std::cout << "  Control char 0x01: " << cppEscape( "\x01" ) << "\n";
            std::cout << "  Control char 0x1F: " << cppEscape( "\x1F" ) << "\n";
            std::cout << "  DEL (0x7F): " << cppEscape( "\x7F" ) << "\n\n";
        }

        // Unescaping
        std::cout << "C++ Unescaping:\n";
        {
            std::vector<std::string> escapedStrings = {
                "line1\\nline2",
                "col1\\tcol2",
                "path\\\\to\\\\file",
                "say \\\"hello\\\"",
                "it\\'s",
                "null\\0char" };

            for ( const auto& escaped : escapedStrings )
            {
                std::string unescaped = cppUnescape( escaped );
                std::cout << "  \"" << escaped << "\" -> ";
                if ( escaped.find( "null" ) != std::string::npos )
                {
                    std::cout << "(string with null char, length=" << unescaped.size() << ")\n";
                }
                else
                {
                    std::cout << "\"" << unescaped << "\"\n";
                }
            }
            std::cout << "\n";
        }

        // Hexadecimal and octal unescaping
        std::cout << "Hex and Octal Unescaping:\n";
        {
            std::vector<std::string> numericEscapes = {
                "\\x41", // 'A' hex
                "\\x30", // '0' hex
                "\\101", // 'A' octal
                "\\60",  // '0' octal
                "\\0",   // null octal
                "\\012"  // newline octal
            };

            for ( const auto& escaped : numericEscapes )
            {
                std::string unescaped = cppUnescape( escaped );
                std::cout << "  " << escaped << " -> ";
                if ( unescaped[0] == '\0' )
                {
                    std::cout << "(null character)\n";
                }
                else if ( unescaped[0] == '\n' )
                {
                    std::cout << "(newline)\n";
                }
                else
                {
                    std::cout << "'" << unescaped << "'\n";
                }
            }
            std::cout << "\n";
        }

        // Real-world code generation
        std::cout << "Real-World: Code Generation:\n";
        {
            std::string sqlQuery = "SELECT * FROM users WHERE name = \"John\"";
            std::string errorMsg = "File not found:\nC:\\Users\\John\\data.txt";

            std::cout << "  SQL Query: " << sqlQuery << "\n";
            std::cout << "  As C++ literal: \"" << cppEscape( sqlQuery ) << "\"\n\n";

            std::cout << "  Error Message:\n"
                      << errorMsg << "\n";
            std::cout << "  As C++ literal: \"" << cppEscape( errorMsg ) << "\"\n\n";
        }

        // Round-trip encoding
        std::cout << "Round-Trip Encoding:\n";
        {
            std::vector<std::string> testCases = {
                "Simple text",
                "Line 1\nLine 2",
                "Tab\there",
                "Path: C:\\Windows\\System32",
                "Quote: \"Hello\"",
                "Mix: \n\t\r\\",
                std::string( "Null\0inside", 11 ) };

            for ( const auto& original : testCases )
            {
                std::string escaped = cppEscape( original );
                std::string unescaped = cppUnescape( escaped );

                std::cout << "  Original length: " << original.size();
                std::cout << ", Escaped: \"" << escaped << "\"";
                std::cout << ", Match: " << ( original == unescaped ? "YES" : "NO" ) << "\n";
            }
            std::cout << "\n";
        }

        // Malformed input handling
        std::cout << "Malformed Input Handling:\n";
        {
            std::vector<std::string> malformedInputs = {
                "test\\",   // backslash at end
                "test\\q",  // invalid escape
                "test\\x",  // incomplete hex
                "test\\x0", // incomplete hex
                "test\\xGG" // invalid hex digits
            };

            for ( const auto& malformed : malformedInputs )
            {
                std::string result{ cppUnescape( malformed ) };
                std::cout << "  \"" << malformed << "\" -> " << ( result.empty() ? "ERROR (empty)" : result ) << "\n";
            }

            std::cout << "\n";
        }
    }

    return 0;
}
