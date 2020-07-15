module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module BaseSubscriptionOptions = ApolloClient__React_Types.BaseSubscriptionOptions;
module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy;
module Graphql = ApolloClient__Graphql;
module OnSubscriptionDataOptions = ApolloClient__React_Types.OnSubscriptionDataOptions;
module SubscriptionHookOptions = ApolloClient__React_Types.SubscriptionHookOptions;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;

module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module Js_ = {
  type useSubscription_result('jsData, 'variables) = {
    variables: option('variables),
    loading: bool,
    data: option('jsData),
    error: option(ApolloError.Js_.t),
  };

  // export declare function useSubscription<TData = any, TVariables = OperationVariables>(subscription: DocumentNode, options?: SubscriptionHookOptions<TData, TVariables>): {
  //     variables: TVariables | undefined;
  //     loading: boolean;
  //     data?: TData | undefined;
  //     error?: import("../..").ApolloError | undefined;
  // };
  [@bs.module "@apollo/client"]
  external useSubscription:
    (
      . Graphql.Language.documentNode,
      SubscriptionHookOptions.Js_.t('jsData, 'variables)
    ) =>
    useSubscription_result('jsData, 'variables) =
    "useSubscription";
};

type useSubscription_result('data, 'variables) = {
  variables: option('variables),
  loading: bool,
  data: option('data),
  error: option(ApolloError.t),
};

let useSubscription:
  type data jsVariables.
    (
      ~subscription: (module Operation with
                        type t = data and type Raw.t_variables = jsVariables),
      ~client: ApolloClient.t=?,
      ~fetchPolicy: FetchPolicy.t=?,
      ~onSubscriptionData: OnSubscriptionDataOptions.t(data) => unit=?,
      ~onSubscriptionComplete: unit => unit=?,
      ~shouldResubscribe: BaseSubscriptionOptions.t(data, jsVariables) => bool
                            =?,
      ~skip: bool=?,
      jsVariables
    ) =>
    useSubscription_result(data, jsVariables) =
  (
    ~subscription as (module Operation),
    ~client=?,
    ~fetchPolicy=?,
    ~onSubscriptionData=?,
    ~onSubscriptionComplete=?,
    ~shouldResubscribe=?,
    ~skip=?,
    variables,
  ) => {
    let jsSubscriptionResult =
      Js_.useSubscription(.
        Operation.query,
        SubscriptionHookOptions.toJs(
          {
            client,
            fetchPolicy,
            onSubscriptionData,
            onSubscriptionComplete,
            subscription: None,
            shouldResubscribe,
            skip,
            variables,
          },
          ~parse=Operation.parse,
        ),
      );

    Utils.useGuaranteedMemo1(
      () =>
        {
          variables: jsSubscriptionResult.variables,
          loading: jsSubscriptionResult.loading,
          data: jsSubscriptionResult.data->Belt.Option.map(Operation.parse),
          error:
            jsSubscriptionResult.error->Belt.Option.map(ApolloError.fromJs),
        },
      jsSubscriptionResult,
    );
  };

module Extend = (M: Operation) => {
  let use =
      (
        ~client=?,
        ~fetchPolicy=?,
        ~onSubscriptionData=?,
        ~onSubscriptionComplete=?,
        ~shouldResubscribe=?,
        ~skip=?,
        variables,
      ) => {
    useSubscription(
      ~subscription=(module M),
      ~client?,
      ~fetchPolicy?,
      ~onSubscriptionData?,
      ~onSubscriptionComplete?,
      ~shouldResubscribe?,
      ~skip?,
      variables,
    );
  };
};
