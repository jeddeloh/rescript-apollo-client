module DataProxy = ApolloClient__Cache_Core_Types.DataProxy
module Types = ApolloClient__Types
module Utils = ApolloClient__Utils

module type Fragment = Types.Fragment
module type Operation = Types.Operation
module type OperationNoRequiredVars = Types.OperationNoRequiredVars

module ApolloCache = {
  module Js_ = {
    // export declare abstract class ApolloCache<TSerialized> implements DataProxy {
    //     abstract read<T, TVariables = any>(query: Cache.ReadOptions<TVariables>): T | null;
    //     abstract write<TResult = any, TVariables = any>(write: Cache.WriteOptions<TResult, TVariables>): Reference | undefined;
    //     abstract diff<T>(query: Cache.DiffOptions): Cache.DiffResult<T>;
    //     abstract watch(watch: Cache.WatchOptions): () => void;
    //     abstract reset(): Promise<void>;
    //     abstract evict(options: Cache.EvictOptions): boolean;
    //     abstract restore(serializedState: TSerialized): ApolloCache<TSerialized>;
    //     abstract extract(optimistic?: boolean): TSerialized;
    //     abstract removeOptimistic(id: string): void;
    //     abstract performTransaction(transaction: Transaction<TSerialized>, optimisticId?: string | null): void;
    //     recordOptimisticTransaction(transaction: Transaction<TSerialized>, optimisticId: string): void;
    //     transformDocument(document: DocumentNode): DocumentNode;
    //     identify(object: StoreObject | Reference): string | undefined;
    //     gc(): string[];
    //     modify(options: Cache.ModifyOptions): boolean;
    //     transformForLink(document: DocumentNode): DocumentNode;
    //     readQuery<QueryType, TVariables = any>(options: Cache.ReadQueryOptions<TVariables>, optimistic?: boolean): QueryType | null;
    //     private getFragmentDoc;
    //     readFragment<FragmentType, TVariables = any>(options: Cache.ReadFragmentOptions<TVariables>, optimistic?: boolean): FragmentType | null;
    //     writeQuery<TData = any, TVariables = any>(options: Cache.WriteQueryOptions<TData, TVariables>): Reference | undefined;
    //     writeFragment<TData = any, TVariables = any>(options: Cache.WriteFragmentOptions<TData, TVariables>): Reference | undefined;
    //     updateQuery<TData = any, TVariables = any>(options: Cache.UpdateQueryOptions<TData, TVariables>, update: (data: TData | null) => TData | null | void): TData | null;
    //     updateFragment<TData = any, TVariables = any>(options: Cache.UpdateFragmentOptions<TData, TVariables>, update: (data: TData | null) => TData | null | void): TData | null;
    // }
    type t<'tSerialized>

    type reference

    // readFragment<FragmentType, TVariables = any>(options: DataProxy.ReadFragmentOptions<TVariables>, optimistic?: boolean): FragmentType | null;
    @send
    external readFragment: (
      t<'tSerialized>,
      ~options: DataProxy.ReadFragmentOptions.Js_.t,
      ~optimistic: bool=?,
      unit,
    ) => Js.nullable<'jsData> = "readFragment"

    // readQuery<QueryType, TVariables = any>(options: DataProxy.ReadQueryOptions<TVariables>, optimistic?: boolean): QueryType | null;
    @send
    external readQuery: (
      t<'tSerialized>,
      ~options: DataProxy.ReadQueryOptions.Js_.t<'jsVariables>,
      ~optimistic: option<bool>=?,
    ) => Js.nullable<'jsData> = "readQuery"

    // writeFragment<TData = any, TVariables = any>(options: Cache.WriteFragmentOptions<TData, TVariables>): Reference | undefined;
    @send
    external writeFragment: (
      t<'tSerialized>,
      ~options: DataProxy.WriteFragmentOptions.Js_.t<'jsData, 'jsVariables>,
    ) => option<reference> = "writeFragment"

    // writeQuery<TData = any, TVariables = any>(options: Cache.WriteQueryOptions<TData, TVariables>): Reference | undefined;
    @send
    external writeQuery: (
      t<'tSerialized>,
      ~options: DataProxy.WriteQueryOptions.Js_.t<'jsData, 'jsVariables>,
    ) => option<reference> = "writeQuery"

    // updateQuery<TData = any, TVariables = any>(options: Cache.UpdateQueryOptions<TData, TVariables>, update: (data: TData | null) => TData | null | void): TData | null
    @send
    external updateQuery: (
      t<'tSerialized>,
      ~options: DataProxy.UpdateQueryOptions.Js_.t<'jsVariables>,
      ~update: Js.null<'jsData> => Js.nullable<'jsData>,
    ) => Js.nullable<'jsData> = "updateQuery"

    // updateFragment<TData = any, TVariables = any>(options: Cache.UpdateFragmentOptions<TData, TVariables>, update: (data: TData | null) => TData | null | void): TData | null
    @send
    external updateFragment: (
      t<'tSerialized>,
      ~options: DataProxy.UpdateFragmentOptions.Js_.t<'jsVariables>,
      ~update: Js.null<'jsData> => Js.nullable<'jsData>,
    ) => Js.nullable<'jsData> = "updateFragment"
  }

  type reference = Js_.reference

  type t<'tSerialized> = {
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
    @as("rescript_writeFragment")
    writeFragment: 'data. (
      ~fragment: module(Fragment with type t = 'data),
      ~data: 'data,
      ~broadcast: bool=?,
      ~overwrite: bool=?,
      ~id: string,
      ~fragmentName: string=?,
      unit,
    ) => option<reference>,
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
    ) => option<reference>,
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

  let preserveJsPropsAndContext: (Js_.t<'a>, t<'a>) => t<'a> = (js, t) =>
    %raw(`
          function (js, t) {
            return Object.assign(js, t)
          }
        `)(js, t)

  let fromJs: Js_.t<'serialized> => t<'serialized> = js => {
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

      js
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

      js
      ->Js_.readQuery(
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

    let writeFragment = (
      type data,
      ~fragment as module(Fragment: Fragment with type t = data),
      ~data: data,
      ~broadcast=?,
      ~overwrite=?,
      ~id,
      ~fragmentName=?,
      // variables,
      (),
    ) =>
      js->Js_.writeFragment(
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
      js->Js_.writeQuery(
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

      js
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

      js
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
      js,
      {
        readFragment: readFragment,
        readQuery: readQuery,
        writeFragment: writeFragment,
        writeQuery: writeQuery,
        updateFragment: updateFragment,
        updateQuery: updateQuery,
      },
    )
  }
}
