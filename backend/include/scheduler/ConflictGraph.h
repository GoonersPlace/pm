#pragma once

#include "scheduler/Models.h"

#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace timetable {

class ConflictGraph {
public:
    explicit ConflictGraph(std::vector<ClassSession> classes);

    [[nodiscard]] const std::vector<ClassSession>& classes() const noexcept;
    [[nodiscard]] const std::unordered_set<std::size_t>& neighbors(std::size_t vertex) const;
    [[nodiscard]] std::size_t vertexCount() const noexcept;
    [[nodiscard]] std::size_t edgeCount() const noexcept;
    [[nodiscard]] bool hasEdge(std::size_t left, std::size_t right) const;

private:
    static bool conflicts(const ClassSession& left, const ClassSession& right);
    void build();

    std::vector<ClassSession> classes_;
    std::vector<std::unordered_set<std::size_t>> adjacency_;
    std::size_t edgeCount_{0};
};

}  // namespace timetable
