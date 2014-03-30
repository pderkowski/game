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
    executablePath = initialPath;
    basePath = executablePath.parent_path().parent_path();
    binariesPath = basePath/"bin";
    resourcesPath = basePath/"rsc";
}

fs::path Paths::getExecutablePath() {
    return executablePath;
}

fs::path Paths::getBasePath() {
    return basePath;
}

fs::path Paths::getBinariesPath() {
    return binariesPath;
}

fs::path Paths::getResourcesPath() {
    return resourcesPath;
}

fs::path Paths::getResourcePath(const std::string& resource) {
    return getResourcesPath()/resource;
}
