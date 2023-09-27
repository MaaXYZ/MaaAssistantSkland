#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "MaaFramework/MaaAPI.h"
#include "MaaToolKit/MaaToolKitAPI.h"
#include "meojson/json.hpp"

struct Task
{
    std::string name;
    std::string type;
    bool enabled = true;
    json::value param = json::object();
};

using TaskList = std::vector<Task>;

void print_help();

MaaSize scanning_devices();

json::value skland_param();

bool proc_argv(int argc, char** argv, bool& debug, std::string& adb, std::string& adb_address,
               TaskList& tasks, MaaAdbControllerType& ctrl_type);

bool match_adb_address(const std::string& adb_address, MaaSize& index , const MaaSize& device_size);

void print_device_list(const MaaSize& device_size);

MaaSize get_device_index(const MaaSize& device_size);

void save_config(const std::string& adb, const std::string& adb_address, const TaskList& tasks,
                 MaaAdbControllerType ctrl_type);

std::string read_adb_config(const std::filesystem::path& cur_dir);

std::string task_status(MaaStatus status);

void mpause();