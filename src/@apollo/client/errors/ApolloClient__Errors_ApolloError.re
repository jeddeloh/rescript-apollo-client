module Graphql = ApolloClient__Graphql;
module GraphQLError = ApolloClient__Graphql.Error.GraphQLError;
module ServerError = ApolloClient__Link_Utils_ThrowServerError.ServerError;
module ServerParseError = ApolloClient__Link_Http_ParseAndCheckHttpResponse.ServerParseError;

module Js_ = {
  module NetworkErrorUnion: {
    // This is copied from `@apollo/link-error`
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
      if ([%raw
            {|function (v) { return "bodyText" in v && "response" in v && "statusCode" in v}|}
          ](
            v,
          )) {
        ServerError(Obj.magic(v): ServerError.Js_.t);
      } else if ([%raw
                   {|function (v) { return "result" in v && "response" in v && "statusCode" in v}|}
                 ](
                   v,
                 )) {
        ServerParseError(Obj.magic(v): ServerParseError.Js_.t);
      } else {
        Error(Obj.magic(v): Js.Exn.t);
      };
  };
  // export declare class ApolloError extends Error {
  //     message: string;
  //     graphQLErrors: ReadonlyArray<GraphQLError>;
  //     networkError: Error | null;
  //     extraInfo: any;
  // }
  type t = {
    extraInfo: Js.Json.t,
    graphQLErrors: array(Graphql.Error.GraphQLError.t),
    networkError: Js.nullable(NetworkErrorUnion.t), // ACTUAL: Error | null
    // ...extends Error
    name: string,
    message: string,
    stack: option(string),
  };

  type make_args = {
    graphQLErrors: option(array(GraphQLError.t)),
    networkError: Js.nullable(NetworkErrorUnion.t),
    errorMessage: option(string),
    extraInfo: option(Js.Json.t),
  };

  //     constructor({ graphQLErrors, networkError, errorMessage, extraInfo, }: {
  //         graphQLErrors?: ReadonlyArray<GraphQLError>;
  //         networkError?: Error | null;
  //         errorMessage?: string;
  //         extraInfo?: any;
  //     });
  [@bs.module "@apollo/client"] [@bs.new]
  external make: make_args => t = "ApolloError";
};

type t_networkError =
  Js_.NetworkErrorUnion.case =
    // This is a catch-all for any error coming from a fetch call that is not the other two
    | Error(Js.Exn.t)
    // ServerError means you got a bad code
    | ServerError(ServerError.t)
    // ServerParseError means apollo couldn't JSON.parse the body
    | ServerParseError(ServerParseError.t);

type t = {
  extraInfo: Js.Json.t,
  graphQLErrors: array(Graphql.Error.GraphQLError.t),
  networkError: option(t_networkError),
  name: string,
  message: string,
  stack: option(string),
};

let fromJs: Js_.t => t =
  js => {
    extraInfo: js.extraInfo,
    graphQLErrors: js.graphQLErrors,
    networkError:
      js.networkError
      ->Js.toOption
      ->Belt.Option.map(Js_.NetworkErrorUnion.classify),
    name: js.name,
    message: js.message,
    stack: js.stack,
  };

let make:
  (
    ~graphQLErrors: array(GraphQLError.t)=?,
    ~networkError: Js.Exn.t=?,
    ~errorMessage: string=?,
    ~extraInfo: Js.Json.t=?,
    unit
  ) =>
  t =
  (~graphQLErrors=?, ~networkError=?, ~errorMessage=?, ~extraInfo=?, ()) =>
    Js_.make({
      graphQLErrors,
      networkError:
        Js.Nullable.fromOption(
          networkError->Belt.Option.map(Js_.NetworkErrorUnion.error),
        ),
      errorMessage,
      extraInfo,
    })
    ->fromJs;
