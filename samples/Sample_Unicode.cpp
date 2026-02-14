/*
 * MIT License
 *
 * Copyright (c) 2026 nfx
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
 * @file Sample_Unicode.cpp
 * @brief Demonstrates UTF-8 encoding and Unicode string handling
 * @details This sample shows UTF-8 validation, codepoint manipulation, length counting,
 *          substring extraction, and JSON/XML Unicode escaping
 */

#include <iostream>
#include <string>
#include <vector>

#include <nfx/string/Utils.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - Unicode & UTF-8 ===\n\n";

    //=====================================================================
    // 1. UTF-8 validation - Ensure proper encoding
    //=====================================================================
    {
        std::cout << "1. UTF-8 validation - Ensure proper encoding\n";
        std::cout << "----------------------------------------------\n";

        // Valid UTF-8 strings
        std::vector<std::string_view> validStrings{
            "Hello World",
            "café",
            "€100",
            "Hello 世界",
            "😀🎉🚀",
            "Привет мир",
            "مرحبا",
            "こんにちは" };

        std::cout << "Valid UTF-8 strings:\n";
        for ( const auto& str : validStrings )
        {
            std::cout << "  \"" << str << "\" -> " << ( isValidUtf8( str ) ? "✓ Valid" : "✗ Invalid" ) << "\n";
        }

        // Invalid UTF-8 sequences
        std::vector<std::string> invalidStrings{
            std::string( "Hello\xFF" ),            // Invalid byte
            std::string( "\xC0\x80" ),             // Overlong encoding
            std::string( "\xED\xA0\x80" ),         // Surrogate
            std::string( "\xF4\x90\x80\x80" ),     // Out of range
            std::string( "Test\xC2" ),             // Truncated
            std::string( "Valid\xE0\x80Start" ) }; // Invalid in middle

        std::cout << "\nInvalid UTF-8 sequences:\n";
        for ( const auto& str : invalidStrings )
        {
            std::cout << "  (binary data) -> " << ( isValidUtf8( str ) ? "✓ Valid" : "✗ Invalid" ) << "\n";
        }

        // Real-world validation
        std::cout << "\nReal-world validation:\n";
        std::string userInput{ "User entered: 你好 World" };
        if ( isValidUtf8( userInput ) )
        {
            std::cout << "  Input is safe to process: \"" << userInput << "\"\n";
        }
        else
        {
            std::cout << "  Input contains invalid UTF-8!\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 2. Counting Unicode codepoints - True string length
    //=====================================================================
    {
        std::cout << "2. Counting Unicode codepoints - True string length\n";
        std::cout << "-----------------------------------------------------\n";

        // Compare byte length vs codepoint count
        std::vector<std::string_view> testStrings{
            "Hello",        // ASCII
            "café",         // 2-byte chars
            "€100",         // 3-byte char
            "Hello 世界",   // Mixed
            "😀🎉🚀",       // 4-byte chars (emoji)
            "Привет",       // Cyrillic
            "こんにちは" }; // Japanese

        std::cout << "String length comparison:\n";
        for ( const auto& str : testStrings )
        {
            std::cout << "  \"" << str << "\"\n";
            std::cout << "    Bytes:      " << str.size() << "\n";
            std::cout << "    Codepoints: " << utf8Length( str ) << "\n";
        }

        // Real-world example: Character limits
        std::cout << "\nReal-world example - Tweet character limit:\n";
        std::string tweet{ "Hello 世界! 😀 This is a test message." };
        size_t charLimit{ 280 };
        size_t actualLength{ utf8Length( tweet ) };

        std::cout << "  Tweet: \"" << tweet << "\"\n";
        std::cout << "  Byte count: " << tweet.size() << "\n";
        std::cout << "  Character count: " << actualLength << "\n";
        std::cout << "  Limit: " << charLimit << "\n";
        std::cout << "  Status: " << ( actualLength <= charLimit ? "✓ Within limit" : "✗ Too long" ) << "\n";

        // Password validation with Unicode
        std::cout << "\nPassword length validation:\n";
        std::vector<std::string> passwords{
            "pass123",
            "pāss🔒wørd",
            "密码123456" };

        for ( const auto& pwd : passwords )
        {
            size_t minLength{ 8 };
            size_t length{ utf8Length( pwd ) };
            std::cout << "  Password length: " << length << " chars -> ";
            std::cout << ( length >= minLength ? "✓ Valid" : "✗ Too short" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 3. Unicode substring extraction - Codepoint-based operations
    //=====================================================================
    {
        std::cout << "3. Unicode substring extraction - Codepoint-based operations\n";
        std::cout << "--------------------------------------------------------------\n";

        // Basic substring extraction
        std::cout << "Basic substring extraction:\n";
        std::string_view text{ "Hello 世界 😀" };
        std::cout << "  Original: \"" << text << "\"\n";
        std::cout << "  First 5 chars: \"" << utf8Substring( text, 0, 5 ) << "\"\n";
        std::cout << "  Chars 6-7: \"" << utf8Substring( text, 6, 2 ) << "\"\n";
        std::cout << "  Last char: \"" << utf8Substring( text, 9, 1 ) << "\"\n";
        std::cout << "  From char 6 to end: \"" << utf8Substring( text, 6 ) << "\"\n";

        // Multi-language text processing
        std::cout << "\nMulti-language text processing:\n";
        std::vector<std::pair<std::string_view, std::string>> languages{
            { "English: Hello World", "English" },
            { "French: Bonjour le monde", "French" },
            { "Chinese: 你好世界", "Chinese" },
            { "Japanese: こんにちは世界", "Japanese" },
            { "Russian: Привет мир", "Russian" },
            { "Arabic: مرحبا العالم", "Arabic" } };

        for ( const auto& [lang_text, lang] : languages )
        {
            auto greeting{ utf8Substring( lang_text, 0, 20 ) };
            std::cout << "  " << lang << " (" << utf8Length( greeting ) << " chars): \"" << greeting << "\"\n";
        }

        // Text truncation with Unicode awareness
        std::cout << "\nUnicode-aware text truncation:\n";
        std::vector<std::string_view> messages{
            "This is a simple ASCII message for testing",
            "Café au lait €5.50 per cup",
            "世界你好 - Testing Chinese characters",
            "Emoji test 😀🎉🚀 with symbols" };

        size_t maxChars{ 20 };
        for ( const auto& msg : messages )
        {
            auto truncated{ utf8Substring( msg, 0, maxChars ) };
            std::cout << "  Original (" << utf8Length( msg ) << " chars): \"" << msg << "\"\n";
            std::cout << "  Truncated to " << maxChars << ": \"" << truncated;
            if ( utf8Length( msg ) > maxChars )
            {
                std::cout << "...";
            }
            std::cout << "\"\n\n";
        }

        // Extracting user mentions from text
        std::cout << "Extracting words from multilingual text:\n";
        std::string_view multiText{ "User: 用户名 sent 💌" };
        std::cout << "  Full text: \"" << multiText << "\"\n";
        std::cout << "  Word 1 (0-4): \"" << utf8Substring( multiText, 0, 4 ) << "\"\n";
        std::cout << "  Word 2 (6-9): \"" << utf8Substring( multiText, 6, 3 ) << "\"\n";
        std::cout << "  Word 3 (10-14): \"" << utf8Substring( multiText, 10, 4 ) << "\"\n";
        std::cout << "  Word 4 (15-16): \"" << utf8Substring( multiText, 15, 1 ) << "\"\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 4. UTF-8 encoding and decoding - Low-level operations
    //=====================================================================
    {
        std::cout << "4. UTF-8 encoding and decoding - Low-level operations\n";
        std::cout << "-------------------------------------------------------\n";

        // Encode codepoints to UTF-8
        std::cout << "Encoding Unicode codepoints:\n";
        std::vector<std::pair<uint32_t, std::string>> codepoints{
            { 0x0041, "Latin A" },
            { 0x00E9, "Latin é" },
            { 0x20AC, "Euro €" },
            { 0x4E2D, "Chinese 中" },
            { 0x1F600, "Emoji 😀" } };

        for ( const auto& [cp, desc] : codepoints )
        {
            std::string encoded;
            encodeUtf8Codepoint( encoded, cp );
            std::cout << "  U+" << std::hex << std::uppercase << cp << std::dec;
            std::cout << " (" << desc << "): \"" << encoded << "\" (" << encoded.size() << " bytes)\n";
        }

        // Decode UTF-8 to codepoints
        std::cout << "\nDecoding UTF-8 strings:\n";
        std::vector<std::string_view> utf8Strings{
            "A",
            "é",
            "€",
            "中",
            "😀" };

        for ( const auto& str : utf8Strings )
        {
            std::size_t i{};
            uint32_t codepoint{};
            if ( decodeUtf8Codepoint( str, i, codepoint ) )
            {
                std::cout << "  \"" << str << "\" -> U+" << std::hex << std::uppercase << codepoint << std::dec;
                std::cout << " (" << i << " bytes)\n";
            }
        }

        // Round-trip conversion
        std::cout << "\nRound-trip encoding/decoding:\n";
        std::vector<uint32_t> testCodepoints{ 0x41, 0xE9, 0x20AC, 0x1F600 };
        for ( uint32_t original : testCodepoints )
        {
            std::string encoded;
            encodeUtf8Codepoint( encoded, original );

            std::size_t i{};
            uint32_t decoded{};
            bool success{ decodeUtf8Codepoint( encoded, i, decoded ) };

            std::cout << "  U+" << std::hex << std::uppercase << original;
            std::cout << " -> \"" << encoded << "\" -> U+" << decoded << std::dec;
            std::cout << ( success && original == decoded ? " ✓" : " ✗" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 5. JSON Unicode escaping - Generate ASCII-safe JSON
    //=====================================================================
    {
        std::cout << "5. JSON Unicode escaping - Generate ASCII-safe JSON\n";
        std::cout << "-----------------------------------------------------\n";

        // Default behavior (UTF-8 pass-through)
        std::cout << "Default JSON escaping (UTF-8 preserved):\n";
        std::vector<std::string_view> jsonValues{
            "Hello World",
            "café",
            "€100",
            "Hello 世界",
            "😀🎉🚀" };

        for ( const auto& val : jsonValues )
        {
            std::cout << "  \"" << val << "\" -> \"" << jsonEscape( val, false ) << "\"\n";
        }

        // Unicode escaping (ASCII-only output)
        std::cout << "\nJSON with Unicode escaping (escapeNonAscii=true):\n";
        for ( const auto& val : jsonValues )
        {
            std::cout << "  \"" << val << "\" -> \"" << jsonEscape( val, true ) << "\"\n";
        }

        // Real-world example: API response
        std::cout << "\nReal-world: Building JSON API response\n";
        std::string userName{ "José García" };
        std::string message{ "Hello 世界! 😀" };

        std::cout << "  Normal JSON (UTF-8):\n";
        std::cout << "    {\"user\": \"" << jsonEscape( userName, false ) << "\", ";
        std::cout << "\"message\": \"" << jsonEscape( message, false ) << "\"}\n";

        std::cout << "  ASCII-safe JSON (escaped):\n";
        std::cout << "    {\"user\": \"" << jsonEscape( userName, true ) << "\", ";
        std::cout << "\"message\": \"" << jsonEscape( message, true ) << "\"}\n";

        // Round-trip test
        std::cout << "\nJSON Unicode round-trip:\n";
        std::vector<std::string> testStrings{
            "café",
            "€100",
            "世界",
            "😀" };

        for ( const auto& original : testStrings )
        {
            auto escaped{ jsonEscape( original, true ) };
            auto unescaped{ jsonUnescape( escaped ) };
            std::cout << "  \"" << original << "\" -> \"" << escaped << "\" -> \"" << unescaped << "\"";
            std::cout << ( original == unescaped ? " ✓" : " ✗" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 6. XML Unicode escaping - Generate ASCII-safe XML
    //=====================================================================
    {
        std::cout << "6. XML Unicode escaping - Generate ASCII-safe XML\n";
        std::cout << "---------------------------------------------------\n";

        // Default behavior (UTF-8 pass-through)
        std::cout << "Default XML escaping (UTF-8 preserved):\n";
        std::vector<std::string_view> xmlValues{
            "Hello World",
            "café & tea",
            "Price: €100",
            "<tag>Hello 世界</tag>",
            "Rating: ⭐⭐⭐⭐⭐" };

        for ( const auto& val : xmlValues )
        {
            std::cout << "  \"" << val << "\" -> \"" << xmlEscape( val, false ) << "\"\n";
        }

        // Unicode escaping (ASCII-only output)
        std::cout << "\nXML with Unicode escaping (escapeNonAscii=true):\n";
        for ( const auto& val : xmlValues )
        {
            std::cout << "  \"" << val << "\" -> \"" << xmlEscape( val, true ) << "\"\n";
        }

        // Real-world example: XML document generation
        std::cout << "\nReal-world: Building XML document\n";
        std::string title{ "Café Menu" };
        std::string price{ "€5.50" };
        std::string rating{ "⭐⭐⭐⭐" };

        std::cout << "  Normal XML (UTF-8):\n";
        std::cout << "    <item>\n";
        std::cout << "      <title>" << xmlEscape( title, false ) << "</title>\n";
        std::cout << "      <price>" << xmlEscape( price, false ) << "</price>\n";
        std::cout << "      <rating>" << xmlEscape( rating, false ) << "</rating>\n";
        std::cout << "    </item>\n";

        std::cout << "  ASCII-safe XML (escaped):\n";
        std::cout << "    <item>\n";
        std::cout << "      <title>" << xmlEscape( title, true ) << "</title>\n";
        std::cout << "      <price>" << xmlEscape( price, true ) << "</price>\n";
        std::cout << "      <rating>" << xmlEscape( rating, true ) << "</rating>\n";
        std::cout << "    </item>\n";

        // Round-trip test
        std::cout << "\nXML Unicode round-trip:\n";
        std::vector<std::string> testStrings{
            "café",
            "€100",
            "世界",
            "⭐" };

        for ( const auto& original : testStrings )
        {
            auto escaped{ xmlEscape( original, true ) };
            auto unescaped{ xmlUnescape( escaped ) };
            std::cout << "  \"" << original << "\" -> \"" << escaped << "\" -> \"" << unescaped << "\"";
            std::cout << ( original == unescaped ? " ✓" : " ✗" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 7. Real-world use cases - Practical applications
    //=====================================================================
    {
        std::cout << "7. Real-world use cases - Practical applications\n";
        std::cout << "--------------------------------------------------\n";

        // Username validation with Unicode
        std::cout << "Username validation:\n";
        std::vector<std::string> usernames{
            "john_doe",
            "josé_garcía",
            "user_123",
            "用户名",
            "user😀" };

        for ( const auto& username : usernames )
        {
            bool valid{ isValidUtf8( username ) };
            size_t length{ utf8Length( username ) };
            bool lengthOk{ length >= 3 && length <= 20 };

            std::cout << "  \"" << username << "\" (" << length << " chars) -> ";
            std::cout << ( valid && lengthOk ? "✓ Valid" : "✗ Invalid" ) << "\n";
        }

        // Multi-language search preview
        std::cout << "\nSearch result preview (first 30 chars):\n";
        std::vector<std::string_view> searchResults{
            "This is a long English description that needs truncation for preview",
            "C'est une longue description française qui nécessite une troncature",
            "これは切り捨てが必要な長い日本語の説明です",
            "这是一个需要截断以供预览的长中文描述" };

        for ( const auto& result : searchResults )
        {
            auto preview{ utf8Substring( result, 0, 30 ) };
            std::cout << "  \"" << preview;
            if ( utf8Length( result ) > 30 )
            {
                std::cout << "...";
            }
            std::cout << "\"\n";
        }

        // International phone number formatting
        std::cout << "\nInternational data processing:\n";
        std::string data{ "Name: José, City: São Paulo, Price: €50, Rating: ⭐⭐⭐⭐⭐" };
        std::cout << "  Original data: \"" << data << "\"\n";
        std::cout << "  Valid UTF-8: " << ( isValidUtf8( data ) ? "Yes" : "No" ) << "\n";
        std::cout << "  Character count: " << utf8Length( data ) << "\n";
        std::cout << "  Byte count: " << data.size() << "\n";

        // Safe JSON API
        std::cout << "\nGenerating ASCII-safe JSON for legacy systems:\n";
        std::cout << "  " << "{\n";
        std::cout << "    " << "\"name\": \"" << jsonEscape( "José García", true ) << "\",\n";
        std::cout << "    " << "\"city\": \"" << jsonEscape( "São Paulo", true ) << "\",\n";
        std::cout << "    " << "\"message\": \"" << jsonEscape( "Hello 世界! 😀", true ) << "\"\n";
        std::cout << "  " << "}\n";
        std::cout << "\n";
    }

    return 0;
}
