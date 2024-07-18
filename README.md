# StringExtractor

**StringExtractor** is a .NET-based tool for extracting information from executable (.exe) files. This program allows you to analyze Portable Executable (PE) files and extract useful details such as the file name, file size, MD5 hash, and certain PE file details like image size and timestamp.

## Features

- **String Extraction**: Extracts and saves the following information into a text file:
  - File Name
  - File Size in bytes
  - MD5 Hash of the file
  - Image Size (if available)
  - Compilation Timestamp (if available)

## How It Works

1. **Drag and Drop**: Drag and drop an .exe file onto the `StringExtractor` executable.
2. **Information Extraction**: The program reads the PE file, calculates the MD5 hash, and gathers the requested information.
3. **Output**: Extracted information is saved to a text file with the suffix `result.txt`.

## Requirements

- .NET Framework 4.7.2
- [PeNet](https://github.com/pdn/PeNet) for PE file analysis

## Usage

1. **Build**: Compile the project using an environment compatible with .NET Framework 4.7.2.
2. **Run**: Drag an .exe file onto `StringExtractor.exe` to extract information.

## Example Usage

Run `StringExtractor.exe` and drag an .exe file onto it. The program will generate an output file with the extracted information. For example:

File Name: MyApp.exe
File Size: 123456 bytes
MD5: abcdef1234567890abcdef1234567890
PcaSvc: 0x123456
DPS: !2024/07/18:15:30:00


## Notes

- Ensure that `PeNet.dll` is present in the same directory as `StringExtractor.exe` or in the specified project path.
- If you encounter errors related to `PeNet.dll`, check that all dependencies are properly installed and accessible.

## Contributing

If you wish to contribute to this project, please fork the repository and submit a pull request with your changes. Make sure to follow the contribution guidelines.

