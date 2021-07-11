module Operation = ApolloClient__Link_Core.Types.Operation

module DelayFunction = {
  module Js_ = {
    // export interface DelayFunction {
    //     (count: number, operation: Operation, error: any): number;
    // }
    type t = (int, Operation.Js_.t, option<Js.Json.t>) => int
  }

  type t = (~count: int, ~operation: Operation.t, ~error: option<Js.Json.t>) => int

  let toJs: t => Js_.t = (t, count, operation, error) =>
    t(~count, ~operation=operation->Operation.fromJs, ~error)
}

module DelayFunctionOptions = {
  // export interface DelayFunctionOptions {
  //     initial?: number;
  //     max?: number;
  //     jitter?: boolean;
  // }
  type t = {
    initial: option<int>,
    max: option<int>,
    jitter: option<int>,
  }

  module Js_ = {
    type t = t
  }
}
