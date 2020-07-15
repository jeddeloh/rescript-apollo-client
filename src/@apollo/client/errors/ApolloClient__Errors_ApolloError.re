module Graphql = ApolloClient__Graphql;
module GraphQLError = ApolloClient__Graphql.Error.GraphQLError;
module LinkError = ApolloClient__LinkError;

module Js_ = {
  // export declare class ApolloError extends Error {
  //     message: string;
  //     graphQLErrors: ReadonlyArray<GraphQLError>;
  //     networkError: Error | null;
  //     extraInfo: any;
  // }
  type t = {
    extraInfo: Js.Json.t,
    graphQLErrors: array(Graphql.Error.GraphQLError.t),
    networkError:
      Js.nullable(LinkError.ErrorResponse.Js_.NetworkErrorUnion.t),
    // ...extends Error
    name: string,
    message: string,
    stack: option(string),
  };

  type make_args = {
    graphQLErrors: option(array(GraphQLError.t)),
    networkError:
      Js.nullable(LinkError.ErrorResponse.Js_.NetworkErrorUnion.t),
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

type t = {
  extraInfo: Js.Json.t,
  graphQLErrors: array(Graphql.Error.GraphQLError.t),
  networkError: option(LinkError.ErrorResponse.t_networkError),
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
      ->Belt.Option.map(
          LinkError.ErrorResponse.Js_.NetworkErrorUnion.classify,
        ),
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
          networkError->Belt.Option.map(
            LinkError.ErrorResponse.Js_.NetworkErrorUnion.error,
          ),
        ),
      errorMessage,
      extraInfo,
    })
    ->fromJs;
