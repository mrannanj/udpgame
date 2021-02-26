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
