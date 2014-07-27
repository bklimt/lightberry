#ifndef __INCLUDE_JSON_H__
#define __INCLUDE_JSON_H__

#include <map>
#include <string>
#include <vector>

#include <boost/variant.hpp>

namespace lightberry {

class JsonNull {
};

class JsonObject;
class JsonArray;

typedef boost::variant<
    JsonNull,
    int,
    double,
    std::string,
    boost::recursive_wrapper<JsonObject>,
    boost::recursive_wrapper<JsonArray>
    > JsonValue;

std::string Stringify(const JsonValue &value);

class JsonObject {
 public:
  JsonObject() {}

  JsonObject(const JsonObject &other) {
    data = other.data;
  }

  const JsonObject &operator=(const JsonObject &other) {
    data = other.data;
    return *this;
  }

  bool IsUndefined(const std::string &key) const;
  bool IsNull(const std::string &key) const;
  int GetInt(const std::string &key) const;
  double GetDouble(const std::string &key) const;
  const std::string& GetString(const std::string &key) const;
  const JsonObject& GetObject(const std::string &key) const;
  const JsonArray& GetArray(const std::string &key) const;

  void SetUndefined(const std::string &key);
  void SetNull(const std::string &key);
  void Set(const std::string &key, const JsonValue &value);

 private:
  std::map<std::string, JsonValue> data;
};

class JsonArray {
 public:
  JsonArray() {}

  JsonArray(int size) : data(size) {}

  JsonArray(const JsonArray &other) {
    data = other.data;
  }

  const JsonArray &operator=(const JsonArray &other) {
    data = other.data;
    return *this;
  }

  size_t size() const { return data.size(); }
  
  bool IsNull(int index) const;
  int GetInt(int index) const;
  double GetDouble(int index) const;
  const std::string& GetString(int index) const;
  const JsonObject& GetObject(int index) const;
  const JsonArray& GetArray(int index) const;

  void SetNull(int index);
  void Set(int index, const JsonValue &value);

  void Add(const JsonValue &value);
  void RemoveLast();

 private:
  std::vector<JsonValue> data;
};

}  // namespace lightberry

#endif
