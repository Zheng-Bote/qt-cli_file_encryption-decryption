<div id="top" align="center">
<h1>qt-cli_file_encryption-decryption</h1>

<h4>File encryption and decryption, shell/commandline</h4>
<h6>for Linux, MacOS, Windows</h6>

[Report Issue](https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption/issues) [Request Feature](https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption/pulls)

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Zheng-Bote/qt-cli_file_encryption-decryption?logo=GitHub)](https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption/releases)

</div>

<hr>

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

**Table of Contents**

- [Description](#description)
  - [Test / Performance](#test--performance)
    - [Features](#features)
  - [Status](#status)
    - [Documentation](#documentation)
  - [Encryption](#encryption)
  - [Decryption](#decryption)
- [Installation](#installation)
  - [Linux](#linux)
  - [MacOS](#macos)
  - [Windows](#windows)
- [Development](#development)
  - [Dependencies](#dependencies)
    - [CMake](#cmake)
    - [QT](#qt)
    - [Qt-AES](#qt-aes)
  - [folder structure](#folder-structure)
- [Authors and License](#authors-and-license)
  - [MIT License](#mit-license)
  - [Authors](#authors)
    - [Code Contributors](#code-contributors)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

<hr>

# Description

![QT](https://img.shields.io/badge/Community-6-41CD52?logo=qt)
![CXX](https://img.shields.io/badge/C++-23-blue?logo=cplusplus)

Qt6 C++23 shell/commandline application to encrypt / decrypt the given file.

- Encryption: AES-256 CBC
- Password: SHA256, between 5 to 32 characters
- initialization vector: MD5

See folder `docs/img` for screenshots.

## Features

- [ ] i18n
- [x] OSS and license
- [x] works as designed
- [ ] no bugs

- [x] some more or less usefull Github Actions for GH-repo, GH-pages, GH-wiki, CI/CD-Pipelines
- [ ] Packagemanager
- [x] Buildsystem: CMake
- [x] Installation routine (no Adminstrator rights needed)
- [ ] portable application

- [x] runs on DOS/Windows
- [x] runs on MacOS
- [x] runs on Linux
- [ ] runs on iOS
- [ ] runs on Android
- [ ] runs on HarmonyOS

- [x] supports pipe operator or arguments

<p align="right">(<a href="#top">back to top</a>)</p>

# Status

![GitHub Created At](https://img.shields.io/github/created-at/Zheng-Bote/qt-cli_file_encryption-decryption)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Zheng-Bote/qt-cli_file_encryption-decryption?logo=GitHub)](https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption/releases)
![GitHub Release Date](https://img.shields.io/github/release-date/Zheng-Bote/qt-cli_file_encryption-decryption)
![Status](https://img.shields.io/badge/Status-stable-green)
![Status](https://img.shields.io/badge/Status-works_as_designed-green)

![GitHub Issues](https://img.shields.io/github/issues/Zheng-Bote/qt-cli_file_encryption-decryption)
![GitHub Pull Requests](https://img.shields.io/github/issues-pr/Zheng-Bote/qt-cli_file_encryption-decryption)

# Documentation

## Encryption

_under construction_

> \[!WARNING]
> don't loose your password. Decryption/Recovery without valid password is impossible!

## Decryption

_under construction_

## Test / Performance

**tested on**

- x86_64 Ubuntu 24.04.2 LTS
- Intel(R) Core(TM) i5-9600K CPU @ 3.70GHz with 6 cpu cores
- average SSD storage
- fallocate -l 1G test.img

**read / write binary mode of 1 GB file with a chunk size of 4 MB**
| type | val |
| ---- | --------- |
| real | 5m52,734s |
| user | 5m49,905s |
| sys | 0m2,391s |

**read / write binary mode of 1 GB file with a chunk size of 16 MB**
| type | val |
| ---- | --------- |
| real | 5m50,753s |
| user | 5m48,691s |
| sys | 0m2,049s |

=> so compiled chunk size is 4 MB to give better feedback about the process status.

<p align="right">(<a href="#top">back to top</a>)</p>

# Installation

## Linux

- make AppImage executable (eg. `chmod 755 file_encryption-decryption-x86_64.AppImage` )
- execute AppImage

## MacOS

- make DiskImage executable (eg. `chmod 755 file_encryption-decryption.dmg`)
- execute / double-click on the `.dmg` file. A window should appear showing the program you are installing and the Applications Folder.
- drag the program into the Applications Folder; macOS will automatically install the software for you.

## Windows

_under construction_

# Development

## Dependencies

> \[!NOTE]
> All licenses are therefore Open Source.

### CMake

CMake: A Powerful Software Build System

[![CMake](https://img.shields.io/badge/CMake-v3.23+-064F8C?logo=cmake)](https://github.com/conan-io/conan)
[![BSD-3 License](https://img.shields.io/badge/License-BSD_3-green.svg)](https://choosealicense.com/licenses/bsd-3-clause/)

### QT

> \[!NOTE]
> _QT6 - Community Edition_ >= 6.7

The Qt framework contains a comprehensive set of highly intuitive and modularized C++ library classes and is loaded with APIs to simplify your application development. Qt produces highly readable, easily maintainable and reusable code with high runtime performance and small footprint – and it's cross-platform.

[![QT](https://img.shields.io/badge/Community-for_Open_Source_Development-black?logo=qt)](https://www.qt.io/download-open-source)
[![LGPL](https://img.shields.io/badge/License-LGPL_v3-green.svg)](https://choosealicense.com/licenses/lgpl-3.0/) _see also:_[Obligations of the GPL and LGPL](https://www.qt.io/licensing/open-source-lgpl-obligations)

### Qt-AES

Small and portable AES encryption class for Qt. Native support for all key sizes - 128/192/256 bits - ECB, CBC, CFB and OFB modes for all key sizes partial AES-NI support

[![Matt Bricke](https://img.shields.io/badge/Github-bricke-black?logo=github)](https://github.com/bricke/Qt-AES)
[![UNLICENSE](https://img.shields.io/badge/License-Unlicense-green.svg)](https://github.com/bricke/Qt-AES?tab=Unlicense-1-ov-file)

<p align="right">(<a href="#top">back to top</a>)</p>

## folder structure

<!-- readme-tree start -->

```
.
├── .github
│   ├── actions
│   │   └── doctoc
│   │       ├── README.md
│   │       ├── action.yml
│   │       └── dist
│   │           ├── index.js
│   │           ├── index.js.map
│   │           ├── licenses.txt
│   │           └── sourcemap-register.js
│   └── workflows
│       ├── ghp-call_Readme.yml
│       ├── ghp-create_doctoc.yml
│       ├── ghp-markdown_index.yml
│       ├── repo-actions_docu.yml
│       ├── repo-call_Readme.yml
│       ├── repo-create_doctoc.yml_
│       ├── repo-create_doctoc_md.yml
│       └── repo-create_tree_readme.yml
├── .gitignore
├── LICENSE
├── README.md
├── src
│   ├── .gitignore
│   ├── CMakeLists.txt
│   ├── configure
│   │   ├── ClangTidy.cmake
│   │   ├── Doxygen.cmake
│   │   ├── extra_headers
│   │   └── rz_config.h.in
│   ├── includes
│   │   ├── cxxopts.hpp
│   │   ├── qaesencryption.cpp
│   │   ├── qaesencryption.h
│   │   ├── rz_config.h
│   │   ├── rz_options.h
│   │   ├── rz_qt-aes.h
│   │   └── rz_snippets.h
│   └── main.cpp
└── tree.bak

9 directories, 32 files
```

<!-- readme-tree end -->

<p align="right">(<a href="#top">back to top</a>)</p>

# Authors and License

## MIT License

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

Copyright (c) 2024 ZHENG Robert

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Authors

- [![Zheng Robert](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

### Code Contributors

![Contributors](https://img.shields.io/github/contributors/Zheng-Bote/qt-cli_file_encryption-decryption?color=dark-green)

[![Zheng Robert](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

<hr>

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>
