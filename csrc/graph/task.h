// Copyright (c) OpenMMLab. All rights reserved.

#ifndef MMDEPLOY_CSRC_GRAPH_TASK_H_
#define MMDEPLOY_CSRC_GRAPH_TASK_H_

#include "core/graph.h"

namespace mmdeploy::graph {

class Task : public Node {
  friend class TaskParser;

 public:
  Sender<Value> Process(Sender<Value> input) override;

 private:
  std::optional<TypeErasedScheduler<Value>> sched_;
  unique_ptr<Module> module_;
  bool is_batched_{false};
  bool is_thread_safe_{false};
  dynamic_batch_t::context_t batch_context_;
};

class TaskParser {
 public:
  static Result<unique_ptr<Task>> Parse(const Value& config);
};

}  // namespace mmdeploy::graph

#endif  // MMDEPLOY_CSRC_GRAPH_TASK_H_
