module ApolloClient = ApolloClient__Core_ApolloClient
module ApolloError = ApolloClient__Errors_ApolloError
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted
module Graphql = ApolloClient__Graphql
module MutationHookOptions = ApolloClient__React_Types.MutationHookOptions
module MutationTuple = ApolloClient__React_Types.MutationTuple
module MutationTuple__noVariables = ApolloClient__React_Types.MutationTuple__noVariables
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn
module OperationVariables = ApolloClient__Core_Types.OperationVariables
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription
module Types = ApolloClient__Types
module Utils = ApolloClient__Utils

module type Operation = Types.Operation
module type OperationNoRequiredVars = Types.OperationNoRequiredVars

module Js_ = {
  // export declare function useMutation<TData = any, TVariables = OperationVariables>(mutation: DocumentNode, options?: MutationHookOptions<TData, TVariables>): MutationTuple<TData, TVariables>;
  @module("@apollo/client")
  external useMutation: (
    . Graphql.documentNode,
    MutationHookOptions.Js_.t<'jsData, 'jsVariables>,
  ) => MutationTuple.Js_.t<'jsData, 'jsVariables> = "useMutation"
}

let useMutation:
  type data variables jsVariables. (
    ~mutation: module(Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~awaitRefetchQueries: bool=?,
    ~context: Js.Json.t=?,
    ~client: ApolloClient.t=?,
    ~errorPolicy: ErrorPolicy.t=?,
    ~fetchPolicy: FetchPolicy__noCacheExtracted.t=?,
    ~ignoreResults: bool=?,
    ~notifyOnNetworkStatusChange: bool=?,
    ~onError: ApolloError.t => unit=?,
    ~onCompleted: Types.parseResult<data> => unit=?,
    ~optimisticResponse: jsVariables => data=?,
    ~refetchQueries: RefetchQueryDescription.t=?,
    ~update: MutationUpdaterFn.t<data>=?,
    unit,
  ) => MutationTuple.t<data, variables, jsVariables> =
  (
    ~mutation as module(Operation),
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
    let safeParse = Utils.safeParse(Operation.parse)

    let jsMutationTuple = Js_.useMutation(.
      Operation.query,
      MutationHookOptions.toJs(
        {
          mutation: None,
          awaitRefetchQueries: awaitRefetchQueries,
          context: context,
          client: client,
          errorPolicy: errorPolicy,
          fetchPolicy: fetchPolicy,
          ignoreResults: ignoreResults,
          notifyOnNetworkStatusChange: notifyOnNetworkStatusChange,
          onError: onError,
          onCompleted: onCompleted,
          optimisticResponse: optimisticResponse,
          refetchQueries: refetchQueries,
          update: update,
          variables: None,
        },
        ~mapJsVariables=Utils.identity,
        ~safeParse,
        ~serialize=Operation.serialize,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )

    Utils.useGuaranteedMemo1(
      () =>
        jsMutationTuple->MutationTuple.fromJs(
          ~safeParse,
          ~serialize=Operation.serialize,
          ~serializeVariables=Operation.serializeVariables,
        ),
      jsMutationTuple,
    )
  }

let useMutationWithVariables:
  type data variables jsVariables. (
    ~mutation: module(Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~awaitRefetchQueries: bool=?,
    ~context: Js.Json.t=?,
    ~client: ApolloClient.t=?,
    ~errorPolicy: ErrorPolicy.t=?,
    ~fetchPolicy: FetchPolicy__noCacheExtracted.t=?,
    ~ignoreResults: bool=?,
    ~mapJsVariables: jsVariables => jsVariables=?,
    ~notifyOnNetworkStatusChange: bool=?,
    ~onError: ApolloError.t => unit=?,
    ~onCompleted: Types.parseResult<data> => unit=?,
    ~optimisticResponse: jsVariables => data=?,
    ~refetchQueries: RefetchQueryDescription.t=?,
    ~update: MutationUpdaterFn.t<data>=?,
    variables,
  ) => MutationTuple__noVariables.t<data, jsVariables> =
  (
    ~mutation as module(Operation),
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
    let safeParse = Utils.safeParse(Operation.parse)

    let jsMutationTuple = Js_.useMutation(.
      Operation.query,
      MutationHookOptions.toJs(
        {
          mutation: None,
          awaitRefetchQueries: awaitRefetchQueries,
          context: context,
          client: client,
          errorPolicy: errorPolicy,
          fetchPolicy: fetchPolicy,
          ignoreResults: ignoreResults,
          notifyOnNetworkStatusChange: notifyOnNetworkStatusChange,
          onError: onError,
          onCompleted: onCompleted,
          optimisticResponse: optimisticResponse,
          refetchQueries: refetchQueries,
          update: update,
          variables: Some(variables),
        },
        ~mapJsVariables,
        ~safeParse,
        ~serialize=Operation.serialize,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )

    Utils.useGuaranteedMemo1(() => {
      let (mutate, mutationResult) =
        jsMutationTuple->MutationTuple__noVariables.fromJs(
          ~mapJsVariables,
          ~safeParse,
          ~serialize=Operation.serialize,
          ~serializeVariables=Operation.serializeVariables,
          ~variables,
        )
      (mutate, mutationResult)
    }, jsMutationTuple)
  }

module Extend = (M: Types.Operation) => {
  let use = (
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
  ) =>
    useMutation(
      ~mutation=module(M),
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
    )

  let useWithVariables = (
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
  ) =>
    useMutationWithVariables(
      ~mutation=module(M),
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
    )
}
