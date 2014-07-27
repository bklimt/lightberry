
#include "json.h"

namespace lightberry {

class JsonStringifyVisitor : public boost::static_visitor<std::string> {
 public:
  JsonStringifyVisitor(bool pretty) : pretty_(pretty) {
  }

  std::string operator()(const JsonNull &null) const {
    return "null";
  }

  std::string operator()(int &value) const {
    return "no";
  }

  std::string operator()(double &value) const {
    return "no";
  }

  std::string operator()(const std::string &value) const {
    return "no";
  }

  std::string operator()(const JsonObject &value) const {
    
    return "no";
  }

  std::string operator()(const JsonArray &value) const {
    return "no";
  }

 private:
  bool pretty_;
};

std::string Stringify(const JsonValue &value) {
  return boost::apply_visitor(JsonStringifyVisitor(), value);
}

// Getters

bool JsonObject::IsUndefined(const std::string &key) const {
  return data.count(key) == 0;
}

bool JsonObject::IsNull(const std::string &key) const {
  return boost::get<JsonNull>(&data.at(key)) != NULL;
}

int JsonObject::GetInt(const std::string &key) const {
  return boost::get<int>(data.at(key));
}

double JsonObject::GetDouble(const std::string &key) const {
  return boost::get<double>(data.at(key));
}

const std::string& JsonObject::GetString(const std::string &key) const {
  return boost::get<std::string>(data.at(key));
}

const JsonObject& JsonObject::GetObject(const std::string &key) const {
  return boost::get<JsonObject>(data.at(key));
}

const JsonArray& JsonObject::GetArray(const std::string &key) const {
  return boost::get<JsonArray>(data.at(key));
}

// Setters

void JsonObject::SetUndefined(const std::string &key) {
  data.erase(key);
}

void JsonObject::SetNull(const std::string &key) {
  JsonNull null;
  data[key] = null;
}

void JsonObject::Set(const std::string &key, const JsonValue &value) {
  data[key] = value;
}

// Getters

bool JsonArray::IsNull(int index) const {
  return boost::get<JsonNull>(&data.at(index)) != NULL;
}

int JsonArray::GetInt(int index) const {
  return boost::get<int>(data.at(index));
}

double JsonArray::GetDouble(int index) const {
  return boost::get<double>(data.at(index));
}

const std::string& JsonArray::GetString(int index) const {
  return boost::get<std::string>(data.at(index));
}

const JsonObject& JsonArray::GetObject(int index) const {
  return boost::get<JsonObject>(data.at(index));
}

const JsonArray& JsonArray::GetArray(int index) const {
  return boost::get<JsonArray>(data.at(index));
}

// Setters

void JsonArray::SetNull(int index) {
  JsonNull null;
  data[index] = null;
}

void JsonArray::Set(int index, const JsonValue &value) {
  data[index] = value;
}

void JsonArray::Add(const JsonValue &value) {
  data.push_back(value);
}

void JsonArray::RemoveLast() {
  data.pop_back();
}

}  // namespace lightberry

