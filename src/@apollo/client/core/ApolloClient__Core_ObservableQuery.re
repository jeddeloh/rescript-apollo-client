module ObservableQuery = {
  module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult;
  module Subscription = ApolloClient__ZenObservable.Subscription;
  module Observer = ApolloClient__ZenObservable.Observer;

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
    type t('jsData);

    // ...extends Observable<ApolloQueryResult<TData>>
    // <R>(callback: (value: T) => R): Observable<R>;
    [@bs.send] external map: (t('t), 't => 'r) => t('r) = "map";

    // ...extends Observable<ApolloQueryResult<TData>>
    // (onNext: (value: T) => void, onError?: (error: any) => void, onComplete?: () => void): ZenObservable.Subscription;
    [@bs.send]
    external subscribe:
      (
        t('jsData),
        ~onNext: ApolloQueryResult.Js_.t('jsData) => unit,
        ~onError: Js.Json.t => unit=?,
        ~onComplete: unit => unit=?,
        unit
      ) =>
      Subscription.Js_.t =
      "subscribe";
  };

  type t('data);

  external castFromJs: Js_.t('data) => t('data) = "%identity";

  external castToJs: t('data) => Js_.t('data) = "%identity";

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      // Lovely. We should be able to just map, but it's broken:
      // https://github.com/apollographql/apollo-client/issues/6144
      // js->Js_.map(ApolloQueryResult.fromJs(~parse))->castFromJs;
      [%raw
        {|
          function (js, parse) {
            var originalSubscribe = js.subscribe.bind(js);
            js.subscribe = function (onNext, onError, onComplete) {
              var newOnNext = function (result) {
                var parsedResult = result.data
                  ? Object.assign({}, result, { data: parse(result.data) })
                  : result;
                return onNext(parsedResult);
              };
              return originalSubscribe(newOnNext, onError, onComplete);
            };
            return js;
          }
        |}
      ](
        js,
        parse,
      );
    };

  [@bs.send] external map: (t('a), 'a => 'b) => t('b) = "map";

  let subscribe:
    (
      t('data),
      ~onNext: ApolloQueryResult.t('data) => unit,
      ~onError: Js.Json.t => unit=?,
      ~onComplete: unit => unit=?,
      unit
    ) =>
    Subscription.t =
    (t, ~onNext, ~onError=?, ~onComplete=?, ()) =>
      /**
       * Ugh, this diverges from normal patterns because data in these callbacks has to be parsed before this point.
       * I wonder if there is a way we could pass parse along and then use it here or maybe there is a better pattern for this.
       */
      (
        Js_.subscribe(
          t->castToJs,
          ~onNext=Obj.magic(onNext),
          ~onError?,
          ~onComplete?,
          (),
        )
        ->Subscription.fromJs
      );
};
