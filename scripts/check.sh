#!/usr/bin/env bash
set -euo pipefail

cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure

if [ -d frontend/node_modules ]; then
  (
    cd frontend
    npm run format:check
    npm run lint
    npm run typecheck
    npm run build
  )
else
  echo "Skipping frontend checks because frontend/node_modules is absent. Run npm install first." >&2
fi
