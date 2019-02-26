#pragma once

#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class TreeNode {
 public:
  std::variant<int, double, std::string> value;

  std::vector<std::unique_ptr<TreeNode>> children;

  explicit TreeNode(std::string string_value) : value(std::move(string_value)) {}

  explicit TreeNode(double double_value) : value(double_value) {}

  explicit TreeNode(int int_value) : value(int_value) {}

  static bool CompareNodes(const std::unique_ptr<TreeNode> &lhs, const std::unique_ptr<TreeNode> &rhs);

  static TreeNode *StringToNode(const std::string &str);
  static std::vector<std::unique_ptr<TreeNode>> ParseChildren(const std::string &str);

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
  void Serialize(std::ostream &stream, const std::unique_ptr<TreeNode> &root);
  void Print(const std::unique_ptr<TreeNode> &root, int level) const;
  void MapToTree();
  void OutputValueToStream(std::ostream &stream, const std::unique_ptr<TreeNode> &root) const;
  //void PrintValue(const std::unique_ptr<TreeNode> &root) const;
  void Dfs(const std::unique_ptr<TreeNode> &root);

  std::unique_ptr<TreeNode> root_;

  //std::map<std::unique_ptr<TreeNode>, std::vector<std::unique_ptr<TreeNode>>> parent_children_map_;
};

