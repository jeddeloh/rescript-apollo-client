module ApolloLink = ApolloClient__Link_Core_ApolloLink
module ApolloError = ApolloClient__Errors_ApolloError
module GraphQLError = ApolloClient__Graphql.Error.GraphQLError
module ExecutionResult = ApolloClient__Graphql_Execution_Execute.ExecutionResult
module FetchResult = ApolloClient__Link_Core_Types.FetchResult
module NextLink = ApolloClient__Link_Core_Types.NextLink
module Observable = ApolloClient__ZenObservable.Observable
module Operation = ApolloClient__Link_Core_Types.Operation
module ServerError = ApolloClient__Link_Utils_ThrowServerError.ServerError
module ServerParseError = ApolloClient__Link_Http_ParseAndCheckHttpResponse.ServerParseError

// export declare class ErrorLink extends ApolloLink {
//     private link;
//     constructor(errorHandler: ErrorLink.ErrorHandler);
//     request(operation: Operation, forward: NextLink): Observable<FetchResult> | null;
// }

module ErrorResponse = {
  // export interface ErrorResponse {
  //     graphQLErrors?: ReadonlyArray<GraphQLError>;
  //     networkError?: Error | ServerError | ServerParseError;
  //     response?: ExecutionResult;
  //     operation: Operation;
  //     forward: NextLink;
  // }
  module Js_ = {
    module NetworkErrorUnion: {
      type t
      let error: Js.Exn.t => t
      let serverError: ServerError.Js_.t => t
      let serverParseError: ServerParseError.Js_.t => t
      type case =
        | Error(Js.Exn.t)
        | ServerError(ServerError.Js_.t)
        | ServerParseError(ServerParseError.Js_.t)
      let classify: t => case
    } = {
      @unboxed
      type rec t = Any('a): t
      let error = (v: Js.Exn.t) => Any(v)
      let serverError = (v: ServerError.Js_.t) => Any(v)
      let serverParseError = (v: ServerParseError.Js_.t) => Any(v)
      type case =
        | Error(Js.Exn.t)
        | ServerError(ServerError.Js_.t)
        | ServerParseError(ServerParseError.Js_.t)
      let classify = (Any(v): t): case =>
        if (
          %raw(`function (v) { return "bodyText" in v && "response" in v && "statusCode" in v}`)(v)
        ) {
          ServerError((Obj.magic(v): ServerError.Js_.t))
        } else if (
          %raw(`function (v) { return "result" in v && "response" in v && "statusCode" in v}`)(v)
        ) {
          ServerParseError((Obj.magic(v): ServerParseError.Js_.t))
        } else {
          Error((Obj.magic(v): Js.Exn.t))
        }
    }

    type t = {
      graphQLErrors: option<array<GraphQLError.t>>,
      networkError: option<NetworkErrorUnion.t>,
      response: option<ExecutionResult.Js_.t<Js.Json.t>>,
      operation: Operation.Js_.t,
    }

    @send
    external forward: (t, Operation.t) => Observable.Js_.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t> =
      "forward"
  }

  type t_networkError =
    | FetchFailure(Js.Exn.t)
    | BadStatus(int, ServerError.t)
    | BadBody(ServerParseError.t)

  type t = {
    graphQLErrors: option<array<GraphQLError.t>>,
    networkError: option<t_networkError>,
    response: option<ExecutionResult.t<Js.Json.t>>,
    operation: Operation.t,
    forward: NextLink.t,
  }

  let fromJs: Js_.t => t = js => {
    graphQLErrors: js.graphQLErrors,
    networkError: js.networkError->Belt.Option.map(networkError =>
      switch networkError->Js_.NetworkErrorUnion.classify {
      | Error(error) => FetchFailure(error)
      | ServerError(error) => BadStatus(error.statusCode, error)
      | ServerParseError(error) => BadBody(error)
      }
    ),
    response: js.response,
    operation: js.operation->Operation.fromJs,
    forward: operation => js->Js_.forward(operation),
  }
}

module ErrorHandler = {
  // interface ErrorHandler {
  //     (error: ErrorResponse): Observable<FetchResult> | void;
  // }
  module Js_ = {
    type t = ErrorResponse.Js_.t => option<Observable.Js_.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>>
  }

  type t = ErrorResponse.t => option<Observable.Js_.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>>
}

module Js_ = {
  // export declare function onError(errorHandler: ErrorHandler): ApolloLink;
  @module("@apollo/client/link/error")
  external onError: (
    ErrorResponse.Js_.t => option<Observable.Js_.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>>
  ) => ApolloLink.Js_.t = "onError"
}

let onError: ErrorHandler.t => ApolloLink.t = errorCb =>
  Js_.onError(jsErrorResponse => errorCb(jsErrorResponse->ErrorResponse.fromJs))

// rescript-specific
module ErrorLink = {
  let make = onError
}
