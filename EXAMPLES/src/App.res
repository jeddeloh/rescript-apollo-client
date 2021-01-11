@react.component
let make = () =>
  <ApolloClient.React.ApolloProvider client=Apollo.client>
    <h2> {"Fetching Data with Hooks"->React.string} </h2>
    <h4> {"Simple Query"->React.string} </h4>
    <Query_OverlySimple />
    <h4> {"Typical Query"->React.string} </h4>
    <Query_Typical />
    <h4> {"Lazy Query"->React.string} </h4>
    <Query_Lazy />
    <h4> {"Mutation"->React.string} </h4>
    <Mutation />
    <h4> {"Subcription"->React.string} </h4>
    <Subscription />
    <h4> {"Query with Subscription for More"->React.string} </h4>
    <Query_SubscribeToMore />
    <h2> {"Fetching Data Directly with the Client"->React.string} </h2>
    <ClientBasics />
    <h2> {"Fragments"->React.string} </h2>
    <Query_Fragments />
  </ApolloClient.React.ApolloProvider>
