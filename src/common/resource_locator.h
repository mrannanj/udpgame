#pragma once

#include <string>
#include <vector>

class ResourceLocator {
public:
  ResourceLocator();

  void print();
  const std::vector<std::string>& pathPrefix();
private:
  std::vector<std::string> mPathPrefix;
};
