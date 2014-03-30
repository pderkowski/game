/* Copyright 2014 <Piotr Derkowski> */

#ifndef PATHS_H_
#define PATHS_H_

#include <string>
#include "boost/filesystem.hpp"

class Paths {
public:
    explicit Paths(const std::string& relativePathToExec);
    boost::filesystem::path getExecutablePath();
    boost::filesystem::path getBasePath();
    boost::filesystem::path getBinariesPath();
    boost::filesystem::path getResourcesPath();
    boost::filesystem::path getResourcePath(const std::string& resource);

private:
    boost::filesystem::path executablePath_;
    boost::filesystem::path basePath_;
    boost::filesystem::path binariesPath_;
    boost::filesystem::path resourcesPath_;
};

#endif  // PATHS_H_
