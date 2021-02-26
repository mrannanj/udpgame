#include "common/resource_locator.h"

#include <iostream>
#include <sstream>
#include <unistd.h>

ResourceLocator::ResourceLocator():
	mPathPrefix({ ".", "/usr/share/udpgame"})
{
}

std::string ResourceLocator::findResource(const std::string& file) const
{
	for (const std::string& prefix : mPathPrefix) {
		std::stringstream ret_path;
		ret_path << prefix << "/" << file;
		if (access(ret_path.str().c_str(), F_OK | R_OK) == 0)
			return ret_path.str();
	}
	std::cerr << "Failed to find " << file << std::endl;
	exit(EXIT_FAILURE);
}
