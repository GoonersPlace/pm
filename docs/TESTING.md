# Testing and Quality Gates

## 1. C++ checks

For source-code changes, run the relevant subset of:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

When available:

```bash
clang-format --dry-run --Werror <changed-cpp-files>
clang-tidy <changed-cpp-files> -p build
```

A task is not complete if required tests/build fail. If Qt/compiler/tools are unavailable, clearly report which verification could not run.

## 2. Frontend checks

```bash
cd frontend
npm run format:check
npm run lint
npm run typecheck
npm run build
```

## 3. Required unit-test focus

- conflict graph construction;
- Greedy Coloring;
- DSATUR Coloring;
- coloring validity;
- hard constraints;
- room compatibility/assignment;
- soft-constraint scoring;
- empty input;
- impossible input;
- deterministic tie-breaking;
- regression bugs in scheduling/business logic.

## 4. Integration tests

Add basic integration coverage for API + SQLite + scheduling services once those endpoints/services are implemented.

## 5. E2E

A small number of E2E tests may cover the critical flow:

login → prepare/load data → generate schedule → inspect timetable/graph.

E2E breadth is not an MVP priority.

## 6. Coverage guidance

- scheduling/business logic: 70%+ overall;
- conflict graph: 80%+;
- graph coloring: 80%+;
- constraint validation: 80%+;
- scoring: 75%+.

Do not chase 100% at the expense of meaningful cases.

## 7. Definition of Done

A normal code task is done only when:

- implementation matches approved requirements;
- changes stay in scope;
- relevant tests pass;
- relevant lint/static analysis/type checks pass;
- build passes;
- no known regression is introduced;
- behavior/API/schema docs are updated if legitimately changed;
- task log is written;
- remaining TODOs/issues are explicitly recorded.
