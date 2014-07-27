
#include <gtest/gtest.h>

#include "json.h"

TEST(JsonObjectTest, UndefinedField) {
  lightberry::JsonObject obj;
  EXPECT_TRUE(obj.IsUndefined("k"));

  obj.Set("k", 3);
  EXPECT_FALSE(obj.IsUndefined("k"));

  obj.SetUndefined("k");
  EXPECT_TRUE(obj.IsUndefined("k"));

  EXPECT_EQ("{}", lightberry::Stringify(obj));
}

TEST(JsonObjectTest, NullField) {
  lightberry::JsonObject obj;
  obj.SetNull("k");
  EXPECT_TRUE(obj.IsNull("k"));
  EXPECT_FALSE(obj.IsUndefined("k"));
}

TEST(JsonObjectTest, IntField) {
  lightberry::JsonObject obj;
  obj.Set("k", 22);
  EXPECT_EQ(22, obj.GetInt("k"));
  EXPECT_FALSE(obj.IsNull("k"));
  EXPECT_FALSE(obj.IsUndefined("k"));
}

TEST(JsonObjectTest, DoubleField) {
  lightberry::JsonObject obj;
  obj.Set("k", 22.5);
  EXPECT_EQ(22.5, obj.GetDouble("k"));
  EXPECT_FALSE(obj.IsNull("k"));
  EXPECT_FALSE(obj.IsUndefined("k"));
}

TEST(JsonObjectTest, StringField) {
  lightberry::JsonObject obj;
  obj.Set("k", "hello world");
  EXPECT_EQ("hello world", obj.GetString("k"));
  EXPECT_FALSE(obj.IsNull("k"));
  EXPECT_FALSE(obj.IsUndefined("k"));
}

TEST(JsonObjectTest, ObjectField) {
  lightberry::JsonObject a;
  lightberry::JsonObject b;
  lightberry::JsonObject c;

  a.Set("key", "a");
  b.Set("key", "b");
  c.Set("key", "c");

  b.Set("c", c);
  a.Set("b", b);

  EXPECT_EQ("a", a.GetString("key"));
  EXPECT_EQ("b", a.GetObject("b").GetString("key"));
  EXPECT_EQ("c", a.GetObject("b").GetObject("c").GetString("key"));
}

TEST(JsonObjectTest, ArrayField) {
  lightberry::JsonArray array;
  array.Add(22);
  array.Add(22.5);
  array.Add("hello world");

  lightberry::JsonObject obj;
  obj.Set("array", array);

  EXPECT_EQ(3, obj.GetArray("array").size());
  EXPECT_EQ(22, obj.GetArray("array").GetInt(0));
  EXPECT_EQ(22.5, obj.GetArray("array").GetDouble(1));
  EXPECT_EQ("hello world", obj.GetArray("array").GetString(2));
}

TEST(JsonArrayTest, NullField) {
  lightberry::JsonArray array(1);
  EXPECT_TRUE(array.IsNull(0));
  array.Set(0, 22);
  EXPECT_FALSE(array.IsNull(0));
  array.SetNull(0);
  EXPECT_TRUE(array.IsNull(0));
}

TEST(JsonArrayTest, IntField) {
  lightberry::JsonArray array(1);
  array.Set(0, 22);
  EXPECT_EQ(22, array.GetInt(0));
  EXPECT_FALSE(array.IsNull(0));
}

TEST(JsonArrayTest, DoubleField) {
  lightberry::JsonArray array(1);
  array.Set(0, 22.5);
  EXPECT_EQ(22.5, array.GetDouble(0));
  EXPECT_FALSE(array.IsNull(0));
}

TEST(JsonArrayTest, StringField) {
  lightberry::JsonArray array(1);
  array.Set(0, "hello world");
  EXPECT_EQ("hello world", array.GetString(0));
  EXPECT_FALSE(array.IsNull(0));
}

TEST(JsonArrayTest, ObjectField) {
  lightberry::JsonObject obj;
  obj.Set("key", "aaa");

  lightberry::JsonArray array;
  array.Add(obj);

  EXPECT_EQ(1, array.size());
  EXPECT_EQ("aaa", array.GetObject(0).GetString("key"));
}

TEST(JsonArrayTest, ArrayField) {
  lightberry::JsonArray inner;
  inner.Add(22);
  inner.Add(22.5);
  inner.Add("hello world");

  lightberry::JsonArray outer;
  outer.Add(inner);

  EXPECT_EQ(1, outer.size());

  EXPECT_EQ(3, outer.GetArray(0).size());
  EXPECT_EQ(22, outer.GetArray(0).GetInt(0));
  EXPECT_EQ(22.5, outer.GetArray(0).GetDouble(1));
  EXPECT_EQ("hello world", outer.GetArray(0).GetString(2));
}

