[@react.component]
let make = () => {
  <div>
    <h2> "Simple Query"->React.string </h2>
    <Query_OverlySimple />
    <h2> "Typical Query"->React.string </h2>
    <Query_Typical />
    <h2> "Lazy Query"->React.string </h2>
    <Query_Lazy />
    <h2> "Mutation"->React.string </h2>
    <Mutation />
    <h2> "Client Methods"->React.string </h2>
    <ClientBasics />
  </div>;
};
