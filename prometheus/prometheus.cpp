#include "prometheus.h"
#include <ESP8266WiFi.h>

PrometheusClient::PrometheusClient(const String& server,
                                   const uint16_t port,
                                   const String& job,
                                   const String& instance)
    : server_(server),
      port_(port),
      url_("/metrics/job/" + job + "/instance/" + instance) {}

void PrometheusClient::AddGauge(const String& name,
                                const float value,
                                const String& extra_keys) {
  const char needs_comma = extra_keys.startsWith(",") ? '' : ',';
  messages_ += "# TYPE " + name + " gauge\n" +
      name + "{chipid=\"" + String(ESP.getChipId()) + \"" +
      needs_comma + extra_keys + "} " + String(value) + "\n";
}

bool PrometheusClient::Send() {
  if (!client_.connect()) {
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
  delay(100);
  while(client.available()) {
    String line = client.readStringUntil('\r');
    // maybe Serial.print this.
  }
  client.stop();
}


