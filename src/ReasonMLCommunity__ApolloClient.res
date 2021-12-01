// Creating a client
type t = ApolloClient__Core_ApolloClient.t
let make = ApolloClient__Core_ApolloClient.make

module DefaultWatchQueryOptions = ApolloClient__Core_ApolloClient.DefaultWatchQueryOptions
module DefaultQueryOptions = ApolloClient__Core_ApolloClient.DefaultQueryOptions
module DefaultMutateOptions = ApolloClient__Core_ApolloClient.DefaultMutateOptions
module DefaultOptions = ApolloClient__Core_ApolloClient.DefaultOptions

// Fetching data
module React = {
  module ApolloProvider = ApolloClient__React_Context_ApolloProvider
  let useApolloClient = ApolloClient__React_Hooks_UseApolloClient.useApolloClient
  let useMutation = ApolloClient__React_Hooks_UseMutation.useMutation
  let useMutationWithVariables = ApolloClient__React_Hooks_UseMutation.useMutationWithVariables
  let useLazyQuery = ApolloClient__React_Hooks_UseLazyQuery.useLazyQuery
  let useLazyQueryWithVariables = ApolloClient__React_Hooks_UseLazyQuery.useLazyQueryWithVariables
  let useQuery = ApolloClient__React_Hooks_UseQuery.useQuery
  let useSubscription = ApolloClient__React_Hooks_UseSubscription.useSubscription
}

// Caching
module Cache = {
  type t<'serialized> = ApolloClient__Cache_Core_Cache.ApolloCache.t<'serialized>
  // Creating
  module InMemoryCache = ApolloClient__Cache_InMemory_InMemoryCache
  // Local state management
  let makeVar = ApolloClient__Cache_InMemory_ReactiveVars.makeVar
}

// Customize Apollo Client's data flow
module Link = {
  module ContextLink = ApolloClient__Link_Context.ContextLink
  module ErrorLink = ApolloClient__Link_Error.ErrorLink
  module HttpLink = ApolloClient__Link_Http_HttpLink
  module RetryLink = ApolloClient__Link_Retry_RetryLink
  module WebSocketLink = ApolloClient__Link_Ws.WebSocketLink
  type t = ApolloClient__Link_Core_ApolloLink.t
  let concat = ApolloClient__Link_Core_ApolloLink.Static.concat
  let execute = ApolloClient__Link_Core_ApolloLink.Static.execute
  let empty = ApolloClient__Link_Core_ApolloLink.Static.empty
  let make = ApolloClient__Link_Core_ApolloLink.make
  let from = ApolloClient__Link_Core_ApolloLink.Static.from
  let split = ApolloClient__Link_Core_ApolloLink.Static.split
}

// Helpers and utility functions
module Utilities = ApolloClient__Utilities

// Rescript Extras
// 1:1 Javascript package structure
module Bindings = {
  module Client = ApolloClient__Client
  module Graphql = ApolloClient__Graphql
  module SubscriptionTransportWs = ApolloClient__SubscriptionsTransportWs
  module ZenObservable = ApolloClient__ZenObservable
}

// These are extension functors used by graphql-ppx
module GraphQL_PPX = {
  module ExtendMutation = ApolloClient__React_Hooks_UseMutation.Extend
  module ExtendQuery = ApolloClient__React_Hooks_UseQuery.Extend
  module ExtendSubscription = ApolloClient__React_Hooks_UseSubscription.Extend
  type templateTagReturnType = ApolloClient__Graphql.documentNode
}

module Testing = {
  module MockedProvider = ApolloClient__Testing.MockedProvider
  let makeResult = ApolloClient__Testing_Types.makeResult
}

// Convenient access to all types and the methods for working with those types
module Types = {
  module ApolloError = ApolloClient__Errors_ApolloError
  module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult
  module ApolloLink = ApolloClient__Link_Core_ApolloLink
  module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache
  module BaseSubscriptionOptions = ApolloClient__React_Types.BaseSubscriptionOptions
  module ConnectionParamsOptions = ApolloClient__SubscriptionsTransportWs.ConnectionParamsOptions
  module DataProxy = ApolloClient__Cache_Core_Types.DataProxy
  module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy
  module ErrorResponse = ApolloClient__Link_Error.ErrorResponse
  module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy
  module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted
  module FetchResult = ApolloClient__Link_Core_Types.FetchResult
  module FieldPolicy = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldPolicy
  module FieldReadFunction = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldReadFunction
  module FieldMergeFunction = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldMergeFunction
  module FragmentMatcher = ApolloClient__Core_LocalState.FragmentMatcher
  module GraphqlError = ApolloClient__Graphql_Error_GraphQLError
  module GraphQLRequest = ApolloClient__Link_Core_Types.GraphQLRequest
  module KeyArgs = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldPolicy_KeyArgs
  module KeySpecifier = ApolloClient__Cache_InMemory_Policies_FieldPolicy.KeySpecifier
  module KeyFieldsFunction = ApolloClient__Cache_InMemory_Policies.KeyFieldsFunction
  module LazyQueryHookOptions = ApolloClient__React_Types.LazyQueryHookOptions
  module MutationHookOptions = ApolloClient__React_Types.MutationHookOptions
  module MutationOptions = ApolloClient__Core_WatchQueryOptions.MutationOptions
  module MutationQueryReducersMap = ApolloClient__Core_WatchQueryOptions.MutationQueryReducersMap
  module MutationTuple = ApolloClient__React_Types.MutationTuple
  module MutationTuple__noVariables = ApolloClient__React_Types.MutationTuple__noVariables
  module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn
  module Observable = ApolloClient__ZenObservable.Observable
  module ObservableQuery = ApolloClient__Core_ObservableQuery.ObservableQuery
  module OnSubscriptionDataOptions = ApolloClient__React_Types.OnSubscriptionDataOptions
  module Operation = ApolloClient__Link_Core_Types.Operation
  module OperationVariables = ApolloClient__Core_Types.OperationVariables
  module QueryHookOptions = ApolloClient__React_Types.QueryHookOptions
  module QueryOptions = ApolloClient__Core_WatchQueryOptions.QueryOptions
  module QueryTuple = ApolloClient__React_Types.QueryTuple
  module QueryTuple__noVariables = ApolloClient__React_Types.QueryTuple__noVariables
  module QueryResult = ApolloClient__React_Types.QueryResult
  module PossibleTypesMap = ApolloClient__Cache_InMemory_Policies.PossibleTypesMap
  module PureQueryOptions = ApolloClient__Core_Types.PureQueryOptions
  module ReactiveVar = ApolloClient__Cache_InMemory_ReactiveVars.ReactiveVar
  module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription
  module RequestHandler = ApolloClient__Link_Core_Types.RequestHandler
  module Resolvers = ApolloClient__Core_Types.Resolvers
  module SubscriptionHookOptions = ApolloClient__React_Types.SubscriptionHookOptions
  module SubscriptionOptions = ApolloClient__Core_WatchQueryOptions.SubscriptionOptions
  module TypePolicies = ApolloClient__Cache_InMemory_Policies.TypePolicies
  module TypePolicy = ApolloClient__Cache_InMemory_Policies.TypePolicy
  module UriFunction = ApolloClient__Link_Http_SelectHttpOptionsAndBody.UriFunction
  module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy
  module WatchQueryOptions = ApolloClient__Core_WatchQueryOptions.WatchQueryOptions
}
