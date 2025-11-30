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
| **Linux**   | LMDE 7     | Google Benchmark v1.9.4 | GCC 14.2.0-x64            | v0.3.0                  |
| **Linux**   | LMDE 7     | Google Benchmark v1.9.4 | Clang 19.1.7-x64          | v0.3.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | MinGW GCC 14.2.0-x64      | v0.3.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | Clang-GNU-CLI 19.1.5-x64  | v0.3.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | Clang-MSVC-CLI 19.1.5-x64 | v0.3.0                  |
| **Windows** | Windows 10 | Google Benchmark v1.9.4 | MSVC 19.44.35217.0-x64    | v0.3.0                  |

---

# Performance Results

## BM_CharacterClassification.cpp

| Operation                     | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ----------------------------- | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **std::isspace**              | 22.3 ns     | 23.5 ns     | 34.0 ns           | **19.4 ns**           | 27.0 ns                | 30.0 ns      |
| **nfx::string::isWhitespace** | **6.64 ns** | 7.57 ns     | 9.96 ns           | 6.75 ns               | 9.5 ns                 | 18.4 ns      |
| **std::isdigit**              | 5.11 ns     | 5.19 ns     | 7.69 ns           | **4.74 ns**           | 7 ns                   | 32.8 ns      |
| **nfx::string::isDigit**      | 4.97 ns     | 5.35 ns     | 7.91 ns           | **4.70 ns**           | 6.67 ns                | 11.5 ns      |
| **std::isalpha**              | 22.3 ns     | 28.2 ns     | 38.9 ns           | **19.8 ns**           | 25.2 ns                | 30.8 ns      |
| **nfx::string::isAlpha**      | 5.26 ns     | **5.22 ns** | 7.86 ns           | 5.03 ns               | 6.64 ns                | 21.4 ns      |

## BM_NetworkValidation.cpp

| Operation                        | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| -------------------------------- | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **Manual isURIReserved**         | 24.5 ns     | 14.4 ns     | 27.8 ns           | **14.1 ns**           | **14.1 ns**            | 49.5 ns      |
| **nfx::string::isURIReserved**   | 17.6 ns     | 14.3 ns     | 34.2 ns           | 16.3 ns               | **13.9 ns**            | 44.8 ns      |
| **Manual isURIUnreserved**       | **19.3 ns** | 24.8 ns     | 30.2 ns           | 23.7 ns               | 23.9 ns                | 59.0 ns      |
| **nfx::string::isURIUnreserved** | 19.9 ns     | 24.7 ns     | **26.3 ns**       | 24.0 ns               | 24.8 ns                | 50.6 ns      |

## BM_NumericParsing.cpp

| Operation                             | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------------------- | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **std::stoi**                         | **70.5**    | 71.2 ns     | 473 ns            | 241 ns                | 224 ns                 | 234 ns       |
| **std::from_chars (int)**             | **31.9 ns** | 39.3 ns     | 34.4 ns           | 49.8 ns               | 44.9 ns                | 51.5 ns      |
| **nfx::string::fromString\<int\>**    | 43.8 ns     | **31.8 ns** | 53.2 ns           | 49.7 ns               | 44.6 ns                | 88.8 ns      |
| **std::stod**                         | **257 ns**  | 269 ns      | 2311 ns           | 660 ns                | 557 ns                 | 544 ns       |
| **std::from_chars (double)**          | 69.1 ns     | **68.5 ns** | 96.9 ns           | 381 ns                | 339 ns                 | 401 ns       |
| **nfx::string::fromString\<double\>** | 72.2 ns     | **72.0 ns** | 98.1 ns           | 382 ns                | 327 ns                 | 385 ns       |

## BM_Splitter.cpp

| Operation                      | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------------ | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **Manual CSV Splitting**       | **19.5 ns** | 20.3 ns     | 37.7 ns           | 59.8 ns               | 45.5 ns                | 23.8 ns      |
| **Splitter CSV Splitting**     | **22.7 ns** | 23.6 ns     | 40.3 ns           | 36.7 ns               | 34.6 ns                | 26.8 ns      |
| **SplitView CSV Splitting**    | **22.7 ns** | 23.5 ns     | 36.7 ns           | 35.9 ns               | 34.8 ns                | 27.2 ns      |
| **Manual Path Splitting**      | **18.9 ns** | 19.3 ns     | 27.9 ns           | 48.9 ns               | 40.7 ns                | 23.3 ns      |
| **Splitter Path Splitting**    | **20.9 ns** | 21.9 ns     | 30.0 ns           | 32.1 ns               | 30.1 ns                | 25.8 ns      |
| **SplitView Path Splitting**   | **21.1 ns** | 21.8 ns     | 29.7 ns           | 33.4 ns               | 30.1 ns                | 29.3 ns      |
| **Manual Config Splitting**    | **15.3 ns** | 15.6 ns     | 35.1 ns           | 39.5 ns               | 34.9 ns                | 19.3 ns      |
| **Splitter Config Splitting**  | **16.6 ns** | 17.2 ns     | 34.9 ns           | 27.8 ns               | 26.6 ns                | 21.4 ns      |
| **SplitView Config Splitting** | **16.6 ns** | 17.4 ns     | 34.4 ns           | 27.5 ns               | 26.4 ns                | 22.7 ns      |
| **Splitter Zero Allocation**   | **21.9 ns** | 23.4 ns     | 31.2 ns           | 29.7 ns               | 32.2 ns                | 25.0 ns      |

## BM_StringComparison.cpp

| Operation                             | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------------------- | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **Manual compareIgnoreCase**          | 70.3 ns     | 63.3 ns     | **58.2 ns**       | 66.3 ns               | 64.7 ns                | 70.5 ns      |
| **nfx::string::equalsIgnoreCase**     | **15.7 ns** | 16.8 ns     | 17.4 ns           | 16.6 ns               | 16.8 ns                | 25.1 ns      |
| **Manual compareIgnoreCase ordering** | 67.9 ns     | 69.9 ns     | **58.9 ns**       | 67.3 ns               | 69.0 ns                | 78.7 ns      |
| **nfx::string::compareIgnoreCase**    | **15.3 ns** | 17.0 ns     | 16.8 ns           | 16.7 ns               | 16.8 ns                | 24.9 ns      |
| **Lexicographic compare (baseline)**  | 14.0 ns     | **13.3 ns** | 21.6 ns           | 21.8 ns               | 22.6 ns                | 24.9 ns      |
| **nfx::string::naturalCompare**       | 34.9 ns     | **29.0 ns** | 38.2 ns           | 34.2 ns               | 31.3 ns                | 36.8 ns      |
| **Manual commonPrefix**               | 12.8 ns     | 12.0 ns     | 11.8 ns           | 18.4 ns               | **11.6 ns**            | 15.8 ns      |
| **nfx::string::commonPrefix**         | 12.3 ns     | 16.3 ns     | 11.7 ns           | 16.5 ns               | **11.4 ns**            | 19.8 ns      |
| **Manual commonSuffix**               | 16.7 ns     | 15.4 ns     | 13.9 ns           | 14.3 ns               | **13.7 ns**            | 19.6 ns      |
| **nfx::string::commonSuffix**         | **12.5 ns** | 14.2 ns     | 14.0 ns           | 14.8ns                | 17.4 ns                | 18.1 ns      |

## BM_StringOperations.cpp

| Operation                     | Linux GCC    | Linux Clang  | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ----------------------------- | ------------ | ------------ | ----------------- | --------------------- | ---------------------- | ------------ |
| **std::starts_with**          | 1.40 ns      | 1.38 ns      | 2.176 ns          | **0.695 ns**          | 0.784 ns               | 2.65 ns      |
| **nfx::string::startsWith**   | 0.558 ns     | **0.431 ns** | 0.584 ns          | 0.698 ns              | 0.703 ns               | 1.17 ns      |
| **std::ends_with**            | 1.39 ns      | 1.41 ns      | 3.26 ns           | **0.518 ns**          | 0.555 ns               | 3.95 ns      |
| **nfx::string::endsWith**     | **0.324 ns** | 0.337 ns     | 0.348 ns          | 0.566 ns              | 0.575 ns               | 1.01 ns      |
| **std::contains**             | **2.96 ns**  | 5.67 ns      | 6.51 ns           | 10.0 ns               | 9.90 ns                | 10.4 ns      |
| **nfx::string::contains**     | 1.67 ns      | **1.65 ns**  | 3.73 ns           | 9.64 ns               | 9.99 ns                | 10.1 ns      |
| **Manual count (char)**       | 6.23 ns      | 11.7 ns      | 6.81 ns           | **3.96 ns**           | 3.97 ns                | 4.65 ns      |
| **nfx::string::count (char)** | **6.72 ns**  | 11.7 ns      | 7.32 ns           | 12.3 ns               | 12.3 ns                | 15.2 ns      |
| **Manual count (substring)**  | **3.00 ns**  | 3.18 ns      | 14.5 ns           | 22.2 ns               | 23.6 ns                | 23.4 ns      |
| **nfx::string::count (sub)**  | **3.01 ns**  | 3.16 ns      | 14.9 ns           | 23.1 ns               | 24.1 ns                | 23.2 ns      |
| **Manual replaceAll**         | **45.0 ns**  | 46.5 ns      | 69.8 ns           | 76.5 ns               | 65.7 ns                | 71.0 ns      |
| **nfx::string::replaceAll**   | **33.0 ns**  | 46.3 ns      | 71.1 ns           | 88.9 ns               | 76.1 ns                | 69.2 ns      |
| **Manual join**               | **50.4 ns**  | 52.6 ns      | 104 ns            | 83.1 ns               | 83.0 ns                | 101 ns       |
| **nfx::string::join**         | **40.9 ns**  | 52.8 ns      | 89.9 ns           | 90.4 ns               | 90.9 ns                | 98.6 ns      |
| **std::find**                 | **2.93 ns**  | 5.27 ns      | 5.84 ns           | 9.71 ns               | 9.94 ns                | 10.1 ns      |
| **nfx::string::indexOf**      | **1.52 ns**  | 1.71 ns      | 4.31 ns           | 9.91 ns               | 9.82 ns                | 10.1 ns      |
| **std::rfind**                | 23.1 ns      | 22.7 ns      | 24.1 ns           | **10.9 ns**           | 11.0 ns                | 11.9 ns      |
| **nfx::string::lastIndexOf**  | **2.54 ns**  | 3.13 ns      | 2.89 ns           | 11.0 ns               | 10.9 ns                | 12.2 ns      |

## BM_StringTransform.cpp

| Operation                            | Linux GCC    | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------------------ | ------------ | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **nfx::string::trim**                | **3.03 ns**  | **3.03 ns** | 3.64 ns           | 3.32 ns               | 3.23 ns                | 3.47 ns      |
| **nfx::string::trimStart**           | **1.53 ns**  | 1.55 ns     | 1.88 ns           | 1.73 ns               | 1.72 ns                | 2.34 ns      |
| **nfx::string::trimEnd**             | 1.77 ns      | **1.55 ns** | 1.98 ns           | 1.73 ns               | 1.73 ns                | 1.87 ns      |
| **Manual toLower**                   | **56.7 ns**  | 57.2 ns     | 124 ns            | 103 ns                | 119 ns                 | 109 ns       |
| **nfx::string::toLower**             | **51.7 ns**  | 58.9 ns     | 80.6 ns           | 95.5 ns               | 76.9 ns                | 93.3 ns      |
| **Manual toUpper**                   | **57.3 ns**  | 57.6 ns     | 124 ns            | 127 ns                | 124 ns                 | 119 ns       |
| **nfx::string::toUpper**             | **47.8 ns**  | 68.0 ns     | 76.7 ns           | 90.2 ns               | 77.9 ns                | 93.4 ns      |
| **nfx::string::substringBefore**     | **1.90 ns**  | 1.99 ns     | 4.90 ns           | 9.85 ns               | 9.78 ns                | 12.4 ns      |
| **nfx::string::substringAfter**      | **1.87 ns**  | 1.97 ns     | 4.91 ns           | 10.2 ns               | 9.91 ns                | 12.2 ns      |
| **nfx::string::substringBeforeLast** | **0.813 ns** | 1.03 ns     | 0.928 ns          | 4.15 ns               | 4.26 ns                | 5.99 ns      |
| **nfx::string::substringAfterLast**  | **0.934 ns** | 1.01 ns     | 1.04 ns           | 4.41 ns               | 4.27 ns                | 6.22 ns      |

## BM_StringValidation.cpp

| Operation                           | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ----------------------------------- | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **std::string_view::empty**         | **4.63 ns** | 6.06 ns     | 4.74 ns           | 6.24 ns               | 6.31 ns                | 24.4 ns      |
| **nfx::string::isEmpty**            | **4.25 ns** | 6.12 ns     | 4.65 ns           | 6.19 ns               | 6.24 ns                | 24.5 ns      |
| **Manual isNullOrWhiteSpace**       | 47.8 ns     | 40.7 ns     | 44.0 ns           | 37.7 ns               | **34.0 ns**            | 68.0 ns      |
| **nfx::string::isNullOrWhiteSpace** | **12.5 ns** | 14.3 ns     | 15.0 ns           | 15.5 ns               | 17.4 ns                | 43.9 ns      |
| **Manual isAllDigits**              | 20.1 ns     | **19.8 ns** | 21.7 ns           | 24.9 ns               | 24.3 ns                | 89.1 ns      |
| **nfx::string::isAllDigits**        | **2.5 ns**  | 19.6 ns     | 21.9 ns           | 24.4 ns               | 24.4 ns                | 45.3 ns      |

---

_Benchmarks executed on November 30, 2025_
