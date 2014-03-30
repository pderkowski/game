/* Copyright 2014 <Piotr Derkowski> */

#include <unistd.h>
#include <cstdlib>
#include <string>
#include "boost/filesystem.hpp"
#include "Paths.hpp"

namespace fs = boost::filesystem;

Paths::Paths(const std::string& relativePathToExec) {
    fs::path initialPath(fs::initial_path<fs::path>());
    initialPath = fs::canonical(fs::system_complete(fs::path(relativePathToExec)));
    executablePath_ = initialPath;
    basePath_ = executablePath_.parent_path().parent_path();
    binariesPath_ = basePath_/"bin";
    resourcesPath_ = basePath_/"rsc";
}

fs::path Paths::getExecutablePath() {
    return executablePath_;
}

fs::path Paths::getBasePath() {
    return basePath_;
}

fs::path Paths::getBinariesPath() {
    return binariesPath_;
}

fs::path Paths::getResourcesPath() {
    return resourcesPath_;
}

fs::path Paths::getResourcePath(const std::string& resource) {
    return getResourcesPath()/resource;
}
