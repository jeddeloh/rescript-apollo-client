module ApolloError = ApolloClient__Errors_ApolloError
module Graphql = ApolloClient__Graphql
module GraphQLError = ApolloClient__Graphql.Error.GraphQLError
module Observable = ApolloClient__ZenObservable.Observable
module Types = ApolloClient__Types
module Utils = ApolloClient__Utils

module GraphQLRequest = {
  module Js_ = {
    // export interface GraphQLRequest {
    //   query: DocumentNode;
    //   variables?: Record<string, any>;
    //   operationName?: string;
    //   context?: Record<string, any>;
    //   extensions?: Record<string, any>;
    // }
    type t = {
      query: Graphql.documentNode,
      variables: option<Js.Json.t>,
      operationName: option<string>,
      context: option<Js.Json.t>,
      extensions: option<Js.Json.t>,
    }
  }

  type t = Js_.t
}

module Operation = {
  type useMethodFunctionInThisModuleInstead

  module Js_ = {
    // export interface Operation {
    //     query: DocumentNode;
    //     variables: Record<string, any>;
    //     operationName: string;
    //     extensions: Record<string, any>;
    //     setContext: (context: Record<string, any>) => Record<string, any>;
    //     getContext: () => Record<string, any>;
    // }
    type t = {
      query: Graphql.documentNode,
      variables: Js.Json.t,
      operationName: string,
      extensions: Js.Json.t,
    }

    @send external getContext: t => Js.Json.t = "getContext"

    @send external setContext: (t, Js.Json.t) => Js.Json.t = "setContext"
  }

  type t = {
    query: Graphql.documentNode,
    variables: Js.Json.t,
    operationName: string,
    extensions: Js.Json.t,
    @as("rescript_setContext")
    setContext: Js.Json.t => Js.Json.t,
    @as("rescript_getContext")
    getContext: unit => Js.Json.t,
  }

  let preserveJsPropsAndContext: (Js_.t, t) => t = %raw(`
      function (js, t) {
        return Object.assign(js, t)
      }
    `)

  let fromJs: Js_.t => t = js =>
    preserveJsPropsAndContext(
      js,
      {
        query: js.query,
        variables: js.variables,
        operationName: js.operationName,
        extensions: js.extensions,
        setContext: context => js->Js_.setContext(context),
        getContext: () => js->Js_.getContext,
      },
    )

  external toJs: t => Js_.t = "%identity"
}

module FetchResult = {
  module Js_ = {
    // export interface FetchResult<TData = {
    //     [key: string]: any;
    // }, C = Record<string, any>, E = Record<string, any>> extends ExecutionResult {
    //     data?: TData | null;
    //     extensions?: E;
    //     context?: C;
    // }
    type t<'jsData> = {
      data: Js.Nullable.t<'jsData>,
      extensions: option<Js.Json.t>, // ACTUAL: Record<string, any>
      context: option<Js.Json.t>, // ACTUAL: Record<string, any>
      // ...extends ExecutionResult
      errors: option<array<GraphQLError.t>>,
    }
  }

  type t<'data> = {
    data: option<'data>,
    extensions: option<Js.Json.t>, // ACTUAL: Record<string, any>
    context: option<Js.Json.t>, // ACTUAL: Record<string, any>
    // ...extends ExecutionResult
    error: option<ApolloError.t>,
  }

  let fromJs: (Js_.t<'jsData>, ~safeParse: Types.safeParse<'data, 'jsData>) => t<'data> = (
    js,
    ~safeParse,
  ) => {
    let (data, error) = Utils.safeParseAndLiftToCommonResultProps(
      ~jsData=js.data->Js.toOption,
      ~graphQLErrors=?js.errors,
      safeParse,
    )
    {data: data, error: error, extensions: js.extensions, context: js.context}
  }

  let fromError: ApolloError.t => t<'data> = error => {
    data: None,
    extensions: None,
    context: None,
    error: Some(error),
  }

  type t__ok<'data> = {
    data: 'data,
    error: option<ApolloError.t>,
    extensions: option<Js.Json.t>,
    context: option<Js.Json.t>,
  }

  let toResult: t<'data> => Belt.Result.t<t__ok<'data>, ApolloError.t> = fetchResult =>
    switch fetchResult {
    | {data: Some(data)} =>
      Ok({
        data: data,
        error: fetchResult.error,
        extensions: fetchResult.extensions,
        context: fetchResult.context,
      })
    | {error: Some(error)} => Error(error)
    | {data: None, error: None} =>
      Error(
        ApolloError.make(
          ~errorMessage="No data and no error on FetchResult.t. Shouldn't this be impossible?",
          (),
        ),
      )
    }
}

module NextLink = {
  module Js_ = {
    // export declare type NextLink = (operation: Operation) => Observable<FetchResult>;
    type t = Operation.Js_.t => Observable.Js_.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>
  }

  // These are intentionally Js_.t because we can't know what to parse
  type t = Operation.t => Observable.Js_.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>
}

module RequestHandler = {
  module Js_ = {
    // export declare type RequestHandler = (operation: Operation, forward: NextLink) => Observable<FetchResult> | null;
    type t = (
      . Operation.Js_.t,
      NextLink.Js_.t,
    ) => Js.Null.t<Observable.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>>
  }

  // These are intentionally Js_.t because we can't know what to parse
  type t = (
    Operation.Js_.t,
    NextLink.Js_.t,
  ) => option<Observable.t<FetchResult.Js_.t<Js.Json.t>, Js.Exn.t>>

  let toJs: t => Js_.t = (t, . operation, forward) => t(operation, forward)->Js.Null.fromOption
}
