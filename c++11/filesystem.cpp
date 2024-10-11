// Examples using the filesystem library
// Requires c++17
#include <experimental/filesystem>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cerrno>

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

string listPerms(fs::perms perms)
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
    auto tm = localtime(&lastWriteTime);
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

    sort(entries.begin(), entries.end());

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

string humanReadableSize(uintmax_t size)
{
    unsigned int suffixIndex = 0;
    auto humanSize = size;
    array<char, 5> suffix =
    { ' ', 'K', 'M', 'G', 'T' };

    while (humanSize >= 1024 && suffixIndex < (suffix.size() - 1U))
    {
        humanSize /= 1024;
        suffixIndex++;
    }

    stringstream ret;
    ret << humanSize;

    if (suffixIndex > 0)
    {
        ret << suffix.at(suffixIndex);
    }
    return ret.str();
}

// The filesystem library lacks mkdtemp() functionality, so I wrote my own. Hopefully this is resolved in C++20
fs::path& mkdtemp(fs::path& dir)
{
    string name(dir.string());
    char tmp[PATH_MAX];
    strncpy(tmp, name.c_str(), PATH_MAX); // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    if (::mkdtemp(tmp) == nullptr) // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    {
        error_code ec = make_error_code(static_cast<errc>(errno));
        throw fs::filesystem_error("Unable to create directory", ec);
    }
    dir = tmp;
    return dir;
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    try
    {

        // Space info
        cout << "Available space on filesystem containing system temporary directory:" << endl;
        fs::space_info si = fs::space(fs::temp_directory_path());
        cout << fs::temp_directory_path().string() << ": available=" << humanReadableSize(si.available) << " capacity="
                << humanReadableSize(si.capacity) << " free=" << humanReadableSize(si.free) << endl;

        // Get system temp directory
        fs::path tmpDir(fs::temp_directory_path());

        // Operators / or /= works as directory separators
        tmpDir /= "fs_XXXXXX";

        // The filesystem library lacks mkstemp() and mkdtemp() functionality, so I wrote my own. Hopefully this is
        // resolved in C++20
        cout << "Create temporary directory: " << mkdtemp(tmpDir) << endl;

        // Use the / operator on tmpDir to create a filename
        fs::path fooPath(tmpDir / "foo.txt");
        cout << "Create file " << fooPath << endl;
        {
            // Create file. ofstream now accepts filesystem::path as parameter instead of const char *
            ofstream foo(fooPath);
            foo << "foo\n";
        }

        cout << "List directory" << endl;
        list(tmpDir);

        // Rename file
        fs::path barPath(tmpDir / "bar.txt");
        cout << "Rename " << fooPath << " to " << barPath << endl;
        fs::rename(fooPath, barPath);

        // Create symlink
        fs::path linkPath(tmpDir / "link");
        cout << "Create symlink to bar: " << linkPath << endl;
        fs::create_symlink(barPath, linkPath);

        cout << "List directory" << endl;
        list(tmpDir);

        // Read file through link
        cout << "Read file through link " << linkPath << endl;
        ifstream in(linkPath);
        char c = in.get();
        while (in.good())
        {
            cout << c;
            c = in.get();
        }
        in.close();

        cout << "Remove " << linkPath << endl;
        fs::remove(linkPath);
        cout << "Remove " << barPath << endl;
        fs::remove(barPath);
        cout << "Remove " << tmpDir << endl;
        fs::remove(tmpDir);
    } catch (const exception& e)
    {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
