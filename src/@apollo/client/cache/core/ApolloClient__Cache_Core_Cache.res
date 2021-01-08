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
    //     readQuery<QueryType, TVariables = any>(options: DataProxy.Query<TVariables>, optimistic?: boolean): QueryType | null;
    //     private getFragmentDoc;
    //     readFragment<FragmentType, TVariables = any>(options: DataProxy.Fragment<TVariables>, optimistic?: boolean): FragmentType | null;
    //     writeQuery<TData = any, TVariables = any>(options: Cache.WriteQueryOptions<TData, TVariables>): Reference | undefined;
    //     writeFragment<TData = any, TVariables = any>(options: Cache.WriteFragmentOptions<TData, TVariables>): Reference | undefined;
    // }
    type t<'tSerialized>

    type reference

    // readFragment<FragmentType, TVariables = any>(options: DataProxy.Fragment<TVariables>, optimistic?: boolean): FragmentType | null;
    @bs.send
    external readFragment: (
      t<'tSerialized>,
      ~options: DataProxy.Fragment.Js_.t,
      ~optimistic: bool=?,
      unit,
    ) => Js.nullable<'jsData> = "readFragment"

    // readQuery<QueryType, TVariables = any>(options: DataProxy.Query<TVariables>, optimistic?: boolean): QueryType | null;
    @bs.send
    external readQuery: (
      t<'tSerialized>,
      ~options: DataProxy.Query.Js_.t<'jsVariables>,
      ~optimistic: option<bool>,
    ) => Js.nullable<'jsData> = "readQuery"

    // writeFragment<TData = any, TVariables = any>(options: Cache.WriteFragmentOptions<TData, TVariables>): Reference | undefined;
    @bs.send
    external writeFragment: (
      t<'tSerialized>,
      ~options: DataProxy.WriteFragmentOptions.Js_.t<'jsData, 'jsVariables>,
    ) => option<reference> = "writeFragment"

    // writeQuery<TData = any, TVariables = any>(options: Cache.WriteQueryOptions<TData, TVariables>): Reference | undefined;
    @bs.send
    external writeQuery: (
      t<'tSerialized>,
      ~options: DataProxy.WriteQueryOptions.Js_.t<'jsData, 'jsVariables>,
    ) => option<reference> = "writeQuery"
  }

  type reference = Js_.reference

  type t<'tSerialized> = {
    @bs.as("rescript_readFragment")
    readFragment: 'data. (
      ~fragment: module(Fragment with type t = 'data),
      ~id: string,
      ~optimistic: bool=?,
      ~fragmentName: string=?,
      unit,
    ) => option<Types.parseResult<'data>>,
    @bs.as("rescript_readQuery")
    readQuery: 'data 'variables 'jsVariables. (
      ~query: module(Operation with
        type t = 'data
        and type t_variables = 'variables
        and type Raw.t_variables = 'jsVariables
      ),
      ~id: string=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      ~optimistic: bool=?,
      'variables,
    ) => option<Types.parseResult<'data>>,
    @bs.as("rescript_writeFragment")
    writeFragment: 'data. (
      ~fragment: module(Fragment with type t = 'data),
      ~data: 'data,
      ~broadcast: bool=?,
      ~id: string,
      ~fragmentName: string=?,
      unit,
    ) => option<reference>,
    @bs.as("rescript_writeQuery")
    writeQuery: 'data 'variables 'jsVariables. (
      ~query: module(Operation with
        type t = 'data
        and type t_variables = 'variables
        and type Raw.t_variables = 'jsVariables
      ),
      ~broadcast: bool=?,
      ~data: 'data,
      ~id: string=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      'variables,
    ) => option<reference>,
  }

  let preserveJsPropsAndContext: (Js_.t<'a>, t<'a>) => t<'a> = (js, t) =>
    %bs.raw(`
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
      ~fragmentName=?,
      (),
    ) => {
      let safeParse = Utils.safeParse(Fragment.parse)

      js
      ->Js_.readFragment(
        ~options={id: id, fragment: Fragment.query, fragmentName: fragmentName},
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
      variables,
    ) => {
      let safeParse = Utils.safeParse(Operation.parse)

      js
      ->Js_.readQuery(
        ~options=DataProxy.Query.toJs(
          {id: id, query: Operation.query, variables: variables},
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
      ~data,
      ~id=?,
      ~mapJsVariables=Utils.identity,
      variables,
    ) =>
      js->Js_.writeQuery(
        ~options=DataProxy.WriteQueryOptions.toJs(
          {broadcast: broadcast, data: data, id: id, query: Operation.query, variables: variables},
          ~mapJsVariables,
          ~serialize=Operation.serialize,
          ~serializeVariables=Operation.serializeVariables,
        ),
      )

    preserveJsPropsAndContext(
      js,
      {
        readFragment: readFragment,
        readQuery: readQuery,
        writeFragment: writeFragment,
        writeQuery: writeQuery,
      },
    )
  }
}
