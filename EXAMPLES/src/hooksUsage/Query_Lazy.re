module PersonsOlderThanQuery = [%graphql
  {|
  query getPersonsOlderThan($age: Int!) {
    allPersons(filter: { age_gte: $age } ) {
      id
    }
  }
  |}
];

let age = 40;

[@react.component]
let make = () => {
  let (executeQuery, queryResult) =
    PersonsOlderThanQuery.useLazyWithVariables(
      ~fetchPolicy=CacheAndNetwork,
      ~errorPolicy=All,
      PersonsOlderThanQuery.makeVariables(~age, ()),
    );
  <div>
    {switch (queryResult) {
     | Unexecuted(_) =>
       <>
         "Waiting to be executed... "->React.string
         <button onClick={_ => executeQuery()} value="execute">
           "Execute"->React.string
         </button>
       </>
     | Executed({loading: true, data: None}) =>
       <p> "Loading"->React.string </p>
     | Executed({loading, data: Some(data), error}) =>
       <>
         <dialog>
           {loading ? <p> "Refreshing..."->React.string </p> : React.null}
           {switch (error) {
            | Some(_) =>
              <p>
                "The query went wrong, data may be incomplete"->React.string
              </p>
            | None => React.null
            }}
         </dialog>
         <h3>
           {React.string(
              "There are "
              ++ data.allPersons->Belt.Array.length->string_of_int
              ++ " people older than "
              ++ age->string_of_int,
            )}
         </h3>
       </>
     | Executed({loading: false, data: None}) =>
       <p> "Error loading data"->React.string </p>
     }}
  </div>;
};
