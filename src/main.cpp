#include <QCoreApplication>

#include <iostream>
#include <print>

#include "includes/rz_options.h"
#include "includes/rz_qt-aes.h"
#include "includes/rz_snippets.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool oknok{false};
    std::string msg{""};
    auto sptr_structFiles = std::make_shared<rz_snippets::fileStruct>();

    rz_options::check_options(argc, argv, sptr_structFiles);

    std::tie(oknok, msg) = rz_snippets::existFile(sptr_structFiles->srcFile);
    if (!oknok) {
        std::cerr << msg << std::endl;
        return EXIT_FAILURE;
    }

    (sptr_structFiles->srcFile.ends_with(".aes")) ? sptr_structFiles->doDecrypt = true
                                                  : sptr_structFiles->doEncrypt = true;

    if (sptr_structFiles->doEncrypt) {
        if (sptr_structFiles->srcFile.ends_with(sptr_structFiles->encExtension)) {
            std::cerr << "file is allready encrypted" << std::endl;
            return EXIT_SUCCESS;
        }
        if (sptr_structFiles->targetFile.empty()) {
            sptr_structFiles->targetFile = sptr_structFiles->srcFile
                                           + sptr_structFiles->encExtension;
        } else if (!sptr_structFiles->targetFile.ends_with(sptr_structFiles->encExtension)) {
            sptr_structFiles->targetFile.append(sptr_structFiles->encExtension);
        }
        rz_qt_aes::encryptFile(sptr_structFiles);
    }

    if (sptr_structFiles->doDecrypt) {
        if (!sptr_structFiles->srcFile.ends_with(sptr_structFiles->encExtension)) {
            std::cerr << "sourcefile is not encrypted" << std::endl;
            return EXIT_SUCCESS;
        }
        if (sptr_structFiles->targetFile.empty()) {
            sptr_structFiles->targetFile = rz_snippets::removeFileExtension(
                sptr_structFiles->srcFile);
        } else if (sptr_structFiles->targetFile.ends_with(sptr_structFiles->encExtension)) {
            sptr_structFiles->targetFile = rz_snippets::removeFileExtension(
                sptr_structFiles->targetFile);
        }
        rz_qt_aes::decryptFile(sptr_structFiles);
    }

    std::println("Source: {} - Target: {}", sptr_structFiles->srcFile, sptr_structFiles->targetFile);

    return EXIT_SUCCESS;
}
