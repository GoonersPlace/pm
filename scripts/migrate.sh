#!/usr/bin/env bash
set -euo pipefail

DB_PATH="${DATABASE_PATH:-./data/smart_timetable.sqlite}"
MIGRATIONS_DIR="${MIGRATIONS_DIR:-./backend/migrations}"

mkdir -p "$(dirname "$DB_PATH")"

if ! command -v sqlite3 >/dev/null 2>&1; then
  echo "sqlite3 CLI is required to run this helper." >&2
  exit 1
fi

sqlite3 "$DB_PATH" <<'SQL'
PRAGMA foreign_keys = ON;
CREATE TABLE IF NOT EXISTS schema_migrations (
    version TEXT PRIMARY KEY,
    applied_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);
SQL

for migration in "$MIGRATIONS_DIR"/*.sql; do
  version="$(basename "$migration")"
  applied="$(sqlite3 "$DB_PATH" "SELECT COUNT(*) FROM schema_migrations WHERE version = '$version';")"
  if [ "$applied" = "1" ]; then
    echo "Skipping already applied $version"
    continue
  fi

  echo "Applying $version"
  {
    echo "PRAGMA foreign_keys = ON;"
    echo "BEGIN;"
    cat "$migration"
    echo "INSERT INTO schema_migrations(version) VALUES ('$version');"
    echo "COMMIT;"
  } | sqlite3 "$DB_PATH"
done

echo "Migrations complete: $DB_PATH"
