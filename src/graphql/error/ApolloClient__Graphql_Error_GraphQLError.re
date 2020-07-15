module Location = ApolloClient__Graphql_Location;

type t = {
  message: string,
  locations: option(array(Location.sourceLocation)),
  // Union? https://bucklescript.github.io/blog/2020/02/07/union-types-in-bucklescript
  path: option(array(string)) // ACTUAL: string | number
};
