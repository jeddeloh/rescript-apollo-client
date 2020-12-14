module StoreValue = ApolloClient__Utilities_Graphql_StoreUtils.StoreValue

module CanReadFunction = {
  type t = StoreValue.Js_.t => bool
  module Js_ = {
    // export declare type CanReadFunction = (value: StoreValue) => boolean;
    type t = t
  }
}

module ReadFieldFunction = {
  type t
  module Js_ = {
    // export interface ReadFieldFunction {
    //     <V = StoreValue>(options: ReadFieldOptions): SafeReadonly<V> | undefined;
    //     <V = StoreValue>(fieldName: string, from?: StoreObject | Reference): SafeReadonly<V> | undefined;
    // }
    type t = t // Please contribute if you need this!
  }
}

module ToReferenceFunction = {
  type t
  module Js_ = {
    // export declare type ToReferenceFunction = (objOrIdOrRef: StoreObject | string | Reference, mergeIntoStore?: boolean) => Reference | undefined;
    type t = t // Please contribute if you need this!
  }
}
