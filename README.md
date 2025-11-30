# nfx-stringutils

<!-- Project Info -->

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/blob/main/LICENSE.txt) [![GitHub release (latest by date)](https://img.shields.io/github/v/release/nfx-libs/nfx-stringutils?style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/releases) [![GitHub tag (latest by date)](https://img.shields.io/github/tag/nfx-libs/nfx-stringutils?style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/tags)<br/>

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square) ![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg?style=flat-square) ![Cross Platform](https://img.shields.io/badge/Platform-Linux_Windows-lightgrey?style=flat-square)

<!-- CI/CD Status -->

[![Linux GCC](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-stringutils/build-linux-gcc.yml?branch=main&label=Linux%20GCC&style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/actions/workflows/build-linux-gcc.yml) [![Linux Clang](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-stringutils/build-linux-clang.yml?branch=main&label=Linux%20Clang&style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/actions/workflows/build-linux-clang.yml) [![Windows MinGW](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-stringutils/build-windows-mingw.yml?branch=main&label=Windows%20MinGW&style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/actions/workflows/build-windows-mingw.yml) [![Windows MSVC](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-stringutils/build-windows-msvc.yml?branch=main&label=Windows%20MSVC&style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/actions/workflows/build-windows-msvc.yml) [![CodeQL](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-stringutils/codeql.yml?branch=main&label=CodeQL&style=flat-square)](https://github.com/nfx-libs/nfx-stringutils/actions/workflows/codeql.yml)

> A cross-platform C++20 header-only library offering high-performance string utilities, including zero-allocation splitting, validation, parsing, and manipulation

## Overview

nfx-stringutils is a modern C++20 header-only library providing high-performance string validation, manipulation, and splitting utilities. It offers comprehensive string operations including character classification, case conversion, trimming, zero-allocation splitting, boolean/numeric parsing, and URI validation optimized for performance across multiple platforms and compilers.

## Key Features

### 🪒 High-Performance String Splitting

- **Zero-Allocation Design**: Uses `std::string_view` for memory-efficient processing
- **Iterator Interface**: Range-based for loop support with forward iterator
- **Template Support**: Accepts any string-like type (std::string, const char\*, etc.)
- **Single Character Delimiters**: Efficient splitting on any character delimiter
- **Factory Function**: Convenient `splitView()` function for easy usage

### 📊 Real-World Applications

- **CSV Processing**: Parse comma-separated values efficiently
- **Configuration Files**: Split key-value pairs and settings
- **Log Analysis**: Process space or tab-separated log entries
- **Path Manipulation**: Split file paths and URLs
- **Data Processing**: Handle any delimited text data

### ✅ String Validation & Classification

- **Character Classification**: `isWhitespace()`, `isDigit()`, `isAlpha()`, `isAlphaNumeric()`
- **String Validation**: `isEmpty()`, `isNullOrWhiteSpace()`, `isAllDigits()`, `hasExactLength()`
- **URI Character Classification**: `isUriReserved()`, `isUriUnreserved()` with RFC 3986 compliance

### 🌐 Network & URI Validation

- **IPv4 Address Validation**: `isIpv4Address()` with RFC 791 compliance (rejects leading zeros)
- **IPv6 Address Validation**: `isIpv6Address()` with RFC 4291/5952 compliance (supports compression and IPv4-mapped)
- **Hostname Validation**: `isHostname()` with RFC 1123 compliance (max 253 chars, labels max 63 chars)
- **Domain Name Validation**: `isDomainName()` with RFC 1035 compliance (requires FQDN format)
- **Port Validation**: `isPortNumber()` with RFC 6335 compliance (0-65535 range, compile-time type safety)
- **Endpoint Parsing**: `tryParseEndpoint()` supports IPv4:port, hostname:port, [IPv6]:port formats

### 🔧 String Operations

- **String Comparison**: `startsWith()`, `endsWith()`, `contains()`, `equals()`, `iequals()` (case-insensitive)
- **String Trimming**: `trim()`, `trimStart()`, `trimEnd()` with non-allocating stringView versions
- **Case Conversion**: `toLower()`, `toUpper()` for both characters and strings

### ⚡ Performance Optimized

- Header-only library with zero runtime dependencies
- Highly optimized parsing and validation
- Efficient string operations with minimal allocations
- Zero-cost abstractions with constexpr support
- Compiler-optimized inline implementations

### 🌍 Cross-Platform Support

- Linux, Windows
- GCC 14+, Clang 19+, MSVC 2022+
- Thread-safe operations
- Consistent behavior across platforms

## Quick Start

### Requirements

- C++20 compatible compiler:
  - **GCC 14+** (14.2.0 tested)
  - **Clang 18+** (19.1.7 tested)
  - **MSVC 2022+** (19.44+ tested)
- CMake 3.20 or higher

### CMake Integration

```cmake
# Development options
option(NFX_STRINGUTILS_BUILD_TESTS          "Build tests"                        OFF )
option(NFX_STRINGUTILS_BUILD_SAMPLES        "Build samples"                      OFF )
option(NFX_STRINGUTILS_BUILD_BENCHMARKS     "Build benchmarks"                   OFF )
option(NFX_STRINGUTILS_BUILD_DOCUMENTATION  "Build Doxygen documentation"        OFF )

# Installation
option(NFX_STRINGUTILS_INSTALL_PROJECT      "Install project"                    OFF )

# Packaging
option(NFX_STRINGUTILS_PACKAGE_SOURCE       "Enable source package generation"   OFF )
option(NFX_STRINGUTILS_PACKAGE_ARCHIVE      "Enable TGZ/ZIP package generation"  OFF )
option(NFX_STRINGUTILS_PACKAGE_DEB          "Enable DEB package generation"      OFF )
option(NFX_STRINGUTILS_PACKAGE_RPM          "Enable RPM package generation"      OFF )
option(NFX_STRINGUTILS_PACKAGE_WIX          "Enable WiX MSI installer"           OFF )
```

### Using in Your Project

#### Option 1: Using FetchContent (Recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
  nfx-stringutils
  GIT_REPOSITORY https://github.com/nfx-libs/nfx-stringutils.git
  GIT_TAG        main  # or use specific version tag like "0.1.0"
)
FetchContent_MakeAvailable(nfx-stringutils)

# Link with header-only interface library
target_link_libraries(your_target PRIVATE nfx-stringutils::nfx-stringutils)
```

#### Option 2: As a Git Submodule

```bash
# Add as submodule
git submodule add https://github.com/nfx-libs/nfx-stringutils.git third-party/nfx-stringutils
```

```cmake
# In your CMakeLists.txt
add_subdirectory(third-party/nfx-stringutils)
target_link_libraries(your_target PRIVATE nfx-stringutils::nfx-stringutils)
```

#### Option 3: Using find_package (After Installation)

```cmake
find_package(nfx-stringutils REQUIRED)
target_link_libraries(your_target PRIVATE nfx-stringutils::nfx-stringutils)
```

### Building

**Build Commands:**

```bash
# Clone the repository
git clone https://github.com/nfx-libs/nfx-stringutils.git
cd nfx-stringutils

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the library
cmake --build . --config Release --parallel

# Run tests (optional)
ctest -C Release --output-on-failure

# Run benchmarks (optional)
./bin/benchmarks/BM_StringUtilities
./bin/benchmarks/BM_Splitter
```

### Documentation

nfx-stringutils includes API documentation generated with Doxygen.

#### 📚 Online Documentation

The complete API documentation is available online at:
**https://nfx-libs.github.io/nfx-stringutils**

#### Building Documentation Locally

```bash
# Configure with documentation enabled
cmake .. -DCMAKE_BUILD_TYPE=Release -DNFX_STRINGUTILS_BUILD_DOCUMENTATION=ON

# Build the documentation
cmake --build . --target nfx-stringutils-documentation
```

#### Requirements

- **Doxygen** - Documentation generation tool
- **Graphviz Dot** (optional) - For generating class diagrams

#### Accessing Local Documentation

After building, open `./build/doc/html/index.html` in your web browser.

## Usage Examples

### Basic String Splitting

```cpp
#include <iostream>
#include <string>
#include <nfx/string/Splitter.h>

using namespace nfx::string;

// CSV data processing
std::string csvLine = "John,Doe,30,Engineer,NewYork";
for (auto field : splitView(csvLine, ',')) {
    std::cout << "Field: " << field << std::endl;
}

// Configuration parsing
std::string config = "debug=true;port=8080;ssl=false";
for (auto setting : splitView(config, ';')) {
    std::cout << "Setting: " << setting << std::endl;
}

// Path components
std::string path = "/usr/local/bin/myapp";
auto splitter = Splitter(path, '/');
for (auto component : splitter) {
    if (!component.empty()) {  // Skip empty leading component
        std::cout << "Path component: " << component << std::endl;
    }
}
```

### Advanced Usage Patterns

```cpp
#include <cassert>
#include <vector>
#include <nfx/string/Splitter.h>

using namespace nfx::string;

// Collect segments into container
std::string data = "apple,banana,cherry,date";
std::vector<std::string_view> fruits;
for (auto fruit : splitView(data, ',')) {
    fruits.push_back(fruit);
}

// Process log entries
std::string logLine = "2025-10-26 14:30:15 ERROR Database connection failed";
auto logSplitter = splitView(logLine, ' ');
auto it = logSplitter.begin();

if (it != logSplitter.end()) {
    std::string_view date = *it++;
    std::string_view time = *it++;
    std::string_view level = *it++;
    // Remaining segments are the message

    std::cout << "Date: " << date << std::endl;
    std::cout << "Time: " << time << std::endl;
    std::cout << "Level: " << level << std::endl;
}

// Zero-copy performance
std::string original = "one,two,three";
for (auto segment : splitView(original, ',')) {
    // segment.data() points to original string memory
    // No heap allocations performed
    assert(segment.data() >= original.data() &&
           segment.data() < original.data() + original.size());
}
```

### Real-World Applications

```cpp
#include <map>
#include <nfx/string/Splitter.h>

using namespace nfx::string;

// CSV file processing
void processCSVLine(const std::string& csvLine) {
    auto splitter = splitView(csvLine, ',');
    auto it = splitter.begin();

    if (it != splitter.end()) {
        std::string_view name = *it++;
        std::string_view age = *it++;
        std::string_view city = *it++;

        // Process fields without string allocation
    }
}

// Configuration file parsing
std::map<std::string_view, std::string_view> parseConfig(const std::string& config) {
    std::map<std::string_view, std::string_view> settings;

    for (auto line : splitView(config, '\n')) {
        auto keyValue = splitView(line, '=');
        auto it = keyValue.begin();

        if (it != keyValue.end()) {
            std::string_view key = *it++;
            if (it != keyValue.end()) {
                std::string_view value = *it;
                settings[key] = value;
            }
        }
    }

    return settings;
}

// URL path processing
void processURLPath(const std::string& path) {
    // Split "/api/v1/users/123/profile" into components
    std::vector<std::string_view> pathComponents;

    for (auto component : splitView(path, '/')) {
        if (!component.empty()) {  // Skip empty components from leading/trailing '/'
            pathComponents.push_back(component);
        }
    }

    // pathComponents = ["api", "v1", "users", "123", "profile"]
}
```

### Complete Example

```cpp
#include <iostream>
#include <vector>
#include <nfx/string/Splitter.h>

int main()
{
    using namespace nfx::string;

    // CSV processing
    std::string csvData = "John,Doe,30,Engineer,New York";
    std::cout << "CSV Data: " << csvData << std::endl;

    std::vector<std::string_view> fields;
    for (auto field : splitView(csvData, ',')) {
        fields.push_back(field);
    }

    std::cout << "Parsed " << fields.size() << " fields:" << std::endl;
    for (size_t i = 0; i < fields.size(); ++i) {
        std::cout << "  [" << i << "]: '" << fields[i] << "'" << std::endl;
    }

    // Configuration parsing
    std::string config = "debug=true;port=8080;host=localhost";
    std::cout << "\nConfig: " << config << std::endl;

    for (auto setting : splitView(config, ';')) {
        auto keyValue = splitView(setting, '=');
        auto it = keyValue.begin();

        std::string_view key = *it++;
        if (it != keyValue.end()) {
            std::string_view value = *it;
            std::cout << "  " << key << " -> " << value << std::endl;
        }
    }

    // Path processing
    std::string path = "/home/user/documents/file.txt";
    std::cout << "\nPath: " << path << std::endl;
    std::cout << "Components: ";

    bool first = true;
    for (auto component : splitView(path, '/')) {
        if (!component.empty()) {
            if (!first) std::cout << " -> ";
            std::cout << component;
            first = false;
        }
    }
    std::cout << std::endl;

    return 0;
}
```

**Sample Output:**

```
CSV Data: John,Doe,30,Engineer,New York
Parsed 5 fields:
  [0]: 'John'
  [1]: 'Doe'
  [2]: '30'
  [3]: 'Engineer'
  [4]: 'New York'

Config: debug=true;port=8080;host=localhost
  debug -> true
  port -> 8080
  host -> localhost

Path: /home/user/documents/file.txt
Components: home -> user -> documents -> file.txt
```

### String Validation & Classification

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

// String validation
bool empty = isEmpty("");                    // true
bool whitespace = isNullOrWhiteSpace("   "); // true
bool digits = isAllDigits("12345");          // true
bool length = hasExactLength("password", 8); // true

// Character classification
bool space = isWhitespace(' ');              // true
bool digit = isDigit('5');                   // true
bool alpha = isAlpha('A');                   // true
bool alnum = isAlphaNumeric('Z');            // true

// URI classification (RFC 3986)
bool reserved = isUriReserved(':');          // true
bool unreserved = isUriUnreserved('A');      // true
```

### String Operations & Manipulation

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

std::string_view text = "  Hello World  ";

// String operations
bool starts = startsWith(text, "  Hello");      // true
bool ends = endsWith(text, "World  ");          // true
bool contains_word = contains(text, "World");   // true
bool equal = equals(text, "  Hello World  ");   // true
bool iequal = iequals("HELLO", "hello");        // true (case-insensitive)

// String trimming (non-allocating)
std::string_view trimmed = trim(text);          // "Hello World"
std::string_view left = trimStart(text);        // "Hello World  "
std::string_view right = trimEnd(text);         // "  Hello World"

// Case conversion
char lower = toLower('A');                      // 'a'
char upper = toUpper('z');                      // 'Z'
std::string lowerStr = toLower("Hello World");  // "hello world"
std::string upperStr = toUpper("Hello World");  // "HELLO WORLD"
```

### Parsing Utilities

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

// Boolean parsing (supports multiple formats)
bool result;
bool success1 = fromString<bool>("true", result);    // true, result = true
bool success2 = fromString<bool>("yes", result);     // true, result = true
bool success3 = fromString<bool>("1", result);       // true, result = true
bool success4 = fromString<bool>("false", result);   // true, result = false
bool success5 = fromString<bool>("invalid", result); // false

// Numeric parsing
int intValue;
bool intOk = fromString<int>("12345", intValue);     // true, intValue = 12345

std::uint32_t uintValue;
bool uintOk = fromString<std::uint32_t>("42", uintValue);     // true, uintValue = 42

std::int64_t longValue;
bool longOk = fromString<std::int64_t>("-9223372036854775808", longValue); // true

double doubleValue;
bool doubleOk = fromString<double>("123.456", doubleValue); // true, doubleValue = 123.456
```

### Network & URI Validation

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

// IP address validation
bool ipv4Valid = isIpv4Address("192.168.1.1");       // true
bool ipv4Invalid = isIpv4Address("256.1.1.1");       // false (out of range)
bool ipv4LeadingZero = isIpv4Address("01.02.03.04"); // false (leading zeros)

bool ipv6Valid = isIpv6Address("2001:db8::1");       // true
bool ipv6Loopback = isIpv6Address("::1");            // true
bool ipv6Mapped = isIpv6Address("::ffff:192.0.2.1"); // true (IPv4-mapped)
bool ipv6Zone = isIpv6Address("fe80::1%eth0");       // true (with zone ID)

// Hostname and domain validation
bool hostnameValid = isHostname("example.com");  // true
bool hostnameLocal = isHostname("localhost");    // true
bool hostnameInvalid = isHostname("-invalid");   // false (starts with hyphen)

bool domainValid = isDomainName("example.com");       // true (has dot)
bool domainInvalid = isDomainName("localhost");       // false (no dot, not FQDN)

// Port validation (compile-time type safety)
bool portValid = isPortNumber(80);                    // true
bool portMax = isPortNumber(65535);                   // true
bool portInvalid = isPortNumber(70000);               // false (out of range)
bool portStringValid = isPortNumber("8080");          // true

// Endpoint parsing (host:port format)
std::string_view host;
uint16_t port;

// IPv4 endpoint
bool ep1 = tryParseEndpoint("192.168.1.1:80", host, port);
// host = "192.168.1.1", port = 80

// IPv6 endpoint (requires brackets)
bool ep2 = tryParseEndpoint("[2001:db8::1]:443", host, port);
// host = "2001:db8::1", port = 443

// Hostname endpoint
bool ep3 = tryParseEndpoint("example.com:8080", host, port);
// host = "example.com", port = 8080
```

## Installation & Packaging

nfx-stringutils provides packaging options for distribution.

### Package Generation

```bash
# Configure with packaging options
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DNFX_STRINGUTILS_PACKAGE_ARCHIVE=ON \
         -DNFX_STRINGUTILS_PACKAGE_DEB=ON \
         -DNFX_STRINGUTILS_PACKAGE_RPM=ON

# Generate binary packages
cmake --build . --target package
# or
cd build && cpack

# Generate source packages
cd build && cpack --config CPackSourceConfig.cmake
```

### Supported Package Formats

| Format      | Platform       | Description                        | Requirements |
| ----------- | -------------- | ---------------------------------- | ------------ |
| **TGZ/ZIP** | Cross-platform | Compressed archive packages        | None         |
| **DEB**     | Debian/Ubuntu  | Native Debian packages             | `dpkg-dev`   |
| **RPM**     | RedHat/SUSE    | Native RPM packages                | `rpm-build`  |
| **WiX**     | Windows        | Professional MSI installer         | `WiX 3.11+`  |
| **Source**  | Cross-platform | Source code distribution (TGZ+ZIP) | None         |

### Installation

```bash
# Linux (DEB-based systems)
sudo dpkg -i nfx-stringutils_*_amd64.deb

# Linux (RPM-based systems)
sudo rpm -ivh nfx-stringutils-*-Linux.rpm

# Windows (MSI installer)
nfx-stringutils-0.1.0-MSVC.msi

# Manual installation (extract archive)
tar -xzf nfx-stringutils-*-Linux.tar.gz -C /usr/local/
```

## Project Structure

```
nfx-stringutils/
├── benchmark/             # Performance benchmarks with Google Benchmark
├── cmake/                 # CMake modules and configuration
├── include/nfx/           # Public headers: string utilities
├── samples/               # Example usage and demonstrations
└── test/                  # Comprehensive unit tests with GoogleTest
```

## Performance

nfx-stringutils is optimized for high performance with:

- **Zero-allocation operations** using `std::string_view` for splitting and trimming
- **Zero-copy design** - string segments reference original memory without duplication
- **Constexpr functions** for compile-time optimization where possible
- **Highly optimized character classification** faster than standard library equivalents
- **Efficient string parsing** with minimal overhead
- **Iterator-based interface** with minimal runtime cost
- **Cache-friendly memory access** patterns for large data processing

For detailed performance metrics and benchmarks, see the [benchmark documentation](benchmark/README.md).

## Roadmap

See [TODO.md](TODO.md) for upcoming features and project roadmap.

## Changelog

See the [CHANGELOG.md](CHANGELOG.md) for a detailed history of changes, new features, and bug fixes.

## License

This project is licensed under the MIT License.

## Development Dependencies

- **[GoogleTest](https://github.com/google/googletest)**: Testing framework (BSD 3-Clause License) - Development only
- **[Google Benchmark](https://github.com/google/benchmark)**: Performance benchmarking framework (Apache 2.0 License) - Development only

All dependencies are automatically fetched via CMake FetchContent when building the library, tests, or benchmarks.

---

_Updated on November 23, 2025_
