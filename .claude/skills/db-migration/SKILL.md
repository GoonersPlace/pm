# Skill: db-migration

Database schema changes require prior owner approval. After approval: inspect latest migration; create the next numbered SQL file; never rewrite an applied migration; maintain foreign keys/indexes intentionally; update `docs/DATABASE.md`; add/adjust tests; verify migration on a disposable SQLite database. Never include real `.env` values.
