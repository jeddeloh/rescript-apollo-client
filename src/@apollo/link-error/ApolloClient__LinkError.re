module ApolloLink = ApolloClient__Link_Core_ApolloLink;
module GraphQLError = ApolloClient__Graphql.Error.GraphQLError;
module ExecutionResult = ApolloClient__Graphql_Execution_Execute.ExecutionResult;
module NextLink = ApolloClient__Link_Core_Types.NextLink;
module Operation = ApolloClient__Link_Core_Types.Operation;
module ServerError = ApolloClient__Link_Utils_ThrowServerError.ServerError;
module ServerParseError = ApolloClient__Link_Http_ParseAndCheckHttpResponse.ServerParseError;
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
      type t;
      let error: Js.Exn.t => t;
      let serverError: ServerError.Js_.t => t;
      let serverParseError: ServerParseError.Js_.t => t;
      type case =
        | Error(Js.Exn.t)
        | ServerError(ServerError.Js_.t)
        | ServerParseError(ServerParseError.Js_.t);
      let classify: t => case;
    } = {
      [@unboxed]
      type t =
        | Any('a): t;
      let error = (v: Js.Exn.t) => Any(v);
      let serverError = (v: ServerError.Js_.t) => Any(v);
      let serverParseError = (v: ServerParseError.Js_.t) => Any(v);
      type case =
        | Error(Js.Exn.t)
        | ServerError(ServerError.Js_.t)
        | ServerParseError(ServerParseError.Js_.t);
      let classify = (Any(v): t): case =>
        if ([%raw {|function (value) { return "bodyText" in value}|}](v)) {
          ServerParseError(Obj.magic(v): ServerParseError.Js_.t);
        } else if ([%raw {|function (value) { return "result" in value}|}](v)) {
          ServerParseError(Obj.magic(v): ServerParseError.Js_.t);
        } else {
          Error(Obj.magic(v): Js.Exn.t);
        };
    };
    type t = {
      graphQLErrors: option(array(GraphQLError.t)),
      networkError: NetworkErrorUnion.t,
      response: ExecutionResult.Js_.t(Js.Json.t),
      operation: Operation.Js_.t,
      forward: NextLink.Js_.t,
    };
  };

  type t = {
    graphQLErrors: option(array(GraphQLError.t)),
    networkError: Js_.NetworkErrorUnion.case,
    response: ExecutionResult.Js_.t(Js.Json.t),
    operation: Operation.Js_.t,
    forward: NextLink.Js_.t,
  };

  let fromJs: Js_.t => t =
    js => {
      graphQLErrors: js.graphQLErrors,
      networkError: js.networkError->Js_.NetworkErrorUnion.classify,
      response: js.response,
      operation: js.operation,
      forward: js.forward,
    };
};

module ErrorHandler = {
  // interface ErrorHandler {
  //     (error: ErrorResponse): Observable<FetchResult> | void;
  // }
  module Js_ = {
    type t = ErrorResponse.Js_.t => unit;
  };

  type t = ErrorResponse.t => unit;
};

module Js_ = {
  // export declare function onError(errorHandler: ErrorHandler): ApolloLink;
  [@bs.module "@apollo/link-error"]
  external onError:
    (ErrorResponse.Js_.t => option(NextLink.Js_.t)) => ApolloLink.Js_.t =
    "onError";
};

let onError: (ErrorResponse.t => option(NextLink.t)) => ApolloLink.t =
  errorCb =>
    Js_.onError(jsErrorResponse =>
      errorCb(jsErrorResponse->ErrorResponse.fromJs)
    );

// Reason-specific
module ErrorLink = {
  let make = onError;
};
