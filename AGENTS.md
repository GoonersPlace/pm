# AGENTS.md — instructions for coding agents

## Scope

These instructions apply to the entire repository unless a nested `AGENTS.md` adds stricter module-specific rules.

## Sources of truth

1. `docs/SRS.md` and `docs/PRD.md` are co-primary for product behavior and scope. If they conflict, stop and ask rather than selecting one silently.
2. `docs/ARCHITECTURE.md` defines mandatory architecture.
3. `docs/GRAPH_MODEL.md` and `docs/SCHEDULING_RULES.md` define scheduling semantics.
4. `docs/API.md` defines public API contracts.
5. `backend/migrations/*.sql` defines database structure; `docs/DATABASE.md` must mirror it.
6. `docs/DECISIONS.md` records accepted architectural decisions.

## Mandatory architecture

- Web application.
- C++20 + Qt 6 backend (`QtHttpServer`, `QtSql`, `QtCore`).
- SQLite database.
- React + TypeScript + Vite + Tailwind web frontend.
- Graph/scheduling core in testable modern C++ with minimal Qt coupling.
- CMake + CTest for C++ build/tests.

Do not substitute FastAPI, PostgreSQL, Qt Desktop, microservices, or a different core stack without owner approval.

## Autonomy

Small, reversible implementation decisions are allowed. Ask before changing architecture, dependencies, schema, API contract, algorithm strategy, hard/soft constraints, MVP scope, build system, or project-wide configuration.

## Quality

- No over-engineering.
- Stay within task scope.
- Add tests for behavior changes and regression bugs.
- C++: clang-format, clang-tidy, warnings, CTest.
- Frontend: TypeScript strict, ESLint, Prettier.
- Never report success if relevant checks fail.

## Secrets

`.env` may be read when necessary but must never be modified or have its secret values displayed/copied. Use `.env.example` for documentation.

## Git

Do not commit, push, merge, force-push, or switch branches unless explicitly asked.
