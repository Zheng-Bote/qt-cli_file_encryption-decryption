#pragma once

#include <iostream>
#include <memory>
#include <print>
#include <string>

#include "cxxopts.hpp"
#include "dotenv.h"
#include "rz_config.h"
#include "rz_snippets.h"

namespace rz_options {

void check_options(const int argc,
                   char *argv[],
                   std::shared_ptr<rz_snippets::fileStruct> sptr_structFiles)
{
    std::string prog = PROG_NAME;
    std::string source{""}, target{""};

    cxxopts::Options options(PROG_EXEC_NAME, PROG_DESCRIPTION);

    options.set_width(120).add_options()("s,source",
                                         "<path/to/sourcefile> to en-/de-crypt. Mandatory: -s | -d",
                                         cxxopts::value<std::string>())(
        "t,target", "target <path/to/outputfile>. Optional: -t | -d", cxxopts::value<std::string>())(
        "p,pwd",
        "name of password env variable. Mandatory: -p | -d",
        cxxopts::value<std::string>())("d,dotenv",
                                       "<path/to/dotenv> file. Mandatory: -s | -p | -d",
                                       cxxopts::value<std::string>())("h, help", "Print help");

    auto result = options.parse(argc, argv);

    // if (argc <= 1 || result.count("help"))

    if (result.count("help")) {
        std::println("{}", options.help());
        std::println("{} v{} {}", PROG_NAME, PROG_VERSION, PROG_HOMEPAGE);
        exit(EXIT_SUCCESS);
    }

    if (result.count("dotenv")) {
        bool oknok{false};
        std::string msg{""};
        std::tie(oknok, msg) = rz_snippets::existFile(result["dotenv"].as<std::string>());
        if (!oknok) {
            std::cerr << "\n \033[0;31m dotenv " << msg << std::endl;
            exit(EXIT_FAILURE);
        } else {
            std::string dotenvFile = result["dotenv"].as<std::string>();
            dotenv::init(dotenvFile.c_str());

            sptr_structFiles->srcFile = std::getenv("SOURCE_FILE");
            sptr_structFiles->targetFile = std::getenv("TARGET_FILE");
            sptr_structFiles->pwd = std::getenv("PWD");
        }
    }

    if (result.count("source")) {
        sptr_structFiles->srcFile = result["source"].as<std::string>();
    } else if (sptr_structFiles->srcFile.empty()) {
        std::cerr << "\n \033[0;31m missing source argument\n" << std::endl;
        std::println("\x1B[39m {}", options.help());
        std::println("{} v{} {}", PROG_NAME, PROG_VERSION, PROG_HOMEPAGE);
        exit(EXIT_FAILURE);
    }

    if (result.count("target")) {
        sptr_structFiles->targetFile = result["target"].as<std::string>();
    }

    if (!result.count("pwd") && !result.count("dotenv")) {
        std::cerr << "\n \033[0;31m missing pwd or dotenv argument\n" << std::endl;
        std::println("\x1B[39m {}", options.help());
        std::println("{} v{} {}", PROG_NAME, PROG_VERSION, PROG_HOMEPAGE);
        exit(EXIT_FAILURE);
    } else if (result.count("pwd")) {
        sptr_structFiles->pwd = std::getenv(result["pwd"].as<std::string>().c_str());
    }
}
}; // namespace rz_options
