module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache
module FetchResult = ApolloClient__Link_Core_Types.FetchResult
module Graphql = ApolloClient__Graphql
module MutationQueryReducersMap = ApolloClient__Core_Types.MutationQueryReducersMap
module Types = ApolloClient__Types
module PureQueryOptions = ApolloClient__Core_Types.PureQueryOptions

module ErrorPolicy = {
  module Js_ = {
    // export declare type ErrorPolicy = 'none' | 'ignore' | 'all';
    type t = string
  }

  type t =
    | None
    | Ignore
    | All

  let toJs = x =>
    switch x {
    | None => "none"
    | Ignore => "ignore"
    | All => "all"
    }
}

module FetchPolicy = {
  module Js_ = {
    // export declare type FetchPolicy = 'cache-first' | 'network-only' | 'cache-only' | 'no-cache' | 'standby';
    type t = string
  }

  type t =
    | CacheFirst
    | CacheOnly
    | NetworkOnly
    | NoCache
    | Standby

  let toJs = x =>
    switch x {
    | CacheFirst => "cache-first"
    | CacheOnly => "cache-only"
    | NetworkOnly => "network-only"
    | NoCache => "no-cache"
    | Standby => "standby"
    }
}

module FetchPolicy__noCacheExtracted = {
  module Js_ = {
    // Extract<FetchPolicy, 'no-cache'>
    type t = string
  }
  type t = NoCache

  let toJs = x =>
    switch x {
    | NoCache => "no-cache"
    }
}

module WatchQueryFetchPolicy = {
  module Js_ = {
    // export declare type WatchQueryFetchPolicy = FetchPolicy | 'cache-and-network';
    type t = string
  }

  type t =
    | CacheAndNetwork
    | CacheFirst
    | CacheOnly
    | NetworkOnly
    | NoCache
    | Standby

  let toJs = x =>
    switch x {
    | CacheAndNetwork => "cache-and-network"
    | CacheFirst => "cache-first"
    | CacheOnly => "cache-only"
    | NetworkOnly => "network-only"
    | NoCache => "no-cache"
    | Standby => "standby"
    }
}

module QueryOptions = {
  module Js_ = {
    type t<'jsVariables> = {
      fetchPolicy: option<FetchPolicy.Js_.t>,
      // ...extends QueryBaseOptions
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      errorPolicy: option<ErrorPolicy.Js_.t>,
      context: option<Js.Json.t>,
    }
  }

  type t<'jsVariables> = {
    fetchPolicy: option<FetchPolicy.t>,
    query: Graphql.documentNode,
    variables: 'jsVariables,
    errorPolicy: option<ErrorPolicy.t>,
    context: option<Js.Json.t>,
  }

  let toJs: (
    t<'variables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables,
    ~serializeVariables: 'variables => 'jsVariables,
  ) => Js_.t<'jsVariables> = (t, ~mapJsVariables, ~serializeVariables) => {
    fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy.toJs),
    query: t.query,
    variables: t.variables->serializeVariables->mapJsVariables,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    context: t.context,
  }
}

module WatchQueryOptions = {
  module Js_ = {
    type t<'jsVariables> = {
      fetchPolicy: option<WatchQueryFetchPolicy.Js_.t>,
      nextFetchPolicy: option<WatchQueryFetchPolicy.Js_.t>,
      // ...extends QueryBaseOptions
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      errorPolicy: option<ErrorPolicy.Js_.t>,
      context: option<Js.Json.t>,
      pollInterval: option<int>,
    }
  }

  type t<'jsVariables> = {
    fetchPolicy: option<WatchQueryFetchPolicy.t>,
    nextFetchPolicy: option<WatchQueryFetchPolicy.t>,
    query: Graphql.documentNode,
    variables: 'jsVariables,
    errorPolicy: option<ErrorPolicy.t>,
    context: option<Js.Json.t>,
    pollInterval: option<int>,
  }

  let toJs: (
    t<'variables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables,
    ~serializeVariables: 'variables => 'jsVariables,
  ) => Js_.t<'jsVariables> = (t, ~mapJsVariables, ~serializeVariables) => {
    fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    nextFetchPolicy: t.nextFetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    query: t.query,
    variables: t.variables->serializeVariables->mapJsVariables,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    context: t.context,
    pollInterval: t.pollInterval,
  }
}

module UpdateQueryFn = {
  module Js_ = {
    type t_options_subscriptionData<'jsSubscriptionData> = {data: 'jsSubscriptionData}
    type t_options<'jsSubscriptionData, 'jsVariables> = {
      subscriptionData: t_options_subscriptionData<'jsSubscriptionData>,
    }
    // export declare type UpdateQueryFn<TData = any, TSubscriptionVariables = OperationVariables, TSubscriptionData = TData> = (previousQueryResult: TData, options: {
    //     subscriptionData: {
    //         data: TSubscriptionData;
    //     };
    //     variables?: TSubscriptionVariables;
    // }) => TData;
    type t<'jsQueryData, 'subscriptionVariables, 'jsSubscriptionData> = (
      . 'jsQueryData,
      t_options<'jsSubscriptionData, 'subscriptionVariables>,
    ) => 'jsQueryData
  }
  type t_options_subscriptionData<'jsSubscriptionData> = {data: 'jsSubscriptionData}
  type t_options<'jsSubscriptionData, 'jsVariables> = {
    subscriptionData: t_options_subscriptionData<'jsSubscriptionData>,
  }

  type t<'queryData, 'subscriptionVariables, 'subscriptionData> = (
    'queryData,
    t_options<'subscriptionData, 'subscriptionVariables>,
  ) => 'queryData

  let toJs: (
    t<'queryData, 'subscriptionVariables, 'subscriptionData>,
    ~onParseError: Types.parseError => unit,
    ~querySafeParse: Types.safeParse<'queryData, 'jsQueryData>,
    ~querySerialize: 'queryData => 'jsQueryData,
    ~subscriptionSafeParse: Types.safeParse<'subscriptionData, 'jsSubscriptionData>,
  ) => Js_.t<'jsQueryData, 'subscriptionVariables, 'jsSubscriptionData> = (
    t,
    ~onParseError,
    ~querySafeParse,
    ~querySerialize,
    ~subscriptionSafeParse,
    . jsQueryData,
    {subscriptionData: {data}},
  ) =>
    switch (jsQueryData->querySafeParse, data->subscriptionSafeParse) {
    | (Ok(queryData), Ok(subscriptionData)) =>
      t(
        queryData,
        {
          subscriptionData: {
            data: subscriptionData,
          },
        },
      )->querySerialize
    | (Error(parseError), _)
    | (_, Error(parseError)) =>
      onParseError(parseError)
      jsQueryData
    }
}

module SubscribeToMoreOptions = {
  module Js_ = {
    // export declare type SubscribeToMoreOptions<TData = any, TSubscriptionVariables = OperationVariables, TSubscriptionData = TData> = {
    //     document: DocumentNode;
    //     variables?: TSubscriptionVariables;
    //     updateQuery?: UpdateQueryFn<TData, TSubscriptionVariables, TSubscriptionData>;
    //     onError?: (error: Error) => void;
    //     context?: Record<string, any>;
    // };

    type t<'jsQueryData, 'subscriptionVariables, 'jsSubscriptionData> = {
      document: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'subscriptionVariables,
      updateQuery: option<
        UpdateQueryFn.Js_.t<'jsQueryData, 'subscriptionVariables, 'jsSubscriptionData>,
      >,
      onError: option<Js.Exn.t => unit>,
      context: option<Js.Json.t>,
    }
  }

  type t<'queryData, 'subscriptionVariables, 'subscriptionData> = {
    document: Graphql.documentNode,
    variables: 'subscriptionVariables,
    updateQuery: option<UpdateQueryFn.t<'queryData, 'subscriptionVariables, 'subscriptionData>>,
    onError: option<Js.Exn.t => unit>,
    context: option<Js.Json.t>,
  }

  let toJs: (
    t<'queryData, 'subscriptionVariables, 'subscriptionData>,
    ~onUpdateQueryParseError: Types.parseError => unit,
    ~querySafeParse: Types.safeParse<'queryData, 'jsQueryData>,
    ~querySerialize: 'queryData => 'jsQueryData,
    ~subscriptionSafeParse: Types.safeParse<'subscriptionData, 'jsSubscriptionData>,
  ) => Js_.t<'jsQueryData, 'subscriptionVariables, 'jsSubscriptionData> = (
    t,
    ~onUpdateQueryParseError,
    ~querySafeParse,
    ~querySerialize,
    ~subscriptionSafeParse,
  ) => {
    document: t.document,
    variables: t.variables,
    updateQuery: t.updateQuery->Belt.Option.map(
      UpdateQueryFn.toJs(
        ~onParseError=onUpdateQueryParseError,
        ~querySafeParse,
        ~querySerialize,
        ~subscriptionSafeParse,
      ),
    ),
    onError: t.onError,
    context: t.context,
  }
}

module SubscriptionOptions = {
  module Js_ = {
    // export interface SubscriptionOptions<TVariables = OperationVariables, TData = any> {
    //     query: DocumentNode | TypedDocumentNode<TData, TVariables>;
    //     variables?: TVariables;
    //     fetchPolicy?: FetchPolicy;
    //     errorPolicy?: ErrorPolicy;
    //     context?: Record<string, any>;
    // }
    type t<'jsVariables> = {
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      fetchPolicy: option<FetchPolicy.Js_.t>,
      errorPolicy: option<ErrorPolicy.Js_.t>,
      context: option<Js.Json.t>,
    }
  }

  type t<'variables> = {
    query: Graphql.documentNode,
    variables: 'variables,
    fetchPolicy: option<FetchPolicy.t>,
    errorPolicy: option<ErrorPolicy.t>,
    context: option<Js.Json.t>,
  }

  let toJs: (
    t<'variables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables,
    ~serializeVariables: 'varibles => 'jsVariables,
  ) => Js_.t<'jsVariables> = (t, ~mapJsVariables, ~serializeVariables) => {
    query: t.query,
    variables: t.variables->serializeVariables->mapJsVariables,
    fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy.toJs),
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    context: t.context,
  }
}

module MutationUpdaterFn = {
  module Js_ = {
    type t<'jsData> = (. ApolloCache.t<Js.Json.t>, FetchResult.Js_.t<'jsData>) => unit // Non-Js_ cache is correct here
  }

  type t<'data> = (ApolloCache.t<Js.Json.t>, FetchResult.t<'data>) => unit

  let toJs: (t<'data>, ~safeParse: Types.safeParse<'data, 'jsData>) => Js_.t<'jsData> = (
    mutationUpdaterFn,
    ~safeParse,
    . cache,
    jsFetchResult,
  ) => mutationUpdaterFn(cache, jsFetchResult->FetchResult.fromJs(~safeParse))
}

module RefetchQueryDescription = {
  module Js_ = {
    module Union: {
      type t
      let string: string => t
      let pureQueryOptions: PureQueryOptions.Js_.t<_> => t
    } = {
      @unboxed
      type rec t = Any('a): t
      let string = (v: string) => Any(v)
      let pureQueryOptions = (v: PureQueryOptions.Js_.t<_>) => Any(v)
    }

    type t = array<Union.t>
  }

  type rec t_variant =
    | PureQueryOptions(PureQueryOptions.t<'jsVariables>): t_variant
    | String(string): t_variant

  type t = array<t_variant>

  let toJs: t => Js_.t = Belt.Array.map(_, x =>
    switch x {
    | PureQueryOptions(options) => Js_.Union.pureQueryOptions(options->PureQueryOptions.toJs)
    | String(string) => Js_.Union.string(string)
    }
  )
}

module MutationOptions = {
  module Js_ = {
    // export interface MutationOptions<T = {
    //     [key: string]: any;
    // }, TVariables = OperationVariables> extends MutationBaseOptions<T, TVariables> {
    //     mutation: DocumentNode;
    //     context?: any;
    //     fetchPolicy?: Extract<FetchPolicy, 'no-cache'>;
    // }
    type t<'jsData, 'jsVariables> = {
      mutation: Graphql.documentNode,
      context: option<Js.Json.t>,
      fetchPolicy: option<FetchPolicy__noCacheExtracted.Js_.t>,
      // ...extends MutationBaseOption,
      awaitRefetchQueries: option<bool>,
      errorPolicy: option<ErrorPolicy.Js_.t>,
      optimisticResponse: option<(. 'jsVariables) => 'jsData>,
      update: option<MutationUpdaterFn.Js_.t<'jsData>>,
      updateQueries: option<MutationQueryReducersMap.Js_.t<'jsData>>,
      refetchQueries: option<RefetchQueryDescription.Js_.t>,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
    }
  }

  type t<'data, 'variables, 'jsVariables> = {
    context: option<Js.Json.t>,
    fetchPolicy: option<FetchPolicy__noCacheExtracted.t>,
    mutation: Graphql.documentNode,
    // ...extends MutationBaseOptions,
    awaitRefetchQueries: option<bool>,
    errorPolicy: option<ErrorPolicy.t>,
    optimisticResponse: option<'jsVariables => 'data>,
    refetchQueries: option<RefetchQueryDescription.t>,
    update: option<MutationUpdaterFn.t<'data>>,
    updateQueries: option<MutationQueryReducersMap.t<'data>>,
    variables: 'variables,
  }

  let toJs: (
    t<'data, 'variables, 'jsVariables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables,
    ~safeParse: Types.safeParse<'data, 'jsData>,
    ~serialize: 'data => 'jsData,
    ~serializeVariables: 'variables => 'jsVariables,
  ) => Js_.t<'jsData, 'jsVariables> = (
    t,
    ~mapJsVariables,
    ~safeParse,
    ~serialize,
    ~serializeVariables,
  ) => {
    awaitRefetchQueries: t.awaitRefetchQueries,
    context: t.context,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy__noCacheExtracted.toJs),
    mutation: t.mutation,
    optimisticResponse: t.optimisticResponse->Belt.Option.map((optimisticResponse, . variables) =>
      optimisticResponse(variables)->serialize
    ),
    refetchQueries: t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
    update: t.update->Belt.Option.map(MutationUpdaterFn.toJs(~safeParse)),
    updateQueries: t.updateQueries->Belt.Option.map(MutationQueryReducersMap.toJs(~safeParse)),
    variables: t.variables->serializeVariables->mapJsVariables,
  }
}
