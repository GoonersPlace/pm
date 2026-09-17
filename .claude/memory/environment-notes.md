# Environment Notes

Safe, non-secret defaults:

- C++20
- CMake 3.24+
- Qt 6 with Core, Sql, HttpServer
- SQLite Qt driver
- frontend uses npm
- backend quality uses clang-format and clang-tidy when installed
- local backend default: `127.0.0.1:8080`
- local frontend default: Vite dev server
- ngrok may be used to expose local services for demos

Never place actual `.env` values, tokens, passwords, or private URLs in this file.
