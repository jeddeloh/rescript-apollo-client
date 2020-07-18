module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache;
module FetchResult = ApolloClient__Link_Core_Types.FetchResult;
module Graphql = ApolloClient__Graphql;
module MutationQueryReducersMap = ApolloClient__Core_Types.MutationQueryReducersMap;
module Types = ApolloClient__Types;
module PureQueryOptions = ApolloClient__Core_Types.PureQueryOptions;

module ErrorPolicy = {
  module Js_ = {
    // export declare type ErrorPolicy = 'none' | 'ignore' | 'all';
    type t = string;
  };

  type t =
    | None
    | Ignore
    | All;

  let toJs =
    fun
    | None => "none"
    | Ignore => "ignore"
    | All => "all";
};

module FetchPolicy = {
  module Js_ = {
    // export declare type FetchPolicy = 'cache-first' | 'network-only' | 'cache-only' | 'no-cache' | 'standby';
    type t = string;
  };

  type t =
    | CacheFirst
    | CacheOnly
    | NetworkOnly
    | NoCache
    | Standby;

  let toJs =
    fun
    | CacheFirst => "cache-first"
    | CacheOnly => "cache-only"
    | NetworkOnly => "network-only"
    | NoCache => "no-cache"
    | Standby => "standby";
};

module FetchPolicy__noCacheExtracted = {
  module Js_ = {
    // Extract<FetchPolicy, 'no-cache'>
    type t = string;
  };
  type t =
    | CacheFirst
    | CacheOnly
    | NetworkOnly
    | Standby;

  let toJs =
    fun
    | CacheFirst => "cache-first"
    | CacheOnly => "cache-only"
    | NetworkOnly => "network-only"
    | Standby => "standby";
};

module WatchQueryFetchPolicy = {
  module Js_ = {
    // export declare type WatchQueryFetchPolicy = FetchPolicy | 'cache-and-network';
    type t = string;
  };

  type t =
    | CacheAndNetwork
    | CacheFirst
    | CacheOnly
    | NetworkOnly
    | NoCache
    | Standby;

  let toJs =
    fun
    | CacheAndNetwork => "cache-and-network"
    | CacheFirst => "cache-first"
    | CacheOnly => "cache-only"
    | NetworkOnly => "network-only"
    | NoCache => "no-cache"
    | Standby => "standby";
};

module QueryOptions = {
  module Js_ = {
    type t('variables) = {
      fetchPolicy: option(FetchPolicy.Js_.t),
      // ...extends QueryBaseOptions
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'variables,
      errorPolicy: option(ErrorPolicy.Js_.t),
      context: option(Js.Json.t),
    };
  };

  type t('variables) = {
    fetchPolicy: option(FetchPolicy.t),
    query: Graphql.documentNode,
    variables: 'variables,
    errorPolicy: option(ErrorPolicy.t),
    context: option(Js.Json.t),
  };

  let toJs: t('variables) => Js_.t('variables) =
    t => {
      fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy.toJs),
      query: t.query,
      variables: t.variables,
      errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      context: t.context,
    };
};

module WatchQueryOptions = {
  module Js_ = {
    type t('variables) = {
      fetchPolicy: option(WatchQueryFetchPolicy.Js_.t),
      // ...extends QueryBaseOptions
      query: Graphql.documentNode,
      variables: option('variables),
      errorPolicy: option(ErrorPolicy.Js_.t),
      context: option(Js.Json.t),
    };
  };

  type t('variables) = {
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    query: Graphql.documentNode,
    variables: option('variables),
    errorPolicy: option(ErrorPolicy.t),
    context: option(Js.Json.t),
  };

  let toJs: t('variables) => Js_.t('variables) =
    t => {
      fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
      query: t.query,
      variables: t.variables,
      errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      context: t.context,
    };
};

module UpdateQueryFn = {
  module Js_ = {
    type t_options_subscriptionData('jsSubscriptionData) = {
      data: 'jsSubscriptionData,
    };
    type t_options('jsSubscriptionData, 'variables) = {
      subscriptionData: t_options_subscriptionData('jsSubscriptionData),
    };
    // export declare type UpdateQueryFn<TData = any, TSubscriptionVariables = OperationVariables, TSubscriptionData = TData> = (previousQueryResult: TData, options: {
    //     subscriptionData: {
    //         data: TSubscriptionData;
    //     };
    //     variables?: TSubscriptionVariables;
    // }) => TData;
    type t('jsQueryData, 'subscriptionVariables, 'jsSubscriptionData) =
      (
        . 'jsQueryData,
        t_options('jsSubscriptionData, 'subscriptionVariables)
      ) =>
      'jsQueryData;
  };
  type t_options_subscriptionData('jsSubscriptionData) = {
    data: 'jsSubscriptionData,
  };
  type t_options('jsSubscriptionData, 'variables) = {
    subscriptionData: t_options_subscriptionData('jsSubscriptionData),
  };

  type t('queryData, 'subscriptionVariables, 'subscriptionData) =
    ('queryData, t_options('subscriptionData, 'subscriptionVariables)) =>
    'queryData;

  let toJs:
    (
      t('queryData, 'subscriptionVariables, 'subscriptionData),
      ~queryParse: 'jsQueryData => 'queryData,
      ~querySerialize: 'queryData => 'jsQueryData,
      ~subscriptionParse: 'jsSubscriptionData => 'subscriptionData
    ) =>
    Js_.t('jsQueryData, 'subscriptionVariables, 'jsSubscriptionData) =
    (t, ~queryParse, ~querySerialize, ~subscriptionParse) =>
      (. jsQueryData, {subscriptionData: {data}}) =>
        t(
          jsQueryData->queryParse,
          {
            subscriptionData: {
              data: data->subscriptionParse,
            },
          },
        )
        ->querySerialize;
};

module SubscribeToMoreOptions = {
  module Js_ = {
    // export declare type SubscribeToMoreOptions<TData = any, TSubscriptionVariables = OperationVariables, TSubscriptionData = TData> = {
    //     document: DocumentNode;
    //     variables?: TSubscriptionVariables;
    //     updateQuery?: UpdateQueryFn<TData, TSubscriptionVariables, TSubscriptionData>;
    //     onError?: (error: Error) => void;
    //     context?: Record<string, any>;
    // };

    type t('jsQueryData, 'subscriptionVariables, 'jsSubscriptionData) = {
      document: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'subscriptionVariables,
      updateQuery:
        option(
          UpdateQueryFn.Js_.t(
            'jsQueryData,
            'subscriptionVariables,
            'jsSubscriptionData,
          ),
        ),
      onError: option(Js.Exn.t => unit),
      context: option(Js.Json.t),
    };
  };

  type t('queryData, 'subscriptionVariables, 'subscriptionData) = {
    document: Graphql.documentNode,
    variables: 'subscriptionVariables,
    updateQuery:
      option(
        UpdateQueryFn.t(
          'queryData,
          'subscriptionVariables,
          'subscriptionData,
        ),
      ),
    onError: option(Js.Exn.t => unit),
    context: option(Js.Json.t),
  };

  let toJs:
    (
      t('queryData, 'subscriptionVariables, 'subscriptionData),
      ~queryParse: 'jsQueryData => 'queryData,
      ~querySerialize: 'queryData => 'jsQueryData,
      ~subscriptionParse: 'jsSubscriptionData => 'subscriptionData
    ) =>
    Js_.t('jsQueryData, 'subscriptionVariables, 'jsSubscriptionData) =
    (t, ~queryParse, ~querySerialize, ~subscriptionParse) => {
      document: t.document,
      variables: t.variables,
      updateQuery:
        t.updateQuery
        ->Belt.Option.map(
            UpdateQueryFn.toJs(
              ~queryParse,
              ~querySerialize,
              ~subscriptionParse,
            ),
          ),
      onError: t.onError,
      context: t.context,
    };
};

module MutationUpdaterFn = {
  module Js_ = {
    type t('jsData) =
      (. ApolloCache.Js_.t(Js.Json.t), FetchResult.Js_.t('jsData)) => unit;
  };

  type t('data) = (ApolloCache.t(Js.Json.t), FetchResult.t('data)) => unit;

  let toJs: (t('data), ~parse: 'jsData => 'data) => Js_.t('jsData) =
    (mutationUpdaterFn, ~parse) =>
      (. cache, jsFetchResult) =>
        mutationUpdaterFn(cache, jsFetchResult->FetchResult.fromJs(~parse));
};

module RefetchQueryDescription = {
  module Js_ = {
    // CAVEAT: I did not try very hard to find a simpler alternative
    module Union: {
      type t;
      let string: string => t;
      let pureQueryOptions: PureQueryOptions.Js_.t(_) => t;
    } = {
      [@unboxed]
      type t =
        | Any('a): t;
      let string = (v: string) => Any(v);
      let pureQueryOptions = (v: PureQueryOptions.Js_.t(_)) => Any(v);
    };

    type t = array(Union.t);
  };

  type t_variant =
    | PureQueryOptions(PureQueryOptions.t('variables)): t_variant
    | String(string): t_variant;

  type t = array(t_variant);

  let toJs: t => Js_.t =
    Belt.Array.map(
      _,
      fun
      | PureQueryOptions(options) =>
        Js_.Union.pureQueryOptions(options->PureQueryOptions.toJs)
      | String(string) => Js_.Union.string(string),
    );
};

module MutationOptions = {
  module Js_ = {
    // export interface MutationOptions<T = {
    //     [key: string]: any;
    // }, TVariables = OperationVariables> extends MutationBaseOptions<T, TVariables> {
    //     mutation: DocumentNode;
    //     context?: any;
    //     fetchPolicy?: Extract<FetchPolicy, 'no-cache'>;
    // }
    type t('jsData, 'variables) = {
      mutation: Graphql.documentNode,
      context: option(Js.Json.t),
      fetchPolicy: option(FetchPolicy__noCacheExtracted.Js_.t),
      // ...extends MutationBaseOption,
      awaitRefetchQueries: option(bool),
      errorPolicy: option(ErrorPolicy.Js_.t),
      optimisticResponse: option((. 'variables) => 'jsData),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      updateQueries: option(MutationQueryReducersMap.Js_.t('jsData)),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      // We don't allow optional variables because it's not typesafe
      variables: 'variables,
    };
  };

  type t('data, 'variables) = {
    context: option(Js.Json.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    mutation: Graphql.documentNode,
    // ...extends MutationBaseOptions,
    awaitRefetchQueries: option(bool),
    errorPolicy: option(ErrorPolicy.t),
    optimisticResponse: option('variables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    updateQueries: option(MutationQueryReducersMap.t('data)),
    variables: 'variables,
  };

  let toJs:
    (
      t('data, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    Js_.t('jsData, 'variables) =
    (t, ~parse, ~serialize) => {
      awaitRefetchQueries: t.awaitRefetchQueries,
      context: t.context,
      errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      fetchPolicy:
        t.fetchPolicy->Belt.Option.map(FetchPolicy__noCacheExtracted.toJs),
      mutation: t.mutation,
      optimisticResponse:
        t.optimisticResponse
        ->Belt.Option.map(optimisticResponse =>
            (. variables) => optimisticResponse(variables)->serialize
          ),
      refetchQueries:
        t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
      update: t.update->Belt.Option.map(MutationUpdaterFn.toJs(~parse)),
      updateQueries:
        t.updateQueries
        ->Belt.Option.map(MutationQueryReducersMap.toJs(~parse)),
      variables: t.variables,
    };
};
