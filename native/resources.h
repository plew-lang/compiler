#ifndef PLEW_RESOURCES_H
#define PLEW_RESOURCES_H
#include <cstddef>
#include <cstdint>

extern "C" {
uint64_t plew_embedded_source_count();
const char *plew_embedded_source_path(uint64_t index);
const char *plew_embedded_source_text(uint64_t index);
const unsigned char *plew_embedded_runtime_data();
size_t plew_embedded_runtime_size();
const char *plew_distribution_version();
const char *plew_distribution_cpu();
const char *plew_distribution_minimum_macos();
const char *plew_distribution_licenses();
}
#endif
