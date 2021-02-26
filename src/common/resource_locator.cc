#include "common/resource_locator.h"

#include <iostream>

ResourceLocator::ResourceLocator():
	mPathPrefix({ ".", "/usr/share/udpgame"})
{
}

const std::vector<std::string>& ResourceLocator::pathPrefix()
{
	return mPathPrefix;
}

void ResourceLocator::print()
{
	std::cout << mPathPrefix[0] << ", " << mPathPrefix[1] << std::endl;
}
