#include <utility>

#pragma once

#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class TreeNode;

using node_ptr = std::unique_ptr<TreeNode>;

class TreeNode {
 public:
  std::variant<int, double, std::string> value;

  std::vector<std::unique_ptr<TreeNode>> children;

  explicit TreeNode(std::variant<int, double, std::string> data) : value(std::move(data)) {}

  static std::vector<node_ptr> ParseChildren(const std::string &str);
  static std::variant<int, double, std::string> ParseString(std::string &str);

  ~TreeNode() = default;
};

class Tree {
 public:
  Tree() = default;
  ~Tree() = default;

  void Test();
  void PrintTree() const;
  void Serialize(std::ostream &stream);
  void Deserialize(std::istream &stream);

 private:
  void Serialize(std::ostream &stream, const node_ptr &root);
  void Print(const node_ptr &root, int level) const;
  void OutputValueToStream(std::ostream &stream, const node_ptr &root) const;

  node_ptr root_;
};

