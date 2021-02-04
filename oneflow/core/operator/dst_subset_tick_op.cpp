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
#include "oneflow/core/operator/dst_subset_tick_op.h"
#include "oneflow/core/job/sbp_signature_builder.h"

namespace oneflow {

void DstSubsetTickOp::InitFromOpConf() {
  CHECK(op_conf().has_dst_subset_tick_conf());
  if (op_conf().dst_subset_tick_conf().has_in()) { EnrollInputBn("in", false); }
  EnrollOutputBn("out", false);
}

LogicalNode* DstSubsetTickOp::NewProperLogicalNode() const {
  return new DstSubsetTickLogicalNode();
}

Maybe<void> DstSubsetTickOp::InferBlobDescs(
    std::function<BlobDesc*(const std::string&)> GetBlobDesc4BnInOp,
    const ParallelContext* parallel_ctx) const {
  CHECK_EQ_OR_RETURN(parallel_ctx->parallel_num(), 1);
  GetBlobDesc4BnInOp("out")->mut_shape() = Shape({1});
  return Maybe<void>::Ok();
}

Maybe<void> DstSubsetTickOp::InferBatchAxis(
    std::function<OptInt64*(const std::string&)> BatchAxis4BnInOp) const {
  BatchAxis4BnInOp("out")->clear_value();
  return Maybe<void>::Ok();
}

Maybe<void> DstSubsetTickOp::GetSbpSignatures(SbpSignatureList* sbp_sig_list) const {
  SbpSignatureBuilder().Split(output_bns(), 0).Build(sbp_sig_list->mutable_sbp_signature()->Add());
  return Maybe<void>::Ok();
}

REGISTER_CPU_OP(OperatorConf::kDstSubsetTickConf, DstSubsetTickOp);
REGISTER_TICK_TOCK_OP(OperatorConf::kDstSubsetTickConf);

}  // namespace oneflow
