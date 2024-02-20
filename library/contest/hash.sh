# Don't type comments nor #include "..."
# Do type asserts

# cat a.cpp | bash hash.sh
# cat a.cpp | tr -d '[:space:]' | md5sum | cut -c-6
tr -d '[:space:]' | md5sum | cut -c-6
