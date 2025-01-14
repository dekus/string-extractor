
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h> 
#include <LIEF/PE.hpp>
#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <ctime>
#include <vector>
#include <memory>
#include <cstdio> 
#include <windows.h>

std::string CalculateMD5(const std::vector<uint8_t>& data) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_md5();
    unsigned char md5Hash[EVP_MAX_MD_SIZE];
    unsigned int md5Len;

    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, data.data(), data.size());
    EVP_DigestFinal_ex(mdctx, md5Hash, &md5Len);
    EVP_MD_CTX_free(mdctx);

    std::stringstream md5Stream;
    for (unsigned int i = 0; i < md5Len; i++) {
        md5Stream << std::hex << std::setw(2) << std::setfill('0') << (int)md5Hash[i];
    }

    return md5Stream.str();
}

void ExtractStrings(const std::string& peFilePath) {
    std::string fileName = peFilePath.substr(peFilePath.find_last_of("/\\") + 1);

    std::cout << "File Name: " << fileName << std::endl;

    std::ifstream peFile(peFilePath, std::ios::binary | std::ios::ate);
    if (!peFile.is_open()) {
        std::cerr << "Failed to open PE file." << std::endl;
        return;
    }

    std::streamsize fileSize = peFile.tellg();
    std::cout << "File Size: " << fileSize << " bytes" << std::endl;

    peFile.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(fileSize);
    if (!peFile.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        std::cerr << "Failed to read PE file." << std::endl;
        return;
    }

    std::string md5String = CalculateMD5(buffer);
    std::cout << "MD5: " << md5String << std::endl;

    try {
        FILE* nullFile;
        if (freopen_s(&nullFile, "nul", "w", stderr) != 0) { 
            std::cerr << "Failed to redirect stderr." << std::endl;
            return;
        }

        std::unique_ptr<LIEF::PE::Binary> peFileData = LIEF::PE::Parser::parse(peFilePath);
        if (peFileData == nullptr) {
            std::cerr << "Failed to parse PE file." << std::endl;
            return;
        }

        if (freopen_s(&nullFile, "CON", "w", stderr) != 0) { 
            std::cerr << "Failed to restore stderr." << std::endl;
            return;
        }

        std::cout << "PcaSvc: 0x" << std::hex << peFileData->optional_header().sizeof_image() << std::endl;

        uint32_t timestamp = peFileData->header().time_date_stamp();
        std::time_t timestampT = timestamp;
        std::tm timestampTm;
        gmtime_s(&timestampTm, &timestampT);
        char timestampStr[20];
        std::strftime(timestampStr, sizeof(timestampStr), "%Y/%m/%d:%H:%M:%S", &timestampTm);
        std::cout << "DPS: !" << timestampStr << std::endl;
    }
    catch (const std::exception& e) {

        FILE* nullFile;
        if (freopen_s(&nullFile, "CON", "w", stderr) != 0) { 
            std::cerr << "Failed to restore stderr." << std::endl;
        }

        std::cerr << "Error parsing PE file: " << e.what() << std::endl;
    }

    std::cout << "Strings extracted successfully!" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string peFile = argv[1];
        ExtractStrings(peFile);
    }
    else {
        std::cout << "Drag and drop a .exe file onto this application to extract its strings." << std::endl;
    }

    return 0;
}