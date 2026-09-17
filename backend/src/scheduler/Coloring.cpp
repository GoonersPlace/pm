#include "scheduler/Coloring.h"

#include <algorithm>
#include <limits>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace timetable {
namespace {

int smallestAvailableColor(const ConflictGraph& graph, const std::vector<int>& colors,
                           std::size_t vertex) {
    std::unordered_set<int> used;
    for (const auto neighbor : graph.neighbors(vertex)) {
        if (colors[neighbor] >= 0) {
            used.insert(colors[neighbor]);
        }
    }
    int color = 0;
    while (used.contains(color)) {
        ++color;
    }
    return color;
}

std::vector<std::size_t> greedyOrder(const ConflictGraph& graph) {
    std::vector<std::size_t> order(graph.vertexCount());
    for (std::size_t index = 0; index < order.size(); ++index) {
        order[index] = index;
    }

    const auto& classes = graph.classes();
    std::ranges::sort(order, [&graph, &classes](std::size_t left, std::size_t right) {
        const auto leftDegree = graph.neighbors(left).size();
        const auto rightDegree = graph.neighbors(right).size();
        if (leftDegree != rightDegree) {
            return leftDegree > rightDegree;
        }
        return classes[left].classId < classes[right].classId;
    });
    return order;
}

std::size_t saturationDegree(const ConflictGraph& graph, const std::vector<int>& colors,
                             std::size_t vertex) {
    std::set<int> neighborColors;
    for (const auto neighbor : graph.neighbors(vertex)) {
        if (colors[neighbor] >= 0) {
            neighborColors.insert(colors[neighbor]);
        }
    }
    return neighborColors.size();
}

int calculateColorCount(const std::vector<int>& colors) {
    if (colors.empty()) {
        return 0;
    }
    const auto maxColor = *std::ranges::max_element(colors);
    return maxColor < 0 ? 0 : maxColor + 1;
}

}  // namespace

ColoringResult greedyColor(const ConflictGraph& graph) {
    std::vector<int> colors(graph.vertexCount(), -1);
    for (const auto vertex : greedyOrder(graph)) {
        colors[vertex] = smallestAvailableColor(graph, colors, vertex);
    }
    return {colors, calculateColorCount(colors)};
}

ColoringResult dsaturColor(const ConflictGraph& graph) {
    std::vector<int> colors(graph.vertexCount(), -1);
    const auto& classes = graph.classes();

    for (std::size_t step = 0; step < graph.vertexCount(); ++step) {
        std::size_t selected = graph.vertexCount();
        std::size_t bestSaturation = 0;
        std::size_t bestDegree = 0;
        std::string bestClassId;

        for (std::size_t vertex = 0; vertex < graph.vertexCount(); ++vertex) {
            if (colors[vertex] >= 0) {
                continue;
            }
            const auto saturation = saturationDegree(graph, colors, vertex);
            const auto degree = graph.neighbors(vertex).size();
            const auto& classId = classes[vertex].classId;

            const bool better = selected == graph.vertexCount() || saturation > bestSaturation ||
                                (saturation == bestSaturation && degree > bestDegree) ||
                                (saturation == bestSaturation && degree == bestDegree &&
                                 classId < bestClassId);
            if (better) {
                selected = vertex;
                bestSaturation = saturation;
                bestDegree = degree;
                bestClassId = classId;
            }
        }

        if (selected == graph.vertexCount()) {
            throw std::logic_error("DSATUR failed to select an uncolored vertex");
        }
        colors[selected] = smallestAvailableColor(graph, colors, selected);
    }

    return {colors, calculateColorCount(colors)};
}

bool isValidColoring(const ConflictGraph& graph, const ColoringResult& result) {
    if (result.colors.size() != graph.vertexCount()) {
        return false;
    }
    for (std::size_t vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        if (result.colors[vertex] < 0) {
            return false;
        }
        for (const auto neighbor : graph.neighbors(vertex)) {
            if (result.colors[vertex] == result.colors[neighbor]) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace timetable
