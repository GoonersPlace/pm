# Smart Timetable Scheduler

Web application for generating and evaluating university timetables using conflict graphs and graph coloring.

## Core idea

- Each class/session is a vertex.
- An edge means two classes cannot occur in the same time slot.
- Greedy Coloring is the transparent baseline.
- DSATUR is the first improvement algorithm.
- Hard constraints must always hold.
- Soft constraints are scored to compare valid timetables.

## MVP stack

- **Web frontend:** React + TypeScript + Vite + Tailwind CSS, shadcn/ui-compatible component structure.
- **Backend:** C++20 + Qt 6 (`QtHttpServer`, `QtSql`, `QtCore`).
- **Database:** SQLite through Qt SQL.
- **Build:** CMake + CTest.
- **C++ quality:** clang-format + clang-tidy + compiler warnings.
- **Frontend quality:** TypeScript strict + ESLint + Prettier.
- **Demo exposure:** local runtime; ngrok may expose the local web app during demos.

## AI-agent entry points

- Claude Code: read `CLAUDE.md`, then relevant `.claude/skills/*/SKILL.md`.
- Codex: read root `AGENTS.md`, plus nested `AGENTS.md` for the module being edited.
- GitHub Copilot: read `.github/copilot-instructions.md`.
- Product/behavior source of truth: `docs/SRS.md` and `docs/PRD.md`.

## Repository layout

```text
.
├── CLAUDE.md
├── AGENTS.md
├── .claude/
│   ├── memory/
│   └── skills/
├── .github/
├── docs/
├── backend/
├── frontend/
├── scripts/
├── CMakeLists.txt
└── .env.example
```

## Initial setup

### Backend

Requirements: CMake 3.24+, a C++20 compiler, Qt 6.4+ with Core/Sql/HttpServer, and the Qt SQLite driver.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the API server:

```bash
./build/backend/smart_timetable_api
```

Default API URL: `http://127.0.0.1:8080/api/v1`.

### Frontend

```bash
cd frontend
npm install
npm run dev
```

### Database

Migrations live in `backend/migrations/` and are the schema source of truth. Apply the initial migration to a local SQLite database with the helper script:

```bash
./scripts/migrate.sh
```

## Demo authentication

MVP authentication is intentionally a **demo gate, not production security**. Any syntactically valid `@gmail.com` address plus a non-empty password is accepted as the single `scheduler/admin` role. There is no user-management module in MVP.

## Package managers

The final backend is C++, so Python package manager `uv` is not used. CMake manages C++ builds and npm manages frontend packages.

## Important project rules

1. Do not change architecture, dependencies, database schema, public API contracts, graph-coloring strategy, hard/soft constraints, or MVP scope without owner approval.
2. Prefer simple, explainable algorithms and code over premature optimization.
3. Never report a coding task complete unless relevant build/tests/quality checks pass, or clearly state which check could not run and why.
4. AI agents may read `.env` when necessary but must never modify it, print secrets, copy secrets into logs/docs, or expose them in responses.
5. Do not commit, push, merge, or change branches unless the owner explicitly asks.

See `docs/` for full specifications.
