# StringExtractor (C++ Version)

**StringExtractor** is a C++ tool for extracting information from executable (.exe) files. This program allows you to analyze Portable Executable (PE) files and extract useful details such as the file name, file size, MD5 hash, and certain PE file details like image size and timestamp.

## Features

- **String Extraction**: Extracts and saves the following information into a text file:
  - File Name
  - File Size in bytes
  - MD5 Hash of the file
  - Image Size (if available)
  - Compilation Timestamp (if available)

## How It Works

1. **Command Line Usage**: Pass the path to an .exe file as a command-line argument to the `StringExtractor` executable.
2. **Information Extraction**: The program reads the PE file, calculates the MD5 hash, and gathers the requested information using the LIEF library for PE file analysis.
3. **Output**: Extracted information in command prompt.

## Requirements

- C++17 or later
- [LIEF](https://github.com/lief-project/LIEF) for PE file analysis
- [OpenSSL](https://www.openssl.org/) for MD5 hash calculation
- [spdlog](https://github.com/gabime/spdlog) for logging (optional)
- [fmt](https://github.com/fmtlib/fmt) for string formatting

## Usage

1. **Build**: Compile the project using a C++ compiler (e.g., MSVC, GCC, or Clang) with the necessary libraries linked.
2. **Run**: Execute the program from the command line, passing the path to an .exe file as an argument.

### Example Usage

Run the following command in the terminal:

```bash
StringExtractor.exe MyApp.exe
