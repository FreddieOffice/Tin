#ifndef TIN_PCH_HPP
#define TIN_PCH_HPP

// Platform
#include "Tin/Core/Platform.hpp"

#ifdef TIN_PLATFORM_WINDOWS
    #include <windows.h>
#endif

// General
#include <utility>

// Data types, containers
#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <array>
#include <vector>
#include <string>
#include <tuple>

// Streams and I/O
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

// Functional and logic
#include <algorithm>

// Memory
#include <mutex>
#include <memory>

// Time, system
#include <chrono>
#include <ctime>
#include <filesystem>

// Vendor
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#endif