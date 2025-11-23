# Benchmarks

---

## Test Environment

### Hardware Configuration

| Component                | Specification                                                 |
| ------------------------ | ------------------------------------------------------------- |
| **Computer Model**       | Lenovo ThinkPad P15v Gen 3                                    |
| **CPU**                  | 12th Gen Intel Core i7-12800H (20 logical, 14 physical cores) |
| **Base Clock**           | 2.80 GHz                                                      |
| **Turbo Clock**          | 4.80 GHz                                                      |
| **L1 Data Cache**        | 48 KiB (×6 P-cores) + 32 KiB (×8 E-cores)                     |
| **L1 Instruction Cache** | 32 KiB (×6 P-cores) + 64 KiB (×2 E-core clusters)             |
| **L2 Unified Cache**     | 1.25 MiB (×6 P-cores) + 2 MiB (×2 E-core clusters)            |
| **L3 Unified Cache**     | 24 MiB (×1 shared)                                            |
| **RAM**                  | DDR4-3200 (32GB)                                              |
| **GPU**                  | NVIDIA RTX A2000 4GB GDDR6                                    |

### Software Configuration

| Platform    | OS         | Benchmark Framework     | C++ Compiler              | nfx-stringutils Version |
| ----------- | ---------- | ----------------------- | ------------------------- | ----------------------- |
| **Linux**   | LMDE 7     | Google Benchmark v1.9.4 | GCC 14.2.0-x64            | v0.1.0                  |
| **Linux**   | LMDE 7     | Google Benchmark v1.9.4 | Clang 19.1.7-x64          | v0.1.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | MinGW GCC 14.2.0-x64      | v0.1.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | Clang-GNU-CLI 19.1.5-x64  | v0.1.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | Clang-MSVC-CLI 19.1.5-x64 | v0.1.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | MSVC 19.44.35217.0-x64    | v0.1.0                  |

---

# Performance Results

## String Splitter Operations

| Operation                      | Linux GCC | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------------ | --------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **Manual CSV Splitting**       | 22.1 ns   | **21.1 ns** | 32.0 ns           | 45.0 ns               | 47.5 ns                | 25.7 ns      |
| **Splitter CSV Splitting**     | 25.3 ns   | **24.0 ns** | 34.3 ns           | 32.1 ns               | 32.9 ns                | 28.1 ns      |
| **SplitView CSV Splitting**    | 25.2 ns   | **24.1 ns** | 35.1 ns           | 31.4 ns               | 32.9 ns                | 28.3 ns      |
| **Manual Path Splitting**      | 19.0 ns   | **18.5 ns** | 29.5 ns           | 40.2 ns               | 42.1 ns                | 24.2 ns      |
| **Splitter Path Splitting**    | 20.3 ns   | **19.9 ns** | 28.7 ns           | 30.5 ns               | 29.4 ns                | 27.9 ns      |
| **SplitView Path Splitting**   | 20.3 ns   | 20.1 ns     | **28.6 ns**       | **28.6 ns**           | 28.7 ns                | 28.8 ns      |
| **Manual Config Splitting**    | 16.9 ns   | **15.9 ns** | 33.5 ns           | 34.9 ns               | 36.3 ns                | 20.2 ns      |
| **Splitter Config Splitting**  | **17.7 ns** | **17.7 ns** | 34.5 ns         | **25.4 ns**           | 27.4 ns                | 21.9 ns      |
| **SplitView Config Splitting** | 17.7 ns   | **17.5 ns** | 35.1 ns           | 25.7 ns               | 27.4 ns                | 23.8 ns      |
| **Splitter Zero Allocation**   | **23.9 ns** | 24.0 ns   | 32.1 ns           | 29.2 ns               | 29.0 ns                | 26.5 ns      |

## String Utilities Operations

| Operation                             | Linux GCC | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------------------- | --------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **std::isspace**                      | 22.0 ns   | 21.8 ns     | 23.4 ns           | **20.6 ns**           | **20.1 ns**            | 32.0 ns      |
| **nfx::string::isWhitespace**         | 7.24 ns   | **6.35 ns** | 6.60 ns           | 6.44 ns               | 6.45 ns                | 17.2 ns      |
| **std::isdigit**                      | **4.79 ns** | **4.79 ns** | 4.94 ns         | 5.12 ns               | 4.94 ns                | 29.7 ns      |
| **nfx::string::isDigit**              | **4.80 ns** | 4.85 ns   | 5.01 ns           | 5.52 ns               | 5.11 ns                | 13.4 ns      |
| **std::isalpha**                      | **21.8 ns** | **21.8 ns** | 26.2 ns         | 25.3 ns               | 25.7 ns                | 32.2 ns      |
| **nfx::string::isAlpha**              | **4.83 ns** | 5.85 ns   | 5.03 ns           | 5.04 ns               | 5.06 ns                | 21.0 ns      |
| **std::string_view::empty**           | 5.01 ns   | 6.25 ns     | **4.41 ns**       | 6.19 ns               | 6.46 ns                | 14.4 ns      |
| **nfx::string::isEmpty**              | 4.82 ns   | 6.27 ns     | **4.63 ns**       | 6.31 ns               | 6.48 ns                | 14.7 ns      |
| **Manual isNullOrWhiteSpace**         | 50.7 ns   | 48.1 ns     | 48.7 ns           | **35.1 ns**           | 35.4 ns                | 59.6 ns      |
| **nfx::string::isNullOrWhiteSpace**   | **13.3 ns** | 17.7 ns   | 15.0 ns           | 19.4 ns               | 17.8 ns                | 33.4 ns      |
| **Manual isAllDigits**                | 21.5 ns   | **20.1 ns** | 20.6 ns           | 22.8 ns               | 24.5 ns                | 72.1 ns      |
| **nfx::string::isAllDigits**          | 22.5 ns   | 24.1 ns     | **21.9 ns**       | **22.1 ns**           | 24.3 ns                | 35.4 ns      |
| **std::starts_with**                  | 13.1 ns   | **9.39 ns** | 16.4 ns           | 10.3 ns               | 10.2 ns                | 33.0 ns      |
| **nfx::string::startsWith**           | 13.0 ns   | **10.4 ns** | 16.2 ns           | 12.0 ns               | **10.4 ns**            | 28.5 ns      |
| **std::ends_with**                    | 12.3 ns   | 10.6 ns     | **9.77 ns**       | 11.8 ns               | 10.5 ns                | 30.3 ns      |
| **nfx::string::endsWith**             | 12.5 ns   | 11.0 ns     | **9.58 ns**       | 10.0 ns               | 10.1 ns                | 32.2 ns      |
| **std::contains**                     | 53.2 ns   | **47.0 ns** | 76.8 ns           | 144 ns                | 117 ns                 | 155 ns       |
| **nfx::string::contains**             | 51.7 ns   | **48.7 ns** | 83.1 ns           | 152 ns                | 120 ns                 | 159 ns       |
| **Manual count (substring)**          | 76.9 ns   | **73.5 ns** | 128 ns            | 152 ns                | 151 ns                 | 170 ns       |
| **nfx::string::count (substring)**    | **72.6 ns** | 73.7 ns   | 124 ns            | 153 ns                | 147 ns                 | 177 ns       |
| **Manual count (char)**               | 72.8 ns   | **62.8 ns** | 73.5 ns           | 63.6 ns               | 67.8 ns                | 136 ns       |
| **nfx::string::count (char)**         | 71.4 ns   | **49.7 ns** | 70.7 ns           | 53.9 ns               | 52.6 ns                | 122 ns       |
| **Manual replace**                    | 163 ns    | **162 ns**  | 266 ns            | 248 ns                | 249 ns                 | 293 ns       |
| **nfx::string::replace**              | **155 ns** | 200 ns     | 276 ns            | 332 ns                | 316 ns                 | 332 ns       |
| **Manual replaceAll**                 | 228 ns    | **225 ns**  | 313 ns            | 306 ns                | 302 ns                 | 357 ns       |
| **nfx::string::replaceAll**           | **240 ns** | 267 ns     | 367 ns            | 415 ns                | 389 ns                 | 441 ns       |
| **Manual join**                       | **31.6 ns** | 32.4 ns   | 60.4 ns           | 50.1 ns               | 51.3 ns                | 69.3 ns      |
| **nfx::string::join**                 | **31.4 ns** | 43.5 ns   | 59.9 ns           | 61.6 ns               | 59.9 ns                | 83.5 ns      |
| **std::find**                         | 50.9 ns   | **48.2 ns** | 93.0 ns           | 143 ns                | 121 ns                 | 171 ns       |
| **nfx::string::indexOf**              | 51.2 ns   | **47.0 ns** | 94.4 ns           | 148 ns                | 118 ns                 | 171 ns       |
| **std::rfind**                        | 57.1 ns   | **45.5 ns** | 70.6 ns           | 123 ns                | 108 ns                 | 135 ns       |
| **nfx::string::lastIndexOf**          | 52.0 ns   | 52.5 ns     | **65.3 ns**       | 120 ns                | 109 ns                 | 134 ns       |
| **Manual substringBefore**            | 49.0 ns   | **46.0 ns** | 101 ns            | 114 ns                | 117 ns                 | 149 ns       |
| **nfx::string::substringBefore**      | 48.3 ns   | 47.4 ns     | **95.2 ns**       | 116 ns                | 119 ns                 | 155 ns       |
| **Manual substringAfter**             | 49.4 ns   | **44.4 ns** | 100 ns            | 121 ns                | 118 ns                 | 149 ns       |
| **nfx::string::substringAfter**       | 51.5 ns   | **44.5 ns** | 106 ns            | 115 ns                | 120 ns                 | 157 ns       |
| **Manual trim**                       | 33.8 ns   | **28.3 ns** | 37.4 ns           | 104 ns                | 105 ns                 | 295 ns       |
| **nfx::string::trim**                 | **25.1 ns** | 29.0 ns   | 31.3 ns           | 37.9 ns               | 37.2 ns                | 54.6 ns      |
| **std::tolower (char)**               | 22.3 ns   | 22.3 ns     | 23.4 ns           | 22.5 ns               | **21.3 ns**            | 35.2 ns      |
| **nfx::string::toLower (char)**       | **3.30 ns** | 6.53 ns   | 4.08 ns           | 5.69 ns               | 5.78 ns                | 15.8 ns      |
| **std::transform tolower**            | 449 ns    | **432 ns**  | 562 ns            | 492 ns                | 491 ns                 | 686 ns       |
| **nfx::string::toLower (string)**     | **375 ns** | 417 ns     | 488 ns            | 467 ns                | 464 ns                 | 1065 ns      |
| **std::toupper (char)**               | 30.7 ns   | 33.1 ns     | **23.3 ns**       | 30.2 ns               | 27.7 ns                | 40.2 ns      |
| **nfx::string::toUpper (char)**       | **3.31 ns** | 5.03 ns   | 4.10 ns           | 5.60 ns               | 5.46 ns                | 13.3 ns      |
| **std::transform toupper**            | **483 ns** | 509 ns     | 662 ns            | 621 ns                | 529 ns                 | 744 ns       |
| **nfx::string::toUpper (string)**     | 403 ns    | **370 ns**  | 502 ns            | 447 ns                | 446 ns                 | 1059 ns      |
| **std::from_chars (int)**             | **12.2 ns** | 13.6 ns   | 18.9 ns           | 16.3 ns               | 15.2 ns                | 33.6 ns      |
| **nfx::string::fromString\<int\>**    | **12.1 ns** | 16.2 ns   | 14.6 ns           | 14.9 ns               | 15.0 ns                | 53.2 ns      |
| **std::from_chars (double)**          | 41.8 ns   | **40.5 ns** | 60.4 ns           | 101 ns                | 111 ns                 | 179 ns       |
| **nfx::string::fromString\<double\>** | 42.6 ns   | **43.1 ns** | 63.4 ns           | 102 ns                | 111 ns                 | 189 ns       |
| **Manual isURIReserved**              | 8.74 ns   | **7.01 ns** | 9.77 ns           | 7.66 ns               | 7.03 ns                | 26.8 ns      |
| **nfx::string::isURIReserved**        | 8.16 ns   | **7.10 ns** | 16.4 ns           | 7.50 ns               | 7.14 ns                | 27.5 ns      |
| **Manual isURIUnreserved**            | **9.50 ns** | 10.4 ns   | 12.3 ns           | 11.6 ns               | 10.2 ns                | 35.3 ns      |
| **nfx::string::isURIUnreserved**      | **9.74 ns** | 10.2 ns   | 12.4 ns           | 11.3 ns               | 11.2 ns                | 30.3 ns      |
| **Manual compareIgnoreCase**          | 82.8 ns   | 75.6 ns     | 76.8 ns           | 77.2 ns               | **69.3 ns**            | 147 ns       |
| **nfx::string::compareIgnoreCase**    | 21.1 ns   | **17.1 ns** | 22.5 ns           | 18.6 ns               | 17.2 ns                | 31.6 ns      |
| **Lexicographic compare (baseline)**  | 15.5 ns   | **14.4 ns** | 26.6 ns           | 25.8 ns               | 24.0 ns                | 31.3 ns      |
| **nfx::string::naturalCompare**       | 38.5 ns   | **32.7 ns** | 47.3 ns           | 40.1 ns               | 37.3 ns                | 42.4 ns      |
| **Manual commonPrefix**               | **12.5 ns** | 13.7 ns   | 16.7 ns           | 15.4 ns               | 13.1 ns                | 22.7 ns      |
| **nfx::string::commonPrefix**         | 12.4 ns   | **12.1 ns** | 14.4 ns           | 14.7 ns               | 13.3 ns                | 26.1 ns      |
| **Manual commonSuffix**               | 16.4 ns   | **14.1 ns** | 16.8 ns           | 17.5 ns               | **14.1 ns**            | 26.5 ns      |
| **nfx::string::commonSuffix**         | **13.4 ns** | 15.2 ns   | 13.7 ns           | 17.4 ns               | 14.8 ns                | 20.9 ns      |

---

_Benchmarks executed on November 23, 2025_
