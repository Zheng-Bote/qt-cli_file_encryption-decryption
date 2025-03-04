#pragma once

#include <QCoreApplication>
#include <QCryptographicHash>
#include <fstream>
#include <iostream>
#include <print>

#include "qaesencryption.h"
#include "rz_snippets.h"

namespace rz_qt_aes {
QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
QString iv("0x0c2ad4a4acb9f023");
bool oknok{false};
std::string msg{""};

std::tuple<bool, std::string> encrypt_data(const std::string &sourceFile,
                                           const std::string &targetFile,
                                           const std::string &pwd,
                                           const QByteArray &buffer)
{
    QString key = QString::fromStdString(pwd);

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    // Encrypt the data
    QByteArray encodeText = encryption.encode(buffer, hashKey, hashIV);

    std::ofstream file(targetFile, std::ios::binary | std::ios::app);
    if (!file) {
        return std::make_tuple(false, "encrypt_data: Error opening file: " + sourceFile);
    }

    // Write the binary data to the file
    file.write(encodeText.data(), encodeText.size());

    // Check for write errors
    if (!file) {
        return std::make_tuple(false, "encrypt_data: Error writing data to the file: " + targetFile);
    }
    file.close();

    return std::make_tuple(true, "encrypt_data: OK");
}

std::tuple<bool, std::string> decrypt_data(const std::string &sourceFile,
                                           const std::string &targetFile,
                                           const std::string &pwd,
                                           const QByteArray &buffer)
{
    QString key = QString::fromStdString(pwd);

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    // Decrypt the data
    QByteArray decodeText = encryption.decode(buffer, hashKey, hashIV);
    //std::cout << "Decoded data: " << decodeText.toStdString() << std::endl;

    std::ofstream file(targetFile, std::ios::binary | std::ios::app);
    if (!file) {
        return std::make_tuple(false, "decrypt_data: Error opening file: " + sourceFile);
    }

    // Write the binary data to the file
    file.write(decodeText.data(), decodeText.size());

    // Check for write errors
    if (!file) {
        return std::make_tuple(false, "decrypt_data: Error writing data to the file: " + targetFile);
    }
    file.close();

    return std::make_tuple(true, "decrypt_data: OK");
}

std::tuple<bool, std::string> readBinaryFileInChunks(const std::string &sourceFile,
                                                     const std::string &targetFile,
                                                     const std::string &pwd,
                                                     bool do_encrypt)
{
    //std::size_t chunkSize = 1024 * 1024; // 1 MB chunk size
    std::size_t chunkSize = 2048 * 2048; // 4 MB chunk size
    //std::size_t chunkSize = 4096 * 4096; // 16 MB chunk size

    std::ifstream file(sourceFile, std::ios::binary);

    if (!file) {
        return std::make_tuple(false, "readBinaryFileInChunks: Error opening file: " + sourceFile);
    }

    int sourceFileSize = std::filesystem::file_size(sourceFile);
    int processedSize{0};
    int toProcessSize = sourceFileSize;

    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(chunkSize); // Buffer to hold chunks

    while (file) {
        // Read a chunk of the file into the buffer
        file.read(buffer.data(), chunkSize);
        size_t bytesRead = file.gcount(); // Number of bytes read

        //std::cout << "Read " << bytesRead << " bytes" << std::endl;
        processedSize += bytesRead;

        // Create a QByteArray from the buffer
        QByteArray chunkData(buffer.data(), bytesRead);

        if (do_encrypt) {
            //std::cout << "Encrypting..." << std::endl;
            std::println("Encryption {} of {} - {}",
                         processedSize,
                         sourceFileSize,
                         toProcessSize - processedSize);
            std::tie(oknok, msg) = encrypt_data(sourceFile, targetFile, pwd, chunkData);
        } else {
            std::cout << "Decrypting..." << std::endl;
            std::tie(oknok, msg) = decrypt_data(sourceFile, targetFile, pwd, chunkData);
        }
    }

    file.close();
    return std::make_tuple(oknok, msg);
}

std::tuple<bool, std::string> encryptFile(std::shared_ptr<rz_snippets::fileStruct> sptr_structFiles)
{
    std::tie(oknok, msg) = readBinaryFileInChunks(sptr_structFiles->srcFile,
                                                  sptr_structFiles->targetFile,
                                                  sptr_structFiles->pwd,
                                                  true);
    if (oknok) {
        return std::make_tuple(true, "encryptFile: OK");
    } else {
        return std::make_tuple(false, "encryptFile: NOK");
    }
}

std::tuple<bool, std::string> decryptFile(std::shared_ptr<rz_snippets::fileStruct> sptr_structFiles)
{
    std::tie(oknok, msg) = readBinaryFileInChunks(sptr_structFiles->srcFile,
                                                  sptr_structFiles->targetFile,
                                                  sptr_structFiles->pwd,
                                                  false);
    if (oknok) {
        return std::make_tuple(true, "decryptFile: OK");
    } else {
        return std::make_tuple(false, "decryptFile: NOK");
    }
}

}; // namespace rz_qt_aes
