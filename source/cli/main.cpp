#include "main.h"

int main(int argc, char** argv)
{
    MaaToolKitInit();

	print_help();
    print_version();

    bool debug = false;
	std::string adb;
	std::string adb_address;
    std::string package = "com.hypergryph.skland";
    std::string activity = "com.hypergryph.skland/com.hypergryph.skland.SplashActivity";
	TaskList tasks;
	MaaAdbControllerType control_type = 0;

    auto device_size = scanning_devices();
    if (device_size == 0) {
        mpause();
        return -1;
    }
    bool proced = proc_argv(argc, argv, debug, adb, adb_address, tasks, control_type);
    if (!proced) {
        std::cout << "Failed to parse argv" << std::endl;
        mpause();
        return -1;
    }
    if (tasks.empty()) {
        std::cout << "Task empty" << std::endl;
        mpause();
        return -1;
    }

    bool matched = false;
    MaaSize kIndex = 0;
    if (!adb.empty() && !adb_address.empty()) {
        matched = match_adb_address(adb_address, kIndex, device_size);
    }
    if (!matched) {
        kIndex = get_device_index(device_size);
        adb = MaaToolKitGetDeviceAdbPath(kIndex);
        adb_address = MaaToolKitGetDeviceAdbSerial(kIndex);
        save_config(adb, adb_address, tasks, control_type);
    }

    const auto cur_dir = std::filesystem::path(argv[0]).parent_path();
    std::string debug_dir = (cur_dir / "debug").string();
    std::string resource_dir = (cur_dir / "resource").string();
    std::string adb_config = MaaToolKitGetDeviceAdbConfig(kIndex);

    MaaSetGlobalOption(MaaGlobalOption_Logging, (void*)debug_dir.c_str(), debug_dir.size());
    MaaSetGlobalOption(MaaGlobalOption_DebugMode, (void*)&debug, sizeof(bool));

    auto maa_handle = MaaCreate(nullptr, nullptr);
    auto resource_handle = MaaResourceCreate(nullptr, nullptr);
    auto controller_handle = MaaAdbControllerCreate(adb.c_str(), adb_address.c_str(), control_type, adb_config.c_str(), nullptr, nullptr);

    MaaBindResource(maa_handle, resource_handle);
    MaaBindController(maa_handle, controller_handle);
    int height = 720;
    MaaControllerSetOption(controller_handle, MaaCtrlOption_ScreenshotTargetShortSide, reinterpret_cast<void*>(&height), sizeof(int));
    MaaControllerSetOption(controller_handle, MaaCtrlOption_DefaultAppPackageEntry, (void*)activity.c_str(), activity.size());
    MaaControllerSetOption(controller_handle, MaaCtrlOption_DefaultAppPackage, (void*)package.c_str(), package.size());

    auto resource_id = MaaResourcePostPath(resource_handle, resource_dir.c_str());
    auto connection_id = MaaControllerPostConnection(controller_handle);

    MaaResourceWait(resource_handle, resource_id);
    MaaControllerWait(controller_handle, connection_id);

    auto destroy = [&]() {
        MaaDestroy(maa_handle);
        MaaResourceDestroy(resource_handle);
        MaaControllerDestroy(controller_handle);
        MaaToolKitUninit();
    };

    if (!MaaInited(maa_handle)) {
        destroy();
        std::cout << "Failed to init Maa instance, a connection error or resource file corruption occurred, please refer to the log." << std::endl;
        mpause();
        return -1;
    }

    MaaTaskId task_id = 0;
    for (const auto& task : tasks) {
        if (!task.enabled)
        {
            continue;
        }
        std::cout << task.type << " Start" << std::endl;
        task_id = MaaPostTask(maa_handle, task.type.c_str(), task.param.to_string().c_str());
        std::cout << task.type << " Running..." << std::endl;
        auto end_status = MaaWaitTask(maa_handle, task_id);
        std::cout << task.type << " End" << std::endl
                  << task.type << " Result: " << task_status(end_status) << std::endl;
    }

    std::cout << std::endl << "All Tasks Over" << std::endl;

    destroy();

	return 0;
}

void print_help()
{
	std::cout <<
		R"(MAS CLI
Github: https://github.com/MaaAssistantArknights/MaaAssistantSkland

Usage: MAS_CLI.exe [adb_path] [adb_address] [task_name]...

Modify config.json to configure tasks.

Welcome to come and create a GUI for us! :)
)" << std::endl;
}

void print_version()
{
    std::cout << "MaaFramework Version: " << MaaVersion() << std::endl
              << "MAS Version: " << MAS_VERSION << std::endl
              << std::endl;
}

MaaSize scanning_devices()
{
    std::cout << "Scanning for Devices..." << std::endl;
    auto device_size = MaaToolKitFindDevice();
    if (device_size == 0) {
        std::cout << "No Devices Found" << std::endl;
        return 0;
    }
    std::cout << "Scanning Finished"
              << std::endl
              << std::endl;
    return device_size;
}

bool match_adb_address(const std::string& adb_address, MaaSize& index, const MaaSize& device_size)
{
    for (MaaSize i = 0; i < device_size; i++) {
        if (adb_address == MaaToolKitGetDeviceAdbSerial(i)) {
            index = i;
            return true;
        }
    }
    return false;
}

void print_device_list(const MaaSize& device_size) {
    for (MaaSize i = 0; i < device_size; i++) {
        std::cout << "  " << i << ". " << MaaToolKitGetDeviceName(i) << " (" << MaaToolKitGetDeviceAdbSerial(i) << ")\n";
    }
}

MaaSize get_device_index(const MaaSize& device_size)
{
    MaaSize index;
    while (true) {
        std::cout << std::endl
                  << "Please Select a Device to Connect:"
                  << std::endl
                  << std::endl;
        print_device_list(device_size);
        std::cout << std::endl
                  << "Please Enter the Device Number:" 
                  << std::endl;
        std::cin >> index;
        if (index > device_size) {
            std::cout << std::endl
                      << "Unknown Device Number: " << index 
                      << std::endl
                      << std::endl;
            continue;
        }
        std::cout << std::endl;
        break;
    }
    return index;
}

json::value skland_param() {
    json::value param;
    auto& diff = param["diff_task"];
    auto& close_skland_enabled = diff["CloseSkland"]["enabled"];

    close_skland_enabled = false;

    return param;
}

bool proc_argv(int argc, char** argv, bool& debug, std::string& adb, std::string& adb_address, TaskList& tasks,
    MaaAdbControllerType& ctrl_type)
{
    int touch = 1;
    int key = 1;
    int screencap = 3;

    tasks.clear();

    if (auto config_opt = json::open("config.json")) {
        auto& confing = *config_opt;

        debug = confing.get("debug", false);
        adb = confing["adb"].as_string();
        adb_address = confing["adb_address"].as_string();

        int index = 1;
        for (auto& task : confing["tasks"].as_array()) {
            Task task_obj;
            if (task.is_string()) {
                task_obj.type = task.as_string();
                task_obj.name = "MyTask" + std::to_string(index++);
            }
            else {
                task_obj.enabled = task.get("enabled", true);
                if (!task_obj.enabled) {
                    continue;
                }
                task_obj.type = task["type"].as_string();
                task_obj.name = task["name"].as_string();
                task_obj.param = task["param"];
            }
            tasks.emplace_back(task_obj);
        }
        touch = confing.get("touch", touch);
        key = confing.get("key", key);
        screencap = confing.get("screencap", screencap);

        ctrl_type = touch << 0 | key << 8 | screencap << 16;
    }
    else {
        Task task_obj;
        task_obj.name = "MyTask1";
        task_obj.type = "Skland";
        task_obj.param = skland_param();
        tasks.emplace_back(std::move(task_obj));

        ctrl_type = touch << 0 | key << 8 | screencap << 16;
    }

    if (argc >= 3) {
        adb = argv[1];
        adb_address = argv[2];

        std::vector<std::string> task_names;
        for (int i = 3; i < argc; ++i) {
            task_names.emplace_back(argv[i]);
        }
        auto all_tasks = std::move(tasks);
        tasks.clear();
        for (auto& task_name : task_names) {
            for (auto& task : all_tasks) {
                if (task.name == task_name) {
                    task.enabled = true;
                    tasks.emplace_back(task);
                    break;
                }
            }
        }
    }

    return true;
}

void save_config(const std::string& adb, const std::string& adb_address, const TaskList& tasks,
    MaaAdbControllerType ctrl_type)
{
    json::value config;
    config["debug"] = false;
    config["adb"] = adb;
    config["adb_Doc"] = "adb.exe 所在路径，相对绝对均可";
    config["adb_address"] = adb_address;
    config["adb_address_Doc"] = "adb 连接地址，例如 127.0.0.1:7555";

    json::value tasks_array;
    for (auto& task : tasks) {
        json::value task_obj;
        task_obj["enabled"] = task.enabled;
        task_obj["type"] = task.type;
        task_obj["name"] = task.name;
        task_obj["param"] = task.param;
        tasks_array.emplace(std::move(task_obj));
    }
    config["tasks"] = std::move(tasks_array);
    config["tasks_Doc"] = "要执行的任务";

    config["touch"] = (ctrl_type & MaaAdbControllerType_Touch_Mask) >> 0;
    config["touch_Doc"] = "点击方式：1: Adb, 2: MiniTouch, 3: MaaTouch";
    // config["key"] = key;
    // config["key_Doc"] = "按键方式：1: Adb, 2: MaaTouch";
    config["screencap"] = (ctrl_type & MaaAdbControllerType_Screencap_Mask) >> 16;
    config["screencap_Doc"] = "截图方式：1: 自动测速, 2: RawByNetcat, 3: RawWithGzip, 4: Encode, 5: EncodeToFile, 6: "
        "MinicapDirect, 7: MinicapStream";
    config["version"] = "v0.1.0";

    std::ofstream ofs("config.json", std::ios::out);
    ofs << config;
    ofs.close();
}

std::string task_status(MaaStatus status) {
    std::string task_status;
    switch (status) {
    case MaaStatus_Invalid:
        task_status = "Invalid";
        break;
    case MaaStatus_Pending:
        task_status = "Pending";
        break;
    case MaaStatus_Running:
        task_status = "Running";
        break;
    case MaaStatus_Success:
        task_status = "Success";
        break;
    case MaaStatus_Failed:
        task_status = "Failed";
        break;
    default:
        task_status = "Unkown";
        break;
    }
    return task_status;
}

void mpause()
{
    std::ignore = getchar();
}