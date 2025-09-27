#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <system_error>

namespace std_fs {
    namespace fs = boost::filesystem;

    // Path type
    using path = fs::path;

    // Error code type
    using error_code = boost::system::error_code;

    // Check existence
    inline bool exists(const path& p) {
        return fs::exists(p);
    }

    // File type checks
    inline bool is_regular_file(const path& p) {
        return fs::is_regular_file(p);
    }

    inline bool is_directory(const path& p) {
        return fs::is_directory(p);
    }

    // Create directory (throws on error)
    inline bool create_directory(const path& p, error_code& ec) {
        return fs::create_directory(p, ec);
    }

    inline bool create_directory(const path& p) {
        error_code ec;
        bool result = fs::create_directory(p, ec);
        if (ec) throw std::system_error(ec);
        return result;
    }

    // Remove file or empty directory
    inline bool remove(const path& p, error_code& ec) {
        return fs::remove(p, ec);
    }

    inline bool remove(const path& p) {
        error_code ec;
        bool result = fs::remove(p, ec);
        if (ec) throw std::system_error(ec);
        return result;
    }

    // File size
    inline uintmax_t file_size(const path& p, error_code& ec) {
        return fs::file_size(p, ec);
    }

    inline uintmax_t file_size(const path& p) {
        error_code ec;
        uintmax_t size = fs::file_size(p, ec);
        if (ec) throw std::system_error(ec);
        return size;
    }

    // Filename and parent path
    inline path filename(const path& p) { return p.filename(); }
    inline path parent_path(const path& p) { return p.parent_path(); }

    // Directory iteration
    inline std::vector<path> directory_iterator(const path& p) {
        std::vector<path> result;
        if (fs::exists(p) && fs::is_directory(p)) {
            for (auto& entry : fs::directory_iterator(p)) {
                result.push_back(entry.path());
            }
        }
        return result;
    }

    // Recursive iteration
    inline std::vector<path> recursive_directory_iterator(const path& p) {
        std::vector<path> result;
        if (fs::exists(p) && fs::is_directory(p)) {
            for (auto& entry : fs::recursive_directory_iterator(p)) {
                result.push_back(entry.path());
            }
        }
        return result;
    }

    inline bool copy_file(const path& from, const path& to, bool overwrite = false) {
        boost::system::error_code ec;

        // If overwrite is allowed and the target exists, remove it first
        if (overwrite && fs::exists(to)) {
            fs::remove(to, ec);
            if (ec) throw std::system_error(ec);
        }

        bool result = fs::copy_file(from, to, ec);
        if (ec) throw std::system_error(ec);
        return result;
    }

    // Create directories recursively
    inline bool create_directories(const path& p) {
        boost::system::error_code ec;
        bool result = fs::create_directories(p, ec);
        if (ec) throw std::system_error(ec);
        return result;
    }
}
