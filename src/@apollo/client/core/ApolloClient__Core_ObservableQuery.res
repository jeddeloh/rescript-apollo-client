module Types = ApolloClient__Types

module ObservableQuery = {
  module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult
  module Subscription = ApolloClient__ZenObservable.Subscription
  module Observer = ApolloClient__ZenObservable.Observer

  module Js_ = {
    // export declare class ObservableQuery<TData = any, TVariables = OperationVariables> extends Observable<ApolloQueryResult<TData>> {
    //     readonly options: WatchQueryOptions<TVariables>;
    //     readonly queryId: string;
    //     readonly queryName?: string;
    //     get variables(): TVariables | undefined;
    //     private isTornDown;
    //     private queryManager;
    //     private observers;
    //     private subscriptions;
    //     private lastResult;
    //     private lastResultSnapshot;
    //     private lastError;
    //     constructor({ queryManager, options, }: {
    //         queryManager: QueryManager<any>;
    //         options: WatchQueryOptions<TVariables>;
    //     });
    //     result(): Promise<ApolloQueryResult<TData>>;
    //     getCurrentResult(): ApolloCurrentQueryResult<TData>;
    //     isDifferentFromLastResult(newResult: ApolloQueryResult<TData>): boolean;
    //     getLastResult(): ApolloQueryResult<TData>;
    //     getLastError(): ApolloError;
    //     resetLastResults(): void;
    //     resetQueryStoreErrors(): void;
    //     refetch(variables?: Partial<TVariables>): Promise<ApolloQueryResult<TData>>;
    //     fetchMore<K extends keyof TVariables>(fetchMoreOptions: FetchMoreQueryOptions<TVariables, K> & FetchMoreOptions<TData, TVariables>): Promise<ApolloQueryResult<TData>>;
    //     subscribeToMore<TSubscriptionData = TData, TSubscriptionVariables = TVariables>(options: SubscribeToMoreOptions<TData, TSubscriptionVariables, TSubscriptionData>): () => void;
    //     setOptions(newOptions: Partial<WatchQueryOptions<TVariables>>): Promise<ApolloQueryResult<TData>>;
    //     setVariables(variables: TVariables): Promise<ApolloQueryResult<TData> | void>;
    //     updateQuery<TVars = TVariables>(mapFn: (previousQueryResult: TData, options: Pick<WatchQueryOptions<TVars>, "variables">) => TData): void;
    //     private getCurrentQueryResult;
    //     startPolling(pollInterval: number): void;
    //     stopPolling(): void;
    //     private updateLastResult;
    //     private onSubscribe;
    //     private reobserver?;
    //     private getReobserver;
    //     private newReobserver;
    //     reobserve(newOptions?: Partial<WatchQueryOptions<TVariables>>, newNetworkStatus?: NetworkStatus): Promise<ApolloQueryResult<TData>>;
    //     private observer;
    //     private tearDownQuery;
    // }
    type t<'jsData>

    // ...extends Observable<ApolloQueryResult<TData>>
    // <R>(callback: (value: T) => R): Observable<R>;
    @send external map: (t<'t>, 't => 'r) => t<'r> = "map"
    let fakeMap: (t<'t>, ('t, Js.Exn.t => unit) => option<'r>) => t<'r> = (js, fn) =>
      @ocaml.doc("
          * We should be able to just map, but it's broken:
          * https://github.com/apollographql/apollo-client/issues/6144
          * This is not any sort of real map, of course. It just returns an observable
          * with a subcribe method that builds the transformation into onNext :(
          ")
      %raw(`
            function (js, fn) {
              var originalSubscribe = js.subscribe.bind(js);
              js.subscribe = function (onNext, onError, onComplete) {
                var newOnNext = function (result) {
                  var parsedData = result.data ? fn(result.data, onError) : undefined;
                  var transformedResult = parsedData
                    ? Object.assign({}, result, { data: parsedData })
                    : result;
                  return onNext(transformedResult);
                };
                return originalSubscribe(newOnNext, onError, onComplete);
              };
              return js;
            }
          `)(js, fn)

    // ...extends Observable<ApolloQueryResult<TData>>
    // (onNext: (value: T) => void, onError?: (error: any) => void, onComplete?: () => void): ZenObservable.Subscription;
    @send
    external subscribe: (
      t<'jsData>,
      ~onNext: ApolloQueryResult.Js_.t<'jsData> => unit,
      ~onError: Js.Json.t => unit=?,
      ~onComplete: unit => unit=?,
      unit,
    ) => Subscription.Js_.t = "subscribe"
  }

  type t<'data> = {
    @as("rescript_subscribe")
    subscribe: (
      ~onNext: ApolloQueryResult.t<'data> => unit,
      ~onError: Js.Json.t => unit=?,
      ~onComplete: unit => unit=?,
      unit,
    ) => Subscription.t,
  }

  external castFromJs: Js_.t<'data> => t<'data> = "%identity"

  external castToJs: t<'data> => Js_.t<'data> = "%identity"

  let preserveJsPropsAndContext: (Js_.t<'jsData>, t<'data>) => t<'data> = (js, t) =>
    %raw(`
          function (js, t) {
            return Object.assign(js, t)
          }
        `)(js, t)

  let fromJs: (Js_.t<'jsData>, ~safeParse: Types.safeParse<'data, 'jsData>) => t<'data> = (
    js,
    ~safeParse,
  ) => {
    let parseWithOnErrorCall = (jsData, onError) =>
      switch safeParse(jsData) {
      | Ok(data) => Some(data)
      | Error({error}) =>
        onError(error)
        None
      }

    let observableWithParsedData = js->Js_.fakeMap(parseWithOnErrorCall)

    preserveJsPropsAndContext(
      observableWithParsedData,
      {
        subscribe: (~onNext, ~onError=?, ~onComplete=?, ()) =>
          js
          ->Js_.subscribe(
            ~onNext=jsApolloQueryResult =>
              onNext(jsApolloQueryResult->ApolloQueryResult.fromJs(~safeParse)),
            ~onError?,
            ~onComplete?,
            (),
          )
          ->Subscription.fromJs,
      },
    )
  }
}
