#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>

#include <boost/algorithm/string.hpp>

#include "tree.h"

void Tree::PrintTree() const {
  Print(root_, 0);
}

void Tree::Print(const std::unique_ptr<TreeNode> &root, int level) const {
  for (int i = 0; i < level; ++i)
    std::cout << "\t";
//  PrintValue(root);
  OutputValueToStream(std::cout, root);
  for (auto &x : root->children) {
    Print(x, level + 1);
  }
}

void Tree::Test() {
//  auto *node1 = new TreeNode("qwe");
//  auto *node2 = new TreeNode("baz");
//  auto *node3 = new TreeNode(12);
//  auto *node4 = new TreeNode(13.2);
//  auto *node5 = new TreeNode("bar");
//  auto *node6 = new TreeNode(15);
//  node6->children.push_back(new TreeNode(22));
//  root_->children.push_back(node1);
//  root_->children.push_back(node2);
//  root_->children.push_back(new TreeNode("asd"));
//
//  root_->children[0]->children.push_back(node3);
//  root_->children[0]->children.push_back(node4);
//
//  root_->children[1]->children.push_back(node5);
//  root_->children[1]->children.push_back(node6);

}

void Tree::Serialize(std::ostream &stream) {
  Serialize(stream, root_);
}

void Tree::Serialize(std::ostream &stream, const std::unique_ptr<TreeNode> &root) {
  if (root == nullptr) {
    stream << "nullptr";
    return;
  }

  OutputValueToStream(stream, root);
  stream << std::endl;

  for (auto &x : root->children) {
    OutputValueToStream(stream, x);
    stream << " ";
  }
  stream << std::endl;

  for (auto &x : root->children)
    Serialize(stream, x);

}

void Tree::Deserialize(std::istream &stream) {
  std::string parent;
  std::string children;

  // First string - parent
  // Second string - children
  getline(stream, parent);
  boost::trim(parent);

  if (parent.empty()) {
    std::cerr << "File is empty" << std::endl;
    return;
  }
  root_ = std::unique_ptr<TreeNode>(TreeNode::StringToNode(parent));
  getline(stream, children);
  root_->children = std::move(TreeNode::ParseChildren(children));

  std::unordered_map<std::unique_ptr<TreeNode>, std::vector<std::unique_ptr<TreeNode>>> all_nodes;
  while (getline(stream, parent)) {
    getline(stream, children);

    boost::trim(parent);
    boost::trim(children);

    all_nodes[std::make_unique<TreeNode>(parent)] = std::move(TreeNode::ParseChildren(children));
  }

  // TODO: find a way to restore nodes from map
  for (auto &&child : root_->children) {
    //child->children = std::move(all_nodes[child]);

  }
  MapToTree();
}

void Tree::MapToTree() {
  // In the map begin stored root of tree, because map isn't sorted
  // so I'm able to get first element in map as root

//  auto it = parent_children_map_.begin();
//  root_ = std::make_unique<TreeNode>(it->first);
//  root_->children = it->second;
//  parent_children_map_.erase(it);
//
//   Starting dfs and restoring tree
//  Dfs(root_);
}

void Tree::OutputValueToStream(std::ostream &stream, const std::unique_ptr<TreeNode> &root) const {
  std::visit([&stream](auto &&arg) { stream << arg << std::endl; }, root->value);
}

//void Tree::PrintValue(const std::unique_ptr<TreeNode> &root) const {
//  std::visit([](auto&& arg) {std::cout << arg << std::endl;}, root->value);
//}

void Tree::Dfs(const std::unique_ptr<TreeNode> &root) {
//  for (auto &x : parent_children_map_) {
//    if (TreeNode::CompareNodes(x.first, root))
//      root->children = x.second;
//  }
//
//  for (auto &x : root->children) {
//    Dfs(x);
//  }
}

bool TreeNode::CompareNodes(const std::unique_ptr<TreeNode> &lhs, const std::unique_ptr<TreeNode> &rhs) {
  return lhs->value == rhs->value;
}

TreeNode *TreeNode::StringToNode(const std::string &str) {
  try {
    double value = std::stod(str);
//      key_node = new TreeNode(value);
    return new TreeNode(value);
  } catch (const std::invalid_argument &e) {
    return new TreeNode(str);
  }
}

std::vector<std::unique_ptr<TreeNode>> TreeNode::ParseChildren(const std::string &str) {
  std::vector<std::unique_ptr<TreeNode>> result;

  std::vector<std::string> split_values;
  boost::split(split_values, str, boost::algorithm::is_any_of(" "), boost::algorithm::token_compress_on);
  result.reserve(split_values.size());
  // Add children to parent key
  for (const auto &str_value : split_values) {
    if (str_value.empty())
      continue;
    result.push_back(std::move(std::unique_ptr<TreeNode>(TreeNode::StringToNode(str_value))));
  }

  return result;
}
