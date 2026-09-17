# Architecture Decision Record Index

## ADR-001 — Web application with C++/Qt backend
**Status:** Accepted

The system remains a browser-based web application. Backend and scheduling logic use C++20 + Qt 6. Qt is used for HTTP/database integration, not to convert the product into a native Qt Desktop application.

## ADR-002 — SQLite for MVP
**Status:** Accepted

SQLite is sufficient for a single-user/demo-oriented scheduler MVP and keeps setup simple. Qt SQL provides database access. PostgreSQL is not part of the current architecture.

## ADR-003 — Browser frontend uses React/Vite
**Status:** Accepted for initial repository design

Because the product remains a web app and the desired UI direction includes Tailwind/shadcn-style components, the browser layer uses React + TypeScript + Vite rather than Next.js. Backend logic remains entirely C++.

## ADR-004 — Greedy baseline, DSATUR improvement
**Status:** Accepted

Greedy Coloring is used first because it is simple to demonstrate. DSATUR is the first improvement algorithm for comparison. Advanced optimizers are out of MVP.

## ADR-005 — Demo-only authentication
**Status:** Accepted

Any syntactically valid Gmail address and non-empty password is accepted as the only scheduler/admin role. No user-management data model is created in MVP.

## ADR-006 — Modular monolith
**Status:** Accepted

No microservices. Scheduling, API, and persistence are modules of one C++ backend application.

## ADR-007 — Local demo deployment
**Status:** Accepted

The project runs locally; ngrok may expose it during demos. No production deployment platform is selected for MVP.

## ADR-008 — Balanced AI autonomy
**Status:** Accepted

Agents may decide small reversible implementation details but must request approval for architecture, dependencies, schema, API contracts, core algorithm/constraint behavior, build-system changes, or large refactors.

## ADR-009 — No Python package manager in current stack
**Status:** Accepted by final stack selection

The earlier `uv` preference became non-applicable after the project was finalized as C++/Qt for the backend with no Python runtime. CMake manages C++ builds and npm manages the browser frontend. If Python tooling is introduced later, adding it is a dependency/tooling decision that requires approval.
