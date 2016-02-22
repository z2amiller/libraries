#include <ESP8266WiFi.h>

enum PrometheusType {
  GAUGE,
  RATE
};

static inline const char *stringFromPrometheusType(PrometheusType t) {
  static const char *ptstrings[] = { "gauge", "rate" };
  return ptstrings[t];
}

class BaseMetric {
 public:
   virtual const String& Format() const = 0;
};

class PrometheusClient {
 public:
  // Create a new prometheus client connecting to server:port,
  // with "job" and "instance".  (See prometheus pushgateway docs)
  PrometheusClient(const String& server,
                   const uint16_t port,
                   const String& job,
                   const String& instance);
  void AddMetric(const BaseMetric& metric);
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

class MapMetric : public BaseMetric {
 public:
  MapMetric(const String& name,
            const String& dimension,
            const PrometheusType type = GAUGE);
  void Add(const String& key, const float value);
  const String& Format() const;
 private:
    const String name_;
    const String dimension_;
    const PrometheusType type_;
    String messages_;
};

class Metric : public BaseMetric {
 public:
   Metric(const String& name,
          const PrometheusType type = GAUGE);
   void Add(const float value);
   const String& Format() const;
  private:
   const String name_;
   const PrometheusType type_;
   String messages_;
};
