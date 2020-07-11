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
  let (executeQuery, queryResult) = TodosQuery.useLazy();
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
     | Executed({loading, data: Some({todos}), error}) =>
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
       </>
     | Executed({loading: false, data: None}) =>
       <p> "Error loading data"->React.string </p>
     }}
  </div>;
};
