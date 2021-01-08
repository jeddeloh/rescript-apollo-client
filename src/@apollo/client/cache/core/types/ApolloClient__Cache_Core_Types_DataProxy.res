module Graphql = ApolloClient__Graphql
module Utils = ApolloClient__Utils

module Query = {
  module Js_ = {
    // interface Query<TVariables> {
    //   query: DocumentNode;
    //   variables?: TVariables;
    //   id?: string;
    // }
    type t<'jsVariables> = {
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      id: option<string>,
    }
  }

  type t<'jsVariables> = Js_.t<'jsVariables>

  let toJs: (
    t<'variables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~serializeVariables: 'variables => 'jsVariables,
  ) => Js_.t<'jsVariables> = (t, ~mapJsVariables=Utils.identity, ~serializeVariables) => {
    query: t.query,
    variables: t.variables->serializeVariables->mapJsVariables,
    id: t.id,
  }
}

module Fragment = {
  module Js_ = {
    // interface Fragment<TVariables> {
    //   id: string;
    //   fragment: DocumentNode;
    //   fragmentName?: string;
    //   variables?: TVariables;
    // }
    type t = {
      id: string,
      fragment: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      // variables: 'jsVariables,
      fragmentName: option<string>,
    }
  }

  type t = Js_.t = {
    id: string,
    fragment: Graphql.documentNode,
    // We don't allow optional variables because it's not typesafe
    // variables: 'jsVariables,
    fragmentName: option<string>,
  }
}

module WriteQueryOptions = {
  module Js_ = {
    // interface WriteQueryOptions<TData, TVariables> extends Query<TVariables> {
    //   data: TData;
    //   broadcast?: boolean;
    // }
    type t<'jsData, 'jsVariables> = {
      data: 'jsData,
      broadcast: option<bool>,
      // ...extends Query
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      id: option<string>,
    }
  }

  type t<'data, 'variables> = {
    data: 'data,
    broadcast: option<bool>,
    query: Graphql.documentNode,
    variables: 'variables,
    id: option<string>,
  }

  let toJs: (
    t<'data, 'variables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~serialize: 'data => 'jsData,
    ~serializeVariables: 'variables => 'jsVariables,
  ) => Js_.t<'jsData, 'jsVariables> = (
    t,
    ~mapJsVariables=Utils.identity,
    ~serialize,
    ~serializeVariables,
  ) => {
    data: t.data->serialize,
    broadcast: t.broadcast,
    query: t.query,
    variables: t.variables->serializeVariables->mapJsVariables,
    id: t.id,
  }
}

module WriteFragmentOptions = {
  module Js_ = {
    // interface WriteFragmentOptions<TData, TVariables> extends Fragment<TVariables> {
    //    data: TData;
    //    broadcast?: boolean;
    // }
    type t<'jsData, 'jsVariables> = {
      data: 'jsData,
      broadcast: option<bool>,
      // ...extends Fragment
      id: string,
      fragment: Graphql.documentNode,
      fragmentName: option<string>,
      // I think fragment variables are still experimental?
      // // We don't allow optional variables because it's not typesafe
      // variables: 'jsVariables,
    }
  }

  type t<'data, 'variables> = {
    data: 'data,
    broadcast: option<bool>,
    id: string,
    fragment: Graphql.documentNode,
    fragmentName: option<string>,
    // variables: 'variables,
  }

  let toJs: (
    t<'data, 'variables>,
    ~serialize: // ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    'data => 'jsData,
  ) => // ~serializeVariables: 'variables => 'jsVariables
  Js_.t<'jsData, 'jsVariables> = (t, ~serialize) => {
    data: t.data->serialize,
    broadcast: t.broadcast,
    id: t.id,
    fragment: t.fragment,
    fragmentName: t.fragmentName,
    // variables: t.variables->serializeVariables->mapJsVariables,
  }
}
