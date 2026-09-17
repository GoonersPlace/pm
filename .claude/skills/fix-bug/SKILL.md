# Skill: fix-bug

1. Reproduce or characterize the failure before changing code.
2. Identify the smallest root cause.
3. For scheduling/constraint/API business bugs, add a regression test that fails before the fix when practical.
4. Fix without unrelated refactoring.
5. Run affected tests plus relevant build/static checks.
6. Update docs only if documented behavior was wrong and owner-approved behavior is clear.
7. Run `log-task`.
