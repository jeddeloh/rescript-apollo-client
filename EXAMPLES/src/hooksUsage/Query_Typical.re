module QueryResult = ApolloClient.Types.QueryResult;

module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        id
        text
        completed
      }
    }
  |}
];

[@react.component]
let make = () => {
  let queryResult = TodosQuery.use();

  <div>
    {switch (queryResult) {
     | {loading: true, data: None} => <p> "Loading"->React.string </p>
     | {loading, data: Some({todos}), error} =>
       <>
         <dialog>
           {loading ? <p> "Refreshing..."->React.string </p> : React.null}
           {switch (error) {
            | Some(_) =>
              <p>
                "Something went wrong, data may be incomplete"->React.string
              </p>
            | None => React.null
            }}
         </dialog>
         <p>
           {React.string(
              "There are "
              ++ todos->Belt.Array.length->string_of_int
              ++ " To-Dos",
            )}
         </p>
         <p>
           <button
             onClick={_ =>
               queryResult
               ->QueryResult.fetchMore(
                   ~updateQuery=
                     (previousData, {fetchMoreResult}) => {
                       switch (fetchMoreResult) {
                       | Some({todos: newTodos}) => {
                           todos:
                             Belt.Array.concat(previousData.todos, newTodos),
                         }
                       | None => previousData
                       }
                     },
                   (),
                 )
               ->ignore
             }>
             "Fetch More!"->React.string
           </button>
         </p>
       </>
     | {loading: false, data: None} =>
       <p> "Error loading data"->React.string </p>
     }}
  </div>;
};
