/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 */

#pragma once

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "common/log.h"

namespace sm {
namespace common {

// file type: file or directory
enum FileType { TYPE_FILE, TYPE_DIR };

/**
 * @brief Get file content as string.
 * @param file_name The name of the file to read content.
 * @param content The file content.
 * @return If the action is successful.
 */
bool GetContent(const std::string &file_name, std::string *content);

/**
 * @brief Get absolute path by concatenating prefix and relative_path.
 * @return The absolute path.
 */
std::string GetAbsolutePath(const std::string &prefix,
                            const std::string &relative_path);

/**
 * @brief Check if the path exists.
 * @param path a file name, such as /a/b/c.txt
 * @return If the path exists.
 */
bool PathExists(const std::string &path);

bool PathIsAbsolute(const std::string &path);

/**
 * @brief Check if the directory specified by directory_path exists
 *        and is indeed a directory.
 * @param directory_path Directory path.
 * @return If the directory specified by directory_path exists
 *         and is indeed a directory.
 */
bool DirectoryExists(const std::string &directory_path);

/**
 * @brief Expand path pattern to matched paths.
 * @param pattern Path pattern, which may contain wildcards [?*].
 * @return Matched path list.
 */
std::vector<std::string> Glob(const std::string &pattern);

/**
 * @brief Copy a file.
 * @param from The file path to copy from.
 * @param to The file path to copy to.
 * @return If the action is successful.
 */
bool CopyFile(const std::string &from, const std::string &to);

/**
 * @brief Copy a directory.
 * @param from The path to copy from.
 * @param to The path to copy to.
 * @return If the action is successful.
 */
bool CopyDir(const std::string &from, const std::string &to);

/**
 * @brief Copy a file or directory.
 * @param from The path to copy from.
 * @param to The path to copy to.
 * @return If the action is successful.
 */
bool Copy(const std::string &from, const std::string &to);

/**
 * @brief Check if a specified directory specified by directory_path exists.
 *        If not, recursively create the directory (and its parents).
 * @param directory_path Directory path.
 * @return If the directory does exist or its creation is successful.
 */
bool EnsureDirectory(const std::string &directory_path);

/**
 * @brief Remove all the files under a specified directory. Note that
 *        sub-directories are NOT affected.
 * @param directory_path Directory path.
 * @return If the action is successful.
 */
bool RemoveAllFiles(const std::string &directory_path);

/**
 * @brief List sub-paths.
 * @param directory_path Directory path.
 * @param d_type Sub-path type, DT_DIR for directory, or DT_REG for file.
 * @return A vector of sub-paths, without the directory_path prefix.
 */
std::vector<std::string> ListSubPaths(const std::string &directory_path,
                                      const unsigned char d_type = DT_DIR);

/**
 * @brief Find path with pattern
 * @param base_path search root
 * @param patt pattern to compare with entry->d_name for filter
 * @param d_type entry type for filter
 * @param recursive search directory recursively
 * @param result_list a vector reference for storing the search result
 * @return the result count
 */
size_t FindPathByPattern(const std::string &base_path, const std::string &patt,
                         const unsigned char d_type, const bool recursive,
                         std::vector<std::string> *result_list);

/**
 * @brief get directory name of path
 * @param path
 * @return dirname of path
 */
std::string GetDirName(const std::string &path);

std::string GetFileName(const std::string &path,
                        const bool remove_extension = false);

/**
 * @brief get file path, judgement priority:
 * 1. absolute path.
 * 2. relative path starts with '.'.
 * 3. add environment variable prefix before the path.
 * 4. a common relative path.
 *
 * @param path input file path string.
 * @param env_var environment var string.
 * @param file_path the output file path.
 *
 * @return if no valid path found, return false.
 */
bool GetFilePathWithEnv(const std::string &path, const std::string &env_var,
                        std::string *file_path);

std::string GetCurrentPath();

// delete file including file or directory
bool DeleteFile(const std::string &filename);

bool GetType(const std::string &filename, FileType *type);

bool CreateDir(const std::string &dir);

}  // namespace common
}  // namespace sm
