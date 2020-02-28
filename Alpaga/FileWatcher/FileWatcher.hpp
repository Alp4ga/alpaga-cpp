/*
  * @Author: Alpaga
  * @Date: 2019-10-03 16:22:02
 * @Last Modified by: Alpaga
<<<<<<< HEAD
 * @Last Modified time: 2020-02-28 10:53:12
=======
 * @Last Modified time: 2020-02-27 16:45:27
>>>>>>> 6cf30bfa9d6625099d37321493aab070c65894fa
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
			bool firstRound = true;
			while(_running == FileAction::Continue) {
				for (const auto &[file, type] : _paths) {
					if (!std::filesystem::exists(file)) {
						_running = action(file, FileStatus::erased);
						 _paths.erase(file);
					} else if (firstRound) {
						_running =  action(file, FileStatus::in);
					}
				}
				if (firstRound)
					firstRound = false;

				for(const auto &file : std::filesystem::recursive_directory_iterator(_pathToWatch)) {
					const auto current_file_last_write_time = std::filesystem::last_write_time(file);
					if(_paths.find(file.path().string()) == _paths.end()) {
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