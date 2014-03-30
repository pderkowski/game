/* Copyright 2014 <Piotr Derkowski> */

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
    boost::filesystem::path executablePath;
    boost::filesystem::path basePath;
    boost::filesystem::path binariesPath;
    boost::filesystem::path resourcesPath;
};
