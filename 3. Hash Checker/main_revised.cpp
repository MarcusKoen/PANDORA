#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#pragma comment(lib, "advapi32.lib")

// Function to calculate SHA-256 hash of a file
std::string sha256HashFile(const std::string& filePath) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE buffer[4096];
    DWORD bytesRead;
    std::ifstream file(filePath, std::ios::binary);
    std::string hashStr;

    if (!file.is_open()) return "";

    if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        return "";

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return "";
    }

    while (file.read(reinterpret_cast<char*>(buffer), sizeof(buffer)) || (bytesRead = file.gcount())) {
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

int main() {
    // Get the path to the currently running executable
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);

    // Calculate its SHA-256 hash
    std::string currentHash = sha256HashFile(path);

    // Replace this with your actual known good hash
    std::string expectedHash = "PUT_YOUR_KNOWN_HASH_HERE";

    std::cout << "Checking executable integrity..." << std::endl;
    std::cout << "Current hash:  " << currentHash << std::endl;
    std::cout << "Expected hash: " << expectedHash << std::endl;

    if (currentHash != expectedHash) {
        std::cout << "\n❌ WARNING: This executable has been modified or corrupted!\n";
        return 1;
    }

    std::cout << "\n✅ Executable verified successfully.\n";

    std::string input;
    while (true) {
        std::cout << "\nEnter a message to print (or 'y' to exit): ";
        std::getline(std::cin, input);

        if (input == "y" || input == "Y") {
            std::cout << "Exiting program.\n";
            break;
        }

        std::cout << "You said: " << input << std::endl;
    }

    return 0;
}
