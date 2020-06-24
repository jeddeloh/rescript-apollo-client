module Bindings = {
  module Client = ApolloClient__Client;
  module Graphql = ApolloClient__Graphql;
  module LinkWs = ApolloClient__LinkWs;
  module SubscriptionTransportWs = ApolloClient__SubscriptionsTransportWs;
  module ZenObservable = ApolloClient__ZenObservable;
};

module GraphQL_PPX = {
  module ExtendMutation = ApolloClient__React_Hooks_UseMutation.Extend;
  module ExtendMutationNoRequiredVariables = ApolloClient__React_Hooks_UseMutation.ExtendNoRequiredVariables;
  module ExtendQuery = ApolloClient__React_Hooks_UseQuery.Extend;
  module ExtendQueryNoRequiredVariables = ApolloClient__React_Hooks_UseQuery.ExtendNoRequiredVariables;
  module ExtendSubscription = ApolloClient__React_Hooks_UseSubscription.Extend;
  module ExtendSubscriptionNoRequiredVariables = ApolloClient__React_Hooks_UseSubscription.ExtendNoRequiredVariables;
};

module Links = {
  module ApolloLink = ApolloClient__Link_Core_ApolloLink;
  module HttpLink = ApolloClient__Link_Http_HttpLink;
  module LinkWs = ApolloClient__LinkWs;
  let concat = ApolloClient__Link_Core_ApolloLink.Static.concat;
  let execute = ApolloClient__Link_Core_ApolloLink.Static.execute;
  let empty = ApolloClient__Link_Core_ApolloLink.Static.empty;
  let from = ApolloClient__Link_Core_ApolloLink.Static.from;
  let split = ApolloClient__Link_Core_ApolloLink.Static.split;
};

module React = {
  module ApolloProvider = ApolloClient__React_Context_ApolloProvider;
  let useApolloClient = ApolloClient__React_Hooks_UseApolloClient.useApolloClient;
  let useMutation = ApolloClient__React_Hooks_UseMutation.useMutation;
  let useMutation0 = ApolloClient__React_Hooks_UseMutation.useMutation0;
  let useQuery = ApolloClient__React_Hooks_UseQuery.useQuery;
  let useQuery0 = ApolloClient__React_Hooks_UseQuery.useQuery0;
  let useSubscription = ApolloClient__React_Hooks_UseSubscription.useSubscription;
  let useSubscription0 = ApolloClient__React_Hooks_UseSubscription.useSubscription0;
};

module Utilities = ApolloClient__Utilities;

module ApolloCache = ApolloClient__ApolloClient.ApolloCache;
module InMemoryCache = ApolloClient__Cache_InMemory_InMemoryCache;

module DefaultWatchQueryOptions = ApolloClient__ApolloClient.DefaultWatchQueryOptions;
module DefaultQueryOptions = ApolloClient__ApolloClient.DefaultQueryOptions;
module DefaultMutateOptions = ApolloClient__ApolloClient.DefaultMutateOptions;
module DefaultOptions = ApolloClient__ApolloClient.DefaultOptions;
module ApolloClientOptions = ApolloClient__ApolloClient.ApolloClientOptions;

type t = ApolloClient__ApolloClient.t;
let make = ApolloClient__ApolloClient.make;
let mutate = ApolloClient__ApolloClient.mutate;
let query = ApolloClient__ApolloClient.query;
let readQuery = ApolloClient__ApolloClient.readQuery;
let writeQuery = ApolloClient__ApolloClient.writeQuery;