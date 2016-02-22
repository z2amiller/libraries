#include "prometheus.h"
#include <ESP8266WiFi.h>

PrometheusClient::PrometheusClient(const String& server,
                                   const uint16_t port,
                                   const String& job,
                                   const String& instance)
    : server_(server),
      port_(port),
      url_("/metrics/job/" + job + "/instance/" + instance) {}

void PrometheusClient::AddMetric(const BaseMetric& metric) {
  messages_ += metric.Format();
}

bool PrometheusClient::Send() {
  if (!client_.connect(server_.c_str(), port_)) {
    Clear();
    return false;
  }
  const int content_length = messages_.length();
  client_.print(
      "POST " + url_ + " HTTP/1.1\r\n" +
      "Host: " + server_ + "\r\n" +
      "Connection: close\r\n" +
      "Content-Length: " + String(content_length) + "\r\n" +
      "\r\n" +
      messages_);
  Clear();
  client_.flush();
  client_.stop();
  return true;
}

String& makeHeader(const String& name, const PrometheusType type) {
  return "# TYPE " + name + " " + stringFromPrometheusType(type) + "\n";
}

MapMetric::MapMetric(const String& name,
                     const String& dimension,
                     const PrometheusType type)
    : name_(name),
      dimension_(dimension),
      type_(type),
      messages_(makeHeader(name, type)) {}

void MapMetric::Add(const String& key, const float value) {
  messages_ += name_ + "{" + dimension_ + "=\"" + key + "\"} "
            + String(value) + "\n";
}

const String& MapMetric::Format() const {
  return messages_;
}

Metric::Metric(const String& name,
               const PrometheusType type)
    : name_(name),
      type_(type),
      messages_(makeHeader(name, type)) {}

void Metric::Add(const float value) {
  messages_ += name_ + " " + String(value) + "\n";
}

const String& Metric::Format() const {
  return messages_;
}
