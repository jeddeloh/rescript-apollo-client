module Operation = ApolloClient__Link_Core.Types.Operation

module RetryFunction = {
  module Js_ = {
    // export interface RetryFunction {
    //     (count: number, operation: Operation, error: any): boolean | Promise<boolean>;
    // }
    type t = (int, Operation.Js_.t, option<Js.Json.t>) => Js.Promise.t<bool>
  }

  type t = (~count: int, ~operation: Operation.t, ~error: option<Js.Json.t>) => Js.Promise.t<bool>

  let toJs: t => Js_.t = (t, count, operation, error) =>
    t(~count, ~operation=operation->Operation.fromJs, ~error)
}

module RetryFunctionOptions = {
  module Js_ = {
    // export interface RetryFunctionOptions {
    //     max?: number;
    //     retryIf?: (error: any, operation: Operation) => boolean | Promise<boolean>;
    // }
    type t = {
      max: option<int>,
      retryIf: (option<Js.Json.t>, Operation.Js_.t) => Js.Promise.t<bool>,
    }
  }

  type t = {
    max: option<int>,
    retryIf: (~error: option<Js.Json.t>, ~operation: Operation.t) => Js.Promise.t<bool>,
  }

  let toJs: t => Js_.t = t => {
    max: t.max,
    retryIf: (error, operation) => t.retryIf(~error, ~operation=operation->Operation.fromJs),
  }
}
