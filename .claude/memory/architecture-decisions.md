# Durable Architecture Decisions

- Product is a web app, not Qt Desktop.
- Backend/API/scheduling engine: C++20 + Qt 6.
- HTTP: QtHttpServer.
- Database: SQLite via QtSql.
- Frontend: React + TypeScript + Vite + Tailwind.
- Architecture: small modular monolith.
- No microservices.
- No FastAPI or PostgreSQL in current design.
- Graph core should avoid Qt dependencies where practical.
- Public REST API uses `/api/v1`.
- Schema changes and dependencies require owner approval.
