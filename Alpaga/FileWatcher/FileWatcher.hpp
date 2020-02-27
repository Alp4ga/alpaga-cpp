/*
  * @Author: Alpaga
  * @Date: 2019-10-03 16:22:02
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-01-30 15:41:00
*/

#pragma once

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	class FileWatcher;
};

/*! @class Alpaga::FileWatcher
 * @brief Handle action in directory
 * Can detect if file is in, created, modified or erased
*/
class Alpaga::FileWatcher {
	public:
		/*! @enum FileStatus
		* @brief  Status file
		*/
		enum class FileStatus {in, created, modified, erased};
		/*! @enum FileAction
		* @brief  State of the class after detecting a file
		*/
		enum class FileAction {Stop, Continue};

	public:
		/*! @brief Constructor class FileWatcher
		 *
		 * @param pathToWatch Path to the directory to watch
		 * @param delay Delay between each check
		*/
		explicit FileWatcher(const std::string &pathToWatch, std::chrono::duration<int, std::milli> delay)
			: _pathToWatch(pathToWatch), _delay(delay)
		{
			for(const auto &file : std::filesystem::recursive_directory_iterator(_pathToWatch))
				_paths[file.path().string()] = std::filesystem::last_write_time(file);
		}
		/*!
		 * @brief Default copy Constructor class FileWatcher
		*/
		FileWatcher(const FileWatcher &) noexcept = default;
		/*!
		 * @brief Default operator= class FileWatcher
		*/
		FileWatcher &operator=(const FileWatcher &) noexcept = default;
		/*!
		 * @brief Default descrutor class FileWatcher
		*/
		~FileWatcher() noexcept = default;

	public:
		/*! @brief Starting to watch
		 * @param action Callback when a new event is coming 
		*/
	    void lunch(const std::function<FileAction(const std::string &, FileStatus)> &action) {
			bool first = true;
			while(_running == FileAction::Continue) {
				auto it = _paths.begin();
				while (it != _paths.end()) {
					if (!std::filesystem::exists(it->first)) {
						_running = action(it->first, FileStatus::erased);
						it = _paths.erase(it);
					} else {
						if (first)
							_running =  action(it->first, FileStatus::in);
						it++;
					}                    
				}
				if (first)
					first = false;

				for(const auto &file : std::filesystem::recursive_directory_iterator(_pathToWatch)) {
					const auto current_file_last_write_time = std::filesystem::last_write_time(file);
					if(!contains(file.path().string())) {
						_paths[file.path().string()] = current_file_last_write_time;
						_running = action(file.path().string(), FileStatus::created);
					} else {
						if(_paths[file.path().string()] != current_file_last_write_time) {
							_paths[file.path().string()] = current_file_last_write_time;
							_running =  action(file.path().string(), FileStatus::modified);
						}
					}
				}
				std::this_thread::sleep_for(_delay);
			}
		}

	private:
		/*! @brief Check if file is already in
		 * @param key Filename
		 *
		 * @return true if file is not found
		*/
		bool contains(const std::string &key) {
        	auto el = _paths.find(key);
        	return el != _paths.end();
		}

	private:
		/*!
		 * @brief path to the directory to watch
		*/
		std::string _pathToWatch;
		/*!
		 * @brief Timer between each look
		*/
		std::chrono::duration<int, std::milli> _delay;
		/*!
		 * @brief Container files in directory
		*/
		std::unordered_map<std::string, std::filesystem::file_time_type> _paths;
		/*!
		 * @brief Current action
		*/
    	FileAction _running = FileAction::Continue;
};