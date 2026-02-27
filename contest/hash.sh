# Don't type comments nor #include "..."
# Do type asserts

# hash of first 5 lines
# head -n 5 a.cpp | bash hash.sh
# head -n 5 a.cpp | tr -d '[:space:]' | md5sum | cut -c-6
tr -d '[:space:]' | md5sum | cut -c-6
