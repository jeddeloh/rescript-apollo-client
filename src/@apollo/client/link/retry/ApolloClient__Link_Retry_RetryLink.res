module ApolloLink = ApolloClient__Link_Core_ApolloLink
module DelayFunctionOptions = ApolloClient__Link_Retry_DelayFunction.DelayFunctionOptions
module DelayFunction = ApolloClient__Link_Retry_DelayFunction.DelayFunction
module RetryFunctionOptions = ApolloClient__Link_Retry_RetryFunction.RetryFunctionOptions
module RetryFunction = ApolloClient__Link_Retry_RetryFunction.RetryFunction

module Options = {
  module Js_ = {
    module T_delayUnion: {
      type t
      let delayFunctionOptions: DelayFunctionOptions.Js_.t => t
      let delayFunction: (. DelayFunction.Js_.t) => t
    } = {
      @unboxed
      type rec t = Any('a): t
      let delayFunctionOptions = (v: DelayFunctionOptions.Js_.t) => Any(v)
      let delayFunction = (. v: DelayFunction.Js_.t) => Any(v)
    }

    module T_attemptsUnion: {
      type t
      let retryFunctionOptions: RetryFunctionOptions.Js_.t => t
      let retryFunction: (. RetryFunction.Js_.t) => t
    } = {
      @unboxed
      type rec t = Any('a): t
      let retryFunctionOptions = (v: RetryFunctionOptions.Js_.t) => Any(v)
      let retryFunction = (. v: RetryFunction.Js_.t) => Any(v)
    }

    // export declare namespace RetryLink {
    //     interface Options {
    //         delay?: DelayFunctionOptions | DelayFunction;
    //         attempts?: RetryFunctionOptions | RetryFunction;
    //     }
    // }
    type t = {
      delay?: T_delayUnion.t,
      attempts?: T_attemptsUnion.t,
    }
  }

  type t_delay = DelayFunctionOptions(DelayFunctionOptions.t) | DelayFunction(DelayFunction.t)
  type t_attempts = RetryFunctionOptions(RetryFunctionOptions.t) | RetryFunction(RetryFunction.t)

  type t = {
    delay?: t_delay,
    attempts?: t_attempts,
  }

  let toJs: t => Js_.t = t => {
    delay: ?t.delay->Belt.Option.mapU((. delay) =>
      switch delay {
      | DelayFunctionOptions(delayFunctionOptions) =>
        Js_.T_delayUnion.delayFunctionOptions(delayFunctionOptions)
      | DelayFunction(delayFunction) =>
        Js_.T_delayUnion.delayFunction(. DelayFunction.toJs(. delayFunction))
      }
    ),
    attempts: ?t.attempts->Belt.Option.mapU((. attempts) =>
      switch attempts {
      | RetryFunctionOptions(retryFunctionOptions) =>
        Js_.T_attemptsUnion.retryFunctionOptions(retryFunctionOptions->RetryFunctionOptions.toJs)
      | RetryFunction(retryFunction) =>
        Js_.T_attemptsUnion.retryFunction(. RetryFunction.toJs(. retryFunction))
      }
    ),
  }
}

module Js_ = {
  // export declare class RetryLink extends ApolloLink {
  //     private delayFor;
  //     private retryIf;
  //     constructor(options?: RetryLink.Options);
  //     request(operation: Operation, nextLink: NextLink): Observable<FetchResult>;
  // }
  @module("@apollo/client/link/retry") @new
  external make: Options.Js_.t => ApolloLink.Js_.t = "RetryLink"
}

let make = (~attempts=?, ~delay=?, ()) =>
  Js_.make(
    Options.toJs({
      ?attempts,
      ?delay,
    }),
  )
