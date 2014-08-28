/* Copyright 2014 <Piotr Derkowski> */

#ifndef GLOBAL_PATHS_HPP_
#define GLOBAL_PATHS_HPP_

#include <string>
#include "boost/filesystem.hpp"


namespace global {


class Paths {
public:
    static void initialize(const std::string& relativePathToExec);

    static boost::filesystem::path getExecutablePath();
    static boost::filesystem::path getBasePath();
    static boost::filesystem::path getBinariesPath();
    static boost::filesystem::path getResourcesPath();
    static boost::filesystem::path getResourcePath(const std::string& resource);

private:
    Paths() = delete;

    static boost::filesystem::path executablePath_;
    static boost::filesystem::path basePath_;
    static boost::filesystem::path binariesPath_;
    static boost::filesystem::path resourcesPath_;
};


}  // namespace global

#endif  // GLOBAL_PATHS_HPP_


