#ifndef TIN_PCH_HPP
#define TIN_PCH_HPP

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

// Platform
#include "Tin/Core/Platform.hpp"

#ifdef TIN_PLATFORM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #include <windows.h>
#endif

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