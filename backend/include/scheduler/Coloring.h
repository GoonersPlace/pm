#pragma once

#include "scheduler/ConflictGraph.h"

#include <cstddef>
#include <vector>

namespace timetable {

struct ColoringResult {
    std::vector<int> colors;
    int colorCount{0};
};

[[nodiscard]] ColoringResult greedyColor(const ConflictGraph& graph);
[[nodiscard]] ColoringResult dsaturColor(const ConflictGraph& graph);
[[nodiscard]] bool isValidColoring(const ConflictGraph& graph, const ColoringResult& result);

}  // namespace timetable
