/*
 *  Copyright (C) 2004-2020 Savoir-faire Linux Inc.
 *
 *  Author: Alexandre Lision <alexandre.lision@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#pragma once

#include "noncopyable.h"

#include <string>
#include <vector>
#include <map>
#include <functional>

typedef struct gzFile_s *gzFile;

namespace jami {

/**
 * Archiver is used to generate/read encrypted archives
 */
namespace archiver {

using FileMatchPair = std::function<std::pair<bool,const std::string>(const std::string&)>;

/**
 * Create a protected archive containing a list of accounts
 * @param accountIDs The accounts to exports
 * @param filepath The filepath where to put the resulting archive
 * @param password The mandatory password to set on the archive
 * @returns 0 for OK, error code otherwise
 */
int exportAccounts(const std::vector<std::string>& accountIDs,
                   const std::string& filepath,
                   const std::string& password);

/**
 * Read a protected archive and add accounts found in it
 * Warning: this function must be called from a registered pjsip thread
 * @param archivePath The path to the archive file
 * @param password The password to read the archive
 * @returns 0 for OK, error code otherwise
 */
int importAccounts(const std::string& archivePath, const std::string& password);

/**
 * Compress a STL string using zlib with given compression level and return
 * the binary data.
 */
std::vector<uint8_t> compress(const std::string& str);

/**
 * Decompress an STL string using zlib and return the original data.
 */
std::vector<uint8_t> decompress(const std::vector<uint8_t>& dat);

/**
 * Compress string to a Gzip file
 */
void compressGzip(const std::string& str, const std::string& path);

/**
 * Decompress Gzip file to bytes
 */
std::vector<uint8_t> decompressGzip(const std::string& path);

/**
 * Open Gzip file (uses wide string version of gzopen on windows)
 */
gzFile openGzip(const std::string& path, const char *mode);

/**
 * @brief listArchiveContent
 * @param archivePath
 * @return list of relative file path names
 */
std::vector<std::string> listArchiveContent(const std::string& archivePath);

/**
 * @brief uncompressArchive Uncompresses an archive and puts the different files
 * in dir folder according to a FileMatchPair f
 * @param path
 * @param dir
 * @param f takes a file name relative path inside the archive like mysubfolder/myfile
 * and returns a pair (bool, new file name relative path)
 * Where the bool indicates if we should uncompress this file
 * and the new file name relative path puts the file in the directory dir under a different
 * relative path name like mynewsubfolder/myfile
 * @return void
 */
void uncompressArchive(const std::string& path, const std::string &dir, const FileMatchPair& f);

/**
 * @brief readFileFromArchive read a file from an archive without uncompressing
 * the whole archive
 * @param path archive path
 * @param fileRelativePathName file path relative path name in the archive
 * E.g: data/myfile.txt inside the archive
 * @return fileContent std::vector<uint8_t> that contains the file content
 */
std::vector<uint8_t> readFileFromArchive(const std::string &path,
                                 const std::string &fileRelativePathName);
}

} // namespace jami
