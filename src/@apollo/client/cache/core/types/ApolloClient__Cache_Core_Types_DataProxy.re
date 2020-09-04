module Graphql = ApolloClient__Graphql;

module Query = {
  module Js_ = {
    // interface Query<TVariables> {
    //   query: DocumentNode;
    //   variables?: TVariables;
    //   id?: string;
    // }
    type t('jsVariables) = {
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      id: option(string),
    };
  };

  type t('jsVariables) = Js_.t('jsVariables);
};

module Fragment = {
  module Js_ = {
    // interface Fragment<TVariables> {
    //   id: string;
    //   fragment: DocumentNode;
    //   fragmentName?: string;
    //   variables?: TVariables;
    // }
    type t('jsVariables) = {
      id: string,
      fragment: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      fragmentName: string,
      variables: option('jsVariables),
    };
  };

  type t('jsVariables) = Js_.t('jsVariables);
};

module WriteQueryOptions = {
  module Js_ = {
    // interface WriteQueryOptions<TData, TVariables> extends Query<TVariables> {
    //   data: TData;
    //   broadcast?: boolean;
    // }
    type t('jsData, 'jsVariables) = {
      data: 'jsData,
      broadcast: option(bool),
      // ...extends Query
      query: Graphql.documentNode,
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      id: option(string),
    };
  };

  type t('data, 'jsVariables) = {
    data: 'data,
    broadcast: option(bool),
    query: Graphql.documentNode,
    variables: 'jsVariables,
    id: option(string),
  };

  let toJs:
    (t('data, 'jsVariables), ~parse: 'jsData => 'data) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~parse) => {
      data: t.data->parse,
      broadcast: t.broadcast,
      query: t.query,
      variables: t.variables,
      id: t.id,
    };
};

module WriteFragmentOptions = {
  module Js_ = {
    // interface WriteFragmentOptions<TData, TVariables> extends Fragment<TVariables> {
    //    data: TData;
    //    broadcast?: boolean;
    // }
    type t('jsData, 'jsVariables) = {
      data: 'jsData,
      broadcast: option(bool),
      // ...extends Fragment
      id: string,
      fragment: Graphql.documentNode,
      fragmentName: option(string),
      // I think fragment variables are still experimental?
      // // We don't allow optional variables because it's not typesafe
      // variables: 'jsVariables,
    };
  };

  type t('data, 'jsVariables) = {
    data: 'data,
    broadcast: option(bool),
    id: string,
    fragment: Graphql.documentNode,
    fragmentName: option(string),
  };

  let toJs:
    (t('data, 'jsVariables), ~parse: 'jsData => 'data) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~parse) => {
      data: t.data->parse,
      broadcast: t.broadcast,
      id: t.id,
      fragment: t.fragment,
      fragmentName: t.fragmentName,
    };
};
