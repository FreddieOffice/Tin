#ifndef TIN_PCH_HPP
#define TIN_PCH_HPP

// Platform
#include <windows.h>

// General
#include <utility>

// Data types, containers
#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <array>
#include <vector>
#include <string>

// Streams and I/O
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

// Functional and logic
#include <algorithm>
#include <optional>

// Memory
#include <mutex>
#include <memory>

// Time, system
#include <chrono>
#include <ctime>
#include <filesystem>

// Vendor
#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#endif