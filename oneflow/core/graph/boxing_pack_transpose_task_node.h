/*
Copyright 2020 The OneFlow Authors. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef ONEFLOW_CORE_GRAPH_BOXING_PACK_TRANSPOSE_TASK_NODE_H_
#define ONEFLOW_CORE_GRAPH_BOXING_PACK_TRANSPOSE_TASK_NODE_H_
#include "oneflow/core/graph/task_node.h"

namespace oneflow {

class BoxingPackTransposeTaskNode : public TaskNode {
 public:
  OF_DISALLOW_COPY_AND_MOVE(BoxingPackTransposeTaskNode);
  BoxingPackTransposeTaskNode() = default;
  ~BoxingPackTransposeTaskNode() override = default;

  void Init(int64_t machine_id, int64_t thrd_id, int64_t area_id, const LogicalBlobId& lbi,
            const int64_t dst_split_axis, const int64_t parallel_num);
  TaskType GetTaskType() const override { return TaskType::kBoxingS2SAll2AllPack; }

 private:
  void BuildExecGphAndRegst() override;
  void ProduceAllRegstsAndBindEdges() override;
  void ConsumeAllRegsts() final;
  void InferProducedDataRegstTimeShape() final;
  int64_t dst_split_axis_;
  int64_t parallel_num_;
  LogicalBlobId lbi_;
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_GRAPH_BOXING_PACK_TRANSPOSE_TASK_NODE_H_