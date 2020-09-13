module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy;
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
module FetchResult = ApolloClient__Link_Core_Types.FetchResult;
module Graphql = ApolloClient__Graphql;
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn;
module NetworkStatus = ApolloClient__Core_NetworkStatus.NetworkStatus;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module SubscribeToMoreOptions = ApolloClient__Core_WatchQueryOptions.SubscribeToMoreOptions;
module Types = ApolloClient__Types;
module UpdateQueryFn = ApolloClient__Core_WatchQueryOptions.UpdateQueryFn;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module type Operation = Types.Operation;

module QueryHookOptions = {
  module Js_ = {
    // export interface QueryHookOptions<TData = any, TVariables = OperationVariables> extends QueryFunctionOptions<TData, TVariables> {
    //     query?: DocumentNode;
    // }
    type t('jsData, 'jsVariables) = {
      query: option(Graphql.documentNode),
      // ...extends QueryFunctionOptions
      displayName: option(string),
      skip: option(bool),
      onCompleted: option('jsData => unit),
      onError: option((. ApolloError.Js_.t) => unit),
      // ..extends BaseQueryOptions
      client: option(ApolloClient.t),
      context: option(Js.Json.t), // ACTUAL: Record<string, any>
      errorPolicy: option(string),
      fetchPolicy: option(string),
      notifyOnNetworkStatusChange: option(bool),
      partialRefetch: option(bool),
      pollInterval: option(int),
      // INTENTIONALLY IGNORED (but now with safeParse and result unwrapping, maybe it shouldn't be?)
      // returnPartialData: option(bool),
      ssr: option(bool),
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
    };
  };

  type t('data, 'jsVariables) = {
    query: option(Graphql.documentNode),
    // ...extends QueryFunctionOptions
    displayName: option(string),
    skip: option(bool),
    onCompleted: option(Types.parseResult('data) => unit),
    onError: option(ApolloError.t => unit),
    // ...extends BaseQueryOptions
    client: option(ApolloClient.t),
    context: option(Js.Json.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    notifyOnNetworkStatusChange: option(bool),
    partialRefetch: option(bool),
    pollInterval: option(int),
    // INTENTIONALLY IGNORED (but now with safeParse and result unwrapping, maybe it shouldn't be?)
    // returnPartialData: option(bool),
    ssr: option(bool),
    variables: 'jsVariables,
  };

  let toJs =
      (
        t: t('data, 'jsVariables),
        ~safeParse: Types.safeParse('data, 'jsData),
      )
      : Js_.t('jsData, 'jsVariables) => {
    client: t.client,
    context: t.context,
    displayName: t.displayName,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    onCompleted:
      t.onCompleted
      ->Belt.Option.map((onCompleted, jsData) =>
          onCompleted(jsData->safeParse)
        ),
    onError:
      t.onError
      ->Belt.Option.map(onError =>
          (. jsApolloError) => onError(ApolloError.fromJs(jsApolloError))
        ),
    fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    notifyOnNetworkStatusChange: t.notifyOnNetworkStatusChange,
    query: t.query,
    pollInterval: t.pollInterval,
    partialRefetch: t.partialRefetch,
    skip: t.skip,
    ssr: t.ssr,
    variables: t.variables,
  };
};

module LazyQueryHookOptions = {
  module Js_ = {
    // export interface LazyQueryHookOptions<TData = any, TVariables = OperationVariables> extends Omit<QueryFunctionOptions<TData, TVariables>, 'skip'> {
    //     query?: DocumentNode;
    // }
    [@bs.deriving abstract]
    type t('jsData, 'jsVariables) = {
      [@bs.optional]
      query: Graphql.documentNode,
      // ...extends QueryFunctionOptions
      [@bs.optional]
      displayName: string,
      [@bs.optional]
      onCompleted: 'jsData => unit,
      [@bs.optional]
      onError: (. ApolloError.Js_.t) => unit,
      // ..extends BaseQueryOptions
      [@bs.optional]
      client: ApolloClient.t,
      [@bs.optional]
      context: Js.Json.t, // ACTUAL: Record<string, any>
      [@bs.optional]
      errorPolicy: string,
      [@bs.optional]
      fetchPolicy: string,
      [@bs.optional]
      notifyOnNetworkStatusChange: bool,
      [@bs.optional]
      partialRefetch: bool,
      [@bs.optional]
      pollInterval: int,
      // INTENTIONALLY IGNORED (but now with safeParse and result unwrapping, maybe it shouldn't be?)
      // returnPartialData: option(bool),
      [@bs.optional]
      ssr: bool,
      [@bs.optional]
      variables: 'jsVariables,
    };
    let make = t;
  };

  type t('data, 'jsVariables) = {
    query: option(Graphql.documentNode),
    // ...extends QueryFunctionOptions
    displayName: option(string),
    onCompleted: option(Types.parseResult('data) => unit),
    onError: option(ApolloError.t => unit),
    // ...extends BaseQueryOptions
    client: option(ApolloClient.t),
    context: option(Js.Json.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    notifyOnNetworkStatusChange: option(bool),
    partialRefetch: option(bool),
    pollInterval: option(int),
    // INTENTIONALLY IGNORED (but now with safeParse and result unwrapping, maybe it shouldn't be?)
    // returnPartialData: option(bool),
    ssr: option(bool),
    variables: option('jsVariables),
  };

  let toJs =
      (
        t: t('data, 'jsVariables),
        ~safeParse: Types.safeParse('data, 'jsData),
      )
      : Js_.t('jsData, 'jsVariables) =>
    Js_.make(
      ~client=?t.client,
      ~context=?t.context,
      ~displayName=?t.displayName,
      ~errorPolicy=?t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      ~onCompleted=?
        t.onCompleted
        ->Belt.Option.map((onCompleted, jsData) =>
            onCompleted(jsData->safeParse)
          ),
      ~onError=?
        t.onError
        ->Belt.Option.map(onError =>
            (. jsApolloError) => onError(ApolloError.fromJs(jsApolloError))
          ),
      ~fetchPolicy=?
        t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
      ~notifyOnNetworkStatusChange=?t.notifyOnNetworkStatusChange,
      ~query=?t.query,
      ~pollInterval=?t.pollInterval,
      ~partialRefetch=?t.partialRefetch,
      ~ssr=?t.ssr,
      ~variables=?t.variables,
      (),
    );
};
module QueryLazyOptions = {
  module Js_ = {
    // export interface QueryLazyOptions<TVariables> {
    //     variables?: TVariables;
    //     context?: Context;
    // }
    type t('jsVariables) = {
      variables: 'jsVariables,
      context: option(Js.Json.t),
    };
  };

  type t('jsVariables) = Js_.t('jsVariables);
};

module QueryResult = {
  type useMethodFunctionsInThisModuleInstead;

  module Js_ = {
    type t_fetchMoreOptions_updateQueryOptions('jsData, 'jsVariables) = {
      fetchMoreResult: option('jsData),
      variables: option('jsVariables),
    };

    // We use abstract because Apollo is looking at query key, not just value
    [@bs.deriving abstract]
    type t_fetchMoreOptions('jsData, 'jsVariables) = {
      [@bs.optional]
      query: Graphql.Language.documentNode,
      // ...extends FetchMoreQueryOptions
      [@bs.optional]
      variables: 'jsVariables,
      [@bs.optional]
      context: Js.Json.t,
      // ...extends FetchMoreOptions
      [@bs.optional]
      updateQuery:
        (
          . 'jsData,
          t_fetchMoreOptions_updateQueryOptions('jsData, 'jsVariables)
        ) =>
        'jsData,
    };

    type t_updateQueryOptions('jsVariables) = {variables: 'jsVariables};

    // export interface QueryResult<TData = any, TVariables = OperationVariables> extends ObservableQueryFields<TData, TVariables> {
    //     client: ApolloClient<any>;
    //     data: TData | undefined;
    //     error?: ApolloError;
    //     loading: boolean;
    //     networkStatus: NetworkStatus;
    //     called: true;
    // }
    type t('jsData, 'jsVariables) = {
      called: bool,
      client: ApolloClient.t,
      data: option('jsData),
      error: option(ApolloError.Js_.t),
      loading: bool,
      networkStatus: NetworkStatus.t,
      // ...extends ObservableQueryFields<TData, TVariables> = Pick<ObservableQuery<TData, TVariables>, 'startPolling' | 'stopPolling' | 'subscribeToMore' | 'updateQuery' | 'refetch' | 'jsVariables'>
      fetchMore: useMethodFunctionsInThisModuleInstead,
      refetch: useMethodFunctionsInThisModuleInstead,
      startPolling: useMethodFunctionsInThisModuleInstead,
      stopPolling: useMethodFunctionsInThisModuleInstead,
      subscribeToMore: useMethodFunctionsInThisModuleInstead,
      updateQuery: useMethodFunctionsInThisModuleInstead,
      variables: 'jsVariables,
    };

    [@bs.send]
    external fetchMore:
      (
        t('jsData, 'jsVariables),
        t_fetchMoreOptions('jsData, 'jsVariables)
      ) =>
      Js.Promise.t(ApolloQueryResult.Js_.t('jsData)) =
      "fetchMore";

    [@bs.send]
    external refetch:
      (t('jsData, 'jsVariables), 'jsVariables) =>
      Js.Promise.t(ApolloQueryResult.Js_.t('jsData)) =
      "refetch";

    [@bs.send]
    external startPolling: (t('jsData, 'jsVariables), int) => unit =
      "startPolling";

    [@bs.send]
    external stopPolling: (t('jsData, 'jsVariables), unit) => unit =
      "stopPolling";

    [@bs.send]
    external updateQuery:
      (
        t('jsData, 'jsVariables),
        ('jsData, t_updateQueryOptions('jsVariables)) => 'jsData
      ) =>
      unit =
      "updateQuery";

    // subscribeToMore<TSubscriptionData = TData, TSubscriptionVariables = TVariables>(options: SubscribeToMoreOptions<TData, TSubscriptionVariables, TSubscriptionData>): () => void;
    [@bs.send]
    external subscribeToMore:
      (
        t('jsData, 'jsVariables),
        SubscribeToMoreOptions.Js_.t(
          'jsData,
          'subscriptionVariables,
          'jsSubscriptionData,
        )
      ) =>
      unit =
      "subscribeToMore";
  };

  type t_updateQueryOptions('jsVariables) =
    Js_.t_updateQueryOptions('jsVariables);

  type t_fetchMoreOptions_updateQueryOptions('jsData, 'data, 'jsVariables) = {
    fetchMoreResult: option('data),
    variables: option('jsVariables),
  };

  type t_fetchMoreOptions('jsData, 'data, 'jsVariables) = {
    query: option(Graphql.Language.documentNode),
    // ...extends FetchMoreQueryOptions
    variables: option('jsVariables),
    context: option(Js.Json.t),
    // ...extends FetchMoreOptions
    updateQuery:
      option(
        (
          'data,
          t_fetchMoreOptions_updateQueryOptions('jsData, 'data, 'jsVariables)
        ) =>
        'data,
      ),
  };

  type t('data, 'jsData, 'jsVariables) = {
    called: bool,
    client: ApolloClient.t,
    data: option('data),
    error: option(ApolloError.t),
    loading: bool,
    networkStatus: NetworkStatus.t,
    fetchMore: useMethodFunctionsInThisModuleInstead,
    refetch: useMethodFunctionsInThisModuleInstead,
    startPolling: useMethodFunctionsInThisModuleInstead,
    stopPolling: useMethodFunctionsInThisModuleInstead,
    subscribeToMore: useMethodFunctionsInThisModuleInstead,
    updateQuery: useMethodFunctionsInThisModuleInstead,
    __safeParse: Types.safeParse('data, 'jsData),
    __serialize: 'data => 'jsData,
  };

  external unsafeCastForMethod:
    t('data, 'jsData, 'jsVariables) => Js_.t('jsData, 'jsVariables) =
    "%identity";

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'jsData, 'jsVariables) =
    (js, ~safeParse, ~serialize) => {
      let (data, error) =
        Utils.safeParseAndLiftToCommonResultProps(
          ~jsData=js.data,
          ~apolloError=?js.error->Belt.Option.map(ApolloError.fromJs),
          safeParse,
        );
      {
        called: js.called,
        client: js.client,
        data,
        error,
        loading: js.loading,
        networkStatus: js.networkStatus,
        fetchMore: js.fetchMore,
        refetch: js.refetch,
        startPolling: js.startPolling,
        stopPolling: js.stopPolling,
        subscribeToMore: js.subscribeToMore,
        updateQuery: js.updateQuery,
        __safeParse: safeParse,
        __serialize: serialize,
      };
    };

  let fetchMore:
    (
      t('data, 'jsData, 'jsVariables),
      ~context: Js.Json.t=?,
      ~variables: 'jsVariables=?,
      ~updateQuery: (
                      'data,
                      t_fetchMoreOptions_updateQueryOptions(
                        'jsData,
                        'data,
                        'jsVariables,
                      )
                    ) =>
                    'data
                      =?,
      unit
    ) =>
    Promise.t(ApolloQueryResult.t('data)) =
    (queryResult, ~context=?, ~variables=?, ~updateQuery=?, ()) => {
      let serialize = queryResult.__serialize;
      let safeParse = queryResult.__safeParse;

      let parseErrorDuringCall: ref(option(Types.parseResult(_))) =
        ref(None);

      queryResult
      ->unsafeCastForMethod
      ->Js_.fetchMore(
          Js_.t_fetchMoreOptions(
            ~context?,
            ~updateQuery=?
              updateQuery->Belt.Option.map(updateQuery =>
                (.
                  previousResult,
                  jsFetchMoreOptions:
                    Js_.t_fetchMoreOptions_updateQueryOptions(
                      'jsData,
                      'jsVariables,
                    ),
                ) => {
                  switch (
                    safeParse(previousResult),
                    jsFetchMoreOptions.fetchMoreResult
                    ->Belt.Option.map(safeParse),
                  ) {
                  | (Data(previousResult), Some(Data(fetchMoreResult))) =>
                    updateQuery(
                      previousResult,
                      {
                        fetchMoreResult: Some(fetchMoreResult),
                        variables: jsFetchMoreOptions.variables,
                      },
                    )
                    ->serialize
                  | (Data(previousResult), None) =>
                    updateQuery(
                      previousResult,
                      {
                        fetchMoreResult: None,
                        variables: jsFetchMoreOptions.variables,
                      },
                    )
                    ->serialize
                  | (ParseError(parseError), _)
                  | (Data(_), Some(ParseError(parseError))) =>
                    parseErrorDuringCall.contents =
                      Some(ParseError(parseError));
                    previousResult;
                  };
                }
              ),
            ~variables?,
            (),
          ),
        )
      ->Promise.Js.fromBsPromise
      ->Promise.Js.toResult
      ->Promise.map(result => {
          switch (result) {
          | Ok(jsApolloQueryResult) =>
            switch (parseErrorDuringCall.contents) {
            | Some(ParseError(parseError)) =>
              ApolloQueryResult.fromError(
                ApolloError.make(~networkError=ParseError(parseError), ()),
              )
            | _ => ApolloQueryResult.fromJs(jsApolloQueryResult, ~safeParse)
            }
          | Error(error) =>
            ApolloQueryResult.fromError(
              ApolloError.make(
                ~networkError=FetchFailure(Utils.(ensureError(Any(error)))),
                (),
              ),
            )
          }
        });
    };

  let refetch:
    (t('data, 'jsData, 'jsVariables), 'jsVariables) =>
    Promise.t(ApolloQueryResult.t('data)) =
    (queryResult, variables) =>
      queryResult
      ->unsafeCastForMethod
      ->Js_.refetch(variables)
      ->Promise.Js.fromBsPromise
      ->Promise.Js.toResult
      ->Promise.map(result =>
          switch (result) {
          | Ok(jsApolloQueryResult) =>
            jsApolloQueryResult->ApolloQueryResult.fromJs(
              ~safeParse=queryResult.__safeParse,
            )
          | Error(error) =>
            ApolloQueryResult.fromError(
              ApolloError.make(
                ~networkError=FetchFailure(Utils.ensureError(Any(error))),
                (),
              ),
            )
          }
        );

  [@bs.send]
  external startPolling: (t('data, 'jsData, 'jsVariables), int) => unit =
    "startPolling";

  [@bs.send]
  external stopPolling: (t('data, 'jsData, 'jsVariables), unit) => unit =
    "stopPolling";

  type subscribeToMore_error =
    | ParseError(Types.parseError)
    | SubscriptionError(Js.Exn.t);

  let subscribeToMore:
    type subscriptionData subscriptionVariables.
      (
        t('queryData, 'jsQueryData, 'jsVariables),
        ~subscription: (module Operation with
                          type t = subscriptionData and
                          type Raw.t_variables = subscriptionVariables),
        ~updateQuery: UpdateQueryFn.t(
                        'queryData,
                        subscriptionVariables,
                        subscriptionData,
                      )
                        =?,
        ~onError: subscribeToMore_error => unit=?,
        ~context: Js.Json.t=?,
        subscriptionVariables
      ) =>
      unit =
    (
      queryResult,
      ~subscription as (module Operation),
      ~updateQuery=?,
      ~onError=?,
      ~context=?,
      variables,
    ) => {
      let subscriptionSafeParse = Utils.safeParse(Operation.parse);

      queryResult
      ->unsafeCastForMethod
      ->Js_.subscribeToMore(
          SubscribeToMoreOptions.toJs(
            {
              document: Operation.query,
              variables,
              updateQuery,
              onError:
                onError->Belt.Option.map((onError, error) =>
                  onError(SubscriptionError(error))
                ),
              context,
            },
            ~onUpdateQueryParseError=
              parseError =>
                switch (onError) {
                | Some(onError) => onError(ParseError(parseError))
                | None => ()
                },
            ~querySafeParse=queryResult.__safeParse,
            ~querySerialize=queryResult.__serialize,
            ~subscriptionSafeParse,
          ),
        );
    };

  let updateQuery:
    (
      t('data, 'jsData, 'jsVariables),
      (Types.parseResult('data), t_updateQueryOptions('jsVariables)) => 'data
    ) =>
    unit =
    (queryResult, updateQueryFn) => {
      let safeParse = queryResult.__safeParse;
      let serialize = queryResult.__serialize;
      queryResult
      ->unsafeCastForMethod
      ->Js_.updateQuery((jsPreviousData, options) => {
          updateQueryFn(jsPreviousData->safeParse, options)->serialize
        });
    };
};

module UnexecutedLazyResult = {
  module Js_ = {
    // declare type UnexecutedLazyFields = {
    //     loading: false;
    //     networkStatus: NetworkStatus.ready;
    //     called: false;
    //     data: undefined;
    // };
    // declare type UnexecutedLazyResult = UnexecutedLazyFields & AbsentLazyResultFields;
    type t = {
      loading: bool,
      networkStatus: NetworkStatus.Js_.t,
      called: bool,
    };
  };
  type t = {
    loading: bool,
    networkStatus: NetworkStatus.t,
    called: bool,
  };

  let fromJs: Js_.t => t =
    js => {
      loading: js.loading,
      networkStatus: js.networkStatus->NetworkStatus.fromJs,
      called: js.called,
    };
};

module LazyQueryResult = {
  module Js_ = {
    module Union: {
      type t;
      let unexecutedLazyResult: UnexecutedLazyResult.Js_.t => t;
      let queryResult: QueryResult.Js_.t('jsData, 'jsVariables) => t;
      type case('jsData, 'jsVariables) =
        | UnexecutedLazyResult(UnexecutedLazyResult.Js_.t)
        | QueryResult(QueryResult.Js_.t('jsData, 'jsVariables));
      let classify: t => case('jsData, 'jsVariables);
    } = {
      [@unboxed]
      type t =
        | Any('a): t;
      let unexecutedLazyResult = (v: UnexecutedLazyResult.Js_.t) => Any(v);
      let queryResult = (v: QueryResult.Js_.t('jsData, 'jsVariables)) =>
        Any(v);
      type case('jsData, 'jsVariables) =
        | UnexecutedLazyResult(UnexecutedLazyResult.Js_.t)
        | QueryResult(QueryResult.Js_.t('jsData, 'jsVariables));
      let classify = (Any(v): t): case('jsData, 'jsVariables) =>
        if ([%raw {|function (value) { return "client" in value}|}](v)) {
          QueryResult(
            Obj.magic(v): QueryResult.Js_.t('jsData, 'jsVariables),
          );
        } else {
          UnexecutedLazyResult(Obj.magic(v): UnexecutedLazyResult.Js_.t);
        };
    };
    // export declare type LazyQueryResult<TData, TVariables> = UnexecutedLazyResult | QueryResult<TData, TVariables>;
    type t('jsData, 'jsVariables) = Union.t;
  };

  type t('data, 'jsData, 'jsVariables) =
    | Executed(QueryResult.t('data, 'jsData, 'jsVariables))
    | Unexecuted(UnexecutedLazyResult.t);

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'jsData, 'jsVariables) =
    (js, ~safeParse, ~serialize) => {
      switch (js->Js_.Union.classify) {
      | UnexecutedLazyResult(v) => Unexecuted(v->UnexecutedLazyResult.fromJs)
      | QueryResult(v) =>
        Executed(v->QueryResult.fromJs(~safeParse, ~serialize))
      };
    };
};

module QueryTuple = {
  module Js_ = {
    // export declare type QueryTuple<TData, TVariables> = [(options?: QueryLazyOptions<TVariables>) => void, LazyQueryResult<TData, TVariables>];
    type t('jsData, 'variables, 'jsVariables) = (
      QueryLazyOptions.Js_.t('jsVariables) => unit,
      LazyQueryResult.Js_.t('jsData, 'jsVariables),
    );
  };

  type t('data, 'jsData, 'variables, 'jsVariables) = (
    (
      ~context: Js.Json.t=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      'variables
    ) =>
    unit,
    LazyQueryResult.t('data, 'jsData, 'jsVariables),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData,
      ~serializeVariables: 'variables => 'jsVariables
    ) =>
    t('data, 'jsData, 'variables, 'jsVariables) =
    (
      (jsExecuteQuery, jsLazyQueryResult),
      ~safeParse,
      ~serialize,
      ~serializeVariables,
    ) => (
      (~context=?, ~mapJsVariables=ApolloClient__Utils.identity, variables) =>
        jsExecuteQuery({
          context,
          variables: variables->serializeVariables->mapJsVariables,
        }),
      jsLazyQueryResult->LazyQueryResult.fromJs(~safeParse, ~serialize),
    );
};

module QueryTuple__noVariables = {
  module Js_ = {
    type t('jsData, 'variables, 'jsVariables) =
      QueryTuple.Js_.t('jsData, 'variables, 'jsVariables);
  };

  type t('data, 'jsData, 'jsVariables) = (
    (~context: Js.Json.t=?, unit) => unit,
    LazyQueryResult.t('data, 'jsData, 'jsVariables),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData,
      ~variables: 'jsVariables
    ) =>
    t('data, 'jsData, 'jsVariables) =
    ((jsExecuteQuery, jsLazyQueryResult), ~safeParse, ~serialize, ~variables) => (
      (~context=?, ()) => jsExecuteQuery({context, variables}),
      jsLazyQueryResult->LazyQueryResult.fromJs(~safeParse, ~serialize),
    );
};

module BaseMutationOptions = {
  module Js_ = {
    // export interface BaseMutationOptions<TData = any, TVariables = OperationVariables> {
    //     awaitRefetchQueries?: boolean;
    //     client?: ApolloClient<object>;
    //     context?: Context;
    //     errorPolicy?: ErrorPolicy;
    //     fetchPolicy?: Extract<WatchQueryFetchPolicy, 'no-cache'>;
    //     ignoreResults?: boolean;
    //     onCompleted?: (data: TData) => void;
    //     onError?: (error: ApolloError) => void;
    //     optimisticResponse?: TData | ((vars: TVariables) => TData);
    //     notifyOnNetworkStatusChange?: boolean;
    //     refetchQueries?: Array<string | PureQueryOptions> | RefetchQueriesFunction;
    //     update?: MutationUpdaterFn<TData>;
    //     variables?: TVariables;
    // }
    type t('jsData, 'jsVariables) = {
      awaitRefetchQueries: option(bool),
      client: option(ApolloClient.Js_.t),
      context: option(Js.Json.t), // actual: option(Context)
      errorPolicy: option(ErrorPolicy.Js_.t),
      fetchPolicy: option(FetchPolicy__noCacheExtracted.Js_.t),
      ignoreResults: option(bool),
      notifyOnNetworkStatusChange: option(bool),
      onError: option(ApolloError.Js_.t => unit),
      optimisticResponse: option('jsVariables => 'jsData),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      variables: option('jsVariables),
    };
  };

  type t('data, 'jsVariables) = {
    awaitRefetchQueries: option(bool),
    context: option(Js.Json.t),
    client: option(ApolloClient.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    ignoreResults: option(bool),
    notifyOnNetworkStatusChange: option(bool),
    onError: option(ApolloError.t => unit),
    onCompleted: option('data => unit),
    optimisticResponse: option('jsVariables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    variables: option('jsVariables),
  };
};

module MutationHookOptions = {
  module Js_ = {
    // export interface MutationHookOptions<TData = any, TVariables = OperationVariables> extends BaseMutationOptions<TData, TVariables> {
    //   mutation?: DocumentNode;
    // }
    /**
     * We use deriving abstract here because option('jsVariables) is not typesafe,
     * but still needs to be optional since a user has the option of providing
     * the variables to the results of the hook rather than the hook itself
     */
    [@bs.deriving abstract]
    type t('jsData, 'jsVariables) = {
      [@bs.optional]
      mutation: Graphql.documentNode,
      // ...extends BaseMutationOptions
      [@bs.optional]
      awaitRefetchQueries: bool,
      [@bs.optional]
      client: ApolloClient.Js_.t,
      [@bs.optional]
      context: Js.Json.t, // actual: option(Context)
      [@bs.optional]
      errorPolicy: ErrorPolicy.Js_.t,
      [@bs.optional]
      fetchPolicy: FetchPolicy__noCacheExtracted.Js_.t,
      [@bs.optional]
      ignoreResults: bool,
      [@bs.optional]
      notifyOnNetworkStatusChange: bool,
      [@bs.optional]
      onError: (. ApolloError.Js_.t) => unit,
      [@bs.optional]
      optimisticResponse: 'jsVariables => 'jsData,
      [@bs.optional]
      refetchQueries: RefetchQueryDescription.Js_.t,
      [@bs.optional]
      update: MutationUpdaterFn.Js_.t('jsData),
      [@bs.optional]
      variables: 'jsVariables,
    };
    let make = t;
  };

  type t('data, 'jsVariables) = {
    mutation: option(Graphql.documentNode),
    awaitRefetchQueries: option(bool),
    context: option(Js.Json.t),
    client: option(ApolloClient.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    ignoreResults: option(bool),
    notifyOnNetworkStatusChange: option(bool),
    onError: option(ApolloError.t => unit),
    onCompleted: option('data => unit),
    optimisticResponse: option('jsVariables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    variables: option('jsVariables),
  };

  let toJs:
    (
      t('data, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData
    ) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~safeParse, ~serialize) => {
      Js_.make(
        ~awaitRefetchQueries=?t.awaitRefetchQueries,
        ~context=?t.context,
        ~client=?t.client,
        ~errorPolicy=?t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
        ~fetchPolicy=?
          t.fetchPolicy->Belt.Option.map(FetchPolicy__noCacheExtracted.toJs),
        ~ignoreResults=?t.ignoreResults,
        ~mutation=?t.mutation,
        ~notifyOnNetworkStatusChange=?t.notifyOnNetworkStatusChange,
        ~onError=?
          t.onError
          ->Belt.Option.map(onError =>
              (. jsApolloError) =>
                onError(ApolloError.fromJs(jsApolloError))
            ),
        ~optimisticResponse=?
          t.optimisticResponse
          ->Belt.Option.map((optimisticResponse, variables) =>
              optimisticResponse(variables)->serialize
            ),
        ~refetchQueries=?
          t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
        ~update=?
          t.update->Belt.Option.map(MutationUpdaterFn.toJs(~safeParse)),
        ~variables=?t.variables,
        (),
      );
    };
};

module MutationResult = {
  module Js_ = {
    // export interface MutationResult<TData = any> {
    //     data?: TData | null;
    //     error?: ApolloError;
    //     loading: boolean;
    //     called: boolean;
    //     client?: ApolloClient<object>;
    // }
    type t('jsData) = {
      data: Js.nullable('jsData),
      error: option(ApolloError.Js_.t),
      loading: bool,
      called: bool,
      client: option(ApolloClient.Js_.t),
    };
  };

  type t('data) = {
    data: option('data),
    error: option(ApolloError.t),
    loading: bool,
    called: bool,
    client: option(ApolloClient.t),
  };

  let fromJs:
    (Js_.t('jsData), ~safeParse: Types.safeParse('data, 'jsData)) =>
    t('data) =
    (js, ~safeParse) => {
      let (data, error) =
        Utils.safeParseAndLiftToCommonResultProps(
          ~jsData=js.data->Js.toOption,
          ~apolloError=?js.error->Belt.Option.map(ApolloError.fromJs),
          safeParse,
        );
      {
        data,
        error,
        loading: js.loading,
        called: js.called,
        client: js.client,
      };
    };
};

module MutationFunctionOptions = {
  module Js_ = {
    // export interface MutationFunctionOptions<TData = any, TVariables = OperationVariables> {
    //     variables?: TVariables;
    //     optimisticResponse?: TData | ((vars: TVariables | {}) => TData);
    //     refetchQueries?: Array<string | PureQueryOptions> | RefetchQueriesFunction;
    //     awaitRefetchQueries?: boolean;
    //     update?: MutationUpdaterFn<TData>;
    //     context?: Context;
    //     fetchPolicy?: WatchQueryFetchPolicy;
    // }
    /**
     * We use deriving abstract here because this is used in a context where passing in explicit
     * properties could override one already passed in
     */
    type t('jsData, 'jsVariables) = {
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      optimisticResponse: option((. 'jsVariables) => 'jsData),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      awaitRefetchQueries: option(bool),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      context: option(Js.Json.t), // actual: option(Context)
      fetchPolicy: option(WatchQueryFetchPolicy.Js_.t),
    };
  };

  type t('data, 'jsVariables) = {
    variables: 'jsVariables,
    optimisticResponse: option('jsVariables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    awaitRefetchQueries: option(bool),
    update: option(MutationUpdaterFn.t('data)),
    context: option(Js.Json.t), // actual: option(Context)
    fetchPolicy: option(WatchQueryFetchPolicy.t),
  };

  let toJs:
    (
      t('data, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData
    ) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~safeParse, ~serialize) => {
      variables: t.variables,
      optimisticResponse:
        t.optimisticResponse
        ->Belt.Option.map(optimisticResponse =>
            (. variables) => optimisticResponse(variables)->serialize
          ),
      refetchQueries:
        t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
      awaitRefetchQueries: t.awaitRefetchQueries,
      update: t.update->Belt.Option.map(MutationUpdaterFn.toJs(~safeParse)),
      context: t.context,
      fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    };
};

module MutationTuple = {
  module Js_ = {
    // export declare type MutationTuple<TData, TVariables> = [(options?: MutationFunctionOptions<TData, TVariables>) => Promise<FetchResult<TData>>, MutationResult<TData>];
    type t('jsData, 'jsVariables) = (
      option(MutationFunctionOptions.Js_.t('jsData, 'jsVariables)) =>
      Js.Promise.t(FetchResult.Js_.t('jsData)),
      MutationResult.Js_.t('jsData),
    );
  };
  type t_mutationFn('data, 'variables, 'jsVariables) =
    (
      ~awaitRefetchQueries: bool=?,
      ~context: Js.Json.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      ~optimisticResponse: 'jsVariables => 'data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~update: MutationUpdaterFn.t('data)=?,
      'variables
    ) =>
    Promise.t(FetchResult.t('data));

  type t('data, 'variables, 'jsVariables) = (
    t_mutationFn('data, 'variables, 'jsVariables),
    MutationResult.t('data),
  );

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData,
      ~serializeVariables: 'variables => 'jsVariables
    ) =>
    t('data, 'variables, 'jsVariables) =
    (
      (jsMutationFn, jsMutationResult),
      ~safeParse,
      ~serialize,
      ~serializeVariables,
    ) => {
      let mutationFn =
          (
            ~awaitRefetchQueries=?,
            ~context=?,
            ~fetchPolicy=?,
            ~mapJsVariables=Utils.identity,
            ~optimisticResponse=?,
            ~refetchQueries=?,
            ~update=?,
            variables,
          ) => {
        jsMutationFn(
          Some(
            MutationFunctionOptions.toJs(
              {
                variables: variables->serializeVariables->mapJsVariables,
                optimisticResponse,
                refetchQueries,
                awaitRefetchQueries,
                update,
                context,
                fetchPolicy,
              },
              ~safeParse,
              ~serialize,
            ),
          ),
        )
        ->Promise.Js.fromBsPromise
        ->Promise.Js.toResult
        ->Promise.map(result =>
            switch (result) {
            | Ok(jsFetchResult) =>
              FetchResult.fromJs(jsFetchResult, ~safeParse)
            | Error(error) =>
              FetchResult.fromError(
                ApolloError.make(
                  ~networkError=FetchFailure(Utils.ensureError(Any(error))),
                  (),
                ),
              )
            }
          );
      };

      (mutationFn, jsMutationResult->MutationResult.fromJs(~safeParse));
    };
};

module MutationTuple__noVariables = {
  module Js_ = {
    type t('jsData, 'jsVariables) =
      MutationTuple.Js_.t('jsData, 'jsVariables);
  };

  type t_mutationFn('data, 'jsVariables) =
    (
      ~optimisticResponse: 'jsVariables => 'data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~awaitRefetchQueries: bool=?,
      ~update: MutationUpdaterFn.t('data)=?,
      ~context: Js.Json.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      unit
    ) =>
    Promise.t(FetchResult.t('data));

  type t('data, 'jsVariables) = (
    t_mutationFn('data, 'jsVariables),
    MutationResult.t('data),
  );

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~safeParse: Types.safeParse('data, 'jsData),
      ~serialize: 'data => 'jsData,
      ~variables: 'jsVariables
    ) =>
    t('data, 'jsVariables) =
    ((jsMutationFn, jsMutationResult), ~safeParse, ~serialize, ~variables) => {
      let mutationFn =
          (
            ~optimisticResponse=?,
            ~refetchQueries=?,
            ~awaitRefetchQueries=?,
            ~update=?,
            ~context=?,
            ~fetchPolicy=?,
            (),
          ) => {
        jsMutationFn(
          Some(
            MutationFunctionOptions.toJs(
              {
                variables,
                optimisticResponse,
                refetchQueries,
                awaitRefetchQueries,
                update,
                context,
                fetchPolicy,
              },
              ~safeParse,
              ~serialize,
            ),
          ),
        )
        ->Promise.Js.fromBsPromise
        ->Promise.Js.toResult
        ->Promise.map(result =>
            switch (result) {
            | Ok(jsFetchResult) =>
              FetchResult.fromJs(jsFetchResult, ~safeParse)
            | Error(error) =>
              FetchResult.fromError(
                ApolloError.make(
                  ~networkError=FetchFailure(Utils.ensureError(Any(error))),
                  (),
                ),
              )
            }
          );
      };

      (mutationFn, jsMutationResult->MutationResult.fromJs(~safeParse));
    };
};

module SubscriptionResult = {
  module Js_ = {
    // export interface SubscriptionResult<TData = any> {
    //     loading: boolean;
    //     data?: TData;
    //     error?: ApolloError;
    // }
    type t('jsData) = {
      loading: bool,
      data: option('jsData),
      error: option(ApolloError.Js_.t),
    };
  };

  type t('data) = {
    loading: bool,
    data: option('data),
    error: option(ApolloError.t),
  };

  let fromJs:
    (Js_.t('jsData), ~safeParse: Types.safeParse('data, 'jsData)) =>
    t('data) =
    (js, ~safeParse) => {
      let (data, error) =
        Utils.safeParseAndLiftToCommonResultProps(
          ~jsData=js.data,
          ~apolloError=?js.error->Belt.Option.map(ApolloError.fromJs),
          safeParse,
        );

      {loading: js.loading, data, error};
    };
};

module OnSubscriptionDataOptions = {
  module Js_ = {
    // export interface OnSubscriptionDataOptions<TData = any> {
    //     client: ApolloClient<object>;
    //     subscriptionData: SubscriptionResult<TData>;
    // }
    type t('jsData) = {
      client: ApolloClient.t,
      subscriptionData: SubscriptionResult.Js_.t('jsData),
    };
  };

  type t('data) = {
    client: ApolloClient.t,
    subscriptionData: SubscriptionResult.t('data),
  };

  let fromJs:
    (Js_.t('jsData), ~safeParse: Types.safeParse('data, 'jsData)) =>
    t('data) =
    (js, ~safeParse) => {
      client: js.client,
      subscriptionData:
        js.subscriptionData->SubscriptionResult.fromJs(~safeParse),
    };
};

module BaseSubscriptionOptions = {
  module Js_ = {
    // export interface BaseSubscriptionOptions<TData = any, TVariables = OperationVariables> {
    //     variables?: TVariables;
    //     fetchPolicy?: FetchPolicy;
    //     shouldResubscribe?: boolean | ((options: BaseSubscriptionOptions<TData, TVariables>) => boolean);
    //     client?: ApolloClient<object>;
    //     skip?: boolean;
    //     onSubscriptionData?: (options: OnSubscriptionDataOptions<TData>) => any;
    //     onSubscriptionComplete?: () => void;
    // }
    type t('jsData, 'jsVariables) = {
      variables: option('jsVariables),
      fetchPolicy: option(FetchPolicy.t),
      shouldResubscribe: option((. t('jsData, 'jsVariables)) => bool),
      client: option(ApolloClient.t),
      skip: option(bool),
      onSubscriptionData:
        option((. OnSubscriptionDataOptions.Js_.t('jsData)) => unit),
      onSubscriptionComplete: option(unit => unit),
    };
  };

  type t('data, 'jsVariables) = {
    variables: option('jsVariables),
    fetchPolicy: option(FetchPolicy.t),
    shouldResubscribe: option(t('data, 'jsVariables) => bool),
    client: option(ApolloClient.t),
    skip: option(bool),
    onSubscriptionData: option(OnSubscriptionDataOptions.t('data) => unit),
    onSubscriptionComplete: option(unit => unit),
  };

  let fromJs: Js_.t('jsData, 'jsVariables) => t('data, 'jsVariables) =
    js => {
      variables: js.variables,
      fetchPolicy: js.fetchPolicy,
      // shouldResubscribe: what to do here?
      shouldResubscribe: Obj.magic(js.shouldResubscribe),
      client: js.client,
      skip: js.skip,
      // onSubscriptionData: what to do here?
      onSubscriptionData: Obj.magic(js.onSubscriptionData),
      onSubscriptionComplete: js.onSubscriptionComplete,
    };
};

module SubscriptionHookOptions = {
  module Js_ = {
    // export interface SubscriptionHookOptions<TData = any, TVariables = OperationVariables> extends BaseSubscriptionOptions<TData, TVariables> {
    //     subscription?: DocumentNode;
    // }
    type t('jsData, 'jsVariables) = {
      subscription: option(Graphql.documentNode),
      // ...extends BaseSubscriptionOptions
      // Intentionally restricted to not be non-optional. `option(unit)` does not compile cleanly to `undefined`
      variables: 'jsVariables,
      fetchPolicy: option(FetchPolicy.t),
      shouldResubscribe:
        option(
          (. BaseSubscriptionOptions.Js_.t('jsData, 'jsVariables)) => bool,
        ),
      client: option(ApolloClient.t),
      skip: option(bool),
      onSubscriptionData:
        option((. OnSubscriptionDataOptions.Js_.t('jsData)) => unit),
      onSubscriptionComplete: option(unit => unit),
    };
  };

  type t('data, 'jsVariables) = {
    subscription: option(Graphql.documentNode),
    variables: 'jsVariables,
    fetchPolicy: option(FetchPolicy.t),
    shouldResubscribe:
      option(BaseSubscriptionOptions.t('data, 'jsVariables) => bool),
    client: option(ApolloClient.t),
    skip: option(bool),
    onSubscriptionData: option(OnSubscriptionDataOptions.t('data) => unit),
    onSubscriptionComplete: option(unit => unit),
  };

  let toJs:
    (t('data, 'jsVariables), ~safeParse: Types.safeParse('data, 'jsData)) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~safeParse) => {
      subscription: t.subscription,
      variables: t.variables,
      fetchPolicy: t.fetchPolicy,
      shouldResubscribe:
        t.shouldResubscribe
        ->Belt.Option.map(shouldResubscribe =>
            (. jsBaseSubscriptionOptions) =>
              shouldResubscribe(
                jsBaseSubscriptionOptions->BaseSubscriptionOptions.fromJs,
              )
          ),
      client: t.client,
      skip: t.skip,
      onSubscriptionData:
        t.onSubscriptionData
        ->Belt.Option.map(onSubscriptionData =>
            (. jsOnSubscriptionDataOptions) =>
              onSubscriptionData(
                jsOnSubscriptionDataOptions->OnSubscriptionDataOptions.fromJs(
                  ~safeParse,
                ),
              )
          ),
      onSubscriptionComplete: t.onSubscriptionComplete,
    };
};
