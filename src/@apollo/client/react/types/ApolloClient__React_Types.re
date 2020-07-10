module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__ApolloError;
module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy;
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
module FetchResult = ApolloClient__Link_Core_Types.FetchResult;
module Graphql = ApolloClient__Graphql;
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn;
module NetworkStatus = ApolloClient__Core_NetworkStatus;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module Types = ApolloClient__Types;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module QueryHookOptions = {
  module Js_ = {
    // export interface QueryHookOptions<TData = any, TVariables = OperationVariables> extends QueryFunctionOptions<TData, TVariables> {
    //     query?: DocumentNode;
    // }
    type t('jsData, 'variables) = {
      query: option(Graphql.documentNode),
      // ...extends QueryFunctionOptions
      displayName: option(string),
      skip: option(bool),
      onCompleted: option('jsData => unit),
      onError: option(ApolloError.t => unit),
      // ..extends BaseQueryOptions
      client: option(ApolloClient.t),
      context: option(Js.Json.t), // ACTUAL: Record<string, any>
      errorPolicy: option(string),
      fetchPolicy: option(string),
      notifyOnNetworkStatusChange: option(bool),
      partialRefetch: option(bool),
      pollInterval: option(int),
      // INTENTIONALLY IGNORED
      // returnPartialData: option(bool),
      ssr: option(bool),
      // We don't allow optional variables because it's not typesafe
      variables: 'variables,
    };
  };

  type t('data, 'variables) = {
    query: option(Graphql.documentNode),
    // ...extends QueryFunctionOptions
    displayName: option(string),
    skip: option(bool),
    onCompleted: option('data => unit),
    onError: option(ApolloError.t => unit),
    // ...extends BaseQueryOptions
    client: option(ApolloClient.t),
    context: option(Js.Json.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    notifyOnNetworkStatusChange: option(bool),
    partialRefetch: option(bool),
    pollInterval: option(int),
    // INTENTIONALLY IGNORED
    // returnPartialData: option(bool),
    ssr: option(bool),
    variables: 'variables,
  };

  let toJs =
      (t: t('data, 'variables), ~parse: 'jsData => 'data)
      : Js_.t('jsData, 'variables) => {
    client: t.client,
    context: t.context,
    displayName: t.displayName,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    onCompleted:
      t.onCompleted
      ->Belt.Option.map((onCompleted, jsData) => onCompleted(jsData->parse)),
    onError: t.onError,
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
    type t('jsData, 'variables) = {
      [@bs.optional]
      query: Graphql.documentNode,
      // ...extends QueryFunctionOptions
      [@bs.optional]
      displayName: string,
      [@bs.optional]
      onCompleted: 'jsData => unit,
      [@bs.optional]
      onError: ApolloError.t => unit,
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
      // INTENTIONALLY IGNORED
      // returnPartialData: option(bool),
      [@bs.optional]
      ssr: bool,
      [@bs.optional]
      variables: 'variables,
    };
    let make = t;
  };

  type t('data, 'variables) = {
    query: option(Graphql.documentNode),
    // ...extends QueryFunctionOptions
    displayName: option(string),
    onCompleted: option('data => unit),
    onError: option(ApolloError.t => unit),
    // ...extends BaseQueryOptions
    client: option(ApolloClient.t),
    context: option(Js.Json.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    notifyOnNetworkStatusChange: option(bool),
    partialRefetch: option(bool),
    pollInterval: option(int),
    // INTENTIONALLY IGNORED
    // returnPartialData: option(bool),
    ssr: option(bool),
    variables: option('variables),
  };

  let toJs =
      (t: t('data, 'variables), ~parse: 'jsData => 'data)
      : Js_.t('jsData, 'variables) =>
    Js_.make(
      ~client=?t.client,
      ~context=?t.context,
      ~displayName=?t.displayName,
      ~errorPolicy=?t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      ~onCompleted=?
        t.onCompleted
        ->Belt.Option.map((onCompleted, jsData) =>
            onCompleted(jsData->parse)
          ),
      ~onError=?t.onError,
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
    type t('variables) = {
      variables: 'variables,
      context: option(Js.Json.t),
    };
  };

  type t('variables) = Js_.t('variables);
};

module QueryResult = {
  module Js_ = {
    // TODO: 'parsedData ??? check this
    type t_fetchMoreOptions_updateQueryOptions('parsedData, 'variables) = {
      fetchMoreResult: option('parsedData),
      variables: option('variables),
    };

    type t_fetchMoreOptions('jsData, 'variables) = {
      query: option(Graphql.Language.documentNode),
      // ...extends FetchMoreQueryOptions
      variables: option('variables),
      context: option(Js.Json.t),
      // ...extends FetchMoreOptions
      updateQuery:
        option(
          (
            'jsData,
            t_fetchMoreOptions_updateQueryOptions('jsData, 'variables)
          ) =>
          'jsData,
        ),
    };

    // export interface QueryResult<TData = any, TVariables = OperationVariables> extends ObservableQueryFields<TData, TVariables> {
    //     client: ApolloClient<any>;
    //     data: TData | undefined;
    //     error?: ApolloError;
    //     loading: boolean;
    //     networkStatus: NetworkStatus;
    //     called: true;
    // }
    type t('jsData, 'variables) = {
      called: bool,
      client: ApolloClient.t,
      data: option('jsData),
      error: option(ApolloError.t),
      loading: bool,
      networkStatus: NetworkStatus.t,
      // ...extends ObservableQueryFields
      fetchMore:
        t_fetchMoreOptions('jsData, 'variables) =>
        Js.Promise.t(ApolloQueryResult.Js_.t('jsData)),
    };
  };

  type t('parsedData, 'variables) = {
    called: bool,
    client: ApolloClient.t,
    data: option('parsedData),
    error: option(ApolloError.t),
    fetchMore:
      (
        ~context: Js.Json.t=?,
        ~variables: 'variables=?,
        ~updateQuery: (
                        'parsedData,
                        Js_.t_fetchMoreOptions_updateQueryOptions(
                          'parsedData,
                          'variables,
                        )
                      ) =>
                      'parsedData
                        =?,
        unit
      ) =>
      Js.Promise.t(ApolloQueryResult.t('parsedData)),
    loading: bool,
    networkStatus: NetworkStatus.t,
  };

  let fromJs:
    (
      Js_.t('jsData, 'variables),
      ~parse: 'jsData => 'parsedData,
      ~serialize: 'parsedData => 'jsData
    ) =>
    t('parsedData, 'variables) =
    (js, ~parse, ~serialize) => {
      called: js.called,
      client: js.client,
      data: js.data->Belt.Option.map(parse),
      error: js.error,
      fetchMore:
        (~context=?, ~variables=?, ~updateQuery as jsUpdateQuery=?, ()) => {
        js.fetchMore({
          context,
          query: None,
          updateQuery:
            jsUpdateQuery->Belt.Option.map(
              (
                jsUpdateQuery,
                previousResult,
                Js_.{fetchMoreResult, variables},
              ) =>
              jsUpdateQuery(
                parse(previousResult),
                {
                  fetchMoreResult: fetchMoreResult->Belt.Option.map(parse),
                  variables,
                },
              )
              ->serialize
            ),
          variables,
        })
        ->Js.Promise.then_(
            jsResult =>
              Js.Promise.resolve(ApolloQueryResult.fromJs(jsResult, ~parse)),
            _,
          );
      },
      loading: js.loading,
      networkStatus: js.networkStatus,
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
      let queryResult: QueryResult.Js_.t('jsData, 'variables) => t;
      type case('jsData, 'variables) =
        | UnexecutedLazyResult(UnexecutedLazyResult.Js_.t)
        | QueryResult(QueryResult.Js_.t('jsData, 'variables));
      let classify: t => case('jsData, 'variables);
    } = {
      [@unboxed]
      type t =
        | Any('a): t;
      let unexecutedLazyResult = (v: UnexecutedLazyResult.Js_.t) => Any(v);
      let queryResult = (v: QueryResult.Js_.t('jsData, 'variables)) =>
        Any(v);
      type case('jsData, 'variables) =
        | UnexecutedLazyResult(UnexecutedLazyResult.Js_.t)
        | QueryResult(QueryResult.Js_.t('jsData, 'variables));
      let classify = (Any(v): t): case('jsData, 'variables) =>
        if ([%raw {|function (value) { return "client" in value}|}](v)) {
          QueryResult(Obj.magic(v): QueryResult.Js_.t('jsData, 'variables));
        } else {
          UnexecutedLazyResult(Obj.magic(v): UnexecutedLazyResult.Js_.t);
        };
    };
    // export declare type LazyQueryResult<TData, TVariables> = UnexecutedLazyResult | QueryResult<TData, TVariables>;
    type t('jsData, 'variables) = Union.t;
  };

  type t('data, 'variables) =
    | Executed(QueryResult.t('data, 'variables))
    | Unexecuted(UnexecutedLazyResult.t);

  let fromJs:
    (
      Js_.t('jsData, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'variables) =
    (js, ~parse, ~serialize) => {
      switch (js->Js_.Union.classify) {
      | UnexecutedLazyResult(v) => Unexecuted(v->UnexecutedLazyResult.fromJs)
      | QueryResult(v) => Executed(v->QueryResult.fromJs(~parse, ~serialize))
      };
    };
};

module QueryTuple = {
  module Js_ = {
    // export declare type QueryTuple<TData, TVariables> = [(options?: QueryLazyOptions<TVariables>) => void, LazyQueryResult<TData, TVariables>];
    type t('jsData, 'variables) = (
      QueryLazyOptions.Js_.t('variables) => unit,
      LazyQueryResult.Js_.t('jsData, 'variables),
    );
  };

  type t('data, 'variables) = (
    (~context: Js.Json.t=?, 'variables) => unit,
    LazyQueryResult.t('data, 'variables),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'variables) =
    ((jsExecuteQuery, jsLazyQueryResult), ~parse, ~serialize) => (
      (~context=?, variables) => jsExecuteQuery({context, variables}),
      jsLazyQueryResult->LazyQueryResult.fromJs(~parse, ~serialize),
    );
};

module QueryTuple__noVariables = {
  module Js_ = {
    type t('jsData, 'variables) = QueryTuple.Js_.t('jsData, 'variables);
  };

  type t('data, 'variables) = (
    (~context: Js.Json.t=?, unit) => unit,
    LazyQueryResult.t('data, 'variables),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData,
      ~variables: 'variables
    ) =>
    t('data, 'variables) =
    ((jsExecuteQuery, jsLazyQueryResult), ~parse, ~serialize, ~variables) => (
      (~context=?, ()) => jsExecuteQuery({context, variables}),
      jsLazyQueryResult->LazyQueryResult.fromJs(~parse, ~serialize),
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
    type t('jsData, 'variables) = {
      awaitRefetchQueries: option(bool),
      client: option(ApolloClient.Js_.t),
      context: option(Js.Json.t), // actual: option(Context)
      errorPolicy: option(ErrorPolicy.Js_.t),
      fetchPolicy: option(FetchPolicy__noCacheExtracted.Js_.t),
      ignoreResults: option(bool),
      notifyOnNetworkStatusChange: option(bool),
      onError: option(ApolloError.Js_.t => unit),
      optimisticResponse: option('variables => 'jsData),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      variables: option('variables),
    };
  };

  type t('data, 'variables) = {
    awaitRefetchQueries: option(bool),
    context: option(Js.Json.t),
    client: option(ApolloClient.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    ignoreResults: option(bool),
    notifyOnNetworkStatusChange: option(bool),
    onError: option(ApolloError.t => unit),
    onCompleted: option('data => unit),
    optimisticResponse: option('variables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    variables: option('variables),
  };
};

module MutationHookOptions = {
  module Js_ = {
    // export interface MutationHookOptions<TData = any, TVariables = OperationVariables> extends BaseMutationOptions<TData, TVariables> {
    //   mutation?: DocumentNode;
    // }
    /**
     * We use deriving abstract here because option('variables) is not typesafe,
     * but still needs to be optional since a user has the option of providing
     * the variables to the results of the hook rather than the hook itself
     */
    [@bs.deriving abstract]
    type t('jsData, 'variables) = {
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
      onError: ApolloError.Js_.t => unit,
      [@bs.optional]
      optimisticResponse: 'variables => 'jsData,
      [@bs.optional]
      refetchQueries: RefetchQueryDescription.Js_.t,
      [@bs.optional]
      update: MutationUpdaterFn.Js_.t('jsData),
      [@bs.optional]
      variables: 'variables,
    };
    let make = t;
  };

  type t('data, 'variables) = {
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
    optimisticResponse: option('variables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    variables: option('variables),
  };

  let toJs:
    (
      t('data, 'variables),
      ~parse: Types.parse('jsData, 'data),
      ~serialize: Types.serialize('data, 'jsData)
    ) =>
    Js_.t('jsData, 'variables) =
    (t, ~parse, ~serialize) => {
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
        ~onError=?t.onError,
        ~optimisticResponse=?
          t.optimisticResponse
          ->Belt.Option.map((optimisticResponse, variables) =>
              optimisticResponse(variables)->serialize
            ),
        ~refetchQueries=?
          t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
        ~update=?t.update->Belt.Option.map(MutationUpdaterFn.toJs(~parse)),
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

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      data: js.data->Js.toOption->Belt.Option.map(parse),
      error: js.error,
      loading: js.loading,
      called: js.called,
      client: js.client,
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
    type t('jsData, 'variables) = {
      // We don't allow optional variables because it's not typesafe
      variables: 'variables,
      optimisticResponse: option((. 'variables) => 'jsData),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      awaitRefetchQueries: option(bool),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      context: option(Js.Json.t), // actual: option(Context)
      fetchPolicy: option(WatchQueryFetchPolicy.Js_.t),
    };
  };

  type t('data, 'variables) = {
    variables: 'variables,
    optimisticResponse: option('variables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    awaitRefetchQueries: option(bool),
    update: option(MutationUpdaterFn.t('data)),
    context: option(Js.Json.t), // actual: option(Context)
    fetchPolicy: option(WatchQueryFetchPolicy.t),
  };

  let toJs:
    (
      t('data, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    Js_.t('jsData, 'variables) =
    (t, ~parse, ~serialize) => {
      variables: t.variables,
      optimisticResponse:
        t.optimisticResponse
        ->Belt.Option.map(optimisticResponse =>
            (. variables) => optimisticResponse(variables)->serialize
          ),
      refetchQueries:
        t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
      awaitRefetchQueries: t.awaitRefetchQueries,
      update: t.update->Belt.Option.map(MutationUpdaterFn.toJs(~parse)),
      context: t.context,
      fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    };
};

module MutationTuple = {
  module Js_ = {
    // export declare type MutationTuple<TData, TVariables> = [(options?: MutationFunctionOptions<TData, TVariables>) => Promise<FetchResult<TData>>, MutationResult<TData>];
    type t('jsData, 'variables) = (
      option(MutationFunctionOptions.Js_.t('jsData, 'variables)) =>
      Js.Promise.t(FetchResult.Js_.t('jsData)),
      MutationResult.Js_.t('jsData),
    );
  };
  type t_mutationFn('data, 'variables) =
    (
      ~optimisticResponse: 'variables => 'data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~awaitRefetchQueries: bool=?,
      ~update: MutationUpdaterFn.t('data)=?,
      ~context: Js.Json.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      'variables
    ) =>
    Js.Promise.t(FetchResult.t('data));
  type t('data, 'variables) = (
    t_mutationFn('data, 'variables),
    MutationResult.t('data),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'variables) =
    ((jsMutationFn, jsMutationResult), ~parse, ~serialize) => {
      let mutationFn =
          (
            ~optimisticResponse=?,
            ~refetchQueries=?,
            ~awaitRefetchQueries=?,
            ~update=?,
            ~context=?,
            ~fetchPolicy=?,
            variables,
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
              ~parse,
              ~serialize,
            ),
          ),
        )
        ->Js.Promise.then_(
            jsResult =>
              FetchResult.fromJs(jsResult, ~parse)->Js.Promise.resolve,
            _,
          );
      };

      (mutationFn, jsMutationResult->MutationResult.fromJs(~parse));
    };
};

module MutationTuple__noVariables = {
  module Js_ = {
    type t('jsData, 'variables) = MutationTuple.Js_.t('jsData, 'variables);
  };

  type t_mutationFn('data, 'variables) =
    (
      ~optimisticResponse: 'variables => 'data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~awaitRefetchQueries: bool=?,
      ~update: MutationUpdaterFn.t('data)=?,
      ~context: Js.Json.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      unit
    ) =>
    Js.Promise.t(FetchResult.t('data));

  type t('data, 'variables) = (
    t_mutationFn('data, 'variables),
    MutationResult.t('data),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData,
      ~variables: 'variables
    ) =>
    t('data, 'variables) =
    ((jsMutationFn, jsMutationResult), ~parse, ~serialize, ~variables) => {
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
              ~parse,
              ~serialize,
            ),
          ),
        )
        ->Js.Promise.then_(
            jsResult =>
              FetchResult.fromJs(jsResult, ~parse)->Js.Promise.resolve,
            _,
          );
      };

      (mutationFn, jsMutationResult->MutationResult.fromJs(~parse));
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
    error: option(ApolloError.Js_.t),
  };

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      loading: js.loading,
      data: js.data->Belt.Option.map(parse),
      error: js.error,
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

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      client: js.client,
      subscriptionData:
        js.subscriptionData->SubscriptionResult.fromJs(~parse),
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
    type t('jsData, 'variables) = {
      variables: option('variables),
      fetchPolicy: option(FetchPolicy.t),
      shouldResubscribe: option((. t('jsData, 'variables)) => bool),
      client: option(ApolloClient.t),
      skip: option(bool),
      onSubscriptionData:
        option((. OnSubscriptionDataOptions.Js_.t('jsData)) => unit),
      onSubscriptionComplete: option(unit => unit),
    };
  };

  type t('data, 'variables) = {
    variables: option('variables),
    fetchPolicy: option(FetchPolicy.t),
    shouldResubscribe: option(t('data, 'variables) => bool),
    client: option(ApolloClient.t),
    skip: option(bool),
    onSubscriptionData: option(OnSubscriptionDataOptions.t('data) => unit),
    onSubscriptionComplete: option(unit => unit),
  };

  let fromJs: Js_.t('jsData, 'variables) => t('data, 'variables) =
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
    type t('jsData, 'variables) = {
      subscription: option(Graphql.documentNode),
      // ...extends BaseSubscriptionOptions
      // Intentionally restricted to not be non-optional. `option(unit)` does not compile cleanly to `undefined`
      variables: 'variables,
      fetchPolicy: option(FetchPolicy.t),
      shouldResubscribe:
        option(
          (. BaseSubscriptionOptions.Js_.t('jsData, 'variables)) => bool,
        ),
      client: option(ApolloClient.t),
      skip: option(bool),
      onSubscriptionData:
        option((. OnSubscriptionDataOptions.Js_.t('jsData)) => unit),
      onSubscriptionComplete: option(unit => unit),
    };
  };

  type t('data, 'variables) = {
    subscription: option(Graphql.documentNode),
    variables: 'variables,
    fetchPolicy: option(FetchPolicy.t),
    shouldResubscribe:
      option(BaseSubscriptionOptions.t('data, 'variables) => bool),
    client: option(ApolloClient.t),
    skip: option(bool),
    onSubscriptionData: option(OnSubscriptionDataOptions.t('data) => unit),
    onSubscriptionComplete: option(unit => unit),
  };

  let toJs:
    (t('data, 'variables), ~parse: 'jsData => 'data) =>
    Js_.t('jsData, 'variables) =
    (t, ~parse) => {
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
                  ~parse,
                ),
              )
          ),
      onSubscriptionComplete: t.onSubscriptionComplete,
    };
};
