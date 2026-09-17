# Repository Bootstrap — 2026-09-15

## Task

Create the initial Smart Timetable Scheduler repository with coding-agent rules, specifications, skills, memory, and a minimal code skeleton.

## Scope

- C++20 + Qt 6 web backend architecture.
- SQLite schema/migration baseline.
- React/Vite browser frontend shell.
- Greedy and DSATUR graph-coloring bootstrap.
- Multi-agent instructions for Claude Code, Codex, and GitHub Copilot.

## Important decisions

- Product remains a web app; Qt is used for backend HTTP/database integration, not Qt Desktop.
- PostgreSQL/FastAPI removed.
- SQLite + QtSql selected.
- Greedy baseline + DSATUR improvement.
- Demo-only Gmail/non-empty-password login.
- `/api/v1` versioning.
- Balanced AI autonomy.
- Local deployment; ngrok only for demonstration.

## Verification

- Scheduling core compiled independently with C++20 compiler.
- Scheduler unit test executable passed.
- SQLite migration syntax verified when local sqlite3 tooling is available during bootstrap checks.
- Full Qt API build requires Qt 6 Core/Sql/HttpServer in the target development environment.
- Frontend checks require npm dependencies to be installed.

## Known follow-up work

- CRUD API/persistence services.
- Room assignment and complete hard-constraint validation.
- Soft scoring implementation.
- Schedule generation/persistence endpoint.
- Timetable and graph visualization.
- Integration/E2E coverage.
