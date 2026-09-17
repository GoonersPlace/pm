# GitHub Copilot project instructions

Follow `AGENTS.md` as the repository-wide contract. Before generating substantial code, consult the relevant docs under `docs/`.

Key rules:

- Backend is C++20 + Qt 6 (`QtHttpServer`, `QtSql`) with SQLite.
- Frontend is React + TypeScript + Vite + Tailwind.
- Scheduling core should be plain/testable modern C++ and easy to explain.
- Greedy Coloring is the baseline; DSATUR is the first improvement. Do not replace the strategy without approval.
- Hard constraints must never be weakened silently.
- Do not add dependencies, alter DB schema, change public API contracts, or change project-wide architecture without approval.
- Keep code simple and within scope.
- Never reveal or modify `.env` secrets.
- Do not perform git write actions unless explicitly requested.
