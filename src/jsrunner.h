#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define JSRUNNER_EXPORT __declspec(dllexport)
#else
  #define JSRUNNER_EXPORT
#endif

JSRUNNER_EXPORT void jsrunner();
JSRUNNER_EXPORT void jsrunner_print_vector(const std::vector<std::string> &strings);
