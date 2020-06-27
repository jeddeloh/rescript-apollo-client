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
  let queryResult =
    PersonsOlderThanQuery.use(
      ~fetchPolicy=CacheAndNetwork,
      ~errorPolicy=All,
      PersonsOlderThanQuery.makeVariables(~age, ()),
    );

  <div>
    {switch (queryResult) {
     | {loading: true, data: None} => <p> "Loading"->React.string </p>
     | {loading, data: Some(data), error} =>
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
         <h4>
           {React.string(
              "There are "
              ++ data.allPersons->Belt.Array.length->string_of_int
              ++ " people older than "
              ++ age->string_of_int,
            )}
         </h4>
       </>
     | {loading: false, data: None} =>
       <p> "Error loading data"->React.string </p>
     }}
  </div>;
};
