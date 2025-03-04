#pragma once

#include <iostream>
#include <memory>
#include <print>
#include <string>

#include "cxxopts.hpp"
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
                                         "mandatory: sourcefile to en-/de-crypt",
                                         cxxopts::value<std::string>())(
        "t,target",
        "optional: target outputfile",
        cxxopts::value<std::string>())("p,pwd",
                                       "mandatory: password",
                                       cxxopts::value<std::string>())("h, help", "Print help");

    auto result = options.parse(argc, argv);

    // if (argc <= 1 || result.count("help"))

    if (result.count("help")) {
        std::println("{}", options.help());
        std::println("{} v{} {}", PROG_NAME, PROG_VERSION, PROG_HOMEPAGE);
        exit(EXIT_SUCCESS);
    }

    if (result.count("source")) {
        sptr_structFiles->srcFile = result["source"].as<std::string>();
    } else {
        std::cerr << "\n \033[0;31m missing source argument\n" << std::endl;
        std::println("\x1B[39m {}", options.help());
        std::println("{} v{} {}", PROG_NAME, PROG_VERSION, PROG_HOMEPAGE);
        exit(EXIT_FAILURE);
    }
    if (result.count("target")) {
        sptr_structFiles->targetFile = result["target"].as<std::string>();
    }
    if (result.count("pwd")) {
        sptr_structFiles->pwd = result["pwd"].as<std::string>();
    } else {
        std::cerr << "\n \033[0;31m missing pwd argument\n" << std::endl;
        std::println("\x1B[39m {}", options.help());
        std::println("{} v{} {}", PROG_NAME, PROG_VERSION, PROG_HOMEPAGE);
        exit(EXIT_FAILURE);
    }
}
}; // namespace rz_options
