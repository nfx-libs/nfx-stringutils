# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- NIL

### Changed

- NIL

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- NIL

### Security

- NIL

## [0.3.0] - 2025-11-30

### Added

- **Character Classification**: Additional character validation utilities

  - `isHexDigit()` - Check if character is hexadecimal digit (0-9, a-f, A-F) - `constexpr` and `noexcept`

- **Internationalization Support**: IDN (Internationalized Domain Names) validation

  - `isIdnHostname()` - Validate hostnames with Unicode characters or Punycode encoding (xn--)
  - `isIdnEmail()` - Validate email addresses with Unicode in local-part or domain (EAI/SMTPUTF8)

- **IRI Support**: Internationalized Resource Identifier validation (RFC 3987)

  - `isIri()` - Validate IRI format with Unicode characters (e.g., "https://example.com/路径", "http://例え.jp/テスト")
  - `isIriReference()` - Validate IRI or relative IRI-reference with Unicode support (e.g., "/路径/to/resource", "../über/münchen")
  - Supports Unicode in paths, queries, and fragments while maintaining strict scheme validation
  - Rejects control characters (null bytes, newlines, carriage returns) for security

- **URI Template Support**: URI Template validation (RFC 6570)

  - `isUriTemplate()` - Validate URI Template format with variable expansion syntax
  - Supports simple variables (`{id}`), reserved expansion (`{+path}`), query parameters (`{?q,page}`)
  - Validates operators (+ # . / ; ? &), modifiers (explode `*`, prefix `:max`), and variable names
  - Comprehensive validation: rejects malformed expressions, invalid operators, and control characters

### Changed

- **BREAKING**: Standardized acronym capitalization in function names (camelCase convention)

  - URI functions: `isURIReserved()` → `isUriReserved()`, `isURIUnreserved()` → `isUriUnreserved()`, `isURI()` → `isUri()`, `isURIReference()` → `isUriReference()`
  - IP functions: `isIPv4Address()` → `isIpv4Address()`, `isIPv6Address()` → `isIpv6Address()`
  - UUID: `isUUID()` → `isUuid()`
  - JSON Pointer: `isJSONPointer()` → `isJsonPointer()`, `isRelativeJSONPointer()` → `isRelativeJsonPointer()`

- **BREAKING**: Renamed validation functions for clarity and consistency

  - `isValidHostname()` → `isHostname()`
  - `isValidIdnHostname()` → `isIdnHostname()`
  - `isValidPort()` → `isPortNumber()`

### Fixed

- `isTime()` - Corrected leap second validation (now accepts 00-60, was accepting 61+)
- `isRelativeJsonPointer()` - Fixed validation to accept bare non-negative integers (e.g., "0", "42")

## [0.2.0] - 2025-11-29

### Added

- **Format Validation**: Constexpr RFC-compliant validators (~54x faster than regex)
  - `isDate()`, `isTime()`, `isDateTime()` - RFC 3339 date/time validation
  - `isDuration()` - ISO 8601 duration format (P1Y2M3DT4H5M6S, P1W)
  - `isEmail()` - RFC 5321 email validation
  - `isUUID()` - RFC 4122 UUID format (8-4-4-4-12)
  - `isURI()`, `isURIReference()` - RFC 3986 URI validation
  - `isJSONPointer()`, `isRelativeJSONPointer()` - RFC 6901 JSON Pointer

## [0.1.1] - 2025-11-28

### Changed

- Consolidated packaging tool detection in CMake configuration

### Fixed

- Removed incorrect runtime dependencies from DEB/RPM packages

## [0.1.0] - 2025-11-23 - Initial Release

### Added

- **String Joining & Splitting**: Collection and sequence operations

  - `join()` - Join container elements or iterator range with delimiter
  - `StringSplitter` - Zero-allocation string splitting with iterator interface
  - `splitView()` - Factory function for convenient splitting
  - Supports any string-like type (std::string, const char\*, etc.)
  - Range-based for loop support

- **Character Classification**: ASCII character validation utilities

  - `isWhitespace()` - Check if character is whitespace (space, tab, newline, etc.)
  - `isDigit()` - Check if character is a decimal digit (0-9)
  - `isAlpha()` - Check if character is alphabetic (a-z, A-Z)
  - `isAlphaNumeric()` - Check if character is alphanumeric
  - All functions are `constexpr` and `noexcept` for compile-time evaluation

- **String Validation**: String content validation and testing

  - `isEmpty()` - Check if string is empty
  - `isNullOrWhiteSpace()` - Check if string is null, empty, or contains only whitespace
  - `isAllDigits()` - Check if string contains only digits
  - `hasExactLength()` - Check if string has exact length
  - All functions use `std::string_view` for zero-copy operations

- **Case Conversion**: Character and string case manipulation

  - `toLower()` - Convert character or string to lowercase
  - `toUpper()` - Convert character or string to uppercase
  - Character functions are `constexpr` and `noexcept`
  - String functions support ASCII characters only

- **String Comparison**: Advanced comparison operations

  - `equals()` - Case-sensitive string equality comparison
  - `iequals()` - Case-insensitive string equality comparison
  - `compareIgnoreCase()` - Three-way case-insensitive comparison (-1/0/+1)
  - `naturalCompare()` - Natural sorting with embedded number handling (e.g., "file2.txt" < "file10.txt")
  - `commonPrefix()` - Find longest common prefix between two strings (returns `string_view`)
  - `commonSuffix()` - Find longest common suffix between two strings (returns `string_view`)
  - `startsWith()` - Check if string starts with prefix
  - `endsWith()` - Check if string ends with suffix
  - `contains()` - Check if string contains substring
  - `count()` - Count non-overlapping occurrences of substring or character
  - `countOverlapping()` - Count all occurrences of substring including overlapping matches

- **String Trimming**: Whitespace removal utilities

  - `trim()` - Remove leading and trailing whitespace (returns `string_view`, zero-copy)
  - `trimStart()` - Remove leading whitespace (returns `string_view`, zero-copy)
  - `trimEnd()` - Remove trailing whitespace (returns `string_view`, zero-copy)
  - All functions are `constexpr` and `noexcept` for zero-overhead abstraction

- **Predicate-Based Operations**: Generic string operations with custom predicates

  - `trimIf()` - Remove leading/trailing characters matching predicate
  - `trimStartIf()` - Remove leading characters matching predicate
  - `trimEndIf()` - Remove trailing characters matching predicate
  - `countIf()` - Count characters matching predicate
  - `findIf()` - Find first character matching predicate
  - `findIfNot()` - Find first character NOT matching predicate
  - `replaceIf()` - Replace characters matching predicate
  - `removeIf()` - Remove characters matching predicate
  - All predicate functions accept lambda or function pointer accepting `char` and returning `bool`

- **String Manipulation**: String transformation and modification

  - `replace()` - Replace first occurrence of substring
  - `replaceAll()` - Replace all non-overlapping occurrences of substring
  - `replaceIf()` - Replace characters matching predicate with replacement character
  - `removeAll()` - Remove all occurrences of character or substring
  - `removeIf()` - Remove characters matching predicate
  - `removeWhitespace()` - Remove all whitespace characters
  - `collapseWhitespace()` - Collapse consecutive whitespace to single space
  - `padLeft()` - Pad string to specified length (right-aligned)
  - `padRight()` - Pad string to specified length (left-aligned)
  - `center()` - Center string within specified width
  - `repeat()` - Repeat string specified number of times
  - `reverse()` - Reverse string content

- **Substring Extraction**: Zero-copy substring operations

  - `substringBefore()` - Extract portion before first occurrence of delimiter
  - `substringAfter()` - Extract portion after first occurrence of delimiter
  - `substringBeforeLast()` - Extract portion before last occurrence of delimiter
  - `substringAfterLast()` - Extract portion after last occurrence of delimiter
  - `extractBetween()` - Extract substring between start and end delimiters
  - `removePrefix()` - Remove prefix from string if present
  - `removeSuffix()` - Remove suffix from string if present
  - `indexOf()` - Find first occurrence of substring
  - `lastIndexOf()` - Find last occurrence of substring
  - All functions return `string_view` (non-owning views into original string data)

- **Unified Parsing API**: String to type conversion with validation

  - `fromString<T>()` - Unified parsing API supporting two interfaces:
    - Output parameter: `bool fromString(string_view, T& result)` - zero-overhead for performance-critical code
    - Optional return: `std::optional<T> fromString(string_view)` - modern C++ interface
  - Supported types: `bool`, `int`, `uint32_t`, `int64_t`, `uint64_t`, `float`, `double`
  - Boolean parsing supports: "true"/"false", "1"/"0", "yes"/"no", "on"/"off", "t"/"f", "y"/"n" (case-insensitive)
  - Numeric parsing uses `std::from_chars` for optimal performance (matches stdlib at ~15ns for int)
  - Proper overflow and underflow detection via `std::errc`

- **Text Formatting**: String formatting and layout utilities

  - `truncate()` - Truncate string to maximum length (with optional ellipsis)
  - `wordWrap()` - Word wrap text to specified width
  - `indent()` - Add indentation to each line
  - `dedent()` - Remove common leading whitespace from all lines

- **URI Character Classification**: RFC 3986 compliant URI utilities

  - `isURIReserved()` - Check if character is URI reserved (`:/?#[]@!$&'()*+,;=`)
  - `isURIUnreserved()` - Check if character is URI unreserved (alphanumeric + `-._~`)
  - All functions are `constexpr` and `noexcept`

- **String Encoding**: URL, JSON, XML, and C++ string encoding/decoding

  - `urlEncode()` - Encode string for URL (percent-encoding per RFC 3986)
  - `urlDecode()` - Decode URL-encoded string
  - `jsonEscape()` - Escape string for JSON (handles quotes, backslashes, control characters, Unicode)
  - `jsonUnescape()` - Unescape JSON string (supports Unicode escapes)
  - `xmlEscape()` - Escape string for XML (handles special characters)
  - `xmlUnescape()` - Unescape XML entities
  - `cppEscape()` - Escape string for C++ literals (newline, tab, backslash, quotes)
  - `cppUnescape()` - Unescape C++ escape sequences

- **Network Validation**: RFC-compliant network address validation

  - `isIPv4Address()` - IPv4 address validation (RFC 791)
    - Validates dotted-decimal notation (e.g., "192.168.1.1")
    - Rejects leading zeros (e.g., "192.168.01.1" is invalid)
    - Range validation for each octet (0-255)
  - `isIPv6Address()` - IPv6 address validation (RFC 4291/5952)
    - Supports full notation (e.g., "2001:0db8:85a3:0000:0000:8a2e:0370:7334")
    - Supports compressed notation (e.g., "2001:db8::1")
    - Supports IPv4-mapped addresses (e.g., "::ffff:192.0.2.1")
    - Validates hexadecimal format and segment count
  - `isValidHostname()` - Hostname validation (RFC 1123)
    - Maximum 253 characters total length
    - Labels (segments) max 63 characters each
    - Labels must start/end with alphanumeric
    - Labels can contain hyphens in the middle
  - `isDomainName()` - Domain name validation (RFC 1035)
    - Requires fully qualified domain name format
    - At least one dot separator required
    - Follows same rules as hostname validation
  - `isValidPort()` - Port number validation (RFC 6335)
    - Validates port range (0-65535)
    - Compile-time type safety with templates
    - Supports string and numeric input

- **Endpoint Parsing**: Network endpoint parsing utilities

  - `tryParseEndpoint()` - Parse host:port combinations
    - Supports IPv4:port format (e.g., "192.168.1.1:8080")
    - Supports hostname:port format (e.g., "example.com:443")
    - Supports [IPv6]:port format (e.g., "[2001:db8::1]:8080")
    - Uses output parameters: `bool tryParseEndpoint(endpoint, host, port)`
    - Returns `true` on success, `false` on parse error

- **Documentation**

  - README with feature overview
  - Detailed API documentation with Doxygen comments
  - Sample applications demonstrating library usage
    - `Sample_Network` - Network & URI validation examples
    - `Sample_StringSplitter` - Zero-copy string splitting examples
    - `Sample_StringBasics` - Validation, parsing, case conversion
    - `Sample_StringOperations` - Replacement, joining, padding
    - `Sample_StringPredicates` - Custom predicates and filtering
    - `Sample_StringEncoding` - URL/JSON/XML/C++ encoding
    - `Sample_StringFormatting` - Truncation, wrapping, indentation
    - `Sample_StringComparison` - Advanced comparison operations
  - Build and installation instructions

- **Testing & Benchmarking**
  - Unit test suite
  - Performance benchmarks for all operations
  - Cross-compiler performance validation
