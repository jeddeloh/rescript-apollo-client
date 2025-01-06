module Ast = ApolloClient__Graphql_Language_Ast
module Location = ApolloClient__Graphql_Location
module Source = ApolloClient__Graphql_Language_Source.Source

// export class GraphQLError extends Error {
//   constructor(
//     message: string,
//     nodes?: Maybe<ReadonlyArray<ASTNode> | ASTNode>,
//     source?: Maybe<Source>,
//     positions?: Maybe<ReadonlyArray<number>>,
//     path?: Maybe<ReadonlyArray<string | number>>,
//     originalError?: Maybe<Error>,
//     extensions?: Maybe<{ [key: string]: any }>,
//   );
//   message: string;
//   readonly locations: ReadonlyArray<SourceLocation> | undefined;
//   readonly path: ReadonlyArray<string | number> | undefined;
//   readonly nodes: ReadonlyArray<ASTNode> | undefined;
//   readonly source: Source | undefined;
//   readonly positions: ReadonlyArray<number> | undefined;
//   readonly originalError: Maybe<Error>;
//   readonly extensions: { [key: string]: any } | undefined;
// }
type stringOrNumber

type t = {
  message: string,
  locations: option<array<Location.sourceLocation>>,
  path: option<array<stringOrNumber>>, // TODO: use union for string | number
  nodes: option<array<Ast.ASTNode.t>>,
  source: option<Source.t>,
  position: option<array<int>>,
  originalError: Js.nullable<Js.Exn.t>,
  extensions: option<Js.Dict.t<Js.Json.t>>,
}
