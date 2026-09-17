# CLAUDE.md — Smart Timetable Scheduler

This file is the primary project instruction for Claude Code.

## 1. Read before coding

Before modifying code, read the documents relevant to the task. For behavior and product scope, `docs/SRS.md` and `docs/PRD.md` are co-primary sources of truth. If they conflict, do not guess: explain the conflict and ask the owner before changing behavior.

For implementation work, also read:

- `docs/ARCHITECTURE.md`
- `docs/GRAPH_MODEL.md` for graph/scheduling work
- `docs/SCHEDULING_RULES.md` for constraints/scoring
- `docs/API.md` for API work
- `docs/DATABASE.md` for persistence work
- `docs/UI_GUIDELINES.md` for frontend work
- `docs/TESTING.md` for verification
- `.claude/memory/MEMORY.md` and the referenced memory files

Nested `AGENTS.md` files contain module-local rules and should also be respected.

## 2. Project architecture — mandatory

The project is a web application with:

- Browser UI: React + TypeScript + Vite + Tailwind; shadcn/ui-compatible component patterns.
- Backend/API: C++20 + Qt 6, using `QtHttpServer`, `QtSql`, and `QtCore`.
- Database: SQLite through Qt SQL.
- Build/tests: CMake + CTest.
- Graph/scheduling core: plain modern C++ where possible, kept independent of Qt so it is easy to test and explain.

Do not replace this architecture, introduce FastAPI/PostgreSQL, convert the application to Qt Desktop, or add microservices without explicit approval.

## 3. Balanced autonomy

You may autonomously make small, reversible implementation choices inside the current task. Ask before any change that affects:

- architecture or major module boundaries;
- dependencies/frameworks;
- database schema;
- public API contract;
- build/compiler/project-wide configuration;
- core Graph Coloring strategy or scheduling behavior;
- hard or soft constraint definitions/weights when they change accepted behavior;
- MVP scope;
- large refactors or destructive operations.

If requirements are ambiguous but the choice is local, reversible, and does not change public behavior, choose the simplest option and document the assumption. Otherwise ask.

## 4. Coding principles

- Do not over-engineer.
- Prefer simplicity, maintainability, correctness, then performance appropriate for MVP scale.
- Keep scheduling logic deterministic where practical and easy to demonstrate.
- Use camelCase for variables/functions. Types/classes use PascalCase because this is conventional and improves readability in C++/TypeScript.
- No unexplained magic numbers for weights, penalties, time slots, or thresholds.
- Comments explain *why*, invariants, and non-obvious algorithmic choices rather than restating code.
- Avoid broad refactors outside task scope.
- Do not silently change public behavior.

## 5. C++ quality

For C++ changes:

- C++20.
- Prefer standard library in the scheduling core; Qt types belong at API/database boundaries unless justified.
- Use RAII and value semantics where reasonable.
- Avoid raw owning pointers.
- Treat meaningful compiler warnings as defects.
- Use `.clang-format` and `.clang-tidy`.
- Add/update tests for graph construction, coloring, constraints, score calculation, and regression bugs.

## 6. Frontend quality

For frontend changes:

- TypeScript strict mode.
- No `any` without a documented, narrow reason.
- Use Tailwind tokens and reusable components; do not scatter arbitrary styles.
- Follow `docs/UI_GUIDELINES.md`.
- Desktop is primary; tablet/mobile must remain usable at a basic responsive level.
- Use semantic HTML, labels, keyboard-accessible controls, sufficient contrast, and never use color as the only state indicator.

## 7. Database rules

`backend/migrations/*.sql` and the resulting SQLite schema are the structural source of truth.

- Never change schema without owner approval.
- After approval, create a new versioned SQL migration; do not rewrite an already-applied migration.
- Update `docs/DATABASE.md` in the same task.
- Use foreign keys and enable SQLite foreign-key enforcement.
- No soft delete in MVP unless requirements change.

## 8. API rules

- Base path: `/api/v1`.
- REST.
- Keep success/error envelopes consistent with `docs/API.md`.
- Public endpoint/request/response changes require approval.
- Validate input at the boundary.
- Do not expose stack traces, secrets, or internal database details in responses.

## 9. Demo authentication

MVP uses one `scheduler/admin` role. Login is intentionally a demo gate: any syntactically valid Gmail address and non-empty password may authenticate. Do not introduce user management, password storage, OAuth, RBAC complexity, or claim production-grade security unless requirements change.

## 10. Secret handling

AI agents may read `.env` if necessary to perform a task, but `.env` is read-only to the agent.

Never:

- modify `.env`;
- print or quote secrets;
- place secret values in docs, task logs, code, tests, commits, or chat output;
- copy `.env` into generated files.

Use `.env.example` for documented configuration names and placeholders.

## 11. Required task workflow

1. Read task + relevant docs/memory.
2. Inspect current code before editing.
3. Identify affected modules/contracts.
4. For a non-trivial task, write a short implementation plan.
5. Implement only the requested scope.
6. Run relevant format/lint/static-analysis/test/build checks.
7. Update docs/contracts when behavior legitimately changed.
8. Run the `log-task` workflow for completed implementation tasks.
9. Report files changed, decisions, checks run, results, and remaining issues.

Do not claim completion when required checks fail. If a tool/dependency is unavailable, state exactly what could not be run.

## 12. Git safety

Use branch names `feature/<name>`, `fix/<name>`, or `docs/<name>` when the owner asks for branch work. Use Conventional Commits when the owner asks for commits.

Never commit, push, merge, force-push, or switch branches unless explicitly requested.

## 13. Skills

Use the most specific skill under `.claude/skills/` when the task matches it. The project includes skills for implementation, bugs, review, APIs, migrations, tests, frontend pages, refactors, docs, task logging, PR preparation, project status, scheduling features, graph algorithms, constraint rules, and scheduler benchmarks.
