[@react.component]
let make = () => {
  <ApolloClient.React.ApolloProvider client=Client.instance>
    <h2> "Hooks Usage"->React.string </h2>
    <h4> "Simple Query"->React.string </h4>
    <Query_OverlySimple />
    <h4> "Typical Query"->React.string </h4>
    <Query_Typical />
    <h4> "Lazy Query"->React.string </h4>
    <Query_Lazy />
    <h4> "Mutation"->React.string </h4>
    <Mutation />
    <h2> "Client Usage"->React.string </h2>
    <ClientBasics />
    <h2> "Fragments Usage"->React.string </h2>
    <Query_Fragments />
  </ApolloClient.React.ApolloProvider>;
};
