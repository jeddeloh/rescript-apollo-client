module FieldNode = ApolloClient__Graphql.Language.Ast.FieldNode;

module FieldMergeFunction = {
  module Js_ = {
    type t;
  };
  type t = Js_.t;
};

module FieldReadFunction = {
  type t;

  module Js_ = {
    // export declare type FieldReadFunction<TExisting = any, TReadResult = TExisting> = (existing: SafeReadonly<TExisting> | undefined, options: FieldFunctionOptions) => TReadResult | undefined;
    type nonrec t = t;
  };
};

module KeySpecifier = {
  type t = array(string);
  module Js_ = {
    // declare type KeySpecifier = (string | any[])[];
    type nonrec t = t;
  };
};

module KeyArgsFunction = {
  type t_context = {
    typename: string,
    fieldName: string,
    field: Js.null(FieldNode.t),
    variables: option(Js.Json.t),
  };

  type t = (Js.nullable(Js.Json.t), t_context) => KeySpecifier.t;

  module Js_ = {
    // export declare type KeyArgsFunction = (args: Record<string, any> | null, context: {
    //     typename: string;
    //     fieldName: string;
    //     field: FieldNode | null;
    //     variables?: Record<string, any>;
    // }) => KeySpecifier | ReturnType<IdGetter>;
    type nonrec t = t;
  };
};

module FieldPolicy_KeyArgs = {
  type t =
    | KeySpecifier(KeySpecifier.t)
    | KeyArgsFunction(KeyArgsFunction.t)
    | False;

  module Js_ = {
    module KeyArgsUnion: {
      type t;
      let keySpecifier: KeySpecifier.Js_.t => t;
      let keyArgsFunction: KeyArgsFunction.Js_.t => t;
      let false_: t;
    } = {
      [@unboxed]
      type t =
        | Any('a): t;
      let keySpecifier = (v: KeySpecifier.Js_.t) => Any(v);
      let keyArgsFunction = (v: KeyArgsFunction.Js_.t) => Any(v);
      let false_ = Any(false);
    };

    type t = KeyArgsUnion.t;
  };

  let toJs: t => Js_.t =
    fun
    | KeySpecifier(keySpecifier) =>
      keySpecifier->Js_.KeyArgsUnion.keySpecifier
    | KeyArgsFunction(keyArgsFunction) =>
      keyArgsFunction->Js_.KeyArgsUnion.keyArgsFunction
    | False => Js_.KeyArgsUnion.false_;
};

module FieldPolicy = {
  type t = {
    keyArgs: option(FieldPolicy_KeyArgs.t),
    read: option(FieldReadFunction.t),
    merge: option(FieldMergeFunction.t),
  };

  module Js_ = {
    // export declare type FieldPolicy<TExisting = any, TIncoming = TExisting, TReadResult = TExisting> = {
    //     keyArgs?: KeySpecifier | KeyArgsFunction | false;
    //     read?: FieldReadFunction<TExisting, TReadResult>;
    //     merge?: FieldMergeFunction<TExisting, TIncoming> | boolean;
    // };
    type nonrec t = {
      keyArgs: option(FieldPolicy_KeyArgs.Js_.t),
      read: option(FieldReadFunction.t),
      merge: option(FieldMergeFunction.t),
    };
  };

  let toJs: t => Js_.t =
    t => {
      keyArgs: t.keyArgs->Belt.Option.map(FieldPolicy_KeyArgs.toJs),
      read: t.read,
      merge: t.merge,
    };
};
