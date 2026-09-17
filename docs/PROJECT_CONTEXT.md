# Project Context Snapshot

This document captures the owner-approved initialization decisions used to bootstrap the repository.

- Project: Smart Timetable Scheduler / graph-coloring timetable system.
- Product remains a web app.
- Core/backend language: C++.
- Backend integration: Qt 6, including QtHttpServer and QtSql.
- Database: SQLite; PostgreSQL removed from the design.
- Frontend: browser UI with Tailwind/shadcn-style component direction; initial repo uses React/Vite/TypeScript.
- MVP auth: simple single scheduler/admin demo login; valid Gmail + non-empty password; no user management.
- API versioning: `/api/v1`.
- Architecture adherence is mandatory; dependency additions require approval.
- AI autonomy: Balanced.
- Baseline algorithm: Greedy Coloring; improvement: DSATUR.
- MVP soft constraints are proposed in `SCHEDULING_RULES.md`.
- Deployment: local; ngrok for demos.
- `.env`: agent may read when necessary, but must never modify or reveal secrets.
- Git: main is stable; feature/fix/docs branches; Conventional Commits; agents do not commit/push/merge unless asked.
- SRS and PRD are generated at bootstrap and act as co-primary product sources of truth.
