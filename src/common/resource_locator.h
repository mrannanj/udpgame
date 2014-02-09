#pragma once

#include <string>
#include <vector>

class ResourceLocator {
public:
  ResourceLocator();

  std::string getPath(const std::string&);
  const std::vector<std::string>& pathPrefix();
private:
  std::vector<std::string> mPathPrefix;
};
