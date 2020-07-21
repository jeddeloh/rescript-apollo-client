// Creating a client
module DefaultWatchQueryOptions = ApolloClient__ApolloClient.DefaultWatchQueryOptions;
module DefaultQueryOptions = ApolloClient__ApolloClient.DefaultQueryOptions;
module DefaultMutateOptions = ApolloClient__ApolloClient.DefaultMutateOptions;
module DefaultOptions = ApolloClient__ApolloClient.DefaultOptions;

type t = ApolloClient__ApolloClient.t;
let make = ApolloClient__ApolloClient.make;

// Fetching data
let mutate = ApolloClient__ApolloClient.mutate;
let query = ApolloClient__ApolloClient.query;
let readQuery = ApolloClient__ApolloClient.readQuery;
let watchQuery = ApolloClient__ApolloClient.watchQuery;
let writeFragment = ApolloClient__ApolloClient.writeFragment;
let writeQuery = ApolloClient__ApolloClient.writeQuery;

module React = {
  module ApolloProvider = ApolloClient__React_Context_ApolloProvider;
  let useApolloClient = ApolloClient__React_Hooks_UseApolloClient.useApolloClient;
  let useMutation = ApolloClient__React_Hooks_UseMutation.useMutation;
  let useMutationWithVariables = ApolloClient__React_Hooks_UseMutation.useMutationWithVariables;
  let useLazyQuery = ApolloClient__React_Hooks_UseLazyQuery.useLazyQuery;
  let useLazyQueryWithVariables = ApolloClient__React_Hooks_UseLazyQuery.useLazyQueryWithVariables;
  let useQuery = ApolloClient__React_Hooks_UseQuery.useQuery;
  let useSubscription = ApolloClient__React_Hooks_UseSubscription.useSubscription;
};

// Caching
module Cache = {
  type t('serialized) =
    ApolloClient__Cache_Core_Cache.ApolloCache.t('serialized);
  // Creating
  module InMemoryCache = ApolloClient__Cache_InMemory_InMemoryCache;
  // Reading and writing
  let readQuery = ApolloClient__Cache_Core_Cache.ApolloCache.readQuery;
  let writeFragment = ApolloClient__Cache_Core_Cache.ApolloCache.writeFragment;
  let writeQuery = ApolloClient__Cache_Core_Cache.ApolloCache.writeQuery;
};

// Customize Apollo Client's data flow
module Link = {
  module ContextLink = ApolloClient__LinkContext.ContextLink;
  module ErrorLink = ApolloClient__LinkError.ErrorLink;
  module HttpLink = ApolloClient__Link_Http_HttpLink;
  module WebSocketLink = ApolloClient__LinkWs.WebSocketLink;
  type t = ApolloClient__Link_Core_ApolloLink.t;
  let concat = ApolloClient__Link_Core_ApolloLink.Static.concat;
  let execute = ApolloClient__Link_Core_ApolloLink.Static.execute;
  let empty = ApolloClient__Link_Core_ApolloLink.Static.empty;
  let make = ApolloClient__Link_Core_ApolloLink.make;
  let from = ApolloClient__Link_Core_ApolloLink.Static.from;
  let split = ApolloClient__Link_Core_ApolloLink.Static.split;
};

// Helpers and utilities
module Utilities = ApolloClient__Utilities;

// 1:1 Javascript package structure
module Bindings = {
  module Client = ApolloClient__Client;
  module Graphql = ApolloClient__Graphql;
  module LinkError = ApolloClient__LinkError;
  module LinkContext = ApolloClient__LinkContext;
  module LinkWs = ApolloClient__LinkWs;
  module SubscriptionTransportWs = ApolloClient__SubscriptionsTransportWs;
  module ZenObservable = ApolloClient__ZenObservable;
};

// Extension modules used by graphql-ppx
module GraphQL_PPX = {
  module ExtendMutation = ApolloClient__React_Hooks_UseMutation.Extend;
  module ExtendQuery = ApolloClient__React_Hooks_UseQuery.Extend;
  module ExtendSubscription = ApolloClient__React_Hooks_UseSubscription.Extend;
  type templateTagReturnType = ApolloClient__Graphql.documentNode;
};

// Convenient access to all types and the methods for working with those types
module Types = {
  module ApolloError = ApolloClient__Errors_ApolloError;
  module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult;
  module ApolloLink = ApolloClient__Link_Core_ApolloLink;
  module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache;
  module BaseSubscriptionOptions = ApolloClient__React_Types.BaseSubscriptionOptions;
  module DataProxy = ApolloClient__Cache_Core_Types.DataProxy;
  module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
  module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy;
  module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
  module FragmentMatcher = ApolloClient__Core_LocalState.FragmentMatcher;
  module GraphqlError = ApolloClient__Graphql_Error_GraphQLError;
  module FetchResult = ApolloClient__Link_Core_Types.FetchResult;
  module LazyQueryHookOptions = ApolloClient__React_Types.LazyQueryHookOptions;
  module MutationHookOptions = ApolloClient__React_Types.MutationHookOptions;
  module MutationOptions = ApolloClient__Core_WatchQueryOptions.MutationOptions;
  module MutationQueryReducersMap = ApolloClient__Core_WatchQueryOptions.MutationQueryReducersMap;
  module MutationTuple = ApolloClient__React_Types.MutationTuple;
  module MutationTuple__noVariables = ApolloClient__React_Types.MutationTuple__noVariables;
  module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn;
  module ObservableQuery = ApolloClient__Core_ObservableQuery.ObservableQuery;
  module OnSubscriptionDataOptions = ApolloClient__React_Types.OnSubscriptionDataOptions;
  module OperationVariables = ApolloClient__Core_Types.OperationVariables;
  module QueryHookOptions = ApolloClient__React_Types.QueryHookOptions;
  module QueryOptions = ApolloClient__Core_WatchQueryOptions.QueryOptions;
  module QueryTuple = ApolloClient__React_Types.QueryTuple;
  module QueryTuple__noVariables = ApolloClient__React_Types.QueryTuple__noVariables;
  module QueryResult = ApolloClient__React_Types.QueryResult;
  module PureQueryOptions = ApolloClient__Core_Types.PureQueryOptions;
  module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
  module Resolvers = ApolloClient__Core_Types.Resolvers;
  module SubscriptionHookOptions = ApolloClient__React_Types.SubscriptionHookOptions;
  module UriFunction = ApolloClient__Link_Http_SelectHttpOptionsAndBody.UriFunction;
  module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;
  module WatchQueryOptions = ApolloClient__Core_WatchQueryOptions.WatchQueryOptions;
};
