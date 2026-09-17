# Backend agent rules

Applies to `backend/`.

- Backend language is C++20.
- HTTP boundary uses QtHttpServer; persistence uses QtSql + SQLite.
- Keep `scheduler/` logic independent of Qt when practical.
- Do not add a new C++ dependency without approval.
- Do not alter `backend/migrations/` schema without approval.
- Public routes must remain under `/api/v1` and conform to `docs/API.md`.
- Validate request data before it enters scheduling/domain logic.
- Never return stack traces, SQL text, filesystem paths, or secrets to clients.
- Add CTest coverage for graph/scheduling/constraint behavior.
