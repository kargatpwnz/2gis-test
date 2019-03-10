#include <memory>
#include <iostream>
#include <queue>
#include <fstream>
#include <stdexcept>
#include <memory>

#include <boost/algorithm/string.hpp>

#include "tree.h"

void Tree::PrintTree() const {
  Print(root_, 0);
}

void Tree::Print(const node_ptr &root, int level) const {
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

void Tree::Serialize(std::ostream &oss, const node_ptr &root) {
  if (!root) {
    oss << "nullptr";
    return;
  }

  OutputValueToStream(oss, root);

  for (auto &x : root->children) {
    OutputValueToStream(oss, x);
    oss << " ";
  }

  for (auto &x : root->children)
    Serialize(oss, x);
}

void Tree::Deserialize(std::istream &iss) {
  std::string parent;
  std::string children;

  // First string - parent
  // Second string - children
  std::queue<TreeNode *> queue;
  while (getline(iss, parent)) {
    boost::trim(parent);

    auto data = TreeNode::ParseString(parent);
    if (queue.empty()) {
      root_ = std::make_unique<TreeNode>(TreeNode::ParseString(parent));
      queue.push(root_.get());
    } else {
      for (; !queue.empty(); queue.pop())
        if (queue.front()->value == data)
          break;

      if (queue.empty())
        throw std::runtime_error("error while doing BFS");
    }

    getline(iss, children);
    boost::trim(children);

    if (children.empty())
      continue;

    queue.front()->children = TreeNode::ParseChildren(children);
    for (const auto &child : queue.front()->children) {
      queue.push(child.get());
    }

    queue.pop();
  }
}

void Tree::OutputValueToStream(std::ostream &oss, const node_ptr &root) const {
  std::visit([&oss](auto &arg) { oss << arg << std::endl; }, root->value);
}

std::vector<node_ptr> TreeNode::ParseChildren(const std::string &str) {
  std::vector<node_ptr> result;

  std::vector<std::string> split_values;
  boost::split(split_values, str, boost::algorithm::is_any_of(" "), boost::algorithm::token_compress_on);
  result.reserve(split_values.size());
  // Add children to parent key
  for (auto &str_value : split_values) {
    if (str_value.empty())
      continue;
    result.push_back(std::make_unique<TreeNode>(TreeNode::ParseString(str_value)));
  }

  return result;
}
data_t TreeNode::ParseString(std::string &str) {
  try {
    std::size_t pos = 0;
    int v = std::stoi(str, &pos);
    if (pos == str.size())
      return v;
  } catch (...) {}
  try {
    std::size_t pos = 0;
    double v = std::stod(str, &pos);
    if (pos == str.size())
      return v;
  } catch (...) {}

  return std::move(str);
}
