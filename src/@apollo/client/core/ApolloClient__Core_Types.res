module ApolloError = ApolloClient__Errors_ApolloError
module Graphql = ApolloClient__Graphql
module FetchResult = ApolloClient__Link_Core_Types.FetchResult
module NetworkStatus = ApolloClient__Core_NetworkStatus.NetworkStatus
module Resolver = ApolloClient__Core_LocalState.Resolver
module Types = ApolloClient__Types
module Utils = ApolloClient__Utils

module OperationVariables = {
  module Js_ = {
    // export declare type OperationVariables = Record<string, any>;
    type t = Js.Json.t
  }
  type t = Js_.t
}

module PureQueryOptions = {
  module Js_ = {
    // export declare type PureQueryOptions = {
    //     query: DocumentNode;
    //     variables?: {
    //         [key: string]: any;
    //     };
    //     context?: any;
    // };
    type t<'jsVariables> = {
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      context: option<Js.Json.t>,
    }
  }

  type t<'jsVariables> = {
    query: Graphql.documentNode,
    variables: 'jsVariables,
    context: option<Js.Json.t>,
  }

  let toJs: t<'jsVariables> => Js_.t<'jsVariables> = t => {
    query: t.query,
    variables: t.variables,
    context: t.context,
  }
}

module ApolloQueryResult = {
  module Js_ = {
    // export declare type ApolloQueryResult<T> = {
    //     data?: T;
    //     errors?: ReadonlyArray<GraphQLError>;
    //     loading: boolean;
    //     networkStatus: NetworkStatus;
    // };
    type t<'jsData> = {
      data: option<'jsData>,
      errors: option<array<Graphql.Error.GraphQLError.t>>,
      loading: bool,
      networkStatus: int,
    }
  }

  type t<'data> = {
    data: option<'data>,
    @ocaml.doc("
     * Intentionally elevated from array(Graphql.Error.GraphQLError.t) to ApolloError.
     * This allows us to incorporate network and parse failures into a single result.
     ")
    error: option<ApolloError.t>,
    loading: bool,
    networkStatus: NetworkStatus.t,
  }

  let fromJs: (Js_.t<'jsData>, ~safeParse: Types.safeParse<'data, 'jsData>) => t<'data> = (
    js,
    ~safeParse,
  ) => {
    let (data, error) = Utils.safeParseAndLiftToCommonResultProps(
      ~jsData=js.data,
      ~graphQLErrors=?js.errors,
      safeParse,
    )

    {
      data: data,
      error: error,
      loading: js.loading,
      networkStatus: js.networkStatus->NetworkStatus.fromJs,
    }
  }

  let fromError: ApolloError.t => t<'data> = error => {
    data: None,
    error: Some(error),
    loading: false,
    networkStatus: Error,
  }

  type t__ok<'data> = {
    data: 'data,
    error: option<ApolloError.t>,
    loading: bool,
    networkStatus: NetworkStatus.t,
  }

  let toResult: t<'data> => Belt.Result.t<t__ok<'data>, ApolloError.t> = apolloQueryResult =>
    switch apolloQueryResult {
    | {data: Some(data)} =>
      Ok({
        data: data,
        error: apolloQueryResult.error,
        loading: apolloQueryResult.loading,
        networkStatus: apolloQueryResult.networkStatus,
      })
    | {error: Some(error)} => Error(error)
    | {data: None, error: None} =>
      Error(
        ApolloError.make(
          ~errorMessage="No data and no error on ApolloQueryResult.t. Shouldn't this be impossible?",
          (),
        ),
      )
    }
}

module MutationQueryReducer = {
  module Js_ = {
    // export declare type MutationQueryReducer<T> = (previousResult: Record<string, any>, options: {
    //     mutationResult: FetchResult<T>;
    //     queryName: string | undefined;
    //     queryVariables: Record<string, any>;
    // }) => Record<string, any>;
    type options<'jsData> = {
      mutationResult: FetchResult.Js_.t<'jsData>,
      queryName: option<string>,
      queryVariables: Js.Json.t, // ACTUAL: Record<string, any>
    }

    type t<'jsData> = (. Js.Json.t, options<'jsData>) => Js.Json.t
  }

  type options<'data> = {
    mutationResult: FetchResult.t<'data>,
    queryName: option<string>,
    queryVariables: Js.Json.t, // ACTUAL: Record<string, any>
  }

  type t<'data> = (Js.Json.t, options<'data>) => Js.Json.t

  let toJs: (
    t<'data>,
    ~safeParse: Types.safeParse<'data, 'jsData>,
    . Js.Json.t,
    Js_.options<'jsData>,
  ) => Js.Json.t = (t, ~safeParse, . previousResult, jsOptions) =>
    t(
      previousResult,
      {
        mutationResult: jsOptions.mutationResult->FetchResult.fromJs(~safeParse),
        queryName: jsOptions.queryName,
        queryVariables: jsOptions.queryVariables,
      },
    )
}

module MutationQueryReducersMap = {
  module Js_ = {
    // export declare type MutationQueryReducersMap<T = {
    //     [key: string]: any;
    // }> = {
    //     [queryName: string]: MutationQueryReducer<T>;
    // };
    type t<'jsData> = Js.Dict.t<MutationQueryReducer.Js_.t<'jsData>>
  }

  type t<'data> = Js.Dict.t<MutationQueryReducer.t<'data>>

  let toJs: (t<'data>, ~safeParse: Types.safeParse<'data, 'jsData>) => Js_.t<'jsData> = (
    t,
    ~safeParse,
  ) =>
    Js.Dict.map(
      (. mutationQueryReducer) => mutationQueryReducer->MutationQueryReducer.toJs(~safeParse),
      t,
    )
}

module Resolvers = {
  module Js_ = {
    // export interface Resolvers {
    //     [key: string]: {
    //         [field: string]: Resolver;
    //     };
    // }
    type t = Js.Dict.t<Js.Dict.t<Resolver.Js_.t>>
  }
  type t = Js_.t
}
