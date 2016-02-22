#include <ESP8266WiFi.h>

enum PrometheusType {
  GAUGE,
  RATE
}

class PrometheusClient {
 public:
  // Create a new prometheus client connecting to server:port,
  // with "job" and "instance".  (See prometheus pushgateway docs)
  PrometheusClient(const String& server,
                   const uint16_t port,
                   const String& job,
                   const String& instance);
  // AddGauge adds a gauge metric to be updated to the prometheus server.
  //     "extra_keys" are just copied as-is into the args.
  void AddGauge(const String& name,
                const float value,
                const String& extra_keys = "");
  // TODO(z2amiller): Implement rates, etc.

  // Clear will erase any pending unsent messages.
  void Clear() {
    messages_ = "";
  }
  // Send will post any unsent messages to the prometheus server and clear
  //     the list of pending messages.
  bool Send();
 private:
  const String server_;
  const uint16_t port_;
  const String url_;
  String messages_;
  WiFiClient client_;
};

class PrometheusMap {
 public:
  PrometheusMap(const String& name,
                const String& dimension,
                const PrometheusType type = GAUGE)
    : name_(name),
      dimension_(dimension),
      type_(type) {}
  Add(const String& key,
      const float value);
  

  
                
