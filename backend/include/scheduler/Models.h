#pragma once

#include <optional>
#include <string>
#include <vector>

namespace timetable {

struct ClassSession {
    std::string classId;
    std::string courseId;
    std::string lecturerId;
    std::vector<std::string> studentGroupIds;
    int requiredCapacity{0};
    std::optional<std::string> requiredRoomType;
};

}  // namespace timetable
