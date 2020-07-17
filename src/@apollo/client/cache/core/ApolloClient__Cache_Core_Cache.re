module DataProxy = ApolloClient__Cache_Core_Types.DataProxy;
module Types = ApolloClient__Types;

module type Fragment = Types.Fragment;
module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

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
    type t('tSerialized);

    type reference;

    // readQuery<QueryType, TVariables = any>(options: DataProxy.Query<TVariables>, optimistic?: boolean): QueryType | null;
    [@bs.send]
    external readQuery:
      (
        t('tSerialized),
        ~options: DataProxy.Query.Js_.t('variables),
        ~optimistic: option(bool)
      ) =>
      Js.nullable('jsData) =
      "readQuery";

    // writeFragment<TData = any, TVariables = any>(options: Cache.WriteFragmentOptions<TData, TVariables>): Reference | undefined;
    [@bs.send]
    external writeFragment:
      (
        t('tSerialized),
        ~options: DataProxy.WriteFragmentOptions.Js_.t('jsData, 'variables)
      ) =>
      option(reference) =
      "writeFragment";

    // writeQuery<TData = any, TVariables = any>(options: Cache.WriteQueryOptions<TData, TVariables>): Reference | undefined;
    [@bs.send]
    external writeQuery:
      (
        t('tSerialized),
        ~options: DataProxy.WriteQueryOptions.Js_.t('jsData, 'variables)
      ) =>
      option(reference) =
      "writeQuery";
  };

  type reference = Js_.reference;

  type t('tSerialized) = Js_.t('tSerialized);

  let readQuery:
    type data jsVariables.
      (
        t('tSerialized),
        ~query: (module Operation with
                   type t = data and type Raw.t_variables = jsVariables),
        ~id: string=?,
        ~optimistic: bool=?,
        jsVariables
      ) =>
      option(data) =
    (client, ~query as (module Operation), ~id=?, ~optimistic=?, variables) => {
      Js_.readQuery(
        client,
        ~options={id, query: Operation.query, variables},
        ~optimistic,
      )
      ->Js.toOption
      ->Belt.Option.map(Operation.parse);
    };

  let writeFragment:
    type data jsVariables.
      (
        t('tSerialized),
        ~fragment: (module Fragment with type t = data),
        ~data: data,
        ~broadcast: bool=?,
        ~id: string,
        ~fragmentName: string=?,
        unit
      ) =>
      // jsVariables
      option(reference) =
    (
      client,
      ~fragment as (module Fragment),
      ~data: data,
      ~broadcast=?,
      ~id,
      ~fragmentName=?,
      (),
    ) => {
      // variables,
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
    type data jsVariables.
      (
        t('tSerialized),
        ~query: (module Operation with
                   type t = data and type Raw.t_variables = jsVariables),
        ~broadcast: bool=?,
        ~data: data,
        ~id: string=?,
        jsVariables
      ) =>
      option(reference) =
    (
      client,
      ~query as (module Operation),
      ~broadcast=?,
      ~data,
      ~id=?,
      variables,
    ) => {
      Js_.writeQuery(
        client,
        ~options={
          broadcast,
          data: data->Operation.serialize,
          id,
          query: Operation.query,
          variables,
        },
      );
    };
};
