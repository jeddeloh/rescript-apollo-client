module Bindings = {
  module Client = ApolloClient__Client;
  module Graphql = ApolloClient__Graphql;
  module LinkError = ApolloClient__LinkError;
  module LinkContext = ApolloClient__LinkContext;
  module LinkWs = ApolloClient__LinkWs;
  module SubscriptionTransportWs = ApolloClient__SubscriptionsTransportWs;
  module ZenObservable = ApolloClient__ZenObservable;
};

module GraphQL_PPX = {
  module ExtendMutation = ApolloClient__React_Hooks_UseMutation.Extend;
  module ExtendQuery = ApolloClient__React_Hooks_UseQuery.Extend;
  module ExtendSubscription = ApolloClient__React_Hooks_UseSubscription.Extend;
  type templateTagReturnType = ApolloClient__Graphql.documentNode;
};

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

module Utilities = ApolloClient__Utilities;

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

module Cache = {
  module InMemoryCache = ApolloClient__Cache_InMemory_InMemoryCache;
  type t('serialized) =
    ApolloClient__Cache_Core_Cache.ApolloCache.t('serialized);
};

module DefaultWatchQueryOptions = ApolloClient__ApolloClient.DefaultWatchQueryOptions;
module DefaultQueryOptions = ApolloClient__ApolloClient.DefaultQueryOptions;
module DefaultMutateOptions = ApolloClient__ApolloClient.DefaultMutateOptions;
module DefaultOptions = ApolloClient__ApolloClient.DefaultOptions;

type t = ApolloClient__ApolloClient.t;
let make = ApolloClient__ApolloClient.make;
let mutate = ApolloClient__ApolloClient.mutate;
let query = ApolloClient__ApolloClient.query;
let readQuery = ApolloClient__ApolloClient.readQuery;
let writeQuery = ApolloClient__ApolloClient.writeQuery;
