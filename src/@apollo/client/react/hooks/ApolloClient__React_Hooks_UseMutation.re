module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
module Graphql = ApolloClient__Graphql;
module MutationHookOptions = ApolloClient__React_Types.MutationHookOptions;
module MutationTuple = ApolloClient__React_Types.MutationTuple;
module MutationTuple__noVariables = ApolloClient__React_Types.MutationTuple__noVariables;
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn;
module OperationVariables = ApolloClient__Core_Types.OperationVariables;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;

module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module Js_ = {
  // export declare function useMutation<TData = any, TVariables = OperationVariables>(mutation: DocumentNode, options?: MutationHookOptions<TData, TVariables>): MutationTuple<TData, TVariables>;
  [@bs.module "@apollo/client"]
  external useMutation:
    (
      . Graphql.documentNode,
      MutationHookOptions.Js_.t('jsData, 'jsVariables)
    ) =>
    MutationTuple.Js_.t('jsData, 'jsVariables) =
    "useMutation";
};

let useMutation:
  type data variables jsVariables.
    (
      ~mutation: (module Operation with
                    type t = data and
                    type t_variables = variables and
                    type Raw.t_variables = jsVariables),
      ~awaitRefetchQueries: bool=?,
      ~context: Js.Json.t=?,
      ~client: ApolloClient.t=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: FetchPolicy__noCacheExtracted.t=?,
      ~ignoreResults: bool=?,
      ~notifyOnNetworkStatusChange: bool=?,
      ~onError: ApolloError.t => unit=?,
      ~onCompleted: data => unit=?,
      ~optimisticResponse: jsVariables => data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~update: MutationUpdaterFn.t(data)=?,
      unit
    ) =>
    MutationTuple.t(data, variables, jsVariables) =
  (
    ~mutation as (module Operation),
    ~awaitRefetchQueries=?,
    ~context=?,
    ~client=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~ignoreResults=?,
    ~notifyOnNetworkStatusChange=?,
    ~onError=?,
    ~onCompleted=?,
    ~optimisticResponse=?,
    ~refetchQueries=?,
    ~update=?,
    (),
  ) => {
    let jsMutationTuple =
      Js_.useMutation(.
        Operation.query,
        MutationHookOptions.toJs(
          {
            mutation: None,
            awaitRefetchQueries,
            context,
            client,
            errorPolicy,
            fetchPolicy,
            ignoreResults,
            notifyOnNetworkStatusChange,
            onError,
            onCompleted,
            optimisticResponse,
            refetchQueries,
            update,
            variables: None,
          },
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsMutationTuple->MutationTuple.fromJs(
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
          ~serializeVariables=Operation.serializeVariables,
        )
      },
      jsMutationTuple,
    );
  };

let useMutationWithVariables:
  type data variables jsVariables.
    (
      ~mutation: (module Operation with
                    type t = data and
                    type t_variables = variables and
                    type Raw.t_variables = jsVariables),
      ~awaitRefetchQueries: bool=?,
      ~context: Js.Json.t=?,
      ~client: ApolloClient.t=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: FetchPolicy__noCacheExtracted.t=?,
      ~ignoreResults: bool=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      ~notifyOnNetworkStatusChange: bool=?,
      ~onError: ApolloError.t => unit=?,
      ~onCompleted: data => unit=?,
      ~optimisticResponse: jsVariables => data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~update: MutationUpdaterFn.t(data)=?,
      variables
    ) =>
    MutationTuple__noVariables.t(data, jsVariables) =
  (
    ~mutation as (module Operation),
    ~awaitRefetchQueries=?,
    ~context=?,
    ~client=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~ignoreResults=?,
    ~mapJsVariables=Utils.identity,
    ~notifyOnNetworkStatusChange=?,
    ~onError=?,
    ~onCompleted=?,
    ~optimisticResponse=?,
    ~refetchQueries=?,
    ~update=?,
    variables,
  ) => {
    let jsVariables =
      variables->Operation.serializeVariables->mapJsVariables;

    let jsMutationTuple =
      Js_.useMutation(.
        Operation.query,
        MutationHookOptions.toJs(
          {
            mutation: None,
            awaitRefetchQueries,
            context,
            client,
            errorPolicy,
            fetchPolicy,
            ignoreResults,
            notifyOnNetworkStatusChange,
            onError,
            onCompleted,
            optimisticResponse,
            refetchQueries,
            update,
            variables: Some(jsVariables),
          },
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        let (mutate, mutationResult) =
          jsMutationTuple->MutationTuple__noVariables.fromJs(
            ~parse=Operation.parse,
            ~serialize=Operation.serialize,
            // Passing in the same variables from above allows us to reuse some types
            ~variables=jsVariables,
          );
        (mutate, mutationResult);
      },
      jsMutationTuple,
    );
  };

module Extend = (M: Types.Operation) => {
  let useMutation =
      (
        ~awaitRefetchQueries=?,
        ~context=?,
        ~client=?,
        ~errorPolicy=?,
        ~fetchPolicy=?,
        ~ignoreResults=?,
        ~notifyOnNetworkStatusChange=?,
        ~onError=?,
        ~onCompleted=?,
        ~optimisticResponse=?,
        ~refetchQueries=?,
        ~update=?,
        (),
      ) => {
    useMutation(
      ~mutation=(module M),
      ~awaitRefetchQueries?,
      ~context?,
      ~client?,
      ~errorPolicy?,
      ~fetchPolicy?,
      ~ignoreResults?,
      ~notifyOnNetworkStatusChange?,
      ~onError?,
      ~onCompleted?,
      ~optimisticResponse?,
      ~refetchQueries?,
      ~update?,
      (),
    );
  };

  let useMutationWithVariables =
      (
        ~awaitRefetchQueries=?,
        ~context=?,
        ~client=?,
        ~errorPolicy=?,
        ~fetchPolicy=?,
        ~ignoreResults=?,
        ~mapJsVariables=?,
        ~notifyOnNetworkStatusChange=?,
        ~onError=?,
        ~onCompleted=?,
        ~optimisticResponse=?,
        ~refetchQueries=?,
        ~update=?,
        variables,
      ) => {
    useMutationWithVariables(
      ~mutation=(module M),
      ~awaitRefetchQueries?,
      ~context?,
      ~client?,
      ~errorPolicy?,
      ~fetchPolicy?,
      ~ignoreResults?,
      ~mapJsVariables?,
      ~notifyOnNetworkStatusChange?,
      ~onError?,
      ~onCompleted?,
      ~optimisticResponse?,
      ~refetchQueries?,
      ~update?,
      variables,
    );
  };
};
