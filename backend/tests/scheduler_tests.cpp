#include "scheduler/Coloring.h"
#include "scheduler/ConflictGraph.h"
#include "scheduler/Models.h"

#include <cassert>
#include <iostream>
#include <vector>

using timetable::ClassSession;
using timetable::ConflictGraph;

namespace {

std::vector<ClassSession> sampleClasses() {
    return {
        {.classId = "A", .courseId = "C1", .lecturerId = "L1", .studentGroupIds = {"G1"}, .requiredCapacity = 30, .requiredRoomType = std::nullopt},
        {.classId = "B", .courseId = "C2", .lecturerId = "L1", .studentGroupIds = {"G2"}, .requiredCapacity = 25, .requiredRoomType = std::nullopt},
        {.classId = "C", .courseId = "C3", .lecturerId = "L2", .studentGroupIds = {"G1"}, .requiredCapacity = 20, .requiredRoomType = std::nullopt},
        {.classId = "D", .courseId = "C4", .lecturerId = "L3", .studentGroupIds = {"G3"}, .requiredCapacity = 20, .requiredRoomType = std::nullopt},
    };
}

void testConflictGraph() {
    const ConflictGraph graph(sampleClasses());
    assert(graph.vertexCount() == 4);
    assert(graph.edgeCount() == 2);
    assert(graph.hasEdge(0, 1));  // shared lecturer
    assert(graph.hasEdge(0, 2));  // shared student group
    assert(!graph.hasEdge(1, 2));
    assert(!graph.hasEdge(0, 3));
}

void testGreedyColoring() {
    const ConflictGraph graph(sampleClasses());
    const auto result = timetable::greedyColor(graph);
    assert(timetable::isValidColoring(graph, result));
    assert(result.colorCount >= 2);
}

void testDsaturColoring() {
    const ConflictGraph graph(sampleClasses());
    const auto result = timetable::dsaturColor(graph);
    assert(timetable::isValidColoring(graph, result));
    assert(result.colorCount >= 2);
}

void testEmptyGraph() {
    const ConflictGraph graph({});
    const auto greedy = timetable::greedyColor(graph);
    const auto dsatur = timetable::dsaturColor(graph);
    assert(greedy.colorCount == 0);
    assert(dsatur.colorCount == 0);
    assert(timetable::isValidColoring(graph, greedy));
    assert(timetable::isValidColoring(graph, dsatur));
}

}  // namespace

int main() {
    testConflictGraph();
    testGreedyColoring();
    testDsaturColoring();
    testEmptyGraph();
    std::cout << "scheduler_tests passed\n";
    return 0;
}
