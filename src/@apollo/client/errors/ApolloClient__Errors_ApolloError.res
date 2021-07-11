module Graphql = ApolloClient__Graphql
module GraphQLError = ApolloClient__Graphql.Error.GraphQLError
module ServerError = ApolloClient__Link_Utils_ThrowServerError.ServerError
module ServerParseError = ApolloClient__Link_Http_ParseAndCheckHttpResponse.ServerParseError
module Types = ApolloClient__Types

@unboxed
type rec any = Any('a): any

let ensureError: any => Js.Exn.t = %raw(`
  function (unknown) {
    if (unknown instanceof Error) {
      return unknown;
    } else {
      unknown = unknown || {};
      const message = unknown.message;
      const errorMessage = unknown.errorMessage;
      const keys = Object.keys(unknown);
      const error = new Error(message || errorMessage || "[Non-error exception with keys: " + keys.join(", ") + "]");

      keys.forEach(function(key) {
        error[key] = unknown[key];
      });

      return error;
    }
  }
  `)

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
      if %raw(`function (v) { return "bodyText" in v && "response" in v && "statusCode" in v}`)(v) {
        ServerError((Obj.magic(v): ServerError.Js_.t))
      } else if (
        %raw(`function (v) { return "result" in v && "response" in v && "statusCode" in v}`)(v)
      ) {
        ServerParseError((Obj.magic(v): ServerParseError.Js_.t))
      } else {
        Error((Obj.magic(v): Js.Exn.t))
      }
  }
  // export declare class ApolloError extends Error {
  //     message: string;
  //     graphQLErrors: ReadonlyArray<GraphQLError>;
  //     networkError: Error | ServerParseError | ServerError | null;
  //     extraInfo: any;
  // }
  type t = {
    extraInfo: Js.Json.t,
    @ocaml.doc("
     This is not actually optional, but apollo-client casts an any to ApolloError in
     SubscriptionData, and doesn't check the error at all which results in GraphQLErrors
     masquerading as ApolloErrors (no graphqlErrors property).
     See: https://github.com/apollographql/apollo-client/pull/6894
     ")
    graphQLErrors: option<array<Graphql.Error.GraphQLError.t>>,
    networkError: Js.nullable<NetworkErrorUnion.t>,
    // ...extends Error
    name: string,
    message: string,
    stack: option<string>,
  }

  type make_args = {
    graphQLErrors: option<array<GraphQLError.t>>,
    networkError: Js.nullable<NetworkErrorUnion.t>,
    errorMessage: option<string>,
    extraInfo: option<Js.Json.t>,
  }

  // constructor({ graphQLErrors, networkError, errorMessage, extraInfo, }: {
  //     graphQLErrors?: ReadonlyArray<GraphQLError>;
  //     networkError?: Error | ServerParseError | ServerError | null;
  //     errorMessage?: string;
  //     extraInfo?: any;
  // });
  @module("@apollo/client") @new
  external make: make_args => t = "ApolloError"

  // This is not an exhaustive check. It is intended to address the most common subscription error issues only
  // See: https://github.com/apollographql/apollo-client/pull/6894
  let ensureApolloError: t => t = error =>
    %raw(`
          function (error, makeApolloError, ensureError) {
            var error = error || {};
            if (Array.isArray(error.graphQLErrors)) {
              return error;
            } else if (error && typeof error.message === "string" && error.extensions) {
              return makeApolloError({graphQLErrors: [error]});
            } else {
              return makeApolloError({networkError: ensureError(error)}) 
            }
          }
        `)(error, make, ensureError)
}

type t_networkError =
  /* Fetch threw an error for some reason and we caught it */
  | FetchFailure(Js.Exn.t)
  /* Fetch got a response, but the status code was >=300 */
  | BadStatus(int, ServerError.t)
  /* Fetch got a response, but it wasn't JSON */
  | BadBody(ServerParseError.t)
  /* We got a JSON response, but it wasn't in a shape we could parse */
  | ParseError(Types.parseError) // ParseError is rescript-apollo-client only

type t = {
  extraInfo: Js.Json.t,
  graphQLErrors: array<Graphql.Error.GraphQLError.t>,
  networkError: option<t_networkError>,
  name: string,
  message: string,
  stack: option<string>,
}

let fromJs: Js_.t => t = untrustedJs => {
  let js = Js_.ensureApolloError(untrustedJs)
  {
    extraInfo: js.extraInfo,
    graphQLErrors: js.graphQLErrors->Belt.Option.getWithDefault([]),
    networkError: js.networkError
    ->Js.toOption
    ->Belt.Option.map(networkError =>
      switch networkError->Js_.NetworkErrorUnion.classify {
      | Error(error) => FetchFailure(error)
      | ServerError(error) => BadStatus(error.statusCode, error)
      | ServerParseError(error) => BadBody(error)
      }
    ),
    name: js.name,
    message: js.message,
    stack: js.stack,
  }
}

let make: (
  ~graphQLErrors: array<GraphQLError.t>=?,
  ~networkError: t_networkError=?,
  ~errorMessage: string=?,
  ~extraInfo: Js.Json.t=?,
  unit,
) => t = (~graphQLErrors=?, ~networkError=?, ~errorMessage=?, ~extraInfo=?, ()) => {
  let errorWithoutNetworkError = Js_.make({
    graphQLErrors: graphQLErrors,
    networkError: Js.Nullable.undefined,
    errorMessage: errorMessage,
    extraInfo: extraInfo,
  })->fromJs

  {...errorWithoutNetworkError, networkError: networkError}
}
