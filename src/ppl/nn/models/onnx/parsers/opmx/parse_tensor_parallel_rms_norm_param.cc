// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "ppl/nn/models/onnx/parsers/opmx/parse_tensor_parallel_rms_norm_param.h"
#include "ppl/nn/common/logger.h"
#include "ppl/nn/models/onnx/utils.h"
using namespace std;
using namespace ppl::common;
using namespace ppl::nn::opmx;

namespace ppl { namespace nn { namespace opmx {

RetCode ParseTensorParallelRMSNormParam(const ::onnx::NodeProto& pb_node, const onnx::ParamParserExtraArgs& args, ir::Node* node,
                                  ir::Attr* arg) {
    auto param = static_cast<ppl::nn::opmx::TensorParallelRMSNormParam*>(arg);
    onnx::utils::GetNodeAttr(pb_node, "scale", &param->scale, 1.0);
    onnx::utils::GetNodeAttr(pb_node, "axis", &param->axis, -1);
    onnx::utils::GetNodeAttr(pb_node, "eps", &param->eps, 1e-5);
    return RC_SUCCESS;
}

}}} // namespace ppl::nn::opmx
