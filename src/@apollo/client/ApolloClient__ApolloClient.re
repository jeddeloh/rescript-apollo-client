module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult;
module ApolloLink = ApolloClient__Link_Core_ApolloLink;
module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache;
module DataProxy = ApolloClient__Cache_Core_Types.DataProxy;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy;
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
module FragmentMatcher = ApolloClient__Core_LocalState.FragmentMatcher;
module Graphql = ApolloClient__Graphql;
module FetchResult = ApolloClient__Link_Core_Types.FetchResult;
module MutationOptions = ApolloClient__Core_WatchQueryOptions.MutationOptions;
module MutationQueryReducersMap = ApolloClient__Core_WatchQueryOptions.MutationQueryReducersMap;
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn;
module ObservableQuery = ApolloClient__Core_ObservableQuery.ObservableQuery;
module QueryOptions = ApolloClient__Core_WatchQueryOptions.QueryOptions;
module PureQueryOptions = ApolloClient__Core_Types.PureQueryOptions;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module Resolvers = ApolloClient__Core_Types.Resolvers;
module UriFunction = ApolloClient__Link_Http_SelectHttpOptionsAndBody.UriFunction;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;
module WatchQueryOptions = ApolloClient__Core_WatchQueryOptions.WatchQueryOptions;

module type Fragment = Types.Fragment;
module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module DefaultWatchQueryOptions = {
  module Js_ = {
    // Partial<QueryOptions>;
    type t = {
      fetchPolicy: option(WatchQueryFetchPolicy.Js_.t),
      // query: GraphQL.Language.documentNode,
      // variables: option('jsVariables),
      errorPolicy: option(ErrorPolicy.Js_.t),
      context: option(Js.Json.t),
    };
  };

  type t = {
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    errorPolicy: option(ErrorPolicy.t),
    context: option(Js.Json.t),
  };

  let toJs: t => Js_.t =
    t => {
      fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
      errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      context: t.context,
    };

  let make = (~fetchPolicy=?, ~errorPolicy=?, ~context=?, ()) => {
    fetchPolicy,
    errorPolicy,
    context,
  };
};

module DefaultQueryOptions = {
  module Js_ = {
    // Partial<QueryOptions>;
    type t = {
      fetchPolicy: option(FetchPolicy.Js_.t),
      // query: GraphQL.Language.documentNode,
      // variables: option('jsVariables),
      errorPolicy: option(ErrorPolicy.Js_.t),
      context: option(Js.Json.t),
    };
  };

  type t = {
    fetchPolicy: option(FetchPolicy.t),
    errorPolicy: option(ErrorPolicy.t),
    context: option(Js.Json.t),
  };

  let toJs: t => Js_.t =
    t => {
      fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy.toJs),
      errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      context: t.context,
    };

  let make = (~fetchPolicy=?, ~errorPolicy=?, ~context=?, ()) => {
    fetchPolicy,
    errorPolicy,
    context,
  };
};

module DefaultMutateOptions = {
  module Js_ = {
    // Partial<MutationOptions>;
    type t = {
      context: option(Js.Json.t),
      fetchPolicy: option(FetchPolicy__noCacheExtracted.Js_.t),
      awaitRefetchQueries: option(bool),
      errorPolicy: option(ErrorPolicy.Js_.t),
      // optimisticResponse: option('jsVariables => 'jsData),
      // update: option(MutationUpdaterFn.Js_.t('jsData)),
      // updateQueries: option(MutationQueryReducersMap.Js_.t('jsData)),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      // variables: option('jsVariables),
    };
  };

  type t = {
    context: option(Js.Json.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    awaitRefetchQueries: option(bool),
    errorPolicy: option(ErrorPolicy.t),
    refetchQueries: option(RefetchQueryDescription.t),
  };

  let toJs: t => Js_.t =
    t => {
      context: t.context,
      fetchPolicy:
        t.fetchPolicy->Belt.Option.map(FetchPolicy__noCacheExtracted.toJs),
      awaitRefetchQueries: t.awaitRefetchQueries,
      errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      refetchQueries:
        t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
    };

  let make =
      (
        ~context=?,
        ~fetchPolicy=?,
        ~awaitRefetchQueries=?,
        ~errorPolicy=?,
        ~refetchQueries=?,
        (),
      ) => {
    context,
    fetchPolicy,
    awaitRefetchQueries,
    errorPolicy,
    refetchQueries,
  };
};

module DefaultOptions = {
  module Js_ = {
    // export interface DefaultOptions {
    //     watchQuery?: Partial<WatchQueryOptions>;
    //     query?: Partial<QueryOptions>;
    //     mutate?: Partial<MutationOptions>;
    // }
    type t = {
      watchQuery: option(DefaultWatchQueryOptions.Js_.t),
      query: option(DefaultQueryOptions.Js_.t),
      mutate: option(DefaultMutateOptions.Js_.t),
    };
  };

  type t = {
    watchQuery: option(DefaultWatchQueryOptions.t),
    query: option(DefaultQueryOptions.t),
    mutate: option(DefaultMutateOptions.t),
  };

  let toJs: t => Js_.t =
    t => {
      watchQuery:
        t.watchQuery->Belt.Option.map(DefaultWatchQueryOptions.toJs),
      query: t.query->Belt.Option.map(DefaultQueryOptions.toJs),
      mutate: t.mutate->Belt.Option.map(DefaultMutateOptions.toJs),
    };

  let make:
    (
      ~mutate: DefaultMutateOptions.t=?,
      ~query: DefaultQueryOptions.t=?,
      ~watchQuery: DefaultWatchQueryOptions.t=?,
      unit
    ) =>
    t =
    (~mutate=?, ~query=?, ~watchQuery=?, ()) => {watchQuery, query, mutate};
};

module ApolloClientOptions = {
  module Js_ = {
    // export declare type ApolloClientOptions<TCacheShape> = {
    //     uri?: string | UriFunction;
    //     credentials?: string;
    //     headers?: Record<string, string>;
    //     link?: ApolloLink;
    //     cache: ApolloCache<TCacheShape>;
    //     ssrForceFetchDelay?: number;
    //     ssrMode?: boolean;
    //     connectToDevTools?: boolean;
    //     queryDeduplication?: boolean;
    //     defaultOptions?: DefaultOptions;
    //     assumeImmutableResults?: boolean;
    //     resolvers?: Resolvers | Resolvers[];
    //     typeDefs?: string | string[] | DocumentNode | DocumentNode[];
    //     fragmentMatcher?: FragmentMatcher;
    //     name?: string;
    //     version?: string;
    // };
    type t = {
      uri: option(UriFunction.Js_.t),
      credentials: option(string),
      headers: option(Js.Dict.t(string)),
      link: option(ApolloLink.Js_.t),
      cache: ApolloCache.Js_.t(Js.Json.t),
      ssrForceFetchDelay: option(int),
      ssrMode: option(bool),
      connectToDevTools: option(bool),
      queryDeduplication: option(bool),
      defaultOptions: option(DefaultOptions.Js_.t),
      assumeImmutableResults: option(bool),
      resolvers: option(array(Resolvers.Js_.t)),
      typeDefs: option(array(Graphql.documentNode)),
      fragmentMatcher: option(FragmentMatcher.Js_.t),
      name: option(string),
      version: option(string),
    };
  };

  type t = {
    uri: option(UriFunction.t),
    credentials: option(string),
    headers: option(Js.Dict.t(string)),
    link: option(ApolloLink.t),
    cache: ApolloCache.Js_.t(Js.Json.t),
    ssrForceFetchDelay: option(int),
    ssrMode: option(bool),
    connectToDevTools: option(bool),
    queryDeduplication: option(bool),
    defaultOptions: option(DefaultOptions.t),
    assumeImmutableResults: option(bool),
    resolvers: option(array(Resolvers.t)),
    typeDefs: option(array(Graphql.documentNode)),
    fragmentMatcher: option(FragmentMatcher.t),
    name: option(string),
    version: option(string),
  };

  let toJs: t => Js_.t =
    t => {
      uri: t.uri,
      credentials: t.credentials,
      headers: t.headers,
      link: t.link,
      cache: t.cache,
      ssrForceFetchDelay: t.ssrForceFetchDelay,
      ssrMode: t.ssrMode,
      connectToDevTools: t.connectToDevTools,
      queryDeduplication: t.queryDeduplication,
      defaultOptions: t.defaultOptions->Belt.Option.map(DefaultOptions.toJs),
      assumeImmutableResults: t.assumeImmutableResults,
      resolvers: t.resolvers,
      typeDefs: t.typeDefs,
      fragmentMatcher: t.fragmentMatcher,
      name: t.name,
      version: t.version,
    };
};

module Js_ = {
  // export declare class ApolloClient<TCacheShape> implements DataProxy {
  //     link: ApolloLink;
  //     cache: ApolloCache<TCacheShape>;
  //     disableNetworkFetches: boolean;
  //     version: string;
  //     queryDeduplication: boolean;
  //     defaultOptions: DefaultOptions;
  //     readonly typeDefs: ApolloClientOptions<TCacheShape>['typeDefs'];
  //     private queryManager;
  //     private devToolsHookCb;
  //     private resetStoreCallbacks;
  //     private clearStoreCallbacks;
  //     private localState;
  //     constructor(options: ApolloClientOptions<TCacheShape>);
  //     stop(): void;
  //     watchQuery<T = any, TVariables = OperationVariables>(options: WatchQueryOptions<TVariables>): ObservableQuery<T, TVariables>;
  //     query<T = any, TVariables = OperationVariables>(options: QueryOptions<TVariables>): Promise<ApolloQueryResult<T>>;
  //     mutate<T = any, TVariables = OperationVariables>(options: MutationOptions<T, TVariables>): Promise<FetchResult<T>>;
  //     subscribe<T = any, TVariables = OperationVariables>(options: SubscriptionOptions<TVariables>): Observable<FetchResult<T>>;
  //     readQuery<T = any, TVariables = OperationVariables>(options: DataProxy.Query<TVariables>, optimistic?: boolean): T | null;
  //     readFragment<T = any, TVariables = OperationVariables>(options: DataProxy.Fragment<TVariables>, optimistic?: boolean): T | null;
  //     writeQuery<TData = any, TVariables = OperationVariables>(options: DataProxy.WriteQueryOptions<TData, TVariables>): void;
  //     writeFragment<TData = any, TVariables = OperationVariables>(options: DataProxy.WriteFragmentOptions<TData, TVariables>): void;
  //     __actionHookForDevTools(cb: () => any): void;
  //     __requestRaw(payload: GraphQLRequest): Observable<ExecutionResult>;
  //     resetStore(): Promise<ApolloQueryResult<any>[] | null>;
  //     clearStore(): Promise<any[]>;
  //     onResetStore(cb: () => Promise<any>): () => void;
  //     onClearStore(cb: () => Promise<any>): () => void;
  //     reFetchObservableQueries(includeStandby?: boolean): Promise<ApolloQueryResult<any>[]>;
  //     extract(optimistic?: boolean): TCacheShape;
  //     restore(serializedState: TCacheShape): ApolloCache<TCacheShape>;
  //     addResolvers(resolvers: Resolvers | Resolvers[]): void;
  //     setResolvers(resolvers: Resolvers | Resolvers[]): void;
  //     getResolvers(): Resolvers;
  //     setLocalStateFragmentMatcher(fragmentMatcher: FragmentMatcher): void;
  //     setLink(newLink: ApolloLink): void;
  // }

  type t;

  // mutate<T = any, TVariables = OperationVariables>(options: MutationOptions<T, TVariables>): Promise<FetchResult<T>>;
  [@bs.send]
  external mutate:
    (t, ~options: MutationOptions.Js_.t('jsData, 'jsVariables)) =>
    Js.Promise.t(FetchResult.Js_.t('jsData)) =
    "mutate";

  // query<T = any, TVariables = OperationVariables>(options: QueryOptions<TVariables>): Promise<ApolloQueryResult<T>>;
  [@bs.send]
  external query:
    (t, ~options: QueryOptions.Js_.t('jsVariables)) =>
    Js.Promise.t(ApolloQueryResult.Js_.t('jsData)) =
    "query";

  // readQuery<T = any, TVariables = OperationVariables>(options: DataProxy.Query<TVariables>, optimistic?: boolean): T | null;
  [@bs.send]
  external readQuery:
    (
      t,
      ~options: DataProxy.Query.Js_.t('jsVariables),
      ~optimistic: option(bool)
    ) =>
    Js.nullable('jsData) =
    "readQuery";

  // setLink(newLink: ApolloLink): void;
  [@bs.send] external setLink: (t, ApolloLink.Js_.t) => unit = "setLink";

  // <T = any, TVariables = OperationVariables>(options: WatchQueryOptions<TVariables>): ObservableQuery<T, TVariables>;
  [@bs.send]
  external watchQuery:
    (t, ~options: WatchQueryOptions.Js_.t('jsVariables)) =>
    ObservableQuery.Js_.t('jsData) =
    "watchQuery";

  // writeFragment<TData = any, TVariables = OperationVariables>(options: DataProxy.WriteFragmentOptions<TData, TVariables>): void;
  [@bs.send]
  external writeFragment:
    (
      t,
      ~options: DataProxy.WriteFragmentOptions.Js_.t('jsData, 'jsVariables)
    ) =>
    unit =
    "writeFragment";

  // writeQuery<TData = any, TVariables = OperationVariables>(options: DataProxy.WriteQueryOptions<TData, TVariables>): void;
  [@bs.send]
  external writeQuery:
    (t, ~options: DataProxy.WriteQueryOptions.Js_.t('jsData, 'jsVariables)) =>
    unit =
    "writeQuery";

  [@bs.module "@apollo/client"] [@bs.new]
  external make: ApolloClientOptions.Js_.t => t = "ApolloClient";
};

type t = Js_.t;

let make:
  (
    ~uri: UriFunction.t=?,
    ~credentials: string=?,
    ~headers: Js.Dict.t(string)=?,
    ~link: ApolloLink.t=?,
    ~cache: ApolloCache.t(Js.Json.t),
    ~ssrForceFetchDelay: int=?,
    ~ssrMode: bool=?,
    ~connectToDevTools: bool=?,
    ~queryDeduplication: bool=?,
    ~defaultOptions: DefaultOptions.t=?,
    ~assumeImmutableResults: bool=?,
    ~resolvers: array(Resolvers.t)=?,
    ~typeDefs: array(Graphql.documentNode)=?,
    ~fragmentMatcher: FragmentMatcher.t=?,
    ~name: string=?,
    ~version: string=?,
    unit
  ) =>
  t =
  (
    ~uri=?,
    ~credentials=?,
    ~headers=?,
    ~link=?,
    ~cache,
    ~ssrForceFetchDelay=?,
    ~ssrMode=?,
    ~connectToDevTools=?,
    ~queryDeduplication=?,
    ~defaultOptions=?,
    ~assumeImmutableResults=?,
    ~resolvers=?,
    ~typeDefs=?,
    ~fragmentMatcher=?,
    ~name=?,
    ~version=?,
    (),
  ) =>
    Js_.make(
      ApolloClientOptions.toJs({
        uri,
        credentials,
        headers,
        link,
        cache,
        ssrForceFetchDelay,
        ssrMode,
        connectToDevTools,
        queryDeduplication,
        defaultOptions,
        assumeImmutableResults,
        resolvers,
        typeDefs,
        fragmentMatcher,
        name,
        version,
      }),
    );

module type Config = {
  type output('a);
  let promiseTransform: Js.Promise.t('a) => output('a);
};

let mutate:
  type data variables jsVariables.
    (
      t,
      ~mutation: (module Operation with
                    type t = data and
                    type t_variables = variables and
                    type Raw.t_variables = jsVariables),
      ~awaitRefetchQueries: bool=?,
      ~context: Js.Json.t=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: FetchPolicy__noCacheExtracted.t=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      ~optimisticResponse: jsVariables => data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~updateQueries: MutationQueryReducersMap.t(data)=?,
      ~update: MutationUpdaterFn.t(data)=?,
      variables
    ) =>
    Js.Promise.t(FetchResult.t(data)) =
  (
    client,
    ~mutation as (module Operation),
    ~awaitRefetchQueries=?,
    ~context=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    ~optimisticResponse=?,
    ~refetchQueries=?,
    ~updateQueries=?,
    ~update=?,
    variables,
  ) => {
    let jsVariables = variables->Operation.serializeVariables->mapJsVariables;

    Js_.mutate(
      client,
      ~options=
        MutationOptions.toJs(
          {
            awaitRefetchQueries,
            context,
            errorPolicy,
            fetchPolicy,
            mutation: Operation.query,
            optimisticResponse,
            updateQueries,
            refetchQueries,
            update,
            variables: jsVariables,
          },
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
        ),
    )
    ->Js.Promise.then_(
        jsResult =>
          jsResult
          ->FetchResult.fromJs(_, ~parse=Operation.parse)
          ->Js.Promise.resolve,
        _,
      );
  };

let query:
  type data variables jsVariables.
    (
      t,
      ~query: (module Operation with
                 type t = data and
                 type t_variables = variables and
                 type Raw.t_variables = jsVariables),
      ~context: Js.Json.t=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: FetchPolicy.t=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      variables
    ) =>
    Js.Promise.t(ApolloQueryResult.t(data)) =
  (
    client,
    ~query as (module Operation),
    ~context=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    variables,
  ) => {
    let jsVariables = variables->Operation.serializeVariables->mapJsVariables;

    Js_.query(
      client,
      ~options=
        QueryOptions.toJs({
          fetchPolicy,
          query: Operation.query,
          variables: jsVariables,
          errorPolicy,
          context,
        }),
    )
    ->Js.Promise.then_(
        jsResult =>
          jsResult
          ->ApolloQueryResult.fromJs(_, ~parse=Operation.parse)
          ->Js.Promise.resolve,
        _,
      );
  };

let readQuery:
  type data variables jsVariables.
    (
      t,
      ~query: (module Operation with
                 type t = data and
                 type t_variables = variables and
                 type Raw.t_variables = jsVariables),
      ~id: string=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      ~optimistic: bool=?,
      variables
    ) =>
    option(data) =
  (
    client,
    ~query as (module Operation),
    ~id=?,
    ~mapJsVariables=Utils.identity,
    ~optimistic=?,
    variables,
  ) => {
    let jsVariables = variables->Operation.serializeVariables->mapJsVariables;

    Js_.readQuery(
      client,
      ~options={id, query: Operation.query, variables: jsVariables},
      ~optimistic,
    )
    ->Js.toOption
    ->Belt.Option.map(Operation.parse);
  };

let setLink: (t, ApolloLink.t) => unit = Js_.setLink;

let watchQuery:
  type data variables jsVariables.
    (
      t,
      ~query: (module Operation with
                 type t = data and
                 type t_variables = variables and
                 type Raw.t_variables = jsVariables),
      ~context: Js.Json.t=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      variables
    ) =>
    ObservableQuery.t(data) =
  (
    client,
    ~query as (module Operation),
    ~context=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    variables,
  ) => {
    let jsVariables = variables->Operation.serializeVariables->mapJsVariables;

    Js_.watchQuery(
      client,
      ~options=
        WatchQueryOptions.toJs({
          fetchPolicy,
          query: Operation.query,
          variables: Some(jsVariables),
          errorPolicy,
          context,
        }),
    )
    ->ObservableQuery.fromJs(~parse=Operation.parse);
  };

let writeFragment:
  type data jsVariables.
    (
      t,
      ~fragment: (module Fragment with type t = data),
      ~data: data,
      ~broadcast: bool=?,
      ~id: string,
      ~fragmentName: string=?,
      unit
    ) =>
    unit =
  (
    client,
    ~fragment as (module Fragment),
    ~data: data,
    ~broadcast=?,
    ~id,
    ~fragmentName=?,
    (),
  ) => {
    Js_.writeFragment(
      client,
      ~options={
        broadcast,
        data: data->Fragment.serialize,
        id,
        fragment: Fragment.query,
        fragmentName,
      },
    );
  };

let writeQuery:
  type data variables jsVariables.
    (
      t,
      ~query: (module Operation with
                 type t = data and
                 type t_variables = variables and
                 type Raw.t_variables = jsVariables),
      ~broadcast: bool=?,
      ~data: data,
      ~id: string=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      variables
    ) =>
    unit =
  (
    client,
    ~query as (module Operation),
    ~broadcast=?,
    ~data,
    ~id=?,
    ~mapJsVariables=Utils.identity,
    variables,
  ) => {
    let jsVariables = variables->Operation.serializeVariables->mapJsVariables;

    Js_.writeQuery(
      client,
      ~options={
        broadcast,
        data: data->Operation.serialize,
        id,
        query: Operation.query,
        variables: jsVariables,
      },
    );
  };
