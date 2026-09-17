# Security Notes

## 1. Demo authentication warning

MVP login is intentionally not production authentication. It accepts any syntactically valid Gmail address and non-empty password and grants the single scheduler/admin role. It must only be used for local/classroom demonstration.

Do not store submitted passwords.

## 2. Environment files

Coding agents may read `.env` only when required for local configuration diagnosis. They must never:

- modify `.env`;
- print secret values;
- quote them in task logs or messages;
- copy them into tests or source files.

`.env.example` contains only safe placeholders/defaults.

## 3. API

- Validate all input.
- Do not expose stack traces or SQL errors directly to clients.
- Avoid reflecting secrets/config values in error messages.
- Bind to localhost by default.

## 4. Data

MVP should use fake or de-identified academic data. Do not add unnecessary student/lecturer personal information to the schema.
