@react.component @module("@apollo/client/testing")
external make: (
  ~mocks: array<mock<'jsVariables>>,
  ~addTypeName: bool=?,
  ~cache: InMemoryCache.t=?,
  ~children: React.element,
) => React.element = "MockedProvider"
