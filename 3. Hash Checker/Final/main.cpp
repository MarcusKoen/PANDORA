#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>

#pragma comment(lib, "advapi32.lib")

// Convert a string to lowercase for case-insensitive comparison
std::string toLower(const std::string& input) {
    std::string output = input;
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);
    return output;
}

// Compute SHA-256 hash of the given file
std::string sha256HashFile(const std::string& filePath) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE buffer[4096];
    std::ifstream file(filePath, std::ios::binary);
    std::string hashStr;

    if (!file.is_open()) return "";

    if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        return "";

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return "";
    }

    while (file.read(reinterpret_cast<char*>(buffer), sizeof(buffer)) || file.gcount()) {
        if (!CryptHashData(hHash, buffer, static_cast<DWORD>(file.gcount()), 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return "";
        }
    }

    BYTE hash[32];
    DWORD hashLen = sizeof(hash);
    if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
        std::ostringstream oss;
        for (DWORD i = 0; i < hashLen; ++i)
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        hashStr = oss.str();
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    return hashStr;
}

// Read the expected hash from the .sha256 file
std::string readExpectedHash(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string hash;
    std::getline(file, hash);
    return hash;
}

int main() {
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);
    std::string exePath = path;
    std::string hashFilePath = exePath + ".sha256";

    std::string actualHash = sha256HashFile(exePath);
    std::string expectedHash = readExpectedHash(hashFilePath);

    std::cout << "Current hash:  " << actualHash << "\n";
    std::cout << "Expected hash: " << expectedHash << "\n";

    if (toLower(actualHash) != toLower(expectedHash)) {
        std::cout << "ERROR: Executable has been modified!" << std::endl;
        return 1;
    }

    std::cout << "OK: Executable is verified.\n" << std::endl;

 int userCode = 0;
    while (true) {
        std::cout << "Enter the code: ";
        std::cin >> userCode;

        if (userCode == 80085) {
            std::cout << "Congrats!" << std::endl;

            char choice;
            while (true) {
                std::cout << "Exit? (y/Y to exit): ";
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    std::cout << "Exiting." << std::endl;
  return 0;
                }
            }
        } else {
            std::cout << "Wrong code!" << std::endl;
        }
    }


}
