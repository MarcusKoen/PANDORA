#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#pragma comment(lib, "advapi32.lib")

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
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);

    std::string hash = sha256HashFile(path);
    std::string expectedHash = "YOUR_KNOWN_SHA256_HASH_HERE"; // Replace with the real one

    std::cout << "Current hash:  " << hash << std::endl;
    std::cout << "Expected hash: " << expectedHash << std::endl;

    if (hash != expectedHash) {
        std::cout << "WARNING: Executable has been modified!" << std::endl;
        return 1;
    } else {
        std::cout << "Executable verified." << std::endl;
    }

    // Continue with normal program
    return 0;
}
