module Graphql = ApolloClient__Graphql
module Utils = ApolloClient__Utils

module ReadQueryOptions = {
  module Js_ = {
    // interface Query<TVariables, TData> {
    //   query: DocumentNode | TypedDocumentNode<TData, TVariables>;
    //   variables?: TVariables;
    //   id?: string;
    // }
    // export interface ReadQueryOptions<TData, TVariables> extends Query<TVariables, TData> {
    //   returnPartialData?: boolean;
    //   optimistic?: boolean;
    //   canonizeResults?: boolean;
    // }
    type t<'jsVariables> = {
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      id: option<string>,
      // returnPartialData: option<bool>,
      optimistic: option<bool>,
      canonizeResults: option<bool>,
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
    // returnPartialData: t.returnPartialData,
    optimistic: t.optimistic,
    canonizeResults: t.canonizeResults,
  }
}

module ReadFragmentOptions = {
  module Js_ = {
    // interface Fragment<TVariables> {
    //   id: string;
    //   fragment: DocumentNode;
    //   fragmentName?: string;
    //   variables?: TVariables;
    // }
    // export interface ReadFragmentOptions<TData, TVariables> extends Fragment<TVariables, TData> {
    //   returnPartialData?: boolean;
    //   optimistic?: boolean;
    //   canonizeResults?: boolean;
    // }
    type t = {
      id: string,
      fragment: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      // variables: 'jsVariables,
      fragmentName: option<string>,
      // returnPartialData: option<bool>,
      optimistic: option<bool>,
      canonizeResults: option<bool>,
    }
  }

  type t = Js_.t = {
    id: string,
    fragment: Graphql.documentNode,
    // We don't allow optional variables because it's not typesafe
    // variables: 'jsVariables,
    fragmentName: option<string>,
    // returnPartialData: option<bool>,
    optimistic: option<bool>,
    canonizeResults: option<bool>,
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
      overwrite: option<bool>,
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
    overwrite: option<bool>,
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
    overwrite: t.overwrite,
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
      overwrite: option<bool>,
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
    overwrite: option<bool>,
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
    overwrite: t.overwrite,
    id: t.id,
    fragment: t.fragment,
    fragmentName: t.fragmentName,
    // variables: t.variables->serializeVariables->mapJsVariables,
  }
}

module UpdateQueryOptions = {
  module Js_ = {
    // interface UpdateQueryOptions<TData, TVariables> extends Omit<(
    //   ReadQueryOptions<TData, TVariables> &
    //   WriteQueryOptions<TData, TVariables>
    // ), 'data'> {}
    type t<'jsVariables> = {
      // ReadQueryOptions<TData, TVariables>
      // ...extends Query
      id: option<string>,
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      // ...extends ReadQueryOptions
      optimistic: option<bool>,
      canonizeResults: option<bool>,
      // ...extends Omit<WriteQueryOptions, 'data'>
      // returnPartialData: option<bool>, // Don't believe this is supported by graphql-ppx
      broadcast: option<bool>,
      overwrite: option<bool>,
    }
  }

  type t<'variables> = {
    id: option<string>,
    query: Graphql.documentNode,
    variables: 'variables,
    optimistic: option<bool>,
    canonizeResults: option<bool>,
    // returnPartialData: option<bool>, // Don't believe this is supported by graphql-ppx
    broadcast: option<bool>,
    overwrite: option<bool>,
  }

  let toJs: (
    t<'variables>,
    ~mapJsVariables: 'jsVariables => 'jsVariables=?,
    ~serializeVariables: 'variables => 'jsVariables,
  ) => Js_.t<'jsVariables> = (t, ~mapJsVariables=Utils.identity, ~serializeVariables) => {
    id: t.id,
    query: t.query,
    variables: t.variables->serializeVariables->mapJsVariables,
    optimistic: t.optimistic,
    canonizeResults: t.canonizeResults,
    broadcast: t.broadcast,
    overwrite: t.overwrite,
    // returnPartialData: t.returnPartialData, // Don't believe this is supported by graphql-ppx
  }
}

module UpdateFragmentOptions = {
  module Js_ = {
    // interface UpdateFragmentOptions<TData, TVariables> extends Omit<(
    //   ReadFragmentOptions<TData, TVariables> &
    //   WriteFragmentOptions<TData, TVariables>
    // ), 'data'> {}
    type t<'jsVariables> = {
      // ReadFragmentOptions<TData, TVariables>
      // ...extends Fragment
      id: string,
      fragment: Graphql.documentNode,
      fragmentName: option<string>,
      // We don't allow optional variables because it's not typesafe
      // variables: 'jsVariables,
      // ...extends ReadFragmentOptions
      optimistic: option<bool>,
      canonizeResults: option<bool>,
      // ...extends Omit<WriteFragmentOptions, 'data'>
      // returnPartialData: option<bool>, // Don't believe this is supported by graphql-ppx
      broadcast: option<bool>,
      overwrite: option<bool>,
    }
  }

  type t<'variables> = {
    id: string,
    fragment: Graphql.documentNode,
    fragmentName: option<string>,
    // variables: 'variables,
    optimistic: option<bool>,
    canonizeResults: option<bool>,
    // returnPartialData: option<bool>, // Don't believe this is supported by graphql-ppx
    broadcast: option<bool>,
    overwrite: option<bool>,
  }

  let toJs: t<'variables> => Js_.t<'jsVariables> = t => {
    id: t.id,
    fragment: t.fragment,
    fragmentName: t.fragmentName,
    // variables: t.variables,
    optimistic: t.optimistic,
    canonizeResults: t.canonizeResults,
    broadcast: t.broadcast,
    overwrite: t.overwrite,
    // returnPartialData: t.returnPartialData, // Don't believe this is supported by graphql-ppx
  }
}
