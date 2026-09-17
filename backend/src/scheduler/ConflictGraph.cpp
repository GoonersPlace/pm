#include "scheduler/ConflictGraph.h"

#include <algorithm>
#include <stdexcept>

namespace timetable {

ConflictGraph::ConflictGraph(std::vector<ClassSession> classes)
    : classes_(std::move(classes)), adjacency_(classes_.size()) {
    build();
}

const std::vector<ClassSession>& ConflictGraph::classes() const noexcept {
    return classes_;
}

const std::unordered_set<std::size_t>& ConflictGraph::neighbors(std::size_t vertex) const {
    if (vertex >= adjacency_.size()) {
        throw std::out_of_range("ConflictGraph vertex out of range");
    }
    return adjacency_[vertex];
}

std::size_t ConflictGraph::vertexCount() const noexcept {
    return classes_.size();
}

std::size_t ConflictGraph::edgeCount() const noexcept {
    return edgeCount_;
}

bool ConflictGraph::hasEdge(std::size_t left, std::size_t right) const {
    if (left >= adjacency_.size() || right >= adjacency_.size()) {
        return false;
    }
    return adjacency_[left].contains(right);
}

bool ConflictGraph::conflicts(const ClassSession& left, const ClassSession& right) {
    if (left.lecturerId == right.lecturerId) {
        return true;
    }

    std::unordered_set<std::string> groups(left.studentGroupIds.begin(), left.studentGroupIds.end());
    return std::ranges::any_of(right.studentGroupIds, [&groups](const std::string& groupId) {
        return groups.contains(groupId);
    });
}

void ConflictGraph::build() {
    for (std::size_t left = 0; left < classes_.size(); ++left) {
        for (std::size_t right = left + 1; right < classes_.size(); ++right) {
            if (!conflicts(classes_[left], classes_[right])) {
                continue;
            }
            adjacency_[left].insert(right);
            adjacency_[right].insert(left);
            ++edgeCount_;
        }
    }
}

}  // namespace timetable
