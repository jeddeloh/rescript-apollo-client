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
    typename: option<string>,
    selectionSet: option<SelectionSetNode.t>,
    fragment: option<FragmentMap.t>,
    keyObject: option<Js.Json.t>,
  }
  module Js_ = {
    // declare type KeyFieldsContext = {
    //     typename?: string;
    //     selectionSet?: SelectionSetNode;
    //     fragmentMap?: FragmentMap;
    //     keyObject?: Record<string, any>;
    // };
    type t = t = {
      typename: option<string>,
      selectionSet: option<SelectionSetNode.t>,
      fragment: option<FragmentMap.Js_.t>,
      keyObject: option<Js.Json.t>,
    }
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
      keyFields: option<KeyArgs.Js_.t>,
      queryType: option<bool>,
      mutationType: option<bool>,
      subscriptionType: option<bool>,
      fields: option<Js.Dict.t<FieldsUnion.t>>,
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
    keyFields: option<KeyArgs.t>,
    queryType: option<bool>,
    mutationType: option<bool>,
    subscriptionType: option<bool>,
    fields: option<t_fields>,
  }

  let toJs: (. t) => Js_.t = (. t) => {
    keyFields: t.keyFields->Belt.Option.map(KeyArgs.toJs),
    queryType: t.queryType,
    mutationType: t.mutationType,
    subscriptionType: t.subscriptionType,
    fields: t.fields->Belt.Option.map(fields =>
      fields
      ->Belt.Array.map(((fieldKey, t_field)) => (
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
          fieldReadFunction->FieldReadFunction.toJs->Js_.FieldsUnion.fieldReadFunction
        },
      ))
      ->Js.Dict.fromArray
    ),
  }

  let make: (
    ~fields: t_fields=?,
    ~keyFields: KeyArgs.t=?,
    ~mutationType: bool=?,
    ~queryType: bool=?,
    ~subscriptionType: bool=?,
    unit,
  ) => t = (~fields=?, ~keyFields=?, ~mutationType=?, ~queryType=?, ~subscriptionType=?, ()) => {
    fields: fields,
    keyFields: keyFields,
    mutationType: mutationType,
    queryType: queryType,
    subscriptionType: subscriptionType,
  }
}

module TypePolicies = {
  module Js_ = {
    // export declare type TypePolicies = {
    //     [__typename: string]: TypePolicy;
    // };
    type t = Js.Dict.t<TypePolicy.Js_.t>
  }

  type typename = string

  type t = array<(typename, TypePolicy.t)>

  let toJs: t => Js_.t = t =>
    t->Belt.Array.map(((key, policy)) => (key, TypePolicy.toJs(. policy)))->Js.Dict.fromArray
}

module PossibleTypesMap = {
  type t = Js.Dict.t<array<string>>
  module Js_ = {
    // export declare type PossibleTypesMap = {
    //     [supertype: string]: string[];
    // };
    type t = t
  }
}
