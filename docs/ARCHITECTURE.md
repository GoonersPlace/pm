# Architecture — Smart Timetable Scheduler

## 1. Architectural style

A small modular monolith is used. The web frontend is separate from the C++ HTTP backend, while backend domain modules remain in one CMake project.

```text
Browser
  |
  | HTTP/JSON
  v
React/Vite Frontend
  |
  | /api/v1
  v
C++ QtHttpServer API
  |
  +--> Application services
  |      |
  |      +--> Scheduling Core (Conflict Graph, Coloring, Validation, Scoring)
  |      +--> Repositories
  |
  +--> QtSql --> SQLite
```

## 2. Technology decisions

- C++20 for backend and scheduling engine; Qt 6.4+ is required because the HTTP server module is used.
- Qt 6 Core/HttpServer/Sql at system boundaries.
- SQLite for local/demo persistence.
- React + TypeScript + Vite for browser UI.
- Tailwind CSS with shadcn/ui-compatible component patterns.
- CMake/CTest for build and tests.

## 3. Module boundaries

### Scheduling core

`backend/include/scheduler` and `backend/src/scheduler`.

Responsibilities:

- domain models required by algorithms;
- Conflict Graph construction;
- Greedy Coloring;
- DSATUR Coloring;
- schedule validation;
- soft-constraint scoring.

Rules:

- keep Qt dependencies out unless there is a strong reason;
- no SQL/HTTP logic;
- deterministic behavior for equal input when practical;
- algorithms expose diagnostics useful for demo/tests.

### API

`backend/src/api`.

Responsibilities:

- HTTP routing;
- request parsing/validation;
- response envelopes;
- mapping between JSON DTOs and application/domain data.

### Persistence

`backend/src/db` and `backend/migrations`.

Responsibilities:

- SQLite connection;
- repositories/query functions;
- migration-aware schema usage.

Database schema changes require approval and a new migration.

### Frontend

`frontend/src`.

Responsibilities:

- demo login;
- input management views;
- timetable generation controls;
- timetable display;
- graph visualization;
- score/validation diagnostics.

## 4. Request flow for schedule generation

1. Frontend sends algorithm choice and dataset/schedule request.
2. API validates request.
3. Application layer loads relevant input data.
4. Conflict Graph is built.
5. Selected coloring algorithm assigns color indices.
6. Colors map to active time slots.
7. Compatible rooms are assigned.
8. Hard constraints are validated.
9. If valid, soft constraints are scored.
10. Result is persisted and returned with diagnostics.

## 5. Why coloring and room assignment are separate

Graph edges encode classes that must never share a time slot (for example shared lecturer/student group). Room capacity/type/availability is better handled during room assignment because two otherwise independent classes may run at the same time as long as different compatible rooms exist.

This keeps the graph model easy to explain and avoids creating false class-to-class conflicts merely because room resources are limited.

## 6. Deployment model

MVP runs locally:

- frontend dev/server on a local port;
- backend API on a local port;
- SQLite local file;
- ngrok may expose the frontend/backend for demonstrations.

There is no production hosting architecture in MVP.

## 7. Prohibited silent changes

Agents must ask before:

- changing backend/web technologies;
- introducing microservices;
- adding dependencies;
- changing schema/API contracts;
- replacing Graph Coloring as the primary approach;
- adding advanced optimizers;
- changing approved constraints.
