module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache
module ApolloError = ApolloClient__Errors_ApolloError
module ApolloLink = ApolloClient__Link_Core_ApolloLink
module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult
module DataProxy = ApolloClient__Cache_Core_Types.DataProxy
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy
module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted
module FetchResult = ApolloClient__Link_Core_Types.FetchResult
module FragmentMatcher = ApolloClient__Core_LocalState.FragmentMatcher
module Graphql = ApolloClient__Graphql
module MutationOptions = ApolloClient__Core_WatchQueryOptions.MutationOptions
module MutationQueryReducersMap = ApolloClient__Core_WatchQueryOptions.MutationQueryReducersMap
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn
module Observable = ApolloClient__ZenObservable.Observable
module ObservableQuery = ApolloClient__Core_ObservableQuery.ObservableQuery
module QueryOptions = ApolloClient__Core_WatchQueryOptions.QueryOptions
module PureQueryOptions = ApolloClient__Core_Types.PureQueryOptions
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription
module Resolvers = ApolloClient__Core_Types.Resolvers
module SubscriptionOptions = ApolloClient__Core_WatchQueryOptions.SubscriptionOptions
module Types = ApolloClient__Types
module UriFunction = ApolloClient__Link_Http_SelectHttpOptionsAndBody.UriFunction
module Utils = ApolloClient__Utils
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy
module WatchQueryOptions = ApolloClient__Core_WatchQueryOptions.WatchQueryOptions

module type Fragment = Types.Fragment
module type Operation = Types.Operation
module type OperationNoRequiredVars = Types.OperationNoRequiredVars

module DefaultWatchQueryOptions = {
  module Js_ = {
    // Partial<QueryOptions>;
    type t = {
      fetchPolicy: option<WatchQueryFetchPolicy.Js_.t>,
      // query: GraphQL.Language.documentNode,
      // variables: option('jsVariables),
      errorPolicy: option<ErrorPolicy.Js_.t>,
      context: option<Js.Json.t>,
    }
  }

  type t = {
    fetchPolicy: option<WatchQueryFetchPolicy.t>,
    errorPolicy: option<ErrorPolicy.t>,
    context: option<Js.Json.t>,
  }

  let toJs: t => Js_.t = t => {
    fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    context: t.context,
  }

  let make = (~fetchPolicy=?, ~errorPolicy=?, ~context=?, ()) => {
    fetchPolicy: fetchPolicy,
    errorPolicy: errorPolicy,
    context: context,
  }
}

module DefaultQueryOptions = {
  module Js_ = {
    // Partial<QueryOptions>;
    type t = {
      fetchPolicy: option<FetchPolicy.Js_.t>,
      // query: GraphQL.Language.documentNode,
      // variables: option('jsVariables),
      errorPolicy: option<ErrorPolicy.Js_.t>,
      context: option<Js.Json.t>,
    }
  }

  type t = {
    fetchPolicy: option<FetchPolicy.t>,
    errorPolicy: option<ErrorPolicy.t>,
    context: option<Js.Json.t>,
  }

  let toJs: t => Js_.t = t => {
    fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy.toJs),
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    context: t.context,
  }

  let make = (~fetchPolicy=?, ~errorPolicy=?, ~context=?, ()) => {
    fetchPolicy: fetchPolicy,
    errorPolicy: errorPolicy,
    context: context,
  }
}

module DefaultMutateOptions = {
  module Js_ = {
    // Partial<MutationOptions>;
    type t = {
      context: option<Js.Json.t>,
      fetchPolicy: option<FetchPolicy__noCacheExtracted.Js_.t>,
      awaitRefetchQueries: option<bool>,
      errorPolicy: option<ErrorPolicy.Js_.t>,
      // optimisticResponse: option('jsVariables => 'jsData),
      // update: option(MutationUpdaterFn.Js_.t('jsData)),
      // updateQueries: option(MutationQueryReducersMap.Js_.t('jsData)),
      refetchQueries: option<RefetchQueryDescription.Js_.t>,
      // variables: option('jsVariables),
    }
  }

  type t = {
    context: option<Js.Json.t>,
    fetchPolicy: option<FetchPolicy__noCacheExtracted.t>,
    awaitRefetchQueries: option<bool>,
    errorPolicy: option<ErrorPolicy.t>,
    refetchQueries: option<RefetchQueryDescription.t>,
  }

  let toJs: t => Js_.t = t => {
    context: t.context,
    fetchPolicy: t.fetchPolicy->Belt.Option.map(FetchPolicy__noCacheExtracted.toJs),
    awaitRefetchQueries: t.awaitRefetchQueries,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    refetchQueries: t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
  }

  let make = (
    ~context=?,
    ~fetchPolicy=?,
    ~awaitRefetchQueries=?,
    ~errorPolicy=?,
    ~refetchQueries=?,
    (),
  ) => {
    context: context,
    fetchPolicy: fetchPolicy,
    awaitRefetchQueries: awaitRefetchQueries,
    errorPolicy: errorPolicy,
    refetchQueries: refetchQueries,
  }
}

module DefaultOptions = {
  module Js_ = {
    // export interface DefaultOptions {
    //     watchQuery?: Partial<WatchQueryOptions>;
    //     query?: Partial<QueryOptions>;
    //     mutate?: Partial<MutationOptions>;
    // }
    type t = {
      watchQuery: option<DefaultWatchQueryOptions.Js_.t>,
      query: option<DefaultQueryOptions.Js_.t>,
      mutate: option<DefaultMutateOptions.Js_.t>,
    }
  }

  type t = {
    watchQuery: option<DefaultWatchQueryOptions.t>,
    query: option<DefaultQueryOptions.t>,
    mutate: option<DefaultMutateOptions.t>,
  }

  let toJs: t => Js_.t = t => {
    watchQuery: t.watchQuery->Belt.Option.map(DefaultWatchQueryOptions.toJs),
    query: t.query->Belt.Option.map(DefaultQueryOptions.toJs),
    mutate: t.mutate->Belt.Option.map(DefaultMutateOptions.toJs),
  }

  let make: (
    ~mutate: DefaultMutateOptions.t=?,
    ~query: DefaultQueryOptions.t=?,
    ~watchQuery: DefaultWatchQueryOptions.t=?,
    unit,
  ) => t = (~mutate=?, ~query=?, ~watchQuery=?, ()) => {
    watchQuery: watchQuery,
    query: query,
    mutate: mutate,
  }
}

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
      uri: option<UriFunction.Js_.t>,
      credentials: option<string>,
      headers: option<Js.Dict.t<string>>,
      link: option<ApolloLink.Js_.t>,
      cache: ApolloCache.t<Js.Json.t>, // Non-Js_ ApolloCache is correct here
      ssrForceFetchDelay: option<int>,
      ssrMode: option<bool>,
      connectToDevTools: option<bool>,
      queryDeduplication: option<bool>,
      defaultOptions: option<DefaultOptions.Js_.t>,
      assumeImmutableResults: option<bool>,
      resolvers: option<array<Resolvers.Js_.t>>,
      typeDefs: option<array<Graphql.documentNode>>,
      fragmentMatcher: option<FragmentMatcher.Js_.t>,
      name: option<string>,
      version: option<string>,
    }
  }

  type t = {
    uri: option<UriFunction.t>,
    credentials: option<string>,
    headers: option<Js.Dict.t<string>>,
    link: option<ApolloLink.t>,
    cache: ApolloCache.t<Js.Json.t>,
    ssrForceFetchDelay: option<int>,
    ssrMode: option<bool>,
    connectToDevTools: option<bool>,
    queryDeduplication: option<bool>,
    defaultOptions: option<DefaultOptions.t>,
    assumeImmutableResults: option<bool>,
    resolvers: option<array<Resolvers.t>>,
    typeDefs: option<array<Graphql.documentNode>>,
    fragmentMatcher: option<FragmentMatcher.t>,
    name: option<string>,
    version: option<string>,
  }

  let toJs: t => Js_.t = t => {
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
  }
}

module Js_ = {
  module Cast = {
    external asRescriptCache: ApolloCache.Js_.t<'a> => ApolloCache.t<'a> = "%identity"
  }

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
  //     watchQuery<T = any, TVariables = OperationVariables>(options: WatchQueryOptions<TVariables, T>): ObservableQuery<T, TVariables>;
  //     query<T = any, TVariables = OperationVariables>(options: QueryOptions<TVariables, T>): Promise<ApolloQueryResult<T>>;
  //     mutate<T = any, TVariables = OperationVariables>(options: MutationOptions<T, TVariables>): Promise<FetchResult<T>>;
  //     subscribe<T = any, TVariables = OperationVariables>(options: SubscriptionOptions<TVariables, T>): Observable<FetchResult<T>>;
  //     readQuery<T = any, TVariables = OperationVariables>(options: DataProxy.ReadQueryOptions<TVariables, T>, optimistic?: boolean): T | null;
  //     readFragment<T = any, TVariables = OperationVariables>(options: DataProxy.ReadFragmentOptions<TVariables, T>, optimistic?: boolean): T | null;
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
  type t

  // clearStore(): Promise<any[]>;
  @send
  external clearStore: t => Js.Promise.t<array<Js.Json.t>> = "clearStore"

  // extract(optimistic?: boolean): TCacheShape;
  @send
  external extract: (t, ~optimistic: bool=?, unit) => Js.Json.t = "extract"

  // mutate<T = any, TVariables = OperationVariables>(options: MutationOptions<T, TVariables>): Promise<FetchResult<T>>;
  @send
  external mutate: (
    t,
    ~options: MutationOptions.Js_.t<'jsData, 'jsVariables>,
  ) => Js.Promise.t<FetchResult.Js_.t<'jsData>> = "mutate"

  // onClearStore(cb: () => Promise<any>): () => void;
  @send
  external onClearStore: (t, ~cb: unit => Js.Promise.t<unit>, unit) => unit = "onClearStore"

  // onResetStore(cb: () => Promise<any>): () => void;
  @send
  external onResetStore: (t, ~cb: unit => Js.Promise.t<unit>, unit) => unit = "onResetStore"

  // query<T = any, TVariables = OperationVariables>(options: QueryOptions<TVariables>): Promise<ApolloQueryResult<T>>;
  @send
  external query: (
    t,
    ~options: QueryOptions.Js_.t<'jsVariables>,
  ) => Js.Promise.t<ApolloQueryResult.Js_.t<'jsData>> = "query"

  // readFragment<T = any, TVariables = OperationVariables>(options: DataProxy.ReadFragmentOptions<TVariables>, optimistic?: boolean): T | null;
  @send
  external readFragment: (
    t,
    ~options: DataProxy.ReadFragmentOptions.Js_.t,
    ~optimistic: bool=?,
    unit,
  ) => Js.nullable<'jsData> = "readFragment"

  // readQuery<T = any, TVariables = OperationVariables>(options: DataProxy.ReadQueryOptions<TVariables>, optimistic?: boolean): T | null;
  @send
  external readQuery: (
    t,
    ~options: DataProxy.ReadQueryOptions.Js_.t<'jsVariables>,
    ~optimistic: option<bool>,
  ) => Js.nullable<'jsData> = "readQuery"

  // resetStore(): Promise<ApolloQueryResult<any>[] | null>;
  @send
  external resetStore: t => Js.Promise.t<Js.nullable<array<ApolloQueryResult.Js_.t<Js.Json.t>>>> =
    "resetStore"

  // restore(serializedState: TCacheShape): ApolloCache<TCacheShape>;
  @send
  external restore: (t, Js.Json.t) => ApolloCache.Js_.t<Js.Json.t> = "restore"

  // setLink(newLink: ApolloLink): void;
  @send external setLink: (t, ApolloLink.Js_.t) => unit = "setLink"

  // stop(): void;
  @send external stop: (t, unit) => unit = "stop"

  // subscribe<T = any, TVariables = OperationVariables>(options: SubscriptionOptions<TVariables>): Observable<FetchResult<T>>;

  @send
  external subscribe: (
    t,
    ~options: SubscriptionOptions.Js_.t<'jsVariables>,
  ) => Observable.Js_.t<FetchResult.Js_.t<'jsData>, 'error> = "subscribe"

  // <T = any, TVariables = OperationVariables>(options: WatchQueryOptions<TVariables>): ObservableQuery<T, TVariables>;
  @send
  external watchQuery: (
    t,
    ~options: WatchQueryOptions.Js_.t<'jsVariables>,
  ) => ObservableQuery.Js_.t<'jsData> = "watchQuery"

  // writeFragment<TData = any, TVariables = OperationVariables>(options: DataProxy.WriteFragmentOptions<TData, TVariables>): void;
  @send
  external writeFragment: (
    t,
    ~options: DataProxy.WriteFragmentOptions.Js_.t<'jsData, 'jsVariables>,
  ) => option<ApolloCache.reference> = "writeFragment"

  // writeQuery<TData = any, TVariables = OperationVariables>(options: DataProxy.WriteQueryOptions<TData, TVariables>): void;
  @send
  external writeQuery: (
    t,
    ~options: DataProxy.WriteQueryOptions.Js_.t<'jsData, 'jsVariables>,
  ) => option<ApolloCache.reference> = "writeQuery"

  // updateQuery<TData = any, TVariables = any>(options: Cache.UpdateQueryOptions<TData, TVariables>, update: (data: TData | null) => TData | null | void): TData | null
  @send
  external updateQuery: (
    t,
    ~options: DataProxy.UpdateQueryOptions.Js_.t<'jsVariables>,
    ~update: Js.null<'jsData> => Js.nullable<'jsData>,
  ) => Js.nullable<'jsData> = "updateQuery"

  // updateFragment<TData = any, TVariables = any>(options: Cache.UpdateFragmentOptions<TData, TVariables>, update: (data: TData | null) => TData | null | void): TData | null
  @send
  external updateFragment: (
    t,
    ~options: DataProxy.UpdateFragmentOptions.Js_.t<'jsVariables>,
    ~update: Js.null<'jsData> => Js.nullable<'jsData>,
  ) => Js.nullable<'jsData> = "updateFragment"

  @module("@apollo/client") @new
  external make: ApolloClientOptions.Js_.t => t = "ApolloClient"
}

type t = {
  @as("rescript_clearStore")
  clearStore: unit => Js.Promise.t<Belt.Result.t<array<Js.Json.t>, Js.Exn.t>>,
  @as("rescript_extract")
  extract: (~optimistic: bool=?, unit) => Js.Json.t,
  @as("rescript_mutate")
  mutate: 'data 'variables 'jsVariables. (
    ~mutation: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~awaitRefetchQueries: bool=?,
    ~context: Js.Json.t=?,
    ~errorPolicy: ErrorPolicy.t=?,
    ~fetchPolicy: FetchPolicy__noCacheExtracted.t=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~optimisticResponse: 'jsVariables => 'data=?,
    ~refetchQueries: RefetchQueryDescription.t=?,
    ~updateQueries: MutationQueryReducersMap.t<'data>=?,
    ~update: MutationUpdaterFn.t<'data>=?,
    'variables,
  ) => Js.Promise.t<Belt.Result.t<FetchResult.t__ok<'data>, ApolloError.t>>,
  @as("rescript_onClearStore")
  onClearStore: (~cb: unit => Js.Promise.t<unit>, unit) => unit,
  @as("rescript_onResetStore")
  onResetStore: (~cb: unit => Js.Promise.t<unit>, unit) => unit,
  @as("rescript_query")
  query: 'data 'variables 'jsVariables. (
    ~query: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~context: Js.Json.t=?,
    ~errorPolicy: ErrorPolicy.t=?,
    ~fetchPolicy: FetchPolicy.t=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    'variables,
  ) => Js.Promise.t<Belt.Result.t<ApolloQueryResult.t__ok<'data>, ApolloError.t>>,
  @as("rescript_readFragment")
  readFragment: 'data. (
    ~fragment: module(Fragment with type t = 'data),
    ~id: string,
    ~optimistic: bool=?,
    ~canonizeResults: bool=?,
    ~fragmentName: string=?,
    unit,
  ) => option<Types.parseResult<'data>>,
  @as("rescript_readQuery")
  readQuery: 'data 'variables 'jsVariables. (
    ~query: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~id: string=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~optimistic: bool=?,
    ~canonizeResults: bool=?,
    'variables,
  ) => option<Types.parseResult<'data>>,
  @as("rescript_resetStore")
  resetStore: unit => Js.Promise.t<
    Belt.Result.t<option<array<ApolloQueryResult.Js_.t<Js.Json.t>>>, Js.Exn.t>,
  >,
  @as("rescript_restore")
  restore: (~serializedState: Js.Json.t) => ApolloCache.t<Js.Json.t>,
  @as("rescript_setLink")
  setLink: ApolloLink.t => unit,
  stop: unit => unit,
  @as("rescript_subscribe")
  subscribe: 'data 'variables 'jsVariables. (
    ~subscription: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~context: Js.Json.t=?,
    ~errorPolicy: ErrorPolicy.t=?,
    ~fetchPolicy: FetchPolicy.t=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    'variables,
  ) => Observable.t<FetchResult.t__ok<'data>, ApolloError.t>,
  @as("rescript_watchQuery")
  watchQuery: 'data 'variables 'jsVariables. (
    ~query: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~context: Js.Json.t=?,
    ~errorPolicy: ErrorPolicy.t=?,
    ~fetchPolicy: WatchQueryFetchPolicy.t=?,
    ~nextFetchPolicy: WatchQueryFetchPolicy.t=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~pollInterval: int=?,
    'variables,
  ) => ObservableQuery.t<'data>,
  @as("rescript_writeFragment")
  writeFragment: 'data 'jsVariables. (
    ~fragment: module(Fragment with type t = 'data),
    ~data: 'data,
    ~broadcast: bool=?,
    ~overwrite: bool=?,
    ~id: string,
    ~fragmentName: string=?,
    unit,
  ) => option<ApolloCache.reference>,
  @as("rescript_writeQuery")
  writeQuery: 'data 'variables 'jsVariables. (
    ~query: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~broadcast: bool=?,
    ~overwrite: bool=?,
    ~data: 'data,
    ~id: string=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    'variables,
  ) => option<ApolloCache.reference>,
  @as("rescript_updateFragment")
  updateFragment: 'data. (
    ~fragment: module(Fragment with type t = 'data),
    ~fragmentName: string=?,
    ~optimistic: bool=?,
    ~canonizeResults: bool=?,
    ~broadcast: bool=?,
    ~overwrite: bool=?,
    ~id: string,
    ~update: option<'data> => option<'data>,
    unit,
  ) => option<Utils.Types.parseResult<'data>>,
  @as("rescript_updateQuery")
  updateQuery: 'data 'variables 'jsVariables. (
    ~query: module(Operation with
      type t = 'data
      and type t_variables = 'variables
      and type Raw.t_variables = 'jsVariables
    ),
    ~optimistic: bool=?,
    ~canonizeResults: bool=?,
    ~broadcast: bool=?,
    ~overwrite: bool=?,
    ~id: string=?,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~update: option<'data> => option<'data>,
    'variables,
  ) => option<Utils.Types.parseResult<'data>>,
}

let preserveJsPropsAndContext: (Js_.t, t) => t = %raw(`
    function (js, t) {
      return Object.assign(js, t)
    }
  `)

let make: (
  ~uri: UriFunction.t=?,
  ~credentials: string=?,
  ~headers: Js.Dict.t<string>=?,
  ~link: ApolloLink.t=?,
  ~cache: ApolloCache.t<Js.Json.t>,
  ~ssrForceFetchDelay: int=?,
  ~ssrMode: bool=?,
  ~connectToDevTools: bool=?,
  ~queryDeduplication: bool=?,
  ~defaultOptions: DefaultOptions.t=?,
  ~assumeImmutableResults: bool=?,
  ~resolvers: array<Resolvers.t>=?,
  ~typeDefs: array<Graphql.documentNode>=?,
  ~fragmentMatcher: FragmentMatcher.t=?,
  ~name: string=?,
  ~version: string=?,
  unit,
) => t = (
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
) => {
  let jsClient = Js_.make(
    ApolloClientOptions.toJs({
      uri: uri,
      credentials: credentials,
      headers: headers,
      link: link,
      cache: cache,
      ssrForceFetchDelay: ssrForceFetchDelay,
      ssrMode: ssrMode,
      connectToDevTools: connectToDevTools,
      queryDeduplication: queryDeduplication,
      defaultOptions: defaultOptions,
      assumeImmutableResults: assumeImmutableResults,
      resolvers: resolvers,
      typeDefs: typeDefs,
      fragmentMatcher: fragmentMatcher,
      name: name,
      version: version,
    }),
  )

  let clearStore = () =>
    jsClient
    ->Js_.clearStore
    ->Js.Promise.then_(value => Js.Promise.resolve(Ok(value)), _)
    ->Js.Promise.catch(e => Js.Promise.resolve(Error(Utils.ensureError(Any(e)))), _)

  let extract = (~optimistic=?, ()) => jsClient->Js_.extract(~optimistic?, ())

  let mutate = (
    type data variables jsVariables,
    ~mutation as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
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
    let safeParse = Utils.safeParse(Operation.parse)

    Js_.mutate(
      jsClient,
      ~options=MutationOptions.toJs(
        {
          awaitRefetchQueries: awaitRefetchQueries,
          context: context,
          errorPolicy: errorPolicy,
          fetchPolicy: fetchPolicy,
          mutation: Operation.query,
          optimisticResponse: optimisticResponse,
          updateQueries: updateQueries,
          refetchQueries: refetchQueries,
          update: update,
          variables: variables,
        },
        ~mapJsVariables,
        ~safeParse,
        ~serialize=Operation.serialize,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )
    ->Js.Promise.then_(
      jsFetchResult =>
        Js.Promise.resolve(jsFetchResult->FetchResult.fromJs(~safeParse)->FetchResult.toResult),
      _,
    )
    ->Js.Promise.catch(error =>
      Js.Promise.resolve(
        Error(
          ApolloError.make(
            ~networkError=FetchFailure({
              open Utils
              ensureError(Any(error))
            }),
            (),
          ),
        ),
      )
    , _)
  }

  let onClearStore = (~cb) => jsClient->Js_.onClearStore(~cb)

  let onResetStore = (~cb) => jsClient->Js_.onResetStore(~cb)

  let query = (
    type data variables jsVariables,
    ~query as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~context=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    variables,
  ) => {
    let safeParse = Utils.safeParse(Operation.parse)

    Js_.query(
      jsClient,
      ~options=QueryOptions.toJs(
        {
          fetchPolicy: fetchPolicy,
          query: Operation.query,
          variables: variables,
          errorPolicy: errorPolicy,
          context: context,
        },
        ~mapJsVariables,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )
    ->Js.Promise.then_(
      jsApolloQueryResult =>
        Js.Promise.resolve(
          jsApolloQueryResult->ApolloQueryResult.fromJs(~safeParse)->ApolloQueryResult.toResult,
        ),
      _,
    )
    ->Js.Promise.catch(error =>
      Js.Promise.resolve(
        Error(
          ApolloError.make(
            ~networkError=FetchFailure({
              open Utils
              ensureError(Any(error))
            }),
            (),
          ),
        ),
      )
    , _)
  }

  let readFragment = (
    type data,
    ~fragment as module(Fragment: Fragment with type t = data),
    ~id,
    ~optimistic=?,
    ~canonizeResults=?,
    ~fragmentName=?,
    (),
  ) => {
    let safeParse = Utils.safeParse(Fragment.parse)

    jsClient
    ->Js_.readFragment(
      ~options={
        id: id,
        fragment: Fragment.query,
        fragmentName: fragmentName,
        optimistic: optimistic,
        canonizeResults: canonizeResults,
      },
      ~optimistic?,
      (),
    )
    ->Js.toOption
    ->Belt.Option.map(safeParse)
  }

  let readQuery = (
    type data variables jsVariables,
    ~query as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~id=?,
    ~mapJsVariables=Utils.identity,
    ~optimistic=?,
    ~canonizeResults=?,
    variables,
  ) => {
    let safeParse = Utils.safeParse(Operation.parse)

    Js_.readQuery(
      jsClient,
      ~options=DataProxy.ReadQueryOptions.toJs(
        {
          id: id,
          query: Operation.query,
          variables: variables,
          optimistic: optimistic,
          canonizeResults: canonizeResults,
        },
        ~mapJsVariables,
        ~serializeVariables=Operation.serializeVariables,
      ),
      ~optimistic,
    )
    ->Js.toOption
    ->Belt.Option.map(safeParse)
  }

  let resetStore: unit => Js.Promise.t<
    Belt.Result.t<option<array<ApolloQueryResult.Js_.t<Js.Json.t>>>, Js.Exn.t>,
  > = () =>
    jsClient
    ->Js_.resetStore
    ->Js.Promise.then_(value => Js.Promise.resolve(Ok(value->Js.toOption)), _)
    ->Js.Promise.catch(e => Js.Promise.resolve(Error(Utils.ensureError(Any(e)))), _)

  let restore = (~serializedState) =>
    jsClient->Js_.restore(serializedState)->Js_.Cast.asRescriptCache

  let setLink = link => jsClient->Js_.setLink(link)

  let stop = () => jsClient->Js_.stop()

  let subscribe = (
    type data variables jsVariables,
    ~subscription as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~context=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    variables,
  ) => {
    let safeParse = Utils.safeParse(Operation.parse)

    let jsObservable = Js_.subscribe(
      jsClient,
      ~options=SubscriptionOptions.toJs(
        {
          fetchPolicy: fetchPolicy,
          query: Operation.query,
          variables: variables,
          errorPolicy: errorPolicy,
          context: context,
        },
        ~mapJsVariables,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )

    {
      Observable.subscribe: (~onNext, ~onError=?, ~onComplete=?, ()) => {
        let onNext' = jsFetchResult =>
          switch jsFetchResult->FetchResult.fromJs(~safeParse)->FetchResult.toResult {
          | Ok(ok) => onNext(ok)
          | Error(error) =>
            switch onError {
            | Some(onError) => onError(error)
            | None => ()
            }
          }

        let onError' = onError->Belt.Option.map(onError => {
          let return = unknown =>
            Obj.magic(unknown)->ApolloError.Js_.ensureApolloError->ApolloError.fromJs->onError
          return
        })

        let observable = jsObservable->Observable.fromJs
        observable.subscribe(~onNext=onNext', ~onError=?onError', ~onComplete?, ())
      },
    }
  }

  let watchQuery = (
    type data variables jsVariables,
    ~query as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~context=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~nextFetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    ~pollInterval=?,
    variables,
  ) => {
    let safeParse = Utils.safeParse(Operation.parse)

    jsClient
    ->Js_.watchQuery(
      ~options=WatchQueryOptions.toJs(
        {
          fetchPolicy: fetchPolicy,
          nextFetchPolicy: nextFetchPolicy,
          query: Operation.query,
          variables: variables,
          errorPolicy: errorPolicy,
          context: context,
          pollInterval: pollInterval,
        },
        ~mapJsVariables,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )
    ->ObservableQuery.fromJs(~safeParse)
  }

  let writeFragment = (
    type data,
    ~fragment as module(Fragment: Fragment with type t = data),
    ~data: data,
    ~broadcast=?,
    ~overwrite=?,
    ~id,
    ~fragmentName=?,
    (),
  ) =>
    jsClient->Js_.writeFragment(
      ~options=DataProxy.WriteFragmentOptions.toJs(
        {
          broadcast: broadcast,
          data: data,
          id: id,
          fragment: Fragment.query,
          fragmentName: fragmentName,
          overwrite: overwrite,
        },
        ~serialize=Fragment.serialize,
      ),
    )

  let writeQuery = (
    type data variables jsVariables,
    ~query as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~broadcast=?,
    ~overwrite=?,
    ~data,
    ~id=?,
    ~mapJsVariables=Utils.identity,
    variables,
  ) =>
    jsClient->Js_.writeQuery(
      ~options=DataProxy.WriteQueryOptions.toJs(
        {
          broadcast: broadcast,
          data: data,
          id: id,
          query: Operation.query,
          variables: variables,
          overwrite: overwrite,
        },
        ~mapJsVariables,
        ~serialize=Operation.serialize,
        ~serializeVariables=Operation.serializeVariables,
      ),
    )

  let updateQuery = (
    type data variables jsVariables,
    ~query as module(Operation: Operation with
      type t = data
      and type t_variables = variables
      and type Raw.t_variables = jsVariables
    ),
    ~optimistic=?,
    ~canonizeResults=?,
    ~broadcast=?,
    ~overwrite=?,
    ~id=?,
    ~mapJsVariables=Utils.identity,
    ~update,
    variables,
  ) => {
    let safeParse = Utils.safeParse(Operation.parse)

    jsClient
    ->Js_.updateQuery(~options=DataProxy.UpdateQueryOptions.toJs(
      {
        optimistic: optimistic,
        canonizeResults: canonizeResults,
        broadcast: broadcast,
        id: id,
        query: Operation.query,
        variables: variables,
        overwrite: overwrite,
      },
      ~mapJsVariables,
      ~serializeVariables=Operation.serializeVariables,
    ), ~update=jsData =>
      jsData
      ->Js.nullToOption
      ->Belt.Option.map(Operation.parse)
      ->update
      ->Belt.Option.map(Operation.serialize)
      ->Js.Nullable.fromOption
    )
    ->Js.toOption
    ->Belt.Option.map(safeParse)
  }

  let updateFragment = (
    type data,
    ~fragment as module(Fragment: Fragment with type t = data),
    ~fragmentName=?,
    ~optimistic=?,
    ~canonizeResults=?,
    ~broadcast=?,
    ~overwrite=?,
    ~id,
    ~update,
    (),
  ) => {
    let safeParse = Utils.safeParse(Fragment.parse)

    jsClient
    ->Js_.updateFragment(~options=DataProxy.UpdateFragmentOptions.toJs({
      optimistic: optimistic,
      canonizeResults: canonizeResults,
      broadcast: broadcast,
      id: id,
      fragment: Fragment.query,
      fragmentName: fragmentName,
      overwrite: overwrite,
    }), ~update=jsData =>
      jsData
      ->Js.nullToOption
      ->Belt.Option.map(Fragment.parse)
      ->update
      ->Belt.Option.map(Fragment.serialize)
      ->Js.Nullable.fromOption
    )
    ->Js.toOption
    ->Belt.Option.map(safeParse)
  }

  preserveJsPropsAndContext(
    jsClient,
    {
      clearStore: clearStore,
      extract: extract,
      mutate: mutate,
      onClearStore: onClearStore,
      onResetStore: onResetStore,
      query: query,
      readFragment: readFragment,
      readQuery: readQuery,
      resetStore: resetStore,
      restore: restore,
      setLink: setLink,
      stop: stop,
      subscribe: subscribe,
      watchQuery: watchQuery,
      writeFragment: writeFragment,
      writeQuery: writeQuery,
      updateQuery: updateQuery,
      updateFragment: updateFragment,
    },
  )
}
