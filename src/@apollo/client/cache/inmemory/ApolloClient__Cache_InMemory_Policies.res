module FragmentMap = ApolloClient__Utilities_Graphql_Fragments.FragmentMap
module FieldPolicy = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldPolicy
module FieldReadFunction = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldReadFunction
module FieldMergeFunction = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldMergeFunction
module KeyArgs = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldPolicy_KeyArgs
module KeySpecifier = ApolloClient__Cache_InMemory_Policies_FieldPolicy.KeySpecifier
module Pagination = ApolloClient__Utilities_Policies_Pagination
module SelectionSetNode = ApolloClient__Graphql.Language.Ast.SelectionSetNode

module KeyFieldsContext = {
  type t = {
    typename?: string,
    selectionSet?: SelectionSetNode.t,
    fragment?: FragmentMap.t,
    keyObject?: Js.Json.t,
  }
}

module KeyFieldsFunction = {
  type t = (Js.Json.t, KeyFieldsContext.t) => string
  module Js_ = {
    // export declare type KeyFieldsFunction = (object: Readonly<StoreObject>, context: KeyFieldsContext) => KeySpecifier | ReturnType<IdGetter>;
    type t = t
  }
}

// export declare const defaultDataIdFromObject: KeyFieldsFunction;
@module("@apollo/client")
external defaultDataIdFromObject: KeyFieldsFunction.t = "defaultDataIdFromObject"

module TypePolicy = {
  module Js_ = {
    module FieldsUnion: {
      type t
      let fieldPolicy: FieldPolicy.Js_.t<'existing> => t
      let fieldReadFunction: FieldReadFunction.Js_.t<'existing> => t
    } = {
      @unboxed
      type rec t = Any('a): t
      let fieldPolicy = (v: FieldPolicy.Js_.t<'existing>) => Any(v)
      let fieldReadFunction = (v: FieldReadFunction.Js_.t<'existing>) => Any(v)
    }

    // export declare type TypePolicy = {
    //     keyFields?: KeySpecifier | KeyFieldsFunction | false;
    //     queryType?: true;
    //     mutationType?: true;
    //     subscriptionType?: true;
    //     fields?: {
    //         [fieldName: string]: FieldPolicy<any> | FieldReadFunction<any>;
    //     };
    // };
    type t = {
      keyFields?: KeyArgs.Js_.t,
      queryType?: bool,
      mutationType?: bool,
      subscriptionType?: bool,
      fields?: Js.Dict.t<FieldsUnion.t>,
    }
  }

  type rec t_field =
    | ConcatPagination(KeyArgs.t)
    | OffsetLimitPagination(KeyArgs.t)
    | RelayStylePagination(KeyArgs.t)
    | FieldPolicy(FieldPolicy.t<'existing>): t_field
    | FieldReadFunction(FieldReadFunction.t<'existing>): t_field

  type fieldKey = string

  type t_fields = array<(fieldKey, t_field)>

  type t = {
    keyFields?: KeyArgs.t,
    queryType?: bool,
    mutationType?: bool,
    subscriptionType?: bool,
    fields?: t_fields,
  }

  let toJs: t => Js_.t = t => {
    keyFields: ?t.keyFields->Belt.Option.map(KeyArgs.toJs),
    queryType: ?t.queryType,
    mutationType: ?t.mutationType,
    subscriptionType: ?t.subscriptionType,
    fields: ?t.fields->Belt.Option.mapU(fields =>
      fields
      ->Belt.Array.mapU(((fieldKey, t_field)) => (
        fieldKey,
        switch t_field {
        | ConcatPagination(keyArgs) =>
          Pagination.concatPagination(keyArgs)->Js_.FieldsUnion.fieldPolicy
        | OffsetLimitPagination(keyArgs) =>
          Pagination.offsetLimitPagination(keyArgs)->Js_.FieldsUnion.fieldPolicy
        | RelayStylePagination(keyArgs) =>
          Pagination.relayStylePagination(keyArgs)->Js_.FieldsUnion.fieldPolicy

        | FieldPolicy(fieldPolicy) => fieldPolicy->FieldPolicy.toJs->Js_.FieldsUnion.fieldPolicy
        | FieldReadFunction(fieldReadFunction) =>
          FieldReadFunction.toJs(fieldReadFunction)->Js_.FieldsUnion.fieldReadFunction
        },
      ))
      ->Js.Dict.fromArray
    ),
  }

  @deprecated("Construct the record directly instead")
  let make: (
    ~fields: t_fields=?,
    ~keyFields: KeyArgs.t=?,
    ~mutationType: bool=?,
    ~queryType: bool=?,
    ~subscriptionType: bool=?,
    unit,
  ) => t = (~fields=?, ~keyFields=?, ~mutationType=?, ~queryType=?, ~subscriptionType=?, ()) => {
    ?fields,
    ?keyFields,
    ?mutationType,
    ?queryType,
    ?subscriptionType,
  }
}

module TypePolicies = {
  module Js_ = {
    // export declare type TypePolicies = {
    //     [__typename: string]: TypePolicy;
    // };
    type t = RescriptCore.Dict.t<TypePolicy.Js_.t>
  }

  type typename = string

  type t = array<(typename, TypePolicy.t)>

  let toJs: t => Js_.t = t =>
    t
    ->Belt.Array.map(((key, policy)) => (key, TypePolicy.toJs(policy)))
    ->Js.Dict.fromArray
}

module PossibleTypesMap = {
  type t = RescriptCore.Dict.t<array<string>>
  module Js_ = {
    // export declare type PossibleTypesMap = {
    //     [supertype: string]: string[];
    // };
    type t = t
  }
}
