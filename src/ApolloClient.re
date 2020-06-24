include ApolloClient__Client;

module LinkWs = ApolloClient__LinkWs;

module DefaultQueryOptions = ApolloClient__ApolloClient.DefaultQueryOptions;
module DefaultWatchQueryOptions = ApolloClient__ApolloClient.DefaultWatchQueryOptions;
module DefaultMutateOptions = ApolloClient__ApolloClient.DefaultMutateOptions;
module DefaultOptions = ApolloClient__ApolloClient.DefaultOptions;
let make = ApolloClient__ApolloClient.make;

module GraphQL_PPX = {
  module ExtendMutation = ApolloClient__React_UseMutation.Extend;
  module ExtendMutationNoRequiredVariables = ApolloClient__React_UseMutation.ExtendNoRequiredVariables;
  module ExtendQuery = ApolloClient__React_UseQuery.Extend;
  module ExtendQueryNoRequiredVariables = ApolloClient__React_UseQuery.ExtendNoRequiredVariables;
  module ExtendSubscription = ApolloClient__React_UseSubscription.Extend;
  module ExtendSubscriptionNoRequiredVariables = ApolloClient__React_UseSubscription.ExtendNoRequiredVariables;
};