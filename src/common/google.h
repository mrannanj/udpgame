// from http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

#define DISALLOW_COPY_AND_ASSIGN(TypeName)      \
  TypeName(const TypeName&) = delete;           \
  TypeName& operator=(const TypeName&) = delete

