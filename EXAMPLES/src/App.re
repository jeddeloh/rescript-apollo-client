[@react.component]
let make = () => {
  <div>
    <h2> "Simple Query"->React.string </h2>
    <Query_OverlySimple />
    <h2> "Query"->React.string </h2>
    <Query_Typical />
    <h2> "Mutation"->React.string </h2>
    <Mutation />
    <h2> "Lazy Query"->React.string </h2>
    <Query_Lazy />
  </div>;
};
