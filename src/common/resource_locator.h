#pragma once

#include <string>
#include <vector>

class ResourceLocator {
public:
	ResourceLocator();

	std::string findResource(const std::string&) const;
private:
	std::vector<std::string> mPathPrefix;
};
