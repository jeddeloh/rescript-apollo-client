const {
  ensureApolloError,
} = require("../ApolloClient__Errors_ApolloError.bs").Js_;
const { ApolloError } = require("@apollo/client");
console.log(ensureApolloError);

describe("dealing with garbage", () => {
  it("ignores proper ApolloErrors", () => {
    let networkError = new Error("This should be preserved");
    let apolloError = new ApolloError({ networkError });
    const checkedApolloError = ensureApolloError(apolloError);

    expect(checkedApolloError.networkError).toBe(networkError);
  });

  it("should intelligently wrap a GrapqhQLError masquerading as ApolloError", () => {
    const apolloError = ensureApolloError({
      message: "this is a graphql error",
      extensions: { code: "some_code" },
    });

    expect(apolloError.graphQLErrors[0].extensions.code).toBe("some_code");
  });
});
