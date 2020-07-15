module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module Graphql = ApolloClient__Graphql;
module QueryHookOptions = ApolloClient__React_Types.QueryHookOptions;
module QueryResult = ApolloClient__React_Types.QueryResult;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module Js_ = {
  // export declare function useQuery<TData = any, TVariables = OperationVariables>(query: DocumentNode, options?: QueryHookOptions<TData, TVariables>): QueryResult<TData, TVariables>;
  [@bs.module "@apollo/client"]
  external useQuery:
    (. Graphql.documentNode, QueryHookOptions.Js_.t('jsData, 'variables)) =>
    QueryResult.Js_.t('jsData, 'variables) =
    "useQuery";
};

let useQuery:
  type data jsVariables.
    (
      ~query: (module Operation with
                 type t = data and type Raw.t_variables = jsVariables),
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
      ~skip: bool=?,
      ~ssr: bool=?,
      jsVariables
    ) =>
    QueryResult.t(data, jsVariables) =
  (
    ~query as (module Operation),
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
    ~skip=?,
    ~ssr=?,
    variables,
  ) => {
    let jsQueryResult =
      Js_.useQuery(.
        Operation.query,
        QueryHookOptions.toJs(
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
            skip,
            ssr,
            variables,
          },
          ~parse=Operation.parse,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsQueryResult->QueryResult.fromJs(
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
        )
      },
      jsQueryResult,
    );
  };

module Extend = (M: Operation) => {
  let refetchQueryDescription:
    (~context: Js.Json.t=?, M.Raw.t_variables) =>
    RefetchQueryDescription.t_variant =
    (~context=?, variables: M.Raw.t_variables) =>
      RefetchQueryDescription.PureQueryOptions({
        query: M.query,
        variables,
        context,
      });

  let use =
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
        ~skip=?,
        ~ssr=?,
        variables,
      ) => {
    useQuery(
      ~query=(module M),
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
      ~skip?,
      ~ssr?,
      variables,
    );
  };

  let useLazy =
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
        (),
      ) => {
    ApolloClient__React_Hooks_UseLazyQuery.useLazyQuery(
      ~query=(module M),
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
      (),
    );
  };

  let useLazyWithVariables =
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
        variables,
      ) => {
    ApolloClient__React_Hooks_UseLazyQuery.useLazyQueryWithVariables(
      ~query=(module M),
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
      variables,
    );
  };
};
