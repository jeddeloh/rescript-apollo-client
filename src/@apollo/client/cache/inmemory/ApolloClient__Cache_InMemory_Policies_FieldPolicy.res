module ApolloCache = ApolloClient__Cache_Core_Cache.ApolloCache
module CanReadFunction = ApolloClient__Cache_Core_Types_Common.CanReadFunction
module FieldNode = ApolloClient__Graphql.Language.Ast.FieldNode
module ReadFieldFunction = ApolloClient__Cache_Core_Types_Common.ReadFieldFunction
module ToReferenceFunction = ApolloClient__Cache_Core_Types_Common.ToReferenceFunction

module StorageType = {
  type t = Js.Dict.t<Js.Json.t>
  module Js_ = {
    type t = t
  }
}

module FieldFunctionOptions = {
  type unimplemented

  module Js_ = {
    // export interface FieldFunctionOptions<TArgs = Record<string, any>, TVars = Record<string, any>> {
    //     args: TArgs | null;
    //     fieldName: string;
    //     storeFieldName: string;
    //     field: FieldNode | null;
    //     variables?: TVars;
    //     isReference: typeof isReference;
    //     toReference: ToReferenceFunction;
    //     storage: StorageType | null;
    //     cache: InMemoryCache;
    //     readField: ReadFieldFunction;
    //     canRead: CanReadFunction;
    //     mergeObjects<T extends StoreObject | Reference>(existing: T, incoming: T): T | undefined;
    // }
    type t = {
      args: Js.nullable<Js.Dict.t<Js.Json.t>>,
      fieldName: string,
      storeFieldName: string,
      field: Js.nullable<FieldNode.t>,
      variables: option<Js.Dict.t<Js.Json.t>>,
      isReference: bool,
      toReference: unimplemented,
      readField: unimplemented,
      canRead: unimplemented,
      storage: Js.nullable<StorageType.Js_.t>,
      cache: ApolloCache.t<Js.Json.t>, // Non-Js_ ApolloCache is correct here
    }
    @send external canRead: t => CanReadFunction.Js_.t = "canRead"
    @send
    external mergeObjects: (t, ~existing: Js.Json.t, ~incoming: Js.Json.t) => option<Js.Json.t> =
      "canRead"
    @send external readField: t => ReadFieldFunction.Js_.t = "readField"
    @send
    external toReference: t => ToReferenceFunction.t = "toReference"
  }

  type t = {
    args: Js.nullable<Js.Dict.t<Js.Json.t>>,
    fieldName: string,
    storeFieldName: string,
    field: Js.nullable<FieldNode.t>,
    variables: option<Js.Dict.t<Js.Json.t>>,
    isReference: bool,
    toReference: unimplemented,
    storage: Js.nullable<StorageType.t>,
    cache: ApolloCache.t<Js.Json.t>,
    readField: unimplemented,
    canRead: unimplemented,
    mergeObjects: (~existing: Js.Json.t, ~incoming: Js.Json.t) => option<Js.Json.t>,
  }

  let fromJs: Js_.t => t = js => {
    args: js.args,
    fieldName: js.fieldName,
    storeFieldName: js.storeFieldName,
    field: js.field,
    variables: js.variables,
    isReference: js.isReference,
    toReference: js.toReference,
    storage: js.storage,
    cache: js.cache,
    readField: js.readField,
    canRead: js.canRead,
    mergeObjects: (~existing: Js.Json.t, ~incoming: Js.Json.t) =>
      js->Js_.mergeObjects(~existing, ~incoming),
  }
}

module FieldMergeFunction = {
  type t<'existing> = ('existing, 'existing, FieldFunctionOptions.t) => 'existing

  module Js_ = {
    //  export type FieldMergeFunction<
    //    TExisting = any,
    //    TIncoming = TExisting,
    //    // Passing the whole FieldFunctionOptions makes the current definition
    //    // independent from its implementation
    //    TOptions extends FieldFunctionOptions = FieldFunctionOptions
    //  > = (
    //    existing: SafeReadonly<TExisting> | undefined,
    //    // The incoming parameter needs to be positional as well, for the same
    //    // reasons discussed in FieldReadFunction above.
    //    incoming: SafeReadonly<TIncoming>,
    //    options: TOptions,
    //  ) => SafeReadonly<TExisting>;
    type t<'existing> = ('existing, 'existing, FieldFunctionOptions.Js_.t) => 'existing
  }

  let toJs: t<'existing> => Js_.t<'existing> = (t, existing, incoming, jsFieldFunctionOptions) =>
    t(existing, incoming, jsFieldFunctionOptions->FieldFunctionOptions.fromJs)
}

module FieldMerge = {
  type t<'existing> =
    | MergeFunction(FieldMergeFunction.t<'existing>)
    | True

  module Js_ = {
    // FieldMergeFunction<TExisting, TIncoming, TOptions> | boolean;
    module FieldMergeUnion: {
      type t<'existing>
      let mergeFunction: FieldMergeFunction.Js_.t<'existing> => t<'existing>
      let true_: t<'existing>
    } = {
      @unboxed
      type rec t<'existing> = Any('a): t<'existing>
      let mergeFunction = (v: FieldMergeFunction.Js_.t<'existing>) => Any(v)
      let true_ = Any(true)
    }

    type t<'existing> = FieldMergeUnion.t<'existing>
  }

  let toJs: t<'existing> => Js_.t<'existing> = x =>
    switch x {
    | MergeFunction(mergeFunction) =>
      mergeFunction->FieldMergeFunction.toJs->Js_.FieldMergeUnion.mergeFunction
    | True => Js_.FieldMergeUnion.true_
    }
}

module FieldReadFunction = {
  type t<'existing> = (option<'existing>, FieldFunctionOptions.t) => 'existing

  module Js_ = {
    // export declare type FieldReadFunction<TExisting = any, TReadResult = TExisting> = (existing: SafeReadonly<TExisting> | undefined, options: FieldFunctionOptions) => TReadResult | undefined;
    type t<'existing> = (option<'existing>, FieldFunctionOptions.Js_.t) => 'existing
  }

  let toJs: t<'existing> => Js_.t<'existing> = (t, existing, jsFieldFunctionOptions) =>
    t(existing, jsFieldFunctionOptions->FieldFunctionOptions.fromJs)
}

module KeySpecifier = {
  type t = array<string>
  module Js_ = {
    // declare type KeySpecifier = (string | any[])[];
    type t = t
  }
}

module KeyArgsFunction = {
  type t_context = {
    typename: string,
    fieldName: string,
    field: Js.null<FieldNode.t>,
    variables: option<Js.Json.t>,
  }

  type t = (Js.nullable<Js.Json.t>, t_context) => KeySpecifier.t

  module Js_ = {
    // export declare type KeyArgsFunction = (args: Record<string, any> | null, context: {
    //     typename: string;
    //     fieldName: string;
    //     field: FieldNode | null;
    //     variables?: Record<string, any>;
    // }) => KeySpecifier | ReturnType<IdGetter>;
    type t = t
  }
}

module FieldPolicy_KeyArgs = {
  type t =
    | KeySpecifier(KeySpecifier.t)
    | KeyArgsFunction(KeyArgsFunction.t)
    | False

  module Js_ = {
    module KeyArgsUnion: {
      type t
      let keySpecifier: KeySpecifier.Js_.t => t
      let keyArgsFunction: KeyArgsFunction.Js_.t => t
      let false_: t
    } = {
      @unboxed
      type rec t = Any('a): t
      let keySpecifier = (v: KeySpecifier.Js_.t) => Any(v)
      let keyArgsFunction = (v: KeyArgsFunction.Js_.t) => Any(v)
      let false_ = Any(false)
    }

    type t = KeyArgsUnion.t
  }

  let toJs: t => Js_.t = x =>
    switch x {
    | KeySpecifier(keySpecifier) => keySpecifier->Js_.KeyArgsUnion.keySpecifier
    | KeyArgsFunction(keyArgsFunction) => keyArgsFunction->Js_.KeyArgsUnion.keyArgsFunction
    | False => Js_.KeyArgsUnion.false_
    }
}

module FieldPolicy = {
  type t<'existing> = {
    keyArgs: option<FieldPolicy_KeyArgs.t>,
    read: option<FieldReadFunction.t<'existing>>,
    merge: option<FieldMerge.t<'existing>>,
  }

  module Js_ = {
    // export declare type FieldPolicy<TExisting = any, TIncoming = TExisting, TReadResult = TExisting> = {
    //     keyArgs?: KeySpecifier | KeyArgsFunction | false;
    //     read?: FieldReadFunction<TExisting, TReadResult>;
    //     merge?: FieldMergeFunction<TExisting, TIncoming> | boolean;
    // };
    type t<'existing> = {
      keyArgs: option<FieldPolicy_KeyArgs.Js_.t>,
      read: option<FieldReadFunction.Js_.t<'existing>>,
      merge: option<FieldMerge.Js_.t<'existing>>,
    }
  }

  let toJs: t<'existing> => Js_.t<'existing> = t => {
    keyArgs: t.keyArgs->Belt.Option.map(FieldPolicy_KeyArgs.toJs),
    read: t.read->Belt.Option.map(FieldReadFunction.toJs),
    merge: t.merge->Belt.Option.map(FieldMerge.toJs),
  }
}
