module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__ApolloError;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module Graphql = ApolloClient__Graphql;
module LazyQueryHookOptions = ApolloClient__React_Types.LazyQueryHookOptions;
module QueryTuple = ApolloClient__React_Types.QueryTuple;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module Js_ = {
  // export declare function useLazyQuery<TData = any, TVariables = OperationVariables>(query: DocumentNode, options?: LazyQueryHookOptions<TData, TVariables>): QueryTuple<TData, TVariables>;
  [@bs.module "@apollo/client"]
  external useLazyQuery:
    (
      . Graphql.documentNode,
      LazyQueryHookOptions.Js_.t('jsData, 'variables)
    ) =>
    QueryTuple.Js_.t('jsData, 'variables) =
    "useLazyQuery";
};

let useLazyQuery:
  type data jsData jsVariables.
    (
      ~client: ApolloClient.t=?,
      ~context: Js.Json.t=?,
      ~displayName: string=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~notifyOnNetworkStatusChange: bool=?,
      ~onCompleted: data => unit=?,
      ~onError: ApolloError.t => unit=?,
      ~partialRefetch: bool=?,
      ~pollInterval: int=?,
      ~ssr: bool=?,
      ~variables: jsVariables,
      (module Operation with
         type t = data and
         type Raw.t = jsData and
         type Raw.t_variables = jsVariables)
    ) =>
    QueryTuple.t(data, jsVariables) =
  (
    ~client=?,
    ~context=?,
    ~displayName=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~notifyOnNetworkStatusChange=?,
    ~onCompleted=?,
    ~onError=?,
    ~partialRefetch=?,
    ~pollInterval=?,
    ~ssr=?,
    ~variables,
    (module Operation),
  ) => {
    let jsQueryTuple =
      Js_.useLazyQuery(
        Operation.query->Utils.castStringAsDocumentNode,
        LazyQueryHookOptions.toJs(
          {
            client,
            context,
            displayName,
            errorPolicy,
            fetchPolicy,
            onCompleted,
            onError,
            notifyOnNetworkStatusChange,
            partialRefetch,
            pollInterval,
            query: None,
            ssr,
            variables,
          },
          ~parse=Operation.parse,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsQueryTuple->QueryTuple.fromJs(
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
        )
      },
      jsQueryTuple,
    );
  };

let useLazyQuery0:
  type data jsData jsVariables.
    (
      ~client: ApolloClient.t=?,
      ~context: Js.Json.t=?,
      ~displayName: string=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~notifyOnNetworkStatusChange: bool=?,
      ~onCompleted: data => unit=?,
      ~onError: ApolloError.t => unit=?,
      ~partialRefetch: bool=?,
      ~pollInterval: int=?,
      ~ssr: bool=?,
      (module Types.OperationNoRequiredVars with
         type t = data and
         type Raw.t = jsData and
         type Raw.t_variables = jsVariables)
    ) =>
    QueryTuple.t(data, jsVariables) =
  (
    ~client=?,
    ~context=?,
    ~displayName=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~notifyOnNetworkStatusChange=?,
    ~onCompleted=?,
    ~onError=?,
    ~partialRefetch=?,
    ~pollInterval=?,
    ~ssr=?,
    (module Operation),
  ) => {
    useLazyQuery(
      ~client?,
      ~context?,
      ~displayName?,
      ~errorPolicy?,
      ~fetchPolicy?,
      ~notifyOnNetworkStatusChange?,
      ~onCompleted?,
      ~onError?,
      ~partialRefetch?,
      ~pollInterval?,
      ~ssr?,
      ~variables=Operation.makeDefaultVariables(),
      (module Operation),
    );
  };
