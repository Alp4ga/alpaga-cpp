/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:34:26
  * @Last Modified by:   Alpaga
  * @Last Modified time: 2020-02-28 10:34:26
*/

#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(_LINUX)
    #define SYSTEM_LINUX
    #define SHARED_LIB_EXT ".so"
#elif defined(__APPLE__)
    #define SYSTEM_DARWIN
    #define SHARED_LIB_EXT ".dylib"
#elif defined(_WIN32) || defined(_WIN64)
    #define SYSTEM_WINDOWS
    #define SHARED_LIB_EXT ".dll"
#else
    #error "Operating System not supported by Hidlo Loader"
#endif

#if defined(SYSTEM_LINUX) || defined(SYSTEM_DARWIN)
#include <dlfcn.h>
#elif defined(SYSTEM_WINDOWS)
#include <Windows.h>
#endif

#include <string>
#include <unordered_map>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
    class DynamicLoader;

#if defined(SYSTEM_WINDOWS)
	/*! @def DynamicHandler
	 * @brief Type of module loaded
	*/
    using DynamicHandler = HMODULE;
#else
    using DynamicHandler = void*;
#endif
}

/*! @class Alpaga::DynamicLoader
 * @brief Load shared cross plateforme library
 * 
*/
class Alpaga::DynamicLoader {
	public:
		/**
		* @brief Construct a new Dynamic Loader object
		*/
		DynamicLoader(void) = default;

		/**
		* @brief Destroy the Dynamic Loader object and release its content
		*/
		~DynamicLoader(void);

		/**
		* @brief Load a dynamic library
		*/
		[[nodiscard]] DynamicHandler load(const std::string &path);

		/**
		* @brief Get a function of handler library, returning opaque pointer
		*/
		[[nodiscard]] void *getFunction(DynamicHandler handler, const std::string &name);

		/**
		* @brief Get a function of handler library, returning custom Signature
		*/
		template<typename Signature>
		[[nodiscard]] Signature getFunction(DynamicHandler handler, const std::string &name) { return reinterpret_cast<Signature>(getFunction(handler, name)); }

		/**
		* @brief Release loaded libraries.
		*  Call this function after every instances aquired from libraries are destroyed.
		*  If you destroy instances after, the virtual destructor will be unloaded and your program will crash.
		*/
		void release(void);

		/**
		* @brief Get the last error as string
		*/
		[[nodiscard]] std::string getLastError(void) const noexcept;

		/**
		* @brief Get the name of a handler
		*/
		[[nodiscard]] std::string getHandlerPath(const DynamicHandler handler) const noexcept;

	private:
		std::unordered_map<DynamicHandler, std::string> _handlers {};
};