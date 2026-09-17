#include <QCoreApplication>
#include <QHostAddress>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QUuid>

#include <cstdlib>

namespace {

QHttpServerResponse jsonResponse(const QJsonObject& object,
                                 QHttpServerResponse::StatusCode status =
                                     QHttpServerResponse::StatusCode::Ok) {
    return QHttpServerResponse(object, status);
}

QJsonObject successEnvelope(QJsonObject data, const QString& message = "OK") {
    return {{"success", true}, {"data", std::move(data)}, {"message", message}};
}

QJsonObject errorEnvelope(const QString& code, const QString& message) {
    return {{"success", false},
            {"error", QJsonObject{{"code", code}, {"message", message}, {"details", QJsonObject{}}}}};
}

bool isDemoGmail(const QString& email) {
    static const QRegularExpression pattern(
        R"(^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@gmail\.com$)",
        QRegularExpression::CaseInsensitiveOption);
    return pattern.match(email.trimmed()).hasMatch();
}

quint16 configuredPort() {
    const QByteArray value = qgetenv("APP_PORT");
    bool ok = false;
    const auto parsed = value.toUShort(&ok);
    return ok ? parsed : 8080;
}

}  // namespace

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QHttpServer server;

    server.route("/api/v1/health", QHttpServerRequest::Method::Get, []() {
        return jsonResponse(successEnvelope({{"status", "ok"}, {"service", "smart-timetable-api"}}));
    });

    server.route("/api/v1/auth/login", QHttpServerRequest::Method::Post,
                 [](const QHttpServerRequest& request) {
                     QJsonParseError parseError;
                     const auto document = QJsonDocument::fromJson(request.body(), &parseError);
                     if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
                         return jsonResponse(errorEnvelope("VALIDATION_ERROR", "Invalid JSON body"),
                                             QHttpServerResponse::StatusCode::BadRequest);
                     }

                     const auto body = document.object();
                     const auto email = body.value("email").toString().trimmed();
                     const auto password = body.value("password").toString();
                     if (!isDemoGmail(email) || password.isEmpty()) {
                         return jsonResponse(
                             errorEnvelope("INVALID_CREDENTIALS",
                                           "Demo login requires a valid Gmail address and non-empty password"),
                             QHttpServerResponse::StatusCode::Unauthorized);
                     }

                     const auto token = QUuid::createUuid().toString(QUuid::WithoutBraces);
                     return jsonResponse(successEnvelope(
                         {{"role", "scheduler_admin"}, {"token", token}}, "Demo login accepted"));
                 });

    const auto port = configuredPort();
    const auto boundPort = server.listen(QHostAddress::LocalHost, port);
    if (boundPort == 0) {
        return EXIT_FAILURE;
    }

    return app.exec();
}
