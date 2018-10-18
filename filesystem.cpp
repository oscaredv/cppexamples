// Examples using the filesystem library
// Requires c++17
#include <iostream>
#include <iomanip>
#include <experimental/filesystem>
#include <map>
#include <chrono>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;
namespace fs = std::experimental::filesystem;

char listType(const fs::file_status& status)
{
    char ret;
    switch (status.type())
    {
    case fs::file_type::regular:
        ret = '-';
        break;
    case fs::file_type::directory:
        ret = 'd';
        break;
    case fs::file_type::symlink:
        ret = 'l';
        break;
    case fs::file_type::block:
        ret = 'b';
        break;
    case fs::file_type::character:
        ret = 'c';
        break;
    case fs::file_type::fifo:
        ret = 'p';
        break;
    case fs::file_type::socket:
        ret = 's';
        break;
    case fs::file_type::unknown:
        [[fallthrough]];
    case fs::file_type::none:
        [[fallthrough]];
    case fs::file_type::not_found:
        ret = '?';
        break;
    }
    return ret;
}

std::string listPerms(fs::perms perms)
{
    string ret("rwxrwxrwx");
    if ((perms & fs::perms::owner_read) == fs::perms::none)
    {
        ret.at(0) = '-';
    }
    if ((perms & fs::perms::owner_write) == fs::perms::none)
    {
        ret.at(1) = '-';
    }
    if ((perms & fs::perms::set_uid) != fs::perms::none)
    {
        ret.at(2) = 's';
    }
    else if ((perms & fs::perms::owner_exec) == fs::perms::none)
    {
        ret.at(2) = '-';
    }

    if ((perms & fs::perms::group_read) == fs::perms::none)
    {
        ret.at(3) = '-';
    }
    if ((perms & fs::perms::group_write) == fs::perms::none)
    {
        ret.at(4) = '-';
    }
    if ((perms & fs::perms::set_gid) != fs::perms::none)
    {
        ret.at(5) = 's';
    }
    else if ((perms & fs::perms::group_exec) == fs::perms::none)
    {
        ret.at(5) = '-';
    }

    if ((perms & fs::perms::others_read) == fs::perms::none)
    {
        ret.at(6) = '-';
    }
    if ((perms & fs::perms::others_write) == fs::perms::none)
    {
        ret.at(7) = '-';
    }
    if ((perms & fs::perms::sticky_bit) != fs::perms::none)
    {
        ret.at(8) = 't';
    }
    else if ((perms & fs::perms::others_exec) == fs::perms::none)
    {
        ret.at(8) = '-';
    }

    return ret;
}

void listFile(const fs::path& file)
{
    string filename = file.filename().string();
    if (!filename.empty() && filename.at(0) == '.')
    {
        return;
    }
    fs::file_status status = fs::status(file);
    cout << listType(status) << listPerms(status.permissions());
    cout << " " << fs::hard_link_count(file);

    cout << " " << setw(5);
    switch (status.type())
    {
    case fs::file_type::symlink:
        [[fallthrough]];
    case fs::file_type::regular:
        cout << fs::file_size(file);
        break;
    case fs::file_type::directory:
        cout << "";
        break;
    default:
        cout << "0";
        break;
    }

    auto lastWriteTime = system_clock::to_time_t(fs::last_write_time(file));
    auto tm = std::localtime(&lastWriteTime);
    cout << " " << put_time(tm, "%b.  %e %H:%M");

    cout << " " << filename << endl;
}

void listDir(const fs::path& dir)
{
    vector<fs::path> entries;
    for (auto &entry : fs::directory_iterator(dir))
    {
        entries.push_back(entry);
    }

    std::sort(entries.begin(), entries.end());

    for (auto& entry : entries)
    {
        listFile(entry);
    }
}

void list(const fs::path& path)
{
    if (fs::is_directory(path))
    {
        listDir(path);
    }
    else
    {
        listFile(path);
    }
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    try
    {
        list(".");
    } catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
