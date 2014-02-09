#include "common/resource_locator.h"

#include <iostream>
#include <sstream>
#include <algorithm>

//mPathPrefix({".", "/usr/share/udpgame"})

ResourceLocator::ResourceLocator():
  mPathPrefix()
{
  mPathPrefix.push_back(".");
}

std::string ResourceLocator::getPath(const std::string& s) {
  std::stringstream p;
  p << mPathPrefix[0] << "/" << s;
  std::string r(p.str());
#ifdef _WIN32
  for (size_t i = 0; i < r.size(); ++i)
    if (r[i] == '/') r[i] = '\\';
#endif
  return r;
}

const std::vector<std::string>& ResourceLocator::pathPrefix() {
  return mPathPrefix;
}
