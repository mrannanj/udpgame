
// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
// source: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

