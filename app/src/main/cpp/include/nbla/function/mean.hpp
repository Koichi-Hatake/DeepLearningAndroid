// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/** Mean
 */
#ifndef __NBLA_FUNCTION_MEAN_HPP__
#define __NBLA_FUNCTION_MEAN_HPP__

#include <nbla/function/sum.hpp>

namespace nbla {

NBLA_REGISTER_FUNCTION_HEADER(Mean, const vector<int> &, bool);

/** Reduction along axes with mean operation.

@tparam T Data type for computation.
@param axes A list of axes to be reduced.
@param keep_dims Flag whether the reduced axes are kept.

\ingroup FunctionImplGrp
 */
template <typename T> class Mean : public Sum<T> {

public:
  Mean(const Context &ctx, const vector<int> &axes, bool keep_dims)
      : Sum<T>(ctx, axes, keep_dims) {}
  virtual ~Mean() {}
  virtual shared_ptr<Function> copy() const {
    return create_Mean(this->ctx_, this->axes_, this->keep_dims_);
  }
  virtual string name() { return "Mean"; }

protected:
  NBLA_API virtual void forward_impl_reduce(const T *x, T *y, int outer_size,
                                            int reduction_size);
  NBLA_API virtual void backward_impl_reduce(const T *dy, T *dx, int outer_size,
                                             int reduction_size, bool accum);
};
}
#endif
