module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__ApolloError;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
module Graphql = ApolloClient__Graphql;
module MutationHookOptions = ApolloClient__React_Types.MutationHookOptions;
module MutationTuple = ApolloClient__React_Types.MutationTuple;
module MutationTuple__noVariables = ApolloClient__React_Types.MutationTuple__noVariables;
module MutationTuple__optionalVariables = ApolloClient__React_Types.MutationTuple__optionalVariables;
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
      MutationHookOptions.Js_.t('jsData, 'variables)
    ) =>
    MutationTuple.Js_.t('jsData, 'variables) =
    "useMutation";
};

let useMutation:
  type data jsData jsVariables.
    (
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
      (module Operation with
         type t = data and
         type Raw.t = jsData and
         type Raw.t_variables = jsVariables)
    ) =>
    MutationTuple.t(data, jsVariables) =
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
    (module Operation),
  ) => {
    let jsMutationTuple =
      Js_.useMutation(.
        Operation.query->Utils.castStringAsDocumentNode,
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
        )
      },
      jsMutationTuple,
    );
  };

let useMutationWithVariables:
  type data jsData jsVariables.
    (
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
      ~variables: jsVariables,
      (module Operation with
         type t = data and
         type Raw.t = jsData and
         type Raw.t_variables = jsVariables)
    ) =>
    MutationTuple__noVariables.t(data, jsVariables) =
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
    ~variables,
    (module Operation),
  ) => {
    let jsMutationTuple =
      Js_.useMutation(.
        Operation.query->Utils.castStringAsDocumentNode,
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
            variables: Some(variables),
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
            ~variables,
          );
        (mutate, mutationResult);
      },
      jsMutationTuple,
    );
  };

let useMutation0:
  type data jsData jsVariables.
    (
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
      (module OperationNoRequiredVars with
         type t = data and
         type Raw.t = jsData and
         type Raw.t_variables = jsVariables)
    ) =>
    MutationTuple__optionalVariables.t(data, jsVariables) =
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
    (module OperationNoRequiredVars),
  ) => {
    let jsMutationTuple =
      Js_.useMutation(.
        OperationNoRequiredVars.query->Utils.castStringAsDocumentNode,
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
            variables: Some(OperationNoRequiredVars.makeDefaultVariables()),
          },
          ~parse=OperationNoRequiredVars.parse,
          ~serialize=OperationNoRequiredVars.serialize,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsMutationTuple->MutationTuple__optionalVariables.fromJs(
          ~defaultVariables=OperationNoRequiredVars.makeDefaultVariables(),
          ~parse=OperationNoRequiredVars.parse,
          ~serialize=OperationNoRequiredVars.serialize,
        )
      },
      jsMutationTuple,
    );
  };

module Extend = (M: Types.Operation) => {
  let use =
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
      (module M),
    );
  };

  let useWithVariables =
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
        variables,
      ) => {
    useMutationWithVariables(
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
      ~variables,
      (module M),
    );
  };
};

module ExtendNoRequiredVariables = (M: Types.OperationNoRequiredVars) => {
  let use =
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
    useMutation0(
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
      (module M),
    );
  };

  let useWithVariables =
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
        variables,
      ) => {
    useMutationWithVariables(
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
      ~variables,
      (module M),
    );
  };
};
