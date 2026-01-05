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
 * @file Sample_StringSplitter.cpp
 * @brief Demonstrates comprehensive usage of zero-allocation string splitting with Splitter
 * @details This sample shows how to use Splitter for high-performance string processing
 *          in real-world scenarios like CSV parsing, configuration files, log analysis,
 *          and path manipulation
 */

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <nfx/string/Splitter.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - String Splitter ===\n\n";

    //=====================================================================
    // 1. CSV Data Processing
    //=====================================================================
    // 1. CSV data processing
    //=====================================================================
    {
        std::cout << "1. CSV data processing\n";
        std::cout << "------------------------\n";

        const std::string_view csvLine{ "John,Doe,30,Engineer,NewYork,75000" };
        auto csvSplitter{ splitView( csvLine, ',' ) };

        std::cout << "Original CSV line: " << csvLine << "\n";
        std::cout << "Parsed fields:\n";

        // Using range-based for loop (most convenient)
        size_t fieldIndex{};
        const char* fieldNames[]{ "First Name", "Last Name", "Age", "Job", "City", "Salary" };

        for ( const auto field : csvSplitter )
        {
            const char* fieldName = ( fieldIndex < 6 ) ? fieldNames[fieldIndex] : "Unknown";
            std::cout << "  " << std::setw( 12 ) << fieldName << ": " << field << "\n";
            ++fieldIndex;
        }

        std::cout << "Total fields: " << fieldIndex << "\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 2. Configuration file processing
    //=====================================================================
    {
        std::cout << "2. Configuration file processing\n";
        std::cout << "-----------------------------------\n";

        const std::string_view configData{ "server=localhost;port=8080;database=mydb;timeout=30;ssl=true;debug=false" };
        auto configSplitter{ splitView( configData, ';' ) };

        std::cout << "Configuration string: " << configData << "\n";
        std::cout << "Configuration settings:\n";

        for ( const auto setting : configSplitter )
        {
            // Further split each setting by '=' to get key-value pairs
            auto kvSplitter{ splitView( setting, '=' ) };
            auto it{ kvSplitter.begin() };

            if ( it != kvSplitter.end() )
            {
                std::string_view key{ *it };
                ++it;

                if ( it != kvSplitter.end() )
                {
                    std::string_view value{ *it };
                    std::cout << "  " << std::setw( 10 ) << key << " = " << value << "\n";
                }
            }
        }

        std::cout << "\n";
    }

    //=====================================================================
    // 3. Log file analysis
    //=====================================================================
    {
        std::cout << "3. Log file analysis\n";
        std::cout << "----------------------\n";

        const std::string_view logEntries[]{
            "2025-08-31 09:15:32 INFO Application started successfully",
            "2025-08-31 09:15:33 DEBUG Loading configuration from config.xml",
            "2025-08-31 09:15:34 INFO Database connection established",
            "2025-08-31 09:15:35 WARN Cache size limit reached, cleaning up",
            "2025-08-31 09:15:36 ERROR Failed to process request: timeout" };

        std::cout << "Analyzing log entries:\n";

        for ( const auto& logEntry : logEntries )
        {
            auto logSplitter{ splitView( logEntry, ' ' ) };
            auto it{ logSplitter.begin() };

            // Extract log components
            std::string_view date{};
            std::string_view time{};
            std::string_view level{};

            if ( it != logSplitter.end() )
            {
                date = *it;
                ++it;
            }
            if ( it != logSplitter.end() )
            {
                time = *it;
                ++it;
            }
            if ( it != logSplitter.end() )
            {
                level = *it;
                ++it;
            }

            // Collect remaining parts as message
            std::string message;
            while ( it != logSplitter.end() )
            {
                if ( !message.empty() )
                {
                    message += " ";
                }
                message += *it;
                ++it;
            }

            std::cout << "  [" << std::setw( 5 ) << level << "] " << date << " " << time << " - " << message << "\n";
        }

        std::cout << "\n";
    }

    //=====================================================================
    // 4. Path manipulation
    //=====================================================================
    {
        std::cout << "4. Path manipulation\n";
        std::cout << "----------------------\n";

        const std::string_view paths[]{
            "/usr/local/bin/myapp",
            "C:\\Program Files\\MyApp\\bin\\app.exe",
            "../config/settings.ini",
            "./data/output.csv" };

        for ( const auto& path : paths )
        {
            std::cout << "Original path: " << path << "\n";

            // Determine delimiter based on path style
            char delimiter{ ( path.find( '\\' ) != std::string_view::npos ) ? '\\' : '/' };
            auto pathSplitter{ splitView( path, delimiter ) };

            std::cout << "  Components: ";
            bool first{ true };
            for ( const auto component : pathSplitter )
            {
                if ( !first )
                {
                    std::cout << " -> ";
                }
                if ( component.empty() )
                {
                    std::cout << "[root]";
                }
                else
                {
                    std::cout << component;
                }
                first = false;
            }
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    //=====================================================================
    // 5. Performance demonstration - Zero allocation
    //=====================================================================
    {
        std::cout << "5. Performance demonstration - Zero allocation\n";
        std::cout << "------------------------------------------------\n";

        // Large CSV-like data for performance testing
        std::string largeData;
        for ( int i{}; i < 1000; ++i )
        {
            if ( i > 0 )
            {
                largeData += ",";
            }
            largeData += "field" + std::to_string( i );
        }

        auto startTime{ std::chrono::high_resolution_clock::now() };

        // Process large data with zero allocations
        auto largeSplitter{ splitView( largeData, ',' ) };
        size_t count{};
        for ( const auto field : largeSplitter )
        {
            count++;
            (void)field;
        }

        auto endTime{ std::chrono::high_resolution_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::microseconds>( endTime - startTime ) };

        std::cout << "Processed " << count << " fields from large dataset\n";
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
        std::cout << "Performance: " << std::fixed << std::setprecision( 0 )
                  << ( static_cast<double>( count ) * 1000000.0 / static_cast<double>( duration.count() ) )
                  << " fields/second\n";
        std::cout << "Memory allocations: 0 (all string_views point to original data)\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 6. Edge cases and delimiter variations
    //=====================================================================
    {
        std::cout << "6. Edge cases and delimiter variations\n";
        std::cout << "-----------------------------------------\n";

        // Test various edge cases
        const std::string_view edgeCases[]{
            "",       // Empty string
            ",",      // Single delimiter
            "hello,", // Trailing delimiter
            ",world", // Leading delimiter
            "a,,b",   // Consecutive delimiters
            "single"  // No delimiters
        };

        std::cout << "Edge cases:\n";
        for ( const auto& testCase : edgeCases )
        {
            std::cout << "  Input: \"" << testCase << "\"\n";
            std::cout << "    Segments: ";

            auto edgeSplitter{ splitView( testCase, ',' ) };
            bool first{ true };
            for ( const auto segment : edgeSplitter )
            {
                if ( !first )
                {
                    std::cout << " | ";
                }
                std::cout << "\"" << segment << "\"";
                first = false;
            }
            if ( first )
                std::cout << "(no segments)";
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    //=====================================================================
    // 7. Different delimiter examples
    //=====================================================================
    {
        std::cout << "7. Different delimiter examples\n";
        std::cout << "----------------------------------\n";

        const struct
        {
            std::string_view data;
            char delimiter;
            const char* description;
        } delimiterExamples[]{
            { "apple banana cherry date", ' ', "Space-separated words" },
            { "line1\nline2\nline3", '\n', "Newline-separated lines" },
            { "col1\tcol2\tcol3", '\t', "Tab-separated columns" },
            { "key1=val1;key2=val2;key3=val3", ';', "Semicolon-separated pairs" },
            { "192.168.1.1", '.', "Dot-separated IP address" } };

        for ( const auto& example : delimiterExamples )
        {
            std::cout << "  " << example.description << ":\n";
            std::cout << "    Input: \"" << example.data << "\"\n";
            std::cout << "    Parts: ";

            auto delimSplitter{ splitView( example.data, example.delimiter ) };
            bool first{ true };
            for ( const auto part : delimSplitter )
            {
                if ( !first )
                {
                    std::cout << " | ";
                }
                std::cout << "\"" << part << "\"";
                first = false;
            }
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    //=====================================================================
    // 8. Manual iterator usage
    //=====================================================================
    {
        std::cout << "8. Manual iterator usage\n";
        std::cout << "--------------------------\n";

        const std::string_view manualData{ "first,second,third,fourth,fifth" };
        auto manualSplitter{ splitView( manualData, ',' ) };

        std::cout << "Manual iteration through: " << manualData << "\n";

        auto it{ manualSplitter.begin() };
        auto end{ manualSplitter.end() };
        size_t index{};

        while ( it != end )
        {
            std::cout << "  [" << index++ << "] = \"" << *it << "\"\n";
            ++it;
        }

        // Demonstrate iterator comparison
        auto it1{ manualSplitter.begin() };
        auto it2{ manualSplitter.begin() };
        std::cout << "Two begin iterators are equal: " << ( it1 == it2 ? "Yes" : "No" ) << "\n";

        ++it1;
        std::cout << "After advancing first iterator: " << ( it1 == it2 ? "Equal" : "Different" ) << "\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 9. Memory safety demonstration
    //=====================================================================
    {
        std::cout << "9. Memory safety demonstration\n";
        std::cout << "--------------------------------\n";

        const std::string originalString{ "memory,safety,test,data" };
        const std::string_view stringView{ originalString };

        auto safetySplitter{ splitView( stringView, ',' ) };
        auto safety_it{ safetySplitter.begin() };

        std::string_view firstSegment{ *safety_it };

        std::cout << "Original string: \"" << originalString << "\"\n";
        std::cout << "First segment: \"" << firstSegment << "\"\n";
        std::cout << std::boolalpha;
        std::cout << "Segment points to original memory: " << ( firstSegment.data() == originalString.data() ) << "\n";
        std::cout << "No additional memory allocated: Splitter uses zero-copy design\n";
        std::cout << "\n";
    }

    return 0;
}
